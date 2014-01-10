 ///http://jsonviewer.stack.hu/

if(!this['jsppCallback']) this.jsppCallback = function(){};
if(!this['window']) this.window = {};
if(!this['console']) console = { log:function(m){/*trace("@@"+m)*/} }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function ____JSONtoXML(json, rootNode)
{
	if(!rootNode) rootNode = "XML";

	var ____isArray 	= function(obj) {return (Object.prototype.toString.apply(obj) === '[object Array]');}
	var ____isObject	= function(obj) {return (Object.prototype.toString.apply(obj) === '[object Object]');}
	var ____isFunction	= function(obj) {return (Object.prototype.toString.apply(obj) === '[object Function]');}

	var obj = (typeof json == 'string') ? JSON.parse(json) : json;

	var xml = "<" + rootNode + ">" +
			  __JSONtoXML(obj) +
			  "</" + rootNode + ">";

	function __addItem(v,k)
	{
		var x = '';

		if(v==null)
			x= "<" + k + ">null</" + k + ">";
		else
		{
			switch(typeof v)
			{
				case 'object':
					x= "<" + k + ">" + __JSONtoXML(v) + "</" + k + ">";
					break;

				case 'string':
					x= "<" + k + "><![CDATA[" + v + "]]></" + k + ">";
					break;

				default:
					x= "<" + k + ">" + v + "</" + k + ">";
					break;
			}
		}

		return x;
	}

	function __JSONtoXML(obj)
	{
		var x = '';

		if(____isArray(obj))
		{
			for(var i=0;i<obj.length;i++)
			{
				var v = obj[i];
				var k = '_' + i;
				x+= __addItem(v,k);
			}
		}
		else
		{
			for(var k in obj)
			{
				var v = obj[k];
				if(!isNaN(k)) k = '_' + k;
				x+= __addItem(v,k);
			}
		}

		return x;
	}

	return xml;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function RxReplace(buff, patt, opts, repl)
{
	var rx = new RegExp(patt, opts);
	var res = buff.replace(rx, repl);
	return res;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function formatCPP(buff)
{
	buff = RxReplace(buff, "[\s\t\n\r]+\\{[\s\t\n\r]+\\};", "mg", "{};");
	buff = RxReplace(buff, "Array\\s*\\<\\s*([\\w\\*]+)\\s*\\>\\s*", "mg", "Array<$1> ");
	buff = RxReplace(buff, "Dictionary \\< (\\w+) \\> ", "mg", "Dictionary<$1> ");
	buff = RxReplace(buff, "\\bFloat\\b", "mg", "float");
	buff = RxReplace(buff, "\\bInteger\\b", "mg", "int");
	buff = RxReplace(buff, "\\bBoolean\\b", "mg", "bool");
	buff = RxReplace(buff, "\\s*//<<(.*)>>//", "mg", "$1");
	buff = RxReplace(buff, "\\bMath.floor\\(", "mg", "std::floor(");
	buff = RxReplace(buff, "\\bMath.min\\(", "mg", "std::min(");
	buff = RxReplace(buff, "\\bMath.max\\(", "mg", "std::max(");
	buff = RxReplace(buff, "\\bMath.sin\\(", "mg", "std::sin(");
	buff = RxReplace(buff, "\\bMath.cos\\(", "mg", "std::cos(");
	buff = RxReplace(buff, "\\bMath.abs\\(", "mg", "std::abs(");
	buff = RxReplace(buff, "_ENUM\\.(\\w+)", "mg", "_ENUM::$1");
	return buff;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function compile_jspp(code, infolder, outfolder)
{
	try
	{
		// Append externs and ECMA classes
		if(infolder)
		{
			var file = infolder.split("/");
			file.splice(file.length-2,2);
			file = file.join("/") + "/native/JavaScript++/externs.jspp";
			var externs = read(file);
			file = infolder + "/ECMA/externs.jspp";
			code = "\"script_begin:///" + file + "\";\n" + externs + "\n\"script_end:///" + file + "\";\n" + code;
		}

		// Parse source code
		narcissus.__messages = true;
		narcissus.__cpp = false;
		var ast = narcissus.jsparse(code);

		// Compile ast
		var compiler = new Compiler(ast, infolder, outfolder, true, null);
		compiler.compile();

		trace("JavaScript Code generation Done.");
	}
	catch(e)
	{
		//trace("ERROR: " +e);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function compile_cpp(code, infolder, outfolder)
{
	try
	{
		// Append externs and ECMA classes
		if(infolder)
		{
			var file = infolder.split("/");
			file.splice(file.length-2,2);
			file = file.join("/") + "/native/JavaScript++/externs.jspp";
			var externs = read(file);
			file = infolder + "/ECMA/externs.jspp";
			code = "\"script_begin:///" + file + "\";\n" + externs + "\n\"script_end:///" + file + "\";\n" + code;
		}

		// Parse source code
		narcissus.__messages = true;
		narcissus.__cpp = true;
		var ast = narcissus.jsparse(code);

		// Compile ast to JavaScript to build symbol tables


		var compiler = new Compiler(ast, infolder, null, false, null);
		compiler.compile();

		// Compile ast to C++
		var compiler = new CPPCompiler(ast, infolder, outfolder);
		compiler.compile();

		// Update Coconut2D.hpp
		jsppCallback("coconut2d.hpp", "", "", 0, 0, compiler.getClassList());

		trace("C++ Code generation Done.");
	}
	catch(e)
	{
		trace("ERROR: " +e);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function parse_jspp(code, className)
{
	try
	{
		// Parse source code
		narcissus.__messages = false;
		narcissus.__cpp = false;
		var ast = narcissus.jsparse(code);

		// Compile ast
		var compiler = new Compiler(ast, null, null, true, className);
		compiler.compile();
	}
	catch(e)
	{
		trace("ERROR: " +e);
	}
}











