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
//	       _______ ____                ____
//	      / / ___// __ \____  _____   / __ \____ ______________  _____
//	 __  / /\__ \/ / / / __ \/ ___/  / /_/ / __ `/ ___/ ___/ _ \/ ___/
//	/ /_/ /___/ / /_/ / /_/ / /__   / ____/ /_/ / /  (__  )  __/ /
//	\____//____/_____/\____/\___/  /_/    \__,_/_/  /____/\___/_/
//
// ==================================================================================================================================

function JSDocParse(node, comment)
{
	// Parse a comment and set Node properties

	var jsdoc = {};
	var rx = new RegExp("@(\\w+) (.*?)$", "mg");
	var descr = /([\w\W\n\N]+?)@\w+/mg.exec(comment)[1].split('\n');
	var out=[];
	for(i=0;i<descr.length;i++)
	{
		var match = /^[\/\s\t\*]*(.*?)$/.exec(descr[i].trim());
		if(match[1])
			out.push(match[1].trim());
	}
	jsdoc.descr = out.join(" ");

	while(match = rx.exec(comment))
	{
		var attr = match[1];
		var value = match[2];

		switch(attr)
		{
		case "module":
		case "version":
		case "author":
		case "copyright":
		case "tutorial":
		case "summary":
		case "description":
			jsdoc[attr] = value;
			break;

		case "returns":
			break;

		case "param":
			var param = /^\s*\{(\!?)(\w+)(\=?)\}\s*(\w+)\s*\-?\s*(.*?)$/mg.exec(value);
			attr=null;
			value = {};
			if(!jsdoc.args) jsdoc.args = {};
			value.varnull 		= param[1]!="!";
			value.vartype 		= param[2];
			value.varoptional 	= param[3]=="=";
			value.varname		= param[4];
			value.vardescr		= param[5];
			jsdoc.args[value.varname] = value;
			break;
		}

		if(attr)
			jsdoc[attr] = value;
	}

	node.comment = comment;
	node.jsdoc = jsdoc;
}


