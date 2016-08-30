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

#include "HTMLAudioElement.hpp"

Audio::Audio(String url)
{
	duration = 0;
	paused = true;
	ended = true;
	autoplay = false;
	loop = false;
	src = url;
	source = CocoAudioSystem::NewSource(src);
}

Audio::~Audio()
{
	delete source;
}

void Audio::play()								{ if (source) source->play(); }
void Audio::pause()								{ if (source) source->stop(); }

bool Audio::__get_ended()						{ return !source ? false : source->hasEnded(); }
float Audio::__get_duration()					{ return !source ? 0 : (float) source->duration; }
bool Audio::__get_paused()						{ return !source ? false : source->isPaused(); }
float Audio::__get_currentTime()				{ return !source ? 0 : source->get_position(); }
int32_t Audio::__get_readyState()				{ return 4; }

void Audio::__set_autoplay(bool v)				{ if (source) source->set_autoplay(v); }
void Audio::__set_loop(bool v)					{ if (source) source->set_loop(v); }
void Audio::__set_currentTime(float time)		{ if (source) source->set_position(time); }

