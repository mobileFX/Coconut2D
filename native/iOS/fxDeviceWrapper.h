//
//  AppDelegate.h
//  fxCore
//
//  Created by Administrator on 4/2/13.
//  Copyright (c) 2013 mobileFX. All rights reserved.
//

@class fxDeviceWrapper;

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import <OpenGLES/ES2/gl.h>
#import <QuartzCore/QuartzCore.h>
#import "fxCRL.h"
#import "fxGLWrap.h"
#import "fxAsset.h"
#import "fxAudio.h"

@interface fxKeyWrap : UIView <UIKeyInput>
{
}

@end

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
