/* Generated by Coconut2D C++ Compiler from file CocoScene.jspp */

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CocoScene.hpp"
#include "CocoImage.hpp"
#include "CocoClip.hpp"
#include "ICocoRenderContext.hpp"
#include "HTMLWindow.hpp"
#include "CocoTimeline.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoScene::CocoScene()
{
	__sceneName = String("");
	__view_width = 0;
	__view_height = 0;
	__view_pixel_ratio = 0;
	__view_scale = 1;
	__root = nullptr;
	__ready = false;
	__finished = false;
	__imageSymbols = new Array<CocoImage*> ();
	__levelParents = new Array<CocoClip*> ();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoScene::~CocoScene()
{
	if(__root)
	{
		__root = (delete __root, nullptr);
	}
	for(int i = __imageSymbols->size(); i--;)
	{
	}
	if(__imageSymbols)
	{
		__imageSymbols = (delete __imageSymbols, nullptr);
	}
	if(__levelParents)
	{
		__levelParents = (delete __levelParents, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::getImageSymbol(String symbolName)
{
	for(int i = __imageSymbols->size() - 1; i >= 0; i--)
	{
		if((*__imageSymbols)[i]->symbolName == symbolName)
		{
			return (*__imageSymbols)[i];
		}
	}
	return nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoImage* CocoScene::newResourceImage(String symbolName, String baseUrl)
{
	if(getImageSymbol(symbolName))
	{
		throw CocoException(String("Resource image ") + symbolName + String(" already exists."));
	}
	CocoImage* img = new CocoImage();
	img->symbolName = symbolName;
	img->baseUrl = baseUrl;
	img->scene = this;
	__imageSymbols->push(img);
	return img;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::prepare(ICocoRenderContext* ctx)
{
	__view_scale = __view_width > 0 && __view_height > 0 ? std::min((float)(((float)ctx->getWidth())) / (float)(__view_width), (float)(((float)ctx->getHeight())) / (float)(__view_height)) : window->devicePixelRatio;
	__root->prepare(this);
	int L = __imageSymbols->size();
	for(int i = 0; i < L; i++)
	{
		(*__imageSymbols)[i]->load();
	}
	ctx->prepare(this);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::paint(ICocoRenderContext* ctx, float time)
{
	if(!resourcesLoaded(ctx))
	{
		return;
	}
	if(__root)
	{
		__levelParents->push(__root);
		__root->paint(ctx, this, nullptr, false, 0);
		__levelParents->clear();
		CocoClip* max = __root->__childWithMaxTimelineDuration;
		if(max && max->__currentFrame && max->__currentFrame->frameIndex == max->__timeline->lastKeyFrame()->frameIndex)
		{
			__finished = true;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CocoScene::resourcesLoaded(ICocoRenderContext* ctx)
{
	if(!__ready)
	{
		for(int i = __imageSymbols->size() - 1; i >= 0; i--)
		{
			CocoImage* img = (*__imageSymbols)[i];
			if(!img->loaded())
			{
				return false;
			}
		}
		trace((String("Resources loaded.")).c_str());
		__ready = true;
	}
	return __ready;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndPlayByName(String LabelName)
{
	CocoClip* scope = __levelParents->size() == 0 ? __root : (*__levelParents)[__levelParents->size() - 1];
	scope->gotoFrameByName(LabelName, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndStopByName(String LabelName)
{
	CocoClip* scope = __levelParents->size() == 0 ? __root : (*__levelParents)[__levelParents->size() - 1];
	scope->gotoFrameByName(LabelName, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndPlayByIndex(int FrameIndex)
{
	CocoClip* scope = __levelParents->size() == 0 ? __root : (*__levelParents)[__levelParents->size() - 1];
	scope->gotoFrameByIndex(FrameIndex, false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::gotoAndStopyByIndex(int FrameIndex)
{
	CocoClip* scope = __levelParents->size() == 0 ? __root : (*__levelParents)[__levelParents->size() - 1];
	scope->gotoFrameByIndex(FrameIndex, true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoScene::stop()
{
	CocoClip* scope = __levelParents->size() == 0 ? __root : (*__levelParents)[__levelParents->size() - 1];
	scope->gotoFrameByIndex(COCO_STOP_ON_CURRENT_FRAME, true);
}
