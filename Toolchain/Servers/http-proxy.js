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
// HTTP Proxy Server
////////////////////////////////////////////////////////////////////////////////////////////////////

"HTTP Proxy Server";

////////////////////////////////////////////////////////////////////////////////////////////////////
function date()
{
	var today = new Date();
	var dd = today.getDate();
	var mm = today.getMonth()+1;
	var yyyy = today.getFullYear();
	if(dd<10)
	{
	    dd='0'+dd;
	}
	if(mm<10)
	{
	    mm='0'+mm;
	}
	return [yyyy, mm, dd, Date.now()].join('-');
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function paramIndex(p)
{
	for(var i=0; i<process.argv.length; i++)
		if(process.argv[i].indexOf(p)==0)
			return i;
	return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
var httpProxy = require('http-proxy');
var fs = require('fs');
var local = process.argv[2];
var v = local.split(":");
var ip = v[0];
var port = v[1];
var remote = process.argv[3];
var trace = process.argv.indexOf("trace")!=-1;

////////////////////////////////////////////////////////////////////////////////////////////////////
var save = paramIndex("save");
if(save!=-1)
{
	save = process.argv[save];
	v = save.split("=");
	save = v[1];
	if(!fs.existsSync(save))
		fs.mkdirSync(save);
}
else
{
	save = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
var intercept = paramIndex("intercept");
var inject =  "";
if(intercept!=-1)
{
	intercept = process.argv[intercept];
	v = intercept.split("=");
	intercept = v[1];
	if(fs.existsSync(intercept))
	{
		var xml = fs.readFileSync(intercept, 'utf8');
		intercept = /<URL>(.*)<\/URL>/.exec(xml)[1];
		inject = /<BODY>\s*<\!\[CDATA\[([\W\w\S\s]*?)]]>/mg.exec(xml)[1];
		console.log("+ Intercept mode URL: " + intercept);
	}
	else
	{
		intercept = false;
	}
}
else
{
	intercept = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

var proxy = httpProxy.createServer({ target: remote });

////////////////////////////////////////////////////////////////////////////////////////////////////

proxy.on('error', function (e, req, res)
{
	console.log(e);
});

////////////////////////////////////////////////////////////////////////////////////////////////////

proxy.on('open', function (proxySocket)
{
	console.log("Client connected");
});

////////////////////////////////////////////////////////////////////////////////////////////////////

proxy.on('close', function (res, socket, head)
{
	console.log("Client disconnected");
});

////////////////////////////////////////////////////////////////////////////////////////////////////
proxy.on('proxyReq', function(proxyReq, req, res, options)
{
	res.setHeader("Access-Control-Allow-Headers","Origin,X-Requested-With,Content-Type,Accept");
	res.setHeader("Access-Control-Allow-Methods", "GET,PUT,POST,DELETE,OPTIONS");
	res.setHeader("Access-Control-Allow-Origin","*");

	if(req.url == intercept)
	{
		try
		{
			proxyReq.setHeader('Content-Length', Buffer.byteLength(inject, 'utf8'));
			proxyReq.setHeader("Access-Control-Allow-Headers","Origin,X-Requested-With,Content-Type,Accept");
			proxyReq.setHeader("Access-Control-Allow-Methods", "GET,PUT,POST,DELETE,OPTIONS");
			proxyReq.setHeader("Access-Control-Allow-Origin","*");

			res.end(inject);
		}
		catch(e)
		{
		}

	}
	else
	{
		var data = "";

		req.on('data' , function(dataBuffer)
		{
		    data += dataBuffer.toString('utf8');
		});

	    req.on('end' , function()
	    {
	    	req.__body = data.substr(0, data.length-1); // remove null character
	    });
	}
});

////////////////////////////////////////////////////////////////////////////////////////////////////

proxy.on('proxyRes', function (proxyRes, req, res)
{
	res.setHeader("Access-Control-Allow-Headers","Origin,X-Requested-With,Content-Type,Accept");
	res.setHeader("Access-Control-Allow-Methods", "GET,PUT,POST,DELETE,OPTIONS");
	res.setHeader("Access-Control-Allow-Origin","*");

	var headers = JSON.stringify(proxyRes.headers, true, 2);

	if(trace)
		console.log("Response Headers:", headers);

	var data="";

	proxyRes.on('data' , function(dataBuffer)
	{
	    data += dataBuffer.toString('utf8');
	});

    proxyRes.on('end' , function()
    {
    	try
    	{
	    	var obj = JSON.parse(data);
	    	if(obj) data = JSON.stringify(obj, null, 2);
    	}
    	catch(e)
    	{
    		data = "";
    	}

    	if(data && trace)
    	{
    		console.log(data);
    	}

    	if(!intercept && save)
    	{
    		var d = date();

    		var file = save + "/" + d + ".xml";

    		var xml = "<XHR>\n" +
    				  "\t<ID></ID>\n" +
    				  "\t<INTERCEPT>false</INTERCEPT>\n" +
    				  "\t<DESCRIPTION></DESCRIPTION>\n" +
    				  "\t<URL>" + req.url + "</URL>\n" +
    				  "\t<METHOD>" + req.method + "</METHOD>\n" +
    				  "\t<DATE>" + d + "</DATE>\n" +
    				  "\t<REQ>\n<![CDATA[\n" + req.__body + "\n]]>\n\t</REQ>\n" +
    				  "\t<RES>\n" +
    				  "\t\t<HEADERS>\n<![CDATA[\n" + headers + "\n]]>\n\t\t</HEADERS>\n" +
    				  "\t\t<BODY>\n<![CDATA[\n" + data + "\n]]>\n\t\t</BODY>\n" +
    				  "\t</RES>\n</XHR>";

			fs.writeFile(file, xml);
			console.log("@@XHR:" + file);
    	}
    });

});

////////////////////////////////////////////////////////////////////////////////////////////////////

proxy.listen(port, ip);

console.log("Proxy Server Started");
