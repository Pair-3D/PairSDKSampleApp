//
//  PairCamera.h
//  PairSDK
//
//  Created by Matt Loflin on 10/5/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

/*!
 @brief The camera object that represents the orientation of the iOS device in the AR scene.
 It is attached to an PairView.
 */
@interface PairCamera : NSObject

/*!
 @brief The view matrix.
 */
@property (nonatomic, readonly) GLKMatrix4 viewMatrix;

/*!
 @brief The projection matrix.
 */
@property (nonatomic, readonly) GLKMatrix4 projectionMatrix;

/*!
 @brief The up vector.
 */
@property (nonatomic, readonly) GLKVector3 upVector;

/*!
 @brief The forward vector.
 */
@property (nonatomic, readonly) GLKVector3 forwardVector;

/*!
 @brief The position vector.
 */
@property (nonatomic, readonly) GLKVector3 positionVector;

/*!
 @brief Obtain the 2D screen space position coordinates of any 3D world space position.
 */
- (CGPoint)screenPositionFromWorldPosition:(GLKVector3)worldPosition;
@end
