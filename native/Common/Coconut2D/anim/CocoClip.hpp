#ifndef __COCOCLIP_HPP__
#define __COCOCLIP_HPP__

#include "Coconut2D.hpp"
#include "EventTarget.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoImage.hpp"
#include "CocoSound.hpp"
#include "CocoSequence.hpp"
#include "CocoTimeline.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoVector.hpp"

class CocoClip : public EventTarget
{
public:
	std::string __instanceName;
	CocoImage* __image;
	CocoSound* __audio;
	COCO_CLIP_SYMBOL_LOOP_ENUM __symbolLoop;
	Array<CocoClip*> __children;
	CocoSequence* __currentSequence;
	int __currentSequenceFrameIndex;
	CocoTimeline* __timeline;
	CocoClip* __parent;
	float __firstTickTime;
	CocoKeyFrame* __currentFrame;
	bool __hasBoundingBox;
	CocoVector* __vTOP_LEFT;
	CocoVector* __vTOP_RIGHT;
	CocoVector* __vBOTTOM_LEFT;
	CocoVector* __vBOTTOM_RIGHT;
	CocoClip* __childWithMaxTimelineDuration;
	CocoClip(CocoImage* image, CocoSound* audio, std::string sequence);
	void prepare(CocoScene* scene);
	void reset();
	CocoClip* addChild(CocoClip* clipInstance);
	CocoClip* removeChild(CocoClip* clipInstance);
	void normalize();
	CocoClip* getChildByName(std::string instanceName);
	int getChildIndex(CocoClip* child);
	bool gotoFrameByName(std::string LabelName, bool pause, bool deep);
	bool gotoFrameByIndex(int FrameIndex, bool pause, bool deep);
	void render(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip, bool picking);
	bool hitTest(float wx, float wy);
	void initBoundingBoxFromTexture(CocoScene* scene, float W2, float H2);
	void initBoundingBoxFromChildren(CocoScene* scene);
	void drawBoundingBox(CocoScene* scene, WebGLRenderingContext* gl);
};

#endif
