#import "fxDeviceWrapper.h"

@implementation fxDeviceWrapper

@synthesize splashScreen;
@synthesize window;

static inline double radians (double degrees) {return degrees * M_PI/180;}
static BOOL landscape = FALSE;
static BOOL statusBarHidden = TRUE;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	CGAffineTransform rotate = CGAffineTransformMakeRotation(1.57079633);
	
	[[UIApplication sharedApplication] setStatusBarHidden:true];
	application.statusBarOrientation = UIInterfaceOrientationLandscapeRight;
	
	CGRect fullScreen = [[UIScreen mainScreen] bounds];
	CGRect appScreen = [[UIScreen mainScreen] applicationFrame];
	fullScreen = CGRectMake(0, 0, fullScreen.size.height , fullScreen.size.width);
	appScreen = CGRectMake(0, 0, appScreen.size.height , appScreen.size.width);
	
	self.window = [[[UIWindow alloc] initWithFrame:fullScreen] autorelease];
	[self.window setCenter:CGPointMake(fullScreen.size.height/2.0f, fullScreen.size.width/2.0f)];
	[self.window setTransform:rotate];
    self.window.backgroundColor = [UIColor whiteColor];
	
    self.glwrap = [[[fxGLWrap alloc] initWithFrame:fullScreen contentsScale:self.window.screen.scale] autorelease];
    //self.keywrap = [[[fxKeyWrap alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    //self.player = [[[MPMoviePlayerController alloc] init] autorelease];
    //self.player.view.hidden = true;
    
    // Override point for customization after application launch.
    [self.window addSubview:self.glwrap];
    //[self.window addSubview:self.keywrap];
    //[self.window addSubview:self.player.view];
    //self.view.multipleTouchEnabled = YES;
    //self.view.exclusiveTouch = YES;
    [self.window makeKeyAndVisible];
    
    last_scale = 1.0;
    last_rotation = 0.0;
    scale = 1.0;
    rotation = 0.0;
    
	/*
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
    */
	
    [self.glwrap InitGL];
    
    fxCRL::init(fxArgs::Args->getArgc(), fxArgs::Args->getArgv(), [self.glwrap GetScreen], self);
    fxCRL::handleEvent(0, fxCRL::fxEvent::LOAD);
    [self tick];
	
    return YES;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)VideoPlay:(const char*)path
{
    LOGI("Playing video!\n");
    //NSString str = [[NSString alloc] initWithUTF8String:path];
    self.player = [[[MPMoviePlayerController alloc] initWithContentURL:[NSURL URLWithString:[[NSString alloc] initWithUTF8String:path]]] autorelease];
    self.player.controlStyle = MPMovieControlStyleNone;
    //[self.player prepareToPlay];
    //[self.player.view setFrame:self.view.bounds];
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)VideoFinished:(NSNotification*)notification
{
    [self.player.view removeFromSuperview];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)dealloc
{
    //[self.player release];
    [self.keywrap release];
    [self.glwrap release];
    [self.window release];
    [super dealloc];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)showKeyboard
{
    [self.keywrap becomeFirstResponder];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

- (void)tick
{
	static std::chrono::steady_clock::time_point now;
	static std::chrono::steady_clock::time_point last_tick;
	static std::chrono::steady_clock::time_point last_draw;
	static std::chrono::steady_clock::time_point t0;
	static std::chrono::steady_clock::time_point t1;
	static std::chrono::duration<double, std::milli> tick_diff;
	static std::chrono::duration<double, std::milli> draw_diff;
	static std::chrono::duration<double, std::milli> diff;
	static float fps = 60;
	static float duration = 1000.0 / fps;
	
    // Mark time and calc difference since last call
    now = std::chrono::steady_clock::now();
    draw_diff = now - last_draw;
    tick_diff = now - last_tick;
	float dd1 = draw_diff.count();
	float dd2;
	
    if(dd1 > duration)
    {
		[self.glwrap SetBuffers];
		t0 = std::chrono::steady_clock::now();
        fxCRL::paint();
		diff = std::chrono::steady_clock::now() - t0;
		dd1 = diff.count();
        t1 = std::chrono::steady_clock::now();
		[self.glwrap SwapBuffers];
		diff = std::chrono::steady_clock::now() - t1;
		dd2 = diff.count();
		//NSLog(@"paint: %f - flush: %f", dd1, dd2);
		now = std::chrono::steady_clock::now();
		last_draw = now;
    }
    
	fxCRL::tick();
	
	last_tick = std::chrono::steady_clock::now();
	dispatch_async(dispatch_get_main_queue(), ^(void){ [self tick]; });
    
    //dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(8 * NSEC_PER_MSEC)), dispatch_get_main_queue(), ^(void){ [self tick]; });
	//dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0), dispatch_get_main_queue(), ^(void){ [self tick]; });
	
}

@end
