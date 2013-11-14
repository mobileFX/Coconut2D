//@compile{native}
//@include{HTML5.js}

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

// ==================================================================================================================================
//	    __  __________  _____    ______                 __ 
//	   / / / /_  __/  |/  / /   / ____/   _____  ____  / /_
//	  / /_/ / / / / /|_/ / /   / __/ | | / / _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ /___ | |/ /  __/ / / / /_  
//	/_/ /_/ /_/ /_/  /_/_____/_____/ |___/\___/_/ /_/\__/  
//	                                                       
// ==================================================================================================================================

function HTMLEvent(){}
HTMLEvent.prototype = new Object();
HTMLEvent.prototype.type = "";
HTMLEvent.prototype.bubbles = false;
HTMLEvent.prototype.cancelable = false;
HTMLEvent.prototype.stopPropagation = function(){};
HTMLEvent.prototype.clientX = 0; 
HTMLEvent.prototype.clientY = 0;
HTMLEvent.prototype.pageX;
HTMLEvent.prototype.pageY;
HTMLEvent.prototype.screenX = 0;
HTMLEvent.prototype.screenY = 0;
HTMLEvent.prototype.preventDefault = function(type, bubbles, cancelable){};
HTMLEvent.prototype.defaultPrevented = false;
HTMLEvent.prototype.timeStamp = new Object();
HTMLEvent.prototype.changedTouches = new TouchList(5);
HTMLEvent.prototype.touches = new TouchList(5);
HTMLEvent.prototype.targets = [];

//HTMLEvent.prototype.button = 0;
//HTMLEvent.prototype.buttons = 0;
//HTMLEvent.prototype.ctrlKey = false;
//HTMLEvent.prototype.currentTarget = new HTMLElement();
//HTMLEvent.prototype.eventPhase = 0;
//HTMLEvent.prototype.getModifierState = function(keyArg){};
//HTMLEvent.prototype.identifier;
//HTMLEvent.prototype.initEvent = function(eventTypeArg, canBubbleArg, cancelableArg){};
//HTMLEvent.prototype.initMouseEvent = function(typeArg, canBubbleArg, cancelableArg, viewArg, detailArg, screenXArg, screenYArg, clientXArg, clientYArg, ctrlKeyArg, altKeyArg, shiftKeyArg, metaKeyArg, buttonArg, relatedTargetArg){};
//HTMLEvent.prototype.initTouchEvent = function(type, canBubble, cancelable,view, detail, screenX, screenY, clientX, clientY, ctrlKey, altKey, shiftKey, metaKey, touches, targetTouches, changedTouches, scale, rotation) {};
//HTMLEvent.prototype.inputMethod = 0;
//HTMLEvent.prototype.metaKey = false;
//HTMLEvent.prototype.relatedTarget = new HTMLElement();
//HTMLEvent.prototype.rotation;
//HTMLEvent.prototype.scale;
//HTMLEvent.prototype.shiftKey = false;
//HTMLEvent.prototype.targetTouches;
//HTMLEvent.prototype.target = new HTMLElement();

// ==================================================================================================================================
//	  ______                 __    __    _      __ 
//	 /_  __/___  __  _______/ /_  / /   (_)____/ /_
//	  / / / __ \/ / / / ___/ __ \/ /   / / ___/ __/
//	 / / / /_/ / /_/ / /__/ / / / /___/ (__  ) /_  
//	/_/  \____/\__,_/\___/_/ /_/_____/_/____/\__/  
//	                                               
// ==================================================================================================================================function TouchList() {}
function TouchList(num)
{
	this.length = 0;
	var i;
	for(i = num; i--;)
	{
		this[i] = new HTMLEvent();
	}
	this.item = function(index) { return this[index]; };
}
TouchList.prototype = new Array();
TouchList.prototype.item = function(index) { return this[index]; };
TouchList.prototype.length;


// ==================================================================================================================================
//       ______      ______               __           __  ___
//      / ____/___ _/ / / /_  ____ ______/ /_______   /  |/  /___ _____  ____ _____ ____  _____
//     / /   / __ `/ / / __ \/ __ `/ ___/ //_/ ___/  / /|_/ / __ `/ __ \/ __ `/ __ `/ _ \/ ___/
//    / /___/ /_/ / / / /_/ / /_/ / /__/ ,< (__  )  / /  / / /_/ / / / / /_/ / /_/ /  __/ /
//    \____/\__,_/_/_/_.___/\__,_/\___/_/|_/____/  /_/  /_/\__,_/_/ /_/\__,_/\__, /\___/_/
//                                                                          /____/
// ==================================================================================================================================
function CallbackManager()
{	
	__registerManager(this, this.dispatchEvent, this.data);
}
CallbackManager.prototype = new Object;
CallbackManager.prototype.data = new HTMLEvent();
CallbackManager.prototype.elements = {};

CallbackManager.prototype.addEventListener = function(object, type, listener, useCapture)
{
	__registerCallback(object.__uid, type);	
	var callbackInfo = { object:object, type:type, listener:listener };	
	var t = type + object.__uid;
	this.elements[t] = callbackInfo;
};

CallbackManager.prototype.removeEventListener = function(object, type, listener, useCapture)
{
	var callbackInfo = this.elements[type + object.__uid];
	if(callbackInfo)
	{
		callbackInfo.object = null;
		callbackInfo.listener = null;
		callbackInfo.type = null;
	}
	this.elements[type + object.__uid] = null;
	__unRegisterCallback(object.__uid, type);		
};

CallbackManager.prototype.dispatchEvent = function(uid, type)
{
	var t = type + uid;
	var callbackInfo = this.elements[t];
	if(callbackInfo && callbackInfo.listener) 
	{
		var obj = callbackInfo.object;
		obj.__callCtx = function(e) { callbackInfo.listener(e); };
		obj.__callCtx(this.data);
		obj.__callCtx = null;
	}
};

var CallbackManager = new CallbackManager();


