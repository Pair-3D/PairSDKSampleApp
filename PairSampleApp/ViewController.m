//
//  ViewController.m
//  PairSampleApp
//
//  Created by Matt Loflin on 11/14/16.
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import "PairAssetLoader.h"
#import "PairView.h"
#import "ViewController.h"

@interface ViewController () <PairViewModelDelegate, PairViewRecordingDelegate, PairViewSensorFusionDelegate>
@property (nonatomic, weak) IBOutlet UIButton *imageButton;
@property (nonatomic, weak) IBOutlet UIButton *addButton;
@property (nonatomic, weak) IBOutlet UIButton *videoButton;
@property (nonatomic, weak) IBOutlet UIButton *swatchButton;
@property (nonatomic, weak) IBOutlet PairView *pairView; // Used when loading from storyboard or xib.
//@property (nonatomic, strong) PairView *pairView; // Used when loading programmatically via one of he commented out options below.
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Delete the downloaded models each time the app launches because this sample app stores models
    // in the same location and it's expected that during testing the model URL might be changed.
    [NSFileManager.defaultManager removeItemAtURL:ViewController.saveLocation error:nil];

    self.edgesForExtendedLayout = UIRectEdgeTop;

    self.imageButton.hidden = YES;
    self.addButton.hidden = YES;
    self.videoButton.hidden = YES;
    self.swatchButton.hidden = YES;

    // In this example the PairView is loaded via storyboard. Commented out below are some alternative
    // methods for creating and attaching the PairView to your view hierarchy.

    /*
     // Option: Create PairView programmatically using autolayout.
     self.pairView = [PairView new];
     self.pairView.translatesAutoresizingMaskIntoConstraints = NO;
     [self.view insertSubview:self.pairView atIndex:0];
     NSDictionary *views = NSDictionaryOfVariableBindings(_pairView);
     [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|[_pairView]|"
                                                                      options:0
                                                                      metrics:0
                                                                        views:views]];
     [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|[_pairView]|"
                                                                      options:0
                                                                      metrics:0
                                                                        views:views]];
     
     // Assign delegates.
     self.pairView.renderDelegate = self;
     self.pairView.modelDelegate = self;
     self.pairView.sensorFusionDelegate = self;
     self.pairView.recordingDelegate = self;
    */

    /*
     // Option: Create PairView programmatically using a CGRect frame.
     self.pairView = [[PairView alloc] initWithFrame:UIScreen.mainScreen.bounds];
     [self.pairView setAutoresizingMask:UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth];
     [self.view insertSubview:self.pairView atIndex:0];
     
     // Assign delegates.
     self.pairView.renderDelegate = self;
     self.pairView.modelDelegate = self;
     self.pairView.sensorFusionDelegate = self;
     self.pairView.recordingDelegate = self;
    */

    // The PairView will not start until "resume" is called.
    [self.pairView resume];
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id <UIViewControllerTransitionCoordinator>)coordinator
{
    [coordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext> _Nonnull context) {
         [self.pairView viewWillTransitionToSize:size];
    } completion:nil];
}

- (IBAction)onImageButtonTouch:(id)sender
{
    UIImageWriteToSavedPhotosAlbum([self.pairView screenshot], self, @selector(image:didFinishSavingWithError:contextInfo:), nil);
}

- (void)image:(UIImage *)image didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo
{
    NSLog(@"Image saved");
}

+ (nonnull NSURL *)saveLocation
{
    NSURL *documentsDirectory = [NSFileManager.defaultManager URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask].lastObject;
    return [documentsDirectory URLByAppendingPathComponent:@"PairTemp" isDirectory:YES];
}

- (IBAction)onAddButtonTouch:(id)sender
{
    // The path to which the asset's mesh and texture data can be saved.
    NSURL *saveLocation = ViewController.saveLocation;

    PairAsset *pairAsset;
    NSURL *modelURL = [PairAssetLoader findModelFileInDirectory:saveLocation];
    if (modelURL) {
        // The model data is on the device. Load directly from file.
        pairAsset = [[PairAsset alloc] initWithURL:modelURL];
    } else {
        // The model data is not on the device and so needs to be downloaded.

        //
        // Example model with swatches:
        //

        // Download loactaion of the mesh and texture files needed to render the asset.
        NSURL *downloadURL = [NSURL URLWithString:@"https://paircatalog.blob.core.windows.net/pair-public-catalog/catalog-models/a47b580c-d5ca-4b43-a559-d29f1e7f9798/model_v4.tar.gz"]; // example model with swatches

        // Create a bounding box that serves as a placeholder while the asset is loaded.
        // It's best to have the asset's bounding box prior to loading.
        MDLAxisAlignedBoundingBox boundingBox;
        boundingBox.minBounds = (vector_float3){-0.507238686, 0, -0.539075017};
        boundingBox.maxBounds = (vector_float3){0.507238686, 0.876996994, 0.539074898};

        /*
         //
         // Example model with no swatches:
         //

         // Download loactaion of the mesh and texture files needed to render the asset.
         NSURL *downloadURL = [NSURL URLWithString:@"https://paircatalog.blob.core.windows.net/pair-public-catalog/catalog-models/f1e62aa7-4b95-40db-a5c2-395b808acca6/model_v4.tar.gz"];

         // Create a bounding box that serves as a placeholder while the asset is loaded.
         // It's best to have the asset's bounding box prior to loading.
         MDLAxisAlignedBoundingBox boundingBox;
         boundingBox.minBounds = (vector_float3){-0.170000017, 0, -0.325071335};
         boundingBox.maxBounds = (vector_float3){0.170000017, 0.89465636, 0.325071335};
        */

        // PairAssetLoader is an example implementation of how to use the PairAssetLoaderProtocol
        // for downloading and loading of remote models
        PairAssetLoader *pairAssetLoader = [[PairAssetLoader alloc] initWithRemoteDownloadURL:downloadURL
                                                                                 saveLocation:saveLocation
                                                                    andPlaceholderBoundingBox:boundingBox];

        // Create a new PairAsset using a PairAssetLoader (an implementation of the PairAssetLoaderProtocol).
        pairAsset = [[PairAsset alloc] initWithPairAssetLoader:pairAssetLoader];
    }

    // Add PairAsset to the PairView.
    [self.pairView addPairAsset:pairAsset atPoint:self.view.center];

    // Select the newly added PairAsset.
    self.pairView.selectedPairAsset = pairAsset;
}

- (IBAction)onVideoButtonTouch:(id)sender
{
    if (self.pairView.isRecordingVideo) {
        [self.pairView stopVideoRecording];
        [self.videoButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
        [self.videoButton setTitle:@"Record Video" forState:UIControlStateNormal];
    } else {
        [self.pairView startVideoRecording];
        [self.videoButton setTitleColor:UIColor.redColor forState:UIControlStateNormal];
        [self.videoButton setTitle:@"Stop Video" forState:UIControlStateNormal];
    }
}

- (IBAction)onSwapSwatchTouch:(id)sender
{
    for (PairAsset *pairAsset in self.pairView.pairAssets) {
        NSUInteger activeSwatchIndex = pairAsset.activeSwatchIndex + 1;
        if (activeSwatchIndex > pairAsset.numberOfSwatches - 1) {
            pairAsset.activeSwatchIndex = 0;
        } else {
            pairAsset.activeSwatchIndex = activeSwatchIndex;
        }
    }
}

#pragma mark - PairViewModelDelegate

- (void)onDidLoadPairAsset:(nonnull PairAsset *)pairAsset
{
    if (pairAsset.numberOfSwatches > 1) {
        self.swatchButton.hidden = NO;
    }

    self.imageButton.hidden = NO;
    self.videoButton.hidden = NO;
}

- (void)onDidUnloadPairAsset:(nonnull PairAsset *)pairAsset
{
    __block BOOL anAssetHasSwatches = NO;
    [self.pairView.pairAssets enumerateObjectsUsingBlock:^(PairAsset * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if (obj.numberOfSwatches > 1) {
            anAssetHasSwatches = YES;
            *stop = YES;
        }
    }];
    self.swatchButton.hidden = !anAssetHasSwatches;

    if (self.pairView.pairAssets.count == 0) {
        self.imageButton.hidden = YES;
        self.videoButton.hidden = YES;
    }
}

- (void)onWillSelecteModel:(nonnull PairAsset *)pairAsset
{
    // Do something when asset is selected.
}

- (void)onWillDeselecteModel:(nonnull PairAsset *)pairAsset
{
    // Do something when asset is deselected.
}

#pragma mark - PairViewRecordingDelegate

- (void)onVideoRecordingSaved:(NSURL *)filePathURL
{
    if (UIVideoAtPathIsCompatibleWithSavedPhotosAlbum( filePathURL.path)) {
        UISaveVideoAtPathToSavedPhotosAlbum(filePathURL.path, self, @selector(video:didFinishSavingWithError:contextInfo:), nil);
    }
}

- (void)video:(NSString *)videoPath didFinishSavingWithError:(NSError *)error contextInfo:(void *)contextInfo
{
    NSLog(@"Video saved");
}

#pragma mark - PairViewSensorFusionDelegate

- (void)onSensorFusionDidChangeStatus:(nonnull PairSensorFusionStatus *)status
{
    BOOL hideButtons = status.isInitializing;
    self.addButton.hidden = hideButtons;
}

@end
