//@compile{native}
//@depends{Constants.js}

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
//       __  __________  _____    ________                          __
//      / / / /_  __/  |/  / /   / ____/ /__  ____ ___  ___  ____  / /_
//     / /_/ / / / / /|_/ / /   / __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//    / __  / / / / /  / / /___/ /___/ /  __/ / / / / /  __/ / / / /_
//   /_/ /_/ /_/ /_/  /_/_____/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

var __uid_counter = 0;

function HTMLElement()
{
	this.__uid = (++__uid_counter);	
}
HTMLElement.prototype = new Object();
HTMLElement.prototype.__uid = 0;
HTMLElement.prototype.id = "";
HTMLElement.prototype.name = "";
HTMLElement.prototype.tagName = "";
HTMLElement.prototype.children = [];
HTMLElement.prototype.parentElement = null;
HTMLElement.prototype.__defineGetter__("firstChild", function(){return this.children.length?this.children[0]:null;});
HTMLElement.prototype.__defineGetter__("lastChild", function(){return this.children.length?this.children[this.children.length-1]:null;});
HTMLElement.prototype.__defineGetter__("ownerDocument", function() { return window.document; });

HTMLElement.prototype.appendChild = function(node) 
{ 
	if(node.parentElement)
	{
		node.parentElement.removeChild(node);
	};
	this.children.push(node);
	node.parentElement=this;
	return node;
};

HTMLElement.prototype.removeChild = function(child){for(var i=this.children.length;i--;){if(this.children[i]===child){this.children.splice(i,1);child.parentNode=null;return child;}}};
HTMLElement.prototype.addEventListener = function(type, listener, useCapture){ return CallbackManager.addEventListener(this, type, listener, useCapture); };
HTMLElement.prototype.removeEventListener = function(type, listener, useCapture){ return CallbackManager.removeEventListener(this, type, listener, useCapture); };

// ==================================================================================================================================
//      __  __________  _____    ____            __      ________                          __
//     / / / /_  __/  |/  / /   / __ )____  ____/ /_  __/ ____/ /__  ____ ___  ___  ____  / /_
//    / /_/ / / / / /|_/ / /   / __  / __ \/ __  / / / / __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//   / __  / / / / /  / / /___/ /_/ / /_/ / /_/ / /_/ / /___/ /  __/ / / / / /  __/ / / / /_
//  /_/ /_/ /_/ /_/  /_/_____/_____/\____/\__,_/\__, /_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//                                             /____/
//
// ==================================================================================================================================

function HTMLBodyElement(){};
HTMLBodyElement.prototype = new HTMLElement();

// ==================================================================================================================================
//       __  __________  _____    ____                                        __
//      / / / /_  __/  |/  / /   / __ \____  _______  ______ ___  ___  ____  / /_
//     / /_/ / / / / /|_/ / /   / / / / __ \/ ___/ / / / __ `__ \/ _ \/ __ \/ __/
//    / __  / / / / /  / / /___/ /_/ / /_/ / /__/ /_/ / / / / / /  __/ / / / /_
//   /_/ /_/ /_/ /_/  /_/_____/_____/\____/\___/\__,_/_/ /_/ /_/\___/_/ /_/\__/
//
// ==================================================================================================================================

function HTMLDocument()
{
	this.body.parentElement = this;
}
HTMLDocument.prototype = new Object();
HTMLDocument.prototype.body = new HTMLBodyElement();
HTMLDocument.prototype.createElement = function(tagName) 
{
	return new HTMLCanvasElement(); 
};

// ==================================================================================================================================
//	    __  __________  _____    __                     __  _           
//	   / / / /_  __/  |/  / /   / /   ____  _________ _/ /_(_)___  ____ 
//	  / /_/ / / / / /|_/ / /   / /   / __ \/ ___/ __ `/ __/ / __ \/ __ \
//	 / __  / / / / /  / / /___/ /___/ /_/ / /__/ /_/ / /_/ / /_/ / / / /
//	/_/ /_/ /_/ /_/  /_/_____/_____/\____/\___/\__,_/\__/_/\____/_/ /_/ 
//	                                                                    
// ==================================================================================================================================

function HTMLLocation()
{
}
HTMLLocation.prototype = new Object();
HTMLLocation.prototype.origin = "";
HTMLLocation.prototype.pathname = "";

// ==================================================================================================================================
//	    __  __________  _____ _       ___           __             
//	   / / / /_  __/  |/  / /| |     / (_)___  ____/ /___ _      __
//	  / /_/ / / / / /|_/ / / | | /| / / / __ \/ __  / __ \ | /| / /
//	 / __  / / / / /  / / /__| |/ |/ / / / / / /_/ / /_/ / |/ |/ / 
//	/_/ /_/ /_/ /_/  /_/_____/__/|__/_/_/ /_/\__,_/\____/|__/|__/  
//	                                                               
// ==================================================================================================================================

var window = this;
window.__uid = 0; // window must have __uid = 0;
window.document = new HTMLDocument();
window.location - new HTMLLocation();
window.addEventListener = function(type, listener, useCapture){ return CallbackManager.addEventListener(this, type, listener, useCapture); };
window.removeEventListener = function(type, listener, useCapture){ return CallbackManager.removeEventListener(this, type, listener, useCapture); };
window.localStorage = {};

var top = window;
var self = window;
var document = window.document;

