/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef _fxDeviceWrapper_h
#define _fxDeviceWrapper_h

@class CocoDeviceWrapper;
@class CocoDeviceOpenGLContext;
@class CocoDeviceKeyboard;

#import <MediaPlayer/MediaPlayer.h>
#import <QuartzCore/QuartzCore.h>
#import "Coconut2D.hpp"
#import "HTMLWindow.hpp"
#import "HTMLDocument.hpp"
#import "CocoDeviceOpenGLContext.h"
#import "CocoDeviceKeyboard.h"
#import "Coconut2D.hpp"
#import "WebGLRenderingContext.hpp"
#import "GameEngine.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
@interface CocoDeviceWrapper : UIViewController <UIApplicationDelegate, UIGestureRecognizerDelegate>
{
    float scale;
    float last_scale;
    float rotation;
    float last_rotation;
	CADisplayLink* cadlink;
}

@property (strong, nonatomic) UIWindow* window;
@property (strong, nonatomic) CocoDeviceOpenGLContext* glwrap;
@property (strong, nonatomic) CocoDeviceKeyboard* keywrap;
@property (strong, nonatomic) MPMoviePlayerController* player;

- (void)tick;
- (void)showKeyboard;
- (void)hideKeyboard;
- (void)handlePinch:(UIPinchGestureRecognizer *)recognizer;
- (void)handleRotation:(UIRotationGestureRecognizer *)recognizer;
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer;

@end

#endif
