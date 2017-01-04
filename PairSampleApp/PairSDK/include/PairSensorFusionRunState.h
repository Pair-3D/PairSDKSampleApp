//
//  PairSensorFusionRunState.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#ifndef PairSensorFusionRunState_h
#define PairSensorFusionRunState_h

typedef enum
{
    /*! PairSensorFusion is inactive. */
    PairSensorFusionRunStateInactive = 0,
    /*! PairSensorFusion is in static calibration mode. The device should not be moved or touched. Progress is available on [PairSensorFusionStatus calibrationProgress]. */
    PairSensorFusionRunStateStaticCalibration = 1,
    /*! startSensorFusionWithDevice: has been called, and PairSensorFusion is in the handheld steady initialization phase. Progress is available on [PairSensorFusionStatus calibrationProgress]. */
    PairSensorFusionRunStateSteadyInitialization = 2,
    /*! startSensorFusionUnstableWithDevice: has been called, and PairSensorFusion is in the handheld dynamic initialization phase. Progress is available on [PairSensorFusionStatus calibrationProgress]. */
    PairSensorFusionRunStateDynamicInitialization = 3,
    /*! PairSensorFusion is active and updates are being provided with all data. */
    PairSensorFusionRunStateRunning = 4,
    /*! PairSensorFusion is in handheld portrait calibration mode. The device should be held steady in portrait orientation, perpendicular to the floor. Progress is available on [PairSensorFusionStatus calibrationProgress]. */
    PairSensorFusionRunStatePortraitCalibration = 5,
    /*! PairSensorFusion is in handheld landscape calibration mode. The device should be held steady in landscape orientation, perpendicular to the floor. Progress is available on [PairSensorFusionStatus calibrationProgress]. */
    PairSensorFusionRunStateLandscapeCalibration = 6
} PairSensorFusionRunState;

#endif /* PairSensorFusionRunState_h */
