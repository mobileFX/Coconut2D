#include "HTMLCanvasElement.hpp"
#include "HTMLCanvasContext.hpp"
#include "CanvasRenderingContext2D.hpp"
#include "WebGLRenderingContext.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasElement::HTMLCanvasElement()
{
	width = 0.0;
	height = 0.0;
	__imageData = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasElement::~HTMLCanvasElement()
{
	if(__imageData)
	{
		__imageData = (delete __imageData, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
HTMLCanvasContext* HTMLCanvasElement::getContext(String contextId)
{
	if(contextId == String("2d"))
	{
		return new CanvasRenderingContext2D(this);
	}
	else
	{
		return ((HTMLCanvasContext*)new WebGLRenderingContext(this));
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
String HTMLCanvasElement::toDataURL()
{
	return String("data:image/png;base64,") + (__imageData ? __imageData->data->buffer->encodeAsPNG(__imageData->width, __imageData->height)->encodeAsBase64() : String("iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAALUlEQVRYR+3QQREAAAABQfqXFsNnFTizzXk99+MAAQIECBAgQIAAAQIECBAgMBo/ACHo7lH9AAAAAElFTkSuQmCC"));
}
