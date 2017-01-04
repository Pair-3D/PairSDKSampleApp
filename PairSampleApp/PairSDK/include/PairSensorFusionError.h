//
//  PairSensorFusionError.h
//  PairSDK
//
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PairSensorFusionErrorCode.h"

@interface PairSensorFusionError : NSError
- (NSDictionary *)dictionaryRepresentation;
@end
