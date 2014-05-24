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


#import "CocoDeviceWrapper.h"

@implementation CocoDeviceWrapper

//////////////////////////////////////////////////////////////////////////////////////////////
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	// Initialize gesture control variables
    last_scale = 1.0;
    last_rotation = 0.0;
    scale = 1.0;
    rotation = 0.0;

    // Create a Window
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];

    // Create an OpenGL View
    self.glwrap = [[[CocoOpenGLContextWrapper alloc] initWithFrame:[[UIScreen mainScreen] bounds] contentsScale:self.window.screen.scale] autorelease];

    // Set window root view controller
    self.window.backgroundColor = [UIColor whiteColor];
    self.window.rootViewController = self;

    // Add OpenGL View to Window and make it visible
    [self.window addSubview:self.glwrap];
    [self.window makeKeyAndVisible];

	// Initialize OpenGL Context
    [self.glwrap InitGL];

    // Simulate HTML5 Window and Document
	window = new HTMLWindow();
	window->setScreen([self.glwrap GetScreen]);
	document = new HTMLDocument();

	NSLog(@"Orientation: %@", UIInterfaceOrientationIsLandscape(self.window.rootViewController.interfaceOrientation) ? @"Landscape" : @"Portrait");

	// Simulate HTML5 OpenGL Canvas and set its size
	HTMLCanvasElement* canvas = document->createElement("canvas");
	gl = (WebGLRenderingContext*)canvas->getContext("webgl");
	gl->canvas->width = window->innerWidth;
	gl->canvas->height = window->innerHeight;

	// Create the GameEngine
	engine = new GameEngine();

	// Start the game loop
	self->cadlink = [[CADisplayLink displayLinkWithTarget:self selector:@selector(tick)] retain];
	[self->cadlink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];

    return YES;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Request Animation Frame (tick and paint)
//////////////////////////////////////////////////////////////////////////////////////////////
- (void)tick
{
    [self.glwrap SetBuffers];

    #ifdef __XMLHTTPREQUEST_HPP__
    XMLHttpRequest::tick();
    #endif

	engine->run(16.0);			// <-- pseudo/fixed clock of 16 ms since last animation
    [self.glwrap SwapBuffers];
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)dealloc
{
    [self.keywrap release];
    [self.glwrap release];
    [self.window release];
    [super dealloc];
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)applicationWillResignActive:(UIApplication *)application
{
    window->handleEvent(0, fxEvent::BLUR);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)applicationDidBecomeActive:(UIApplication *)application
{
    window->handleEvent(0, fxEvent::FOCUS);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)applicationWillTerminate:(UIApplication *)application
{
    window->handleEvent(0, fxEvent::UNLOAD);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)touchesBegan:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    window->handleEvent(0, fxEvent::TOUCHSTART, (void*)event);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)touchesMoved:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    window->handleEvent(0, fxEvent::TOUCHMOVE, (void*)event);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)touchesEnded:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    window->handleEvent(0, fxEvent::TOUCHEND, (void*)event);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)touchesCancelled:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    window->handleEvent(0, fxEvent::TOUCHCANCEL, (void*)event);
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)handlePinch:(UIPinchGestureRecognizer *)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateBegan)
        last_scale = 1.0;

    scale = [recognizer scale] / last_scale;
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)handleRotation:(UIRotationGestureRecognizer *)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateBegan)
        last_rotation = 0.0;

    rotation = [recognizer rotation] - last_rotation;
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)showKeyboard
{
    [self.keywrap becomeFirstResponder];
}

//////////////////////////////////////////////////////////////////////////////////////////////
- (void)hideKeyboard
{
    [self.keywrap resignFirstResponder];
}

@end
