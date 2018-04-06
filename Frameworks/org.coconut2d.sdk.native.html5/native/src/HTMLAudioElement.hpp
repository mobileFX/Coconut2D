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

#ifndef __HTMLAUDIOELEMENT_HPP__
#define __HTMLAUDIOELEMENT_HPP__

#include "Coconut2D.hpp"
#include "Audio/CocoAudioSystem.h"
#include "HTMLElement.hpp"

// ==================================================================================================================================
//	    __  __________  _____    ___             ___       ________                          __
//	   / / / /_  __/  |/  / /   /   | __  ______/ (_)___  / ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /   / /| |/ / / / __  / / __ \/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ ___ / /_/ / /_/ / / /_/ / /___/ /  __/ / / / / /  __/ / / / /_
//	/_/ /_/ /_/ /_/  /_/_____/_/  |_\__,_/\__,_/_/\____/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

struct MediaError
{
	int code;
};

class Audio	: public HTMLElement
{
public:

	bool __owner;
	String id;
	float volume;
	String src;
	String preload;
	float duration;
	bool paused;
	bool ended;
	bool autoplay;
	bool loop;
	bool muted;
	float currentTime;
	int32_t readyState;
	CocoAudioSystemSource* source;
	MediaError* error;

	Audio();
	Audio(String url);
	virtual ~Audio();
	Audio* cloneNode(bool deep=true);
	void load();
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

	std::function<void()> onended;
	std::function<void()> onplay;
	std::function<void()> oncanplaythrough;
};

#endif /* __HTMLAUDIOELEMENT_HPP__ */
