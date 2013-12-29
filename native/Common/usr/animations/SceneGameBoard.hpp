#ifndef __SCENEGAMEBOARD_HPP__
#define __SCENEGAMEBOARD_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoClip.hpp"
#include "CocoKeyFrame.hpp"

class SceneGameBoard : public CocoScene
{
public:
	SceneGameBoard();
	void btnBuyTicketClicked(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
	void btnOpenAllClicked(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
	void btnPlayAgainClicked(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
	void changeSequence(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
	void waitForAction(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
	void playBustedAnim(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
	void changeBettingText(WebGLRenderingContext* gl, float currentTime, float loopTime, CocoClip* clip, CocoKeyFrame* keyFrame);
};

#endif
