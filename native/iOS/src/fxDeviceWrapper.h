#ifndef _fxDeviceWrapper_h
#define _fxDeviceWrapper_h

@class fxDeviceWrapper;
@class fxGLWrap;
@class fxKeyWrap;

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import <AVFoundation/AVAudioPlayer.h>
#import <AVFoundation/AVPlayer.h>
#import <MediaPlayer/MPMoviePlayerController.h>
#import <MediaPlayer/MediaPlayer.h>

#import <QuartzCore/QuartzCore.h>

#import "fxCRL.h"
#import "fxArgs.h"
#import "fxGLWrap.h"
#import "fxKeyWrap.h"

@interface fxDeviceWrapper : NSObject <UIApplicationDelegate,
                                       UIGestureRecognizerDelegate>
{
	UIWindow *splashScreen;
	UIWindow *window;

	float scale;
    float last_scale;
    float rotation;
    float last_rotation;
}

@property (nonatomic, retain) IBOutlet UIWindow *splashScreen;
@property (nonatomic, retain) IBOutlet UIWindow *window;

//@property (strong, nonatomic) UIWindow* window;
@property (strong, nonatomic) fxGLWrap* glwrap;
@property (strong, nonatomic) fxKeyWrap* keywrap;
@property (strong, nonatomic) MPMoviePlayerController* player;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
- (void)tick;
- (void)showKeyboard;
- (void)hideKeyboard;
- (void)VideoPlay:(const char*)path;
- (void)VideoFinished:(NSNotification*)notification;
- (void)handlePinch:(UIPinchGestureRecognizer *)recognizer;
- (void)handleRotation:(UIRotationGestureRecognizer *)recognizer;
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;
@end

#endif