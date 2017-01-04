//
//  PairTransformation.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PairTranslation.h"
#import "PairRotation.h"
#import "PairPoint.h"

/*! Represents a 3D transformation. */
@interface PairTransformation : NSObject

/*! An PairTranslation object that represents the translation component. */
@property (nonatomic, readonly) PairTranslation* translation;

/*! An PairRotation object that represents the rotation component. */
@property (nonatomic, readonly) PairRotation* rotation;

/*! Compute the inverse transformation.
 @returns The inverse of the transformation.
 */
@property (nonatomic, readonly) PairTransformation *getInverse;

/*! Return a dictionary representation of the transformation. */
@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

/*! Instantiate an PairTransformation composed of the given rotation and translation.

 @param translation An PairTranslation object representing the desired translation.
 @param rotation An PairRotation object representing the desired rotation.
 */
- (instancetype)initWithTranslation:(PairTranslation*)translation withRotation:(PairRotation*)rotation;

/*! Fills in a matrix representation of the transformation that is compatible with OpenGL.

 This matrix can be loaded in an OpenGL ES 2.0 shader by calling glUniformMatrix4fv, with transpose set to false.
 @param matrix A C-style array of 16 floats that will be overwritten with the transformation matrix.
 */
- (void)getOpenGLMatrix:(float[16])matrix;

/*! Apply the transformation to a point.

 The rotation is applied first, then the translation.
 @param point An PairPoint object
 @returns The transformed version of the point.
 */
- (PairPoint *)transformPoint:(PairPoint *)point;

/*! Flip one axis of the coordinate system to move between left and right handed coordinates.
 @param axis The zero-based index of the axis (x = 0, y = 1, z = 2). Other values produced undefined behavior.
 @returns The transformation in the mirrored coordinate system.
 */
- (PairTransformation *)flipAxis:(int)axis;

- (PairTransformation *)transformCoordinatesWithTransform:(PairTransformation *)transform;

/*! Compute the composition of two transformations.

 The composition is performed in such a way that, if T1 and T2 are PairTransformation objects, and pt is an PairPoint object, the following two lines would produce the same results (up to numerical precision):

 [T1 composeWithTransformation:T2] transformPoint:pt];
 [T1 transformPoint:[T2 transformPoint:pt]];

 @param other An PairTransformation object
 @returns An PairTransformation object representing the combined transformation. */
- (PairTransformation *)composeWithTransformation:(PairTransformation *)other;

@end
