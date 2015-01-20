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
//	    __  __________  _____    ___             ___       ________                          __
//	   / / / /_  __/  |/  / /   /   | __  ______/ (_)___  / ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /   / /| |/ / / / __  / / __ \/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ ___ / /_/ / /_/ / / /_/ / /___/ /  __/ / / / / /  __/ / / / /_
//	/_/ /_/ /_/ /_/  /_/_____/_/  |_\__,_/\__,_/_/\____/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

#ifndef __HTMLVideoElement_HPP__
#define __HTMLVideoElement_HPP__

#include "Coconut2D.hpp"
#include "HTMLElement.hpp"

class HTMLVideoElement :
	public HTMLElement
{
public:
	float duration;
	float currentTime;
	float width;
	float height;
	bool paused;
	bool ended;
	bool autoplay;
	bool loop;
	String src;
	HTMLVideoElement();
	~HTMLVideoElement();
	void tick();
	void play();
	void pause();
	float __get_width();
	void __set_width(float w);
	float __get_height();
	void __set_height(float h);
	String __get_src();
	void __set_src(String src);
	float __get_currentTime();
	void __set_currentTime(float time);
	int __get_readyState();
};

#endif // __HTMLVideoElement_HPP__
