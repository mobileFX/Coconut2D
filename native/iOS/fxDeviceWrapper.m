//
//  AppDelegate.m
//  fxCore
//
//  Created by Administrator on 4/2/13.
//  Copyright (c) 2013 mobileFX. All rights reserved.
//

#import "fxDeviceWrapper.h"

extern char* fxFile::filesPath;
extern char* fxFile::assetPath;
extern fxArgs* fxArgs::Args;

@implementation fxGLWrap

+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)rect contentsScale:(CGFloat)scale
{
    if((self = [super initWithFrame:rect]))
    {
        UIInterfaceOrientation ori = [[UIApplication sharedApplication] statusBarOrientation];
        switch(ori)
        {
            case UIInterfaceOrientationPortrait: screen.rotation = fxScreen::Rotation::NONE; break;
            case UIInterfaceOrientationPortraitUpsideDown: screen.rotation = fxScreen::Rotation::FULL; break;
            case UIInterfaceOrientationLandscapeLeft: screen.rotation = fxScreen::Rotation::RCW; break;
            case UIInterfaceOrientationLandscapeRight: screen.rotation = fxScreen::Rotation::RCCW; break;
        }
        if(screen.rotation == fxScreen::Rotation::NONE || screen.rotation == fxScreen::Rotation::FULL)
        {
            screen.top = [UIApplication sharedApplication].statusBarFrame.size.height;
            screen.isPortrait = true;
            screen.width = rect.size.width;
            screen.height = rect.size.height - screen.top;
        }
        else
        {
            screen.top = [UIApplication sharedApplication].statusBarFrame.size.width;
            screen.isPortrait = false;
            screen.width = rect.size.height;
            screen.height = rect.size.width - screen.top;
        }
        screen.pixelRatio = scale;
        screen.width *= screen.pixelRatio;
        screen.height *= screen.pixelRatio;
        
        ((CAEAGLLayer*)self.layer).opaque = YES;
        ((CAEAGLLayer*)self.layer).contentsScale = scale;
        ((CAEAGLLayer*)self.layer).drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys: [NSNumber numberWithBool:NO],
                                                         kEAGLDrawablePropertyRetainedBacking,
                                                         kEAGLColorFormatRGBA8,
                                                         kEAGLDrawablePropertyColorFormat,
                                                         nil];
    }
    return self;
}

- (void)initGLRenderStorage
{
    [[EAGLContext currentContext] renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
}

- (void)InitGL
{
    context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
    [EAGLContext setCurrentContext:context];
    switch(screen.rotation)
    {
        case fxScreen::Rotation::NONE: glViewport(0, 0, screen.width, screen.height); break;
        case fxScreen::Rotation::FULL: glViewport(0, screen.top, screen.width, screen.height + screen.top); break;
        case fxScreen::Rotation::RCW: glViewport(screen.top, 0, screen.height + screen.top, screen.width); break;
        case fxScreen::Rotation::RCCW: glViewport(0, 0, screen.height, screen.width); break;
    }
    
    glGenFramebuffers(1, &fbuff);
    glGenRenderbuffers(1, &rbuff);
    glBindFramebuffer(GL_FRAMEBUFFER, fbuff);
    glBindRenderbuffer(GL_RENDERBUFFER, rbuff);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbuff);
    [self initGLRenderStorage];
}

- (void)QuitGL
{
    [EAGLContext setCurrentContext:context];
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteRenderbuffers(1, &rbuff);
    glDeleteFramebuffers(1, &fbuff);
    [EAGLContext setCurrentContext:nil];
    [context release];
}

- (void)SetContext
{
    [EAGLContext setCurrentContext:context];
}

- (void)ClearContext
{
	[EAGLContext setCurrentContext:nil];
}

- (void)SetBuffers
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbuff);
}

- (void)SwapBuffers
{
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

- (fxScreen)GetScreen
{
    return screen;
}
@end

@implementation fxKeyWrap

- (BOOL)canBecomeFirstResponder { return YES; }

- (BOOL)hasText { return YES; }
- (void)insertText:(NSString *)theText
{
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYDOWN, (void*)[theText cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYPRESS, (void*)[theText cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYUP, (void*)[theText cStringUsingEncoding:NSUTF32LittleEndianStringEncoding]);
}
- (void)deleteBackward
{
    static uint32_t _v = 8;
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYDOWN, (void*)(&_v));
    fxCRL::handleEvent(0, fxCRL::fxEvent::KEYUP, (void*)(&_v));
}

- (UITextAutocapitalizationType)autocapitalizationType { return UITextAutocapitalizationTypeNone; }
- (UITextAutocorrectionType)autocorrectionType { return UITextAutocorrectionTypeNo; }
- (UITextSpellCheckingType)spellCheckingType { return UITextSpellCheckingTypeNo; }
- (BOOL)enablesReturnKeyAutomatically { return NO; }
- (UIKeyboardAppearance)keyboardAppearance { return UIKeyboardAppearanceDefault; }
- (UIKeyboardType)keyboardType { return UIKeyboardTypeDefault; }
- (UIReturnKeyType)returnKeyType { return UIReturnKeyDefault; }

@end



@implementation fxDeviceWrapper

- (void)tick
{
    static std::chrono::steady_clock::time_point now, last_tick = std::chrono::steady_clock::now(), last_draw = std::chrono::steady_clock::now();
    static std::chrono::duration<double, std::milli> tick_dif = std::chrono::duration<double, std::milli>::zero();
    static std::chrono::duration<double, std::milli> draw_dif = std::chrono::duration<double, std::milli>::zero();
    
    
    // Mark time and calc difference since last call
    now = std::chrono::steady_clock::now();
    draw_dif = now - last_draw;
    tick_dif = now - last_tick;
    
    // If the time ellapsed is grater than 16ms we flush OpenGL trying to achieve 60 fps.
    if((draw_dif + tick_dif).count() > 16.0)
    {
        last_draw = now;
        [self.glwrap SetBuffers];
        fxCRL::paint();
        [self.glwrap SwapBuffers];
        
        now = std::chrono::steady_clock::now();
    }
    
    // Tick the HTML5 timers
    last_tick = now;
    fxCRL::tick();
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(4 * NSEC_PER_MSEC)), dispatch_get_main_queue(), ^(void){ [self tick]; });
}

- (void)VideoPlay:(const char*)path
{
    LOGI("Playing video!\n");
    //NSString str = [[NSString alloc] initWithUTF8String:path];
    self.player = [[[MPMoviePlayerController alloc] initWithContentURL:[NSURL URLWithString:[[NSString alloc] initWithUTF8String:path]]] autorelease];
    self.player.controlStyle = MPMovieControlStyleNone;
    //[self.player prepareToPlay];
    [self.player.view setFrame:self.view.bounds];
    //self.player.view.transform = CGAffineTransformConcat(self.player.view.transform, CGAffineTransformMakeRotation(M_PI_2));
    UIWindow *backgroundWindow = [[UIApplication sharedApplication] keyWindow];
    [self.player.view setFrame:backgroundWindow.frame];
    [backgroundWindow addSubview:self.player.view];
    //[self.window addSubview:self.player.view];
    //self.player.fullscreen = YES;
    [self.player.view becomeFirstResponder];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(VideoFinished:) name:MPMoviePlayerPlaybackDidFinishNotification object:self.player];
    [self.player play];

}

- (void)VideoFinished:(NSNotification*)notification
{
    [self.player.view removeFromSuperview];
}

- (void)dealloc
{
    //[self.player release];
    [self.keywrap release];
    [self.glwrap release];
    [self.window release];
    [super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    UIDevice* dev = [UIDevice currentDevice];
    NSLog(@"%@\n", dev.name);
    NSLog(@"%@\n", dev.systemName);
    NSLog(@"%@\n", dev.systemVersion);
    NSLog(@"%@\n", dev.model);
    NSLog(@"%@\n", dev.localizedModel);
    NSLog(@"%d\n", dev.userInterfaceIdiom);
    NSLog(@"%@\n", dev.identifierForVendor);
    
    self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    self.glwrap = [[[fxGLWrap alloc] initWithFrame:[[UIScreen mainScreen] bounds] contentsScale:self.window.screen.scale] autorelease];
    self.keywrap = [[[fxKeyWrap alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    //self.player = [[[MPMoviePlayerController alloc] init] autorelease];
    //self.player.view.hidden = true;
    
    // Override point for customization after application launch.
    self.window.backgroundColor = [UIColor whiteColor];
    self.window.rootViewController = self;
    [self.window addSubview:self.glwrap];
    [self.window addSubview:self.keywrap];
    //[self.window addSubview:self.player.view];
    self.view.multipleTouchEnabled = YES;
    self.view.exclusiveTouch = YES;
    [self.window makeKeyAndVisible];
    
    last_scale = 1.0;
    last_rotation = 0.0;
    scale = 1.0;
    rotation = 0.0;
    
    UIRotationGestureRecognizer *rotationRecognizer = [[[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(handleRotation:)] autorelease];
    rotationRecognizer.cancelsTouchesInView = NO;
    rotationRecognizer.delaysTouchesBegan = NO;
    rotationRecognizer.delaysTouchesEnded = NO;
    [rotationRecognizer setDelegate:self];
    
    UIPinchGestureRecognizer *pinchRecognizer = [[[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinch:)] autorelease];
    pinchRecognizer.cancelsTouchesInView = NO;
    pinchRecognizer.delaysTouchesBegan = NO;
    pinchRecognizer.delaysTouchesEnded = NO;
    [pinchRecognizer setDelegate:self];
    
    [self.view addGestureRecognizer:rotationRecognizer];
    [self.view addGestureRecognizer:pinchRecognizer];
    
    [self.glwrap InitGL];
    
    fxCRL::init(fxArgs::Args->getArgc(), fxArgs::Args->getArgv(), [self.glwrap GetScreen], self);
    fxCRL::handleEvent(0, fxCRL::fxEvent::LOAD);
    [self tick];
    return YES;
}

- (void)showKeyboard
{
    [self.keywrap becomeFirstResponder];
}

- (void)hideKeyboard
{
    [self.keywrap resignFirstResponder];
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    fxCRL::handleEvent(0, fxCRL::fxEvent::BLUR);
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    fxCRL::handleEvent(0, fxCRL::fxEvent::FOCUS);
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    fxCRL::handleEvent(0, fxCRL::fxEvent::UNLOAD);
    fxCRL::quit();
}

- (void)touchesBegan:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    ///[self VideoPlay:"file:///var/mobile/Applications/26DA39E3-D7A3-4B7B-9DA0-1C523A3AA745/fxCore.app/web/assets/videosample.mp4"];
    //[self.keywrap becomeFirstResponder];
    //std::cout<<"Began: "<<[i_touches count]<<"/"<<[[event allTouches] count]<<"\n";
    fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHSTART, (void*)event);
}

- (void)touchesMoved:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    //std::cout<<"Moved: "<<[i_touches count]<<"/"<<[[event allTouches] count]<<"\n";
    fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHMOVE, (void*)event);
}

- (void)touchesEnded:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    //std::cout<<"Ended: "<<[i_touches count]<<"/"<<[[event allTouches] count]<<"\n";
    fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHEND, (void*)event);
}

- (void)touchesCancelled:(NSSet *)i_touches withEvent:(UIEvent *)event
{
    //std::cout<<"Cancelled: "<<[i_touches count]<<"/"<<[[event allTouches] count]<<"\n";
    fxCRL::handleEvent(0, fxCRL::fxEvent::TOUCHCANCEL, (void*)event);
}

- (void)handlePinch:(UIPinchGestureRecognizer *)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateBegan)
        last_scale = 1.0;
    
    scale = [recognizer scale] / last_scale;
}

- (void)handleRotation:(UIRotationGestureRecognizer *)recognizer
{
    if(recognizer.state == UIGestureRecognizerStateBegan)
        last_rotation = 0.0;
    
    rotation = [recognizer rotation] - last_rotation;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
{
    return YES;
}


@end
