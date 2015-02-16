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

////////////////////////////////////////////////////////////////////////////////////////////////////
// Instantiate Coconut2D HTTP Server
////////////////////////////////////////////////////////////////////////////////////////////////////

var http = require('http');
var coco = global.Coconut2D = require("Coconut2D.node");
var server = null;

module.exports.SERVER_OBJ_FOLDER = "$(TARGETS.node.js.TARGET_SERVER_OBJ)";
module.exports.CLIENT_OBJ_FOLDER = "$(TARGETS.node.js.TARGET_CLIENT_OBJ)";

// Attempt to load user HTTP server implementation
if(Coconut2D.fileExists('./$(TARGETS.node.js.TARGET_SERVER_OBJ)/Server.jobj'))
{
	var module = require('./$(TARGETS.node.js.TARGET_SERVER_OBJ)/Server.jobj');
	if(module && module.Server)
	{
		server = new module.Server();
		console.log("Using custom HTTP server.");
	}
}
else if(Coconut2D.fileExists('./$(TARGETS.node.js.TARGET_SERVER_OBJ)/HTTPServer.jobj'))
{
	// Fall-back to generaic HTTP server implementation
	module = require('./$(TARGETS.node.js.TARGET_SERVER_OBJ)/HTTPServer.jobj');
	if(module && module.HTTPServer)
	{
		server = module.HTTPServer();
		console.log("Using generic HTTP server.");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function rawStringToBuffer(str)
{
    var idx, len = str.length, arr = new Array(len);
    for(idx=0; idx<len; ++idx)
    {
        arr[idx] = str.charCodeAt(idx) & 0xFF;
    }
    return new Uint8Array(arr).buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function toArrayBuffer(buffer)
{
    var ab = new ArrayBuffer(buffer.length);
    var view = new Uint8Array(ab);
    for(var i=0; i<buffer.length; ++i)
    {
        view[i] = buffer[i];
    }
    return ab;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Instantiate Node.JS HTTP Server
////////////////////////////////////////////////////////////////////////////////////////////////////
http.createServer( function(request, response)
{
    if(request.method == 'POST')
    {
        var body = '';
        request.on('data', function (data)
        {
            body += data;
            // 1e6 === 1 * Math.pow(10, 6) === 1 * 1000000 ~~~ 1MB
            if (body.length > 1e6)
            {
                // FLOOD ATTACK OR FAULTY CLIENT, NUKE REQUEST
                request.connection.destroy();
            }
        });
        request.on('end', function ()
        {
        	request.__body = body;
        	var sig = "data:coconut2d/datastream;base64,";
        	if(body.indexOf(sig)==0)
        	{
        		var buff = new Buffer(body.substr(sig.length), "base64");
        		request.__arrayBuffer = toArrayBuffer(buff);
        		delete buff;
        	}
        	else
        	{
        		request.__body = body;
            	request.__arrayBuffer = rawStringToBuffer(body);
        	}
            server.handle(request, response);
        });
    }
    else
    {
    	server.handle(request, response);
    }

}).listen(80, '$(LOCALHOST_IP)');

console.log('Server running on http://$(LOCALHOST_IP):80/');
