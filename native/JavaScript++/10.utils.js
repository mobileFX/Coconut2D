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
function compileJSPP(code)
{
	try
	{				
		var ast = narcissus.jsparse(code);	
		
		var compiler = new Compiler(ast);		
		compiler.preprocess(ast, 1);		
		compiler.compile();			
		var classes = compiler.classes;
		
		compiler = new Compiler(ast);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function ____readSourceFiles()
{
	var buff = "";
	var root = "D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/web";	
	var list =
	["/src/externs/CRL_native.js",
	"/src/externs/ECMA.jspp",
	"/src/org/Coconut2D/Constants.js",
	"/src/org/Coconut2D/Coconut.js",
	"/src/org/Coconut2D/html5/HTMLElement.jspp",
	"/src/org/Coconut2D/html5/HTMLEvents.js",
	"/src/org/Coconut2D/html5/ImageData.jspp",
	"/src/org/Coconut2D/html5/HTMLImageElement.jspp",
	"/src/org/Coconut2D/WebGL/WebGLActiveInfo.jspp",
	"/src/org/Coconut2D/WebGL/WebGLBuffer.jspp",
	"/src/org/Coconut2D/WebGL/WebGLContextAttributes.jspp",
	"/src/org/Coconut2D/WebGL/WebGLFramebuffer.jspp",
	"/src/org/Coconut2D/WebGL/WebGLProgram.jspp",
	"/src/org/Coconut2D/WebGL/WebGLRenderbuffer.jspp",
	"/src/org/Coconut2D/WebGL/WebGLShader.jspp",
	"/src/org/Coconut2D/WebGL/WebGLShaderPrecisionFormat.jspp",
	"/src/org/Coconut2D/WebGL/WebGLTexture.jspp",
	"/src/org/Coconut2D/WebGL/WebGLUniformLocation.jspp",
	"/src/org/Coconut2D/WebGL/WebGLRenderingContext.jspp",
	"/src/org/Coconut2D/anim/CocoImageSibling.jspp",
	"/src/org/Coconut2D/anim/CocoRect.jspp",
	"/src/org/Coconut2D/anim/CocoSequence.jspp",
	"/src/org/Coconut2D/anim/CocoImage.jspp",
	"/src/org/Coconut2D/anim/CocoSound.jspp",
	"/src/org/Coconut2D/anim/CocoTimeLabel.jspp",
	"/src/org/Coconut2D/anim/CocoVector.jspp",
	"/src/org/Coconut2D/anim/CocoMatrix.jspp",
	"/src/org/Coconut2D/anim/CocoKeyFrame.jspp",
	"/src/org/Coconut2D/anim/CocoTimeline.jspp",
	"/src/org/Coconut2D/anim/CocoClip.jspp",
	"/src/org/Coconut2D/anim/CocoScene.jspp",
	"/src/org/Coconut2D/anim/CocoEngineState.jspp",
	"/src/org/Coconut2D/anim/CocoEngine.jspp",
	"/src/org/Coconut2D/game/CocoSprite.jspp",
	"/src/org/Coconut2D/game/CocoSpriteActor.jspp",
	"/src/org/Coconut2D/game/CocoSpriteBonus.jspp",
	"/src/org/Coconut2D/game/CocoSpriteBullet.jspp",
	"/src/org/Coconut2D/game/CocoSpriteEnemy.jspp",
	"/src/org/Coconut2D/game/CocoSpritePlayer.jspp",
	"/src/org/Coconut2D/game/CocoSpriteVisual.jspp",
	"/src/org/Coconut2D/game/CocoTiledLayer.jspp",
	"/src/org/Coconut2D/html5/HTMLCanvasElement.jspp",
	"/src/org/Coconut2D/html5/HTMLDocument.jspp",
	"/src/org/Coconut2D/html5/HTMLWindow.jspp",
	"/src/org/Coconut2D/ui/UIView.jspp",
	"/src/org/Coconut2D/ui/UIControlView.jspp",
	"/src/org/Coconut2D/ui/UIButtonView.jspp",
	"/src/org/Coconut2D/ui/UICheckboxView.jspp",
	"/src/org/Coconut2D/ui/UILabelView.jspp",
	"/src/org/Coconut2D/ui/UINavbarView.jspp",
	"/src/org/Coconut2D/ui/UIPageView.jspp",
	"/src/org/Coconut2D/ui/UIPickerView.jspp",
	"/src/org/Coconut2D/ui/UIScrollView.jspp",
	"/src/org/Coconut2D/ui/UITabView.jspp",
	"/src/org/Coconut2D/ui/UITextView.jspp",
	"/src/usr/GameEngine.jspp",
	"/src/usr/animations/Animation1.jspp",
	"/src/usr/states/StateAnim.jspp",
	"/src/main.js"];

	for(var i=0;i<list.length;i++)
	{
		var f = root+list[i];
		var code = read(f);
		buff += "\"script_begin:///" + f + "\";\n" + code + "\n\"script_end:///" + f + "\";\n\n";
	}	
	return buff;	
}

var code = ____readSourceFiles();
var gen = compileJSPP(code);
//write("C:/Users/Admin/Desktop/coco.js", do_js_beautify(gen, 1, false, false, true));






















