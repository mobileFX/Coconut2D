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

#include "Touch.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
Touch::Touch()
{
	identifier = 0;
	target = nullptr;
	screenX = 0;
	screenY = 0;
	clientX = 0;
	clientY = 0;
	pageX = 0;
	pageY = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Touch::~Touch()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Touch::initTouch(int identifier, EventTarget* target, int screenX, int screenY, int clientX, int clientY, int pageX, int pageY)
{
	this->identifier = identifier;
	this->target = target;
	this->screenX = screenX;
	this->screenY = screenY;
	this->clientX = clientX;
	this->clientY = clientY;
	this->pageX = pageX;
	this->pageY = pageY;
}
