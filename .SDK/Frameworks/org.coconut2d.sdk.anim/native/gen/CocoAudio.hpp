#ifndef __COCOAUDIO_HPP__
#define __COCOAUDIO_HPP__

#include "Coconut2D.hpp"

class CocoAudio
{
public:
	String src;
	Audio* audio;
	bool autoplay;
	int loops;
	bool __firstPlayed;
	int __loopCount;
	CocoAudio(String url, bool autoplay, int loops);
	~CocoAudio();
	void reset();
	void tick();
	void play();
	void pause();
	void stop();
	float duration();
	bool paused();
	bool ended();
	float getCurrentTime();
	void setCurrentTime(float t);
};

#endif
