//
//  PairView.h
//  Pair
//
//  Created by Matt Loflin on 9/22/16.
//  Copyright © 2016 Pair. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PairAsset.h"
#import "PairCamera.h"
#import "PairRay.h"
#import "PairSensorFusionData.h"
#import "PairSensorFusionStatus.h"

@protocol PairViewRenderDelegate;
@protocol PairViewModelDelegate;
@protocol PairViewSensorFusionDelegate;
@protocol PairViewRecordingDelegate;

/*!
 @brief A sucblass of UIView that encompases the Pair Augmented Reality view.
 @discussion The PairView is a rectangular area on the screen that renders the Augmented Reality view.
 The view consists of the live camera feed and added PairAsset objects that maintain their position using
 computer vision tracking and device location services. The PairView allows users to manipulate
 the orientation of PairAsset objects using touch gestures.
 The PairView supports video and image capture of the view.
 */
@interface PairView : UIView

/*!
 @brief Attach this delegate to be notified of events related to PairAsset.
 */
@property (nonatomic, weak, nullable) IBOutlet id<PairViewModelDelegate> modelDelegate;

/*!
 @brief Attach this delegate to be notified where video recordings are stored and move them if necessary.
 */
@property (nonatomic, weak, nullable) IBOutlet id<PairViewRecordingDelegate> recordingDelegate;

/*!
 @brief Attach this delegate to receive sensor fusion and status updates.
 */
@property (nonatomic, weak, nullable) IBOutlet id<PairViewSensorFusionDelegate> sensorFusionDelegate;

/*!
 @brief Experimental - Beta.
 */
@property (nonatomic, weak, nullable) IBOutlet id<PairViewRenderDelegate> renderDelegate;

/*!
 @brief Access to the camera class.
 @discussion Control of the camera is handled by the PairSDK.
 */
@property (nonatomic, readonly, nonnull) PairCamera *camera;

/*!
 @brief If true, display dimensions using the metric system. 
        If false, display dimensions using the imperial system. Default is false.
 */
@property (nonatomic, assign) BOOL isMetric;

/*!
 @brief Notify view of a size change.
 @discussion While this may be needed in the case of an iPad app that supports split screen functionality.
 It is not recommened that this be used for device rotation. Pair recommends locking the view to one orienation
 (e.g. Portrait or Landscape). 
 Calling this does result in a substantial portion of the rendering logic being destroyed and recreated.
 @param size new size of the view.
 */
- (void)viewWillTransitionToSize:(CGSize)size;

/*!
 @brief Call when wanting to start or resume AR tracking and rendering.
 */
- (void)resume;

/*!
 @brief Call when wanting to pause AR tracking and rendering.
 */
- (void)pause;

/*!
 @brief Reset the camera to the default height and recalibrate.
 */
- (void)recenter;

/*!
 @brief Capture a screenshot of the view.
 @return captured image of the view.
 */
- (nonnull UIImage *)screenshot;

/*!
 @brief Start video recording of the view.
 @discussion Use the PairViewRecordingDelegate to to notified of where and when the video file has been saved.
 */
- (void)startVideoRecording;

/*!
 @brief Stop video recording of the view.
 @discussion Use the PairViewRecordingDelegate to to notified of where and when the video file has been saved.
 */
- (void)stopVideoRecording;

/*!
 @brief Property indicating if the view is recording video.
 */
@property (nonatomic, readonly) BOOL isRecordingVideo;

/*!
 @brief The PairAsset objects attached to this view.
 */
@property (nonatomic, readonly, nonnull) NSArray<PairAsset *> *pairAssets;

/*!
 @brief The PairAsset object that has focus.
 */
@property (nonatomic, strong, nullable) PairAsset *selectedPairAsset;

/*!
 @brief Add a PairAsset object to the view.
 @param pairAsset The PairAsset object to be added to the view.
 */
- (void)addPairAsset:(nonnull PairAsset *)pairAsset;

/*!
 @brief Add a PairAsset object to a specific location in the view.
 @param pairAsset The PairAsset object to be added to the view.
 @param point The 2D screen coordinates (standard cocoa coordinate system x = 0 is left and y = 0 is top).
 */
- (void)addPairAsset:(nonnull PairAsset *)pairAsset atPoint:(CGPoint)point;

/*!
 @brief Remove a PairAsset object from the view.
 @param pairAsset The PairAsset object to be removed to the view. Does nothing if the PairAsset does not already exist.
 */
- (void)removePairAsset:(nonnull PairAsset *)pairAsset;

/*!
 @brief Remove all PairAsset objects from the view.
 */
- (void)removeAllPairAssets;

/*!
 @brief Set the 3D world space position of a PairAsset object using 2D screen space coordinates. 
 @discussion To set the 3D world space position of the PairAsset explicitly, use the PairAsset object's frame property.
 @param pairAsset The PairAsset to be repositioned.
 @param point The 2D screen coordinates (standard cocoa coordinate system x = 0 is left and y = 0 is top).
 */
- (void)setPositionOfPairAsset:(nonnull PairAsset *)pairAsset atPoint:(CGPoint)point;
@end


/*!
 @brief Attach this delegate to be notified of events related to PairAsset.
 */
@protocol PairViewModelDelegate <NSObject>
@optional
/*!
 @brief Called when the the PairAsset is added to the view and completes loading.
 @discussion If the PairAsset was loaded with a PairAssetLoader, this delegate function will be called after the model file has been completely loaded. If the PairAsset was loaded directly from on an on disk URL it will be called immeditely.
 @param pairAsset The newly loaded PairAsset.
 */
- (void)onDidLoadPairAsset:(nonnull PairAsset *)pairAsset;

/*!
 @brief Called when the the PairAsset is removed from the view.
 @param pairAsset The unloaded PairAsset.
 */
- (void)onDidUnloadPairAsset:(nonnull PairAsset *)pairAsset;

/*!
 @brief Called when a PairAsset will be marked as selected.
 @param pairAsset The about to be selected PairAsset.
 */
- (void)onWillSelecteModel:(nonnull PairAsset *)pairAsset;

/*!
 @brief Called when a PairAsset will become unselected.
 @param pairAsset The about to be unselected PairAsset.
 */
- (void)onWillDeselecteModel:(nonnull PairAsset *)pairAsset;

/*!
 @brief Called when a PairAsset has been tapped.
 @param pairAsset The PairAsset that was tapped.
 @param distanceInMeters The distance from the camera to the PairAsset.
 */
- (void)onTappedPairAsset:(nonnull PairAsset *)pairAsset atDistanceInMeters:(float)distanceInMeters __deprecated;
@end


/*!
 @brief Attach this delegate to be notified where video recordings are stored and move them if necessary.
 */
@protocol PairViewRecordingDelegate <NSObject>
@optional
/*!
 @brief Called when video recording stops.
 @param filePathURL The path to the new video file.
 */
- (void)onVideoRecordingSaved:(nonnull NSURL *)filePathURL;
@end


/*!
 @brief Attach this delegate to receive sensor fusion and status updates.
 */
@protocol PairViewSensorFusionDelegate <NSObject>
@optional
/*!
 @brief Called each frame at a rate of roughly 30 times per second.
 @param data The most recent collection of translation, rotation, point cloud, and other sensor data.
 */
- (void)onSensorFusionDidUpdateData:(nonnull PairSensorFusionData *)data;

/*!
 @brief Called when there is a status change to the sensor fusion data.
 @param status The current sensor fusion status.
 */
- (void)onSensorFusionDidChangeStatus:(nonnull PairSensorFusionStatus *)status;
@end


/*!
 @brief Experimental - Beta.
 */
@protocol PairViewRenderDelegate <NSObject>
@required
- (void)willRenderWithSensorFusionData:(nonnull PairSensorFusionData *)data withCameraToScreenMatrix:(GLKMatrix4)cameraToScreen;
@end
