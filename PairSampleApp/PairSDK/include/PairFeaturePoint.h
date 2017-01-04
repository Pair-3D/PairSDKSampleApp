//
//  PairFeaturePoint.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "PairScalar.h"
#include "PairPoint.h"

/*! Represents a visual feature detected and tracked by computer vision.

 Features are typically located at points in an image with strong visual contrast, such as corners. Such points typically correspond to fixed geometric points in the physical world. Most data in this class is defined relative to the most recently processed video frame, which is available in [PairSensorFusionData sampleBuffer].
 */
@interface PairFeaturePoint : NSObject

/*! A unique identifier for the feature.

 This identifier should be the same for a given feature when it is tracked or matched across frames, and globally unique for a given session of PairSensorFusion. Note that if a particular feature is not found in a frame, but is re-detected in a subsequent frame, a new id will be assigned. */
@property (nonatomic, readonly) uint64_t featurePointId;

/*! The horizontal position, in units of pixels, of the feature in the most recently processed video frame. */
@property (nonatomic, readonly) float x;

/*! The vertical position, in units of pixels, of the feature in the most recently processed video frame. */
@property (nonatomic, readonly) float y;

/*! The current estimate of the depth of the feature, in units of meters, relative to the camera position at the time the feature was first detected.

 Note: This is not the same as the distance of the feature from the camera. Instead it represents the translation of the feature along the camera's Z axis. */
@property (nonatomic, readonly) PairScalar *originalDepth;

/*! An PairPoint object representing the current estimate of the 3D position of the feature relative to the global reference frame, as defined in [PairSensorFusionData transformation]. */
@property (nonatomic, readonly) PairPoint *worldPoint;

/*! Flag reflecting whether the feature is initialized.

 When a feature is first detected, we have no information about its depth and therefore do not know its 3D position.

 TRUE if the feature has been tracked for sufficiently long that depth and worldPoint may be considered valid.
 */
@property (nonatomic, readonly) bool initialized;

@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

/*! A convenient way to get a CGPoint.

 @returns A CGPoint that represents the coordinates contained in this object. */
@property (nonatomic, readonly) CGPoint makeCGPoint;

/*!
 @returns A dictionary representation of the object for the purposes of JSON serialization.
 */
@property (nonatomic, readonly) NSDictionary *proxyForJson;

/*! You will not typically need to instantiate this class yourself. */
- (instancetype)initWithFeaturePointId:(uint64_t)featurePointId
                                 withX:(float)x
                                 withY:(float)y
                     withOriginalDepth:(PairScalar *)originalDepth
                        withWorldPoint:(PairPoint *)worldPoint
                       withInitialized:(bool)initialized;

/*! @returns The distance in pixels between two points. */
- (float)pixelDistanceToPoint:(CGPoint)cgPoint;
@end
