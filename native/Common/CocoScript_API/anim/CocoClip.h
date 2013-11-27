/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __CocoEngine__CocoClip__
#define __CocoEngine__CocoClip__

#include "Coconut2D.h"
#include "CocoMatrix.h"
#include "CocoImage.h"
#include "CocoSound.h"
#include "CocoTimeline.h"

// ==================================================================================================================================
//	   ______                 _________     
//	  / ____/___  _________  / ____/ (_)___ 
//	 / /   / __ \/ ___/ __ \/ /   / / / __ \
//	/ /___/ /_/ / /__/ /_/ / /___/ / / /_/ /
//	\____/\____/\___/\____/\____/_/_/ .___/ 
//	                               /_/      
// ==================================================================================================================================

class CocoClip
{
public:
    String __instanceName;
    CocoImage* __image;
	CocoImage* __mask;
    CocoSound* __sound;
    COCO_CLIP_SYMBOL_LOOP_ENUM __symbolLoop;
    Number __childrenCount;
	Dictionary<CocoClip> __children;
	Array<CocoClip> __childrenOrdered;
    String __currentSequenceName;
    Number __currentSequenceFrameIndex;
    CocoTimeline* __timeline;
    CocoClip* __parent;

    Number __firstTickTime;
    CocoKeyFrame* __currentFrame;

    Boolean __hasBoundingBox;
    CocoVector* __vTOP_LEFT;
    CocoVector* __vTOP_RIGHT;
    CocoVector* __vBOTTOM_LEFT;
    CocoVector* __vBOTTOM_RIGHT;

    CocoClip(CocoImage* image, CocoSound* audio, String sequence, CocoImage* mask)
	{
		__instanceName				= NULL;
		__image						= image;
		__mask						= mask;
		__audio						= audio;
		__symbolLoop				= COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_CONTINUOUS;
		__childrenCount				= 0;	
		__currentSequenceName		= sequence;
		__currentSequenceFrameIndex	= 0;
		__timeline					= new CocoTimeLine();
		__parent					= NULL;

		__firstTickTime				= -1;
		__currentFrame				= NULL;	
		
		__hasBoundingBox			= false;	
		__vTOP_LEFT					= new CocoVector();
		__vTOP_RIGHT				= new CocoVector();
		__vBOTTOM_LEFT				= new CocoVector();
		__vBOTTOM_RIGHT				= new CocoVector();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	Array<CocoClip> children()
	{
		return __childrenOrdered;
	}  
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Number childrenMaxFrameIndex()
	{
		Number T = 0;
		for(auto vClip : __children)
		{
			T = max(T, vClip.second->__timeline->__lastframeIndex);
		}
		return T;    	    
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CocoClip* childWithMaxTimelineDuration()
	{
		CocoClip* ret = NULL;
		Number T = 0;
		for(auto vClip : __children)
		{
			if(T < vClip.second->__timeline->__lastframeIndex)
			{
				ret = vClip.second;
				T = ret->__timeline->__lastframeIndex);
			}
		}
		return ret;
	}
		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void reset()
	{
		__currentFrame = NULL;
	    __firstTickTime = -1;
	    __timeline->reset();
	    
	    for(auto vClip : __children)
		{
			vClip.second->reset();
	    }	    
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	CocoClip* addChild(CocoClip* clipInstance) throw(std::string)
	{
	    if(!clipInstance) return NULL;
	    if(!clipInstance->__instanceName) throw(std::string("Invalid instance name."));
	    if(__children.find(clipInstance->__instanceName) != __children.end()) throw(std::string("Instance ") + clipInstance.__instanceName + " already exists.");
	    __children[clipInstance->__instanceName] = clipInstance;
		__childrenOrdered.push_back(clipInstance);
	    __childrenCount++;
	    return clipInstance;	
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CocoClip* removeChild(CocoClip* clipInstance)
	{
		if(!clipInstance) return NULL;
	    if(clipInstance->__instanceName.empty()) throw(std::string("Invalid instance name."));
	    if(__children.find(clipInstance->__instanceName) != __children.end()) throw(std::string("Instance ") + clipInstance.__instanceName + " already exists.");
		__children.erase(clipInstance->__instanceName);
		for(int i = __childrenOrdered.size(); i--;)
		{
			if(__childrenOrdered[i]->__instanceName == clipInstance->__instanceName)
			{
				__childrenOrdered.erase(i);
				break;
			}
		}
	    __childrenCount--;
	    return clipInstance;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CocoClip* getChildByName(String instanceName)
	{    
		auto ret = __children.find(instanceName);
		if(ret == __children.end()) return NULL;
		return ret->second;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	CocoClip* getChildByIndex(Number index)
	{        
		if(!(index >= 0 && index < __childrenCount)) return NULL;
		return __childrenOrdered[index];
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Number getChildIndex(CocoClip* child)
	{
	    if(child && !clip->__instanceName.empty())
	    	for(int i = __childrenOrdered.size(); i--;)
				if(__childrenOrdered[i]->__instanceName == clip->__instanceName)
					return i;
		return -1;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Boolean isParentOf(CocoClip* child)
	{
	    if(!child || child->__instanceName.empty()) return false;
	    
	    if(__children[child.__instanceName]) 
	        return true;        
	    
		for(auto vClip : __children)
			if(vClip.second->isParentOf(child))
				return true;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Boolean moveChildToIndex(CocoClip* child, Number newIndex)
	{  
		if(newIndex < 0) return false;
	    if(newIndex > __childrenCount) return false;
	    
	    Number oldIndex = getChildIndex(child);
	    if(oldIndex == newIndex) return false;
	    
		if(oldIndex == -1) __children[child->__instanceName] = child;
		else __childrenOrdered.erase(__childrenOrdered.begin() + oldIndex);

		__childrenOrdered.insert(__childrenOrdered.begin() + newIndex, child);
	    return true;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Boolean gotoFrame(String LabelName, Boolean pause, Boolean deep)
	{
		CocoTimeLabel* Label = __timeline->findLabelByName(LabelName);
		if(!Label) return false;
		FrameIndex = Label->frameIndex;
		return gotoFrame(FrameIndex, pause, deep);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	Boolean gotoFrame(Number FrameIndex, Boolean pause, Boolean deep)
	{
		// Loop on children to jump timeline head to desired position.
		for(auto vClip : __children)
		{
			if(FrameIndex == COCO_STOP_ON_CURRENT_FRAME)
			{
				// Special case to stop on current frame.
				vClip.second->__timeline->jumpBy(0, pause);
			}
			else
			{
				// Calculate difference between current frame and jump frame.
				Number frames = (FrameIndex - vClip.second->__currentFrame->frameIndex);
				vClip.second->__timeline->jumpBy(frames, pause);
			}

			// Deep works for stopping / resuming children with no timeline jumping.
			// Otherwise if you need time adjustment for childrent, use the API.
			if(deep)
			{
				vClip.second->gotoFrame(COCO_STOP_ON_CURRENT_FRAME, pause, deep);
			}	
		}		
		return true;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void render(WebGLRenderingContext* gl, CocoScene* scene, CocoClip* parentClip, Boolean picking)
	{        
		// Get scene current time and add timeline skipTime (used in timeline jumps such as stop(), gotoAndPlay(), gotoAndStop() )		                                    
		Number currentTime = scene->__currentTime + __timeline->__skipTime; 

		// Keep track of first tick time.		
		if(__firstTickTime == -1) __firstTickTime = currentTime;//scene.__currentTime;		
		
		// Calculate the parent timeline duraction in time from its children.
		// Note: the parent timeline might have only one KeyFrame but the actual length is defined by the max timeline size of each children.		
		Number parentClipsDuration = (parentClip ? parentClip->childWithMaxTimelineDuration()->__timeline->__durationInTime : __timeline->__durationInTime);
		
		// Calculate this clip's LoopTime which is the projection of this clip's timeline to its parent's timeline.
		Number clippingTime = floor((currentTime - __firstTickTime) / parentClipsDuration) * parentClipsDuration;
		
		// Adjust LoopTime start.
		Number loopTime = (currentTime - __firstTickTime) - clippingTime;					
		
        // Take into account time sync between this clip and its parent.
		switch(__symbolLoop)
		{
		case COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_CONTINUOUS:
			    __currentFrame = __timeline->interpolateByTime(loopTime);
				break;     
				
		case COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_SYNCHRONIZED_WITH_PARENT:
			    __currentFrame = __timeline->interpolateByTime(loopTime); // TODO
				break; 
				
		case COCO_CLIP_SYMBOL_LOOP_ENUM::CLIP_SYMBOL_LOOP_ONCE:
			    if(clippingTime > 0) 
			    	__currentFrame = __timeline->__lastKeyFrame.clone();
			    else
			    	__currentFrame = __timeline->interpolateByTime(loopTime); 
				break;
		}
		
		// Combine parent clip currentframe values with this clip's interpolated frame values.
		if(parentClip)                                      
		{
			 __currentFrame->combine(parentClip->__currentFrame);
			
			// If a child handles events and requires a bounding box calculation 
			// then the entire parent-child chain needs to calculate bounding box.
			if(__currentFrame->calcBoundingBox) 
				parentClip->__currentFrame->calcBoundingBox = true;
		}
			
		// If current frame is visible, render this clip and its children.
		if(__currentFrame->alpha != 0 && __currentFrame->visible)
		{			
			// Apply this clip's current frame values to modelview matrix.
			__currentFrame->apply(scene->__modelViewMatrix);			

			if(__image)
			{								
				// If this clip is a primitive (low-level clip with an image) then render the image.				
				if(__image->isSpriteSheet()) 
				{   
					// If the image is Spritesheet then render its current Animation Sequence.					
					if(!__currentSequenceName && !__image->sequences.empty()) 
						__currentSequenceName = __image->sequences.begin()->second;

					CocoSequence* seq = __image->sequences[__currentSequenceName];				
					__currentSequenceFrameIndex = __timeline->__paused ? 0 : floor(((currentTime - __firstTickTime) / GLOBAL_FPS)) % seq->frames.size();
					Number frame = seq->frames[__currentSequenceFrameIndex];					
					scene->drawFrame(gl, __image, frame, __currentFrame->alpha);					
				} 
				else
				{
					// Render a standard image.					
					scene->drawFrame(gl, __image, 0,  __currentFrame->alpha);	
				}			
			} 
			else
			{			
				// Render Children			    
				scene->__levelParents.push(this);
				for(auto c : __children)
				{	
					scene->__modelViewMatrix->push();
					c.second->ci.render(gl, scene, this, picking);
					scene->__modelViewMatrix->pop();			
				} 
				scene->__levelParents.pop();
			} 
			
			// Handle touch event 
			/*
			if(engine.__touchEvent && this!=scene.__root && __currentFrame.calcBoundingBox)
			{
				// Calculate bounding box vertices
				if(__image)		                                               
					initBoundingBoxFromTexture(scene, __image.textureCellWidth / 2, __image.textureCellHeight / 2);
				else if(__childrenCount>0)		
					initBoundingBoxFromChildren(scene);			
					
				// Draw bounds (debug)
				if(!__image)   
				{
					drawBoundingBox(scene, gl);  
				}
					
				// Point in quad?			
				if(engine.__touchEvent)
				{
		   	        var x = (engine.__touchEvent.clientX - gl.canvas.width / 2.0) / scene.__view_scale;
					var y = (engine.__touchEvent.clientY - gl.canvas.height / 2.0) / scene.__view_scale; 			
					if(engine.__touchEvent && hitTest(x,y))
		   	        {
		   	        	engine.__touchEvent.targets.push(this);
		   	        }			
				}
			}
			*/						
		}
		 		
		// Execute KeyFrame action callback.  
		if(!__timeline->__paused && __currentFrame->action)
		{			
			__parent = parentClip;
			__currentFrame->execute(gl, currentTime, loopTime, scene, this);
			__parent = NULL;		
		}		
	} 
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Boolean hitTest(Number wx, Number wy)
	{		
		return ((((wx - __vTOP_LEFT->X) * (__vTOP_RIGHT->Y - __vTOP_LEFT->Y) - (__vTOP_RIGHT->X - __vTOP_LEFT->X) * (wy - __vTOP_LEFT->Y)) * ((wx - __vBOTTOM_RIGHT->X) * (__vBOTTOM_LEFT->Y - __vBOTTOM_RIGHT->Y) - (__vBOTTOM_LEFT->X - __vBOTTOM_RIGHT->X) * (wy - __vBOTTOM_RIGHT->Y))) > 0
		&& (((wx - __vTOP_RIGHT->X) * (__vBOTTOM_RIGHT->Y - __vTOP_RIGHT->Y) - (__vBOTTOM_RIGHT->X - __vTOP_RIGHT->X) * (wy - __vTOP_RIGHT->Y)) * ((wx - __vBOTTOM_LEFT->X) * (__vTOP_LEFT->Y - __vBOTTOM_LEFT->Y) - (__vTOP_LEFT->X - __vBOTTOM_LEFT->X) * (wy - __vBOTTOM_LEFT->Y))) > 0);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	void initBoundingBoxFromTexture(CocoScene* scene, Number W2, Number H2)
	{    
	    // Reset vectors
	    __vTOP_LEFT->set(-W2, -H2, 0, 1);	    
	    __vTOP_RIGHT->set(W2, -H2, 0, 1);
	    __vBOTTOM_LEFT->set(-W2, H2, 0, 1);
	    __vBOTTOM_RIGHT->set(W2, H2, 0, 1);
	    	    
	    // Multiply vectors with the current modelview matrix
	    __vTOP_LEFT 	= scene->__modelViewMatrix->multiplyByVector(__vTOP_LEFT);
	    __vTOP_RIGHT 	= scene->__modelViewMatrix->multiplyByVector(__vTOP_RIGHT);
	    __vBOTTOM_LEFT 	= scene->__modelViewMatrix->multiplyByVector(__vBOTTOM_LEFT);
	    __vBOTTOM_RIGHT = scene->__modelViewMatrix->multiplyByVector(__vBOTTOM_RIGHT);
	    
	    __hasBoundingBox = true;
	}	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void initBoundingBoxFromChildren(CocoScene* scene)
	{	    
	    // This function calculates the bounding box of all our children.
	    
	    __hasBoundingBox = false;
	    
	    if(__childrenCount==0)
	    	return;
	        
	    CocoMatrix* MI;
	    CocoClip* Child;
	    CocoRect* Rc;
	    Number i;
	    CocoVector* v1;
	    CocoVector* v2;		
		Array<CocoVector> v;
	     
	    // Define an invalid rectangle.
	    Rc = new CocoRect();
	    Rc->left = 100000;
	    Rc->right = -100000;
	    Rc->top = 100000;
	    Rc->bottom = -100000;
	    	            
	    // Invert parent matrix.
	    MI = new CocoMatrix(scene->__modelViewMatrix);
	    MI->invert();
	            
        for(auto vClip : __children)
	    {	        
            // For every child, multiply the inverse parent matrix with child's
            // vertex vectors in order to unproject child coordinates.
            	                      
            if(vClip.second->__hasBoundingBox)
            {
	            v[0] = MI->multiplyByVector(Child->__vTOP_LEFT);
	            v[1] = MI->multiplyByVector(Child->__vTOP_RIGHT);
	            v[2] = MI->multiplyByVector(Child->__vBOTTOM_LEFT);
	            v[3] = MI->multiplyByVector(Child->__vBOTTOM_RIGHT);
	            
	            // Loop verticies to expand our bounding box from the current child.
	            for(i=0; i<4; i++)
	            {
	                if(v[i]->X < Rc->left) Rc->left = v[i]->X;
	                if(v[i]->X > Rc->right) Rc->right = v[i]->X;
	                if(v[i]->Y < Rc->top) Rc->top = v[i]->Y;
	                if(v[i]->Y > Rc->bottom) Rc->bottom = v[i]->Y;
	            }

				delete v[0];
				delete v[1];
				delete v[2];
				delete v[3];
            }
            
            // Ok, combine resulting bounding box with next child...
	    }
	        	    
	    __vTOP_LEFT->X = Rc->left;
	    __vTOP_LEFT->Y = Rc->top;
	    __vTOP_RIGHT->X = Rc->right;
	    __vTOP_RIGHT->Y = Rc->top;
	    __vBOTTOM_LEFT->X = Rc->left;
	    __vBOTTOM_LEFT->Y = Rc->bottom;
	    __vBOTTOM_RIGHT->X = Rc->right;
	    __vBOTTOM_RIGHT->Y = Rc->bottom;
	        
	    // Re-multiply our bounding box vertex vectors with the rotated matrix
	    MI = scene->__modelViewMatrix;
	    __vTOP_LEFT = (delete __vTOP_LEFT, MI->multiplyByVector(__vTOP_LEFT));
	    __vTOP_RIGHT = (delete __vTOP_RIGHT, MI->multiplyByVector(__vTOP_RIGHT));
	    __vBOTTOM_LEFT = (delete __vBOTTOM_LEFT, MI->multiplyByVector(__vBOTTOM_LEFT));
	    __vBOTTOM_RIGHT = (delete __vBOTTOM_RIGHT, MI->multiplyByVector(__vBOTTOM_RIGHT));	        
	    
	    __hasBoundingBox = true;
	} 
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void drawBoundingBox(CocoScene* scene, WebGLRenderingContext* gl)
	{
		if(!__hasBoundingBox) return;
		
		gl->disableVertexAttribArray(scene->__glProgram->GLSLiTexCoords);
		gl->disableVertexAttribArray(scene->__glProgram->GLSLiVecCoords);                         
		
		gl->useProgram(scene->__boundingBoxProgram);       
		gl->enableVertexAttribArray(scene->bbGLSLiVec2Coords);                      
		
		gl->bindBuffer(gl->ARRAY_BUFFER, scene->__boundingBoxBuffer);
		gl->bufferSubData(gl->ARRAY_BUFFER, 0, new Float32Array([__vTOP_LEFT->X, __vTOP_LEFT->Y, __vTOP_RIGHT->X, __vTOP_RIGHT->Y, __vBOTTOM_RIGHT->X, __vBOTTOM_RIGHT->Y, __vBOTTOM_LEFT->X, __vBOTTOM_LEFT->Y]));
		gl->vertexAttribPointer(scene->bbGLSLiVec2Coords, 2, gl->FLOAT, false, 0, 0);
		scene->__projectionMatrix->update(gl, scene->bbGLSLuProjMat);			
		gl->drawArrays(gl->LINE_LOOP, 0, 4);
		gl->bindBuffer(gl->ARRAY_BUFFER, null); 
		               
		gl->disableVertexAttribArray(scene->bbGLSLiVec2Coords);
		gl->useProgram(scene->__glProgram);   
		
		gl->enableVertexAttribArray(scene->GLSLiTexCoords);
		gl->enableVertexAttribArray(scene->GLSLiVecCoords);
	}
};

#endif