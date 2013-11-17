#import "fxGLWrap.h"

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
        //if(screen.rotation == fxScreen::Rotation::NONE || screen.rotation == fxScreen::Rotation::FULL)
        {
            screen.top = [UIApplication sharedApplication].statusBarFrame.size.height;
            screen.isPortrait = true;
            screen.width = rect.size.width;
            screen.height = rect.size.height - screen.top;
        }
        /*else
        {
            screen.top = [UIApplication sharedApplication].statusBarFrame.size.width;
            screen.isPortrait = false;
            screen.width = rect.size.height;
            screen.height = rect.size.width - screen.top;
        }*/
        screen.pixelRatio = scale;
        //screen.width *= screen.pixelRatio;
        //screen.height *= screen.pixelRatio;
        
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
	glViewport(0, 0, screen.width * screen.pixelRatio, screen.height * screen.pixelRatio);
    /*switch(screen.rotation)
    {
        case fxScreen::Rotation::NONE: glViewport(0, 0, screen.width, screen.height); break;
        case fxScreen::Rotation::FULL: glViewport(0, screen.top, screen.width, screen.height + screen.top); break;
        case fxScreen::Rotation::RCW: glViewport(screen.top, 0, screen.height + screen.top, screen.width); break;
        case fxScreen::Rotation::RCCW: glViewport(0, 0, screen.height, screen.width); break;
    }*/
    
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