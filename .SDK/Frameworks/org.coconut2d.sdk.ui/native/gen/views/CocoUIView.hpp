/* Generated by Coconut2D C++ Compiler from file CocoUIView.jspp */

#ifndef __COCOUIVIEW_HPP__
#define __COCOUIVIEW_HPP__

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coconut2D.hpp"
#include "CocoClip.hpp"
#include "ICocoRenderContext.hpp"
#include "CocoScene.hpp"
#include "CanvasRenderingContext2D.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CocoUIView : public CocoClip
{
public:
	float __x;
	float __y;
	float __width;
	float __height;
	bool __visible;
	bool __textureIsInvalid;
	bool __enabled;
	const String __className = String("CocoUIView");
	CocoUIView();
	virtual ~CocoUIView();
	String __get_Name();
	void __set_Name(String v);
	bool __get_Enabled();
	void __set_Enabled(bool v);
	float __get_Width();
	void __set_Width(float v);
	float __get_Height();
	void __set_Height(float v);
	float __get_Left();
	void __set_Left(float v);
	float __get_Top();
	void __set_Top(float v);
	bool __get_Visible();
	void __set_Visible(bool v);
	virtual void move(float x, float y, float width, float height);
	virtual void invalidate();
	virtual void paint(ICocoRenderContext* ctx, CocoScene* scene, CocoClip* parentClip, bool calcBoundingBox, int level);
	virtual void repaint(CocoScene* scene, CocoClip* parentClip, CanvasRenderingContext2D* ctx) = 0;
};

#endif // __COCOUIVIEW_HPP__
