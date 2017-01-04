//
//  PairAssetRayIntersection.h
//  PairSDK
//
//  Created by Matt Loflin on 10/22/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>
#import "PairAsset.h"

@interface PairAssetRayIntersection : NSObject
@property (nonatomic, strong) PairAsset *pairAsset;
@property (nonatomic, assign) BOOL hasIntersection;
@property (nonatomic, assign) float intersectionTime;
@property (nonatomic, assign) GLKVector3 intersectionPosition;
@end
