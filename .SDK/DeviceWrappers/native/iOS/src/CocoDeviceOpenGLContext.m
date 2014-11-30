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


#import "CocoDeviceOpenGLContext.h"

@implementation CocoDeviceOpenGLContext

////////////////////////////////////////////////////////////////////////////////////////////////////
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
- (id)initWithFrame:(CGRect)rect contentsScale:(CGFloat)scale
{
    float iOSVersion = [[[UIDevice currentDevice] systemVersion] floatValue];

    if(iOSVersion<8)
    {
        UIInterfaceOrientation ori = [[UIApplication sharedApplication] statusBarOrientation];

        // Get current screen orientation
        bool screen_is_landscape = (rect.size.height < rect.size.width);
        bool is_iPad = (UI_USER_INTERFACE_IDIOM() != UIUserInterfaceIdiomPhone);
        bool is_iPhone = !is_iPad;

        screen.pixelRatio = scale;

        if(is_iPhone)
        {
            switch(ori)
            {
                default:
                case UIInterfaceOrientationPortrait: 			screen.rotation = fxScreen::Rotation::NONE; screen.isPortrait = true;  break;
                case UIInterfaceOrientationPortraitUpsideDown: 	screen.rotation = fxScreen::Rotation::FULL; screen.isPortrait = true;  break;
                case UIInterfaceOrientationLandscapeLeft: 		screen.rotation = fxScreen::Rotation::RCW;  screen.isPortrait = false; break;
                case UIInterfaceOrientationLandscapeRight: 		screen.rotation = fxScreen::Rotation::RCCW; screen.isPortrait = false; break;
            }
        }
        else
        {
            switch(ori)
            {
                default:
                case UIInterfaceOrientationPortrait: 			screen.rotation = fxScreen::Rotation::NONE; screen.isPortrait = true;  break;
                case UIInterfaceOrientationPortraitUpsideDown: 	screen.rotation = fxScreen::Rotation::FULL; screen.isPortrait = true;  break;
                case UIInterfaceOrientationLandscapeLeft: 		screen.rotation = fxScreen::Rotation::RCW;  screen.isPortrait = false; break;
                case UIInterfaceOrientationLandscapeRight: 		screen.rotation = fxScreen::Rotation::RCCW; screen.isPortrait = false; break;
            }
        }

        switch(ori)
        {
            case UIInterfaceOrientationPortrait:
            case UIInterfaceOrientationPortraitUpsideDown:
                screen.top = [UIApplication sharedApplication].statusBarFrame.size.height;
                screen.width = rect.size.width;
                screen.height = rect.size.height;
                break;

            case UIInterfaceOrientationLandscapeLeft:
            case UIInterfaceOrientationLandscapeRight:
                screen.top = [UIApplication sharedApplication].statusBarFrame.size.width;
                screen.isPortrait = false;
                screen.width = rect.size.height;
                screen.height = rect.size.width;
                break;
        }
    }
    else
    {
		screen.pixelRatio = scale;
		screen.rotation =fxScreen::Rotation::NONE;
		screen.isPortrait=false;
		screen.top = 0;
		screen.width = rect.size.width;
		screen.height = rect.size.height;
    }

    if((self = [super initWithFrame:rect]))
    {
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

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)initGLRenderStorage
{
    [[EAGLContext currentContext] renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer*)self.layer];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)InitGL
{
	context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];
    [EAGLContext setCurrentContext:context];

    if(screen.isPortrait)
		glViewport(0, 0, screen.width * screen.pixelRatio, screen.height * screen.pixelRatio);
	else
		glViewport(0, 0, screen.height * screen.pixelRatio, screen.width * screen.pixelRatio);

    glGenFramebuffers(1, &fbuff);
    glBindFramebuffer(GL_FRAMEBUFFER, fbuff);

    glGenRenderbuffers(1, &rbuff);
    glBindRenderbuffer(GL_RENDERBUFFER, rbuff);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screen.width * screen.pixelRatio, screen.height * screen.pixelRatio);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbuff);

    [self initGLRenderStorage];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)SetContext
{
    [EAGLContext setCurrentContext:context];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)ClearContext
{
	[EAGLContext setCurrentContext:nil];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)SetBuffers
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbuff);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
- (void)SwapBuffers
{
    [context presentRenderbuffer:GL_RENDERBUFFER];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
- (fxScreen)GetScreen
{
    return screen;
}

@end
