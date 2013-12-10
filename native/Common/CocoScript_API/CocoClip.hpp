#ifndef __COCOCLIP_HPP__
#define __COCOCLIP_HPP__

class CocoClip
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
	void reset();
	CocoClip* addChild(CocoClip* clipInstance);
	CocoClip* removeChild(CocoClip* clipInstance);
	void normalize();
	CocoClip* getChildByName(std::string instanceName);
	int getChildIndex(CocoClip* child);
	bool gotoFrame(undefined LabelNameOrFrameIndex, bool pause, bool deep);
	void render(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip, bool picking);
};

#endif
