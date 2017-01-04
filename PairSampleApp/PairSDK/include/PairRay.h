//
//  PairRay.h
//  PairSDK
//
//  Created by Matt Loflin on 10/11/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>

@interface PairRay : NSObject
@property (nonatomic, assign) GLKVector3 origin;
@property (nonatomic, assign) GLKVector3 direction;
@end
