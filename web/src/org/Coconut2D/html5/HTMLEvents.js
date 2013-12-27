//@compile{native}

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
HTMLEvent.prototype.pageX = 0;
HTMLEvent.prototype.pageY = 0;
HTMLEvent.prototype.screenX = 0;
HTMLEvent.prototype.screenY = 0;
HTMLEvent.prototype.preventDefault = function(type, bubbles, cancelable){};
HTMLEvent.prototype.defaultPrevented = false;
HTMLEvent.prototype.timeStamp = new Object();
HTMLEvent.prototype.changedTouches = new TouchList(5);
HTMLEvent.prototype.touches = new TouchList(5);
HTMLEvent.prototype.targets = [];

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
TouchList.prototype.length = 0;
