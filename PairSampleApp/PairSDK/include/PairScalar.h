//
//  PairScalar.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! Represents a scalar value and its standard deviation. */
@interface PairScalar : NSObject
@property (nonatomic, readonly) float scalar;
@property (nonatomic, readonly) float standardDeviation;
@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

- (instancetype)initWithScalar:(float)scalar withStandardDeviation:(float)standardDeviation;
@end
