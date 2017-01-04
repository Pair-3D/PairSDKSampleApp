//
//  PairSensorFusionData.h
//  PairSDK
//
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import "PairCameraParameters.h"
#import "PairScalar.h"
#import "PairTransformation.h"
#import "PairFeaturePoint.h"

/*!
 @brief This class represents a snapshot of the translation, rotation, point cloud, and other sensor fusion data at one moment in time.
 */
@interface PairSensorFusionData : NSObject

/*! An NSArray of PairFeaturePoint objects representing the visual features that were detected by computer vision in the most recent image. */
@property (nonatomic, readonly) NSArray<PairFeaturePoint *> *featurePoints;

/*! An PairTransformation object representing the rotation and translation of the device.

 The transformation is defined relative to a right-handed coordinate system in which the Z axis points straight up (as defined by gravity) and initial rotation about the Z axis is arbitrary. The translational origin is set when [PairSensorFusion startSensorFusion] is called. */
@property (nonatomic, readonly) PairTransformation* transformation;

/*! An PairTransformation object representing the current camera transformation relative to the global reference frame as defined for the transformation property. */
@property (nonatomic, readonly) PairTransformation* cameraTransformation;

/*! If the origin of cameraTransformation and transformation are currently being reported relative to a QR code, the decoded payload of the QR code. Otherwise, nil.
 */
@property (nonatomic, readonly) NSString *originQRCode;

/*! An PairCameraParameters object representing the current optical (intrinsic) properties of the camera. */
@property (nonatomic, readonly) PairCameraParameters *cameraParameters;

/*! An PairScalar object representing the total length of the path the device has traveled.

 Note: This length is not the straight-line distance, which can be computed by calling [PairSensorFusionData.transformation.translation getDistance]. Instead it is the total distance traveled by the device. For example, if the device is moved in a straight line for 1 meter, then returned directly to its starting point, totalPathLength will be 2 meters.
 */
@property (nonatomic, readonly) PairScalar* totalPathLength;

/*! A CMSampleBufferRef containing the video frame that was most recently processed.

 This image corresponds to the other data contained in this class, so for example, the x and y coordinates in the featurePoints array will correspond to the locations of the features detected in this image. If you are displaying an augmented reality view or video preview with any overlays, use this image. This will ensure that the data you draw with corresponds to the video frame being shown, which minimizes perceptible lag. If video data is not being processed, this property will be nil.
 */
@property (nonatomic, readonly) CMSampleBufferRef sampleBuffer;

/*! A uint64_t containing the time in microseconds when this PairSensorFusionData was calculated. */
@property (nonatomic, readonly) uint64_t timestamp;


/*! @returns A dictionary representation of the object, minus the sampleBuffer. */
@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

/*! @returns A dictionary representation of the object, minus the sampleBuffer and feature points. */
@property (nonatomic, readonly) NSDictionary *dictionaryRepresentationForJsonSerialization;

/*! You will not typically need to instantiate this class yourself. */
- (instancetype)initWithTransformation:(PairTransformation*)transformation
              withCameraTransformation:cameraTransformation
                  withCameraParameters:(PairCameraParameters *)cameraParameters
                         withTotalPath:(PairScalar *)totalPath
                          withFeatures:(NSArray<PairFeaturePoint *> *)featurePoints
                      withSampleBuffer:(CMSampleBufferRef)sampleBuffer
                         withTimestamp:(uint64_t)timestamp
                      withOriginQRCode:(NSString *)originQRCode;

@end
