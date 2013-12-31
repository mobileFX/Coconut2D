"#export web"

/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.coconut2D.org
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

// ==================================================================================================================================
//	   ______                 __              __
//	  / ____/___  ____  _____/ /_____ _____  / /______
//	 / /   / __ \/ __ \/ ___/ __/ __ `/ __ \/ __/ ___/
//	/ /___/ /_/ / / / (__  ) /_/ /_/ / / / / /_(__  )
//	\____/\____/_/ /_/____/\__/\__,_/_/ /_/\__/____/
//
// ==================================================================================================================================

"#ignore_errors_begin";
var global = this;
var engine = null;
var gl = null;

if(global["EventTarget"])
{
	// Replace EventTarget native object with JavaScript object
	global.EventTarget = function() {};
}

"#ignore_errors_end";

var RADIANS = Math.PI / 180.0;

////////////////////////////////////////////////////////////////////////////////////////////////////
if(!global["trace"])
{
	global.trace = function(msg) { console.log(msg); };

	"#ignore_errors_begin";
	Image.prototype.load = function(src) { this.src = src; };
	"#ignore_errors_end";
	
	function State(){};
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Extensions of JavaScript Array and Object classes to match C++ Vector and Map.

Object.defineProperty(Array.prototype, "size", { value: function()
{
	return this.length;
}});

Object.defineProperty(Array.prototype, "clear", { value: function()
{
	while(this.length) { this.pop(); }
}});


////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Enum for screen resolution dpi.
 * @enum {number}
 */
var SCREEN_RESOLUTION_DPI_ENUM =
{
    RESOLUTION_nodpi							: 0,
    RESOLUTION_ldpi								: 1,
    RESOLUTION_mdpi								: 2,
    RESOLUTION_tvdpi							: 3,
    RESOLUTION_hdpi								: 4,
    RESOLUTION_xhdpi							: 5,
    RESOLUTION_Retina							: 5,
    RESOLUTION_DefaultDpi						: 0
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Enum for clip symbol loop synchronization.
 * @enum {number}
 */
var COCO_CLIP_SYMBOL_LOOP_ENUM =
{
    CLIP_SYMBOL_LOOP_CONTINUOUS					: 0,
    CLIP_SYMBOL_LOOP_SYNCHRONIZED_WITH_PARENT	: 1,
    CLIP_SYMBOL_LOOP_ONCE						: 2
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Enum for keyframe interpolation calculation.
 * @enum {number}
 */
var COCO_KEYFRAME_INTERPOLATION_ENUM =
{
    KEYFRAME_INTERPOLATION_NONE					: 0,
    KEYFRAME_INTERPOLATION_MOTION_TWEEN			: 1,
    KEYFRAME_INTERPOLATION_ECHO					: 2,
    KEYFRAME_INTERPOLATION_PHYSICS				: 3
};

////////////////////////////////////////////////////////////////////////////////////////////////////
var COCO_STOP_ON_CURRENT_FRAME					= -1;
















