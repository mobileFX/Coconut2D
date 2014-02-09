#ifndef _fxGLWrap_h
#define _fxGLWrap_h

#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <QuartzCore/CAEAGLLayer.h>
#import "Structs.h"

@interface fxGLWrap : UIView
{
    EAGLContext* context;
    GLuint fbuff, rbuff;
    fxScreen screen;
}

- (id)initWithFrame:(CGRect)rect contentsScale:(CGFloat)scale;
- (void)InitGL;
- (void)QuitGL;
- (void)SetContext;
- (void)ClearContext;
- (void)SetBuffers;
- (void)SwapBuffers;
- (fxScreen)GetScreen;

@end

#endif