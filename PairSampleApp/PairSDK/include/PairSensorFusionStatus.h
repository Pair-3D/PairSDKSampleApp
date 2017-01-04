//
//  PairSensorFusionStatus.h
//  PairSDK
//
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PairSensorFusionRunState.h"
#import "PairSensorFusionConfidence.h"

/*! Represents the status of the sensor fusion engine. */
@interface PairSensorFusionStatus : NSObject

/*! Specifies the internal state of PairSensorFusion.

 Sensor fusion states will change asynchronously with the requests made to PairSensorFusion. This property always describes the state the filter was in for the given update. Possible states are:

 - PairSensorFusionRunStateInactive - PairSensorFusion is inactive.
 - PairSensorFusionRunStateStaticCalibration - PairSensorFusion is in static calibration mode. The device should not be moved or touched. Progress is available on [PairSensorFusionStatus calibrationProgress].
 - PairSensorFusionRunStateSteadyInitialization - startSensorFusionWithDevice: has been called, and PairSensorFusion is in the handheld steady initialization phase. Progress is available on [PairSensorFusionStatus calibrationProgress].
 - PairSensorFusionRunStateDynamicInitialization - startSensorFusionUnstableWithDevice: has been called, and PairSensorFusion is in the handheld dynamic initialization phase. Progress is available on [PairSensorFusionStatus calibrationProgress].
 - PairSensorFusionRunStateRunning - PairSensorFusion is active and updates are being provided with all data.
 - PairSensorFusionRunStatePortraitCalibration - PairSensorFusion is in handheld portrait calibration mode. The device should be held steady in portrait orientation, perpendicular to the floor. Progress is available on [PairSensorFusionStatus calibrationProgress].
 - PairSensorFusionRunStateLandscapeCalibration - PairSensorFusion is in handheld landscape calibration mode. The device should be held steady in landscape orientation, perpendicular to the floor. Progress is available on [PairSensorFusionStatus calibrationProgress].
 */
@property (nonatomic, readonly) PairSensorFusionRunState runState;

/*!
 Convienance in accessing the PairSensorFusionRunState.
 */
@property (nonatomic, readonly) BOOL isInitializing;

/*! Indicates the progress in the current runState.

 If appropriate for the runState, such as PairSensorFusionRunStateStaticCalibration, the value of this property will be between 0 and 1 to indicate the progress of the action, such as calibration or initialization.
 */
@property (nonatomic, readonly) float progress;

/*! Specifies the overall level of confidence that PairSensorFusion has in its output.

 PairSensorFusion requires both visual features and motion to provide accurate measurements. If no visual features are visible, the user doesn't move, or the user moves too slowly, then there will not be enough information available to reliably estimate data. If accuracy is important, apps should prompt the user to move the device with enough velocity to trigger PairSensorFusionConfidenceHigh before beginning a measurement. Possible states are:

 - PairSensorFusionConfidenceNone - PairSensorFusion is not currently running (possibly due to failure).
 - PairSensorFusionConfidenceLow - This occurs if no visual features could be detected or tracked.
 - PairSensorFusionConfidenceMedium - This occurs when PairSensorFusion has recently been initialized, or has recovered from having few usable visual features, and continues until the user has moved sufficiently to produce reliable measurements. If the user moves too slowly or features are unreliable, this will not switch to PairSensorFusionConfidenceHigh, and measurements may be unreliable.
 - PairSensorFusionConfidenceHigh - Sufficient visual features and motion have been detected that measurements are likely to be accurate.
 */
@property (nonatomic, readonly) PairSensorFusionConfidence confidence;

/*!
 Indicates the error, if any, that occurred. If a state change has occurred without an associated error, this property will be set to nil.
 Check this property on every invocation of [PairSensorFusionDelegate sensorFusionDidChangeStatus:].
 Check the class of the error to determine which type of error occured. The error class may be PairSensorFusionError or RCLicenseError.
 */
@property (nonatomic, readonly) NSError *error;

@property (nonatomic, readonly) NSDictionary *dictionaryRepresentation;

/*! You will not typically need to instantiate this class yourself. */
- (instancetype)initWithRunState:(PairSensorFusionRunState)runState
                    withProgress:(float)progress
                  withConfidence:(PairSensorFusionConfidence)confidence
                       withError:(NSError *)error;
@end
