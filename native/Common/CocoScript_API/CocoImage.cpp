#include "CocoImage.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage::CocoImage()
{
	image = NULL;
	symbolName = "";
	texture = NULL;
	textureCellWidth = 0;
	textureCellHeight = 0;
	textureGrid = new Float32Array({0, 0});
	color = new Float32Array({1, 1, 1, 1});
	texSize = new Float32Array({1, 1});
	buffer = NULL;
	isSpriteSheet = false;
	viewOptimalWidth = 0;
	viewOptimalHeight = 0;
	pixelRatio = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoImage::addSibling(CocoImageSibling* sibling)
{
	viewSiblings.push(sibling);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSequence* CocoImage::addSequence(CocoSequence* sequence)
{
	if(!sequence) { return NULL; }
	if(getSequence(sequence->name)) { throw CocoException("Cannot add sequence with same name!"); }
	sequences.push(sequence);
	isSpriteSheet = true;
	return sequence;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoSequence* CocoImage::getSequence(std::string name)
{
	for(int i = sequences.size() - 1; i >= 0; i--)
	{
		if(sequences[i]->name == name) { return sequences[i]; }
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoImage::prepare(WebGLRenderingContext* gl)
{
	float w2 = textureCellWidth / 2;
	float h2 = textureCellHeight / 2;
	texSize = new Float32Array({textureCellWidth / image->naturalWidth, textureCellHeight / image->naturalHeight});
	texture = gl->createTexture();
	gl->bindTexture(gl->TEXTURE_2D, texture);
	gl->texImage2D(gl->TEXTURE_2D, 0, gl->RGBA, gl->RGBA, gl->UNSIGNED_BYTE, image);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_WRAP_S, gl->CLAMP_TO_EDGE);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_WRAP_T, gl->CLAMP_TO_EDGE);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_MAG_FILTER, gl->LINEAR);
	gl->texParameteri(gl->TEXTURE_2D, gl->TEXTURE_MIN_FILTER, gl->LINEAR);
	gl->generateMipmap(gl->TEXTURE_2D);
	gl->bindTexture(gl->TEXTURE_2D, NULL);
	Float32Array* texData = new Float32Array({0, 0, -w2, -h2, 0, 1, -w2, h2, 1, 0, w2, -h2, 1, 1, w2, h2});
	buffer = gl->createBuffer();
	gl->bindBuffer(gl->ARRAY_BUFFER, buffer);
	gl->bufferData(gl->ARRAY_BUFFER, texData, gl->STATIC_DRAW);
	gl->bindBuffer(gl->ARRAY_BUFFER, NULL);
}
