//
//  PairAssetLoader.m
//  PairSampleApp
//
//  Created by Matt Loflin on 11/5/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import "NSData+GZip.h"
#import "NSFileManager+Tar.h"
#import "PairAsset.h"
#import "PairAssetLoader.h"

typedef void (^DownloadSuccessBlock)(NSData * _Nonnull data);
typedef void (^DownloadErrorBlock)(NSError * _Nullable error);

@interface PairAssetLoader ()
@property (nonatomic, assign) MDLAxisAlignedBoundingBox placeHolderBoundingBox;
@property (nonatomic, strong, nullable) NSURLSessionTask *task;
@property (nonatomic, strong, nullable) NSURL *remoteDownloadURL;
@property (nonatomic, strong, nullable) NSURL *localDirectoryURL;
@property (nonatomic, strong, nullable) NSURL *saveLocation;
@end

@implementation PairAssetLoader

- (void)dealloc
{
    [self.task cancel];
}

- (nullable instancetype)initWithRemoteDownloadURL:(nonnull NSURL *)URL
                                      saveLocation:(nonnull NSURL *)saveLocation
                         andPlaceholderBoundingBox:(MDLAxisAlignedBoundingBox)boundingBox
{
    self = [super init];
    if (self) {
        self.remoteDownloadURL = URL;
        self.saveLocation = saveLocation;
        self.placeHolderBoundingBox = boundingBox;

        // Save location should be specified, but fallback to the documents directory.
        if (!self.saveLocation) {
            NSURL *documentsDirectory = [NSFileManager.defaultManager URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask].lastObject;
            self.saveLocation = [documentsDirectory URLByAppendingPathComponent:@"PairTemp" isDirectory:YES];
        }
    }
    return self;
}

- (nullable instancetype)initWithLocalDirectoryURL:(nonnull NSURL *)URL
{
    self = [super init];
    if (self) {
        self.localDirectoryURL = URL;
        self.saveLocation = URL;
    }
    return self;
}

#pragma mark - PairAssetLoaderProtocol

- (void)loadWithSuccessBlock:(nullable PairAssetLoadSuccessBlock)successBlock andErrorBlock:(nullable PairAssetLoadErrorBlock)errorBlock
{
    if (self.localDirectoryURL) {
        NSURL *modelURL = [PairAssetLoader findModelFileInDirectory:self.localDirectoryURL];
        if (successBlock) {
            successBlock(modelURL);
        }
    } else if (self.remoteDownloadURL) {
        __weak typeof(self) weakSelf = self;
        [self downloadAssetAtURL:self.remoteDownloadURL withSuccessBlock:^(NSData * _Nonnull data) {
            __strong __typeof(&*weakSelf) strongSelf = weakSelf;
            if (!strongSelf) {
                return;
            }

            NSData *tarData = [data gunzippedData];
            if (tarData) {
                [NSFileManager.defaultManager createFilesAndDirectoriesAtURL:strongSelf.saveLocation
                                                                 withTarData:tarData
                                                                       error:nil
                                                                    progress:nil];

                // Go through the new files in the save location directory and make sure none are backed up to iCloud.
                [PairAssetLoader excludeFilesFromBackupInDirectory:strongSelf.saveLocation];

                if (successBlock) {
                    NSURL *modelURL = [PairAssetLoader findModelFileInDirectory:strongSelf.saveLocation];
                    successBlock(modelURL);
                }
            } else {
                if (errorBlock) {
                    errorBlock(nil);
                }
            }
        } andErrorBlock:^(NSError * _Nullable error) {
            if (errorBlock) {
                errorBlock(error);
            }
        }];
    } else {
        if (errorBlock) {
            NSLog(@"Can not load asset: No URL specified.");
            errorBlock(nil);
        }
    }
}

- (float)percentLoaded
{
    if (self.task.countOfBytesExpectedToReceive > 0 ) {
        return self.task.countOfBytesReceived / (float)self.task.countOfBytesExpectedToReceive;
    } else {
        return 0;
    }
}

#pragma mark - Private

- (void)downloadAssetAtURL:(nonnull NSURL *)url
          withSuccessBlock:(nullable DownloadSuccessBlock)successBlock
             andErrorBlock:(nullable DownloadErrorBlock)errorBlock
{
    [self.task cancel];

    void (^completionBlock)(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error);
    completionBlock = ^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"Failed to download asset: %@", error.localizedDescription);
                if (errorBlock) {
                    errorBlock(error);
                }
            });
        } else if ([response isKindOfClass:[NSHTTPURLResponse class]] && ((NSHTTPURLResponse *)response).statusCode != 200) {
            dispatch_async(dispatch_get_main_queue(), ^{
                NSLog(@"Failed to download asset: %ld", (long)((NSHTTPURLResponse *)response).statusCode);
                if (errorBlock) {
                    errorBlock(nil);
                }
            });
        } else {
            dispatch_async(dispatch_get_main_queue(), ^{
                if (successBlock) {
                    successBlock(data);
                }
            });
        }
    };

    self.task = [NSURLSession.sharedSession dataTaskWithURL:url completionHandler:completionBlock];
    [self.task resume];
}

+ (void)excludeFilesFromBackupInDirectory:(NSURL *)directoryPath
{
    NSArray<NSURL *> *fileURLs = [NSFileManager.defaultManager contentsOfDirectoryAtURL:directoryPath
                                                             includingPropertiesForKeys:nil
                                                                                options:NSDirectoryEnumerationSkipsSubdirectoryDescendants
                                                                                  error:nil];
    for (NSURL *url in fileURLs) {
        [url setResourceValue:@(YES) forKey:NSURLIsExcludedFromBackupKey error:nil];
    }
}

+ (nullable NSURL *)findModelFileInDirectory:(NSURL *)directoryPath
{
    NSArray *extensions = @[@"mdl"];
    NSArray<NSURL *> *dirContents = [NSFileManager.defaultManager contentsOfDirectoryAtURL:directoryPath
                                                                includingPropertiesForKeys:nil
                                                                                   options:NSDirectoryEnumerationSkipsSubdirectoryDescendants
                                                                                     error:nil];
    NSPredicate *predicate = [NSPredicate predicateWithFormat:@"pathExtension IN %@", extensions];
    return [dirContents filteredArrayUsingPredicate:predicate].lastObject;
}

@end
