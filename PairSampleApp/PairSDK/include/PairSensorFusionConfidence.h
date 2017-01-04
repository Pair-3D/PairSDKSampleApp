//
//  PairSensorFusionConfidence.h
//  PairSDK
//  
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#ifndef PairSensorFusionConfidence_h
#define PairSensorFusionConfidence_h

typedef enum
{
    /*! PairSensorFusion is not currently running (possibly due to failure). */
    PairSensorFusionConfidenceNone = 0,
    /*! The data has low confidence. This occurs if no visual features could be detected or tracked. */
    PairSensorFusionConfidenceLow = 1,
    /*! The data has medium confidence. This occurs when PairSensorFusion has recently been initialized, or has recovered from having few usable visual features, and continues until the user has moved sufficiently to produce reliable measurements. If the user moves too slowly or features are unreliable, this will not switch to PairSensorFusionConfidenceHigh, and measurements may be unreliable. */
    PairSensorFusionConfidenceMedium = 2,
    /*! Sufficient visual features and motion have been detected that measurements are likely to be accurate. */
    PairSensorFusionConfidenceHigh = 3
} PairSensorFusionConfidence;

#endif /* PairSensorFusionConfidence_h */
