/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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

#ifndef __COCODEVICEOPENGL_HPP__
#define __COCODEVICEOPENGL_HPP__

#import <UIKit/UIView.h>
#import <UIKit/UIApplication.h>
#import <QuartzCore/CAEAGLLayer.h>
#import <OpenGLES/ES2/gl.h>
#import "Structs.h"

@interface CocoDeviceOpenGLContext : UIView
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

