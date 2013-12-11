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
function TRACE(n)
{
	trace(JSON.stringify( stripNodeFromCyclicReferences(n)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function RxReplace(buff, patt, opts, repl)
{
	var rx = new RegExp(patt, opts);
	var res = buff.replace(rx, repl);
	return res;
} 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function formatCPP(buff)
{  
	buff = RxReplace(buff, "[\s\t\n\r]+\\{[\s\t\n\r]+\\};", "mg", "{};");		
	buff = RxReplace(buff, "Array\\s*\\<\\s*([\\w\\*]+)\\s*\\>\\s*", "mg", "Array<$1> ");			 
	buff = RxReplace(buff, "Dictionary \\< (\\w+) \\> ", "mg", "Dictionary<$1> ");
	buff = RxReplace(buff, "\\bFloat\\b", "mg", "float");			 			 
	buff = RxReplace(buff, "\\bInteger\\b", "mg", "int");
	buff = RxReplace(buff, "\\bBoolean\\b", "mg", "bool");
	buff = RxReplace(buff, "\\bString\\b", "mg", "std::string");
	buff = RxReplace(buff, "\\s*//<<(.*)>>//", "mg", "$1");
	buff = RxReplace(buff, "\\bMath.floor\\(", "mg", "std::floor(");
	buff = RxReplace(buff, "\\bMath.min\\(", "mg", "std::min(");
	buff = RxReplace(buff, "\\bMath.max\\(", "mg", "std::max(");
	buff = RxReplace(buff, "_ENUM\\.(\\w+)", "mg", "_ENUM::$1");		
	return buff;
}
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function compile_jspp(code, infolder, outfolder)
{
	try
	{              		
		if(infolder)
		{
			var externs = read(infolder+"/../../native/JavaScript++/ECMA.jspp");	
			code = "\"script_begin:///externs.jspp\";\n" + externs + "\n\"script_end:///externs.jspp\";\n\n" + code;			
		}
						
		var ast = narcissus.jsparse(code);	
		
		var compiler = new Compiler(ast, infolder, outfolder);		
		compiler.preprocess(ast, 1);		
		compiler.compile();			
		var classes = compiler.classes;
		
		compiler = new Compiler(ast, infolder, outfolder);
		compiler.classes = classes;
		compiler.preprocess(ast, 2);	
		var gen = compiler.compile();			
				 		
		//jsppCallback("errors", 			____JSONtoXML(c.errors));
		//jsppCallback("warnings", 		____JSONtoXML(c.warnings));				
		//jsppCallback("debugSymbols", 	____JSONtoXML(c.debugSymbols));				
		//jsppCallback("codeSymbols", 	____JSONtoXML(c.codeSymbols));
		//jsppCallback("codeScopes", 		____JSONtoXML(c.codeScopes));		
			
		trace("Code generation Done.");
		
		return gen;		
	}
	catch(e)
	{
		trace("ERROR: " +e);
	}
}

