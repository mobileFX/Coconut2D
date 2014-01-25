#ifndef __COCOCLIP_HPP__
#define __COCOCLIP_HPP__

#include "Coconut2D.hpp"
#include "CocoScene.hpp"
#include "CocoClip.hpp"
#include "WebGLRenderingContext.hpp"
#include "CocoImage.hpp"
#include "CocoTimeline.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoVector.hpp"
#include "CocoMatrix.hpp"
#include "CocoSequence.hpp"
#include "CocoAudio.hpp"
#include "HTMLDocument.hpp"

class CocoClip
{
public:
	String __instanceName;
	CocoScene* __scene;
	CocoImage* __image;
	COCO_CLIP_SYMBOL_LOOP_ENUM __symbolLoop;
	Array<CocoClip*> __children;
	CocoTimeline* __timeline;
	CocoClip* __parent;
	Time __currentTime;
	CocoKeyFrame* __currentFrame;
	String __clipPath;
	CocoClip* __childWithMaxTimelineDuration;
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
	CocoSequence* __currentSequence;
	CocoAudio* __currentAudio;
	CocoClip(CocoImage* image = nullptr);
	~CocoClip();
	void prepare(CocoScene* scene);
	void createTextTexture(String text, String fontName, int fontSizePixels, COCO_TEXT_ALIGN_ENUM hAlign, COCO_TEXT_ALIGN_ENUM vAlign, bool multiline, COCO_TEXT_TRIMMING_ENUM trimming, String CSSColor, int textRectWidth, int textRectHeight);
	void reset();
	CocoClip* addChild(CocoClip* clipInstance);
	CocoClip* removeChild(CocoClip* clipInstance);
	void normalize();
	CocoClip* getChildByName(String instanceName);
	int getChildIndex(CocoClip* child);
	bool gotoFrameByName(String LabelName, bool pause = false, bool deep = false);
	bool gotoFrameByIndex(int FrameIndex, bool pause = false, bool deep = false);
	virtual void paint(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip, bool calcBoundingBox, int level);
	void setText(String text);
	bool hitTest(float wx, float wy);
	void initBoundingBoxFromTexture(CocoScene* scene, float W2, float H2);
	void initBoundingBoxFromChildren(CocoScene* scene);
	void drawBoundingBox(CocoScene* scene, WebGLRenderingContext* gl);
};

#endif
