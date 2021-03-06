//
//  Copyright (c) 2016 Google Inc.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#import <Foundation/Foundation.h>

@import Firebase;
@import FirebaseAuth;

@interface FIRAuthMigrator : NSObject

/**
 * Creates a new FIRAuthMigrator for the default FIRApp.
 */
+ (instancetype _Nonnull)authMigrator NS_SWIFT_NAME(authMigrator());

/**
 * Creates a new FIRAuthMigrator for the given FIRApp.
 */
+ (instancetype _Nonnull)authMigratorWithApp:(FIRApp * _Nonnull)app;

/**
 * Looks up whether a user is logged in with a legacy Firebase SDK and logs them in with the current
 * Firebase SDK. This works as follows:
 * 1. Looks up the legacy auth token in the keychain.
 * 2. Sends the legacy token to a Firebase server to exchange it for a new auth token.
 * 3. Uses the new auth token to log in the user.
 * 4. Removes the legacy auth token from the keychain.
 *
 * If a user is already logged in with the new Firebase SDK, then the legacy auth token will be
 * removed, but the logged in user will not be affected.
 *
 * If the Firebase server determines that the legacy auth token is invalid, it will be removed, and
 * the user will not be logged in.
 *
 * @param completion Callback for when the exchange is complete. user can be nil if either:
 * 1. There was a (temporary or permanent) failure, as indicated by error, OR
 * 2. There was no legacy auth token present.
 */
- (void)migrate:(void (^ _Nullable)(FIRUser * _Nullable user,
                                    NSError * _Nullable error))completion;

/**
 * Removes the legacy Firebase auth token from the keychain, if present.
 */
- (void)clearLegacyAuth;

/**
 * Returns whether a user is logged in on this device with a legacy Firebase SDK.
 */
- (BOOL)hasLegacyAuth:(NSError * _Nullable * _Nullable)error;

@end
