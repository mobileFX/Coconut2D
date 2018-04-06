/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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
// HTTP Trace Server
////////////////////////////////////////////////////////////////////////////////////////////////////

function main()
{
	var v = process.argv[2].split(":");
	var ip = v[0];
	var port = v[1];

	require('http').createServer( function(request, response)
	{
	    var body = '';

	    request.on('data', function (data)
	    {
	        body += data;
	        if (body.length > 1e6)
	            request.connection.destroy();
	    });

	    request.on('end', function()
	    {
	    	console.log(body);
			response.writeHead(200, {"Content-Type": "text/plain"});
			response.end();
	    });

	}).listen(port, ip);

	console.log("+ Trace server running on http://" + ip + ":" + port);
}

main();
