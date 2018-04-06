﻿/* ***** BEGIN LICENSE BLOCK *****
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

// ==================================================================================================================================
//	   ______                 ______                 __  ______                            __  _             ____        _       __
//	  / ____/___  _________  / ____/   _____  ____  / /_/ ____/___  ____  ____  ___  _____/ /_(_)___  ____  / __ \____  (_)___  / /_
//	 / /   / __ \/ ___/ __ \/ __/ | | / / _ \/ __ \/ __/ /   / __ \/ __ \/ __ \/ _ \/ ___/ __/ / __ \/ __ \/ /_/ / __ \/ / __ \/ __/
//	/ /___/ /_/ / /__/ /_/ / /___ | |/ /  __/ / / / /_/ /___/ /_/ / / / / / / /  __/ /__/ /_/ / /_/ / / / / ____/ /_/ / / / / / /_
//	\____/\____/\___/\____/_____/ |___/\___/_/ /_/\__/\____/\____/_/ /_/_/ /_/\___/\___/\__/_/\____/_/ /_/_/    \____/_/_/ /_/\__/
//
// ==================================================================================================================================

#ifndef __COCOEVENTCONNECTIONPOINT_HPP__
#define __COCOEVENTCONNECTIONPOINT_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"
#include "engine/CocoEvent.hpp"
#include "IEventListener.hpp"
#include "CocoEventSource.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CocoEventConnectionPoint
{
public:
	CocoEvent* Event;
	int32_t DispID;
	void* Listener;
	const String __className = String("CocoEventConnectionPoint");
	CocoEventConnectionPoint(CocoEvent* Event, void* Listener, int32_t DispID);
	virtual ~CocoEventConnectionPoint();
};

#endif // __COCOEVENTCONNECTIONPOINT_HPP__
