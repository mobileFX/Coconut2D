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

function ExternsParserPlugin(maker)
{
	var _this = this;
	var namespaces={};
	var jsdef = mos_jsdef;

	namespaces['global'] = { classes:{}, methods:[], vars:{} };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.import = function(params)
	{
		trace("\nImporting JavaScript Externs ...");
		trace("+ Import Folder: " + params.path);

		var files = maker.FindFiles(params.path, "*.js", true);
		for(var i=0; i<files.length; i++)
		{
			trace("+ extern: " + files[i].replace(params.path, ""));
			var buff = read(files[i]);
			var ast = moz_narcissus.parse(buff, files[i]);
			_this.parse(ast);
		}

		var gen = _this.generate();

		// Append (or replace) externs to externs.jspp file
		/*
		var start_tag = "// BEGIN 3RD PARTY EXTERNS //";
		var closing_tag = "// END 3RD PARTY EXTERNS //";
		jspp_externs = ["\n", start_tag, "\n", figlet("3RD PARTY EXTERNS"), gen, "\n", closing_tag].join("");
		var externs_file = params.externs;
		var buff = read(externs_file);
		var i1 = buff.indexOf(start_tag);
		var i2 = buff.indexOf(closing_tag);
		if(i1!=-1 && i2!=-1)
		{
			i2 += closing_tag.length;
			buff = buff.replace(buff.substring(i1, i2), jspp_externs);
		}
		else
		{
			buff += jspp_externs;
		}
		maker.module(externs_file, buff);
		*/

		trace(gen);

		//trace("Externs imported in " + externs_file);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.generate = function()
	{
		var out=[];

		for(var n in namespaces)
		{
			out.push(figlet(n));
			out.push("namespace " + n + "\n{");
			var ns = namespaces[n];
			var hasVars = false;
			for(v in ns.vars)
			{
				var vv = ns.vars[v];
				if(vv.value)
					out.push("\tconst " + v + ":" + vv.vartype + "=" + vv.value + ";");
				else
					out.push("\tvar " + v + ":" + vv.vartype + ";");
				hasVars = true;
			}
			if(hasVars)
				out.push("");
			for(var m=0; m<ns.methods.length; m++)
			{
				var method = ns.methods[m];
				var args=[];
				if(method.arguments)
				{
					for(var a=0;a<method.arguments.length;a++)
					{
						var arg = method.arguments[a];
						args.push((arg.optional ? "optional ":"") + arg.name + ":" + arg.vartype);
					}
				}
				args = args.join(", ");
				ret = method.vartype ? ":" + method.vartype : "";
				out.push("\tfunction " + method.name + "(" + args + ")" + ret + " {}");
			}
			for(var c in ns.classes)
			{
				var cls = ns.classes[c];
				out.push("\n\tclass " + c + (cls.extends ? " : " + cls.extends : "") + "\n\t{");
				var hasVars = false;
				for(var v in cls.vars)
				{
					var vv = cls.vars[v];
					if(vv.value)
						out.push("\t\tpublic const " + v + ":" + vv.vartype + "=" + vv.value + ";");
					else
						out.push("\t\tpublic var " + v + ":" + vv.vartype + ";");
					hasVars = true;
				}
				if(hasVars)
					out.push("");
				for(var m=0; m<cls.methods.length; m++)
				{
					var method = cls.methods[m];
					var args=[];
					if(method.arguments)
					{
						for(var a=0;a<method.arguments.length;a++)
						{
							var arg = method.arguments[a];
							args.push((arg.optional ? "optional ":"") + arg.name + ":" + arg.vartype);
						}
					}
					args = args.join(", ");
					ret = method.vartype ? ":" + method.vartype : "";
					out.push("\t\tpublic function " + method.name + "(" + args + ")" + ret + " {}");
				}
				out.push("\t}");
			}

			out.push("}");
		}

		out = out.join("\n");

		// Replace "callback" keyword with "Callback"
		out = out.replace(/\bcallback\b/mg, "Callback");
		out = out.replace(/\bevent\b/mg, "Event");

		return out;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isClassName = function(name)
	{
		return /^[A-Z]{1}[A-Za-z0-9$]*$/.test(name) && ! /^[A-Z][A-Z0-9$]*$/.test(name);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewNameSpace = function(namespace)
	{
		return namespaces[namespace] = namespaces[namespace] || { name:namespace, classes:{}, methods:[], vars:{} };
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewClass = function(namespace, classname)
	{
		var ns = _this.NewNameSpace(namespace);
 		return ns.classes[classname] = ns.classes[classname] || {name:classname, methods:[], vars:{}};
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.parse = function(ast)
	{
		for(var c=0; c<ast.children.length; c++)
		{
			var item = ast.children[c];

			switch(item.type)
			{
			///////////////////////////////////////////////////////////////////////////////////////////////
			case jsdef.VAR:
				// Module Namespace
				//var namespace = item.name;
				//_this.NewNameSpace(namespace);
				break;

			///////////////////////////////////////////////////////////////////////////////////////////////
			case jsdef.FUNCTION:
				// Global Function
				_this.parseNamespaceMember(ast,"global",item.name,item);
				break;

			///////////////////////////////////////////////////////////////////////////////////////////////
			case jsdef.SEMICOLON:
				if(item.expression)
					_this.parseExpression(item);
				break;
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.parseExpression = function(ast)
	{
		var className = null;
		var namespace = null;

		if(ast.expression)
		{
			var signatureNode = ast.expression.children[0];
			var valueNode = ast.expression.children[1];

			switch(signatureNode.type)
			{
			//================================================================================
			case jsdef.INDEX:
				// TODO;
				//debugger;
				break;

			//================================================================================
			case jsdef.DOT:

				namespace = signatureNode.identifier_first.value;
				className = signatureNode.identifiers_list[1].value;

				if(_this.isClassName(className))
				{
					// Namespace Class
					_this.parseNamespaceClass(ast,namespace,className,signatureNode,valueNode);
				}
				else if(!_this.isClassName(namespace))
				{
					// Namespace Member
					_this.parseNamespaceMember(ast,namespace,signatureNode.identifier_last.value,valueNode);
				}
				else
				{
					// Global Class
					className=namespace;
					_this.parseNamespaceClass(ast,"global",className,signatureNode,valueNode);
				}
				break;

			//================================================================================
			case jsdef.IDENTIFIER:
				namespace = ast.expression.children[0].value;
				className = ast.expression.children[1].value;

				if(_this.isClassName(className))
				{
					// Namespace Class
					var cls = _this.NewClass(namespace,className);
				}
				else if(_this.isClassName(namespace))
				{
					// Global Class Member
					var varName = valueNode.value;
					className = namespace;
					_this.parseVar(ast, varName, "global", className);
				}
				else
				{
					// Static Field (?)
					var varName = className;
					_this.parseVar(ast, varName, namespace, null, null);
				}
				break;
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.parseNamespaceMember = function(ast, namespace,memberName,valueNode)
	{
		var ns = _this.NewNameSpace(namespace);

		switch(valueNode.type)
		{
		//--------------------------------------------
		case jsdef.FUNCTION:
			_this.parseFunction(ast, memberName, valueNode, ns);
			break;

		//--------------------------------------------
		case jsdef.NUMBER:
		case jsdef.UNARY_MINUS:
		case jsdef.TRUE:
		case jsdef.FALSE:
		case jsdef.STRING:
			_this.parseVar(ast, memberName, namespace, null, valueNode);
			break;

		case jsdef.OBJECT_INIT:
			_this.parseVar(ast, memberName, namespace, null, null);
			break;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.parseNamespaceClass = function(ast, namespace,classname,signatureNode,valueNode)
	{
		var ns = _this.NewNameSpace(namespace);
		var cls = _this.NewClass(namespace,classname);

		switch(valueNode.type)
		{
		//--------------------------------------------
		case jsdef.FUNCTION:
			switch(signatureNode.identifiers_list.length)
			{
				case 2:
				{
					// Constructor ()
					var fnName = signatureNode.identifier_last.value;
					if(fnName==classname) fnName = "Constructor";
					_this.parseFunction(ast, fnName, valueNode, cls);
					break;
				}
				case 4:
				{
					// Instance Function: Namespace.Class.prototype.FnNanme = function() {}
					var fnName = signatureNode.identifiers_list[3].ast.value;
					_this.parseFunction(ast, fnName, valueNode, cls);
					break;
				}
				case 3:
				{
					// Static Function: Namespace.Class.FnNanme = function() {}
					var fnName = signatureNode.identifiers_list[2].ast.value;
					_this.parseFunction(ast, fnName, valueNode, cls);
					break;
				}
			}
			break;

		//--------------------------------------------
		case jsdef.IDENTIFIER:
			var varName = valueNode.value;
			_this.parseVar(ast, varName, namespace, classname, null);
			break;

		//--------------------------------------------
		case jsdef.NUMBER:
		case jsdef.UNARY_MINUS:
		case jsdef.TRUE:
		case jsdef.FALSE:
		case jsdef.STRING:
			var varName = signatureNode.identifier_last.value;
			_this.parseVar(ast, varName, namespace, classname, valueNode);
			break;

		//--------------------------------------------
		case jsdef.OBJECT_INIT:
		case jsdef.DOT:
			var varName = signatureNode.identifier_last.value;
			_this.parseVar(ast, varName, namespace, classname, valueNode);
			break;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.parseFunction = function(ast, fnName, fnNode, cls)
	{
		// Get JSDoc Comments and Parse it
		var p = ast;
		while(p && !p.blockComments){p=p.parent;}
		var comments = p ? p.blockComments[p.blockComments.length-1] : "";
		var jsdoc = JSDocParse(ast, comments, fnName);

		// Function is Constructor?
		if(jsdoc && jsdoc.contructor) fnName="Constructor";

		var methods = cls['methods'] = cls['methods'] || [];
		var vartype = null;

		// Check for overloaded method
		var method = {name:fnName, vartype:vartype, arguments:[]};
		method.vartype = jsdoc && jsdoc.type ? jsdoc.type.vartype : null;
		var arguments = method['arguments'] = method['arguments'] || [];

		for(var p=0;p<fnNode.params.length;p++)
		{
			var param = fnNode.params[p];
			var vartype = jsdoc && jsdoc.args && jsdoc.args[param] ? jsdoc.args[param].vartype : "Object";
			var optional = jsdoc && jsdoc.args && jsdoc.args[param] ? jsdoc.args[param].varoptional : false;
			arguments.push( {name:param, vartype:vartype, optional:optional} );
		}

		if(jsdoc && jsdoc.extends)
		{
			cls.extends = jsdoc.extends;
		}

		methods.push(method);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.parseVar = function(ast, varName, namespace, classname, valueNode)
	{
		var p = ast;
		while(p && !p.blockComments){p=p.parent;}
		var comments = p ? p.blockComments[p.blockComments.length-1] : "";
		var jsdoc = JSDocParse(ast, comments, varName);

		var ns = _this.NewNameSpace(namespace);
		var cls = classname ? _this.NewClass(namespace, classname) : ns;
		var vars = cls['vars'] = cls['vars'] || {};
		var vartype = jsdoc && jsdoc.type ? jsdoc.type.vartype : "String";
		var value = null;

		if(valueNode)
		{
			if(valueNode.type==jsdef.UNARY_MINUS)
			{
				value = "-" + valueNode.children[0].value;
			}
			else
			{
				value = valueNode.value;
			}
		}

		var v = vars[varName] = vars[varName] || {name:varName, vartype:vartype, value:value};
	};
}
