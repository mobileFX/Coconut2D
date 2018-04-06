/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2014 www.yourcompany.com
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// Extensions of JavaScript Array, String and Object classes to match C++ Vector and Map.
////////////////////////////////////////////////////////////////////////////////////////////////////

Object.defineProperty(Array.prototype, "size", { value: function()
{
	return this.length;
}});

Object.defineProperty(Array.prototype, "clear", { value: function()
{
	while(this.length) { this.pop(); }
}});

Object.defineProperty(Array.prototype, "clone", { value: function()
{
	return [].concat(this);
}});

Object.defineProperty(String.prototype, "size", { value: function()
{
	return this.length;
}});

Object.defineProperty(String.prototype, "toArrayBuffer", { value: function()
{
    var idx, len = this.length, arr = new Array(len);
    for(idx=0; idx<len; ++idx)
        arr[idx] = this.charCodeAt(idx) & 0xFF;
    return new Uint8Array(arr).buffer;
}});

////////////////////////////////////////////////////////////////////////////////////////////////////
global.__delete__ = function(o,a)
{
	if(!o) return;
	if(a)
	{
		for(var i=o.length;i--;)
		{
			o[i] && ((o[i].hasOwnProperty('Destructor') && o[i].Destructor()) || !o[i].hasOwnProperty('Destructor')) && (delete o[i]);o[i]=null;
		}
	}
	((o.hasOwnProperty('Destructor') && o.Destructor()) || !o.hasOwnProperty('Destructor')) && (delete o); o=null;
	return null;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
global.StringToArrayBuffer = function(str)
{
    var idx, len = str.length, arr = new Array(len);
    for(idx=0; idx<len; ++idx)
    {
        arr[idx] = str.charCodeAt(idx) & 0xFF;
    }
    return new Uint8Array(arr).buffer;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
global.BufferToArrayBuffer = function(buffer)
{
    var ab = new ArrayBuffer(buffer.length);
    var view = new Uint8Array(ab);
    for(var i=0; i<buffer.length; ++i)
    {
        view[i] = buffer[i];
    }
    return ab;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
global.trace = console.log;

////////////////////////////////////////////////////////////////////////////////////////////////////
console.log("CocoScript Support Loaded.");

