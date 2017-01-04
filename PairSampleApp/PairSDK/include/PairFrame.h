//
//  PairFrame.h
//  PairSDK
//
//  Created by Matt Loflin on 10/12/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

@interface PairFrame : NSObject <NSCopying>
@property (nonatomic, assign) GLKVector3 position;
@property (nonatomic, assign) GLKVector3 scale;
@property (nonatomic, assign) float yawRadians;
- (GLKMatrix4)matrix;
@end
