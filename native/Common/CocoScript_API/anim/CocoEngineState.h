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

#ifndef __CocoEngineState__
#define __CocoEngineState__

#include "Coconut2D.h"
#include "CocoScene.h"

// ==================================================================================================================================
//	   ______                 ______            _           _____ __        __
//	  / ____/___  _________  / ____/___  ____ _(_)___  ___ / ___// /_____ _/ /____
//	 / /   / __ \/ ___/ __ \/ __/ / __ \/ __ `/ / __ \/ _ \\__ \/ __/ __ `/ __/ _ \
//	/ /___/ /_/ / /__/ /_/ / /___/ / / / /_/ / / / / /  __/__/ / /_/ /_/ / /_/  __/
//	\____/\____/\___/\____/_____/_/ /_/\__, /_/_/ /_/\___/____/\__/\__,_/\__/\___/
//	                                  /____/
// ==================================================================================================================================

class CocoEngineState
{
public:

    String id;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoEngineState()
    {
        id = "Undefined";
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoEngineState(String ID)
    {
        this.id = ID;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ~CocoEngineState()
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    String toString()
    {
        return "[CocoEngineState " + id + "]";
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    tick(CocoEngine* engine, WebGLRenderingContext* gl, Number time)
    {
    }
}

#endif
