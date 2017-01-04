//
//  PairTranslation.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import "PairVector.h"
#import "PairPoint.h"
#import "PairScalar.h"

/*! Represents a 3D translation in units of meters. */
@interface PairTranslation : PairVector

/*! Compute the straight line distance spanned by the translation.
 @returns An PairScalar object representing the distance in meters.
 */
@property (nonatomic, readonly) PairScalar *getDistance;

/*! Compute the inverse translation.
 @returns The inverse of the translation.
 */
@property (nonatomic, readonly) PairTranslation *getInverse;

/*! Apply the translation to a point.
 @param point An PaitPoint object
 @returns The translated version of the point.
 */
- (PairPoint *)transformPoint:(PairPoint *)point;

/*! Flip one axis of the coordinate system to move between left and right handed coordinates.
 @param axis The zero-based index of the axis (x = 0, y = 1, z = 2). Other values produced undefined behavior.
 @returns The translation in the mirrored coordinate system.
 */
- (PairTranslation *)flipAxis:(int)axis;

/*! Compute the composition of two translations.

 Composition of transformations is commutative.

 @param other An PairTranslation object
 @returns An PairTranslation object representing the combined translation. */
- (PairTranslation *)composeWithTranslation:(PairTranslation *)other;

/*! Compute the translation between two points.
 @param fromPoint The first PaitPoint.
 @param toPoint The second PaitPoint.
 @return A new PairTranslation object that such that calling [PairTranslation transformPoint:fromPoint] would return a point with the same 3D position as toPoint.
 */
+ (PairTranslation *)translationFromPoint:(PairPoint *)fromPoint toPoint:(PairPoint *)toPoint;

@end
