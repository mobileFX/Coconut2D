/* Generated by Coconut2D C++ Compiler from file CocoUIPage.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CocoUIPage.hpp"
#include "CocoClip.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoUIPageView::CocoUIPageView()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoUIPageView::~CocoUIPageView()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoClip* CocoUIPageView::addChild(CocoClip* clipInstance)
{
	invalidate();
	return CocoUIView::addChild(clipInstance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoUIPageView::repaint(CocoScene* scene, CocoClip* parentClip, CanvasRenderingContext2D* ctx)
{
}
