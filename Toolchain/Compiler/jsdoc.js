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

// ==================================================================================================================================
//	       _______ ____                ____
//	      / / ___// __ \____  _____   / __ \____ ______________  _____
//	 __  / /\__ \/ / / / __ \/ ___/  / /_/ / __ `/ ___/ ___/ _ \/ ___/
//	/ /_/ /___/ / /_/ / /_/ / /__   / ____/ /_/ / /  (__  )  __/ /
//	\____//____/_____/\____/\___/  /_/    \__,_/_/  /____/\___/_/
//
// ==================================================================================================================================

function JSDocParse(node, comment, fnName)
{
	// Parse a comment and set Node properties
	// JSDoc Reference: http://usejsdoc.org/tags-type.html

	if(!comment) return null;

	var orig_comment = comment;

	// Remove comment stars '*'
	comment = comment.replace(/^[ \t]*\*[ \t]*/mg, "");

	// Split comment to '@'
	comment = comment.split("@");

	// Count params and overloaded params
	var params = 0;
	var overloaded_params = 0;
	for(var i=0; i<comment.length; i++)
	{
		if(comment[i].substr(0,5)=="param")
		{
			params++;
			if(comment[i].indexOf("|")!=-1)
				overloaded_params++;
		}
	}
	if(params>0 && overloaded_params>0)
	{
		if(overloaded_params>1)
		{
			// Found several overloaded params, this is ambiguity.
			trace("WARNING: Overloaded method ambiguity in " + fnName + " at " + node.filename + ":" + node.lineno);
		}
	}

	var jsdoc = {};
	jsdoc.description = comment[0];

	for(var i=1; i<comment.length; i++)
	{
		var rx = /(@\w+)\s([^@]+)/mg;
		var line = "@"+comment[i];

		while(match = rx.exec(line))
		{
			var attr = match[1];
			var value = match[2].trim();

			switch(attr)
			{
			case "@constructor":
				jsdoc.constructor = true;
				break;

 			case "@extends":
				jsdoc.extends = _vt(value);
				break;

			case "@module":
			case "@version":
			case "@author":
			case "@copyright":
			case "@tutorial":
			case "@summary":
			case "@description":
				jsdoc[attr] = value;
				break;

			case "@return":
				if(!/^\{[^}]+\}.*?/.test(value))
					value = "{" + value + "}";
				jsdoc.type = parseValue(value);
				break;

			case "@typedef":
				jsdoc.type = parseValue(value);
				break;

			case "@type":
				jsdoc.type = parseValue(value);
				break;

			case "@param":
				if(!jsdoc.args) jsdoc.args = {};
				var v = parseValue(value);
				jsdoc.args[v.varname] = v;
				break;
			}
		}
	}

	if(node)
	{
		node.comment = comment;
		node.jsdoc = jsdoc;
	}

	return jsdoc;

	////////////////////////////////////////////////////////////////////////////////////
	function _vt(t)
	{
		switch(t.toLowerCase())
		{
		case "object":				return "Object";
		case "global":              return "Global";
		case "array":               return "Array";
		case "function":            return "Function";

		case "string":              return "String";
		case "boolean":				return "Boolean";
		case "number":              return "Number";
		case "date":                return "Date";
		case "math":                return "Math";
		case "regexp":              return "RegExp";

		case "error":               return "Error";
		case "evalerror":           return "EvalError";
		case "rangeerror":          return "RangeError";
		case "referenceerror":      return "ReferenceError";
		case "syntaxerror":         return "SyntaxError";
		case "typeerror":           return "TypeError";

		case "arraybuffer":         return "ArrayBuffer";
		case "arraybufferview":     return "ArrayBufferView";
		case "dataview":            return "DataView";
		case "int8array":           return "Int8Array";
		case "int16array":          return "Int16Array";
		case "int32array":          return "Int32Array";
		case "int64array":          return "Int64Array";
		case "uint8array":          return "Uint8Array";
		case "uint16array":         return "Uint16Array";
		case "uint32array":         return "Uint32Array";
		case "uint64array":         return "Uint64Array";
		case "float32array":        return "Float32Array";
		case "float64array":        return "Float64Array";

		case "long":				return "Integer";

		case "xmlhttprequest":	    return "XMLHttpRequest";

		default:
			if(/\w+\./g.test(t))
			{
				t = t.replace(/\w+\./g, "");
				if(/<\w+>/g.test(t))
				{
					t = "Array<" + /<(\w+)>/g.exec(t)[1] + ">";
				}
				return _vt(t);
			}
			else
				return t;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	function parseValue(value)
	{
		var param = /^\s*\{([\w\W\n\N]*?)(\=?)\}\s*(\w+)?([\w\W\n\N]*)?$/mg.exec(value);
		if(!param)
		{
			debugger;
		}
		else
		{
			var vt = param[1].split("|")[0];
			vt = vt.replace(/[!?]/mg, ""); 		// Null or not-Null directives are ignored
			if(vt.charAt(0)=="(") vt = vt.substr(1);

			var varoptional = param[2]=="=";
			var varname = param[3];
			var vardescr = param[4];

			value = {
				varname:varname,
				vartype:null,
				varoptional:varoptional,
				varnull:false,
				varrest:false,
				vardescr:vardescr
			};

			if(_vt(vt)=="Function" || vt.indexOf("function(")==0)
			{
				// Callback Definition

				if(fnName)
				{
					value.vartype = fnName.charAt(0).toUpperCase() + fnName.substr(1) + "CallBack";
					value.callback = "callback " + value.vartype + "(); // " + vt;
				}
				else if(vt=="function(...)" || vt=="function()")
					value.vartype = "Function";
				else
				{
					//debugger;
				}
			}
			else if(/^Array\.<([^>]+)>$/.test(vt))
			{
				// Typed Array: {Array.<MyClass>}
				var subtype = /^Array\.<([^>]+)>$/.exec(vt)[1];
				if(/^function/ig.test(subtype))
					subtype = "Function";

				value.vartype = "Array<" + subtype + ">";
			}
			else if(/^(\w+)\[\]$/.test(vt))
			{
				// Typed Array: {Class[]}
				value.vartype = "Array<" + /^(\w+)\[\]$/.exec(vt)[1] + ">";
			}
			else if(vt.indexOf("Object.")==0)
			{
				// Dictionary: {Object.<key_type, value_type>}
				value.vartype = "Struct";
			}
			else if(vt.charAt(0)=='{')
			{
				// Struct: {a:number, b:string}
				value.vartype = "Struct";
			}
			else if(/^\w+\.[A-Z]\w+$/.test(vt))
			{
				// Namespace Class: a.Class
				value.vartype = vt;
			}
			else if(vt=="*")
			{
				// Any
				value.vartype = "Object";
			}
			else if(/^\.\.\.(\w+|\*)$/.exec(vt))
			{
				// Rest Params with vartype
				value.varrest = true;
				value.vartype = /^\.\.\.(\w+|\*)$/.exec(vt)[1];
				if(value.vartype=="*")
					value.vartype = "Object";
			}
			else
			{
				// Known ECMA and JSPP Types

				value.vartype = _vt(vt);

				switch(value.vartype)
				{
				case "Object":
				case "Global":
				case "Array":
				case "Function":
				case "String":
				case "Boolean":
				case "Number":
				case "Date":
				case "Math":
				case "RegExp":
				case "Error":
				case "EvalError":
				case "RangeError":
				case "ReferenceError":
				case "SyntaxError":
				case "TypeError":
				case "ArrayBuffer":
				case "ArrayBufferView":
				case "DataView":
				case "Int8Array":
				case "Int16Array":
				case "Int32Array":
				case "Int64Array":
				case "Uint8Array":
				case "Uint16Array":
				case "Uint32Array":
				case "Uint64Array":
				case "Float32Array":
				case "Float64Array":
				case "XMLHttpRequest":
				case "Float":
				case "Integer":
				case "Time":
				case "Color":
				case "State":
				case "Gradient":
				case "ByteBuffer":
					break;

				default:
					trace(vt);
				}
			}

			//trace( JSON.stringify(value) );
		}

		if(value && value.vartype)
			value.vartype = _vt(value.vartype);

		return value;
	}
}


