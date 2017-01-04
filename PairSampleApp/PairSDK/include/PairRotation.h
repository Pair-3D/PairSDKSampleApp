//
//  PairRotation.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "PairPoint.h"
#include "PairTranslation.h"

/*! Represents a 3D rotation. */
@interface PairRotation: NSObject

/*! The w element of the quaternion. */
@property (nonatomic, readonly) float quaternionW;
/*! The x element of the quaternion. */
@property (nonatomic, readonly) float quaternionX;
/*! The y element of the quaternion. */
@property (nonatomic, readonly) float quaternionY;
/*! The z element of the quaternion. */
@property (nonatomic, readonly) float quaternionZ;

/*! Compute the inverse rotation.
 @returns The inverse of the rotation.
 */
@property (nonatomic, readonly) PairRotation *getInverse;

/*! Return a dictionary representation of the quaternion. */
@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

/*! Instantiate an PairRotation with the given quaternion parameters. */
- (instancetype)initWithQuaternionW:(float)w withX:(float)x withY:(float)y withZ:(float)z;
- (instancetype)initWithAxisX:(float)ax withAxisY:(float)ay withAxisZ:(float)az withAngle:(float)theta;

/*! Fills in a matrix representation of the rotation that is compatible with OpenGL.

 This matrix can be loaded in an OpenGL ES 2.0 shader by calling glUniformMatrix4fv, with transpose set to false.
 @param matrix A C-style array of 16 floats that will be overwritten with the rotation matrix.
 */
- (void)getOpenGLMatrix:(float[16])matrix;

/*! Apply the rotation to a point.
 @param point An PairPoint object
 @returns The rotated version of the point.
 */
- (PairPoint *)transformPoint:(PairPoint *)point;

/*! Apply the rotation to a translation vector.
 @param translation An PairTranslation object
 @returns The rotated version of the translation.
 */
- (PairTranslation *)transformTranslation:(PairTranslation *)translation;

/*! Flip one axis of the coordinate system to move between left and right handed coordinates.
 @param axis The zero-based index of the axis (x = 0, y = 1, z = 2). Other values produced undefined behavior.
 @returns The rotation in the mirrored coordinate system.
 */
- (PairRotation *)flipAxis:(int)axis;

/*! Compute the composition of two rotations.

 The composition is performed in such a way that, if R1 and R2 are PairRotation objects, and pt is an PairPoint object, the following two lines would produce the same results (up to numerical precision):

 [[R1 composeWithRotation:R2] transformPoint:pt];
 [R1 transformPoint:[R2 transformPoint:pt]];

 @param other An PairRotation object
 @returns An PairRotation object representing the combined rotation. */
- (PairRotation *)composeWithRotation:(PairRotation *)other;

@end
