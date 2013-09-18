#ifndef _fxDeviceWrapper_h
#define _fxDeviceWrapper_h

@class fxDeviceWrapper;
@class fxGLWrap;
@class fxKeyWrap;

#import <MediaPlayer/MediaPlayer.h>
#import <QuartzCore/QuartzCore.h>
#import "fxCRL.h"
#import "fxArgs.h"
#import "fxGLWrap.h"
#import "fxKeyWrap.h"

@interface fxDeviceWrapper : UIViewController <UIApplicationDelegate, UIGestureRecognizerDelegate>
{
    float scale;
    float last_scale;
    float rotation;
    float last_rotation;
}
@property (strong, nonatomic) UIWindow* window;
@property (strong, nonatomic) fxGLWrap* glwrap;
@property (strong, nonatomic) fxKeyWrap* keywrap;
@property (strong, nonatomic) MPMoviePlayerController* player;

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