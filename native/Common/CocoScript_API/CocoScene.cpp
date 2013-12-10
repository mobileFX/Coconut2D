#include "CocoScene.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoScene::CocoScene(std::string sceneName)
{
	__sceneName = sceneName;
	__view_width = 0;
	__view_height = 0;
	__view_pixel_ratio = 0;
	__view_scale = 1;
	__currentTime = 0;
	__elapsedTime = 0;
	__startTime = -1;
	__root = NULL;
	__modelViewMatrix = NULL;
	__projectionMatrix = NULL;
	__glProgram = NULL;
	__vertex_shader = "attribute vec2 iVecCoords;attribute vec2 iTexCoords;uniform mat4 uProjMat;uniform mat4 uMVMat;uniform vec2 uSprSize;uniform vec2 uSprFrame;varying vec2 pTexCoord;void main(void){ gl_Position = uProjMat * uMVMat * vec4(iVecCoords, 0.0, 1.0); pTexCoord = vec2(((iTexCoords.x + uSprFrame.x) * uSprSize.x), ((iTexCoords.y + uSprFrame.y) * uSprSize.y));}";
	__fragment_shader = "#ifdef GL_ES\nprecision mediump float;\n#endif\nuniform sampler2D uSampler;uniform vec4 uColor;varying vec2 pTexCoord;void main(void){ gl_FragColor = vec4(texture2D(uSampler, pTexCoord).r * uColor.r, texture2D(uSampler, pTexCoord).g * uColor.g, texture2D(uSampler, pTexCoord).b * uColor.b, texture2D(uSampler, pTexCoord).a * uColor.a);}";
	__boundingBoxVertexShader = "attribute vec2 iVec2Coords;uniform mat4 uProjMat;void main(void){ gl_Position = uProjMat * vec4(iVec2Coords, 0.0, 1.0);}";
	__boundingBoxFragmentShader = "#ifdef GL_ES\nprecision mediump float;\n#endif\nvoid main(void){ gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);}";
	__boundingBoxProgram = NULL;
	__boundingBoxBuffer = NULL;
	__ready = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::getImageSymbol(std::string symbolName)
{
	for(int i = __imageSymbols.size() - 1; i >= 0; i--)
	{
		if(__imageSymbols[i]->symbolName == symbolName) { return __imageSymbols[i]; }
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSound* CocoScene::getSoundSymbol(std::string symbolName)
{
	for(int i = __soundSymbols.size() - 1; i >= 0; i--)
	{
		if(__soundSymbols[i]->symbolName == symbolName) { return __soundSymbols[i]; }
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::newResourceImage(std::string symbolName, std::string baseUrl)
{
	if(getImageSymbol(symbolName)) { throw CocoException("Resource image " + symbolName + " already exists."); }
	CocoImage* img = new CocoImage();
	img->symbolName = symbolName;
	img->baseUrl = baseUrl;
	__imageSymbols.push(img);
	return img;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSound* CocoScene::newResourceSound(std::string symbolName, std::string filename)
{
	if(getSoundSymbol(symbolName)) { throw CocoException("Resource sound " + symbolName + " already exists."); }
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
	__boundingBoxProgram = glu.makeProgram(gl, __boundingBoxVertexShader, __boundingBoxFragmentShader);
	gl->useProgram(__boundingBoxProgram);
	__boundingBoxProgram->GLSLiVec2Coords = gl->getAttribLocation(__boundingBoxProgram, "iVec2Coords");
	__boundingBoxProgram->GLSLuProjMat = gl->getUniformLocation(__boundingBoxProgram, "uProjMat");
	__boundingBoxBuffer = gl->createBuffer();
	gl->bindBuffer(gl->ARRAY_BUFFER, __boundingBoxBuffer);
	gl->bufferData(gl->ARRAY_BUFFER, new Float32Array({0, 0, 0, 0, 0, 0, 0, 0}), gl->DYNAMIC_DRAW);
	__glProgram = glu.makeProgram(gl, __vertex_shader, __fragment_shader);
	gl->useProgram(__glProgram);
	__glProgram->GLSLiVecCoords = gl->getAttribLocation(__glProgram, "iVecCoords");
	__glProgram->GLSLiTexCoords = gl->getAttribLocation(__glProgram, "iTexCoords");
	__glProgram->GLSLuProjMat = gl->getUniformLocation(__glProgram, "uProjMat");
	__glProgram->GLSLuMVMat = gl->getUniformLocation(__glProgram, "uMVMat");
	__glProgram->GLSLuSprSize = gl->getUniformLocation(__glProgram, "uSprSize");
	__glProgram->GLSLuSprFrame = gl->getUniformLocation(__glProgram, "uSprFrame");
	__glProgram->GLSLuSampler = gl->getUniformLocation(__glProgram, "uSampler");
	__glProgram->GLSLuColor = gl->getUniformLocation(__glProgram, "uColor");
	__modelViewMatrix = new CocoMatrix();
	__modelViewMatrix->update(gl, __glProgram->GLSLuMVMat);
	__view_scale = this->__view_width > 0 && this->__view_height > 0 ? std::min(gl->canvas.width / this->__view_width, gl->canvas.height / this->__view_height) : window.devicePixelRatio;
	__projectionMatrix = new CocoMatrix();
	__projectionMatrix->ortho( -gl->canvas.width / 2, gl->canvas.width / 2, gl->canvas.height / 2,  -gl->canvas.height / 2,  -1, 1);
	if(window.deviceRotation) { __projectionMatrix->rotateZ( -window.deviceRotation); }
	__projectionMatrix->scale(__view_scale, __view_scale);
	__projectionMatrix->update(gl, __glProgram->GLSLuProjMat);
	gl->enableVertexAttribArray(__glProgram->GLSLiTexCoords);
	gl->enableVertexAttribArray(__glProgram->GLSLiVecCoords);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::loadResources()
{
	std::string t;
	CocoImage* img;
	CocoImageSibling* sibling;
	for(int i = __imageSymbols.size() - 1; i >= 0; i--)
	{
		img = __imageSymbols[i];
		if(__view_width && __view_height)
		{
			float w = img->viewOptimalWidth * __view_scale * window.devicePixelRatio;
			float h = img->viewOptimalHeight * __view_scale * window.devicePixelRatio;
			int i;
			for(i = img->viewSiblings.size() - 1; i >= 0; i--)
			{
				sibling = img->viewSiblings[i];
				if(sibling->textureWidth >= w && sibling->textureHeight >= h)
				{
					img->image = new Image();
					img->image->src = img->baseUrl + sibling->url;
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
			img->image->src = img->baseUrl + sibling->url;
			img->textureCellWidth = sibling->textureWidth;
			img->textureCellHeight = sibling->textureHeight;
			img->pixelRatio = sibling->pixelRatio;
		}
		if(img->image)
		{
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoScene::resourcesLoaded(WebGLRenderingContext* gl)
{
	if(!__ready)
	{
		std::string t;
		CocoImage* img;
		for(t : __imageSymbols)
		{
			img = __imageSymbols[t];
			if(!img->image->width || !img->image->height)
			{
				return false;
			}
			else if(!img->texture)
			{
				img->prepare(gl);
			}
		}
	}
	return (__ready = true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::tick(WebGLRenderingContext* gl, float time)
{
	if(!__glProgram)
	{
		prepare(gl);
		loadResources(this);
	}
	else if(resourcesLoaded(gl))
	{
		gl->clearColor(1, 1, 1, 1);
		gl->clear(gl->COLOR_BUFFER_BIT);
		if(__startTime == -1) { __startTime = time; }
		__elapsedTime = time - __currentTime - __startTime;
		__currentTime = time - __startTime;
		if(__root)
		{
			__modelViewMatrix->identity();
			__levelParents = {__root};
			__root->render(gl, this, NULL, false);
			CocoClip* max = __root->__childWithMaxTimelineDuration;
			if(max && max->__currentFrame == max->__timeline->__lastKeyFrame)
			{
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::drawFrame(WebGLRenderingContext* gl, CocoImage* image, float frame, float alpha)
{
	image->color[3] = alpha;
	__modelViewMatrix->update(gl, __glProgram->GLSLuMVMat);
	gl->uniform2fv(__glProgram->GLSLuSprSize, image->texSize);
	gl->uniform2f(__glProgram->GLSLuSprFrame, image->textureGrid[frame * 2 + 1], image->textureGrid[frame * 2]);
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
bool CocoScene::gotoAndPlay(Object* LabelNameOrFrameIndex, bool deep)
{
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	return scope->gotoFrame(LabelNameOrFrameIndex, false, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoScene::gotoAndStop(Object* LabelNameOrFrameIndex, bool deep)
{
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	return scope->gotoFrame(LabelNameOrFrameIndex, true, deep);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoScene::stop(bool deep)
{
	deep = (deep == "true");
	CocoClip* scope = __levelParents[__levelParents.size() - 1];
	return scope->gotoFrame( -1, true, deep);
}
