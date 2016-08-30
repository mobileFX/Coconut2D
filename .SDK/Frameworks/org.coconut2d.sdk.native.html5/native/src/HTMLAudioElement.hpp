/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2016 www.mobilefx.com
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

#ifndef __HTMLAUDIOELEMENT_HPP__
#define __HTMLAUDIOELEMENT_HPP__

#include "Coconut2D.hpp"
#include "Audio/CocoAudioSystem.h"

// ==================================================================================================================================
//	    __  __________  _____    __  ___         ___       ________                          __
//	   / / / /_  __/  |/  / /   /  |/  /__  ____/ (_)___ _/ ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /   / /|_/ / _ \/ __  / / __ `/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ /  / /  __/ /_/ / / /_/ / /___/ /  __/ / / / / /  __/ / / / /_
//	/_/ /_/ /_/ /_/  /_/_____/_/  /_/\___/\__,_/_/\__,_/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

/*
class HTMLMediaElement
{
public:

	String src;
	float duration;
	bool paused;
	bool ended;
	bool autoplay;
	bool loop;

	float __currentTime;

	HTMLMediaElement(String url)
	{
		duration = 0;
		paused = true;
		ended = true;
		autoplay = false;
		loop = false;

		src = CocoAssetFile::filesPath + url.substr(2);
	}

	virtual ~HTMLMediaElement(){}

	virtual void play(){}
	virtual void pause(){}

	virtual float __get_currentTime(){return 0;}
	virtual void __set_currentTime(float time){}
	virtual int32_t __get_readyState(){return 0;}
};
*/

// ==================================================================================================================================
//	    __  __________  _____    ___             ___       ________                          __
//	   / / / /_  __/  |/  / /   /   | __  ______/ (_)___  / ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /   / /| |/ / / / __  / / __ \/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ ___ / /_/ / /_/ / / /_/ / /___/ /  __/ / / / / /  __/ / / / /_
//	/_/ /_/ /_/ /_/  /_/_____/_/  |_\__,_/\__,_/_/\____/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

class Audio
{
public:

	String src;
	float duration;
	bool paused;
	bool ended;
	bool autoplay;
	bool loop;
	float __currentTime;
	CocoAudioSource* source;

	Audio(String url);
	virtual ~Audio();
	void play();
	void pause();
	bool __get_ended();
	float __get_duration();
	bool __get_paused();
	float __get_currentTime();
	int32_t __get_readyState();
	void __set_autoplay(bool v);
	void __set_loop(bool v);
	void __set_currentTime(float time);
};

#endif /* __HTMLAUDIOELEMENT_HPP__ */
