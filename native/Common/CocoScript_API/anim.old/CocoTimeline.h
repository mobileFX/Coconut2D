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

#ifndef __CocoTimeline__
#define __CocoTimeline__

#include "Coconut2D.h"
#include "CocoKeyFrame.h"
#include "CocoTimeLabel.h"

// ==================================================================================================================================
//	   ______               _______                ___
//	  / ____/___  _________/_  __(_)___ ___  ___  / (_)___  ___
//	 / /   / __ \/ ___/ __ \/ / / / __ `__ \/ _ \/ / / __ \/ _ \
//	/ /___/ /_/ / /__/ /_/ / / / / / / / / /  __/ / / / / /  __/
//	\____/\____/\___/\____/_/ /_/_/ /_/ /_/\___/_/_/_/ /_/\___/
//
// ==================================================================================================================================

class CocoTimeline
{
public:

    Dictionary<CocoTimeLabel> __labels;
    Number __keyFramesCount;
    Index<CocoKeyFrame> __keyFrames:
    CocoKeyFrame* __firstKeyFrame;
    CocoKeyFrame* __lastKeyFrame;
    Number __singleFrameDurationTime;
    Number __durationInTime;
    Number __durationInFrames;
    Number __firstframeIndex;
    Number __lastframeIndex;
    Number __skipTime;
    Boolean __paused;
    CocoKeyFrame* __lastFrame;

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoTimeline()
    {
        addKeyFrameEx(NULL, 0, COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Array<CocoKeyFrame> keyFrames()
    {
        return Array<CocoKeyFrame>(__keyFrames.begin(), __keyFrames.end());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void clear()
    {
        while(!__keyFrames.empty()) {
			delete __keyFrames.begin()->second;
			__keyFrames.erase(__keyFrames.begin());
		}
		while(!__labels.empty()) {
			delete __labels.begin()->second;
			__labels.erase(__labels.begin());
		}
        __keyFramesCount = 0;
        normalizetimeline();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void reset()
    {
        __skipTime = 0;
        __paused = false;
        __lastFrame = NULL;

        for(auto v : __keyFrames)
            v.second->reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoTimeLabel* addLabel(CocoTimeLabel* Label)
    {
        if(!Label) return NULL;
        __labels[std::to_string(Label.frameIndex)] = Label;
        return Label;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoTimeLabel* addLabelEx(Number FrameIndex, String LabelName)
    {
        CocoTimeLabel* Label = new CocoTimeLabel(FrameIndex, LabelName);
        return addLabel(Label);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoTimeLabel* findLabelByName(String LabelName)
    {
        CocoTimeLabel* Label;
		for(auto v : __labels)
			if(v.first == LabelName)
				return v.second;

        return NULL;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* keyFrame(Number frameIndex)
    {
		auto ret = __keyFrames.find(frameIndex);
        return (ret != __keyFrames.end() ? ret : NULL);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* addKeyFrame(CocoKeyFrame* KeyFrame)
    {
        if(!KeyFrame) return NULL;
        KeyFrame->frameIndex = roundIndex(KeyFrame->frameIndex);
        __keyFrames[KeyFrame.frameIndex] = KeyFrame;
        normalizetimeline();
        return KeyFrame;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* addKeyFrameEx(Function actionCallback,
                                  Number frameIndex,
                                  COCO_KEYFRAME_INTERPOLATION_ENUM frameInterpolation,
                                  Boolean handleEvents,
                                  Boolean visible,
                                  Number x,
                                  Number y,
                                  Number scaleX,
                                  Number scaleY,
                                  Number rotation,
                                  Number pivotX,
                                  Number pivotY,
                                  Number alpha)
    {
        CocoKeyFrame* KeyFrame = new CocoKeyFrame();

        KeyFrame->action				= actionCallback;
        KeyFrame->frameIndex 			= frameIndex;
        KeyFrame->frameInterpolation	= frameInterpolation;
        KeyFrame->handleEvents 			= handleEvents;
        KeyFrame->visible 				= visible;
        KeyFrame->x 					= x;
        KeyFrame->y 					= y;
        KeyFrame->scaleX				= scaleX;
        KeyFrame->scaleY				= scaleY;
        KeyFrame->rotation 				= rotation;
        KeyFrame->pivotX 				= pivotX;
        KeyFrame->pivotY 				= pivotY;
        KeyFrame->alpha 				= alpha;

        return addKeyFrame(KeyFrame);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* insertKeyFrame(Number frameIndex)
    {
        frameIndex = roundIndex(frameIndex);
		auto keyFrame = __keyFrames.find(frameIndex);
		return addKeyFrame(keyFrame != __keyFrames.end() ? keyFrame : interpolateByFrame(frameIndex));
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void deleteKeyFrame(CocoKeyFrame* KeyFrame)
    {
        if(!KeyFrame) return;
		auto del = __keyFrames.find(KeyFrame.frameIndex);
		if(del) {
			delete del->second;
			__keyFrames.erase(del);
		}
        normalizetimeline();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void insertFrames(Number AtTimeIndex, Number FramesCount)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void deleteFrames(Number FromTimeIndex, Number ToTimeIndex)
    {
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void setKeyFrameIndex(CocoKeyFrame* KeyFrame, Number frameIndex)
    {
        if(!KeyFrame || (frameIndex == KeyFrame.frameIndex)) return;

        frameIndex = roundIndex(frameIndex);
        KeyFrame.frameIndex = roundIndex(KeyFrame.frameIndex);
        if(frameIndex == KeyFrame.frameIndex) return;

        __keyFrames.erase(KeyFrame.frameIndex);
        KeyFrame.frameIndex = frameIndex;
        __keyFrames[KeyFrame.frameIndex] = KeyFrame;

        normalizetimeline();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* findKeyFrameBeforeframeIndex(Number frameIndex, Boolean inclusive = false, Number excludeListIndex = -1)
    {
        Number i;
        CocoKeyFrame* KeyFrame;
        Array<CocoKeyFrame> list = keyFrames();

        for(i=list.size()-1; i>=0; i--)
        {
            if(i!=excludeListIndex)
            {
                KeyFrame = list[i];
                if(inclusive)
                {
                    if(KeyFrame.frameIndex <= frameIndex)
                        return KeyFrame;
                }
                else
                {
                    if(KeyFrame.frameIndex < frameIndex)
                        return KeyFrame;
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* findKeyFrameAfterframeIndex(Number frameIndex, Boolean inclusive = false, Number excludeListIndex = -1)
    {
        Number i;
        CocoKeyFrame* KeyFrame;
        Array<CocoKeyFrame> list = keyFrames();

        for(i=0; i<list.size(); i++)
        {
            if(i!=excludeListIndex)
            {
                KeyFrame = list[i];
                if(inclusive)
                {
                    if(KeyFrame.frameIndex >= frameIndex)
                        return KeyFrame;
                }
                else
                {
                    if(KeyFrame.frameIndex > frameIndex)
                        return KeyFrame;
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Array<CocoKeyFrame> findKeyFramesBetween(Number startframeIndex, Number stopframeIndex)
    {
        Array<CocoKeyFrame> col;
        Array<CocoKeyFrame> list = keyFrames();
        Number i;
        CocoKeyFrame* KeyFrame;
        for(i=0; i<list.size(); i++)
        {
            KeyFrame = list[i];
            if(KeyFrame.frameIndex >= startframeIndex || KeyFrame.frameIndex <= stopframeIndex)
                col.push_back(KeyFrame);
        }
        return col;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Number listIndexOfKeyFrame(CocoKeyFrame* KeyFrame)
    {
        String v;
        Number index = -1;
		for(auto v : __keyFrames)
		{
			index++;
			if(v.second == KeyFrame)
				return index;
		}
        return -1;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void normalizetimeline()
    {
        CocoKeyFrame* KeyFrame;
        String v;
        Array<CocoKeyFrames> vArr;
        CocoKeyFrame* f;
        Number i;
        Number L=0;

        __durationInFrames = 0;
        __durationInTime = 0;
        __singleFrameDurationTime = 0;
        __firstframeIndex = 0;
        __lastframeIndex = 0;
        __firstKeyFrame = NULL;
        __lastKeyFrame = NULL;
        __keyFramesCount = 0;

        // Count KeyFrames
		__keyFramesCount = __keyFrames.size();

        if(__keyFramesCount)
        {
            // First and Last KeyFrames
			__firstKeyFrame = v.begin()->second;
			__lastKeyFrame = v.rbegin()->second;

            // Sort KeyFrames
			// done magically!

            // Calc expensive time/index variables
            if(__lastKeyFrame)
            {
                __lastframeIndex = __lastKeyFrame->frameIndex;
                __durationInFrames = __lastKeyFrame->frameIndex + 1;
                __durationInTime = (__durationInFrames / GLOBAL_FPS) * 1000;
                __singleFrameDurationTime = __durationInTime / __durationInFrames;
                __firstframeIndex = listIndexOfKeyFrame(__firstKeyFrame);
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    inline Number roundIndex(Number index)
    {
        return floor(index);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    Number frameIndexToLoopTime(Number frameIndex)
    {
        return frameIndex * __singleFrameDurationTime;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void jumpBy(Number frames, Boolean paused)
    {
        __paused = paused;
        if(frames!=0)
        {
            __skipTime += (frames * __singleFrameDurationTime);
            __lastFrame = NULL;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* interpolateByTime(Number LoopTime)
    {
        Number T = (LoopTime / __singleFrameDurationTime);
        return interpolateByFrame(T);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    CocoKeyFrame* interpolateByFrame(Number frameIndex)
    {
        if(__paused && __lastFrame)
            return __lastFrame;

        CocoKeyFrame* F = NULL;
        CocoKeyFrame* F1 = NULL;
        CocoKeyFrame* F2 = NULL;
        Number s = 1;
        Number FrameIndex = roundIndex(frameIndex);

        // Timeline is empty?
        if(!__keyFramesCount)
        {
            F = new CocoKeyFrame();
            F->frameIndex = FrameIndex;
            F->visible = false;
            return __lastFrame = F;
        }

        // Exact KeyFrame exists?
        F1 = keyFrame(FrameIndex);
        if(F1) return (__lastFrame = F1);

        // Seek previous KeyFrame
        F1 = findKeyFrameBeforeframeIndex(FrameIndex, false);

        if(!F1)
        {
            // No previous KeyFrame
            F = new CocoKeyFrame();
            F->frameIndex = FrameIndex;
            F->visible = false;
            return (__lastFrame = F);
        }
        else
        {
            switch(F1->frameInterpolation)
            {
			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_ECHO:

                F = F1->clone();
                F->frameIndex = FrameIndex;
                F->action=null;
                return (__lastFrame = F);

			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_NONE:

                F = F1->clone();
                F->frameIndex = FrameIndex;
                F->action=null;
                F->visible = false;
                return (__lastFrame = F);

			case COCO_KEYFRAME_INTERPOLATION_ENUM::KEYFRAME_INTERPOLATION_MOTION_TWEEN:

                // We need the next KeyFrame now
                F2 = findKeyFrameAfterframeIndex(FrameIndex, false);

                if(!F2)
                {
                    // Fallback to echo
                    F = F1->clone();
                    F->frameIndex = FrameIndex;
                    F->action=NULL;
                    return (__lastFrame = F);

                }
                else
                {
                    // Interpolate between frames
                    F = F1->clone();
                    F->frameIndex = FrameIndex;
                    F->action=NULL;
                    s = (frameIndex - F1->frameIndex) / (F2->frameIndex - F1->frameIndex);
                    F->interpolate(F1, F2, s);
                    return (__lastFrame = F);
                }
            }
        }
    }
}

#endif
