/* Generated by Coconut2D C++ Compiler from file CocoUIPage.jspp */

#ifndef __COCOUIPAGE_HPP__
#define __COCOUIPAGE_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"
#include "CocoUIView.hpp"
#include "CocoClip.hpp"
#include "CocoScene.hpp"
#include "CanvasRenderingContext2D.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CocoUIPageView : public CocoUIView
{
public:
	const String __className = String("CocoUIPageView");
	CocoUIPageView();
	virtual ~CocoUIPageView();
	CocoClip* addChild(CocoClip* clipInstance);
	virtual void repaint(CocoScene* scene, CocoClip* parentClip, CanvasRenderingContext2D* ctx);
};

#endif // __COCOUIPAGE_HPP__
