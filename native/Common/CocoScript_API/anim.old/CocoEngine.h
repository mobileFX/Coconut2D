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

#ifndef __CocoEngine__
#define __CocoEngine__

#include "Coconut2D.h"
#include "CocoEngineState.h"
#include "CocoScene.h"

// ==================================================================================================================================
//	   ______                 ______            _
//	  / ____/___  _________  / ____/___  ____ _(_)___  ___
//	 / /   / __ \/ ___/ __ \/ __/ / __ \/ __ `/ / __ \/ _ \
//	/ /___/ /_/ / /__/ /_/ / /___/ / / / /_/ / / / / /  __/
//	\____/\____/\___/\____/_____/_/ /_/\__, /_/_/ /_/\___/
//	                                  /____/
// ==================================================================================================================================

/*
    A CocoEngine is a state machine that consists of an array of CocoEngineStates.
*/

////////////////////////////////////////////////////////////////////////////////////////////////////
class CocoEngine
{
public:

    CocoEngineState* __currentState;
    CocoEngineState* __nextState;
    Number __stateStart;

    ///////////////////////////////////////////////////////////////////////////////////////////////
    CocoEngine()
    {
        __currentState = null;
        __nextState = null;
        __stateStart = 0;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    CocoEngineState* currentState()
    {
        return __currentState;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    setState(CocoEngineState* state)
    {
        __nextState = state;
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    tick(WebGLRenderingContext* gl, Number time)
    {
        // Change state
        if(__nextState!=null)
        {
            __currentState = __nextState;
            __nextState = null;
            __stateStart = time;
        }

        // Tick current engine state
        __currentState->tick(this, gl, time - __stateStart);
    }
}

#endif
