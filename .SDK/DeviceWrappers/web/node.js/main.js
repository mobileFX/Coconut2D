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
var server = null;

// Attempt to load user HTTP server implementation
var module = require('./obj/Server.jobj');
if(module && module.Server)
{
	server = new module.Server();
	console.log("Using custom HTTP server.");
}
else
{
	// Fall-back to generaic HTTP server implementation
	module = require('./obj/HTTPServer.jobj');
	if(module && module.HttpServer)
	{
		server = module.HttpServer();
		console.log("Using generic HTTP server.");
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Instantiate Node.JS HTTP Server
////////////////////////////////////////////////////////////////////////////////////////////////////
http.createServer( function(req, res)
{
	return server.handle(req, res);

}).listen(80, '127.0.0.1');

console.log('Server running on http://127.0.0.1:80/');
