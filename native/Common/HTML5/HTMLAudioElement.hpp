//
//  HTMLAudioElement.hpp
//  CocoEngine
//
//  Created by Administrator on 1/22/14.
//
//

#ifndef __CocoEngine__HTMLAudioElement__
#define __CocoEngine__HTMLAudioElement__

#include "fxAudioStream.h"

//class HTMLAudioElement;
//typedef HTMLAudioElement Audio;

class Audio
{
public:
	fxAudioStream* stream;
	float __currentTime;
	float duration;
	bool paused;
	bool ended;
	bool autoplay;
	bool loop;
	String src;
	Audio(String url);
	~Audio();
	void tick();
	void play();
	void pause();
	float get_currentTime();
	void set_currentTime(float time);
	int get_readyState();
};

#endif /* defined(__CocoEngine__HTMLAudioElement__) */
