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
		screen.top = 0;
		screen.width = rect.size.width;
		screen.height = rect.size.height;
        screen.pixelRatio = scale;
		screen.isPortrait = FALSE;
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
	glViewport(0, 0, screen.width*screen.pixelRatio, screen.height*screen.pixelRatio);
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