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
//	    ____                           ____        __       
//	   /  _/___ ___  ____ _____ ____  / __ \____ _/ /_____ _
//	   / // __ `__ \/ __ `/ __ `/ _ \/ / / / __ `/ __/ __ `/
//	 _/ // / / / / / /_/ / /_/ /  __/ /_/ / /_/ / /_/ /_/ / 
//	/___/_/ /_/ /_/\__,_/\__, /\___/_____/\__,_/\__/\__,_/  
//	                    /____/                              
// ==================================================================================================================================

function ImageData(a0, a1)
{
	if(typeof a0 == "string")
	{
	    var data = __ImageData_loadImage(a0);
	    if(data)
	    {
	        this.src = a0;
	        this.__buffer = data.buffer;
	        this.width = data.width;
	        this.height = data.height;
	    }
	}
	else if(typeof a0 == "number" && typeof a1 == "number")
	{
		this.width = a0;
		this.height = a1;
		this.__data = new Int32Array(this.width * this.height);
		this.__buffer = this.__data.buffer;
	}
}
ImageData.prototype = new Object();
ImageData.prototype.__buffer = null;
ImageData.prototype.src = "";
ImageData.prototype.width = 0;
ImageData.prototype.height = 0;

// ==================================================================================================================================
//       __  __________  _____    ____                           ________                          __
//      / / / /_  __/  |/  / /   /  _/___ ___  ____ _____ ____  / ____/ /__  ____ ___  ___  ____  / /_
//     / /_/ / / / / /|_/ / /    / // __ `__ \/ __ `/ __ `/ _ \/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//    / __  / / / / /  / / /____/ // / / / / / /_/ / /_/ /  __/ /___/ /  __/ / / / / /  __/ / / / /_
//   /_/ /_/ /_/ /_/  /_/_____/___/_/ /_/ /_/\__,_/\__, /\___/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/
//                                                /____/
//
// ==================================================================================================================================

function HTMLImageElement(){};
HTMLImageElement.prototype = new HTMLElement();

HTMLImageElement.prototype.__defineSetter__("src", function(src)
{
    this.__imageData = new ImageData(src);
    this.__width = this.__imageData.width;
    this.__height = this.__imageData.height;
    this.__complete = true;
    if(this.onload) this.onload(this);
});

HTMLImageElement.prototype.onload = function(){};

HTMLImageElement.prototype.__imageData = null;
HTMLImageElement.prototype.__width = 0;
HTMLImageElement.prototype.__height = 0;
HTMLImageElement.prototype.__complete = false;
HTMLImageElement.prototype.__defineGetter__("src", function(){ return this.__imageData.src; });
HTMLImageElement.prototype.__defineGetter__("complete", function(){return this.__complete;});
HTMLImageElement.prototype.__defineGetter__("width", function(){return this.__width;});
HTMLImageElement.prototype.__defineGetter__("height", function(){return this.__height;});
HTMLImageElement.prototype.__defineGetter__("naturalWidth", function(){return this.__imageData.width;});
HTMLImageElement.prototype.__defineGetter__("naturalHeight", function(){return this.__imageData.height;});

var Image = HTMLImageElement;

// ==================================================================================================================================
//	    __  __________  _____    ______                            ________                          __ 
//	   / / / /_  __/  |/  / /   / ____/___ _____ _   ______ ______/ ____/ /__  ____ ___  ___  ____  / /_
//	  / /_/ / / / / /|_/ / /   / /   / __ `/ __ \ | / / __ `/ ___/ __/ / / _ \/ __ `__ \/ _ \/ __ \/ __/
//	 / __  / / / / /  / / /___/ /___/ /_/ / / / / |/ / /_/ (__  ) /___/ /  __/ / / / / /  __/ / / / /_  
//	/_/ /_/ /_/ /_/  /_/_____/\____/\__,_/_/ /_/|___/\__,_/____/_____/_/\___/_/ /_/ /_/\___/_/ /_/\__/  
//	                                                                                                    
// ==================================================================================================================================

function HTMLCanvasElement()
{
};

HTMLCanvasElement.prototype = new HTMLElement();
HTMLCanvasElement.prototype.__buffer;
HTMLCanvasElement.prototype.width = 0;
HTMLCanvasElement.prototype.height = 0;
HTMLCanvasElement.prototype.toDataURL = function(type, args){};
HTMLCanvasElement.prototype.getContext = function(contextId, args)
{	
	return new WebGLRenderingContext(this);
};



