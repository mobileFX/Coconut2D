#ifndef __COCOSCENE_HPP__
#define __COCOSCENE_HPP__

#include "Coconut2D.hpp"
#include "CocoImage.hpp"
#include "WebGLRenderingContext.hpp"
//#include "WebGLProgram.hpp"
#include "CocoClip.hpp"
#include "CocoMatrix.hpp"
//#include "WebGLBuffer.hpp"

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
	Array<CocoClip*> __levelParents;
	String __vertex_shader;
	String __fragment_shader;
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
	void drawFrame(WebGLRenderingContext* gl, CocoImage* image, int frame, float red, float green, float blue, float alpha, bool flipH, bool flipV);
	void gotoAndPlayByName(String LabelName);
	void gotoAndStopByName(String LabelName);
	void gotoAndPlayByIndex(int FrameIndex);
	void gotoAndStopyByIndex(int FrameIndex);
	void stop();
};

#endif
