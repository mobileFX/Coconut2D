#ifndef __COCOSCENE_HPP__
#define __COCOSCENE_HPP__

#include "Coconut2D.hpp"
#include "CocoImage.hpp"
#include "CocoImageSibling.hpp"
#include "CocoClip.hpp"
#include "CocoMatrix.hpp"
#include "WebGLRenderingContext.hpp"
#include "HTMLCanvasElement.hpp"
#include "HTMLWindow.hpp"
#include "HTMLImageElement.hpp"
#include "CocoEngine.hpp"
#include "CocoKeyFrame.hpp"
#include "CocoTimeline.hpp"
#include "CocoScene.hpp"

class CocoScene
{
public:
	String __sceneName;
	Array<CocoImage*> __imageSymbols;
	float __fps;
	float __view_width;
	float __view_height;
	float __view_pixel_ratio;
	float __view_scale;
	CocoClip* __root;
	CocoMatrix* __modelViewMatrix;
	CocoMatrix* __projectionMatrix;
	WebGLProgram* __glProgram;
	WebGLProgram* __glProgram_Simple;
	WebGLProgram* __glProgram_SimpleWithAlpha;
	WebGLProgram* __glProgram_SaturationWithAlpha;
	Array<CocoClip*> __levelParents;
	String __vertex_shader_Common;
	String __fragment_shader_Simple;
	String __fragment_shader_SimpleWithAlpha;
	String __fragment_shader_SaturationWithAlpha;
	String __boundingBoxVertexShader;
	String __boundingBoxFragmentShader;
	WebGLProgram* __boundingBoxProgram;
	WebGLBuffer* __boundingBoxBuffer;
	bool __ready;
	bool __finished;
	CocoScene();
	~CocoScene();
	CocoImage* getImageSymbol(String symbolName);
	CocoImage* newResourceImage(String symbolName, String baseUrl);
	void prepare(WebGLRenderingContext* gl);
	WebGLProgram* makeProgram(WebGLRenderingContext* gl, String vs, String fs);
	void loadResources();
	bool resourcesLoaded(WebGLRenderingContext* gl);
	virtual void paint(WebGLRenderingContext* gl, Time time);
	bool setFilter(int filter);
	void drawFrame(WebGLRenderingContext* gl, CocoImage* image, int frame, CocoKeyFrame* KF);
	void gotoAndPlayByName(String LabelName);
	void gotoAndStopByName(String LabelName);
	void gotoAndPlayByIndex(int FrameIndex);
	void gotoAndStopyByIndex(int FrameIndex);
	static void stop(CocoScene* scene, CocoClip* clip);
	void stop();
};

#endif
