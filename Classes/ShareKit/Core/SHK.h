//
//  SHK.h
//  ShareKit
//
//  Created by Nathan Weiner on 6/10/10.

//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//

#define SHK_VERSION @"0.2.1"

#import <Foundation/Foundation.h>
#import "DefaultSHKConfigurator.h"
#import "SHKItem.h"
#import "SHKActionSheet.h"
#import "SHKRequest.h"
#import "SHKActivityIndicator.h"
#import "SHKFormFieldSettings.h"
#import "UIWebView+SHK.h"

extern NSString * const SHKSendDidStartNotification;
extern NSString * const SHKSendDidFinishNotification;
extern NSString * const SHKSendDidFailWithErrorNotification;
extern NSString * const SHKSendDidCancelNotification;
extern NSString * const SHKAuthDidFinishNotification;

@class SHKActionSheet;

@interface SHK : NSObject 

@property (nonatomic, retain) UIViewController *currentView;
@property (nonatomic, retain) UIViewController *pendingView;
@property BOOL isDismissingView;

@property (nonatomic, retain) NSOperationQueue *offlineQueue;

#pragma mark -

+ (SHK *)currentHelper;

+ (NSDictionary *)sharersDictionary;

#pragma mark -
#pragma mark View Management

+ (void)setRootViewController:(UIViewController *)vc;

/* original show method, wraps the view to UINavigationViewController prior presenting, if not already a UINavigationViewController */
- (void)showViewController:(UIViewController *)vc;
/* displays sharers with custom UI - without wrapping */
- (void)showStandaloneViewController:(UIViewController *)vc;
/* returns current top view controller to display UI from */
- (UIViewController *)rootViewForUIDisplay;

- (void)hideCurrentViewControllerAnimated:(BOOL)animated;
- (void)viewWasDismissed;

+ (UIBarStyle)barStyle;
+ (UIModalPresentationStyle)modalPresentationStyleForController:(UIViewController *)controller;
+ (UIModalTransitionStyle)modalTransitionStyleForController:(UIViewController *)controller;

#pragma mark -
#pragma mark Favorites

+ (NSArray *)favoriteSharersForItem:(SHKItem *)item;
+ (void)pushOnFavorites:(NSString *)className forItem:(SHKItem *)item;
+ (void)setFavorites:(NSArray *)favs forItem:(SHKItem *)item;

#pragma mark -
#pragma mark Credentials

+ (NSString *)getAuthValueForKey:(NSString *)key forSharer:(NSString *)sharerId;
+ (void)setAuthValue:(NSString *)value forKey:(NSString *)key forSharer:(NSString *)sharerId;
+ (void)removeAuthValueForKey:(NSString *)key forSharer:(NSString *)sharerId;

+ (void)logoutOfAll;
+ (void)logoutOfService:(NSString *)sharerId;

#pragma mark -
#pragma mark Offline Support

+ (NSString *)offlineQueuePath;
+ (NSString *)offlineQueueListPath;
+ (NSMutableArray *)getOfflineQueueList;
+ (void)saveOfflineQueueList:(NSMutableArray *)queueList;
+ (BOOL)addToOfflineQueue:(SHKItem *)item forSharer:(NSString *)sharerId;
+ (void)flushOfflineQueue;

#pragma mark -

+ (NSError *)error:(NSString *)description, ...;

#pragma mark -
#pragma mark Network

+ (BOOL)connected;

@end

NSString * SHKStringOrBlank(NSString * value);
NSString * SHKEncode(NSString * value);
NSString * SHKEncodeURL(NSURL * value);
NSString * SHKFlattenHTML(NSString * value, BOOL preserveLineBreaks);
NSString * SHKLocalizedString(NSString* key, ...);