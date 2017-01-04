//
//  PairSensorFusionErrorCode.h
//  PairSDK
//
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#ifndef PairSensorFusionErrorCode_h
#define PairSensorFusionErrorCode_h

typedef enum
{
    /*! No error has occurred. */
    PairSensorFusionErrorCodeNone = 0,
    /*! No visual features were detected in the most recent image. This is normal in some circumstances, such as quick motion or if the device temporarily looks at a blank wall. PairSensorFusion will continue. When features are detected again, [PairSensorFusionDelegate sensorFusionDidChangeStatus] will be called again with PairSensorFusionStatus.error set to nil. If the time between these two events is more than a couple seconds, it is likely to be unrecoverable.*/
    PairSensorFusionErrorCodeVision = 1,
    /*! The device moved more rapidly than expected for typical handheld motion. This may indicate that PairSensorFusion has failed and is providing invalid data. PairSensorFusion will be reset.*/
    PairSensorFusionErrorCodeTooFast = 2,
    /*! A fatal internal error has occured. Please contact RealityCap and provide [PairSensorFusionStatus statusCode] from the status property of the last received PairSensorFusionData object. PairSensorFusion will be reset.*/
    PairSensorFusionErrorCodeOther = 3,
    /*! A license error indicates that the license has not been properly validated, or needs to be validated again.*/
    PairSensorFusionErrorCodeLicense = 4
} PairSensorFusionErrorCode;

#endif /* PairSensorFusionErrorCode_h */
