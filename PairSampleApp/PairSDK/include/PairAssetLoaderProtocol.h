//
//  PairAssetLoaderProtocol.h
//  PairSDK
//
//  Created by Matt Loflin on 11/5/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <GLKit/GLKit.h>
#import <ModelIO/ModelIO.h>

typedef void (^PairAssetLoadSuccessBlock)(NSURL * _Nonnull modelURL);
typedef void (^PairAssetLoadErrorBlock)(NSError * _Nullable error);

/*!
 @brief A general protocol intended for the asynchronous loading of a PairAsset.
 @discussion Create your own custom implementation that conforms to the PairAssetLoaderProtocol and use it when initializing a PairAsset object. An example loader is provided with the PairSampleApp project that downloads and extracts a tar.gz file.
 */
@protocol PairAssetLoaderProtocol <NSObject>
/*!
 @brief Start loading the pair asset.
 @param successBlock usually good
 @param errorBlock usually bad
 */
- (void)loadWithSuccessBlock:(nullable PairAssetLoadSuccessBlock)successBlock andErrorBlock:(nullable PairAssetLoadErrorBlock)errorBlock;

/*!
 @brief Precentage of asset loaded.
 @returns A value in the range from 0 to 1. A value of 1 indicating 100% loaded, a value of 0 indicating nothing is loaded.
 */
@property (nonatomic, readonly) float percentLoaded;

/*!
 @brief Placeholder bounding box.
 @returns A bounding box used to render a placeholder box while the asset loads.
 */
@property (nonatomic, readonly) MDLAxisAlignedBoundingBox placeHolderBoundingBox;
@end
