#ifndef __COCOSCENE_HPP__
#define __COCOSCENE_HPP__

class CocoScene
{
public:
	std::string __sceneName;
	Array<CocoImage*> __imageSymbols;
	Array<CocoSound*> __soundSymbols;
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
	void loadResources();
	bool resourcesLoaded(WebGLRenderingContext* gl);
	void tick(WebGLRenderingContext* gl, float time);
	void drawFrame(WebGLRenderingContext* gl, CocoImage* image, float frame, float alpha);
	bool gotoAndPlay(Object* LabelNameOrFrameIndex, bool deep);
	bool gotoAndStop(Object* LabelNameOrFrameIndex, bool deep);
	bool stop(bool deep);
};

#endif
