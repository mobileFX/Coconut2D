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

// ==================================================================================================================================
//	   ______               _    __          __            
//	  / ____/___  _________| |  / /__  _____/ /_____  _____
//	 / /   / __ \/ ___/ __ \ | / / _ \/ ___/ __/ __ \/ ___/
//	/ /___/ /_/ / /__/ /_/ / |/ /  __/ /__/ /_/ /_/ / /    
//	\____/\____/\___/\____/|___/\___/\___/\__/\____/_/     
//	                                                       
// ================================================================================================================================== 

#ifndef __CocoVector__
#define __CocoVector__

#include "Coconut2D.h" 

class CocoVector
{

public:

    Number X;
    Number Y;
    Number Z;
    Number W;
	
	CocoVector()
	{
		X = 0.0;
		Y = 0.0;
		Z = 0.0;
		W = 1.0;   
		
	}
	
	~CocoVector()
	{
	}
	
    set(Number x, Number y, Number z, Number w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
}

#endif

