//
//  PairAsset.h
//  PairSDK
//
//  Created by Matt Loflin on 10/18/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import "PairAssetLoaderProtocol.h"
#import "PairFrame.h"

/*!
 @brief PairAsset are added to the PairView. They include a representation of a 3D model.
 @discussion Use Pair's custom model format to load 3D mesh and texture information, as well as optional swappable swatches.
 */
@interface PairAsset : NSObject

/*!
 @brief The asset's frame information (model matrix).
 */
@property (nonatomic, strong, nonnull) PairFrame *frame;

/*!
 @brief Optional dictionary for storing asset related information.
 */
@property (nonatomic, strong, nullable) NSDictionary *infoDictionary;

/*!
 @brief The number of swatches available. Will be zero if the asset does not support swappable swatches.
 */
@property (nonatomic, readonly) NSUInteger numberOfSwatches;

/*!
 @brief The currently active swatch index. Defaults to 0. Is ignored if the asset does not support swappable swatches.
 @discussion Set to a value between 0 and numberOfSwatches - 1 to change the rendered swatch.
 */
@property (nonatomic, assign) NSUInteger activeSwatchIndex;

/*!
 @brief An array of thumbnail images.
 */
@property (nonatomic, readonly, nonnull) NSArray<UIImage *> *swatchThumbnailImages;

/*!
 @brief The scalar used to convert the model unit dimensions to meters. Default value is 1 unit per meter.
 */
@property (nonatomic, readonly) float unitsPerMeter;

/*!
 @brief Initializes a PairAsset from a local file at the specified URL.
 @param modelURL A URL specifying the location of the PairAsset file. Must be on the device's local filesystem.
 @return A new PairAsset object.
 */
- (nullable instancetype)initWithURL:(nonnull NSURL *)modelURL;

/*!
 @brief Initializes a PairAsset from a local file at the specified URL.
 @param modelURL A URL specifying the location of the PairAsset file. Must be on the device's local filesystem.
 @param unitsPerMeter Apply a scalar used to convert the model unit dimensions to meters.
 @return A new PairAsset object.
 */
- (nullable instancetype)initWithURL:(nonnull NSURL *)modelURL andUnitsPerMeter:(float)unitsPerMeter;

/*!
 @brief Initializes a PairAsset using the specified PairAssetLoader.
 @discussion While the asset is loading a placeholder wireframe bounding box will be displayed in it's place.
 @param pairAssetLoader A loader object, conforming to the PairAssetLoaderProtocol, that will be used to asyncronously load the PairAsset model.
 @return A new PairAsset object.
 */
- (nullable instancetype)initWithPairAssetLoader:(nonnull id<PairAssetLoaderProtocol>)pairAssetLoader;

/*!
 @brief Initializes a PairAsset using the specified PairAssetLoader and units per meter.
 @discussion While the asset is loading a placeholder wireframe bounding box will be displayed in it's place.
 @param pairAssetLoader A loader object, conforming to the PairAssetLoaderProtocol, that will be used to asyncronously load the PairAsset model.
 @param unitsPerMeter Apply a scalar used to convert the model unit dimensions to meters.
 @return A new PairAsset object.
 */
- (nullable instancetype)initWithPairAssetLoader:(nonnull id<PairAssetLoaderProtocol>)pairAssetLoader andUnitsPerMeter:(float)unitsPerMeter;

@property (nonatomic, readonly, nullable) NSString *meshName __deprecated; // TODO: Not sure if this should be exposed in the API.
@property (nonatomic, readonly) NSTimeInterval totalTimeViewed __deprecated; // TODO: Not sure if this should be exposed in the API.
@end
