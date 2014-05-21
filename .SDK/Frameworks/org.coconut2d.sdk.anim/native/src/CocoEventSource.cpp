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

// ==================================================================================================================================
//	   ______                 ______                 __  _____
//	  / ____/___  _________  / ____/   _____  ____  / /_/ ___/____  __  _______________
//	 / /   / __ \/ ___/ __ \/ __/ | | / / _ \/ __ \/ __/\__ \/ __ \/ / / / ___/ ___/ _ \
//	/ /___/ /_/ / /__/ /_/ / /___ | |/ /  __/ / / / /_ ___/ / /_/ / /_/ / /  / /__/  __/
//	\____/\____/\___/\____/_____/ |___/\___/_/ /_/\__//____/\____/\__,_/_/   \___/\___/
//
// ==================================================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CocoEventSource.hpp"
#include "CocoEventConnectionPoint.hpp"
#include "CocoEvent.hpp"
#include "IEventListener.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEventSource::CocoEventSource()
{
	__eventListeners = new Array<CocoEventConnectionPoint*> ();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoEventSource::~CocoEventSource()
{
	if(__eventListeners)
	{
		__eventListeners = (delete __eventListeners, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoEventSource::addEventListener(CocoEvent* Event, void* Listener, int DispID)
{
	CocoEventConnectionPoint* item = new CocoEventConnectionPoint(Event, Listener, DispID);
	__eventListeners->push(item);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoEventSource::removeEventListener(CocoEvent* Event, void* Listener, int DispID)
{
	/*
	int i = 0;
	for(i = __eventListeners->size() - 1; i >= 0; i--)
	{
		if((*__eventListeners)[i]->Event->is(Event) && (*__eventListeners)[i]->Listener == Listener && (*__eventListeners)[i]->Callback == Callback)
		{
			__eventListeners->splice(i, 1);
			return true;
		}
	}
	*/
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int CocoEventSource::dispatchEvent(CocoEvent* Event)
{
	int c = 0;
	int i = 0;

	for(i = __eventListeners->size() - 1; i >= 0; i--)
	{
		CocoEventConnectionPoint* cp = (*__eventListeners)[i];
		if(cp->Event->is(Event))
		{
			c++;
			bool cancel = ((IEventListener*)cp->Listener)->__dispatch_event__(cp->Listener, cp->DispID, this, Event);
			if(cancel)
			{
				(*__eventListeners)[i]->Event->cancelBubble();
			}
			if((*__eventListeners)[i]->Event->stopPropagation)
			{
				break;
			}
		}
	}

	return c;
}
