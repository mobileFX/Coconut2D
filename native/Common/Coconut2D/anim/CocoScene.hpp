#ifndef __COCOSCENE_HPP__
#define __COCOSCENE_HPP__

#include "Coconut2D.hpp"
#include "CocoImage.hpp"
#include "CocoSound.hpp"
#include "WebGLRenderingContext.hpp"
#include "WebGLProgram.hpp"
#include "CocoClip.hpp"
#include "CocoMatrix.hpp"
#include "WebGLBuffer.hpp"

class CocoScene
{
public:
	std::string __sceneName;
	Array<CocoImage*> __imageSymbols;
	Array<CocoSound*> __soundSymbols;
	Array<CocoClip*> __clipSymbols;
	float __fps;
	float __view_width;
	float __view_height;
	float __view_pixel_ratio;
	float __view_scale;
	float __currentTime;
	float __elapsedTime;
	float __startTime;
	CocoClip* __root;
	CocoMatrix* __modelViewMatrix;
	CocoMatrix* __projectionMatrix;
	WebGLProgram* __glProgram;
	Array<CocoClip*> __levelParents;
	std::string __vertex_shader;
	std::string __fragment_shader;
	std::string __boundingBoxVertexShader;
	std::string __boundingBoxFragmentShader;
	WebGLProgram* __boundingBoxProgram;
	WebGLBuffer* __boundingBoxBuffer;
	bool __ready;
	CocoScene(std::string sceneName);
	CocoImage* getImageSymbol(std::string symbolName);
	CocoSound* getSoundSymbol(std::string symbolName);
	CocoImage* newResourceImage(std::string symbolName, std::string baseUrl);
	CocoSound* newResourceSound(std::string symbolName, std::string filename);
	void prepare(WebGLRenderingContext* gl);
	WebGLProgram* makeProgram(WebGLRenderingContext* gl, std::string vs, std::string fs);
	void loadResources();
	bool resourcesLoaded(WebGLRenderingContext* gl);
	void tick(WebGLRenderingContext* gl, float time);
	void drawFrame(WebGLRenderingContext* gl, CocoImage* image, float frame, float alpha);
	void gotoAndPlayByName(std::string LabelName, bool deep = false);
	void gotoAndStopByName(std::string LabelName, bool deep = false);
	void gotoAndPlayByIndex(int FrameIndex, bool deep = false);
	void gotoAndStopyByIndex(int FrameIndex, bool deep = false);
	void stop(bool deep = false);
};

#endif
