//
//  Pair.h
//  PairSDK
//
//  Copyright © 2016 Pair, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 * @brief Information about the PairSDK.
 */

@interface Pair : NSObject
/*!
 @brief Sets the PairSDK license key. This method should be called before using any other PairSDK functionality.
 @param licenseKey A license key obtain from Pair.
 */
+ (void)setLicenseKey:(nonnull NSString *)licenseKey;

/*!
 * @brief Retrieve the current iOS PairSDK version.
 * @return The current PairSDK version as a string.
 */
+ (nonnull NSString *)sdkVersion;
@end
