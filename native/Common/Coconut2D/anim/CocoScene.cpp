#include "CocoScene.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoScene::CocoScene()
{
	__sceneName = "";
	__view_width = 0;
	__view_height = 0;
	__view_pixel_ratio = 0;
	__view_scale = 1;
	__root = nullptr;
	__modelViewMatrix = new CocoMatrix();
	__projectionMatrix = new CocoMatrix();
	__glProgram = nullptr;
	__glProgram_Simple = nullptr;
	__glProgram_SimpleWithAlpha = nullptr;
	__glProgram_SaturationWithAlpha = nullptr;
	__vertex_shader_Common = "attribute vec2 iVecCoords;attribute vec2 iTexCoords;uniform mat4 uProjMat;uniform mat4 uMVMat;uniform vec2 uSprSize;uniform vec2 uSprFrame;uniform vec2 uSprFlip;varying vec2 pTexCoord;void main(void){ gl_Position = uProjMat * uMVMat * vec4(iVecCoords, 0.0, 1.0); pTexCoord = vec2(((abs(iTexCoords.x - uSprFlip.x) + uSprFrame.x) * uSprSize.x), ((abs(iTexCoords.y - uSprFlip.y) + uSprFrame.y) * uSprSize.y));}";
	__fragment_shader_Simple = "#ifdef GL_ES\nprecision lowp float;\n#endif\nuniform sampler2D uSampler;\nvarying vec2 pTexCoord; \n \nvoid main(void)\n{\n gl_FragColor = texture2D(uSampler, pTexCoord); }";
	__fragment_shader_SimpleWithAlpha = "#ifdef GL_ES\nprecision lowp float;\n#endif\nuniform sampler2D uSampler;\nuniform float uAlpha;\nvarying vec2 pTexCoord; \n \nvoid main(void)\n{\n vec4 texColor = texture2D(uSampler, pTexCoord);\n gl_FragColor = vec4(texColor.rgb, texColor.a * uAlpha); }";
	__fragment_shader_SaturationWithAlpha = "#ifdef GL_ES\nprecision lowp float;\n#endif\nuniform sampler2D uSampler;\nuniform vec4 uColor;\nvarying vec2 pTexCoord; \n \nvoid main(void)\n{\n vec4 texColor = texture2D(uSampler, pTexCoord);\n float c = (texColor.r + texColor.g + texColor.b) / 3.0; \n gl_FragColor = vec4((1.0 - uColor.r) * c + texColor.r * uColor.r, (1.0 - uColor.g) * c + texColor.g * uColor.g, (1.0 - uColor.b) * c + texColor.b * uColor.b, texColor.a * uColor.a);}";
	__boundingBoxVertexShader = "attribute vec2 iVec2Coords;uniform mat4 uProjMat;void main(void){ gl_Position = uProjMat * vec4(iVec2Coords, 0.0, 1.0);}";
	__boundingBoxFragmentShader = "#ifdef GL_ES\nprecision lowp float;\n#endif\nvoid main(void){ gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);}";
	__boundingBoxProgram = nullptr;
	__boundingBoxBuffer = nullptr;
	__ready = false;
	__finished = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoScene::~CocoScene()
{
	if(__root)
	{
		__root = (delete __root, nullptr);
	}
	if(__modelViewMatrix)
	{
		__modelViewMatrix = (delete __modelViewMatrix, nullptr);
	}
	if(__projectionMatrix)
	{
		__projectionMatrix = (delete __projectionMatrix, nullptr);
	}
	if(__glProgram_Simple)
	{
		__glProgram_Simple = (delete __glProgram_Simple, nullptr);
	}
	if(__glProgram_SimpleWithAlpha)
	{
		__glProgram_SimpleWithAlpha = (delete __glProgram_SimpleWithAlpha, nullptr);
	}
	if(__glProgram_SaturationWithAlpha)
	{
		__glProgram_SaturationWithAlpha = (delete __glProgram_SaturationWithAlpha, nullptr);
	}
	if(__boundingBoxProgram)
	{
		__boundingBoxProgram = (delete __boundingBoxProgram, nullptr);
	}
	if(__boundingBoxBuffer)
	{
		__boundingBoxBuffer = (delete __boundingBoxBuffer, nullptr);
	}
	for(int i = __imageSymbols.size(); i--;)
	{
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::getImageSymbol(String symbolName)
{
	for(int i = __imageSymbols.size() - 1; i >= 0; i--)
	{
		if(__imageSymbols[i]->symbolName == symbolName)
		{
			return __imageSymbols[i];
		}
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::newResourceImage(String symbolName, String baseUrl)
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
void CocoScene::prepare(WebGLRenderingContext* gl)
{
	gl->disable(gl->DEPTH_TEST);
	gl->enable(gl->BLEND);
	gl->blendFunc(gl->SRC_ALPHA, gl->ONE_MINUS_SRC_ALPHA);
	gl->disable(gl->CULL_FACE);
	__view_scale = this->__view_width > 0 && this->__view_height > 0 ? std::min((float)(((float)gl->canvas->width)) / (float)(this->__view_width), (float)(((float)gl->canvas->height)) / (float)(this->__view_height)) : window->devicePixelRatio;
	if(window->deviceRotation)
	{
		float c = cos(window->deviceRotation);
		float s = sin(window->deviceRotation);
		float orthoWidth = abs(c * ((float)gl->canvas->width) + s * ((float)gl->canvas->height));
		float orthoHeight = abs(-s * ((float)gl->canvas->width) + c * ((float)gl->canvas->height));
		__projectionMatrix->ortho((float)(-orthoWidth) / (float)(2.0), (float)(orthoWidth) / (float)(2.0), (float)(orthoHeight) / (float)(2.0), (float)(-orthoHeight) / (float)(2.0),  -1.0, 1.0);
		__projectionMatrix->rotateZ(-window->deviceRotation);
	}
	else
	{
		__projectionMatrix->ortho(-((float)(((float)gl->canvas->width)) / (float)(2.0)), (float)(((float)gl->canvas->width)) / (float)(2.0), (float)(((float)gl->canvas->height)) / (float)(2.0),  -((float)(((float)gl->canvas->height)) / (float)(2.0)),  -1.0, 1.0);
	}
	__projectionMatrix->scale(__view_scale, __view_scale);
	__boundingBoxProgram = makeProgram(gl, __boundingBoxVertexShader, __boundingBoxFragmentShader);
	gl->useProgram(__boundingBoxProgram);
	__boundingBoxProgram->GLSLiVec2Coords = gl->getAttribLocation(__boundingBoxProgram, "iVec2Coords");
	__boundingBoxProgram->GLSLuProjMat = gl->getUniformLocation(__boundingBoxProgram, "uProjMat");
	__boundingBoxBuffer = gl->createBuffer();
	gl->bindBuffer(gl->ARRAY_BUFFER, __boundingBoxBuffer);
	gl->bufferData(gl->ARRAY_BUFFER, new Float32Array(Array<float> ()(0.0)(0.0)(0.0)(0.0)(0.0)(0.0)(0.0)(0.0)), gl->DYNAMIC_DRAW);
	__glProgram_Simple = makeProgram(gl, __vertex_shader_Common, __fragment_shader_Simple);
	gl->useProgram(__glProgram_Simple);
	__glProgram_Simple->GLSLiVecCoords = gl->getAttribLocation(__glProgram_Simple, "iVecCoords");
	__glProgram_Simple->GLSLiTexCoords = gl->getAttribLocation(__glProgram_Simple, "iTexCoords");
	__glProgram_Simple->GLSLuProjMat = gl->getUniformLocation(__glProgram_Simple, "uProjMat");
	__glProgram_Simple->GLSLuMVMat = gl->getUniformLocation(__glProgram_Simple, "uMVMat");
	__glProgram_Simple->GLSLuSprSize = gl->getUniformLocation(__glProgram_Simple, "uSprSize");
	__glProgram_Simple->GLSLuSprFrame = gl->getUniformLocation(__glProgram_Simple, "uSprFrame");
	__glProgram_Simple->GLSLuSprFlip = gl->getUniformLocation(__glProgram_Simple, "uSprFlip");
	__glProgram_Simple->GLSLuSampler = gl->getUniformLocation(__glProgram_Simple, "uSampler");
	gl->enableVertexAttribArray(__glProgram_Simple->GLSLiVecCoords);
	gl->enableVertexAttribArray(__glProgram_Simple->GLSLiTexCoords);
	gl->uniform1i(__glProgram_Simple->GLSLuSampler, 0);
	__modelViewMatrix->update(gl, __glProgram_Simple->GLSLuMVMat);
	__projectionMatrix->update(gl, __glProgram_Simple->GLSLuProjMat);
	__glProgram_SimpleWithAlpha = makeProgram(gl, __vertex_shader_Common, __fragment_shader_SimpleWithAlpha);
	gl->useProgram(__glProgram_SimpleWithAlpha);
	__glProgram_SimpleWithAlpha->GLSLiVecCoords = gl->getAttribLocation(__glProgram_SimpleWithAlpha, "iVecCoords");
	__glProgram_SimpleWithAlpha->GLSLiTexCoords = gl->getAttribLocation(__glProgram_SimpleWithAlpha, "iTexCoords");
	__glProgram_SimpleWithAlpha->GLSLuProjMat = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uProjMat");
	__glProgram_SimpleWithAlpha->GLSLuMVMat = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uMVMat");
	__glProgram_SimpleWithAlpha->GLSLuSprSize = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uSprSize");
	__glProgram_SimpleWithAlpha->GLSLuSprFrame = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uSprFrame");
	__glProgram_SimpleWithAlpha->GLSLuSprFlip = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uSprFlip");
	__glProgram_SimpleWithAlpha->GLSLuSampler = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uSampler");
	__glProgram_SimpleWithAlpha->GLSLuAlpha = gl->getUniformLocation(__glProgram_SimpleWithAlpha, "uAlpha");
	gl->enableVertexAttribArray(__glProgram_SimpleWithAlpha->GLSLiVecCoords);
	gl->enableVertexAttribArray(__glProgram_SimpleWithAlpha->GLSLiTexCoords);
	gl->uniform1i(__glProgram_SimpleWithAlpha->GLSLuSampler, 0);
	__modelViewMatrix->update(gl, __glProgram_SimpleWithAlpha->GLSLuMVMat);
	__projectionMatrix->update(gl, __glProgram_SimpleWithAlpha->GLSLuProjMat);
	__glProgram_SaturationWithAlpha = makeProgram(gl, __vertex_shader_Common, __fragment_shader_SaturationWithAlpha);
	gl->useProgram(__glProgram_SaturationWithAlpha);
	__glProgram_SaturationWithAlpha->GLSLiVecCoords = gl->getAttribLocation(__glProgram_SaturationWithAlpha, "iVecCoords");
	__glProgram_SaturationWithAlpha->GLSLiTexCoords = gl->getAttribLocation(__glProgram_SaturationWithAlpha, "iTexCoords");
	__glProgram_SaturationWithAlpha->GLSLuProjMat = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uProjMat");
	__glProgram_SaturationWithAlpha->GLSLuMVMat = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uMVMat");
	__glProgram_SaturationWithAlpha->GLSLuSprSize = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uSprSize");
	__glProgram_SaturationWithAlpha->GLSLuSprFrame = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uSprFrame");
	__glProgram_SaturationWithAlpha->GLSLuSprFlip = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uSprFlip");
	__glProgram_SaturationWithAlpha->GLSLuSampler = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uSampler");
	__glProgram_SaturationWithAlpha->GLSLuColor = gl->getUniformLocation(__glProgram_SaturationWithAlpha, "uColor");
	gl->enableVertexAttribArray(__glProgram_SaturationWithAlpha->GLSLiVecCoords);
	gl->enableVertexAttribArray(__glProgram_SaturationWithAlpha->GLSLiTexCoords);
	gl->uniform1i(__glProgram_SaturationWithAlpha->GLSLuSampler, 0);
	__modelViewMatrix->update(gl, __glProgram_SaturationWithAlpha->GLSLuMVMat);
	__projectionMatrix->update(gl, __glProgram_SaturationWithAlpha->GLSLuProjMat);
	__glProgram = __glProgram_Simple;
	gl->useProgram(__glProgram);
	__root->prepare(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLProgram* CocoScene::makeProgram(WebGLRenderingContext* gl, String vs, String fs)
{
	WebGLShader* vshader = gl->createShader(gl->VERTEX_SHADER);
	WebGLShader* fshader = gl->createShader(gl->FRAGMENT_SHADER);
	gl->shaderSource(vshader, vs);
	gl->shaderSource(fshader, fs);
	gl->compileShader(vshader);
	gl->compileShader(fshader);
	WebGLProgram* program = gl->createProgram();
	gl->attachShader(program, vshader);
	gl->attachShader(program, fshader);
	gl->linkProgram(program);
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
				img->prepare(this, gl);
				return false;
			}
		}
		__ready = true;
		trace("Resources loaded.");
		return false;
	}
	return __ready;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::paint(WebGLRenderingContext* gl, Time time)
{
	if(!__glProgram)
	{
		prepare(gl);
		loadResources();
	}
	else if(resourcesLoaded(gl))
	{
		if(__root)
		{
			engine->__trace(this, nullptr, "@CYCLE");
			__modelViewMatrix->identity();
			__levelParents = Array<CocoClip*> ()(__root);
			__root->paint(gl, this, nullptr, false, 0);
			CocoClip* max = __root->__childWithMaxTimelineDuration;
			if(max && max->__currentFrame && max->__currentFrame->frameIndex == max->__timeline->lastKeyFrame()->frameIndex)
			{
				__finished = true;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoScene::setFilter(int filter)
{
	bool changed = false;
	switch(filter)
	{
		case COCO_FILTER_ENUM::FILTER_INHERIT:
		{
			if(__glProgram != __glProgram_Simple)
			{
				__glProgram = __glProgram_Simple;
				changed = true;
			}
			break;
		}
		break;
		case COCO_FILTER_ENUM::FILTER_SIMPLE:
		{
			if(__glProgram != __glProgram_Simple)
			{
				__glProgram = __glProgram_Simple;
				changed = true;
			}
			break;
		}
		break;
		case COCO_FILTER_ENUM::FILTER_SIMPLE_WITH_ALPHA:
		{
			if(__glProgram != __glProgram_SimpleWithAlpha)
			{
				__glProgram = __glProgram_SimpleWithAlpha;
				changed = true;
			}
			break;
		}
		break;
		case COCO_FILTER_ENUM::FILTER_SATURATION_WITH_ALPHA:
		{
			if(__glProgram != __glProgram_SaturationWithAlpha)
			{
				__glProgram = __glProgram_SaturationWithAlpha;
				changed = true;
			}
			break;
		}
		break;
	}
	if(changed)
	{
		gl->useProgram(__glProgram);
	}
	return changed;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::drawFrame(WebGLRenderingContext* gl, CocoImage* image, int frame, CocoKeyFrame* KF)
{
	if(setFilter(KF->filter) || __modelViewMatrix->__dirty)
	{
		__modelViewMatrix->update(gl, __glProgram->GLSLuMVMat);
	}
	gl->uniform2f(__glProgram->GLSLuSprSize, (*image->texSize)[0], (*image->texSize)[1]);
	gl->uniform2f(__glProgram->GLSLuSprFrame, (*image->textureGrid)[frame * 2 + 1], (*image->textureGrid)[frame * 2]);
	gl->uniform2f(__glProgram->GLSLuSprFlip, (KF->flipH ? 1.0 : 0.0), (KF->flipV ? 1.0 : 0.0));
	gl->bindBuffer(gl->ARRAY_BUFFER, image->buffer);
	gl->vertexAttribPointer(__glProgram->GLSLiTexCoords, 2, gl->FLOAT, false, 16, 0);
	gl->vertexAttribPointer(__glProgram->GLSLiVecCoords, 2, gl->FLOAT, false, 16, 8);
	gl->bindTexture(gl->TEXTURE_2D, image->texture);
	switch(KF->filter)
	{
		case COCO_FILTER_ENUM::FILTER_INHERIT:
		{
		}
		break;
		case COCO_FILTER_ENUM::FILTER_SIMPLE:
		{
			break;
		}
		break;
		case COCO_FILTER_ENUM::FILTER_SIMPLE_WITH_ALPHA:
		{
			gl->uniform1f(__glProgram->GLSLuAlpha, KF->alpha);
			break;
		}
		break;
		case COCO_FILTER_ENUM::FILTER_SATURATION_WITH_ALPHA:
		{
			gl->uniform4f(__glProgram->GLSLuColor, KF->red, KF->green, KF->blue, KF->alpha);
			break;
		}
		break;
	}
	gl->drawArrays(gl->TRIANGLE_STRIP, 0, 4);
	gl->bindBuffer(gl->ARRAY_BUFFER, nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndPlayByName(String LabelName)
{
	CocoClip* scope = __levelParents.size() == 0 ? __root : __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByName(LabelName, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndStopByName(String LabelName)
{
	CocoClip* scope = __levelParents.size() == 0 ? __root : __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByName(LabelName, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndPlayByIndex(int FrameIndex)
{
	CocoClip* scope = __levelParents.size() == 0 ? __root : __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByIndex(FrameIndex, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndStopyByIndex(int FrameIndex)
{
	CocoClip* scope = __levelParents.size() == 0 ? __root : __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByIndex(FrameIndex, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::stop()
{
	CocoClip* scope = __levelParents.size() == 0 ? __root : __levelParents[__levelParents.size() - 1];
	scope->gotoFrameByIndex(COCO_STOP_ON_CURRENT_FRAME, true);
}
