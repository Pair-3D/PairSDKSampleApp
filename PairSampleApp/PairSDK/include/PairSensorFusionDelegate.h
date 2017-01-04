//
//  PairSensorFusionDelegate.h
//  PairSDK
//
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PairSensorFusionData.h"
#import "PairSensorFusionStatus.h"

/*! The delegate of PairSensorFusion must implement this protocol in order to receive sensor fusion updates. */
@protocol PairSensorFusionDelegate <NSObject>
/*! Sent to the delegate to provide the latest output of sensor fusion.

 This is called after each video frame is processed by PairSensorFusion, typically 30 times per second.
 @param data An instance of PairSensorFusionData that contains the latest sensor fusion data.
 */
- (void)didUpdateSensorFusionData:(PairSensorFusionData *)data;

/*! Sent to the delegate whenever the status of PairSensorFusion changes, including when an error occurs, or a previous error state is cleared.

 @param status An instance of PairSensorFusionStatus containing the current sensor fusion status.
 */
- (void)didChangeSensorFusionStatus:(PairSensorFusionStatus *)status;
@end
