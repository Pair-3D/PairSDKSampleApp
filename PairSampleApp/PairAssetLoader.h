//
//  PairAssetLoader.h
//  PairSampleApp
//
//  Created by Matt Loflin on 11/5/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <ModelIO/ModelIO.h>
#import "PairAssetLoaderProtocol.h"

@interface PairAssetLoader : NSObject <PairAssetLoaderProtocol>
- (nullable instancetype)initWithRemoteDownloadURL:(nonnull NSURL *)URL
                                      saveLocation:(nonnull NSURL *)saveLocation
                         andPlaceholderBoundingBox:(MDLAxisAlignedBoundingBox)boundingBox;

- (nullable instancetype)initWithLocalDirectoryURL:(nonnull NSURL *)URL;

+ (nullable NSURL *)findModelFileInDirectory:(nonnull NSURL *)directoryPath;
@end
