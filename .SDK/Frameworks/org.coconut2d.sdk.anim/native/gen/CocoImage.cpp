#include "CocoImage.hpp"
#include "CocoImageSibling.hpp"
#include "CocoSequence.hpp"
#include "CocoScene.hpp"
#include "WebGLRenderingContext.hpp"
#include "HTMLImageElement.hpp"
#include "TypedArray.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage::CocoImage()
{
	viewSiblings = new Array<CocoImageSibling*> ();
	sequences = new Array<CocoSequence*> ();
	image = nullptr;
	symbolName = String("");
	texture = nullptr;
	textureCellWidth = 0;
	textureCellHeight = 0;
	textureGrid = new Float32Array((new Array<float> ())->push(0.0));
	textureGrid = new Float32Array((new Array<float> ())->push(0.0)->push(0.0));
	color = new Float32Array((new Array<float> ())->push(1.0)->push(1.0)->push(1.0)->push(1.0));
	texSize = new Float32Array((new Array<float> ())->push(1.0)->push(1.0));
	buffer = nullptr;
	isSpriteSheet = false;
	baseUrl = String("");
	viewOptimalWidth = 0;
	viewOptimalHeight = 0;
	pixelRatio = 1.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage::~CocoImage()
{
	if(viewSiblings)
	{
		viewSiblings = (delete viewSiblings, nullptr);
	}
	if(sequences)
	{
		sequences = (delete sequences, nullptr);
	}
	if(texture)
	{
		texture = (delete texture, nullptr);
	}
	if(textureGrid)
	{
		textureGrid = (delete textureGrid, nullptr);
	}
	if(color)
	{
		color = (delete color, nullptr);
	}
	if(texSize)
	{
		texSize = (delete texSize, nullptr);
	}
	if(buffer)
	{
		buffer = (delete buffer, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImageSibling* CocoImage::addSibling(CocoImageSibling* sibling)
{
	viewSiblings->push(sibling);
	return sibling;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSequence* CocoImage::addSequence(CocoSequence* sequence)
{
	if(!sequence)
	{
		return nullptr;
	}
	if(getSequence(sequence->name))
	{
		throw CocoException(String("Sequence ") + sequence->name + String(" already exists."));
	}
	sequences->push(sequence);
	isSpriteSheet = true;
	return sequence;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSequence* CocoImage::getSequence(String name)
{
	for(int i = sequences->size() - 1; i >= 0; i--)
	{
		if((*sequences)[i]->name == name)
		{
			return (*sequences)[i];
		}
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoImage::prepare(CocoScene* scene, WebGLRenderingContext* gl)
{
	__pixelRatioScale = (float)(scene->__view_pixel_ratio) / (float)(pixelRatio);
	float w2 = (float)(textureCellWidth) / (float)(2.0);
	float h2 = (float)(textureCellHeight) / (float)(2.0);
	texSize = new Float32Array((new Array<float> ())->push((float)(textureCellWidth) / (float)(image->naturalWidth))->push((float)(textureCellHeight) / (float)(image->naturalHeight)));
	texture = gl->createTexture();
	gl->bindTexture(gl->TEXTURE_2D, texture);
	gl->texImage2D(gl->TEXTURE_2D, 0, gl->RGBA, gl->RGBA, gl->UNSIGNED_BYTE, image);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_WRAP_S, gl->CLAMP_TO_EDGE);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_WRAP_T, gl->CLAMP_TO_EDGE);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_MAG_FILTER, gl->LINEAR);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_MIN_FILTER, gl->LINEAR_MIPMAP_NEAREST);
	gl->generateMipmap(gl->TEXTURE_2D);
	gl->bindTexture(gl->TEXTURE_2D, nullptr);
	Float32Array* texData = new Float32Array((new Array<float> ())->push(0.0)->push(0.0)->push(-w2)->push(-h2)->push(0.0)->push(1.0)->push(-w2)->push(h2)->push(1.0)->push(0.0)->push(w2)->push(-h2)->push(1.0)->push(1.0)->push(w2)->push(h2));
	buffer = gl->createBuffer();
	gl->bindBuffer(gl->ARRAY_BUFFER, buffer);
	gl->bufferData(gl->ARRAY_BUFFER, texData, gl->STATIC_DRAW);
	gl->bindBuffer(gl->ARRAY_BUFFER, nullptr);
}
