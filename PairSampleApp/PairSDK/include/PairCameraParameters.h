//
//  PairCameraParameters.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! Represents the optical, or intrinsic properties of a camera.

 See http://www.vision.caltech.edu/bouguetj/calib_doc/ for more information.
 */
@interface PairCameraParameters : NSObject

/*! The focal length of the camera, in units of pixels. */
@property (nonatomic, readonly) float focalLength;

/*! The horizontal position of the optical center of the camera, in units of pixels.

 A nominal 640x480 camera has its optical center at position (319.5, 239.5). */
@property (nonatomic, readonly) float opticalCenterX;

/*! The vertical position of the optical center of the camera, in units of pixels.

 A nominal 640x480 camera has its optical center at position (319.5, 239.5). */
@property (nonatomic, readonly) float opticalCenterY;

/*! The coefficient of the second degree polynomial to compensate for radial distortion. In most representations, this is the first "K" parameter. */
@property (nonatomic, readonly) float radialSecondDegree;

/*! The coefficient of the fourth degree polynomial to compensate for radial distortion. In most representations, this is the second "K" parameter. */
@property (nonatomic, readonly) float radialFourthDegree;

@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

/*! You will not typically need to instantiate this class yourself. */
- (instancetype)initWithFocalLength:(float)focalLength
                 withOpticalCenterX:(float)opticalCenterX
                 withOpticalCenterY:(float)opticalCenterY
             withRadialSecondDegree:(float)radialSecondDegree
             withRadialFourthDegree:(float)radialFourthDegree;
@end
