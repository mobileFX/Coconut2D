#ifndef __COCOCLIP_HPP__
#define __COCOCLIP_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoImage.hpp"
#include "CocoSequence.hpp"
#include "CocoTimeline.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoVector.hpp"
#include "CocoMatrix.hpp"
#include "CocoAudio.hpp"

class CocoClip
{
public:
	String __instanceName;
	CocoImage* __image;
	COCO_CLIP_SYMBOL_LOOP_ENUM __symbolLoop;
	Array<CocoClip*> __children;
	CocoSequence* __currentSequence;
	int __currentSequenceFrameIndex;
	CocoTimeline* __timeline;
	CocoClip* __parent;
	float __firstTickTime;
	CocoKeyFrame* __currentFrame;
	bool __hasBoundingBox;
	CocoVector* __vABS_TOP_LEFT;
	CocoVector* __vABS_TOP_RIGHT;
	CocoVector* __vABS_BOTTOM_LEFT;
	CocoVector* __vABS_BOTTOM_RIGHT;
	CocoVector* __vREL_TOP_LEFT;
	CocoVector* __vREL_TOP_RIGHT;
	CocoVector* __vREL_BOTTOM_LEFT;
	CocoVector* __vREL_BOTTOM_RIGHT;
	CocoVector* __vTemp;
	CocoMatrix* __mTemp;
	CocoClip* __childWithMaxTimelineDuration;
	CocoAudio* __currentAudio;
	CocoClip(CocoImage* image = nullptr, String sequence = "");
	~CocoClip();
	void prepare(CocoScene* scene);
	void reset();
	CocoClip* addChild(CocoClip* clipInstance);
	CocoClip* removeChild(CocoClip* clipInstance);
	void normalize();
	CocoClip* getChildByName(String instanceName);
	int getChildIndex(CocoClip* child);
	bool gotoFrameByName(String LabelName, bool pause, bool deep);
	bool gotoFrameByIndex(int FrameIndex, bool pause, bool deep);
	virtual void paint(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip);
	bool hitTest(float wx, float wy);
	void initBoundingBoxFromTexture(CocoScene* scene, float W2, float H2);
	void initBoundingBoxFromChildren(CocoScene* scene);
	void drawBoundingBox(CocoScene* scene, WebGLRenderingContext* gl);
};

#endif
