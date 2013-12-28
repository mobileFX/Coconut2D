#include "CocoScene.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoScene::CocoScene(std::string sceneName)
{
	__sceneName = sceneName;
	__view_width = 0;
	__view_height = 0;
	__view_pixel_ratio = 0;
	__view_scale = 1;
	__currentTime = 0.0;
	__elapsedTime = 0.0;
	__startTime = -1;
	__root = NULL;
	__modelViewMatrix = NULL;
	__projectionMatrix = NULL;
	__glProgram = NULL;
	__vertex_shader = "attribute vec2 iVecCoords;attribute vec2 iTexCoords;uniform mat4 uProjMat;uniform mat4 uMVMat;uniform vec2 uSprSize;uniform vec2 uSprFrame;varying vec2 pTexCoord;void main(void){ gl_Position = uProjMat * uMVMat * vec4(iVecCoords, 0.0, 1.0); pTexCoord = vec2(((iTexCoords.x + uSprFrame.x) * uSprSize.x), ((iTexCoords.y + uSprFrame.y) * uSprSize.y));}";
	__fragment_shader = "#ifdef GL_ES\nprecision lowp float;\n#endif\nuniform sampler2D uSampler;uniform vec4 uColor;varying vec2 pTexCoord;void main(void){ gl_FragColor = vec4(texture2D(uSampler, pTexCoord).r * uColor.r, texture2D(uSampler, pTexCoord).g * uColor.g, texture2D(uSampler, pTexCoord).b * uColor.b, texture2D(uSampler, pTexCoord).a * uColor.a);}";
	__boundingBoxVertexShader = "attribute vec2 iVec2Coords;uniform mat4 uProjMat;void main(void){ gl_Position = uProjMat * vec4(iVec2Coords, 0.0, 1.0);}";
	__boundingBoxFragmentShader = "#ifdef GL_ES\nprecision lowp float;\n#endif\nvoid main(void){ gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);}";
	__boundingBoxProgram = NULL;
	__boundingBoxBuffer = NULL;
	__ready = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::getImageSymbol(std::string symbolName)
{
	for(int i = __imageSymbols.size() - 1; i >= 0; i--)
	{
		if(__imageSymbols[i]->symbolName == symbolName)
		{
			return __imageSymbols[i];
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSound* CocoScene::getSoundSymbol(std::string symbolName)
{
	for(int i = __soundSymbols.size() - 1; i >= 0; i--)
	{
		if(__soundSymbols[i]->symbolName == symbolName)
		{
			return __soundSymbols[i];
		}
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::newResourceImage(std::string symbolName, std::string baseUrl)
{
	if(getImageSymbol(symbolName))
	{
		throw CocoException("Resource image " + symbolName + " already exists.");
	}
	CocoImage* img = new CocoImage();
	img->symbolName = symbolName;
	img->baseUrl = baseUrl;
	__imageSymbols.push(img);
	return img;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSound* CocoScene::newResourceSound(std::string symbolName, std::string filename)
{
	if(getSoundSymbol(symbolName))
	{
		throw CocoException("Resource sound " + symbolName + " already exists.");
	}
	CocoSound* snd = new CocoSound();
	snd->symbolName = symbolName;
	snd->createFromFile(filename, NULL);
	__soundSymbols.push(snd);
	return snd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::prepare(WebGLRenderingContext* gl)
{
	gl->disable(gl->DEPTH_TEST);
	gl->enable(gl->BLEND);
	gl->blendFunc(gl->SRC_ALPHA, gl->ONE_MINUS_SRC_ALPHA);
	gl->disable(gl->CULL_FACE);
	__boundingBoxProgram = makeProgram(gl, __boundingBoxVertexShader, __boundingBoxFragmentShader);
	gl->useProgram(__boundingBoxProgram);
	__boundingBoxProgram->GLSLiVec2Coords = gl->getAttribLocation(__boundingBoxProgram, "iVec2Coords");
	__boundingBoxProgram->GLSLuProjMat = gl->getUniformLocation(__boundingBoxProgram, "uProjMat");
	__boundingBoxBuffer = gl->createBuffer();
	gl->bindBuffer(gl->ARRAY_BUFFER, __boundingBoxBuffer);
	gl->bufferData(gl->ARRAY_BUFFER, new Float32Array({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}), gl->DYNAMIC_DRAW);
	__glProgram = makeProgram(gl, __vertex_shader, __fragment_shader);
	gl->useProgram(__glProgram);
	__glProgram->GLSLiVecCoords = gl->getAttribLocation(__glProgram, "iVecCoords");
	gl->enableVertexAttribArray(__glProgram->GLSLiVecCoords);
	__glProgram->GLSLiTexCoords = gl->getAttribLocation(__glProgram, "iTexCoords");
	gl->enableVertexAttribArray(__glProgram->GLSLiTexCoords);
	__glProgram->GLSLuProjMat = gl->getUniformLocation(__glProgram, "uProjMat");
	__glProgram->GLSLuMVMat = gl->getUniformLocation(__glProgram, "uMVMat");
	__glProgram->GLSLuSprSize = gl->getUniformLocation(__glProgram, "uSprSize");
	__glProgram->GLSLuSprFrame = gl->getUniformLocation(__glProgram, "uSprFrame");
	__glProgram->GLSLuSampler = gl->getUniformLocation(__glProgram, "uSampler");
	__glProgram->GLSLuColor = gl->getUniformLocation(__glProgram, "uColor");
	__modelViewMatrix = new CocoMatrix();
	__modelViewMatrix->update(gl, __glProgram->GLSLuMVMat);
	__view_scale = this->__view_width > 0 && this->__view_height > 0 ? std::min((float)(gl->canvas->width) / (float)(this->__view_width), (float)(gl->canvas->height) / (float)(this->__view_height)) : window->devicePixelRatio;
	__projectionMatrix = new CocoMatrix();
	if(window->deviceRotation)
	{
		float c = std::cosf(window->deviceRotation);
		float s = std::sinf(window->deviceRotation);
		float orthoWidth = std::abs(c * gl->canvas->width + s * gl->canvas->height);
		float orthoHeight = std::abs(-s * gl->canvas->width + c * gl->canvas->height);
		__projectionMatrix->ortho((float)(-orthoWidth) / (float)(2.0), (float)(orthoWidth) / (float)(2.0), (float)(orthoHeight) / (float)(2.0), (float)(-orthoHeight) / (float)(2.0),  -1.0, 1.0);
		__projectionMatrix->rotateZ(-window->deviceRotation);
	}
	else
	{
		__projectionMatrix->ortho(-((float)(gl->canvas->width) / (float)(2.0)), (float)(gl->canvas->width) / (float)(2.0), (float)(gl->canvas->height) / (float)(2.0),  -((float)(gl->canvas->height) / (float)(2.0)),  -1.0, 1.0);
	}
	__projectionMatrix->scale(__view_scale, __view_scale);
	__projectionMatrix->update(gl, __glProgram->GLSLuProjMat);
	__root->prepare(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLProgram* CocoScene::makeProgram(WebGLRenderingContext* gl, std::string vs, std::string fs)
{
	WebGLShader* vshader = gl->createShader(gl->VERTEX_SHADER);
	WebGLShader* fshader = gl->createShader(gl->FRAGMENT_SHADER);
	gl->shaderSource(vshader, vs);
	gl->shaderSource(fshader, fs);
	gl->compileShader(vshader);
	gl->compileShader(fshader);
	if(!gl->getShaderParameter(vshader, gl->COMPILE_STATUS))
	{
		throw CocoException(gl->getShaderInfoLog(vshader));
	}
	if(!gl->getShaderParameter(fshader, gl->COMPILE_STATUS))
	{
		throw CocoException(gl->getShaderInfoLog(fshader));
	}
	WebGLProgram* program = gl->createProgram();
	gl->attachShader(program, vshader);
	gl->attachShader(program, fshader);
	gl->linkProgram(program);
	if(!gl->getProgramParameter(program, gl->LINK_STATUS))
	{
		throw CocoException(gl->getProgramInfoLog(program));
	}
	return program;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::loadResources()
{
	CocoImage* img;
	CocoImageSibling* sibling;
	for(int i = 0,  L = __imageSymbols.size(); i < L; i++)
	{
		img = __imageSymbols[i];
		if(__view_width && __view_height)
		{
			float w = img->viewOptimalWidth * __view_scale * window->devicePixelRatio;
			float h = img->viewOptimalHeight * __view_scale * window->devicePixelRatio;
			for(int j = 0; j < img->viewSiblings.size(); j++)
			{
				sibling = img->viewSiblings[j];
				if(sibling->textureWidth >= w && sibling->textureHeight >= h)
				{
					img->image = new Image();
					img->image->load(img->baseUrl + sibling->url);
					img->textureCellWidth = sibling->textureWidth;
					img->textureCellHeight = sibling->textureHeight;
					img->pixelRatio = sibling->pixelRatio;
					break;
				}
			}
		}
		if(!img->image)
		{
			sibling = img->viewSiblings[img->viewSiblings.size() - 1];
			img->image = new Image();
			img->image->load(img->baseUrl + sibling->url);
			img->textureCellWidth = sibling->textureWidth;
			img->textureCellHeight = sibling->textureHeight;
			img->pixelRatio = sibling->pixelRatio;
		}
		if(img->image)
		{
			trace("Loaded image: " + img->image->src);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoScene::resourcesLoaded(WebGLRenderingContext* gl)
{
	if(!__ready)
	{
		CocoImage* img;
		for(int i = __imageSymbols.size() - 1; i >= 0; i--)
		{
			img = __imageSymbols[i];
			if(!img->image || !img->image->width || !img->image->height)
			{
				return false;
			}
			else if(!img->texture)
			{
				img->prepare(gl);
			}
		}
		trace("Resources loaded.");
	}
	return (__ready = true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::tick(WebGLRenderingContext* gl, float time)
{
	if(!__glProgram)
	{
		prepare(gl);
		loadResources();
	}
	else if(resourcesLoaded(gl))
	{
		gl->clearColor(1.0, 1.0, 1.0, 1.0);
		gl->clear(gl->COLOR_BUFFER_BIT);
		if(__startTime == -1)
		{
			__startTime = time;
			__elapsedTime = 0;
		}
		else
		{
			__elapsedTime = (time - __startTime) - (__currentTime);
		}
		__currentTime = time - __startTime;
		if(__root)
		{
			__modelViewMatrix->identity();
			__levelParents = {__root};
			__root->render(gl, this, NULL, false);
			CocoClip* max = __root->__childWithMaxTimelineDuration;
			if(max && max->__currentFrame == max->__timeline->lastKeyFrame())
			{
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::drawFrame(WebGLRenderingContext* gl, CocoImage* image, float frame, float alpha)
{
	(*image->color)[3] = alpha;
	if(__modelViewMatrix->__dirty)
	{
		__modelViewMatrix->update(gl, __glProgram->GLSLuMVMat);
	}
	gl->uniform2f(__glProgram->GLSLuSprSize, (*image->texSize)[0], (*image->texSize)[1]);
	gl->uniform2f(__glProgram->GLSLuSprFrame, (*image->textureGrid)[frame * 2 + 1], (*image->textureGrid)[frame * 2]);
	gl->bindBuffer(gl->ARRAY_BUFFER, image->buffer);
	gl->vertexAttribPointer(__glProgram->GLSLiTexCoords, 2, gl->FLOAT, false, 16, 0);
	gl->vertexAttribPointer(__glProgram->GLSLiVecCoords, 2, gl->FLOAT, false, 16, 8);
	gl->bindTexture(gl->TEXTURE_2D, image->texture);
	gl->uniform1i(__glProgram->GLSLuSampler, 0);
	gl->uniform4fv(__glProgram->GLSLuColor, image->color);
	gl->drawArrays(gl->TRIANGLE_STRIP, 0, 4);
	gl->bindBuffer(gl->ARRAY_BUFFER, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndPlayByName(std::string LabelName, bool deep)
{
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByName(LabelName, false, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndStopByName(std::string LabelName, bool deep)
{
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByName(LabelName, true, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndPlayByIndex(int FrameIndex, bool deep)
{
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByIndex(FrameIndex, false, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndStopyByIndex(int FrameIndex, bool deep)
{
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByIndex(FrameIndex, true, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::stop(bool deep)
{
	deep = (deep == "true");
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByIndex(-1, true, deep);
}
