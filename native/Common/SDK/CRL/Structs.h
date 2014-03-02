/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
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

#ifndef _Structs_h
#define _Structs_h

typedef unsigned char uint8_t;

struct fxScreen
{
	int width;
	int height;
    int top;
	double pixelRatio;
    bool isPortrait;
    enum class Rotation
    {
		NONE = 0,
		RCW,
        RCCW,
        FULL
	} rotation;
};

template<typename T> struct fxPoint
{
    T x, y;
};

template<typename T> struct fxRect
{
    fxPoint<T> pos, size;
};

enum class ArgState : uint8_t
{
    NONE = 0,
    SCRIPTS = 1,
    FONTS = 2
};

#endif

