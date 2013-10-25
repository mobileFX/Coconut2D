// ==================================================================================================================================
//	   _____                 __          __   ______      __    __   
//	  / ___/__  ______ ___  / /_  ____  / /  /_  __/___ _/ /_  / /__ 
//	  \__ \/ / / / __ `__ \/ __ \/ __ \/ /    / / / __ `/ __ \/ / _ \
//	 ___/ / /_/ / / / / / / /_/ / /_/ / /    / / / /_/ / /_/ / /  __/
//	/____/\__, /_/ /_/ /_/_.___/\____/_/    /_/  \__,_/_.___/_/\___/ 
//	     /____/                                                      
// ==================================================================================================================================	
 
function SymbolTablePlugin(compiler)
{     
	var _this = this;
	var _compiler = compiler;	
     
	this.scopeTable = [];    
	this.debugSymbols = [];	
	this.codeSymbols = 
	[
		  {"type":"CLASS","proto":true,"ecma":true,"name":"Object","fields":[],"methods":[{"name":"toString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toLocaleString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"valueOf","type":"FUNCTION","datatype":"Object","parameters":[],"access":"public","static":false},{"name":"hasOwnProperty","type":"FUNCTION","datatype":"Boolean","parameters":[{"name":"name","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"isPrototypeOf","type":"FUNCTION","datatype":"Boolean","parameters":[{"name":"o","type":"ARGUMENT","restParameter":false,"datatype":"Object"}],"access":"public","static":false},{"name":"propertyIsEnumerable","type":"FUNCTION","datatype":"Boolean","parameters":[{"name":"name","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"String","bases":["Object"],"fields":[{"name":"length","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"fromCharCode","type":"FUNCTION","datatype":"String","parameters":[{"name":"charCode","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"charAt","type":"FUNCTION","datatype":"String","parameters":[{"name":"position","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"charCodeAt","type":"FUNCTION","datatype":"Number","parameters":[{"name":"position","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"concat","type":"FUNCTION","datatype":"String","parameters":[{"name":"value","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"indexOf","type":"FUNCTION","datatype":"Number","parameters":[{"name":"searchString","type":"ARGUMENT","restParameter":false,"datatype":"String"},{"name":"startPosition","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"lastIndexOf","type":"FUNCTION","datatype":"Number","parameters":[{"name":"searchString","type":"ARGUMENT","restParameter":false,"datatype":"String"},{"name":"startPosition","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"localeCompare","type":"FUNCTION","datatype":"Number","parameters":[{"name":"otherString","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"match","type":"FUNCTION","datatype":"Array","parameters":[{"name":"regexp","type":"ARGUMENT","restParameter":false,"datatype":"RegExp"}],"access":"public","static":false},{"name":"replace","type":"FUNCTION","datatype":"String","parameters":[{"name":"regexp","type":"ARGUMENT","restParameter":false,"datatype":"RegExp"},{"name":"replaceValue","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"search","type":"FUNCTION","datatype":"Number","parameters":[{"name":"regexp","type":"ARGUMENT","restParameter":false,"datatype":"RegExp"}],"access":"public","static":false},{"name":"slice","type":"FUNCTION","datatype":"String","parameters":[{"name":"start","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"end","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"split","type":"FUNCTION","datatype":"Array","parameters":[{"name":"separator","type":"ARGUMENT","restParameter":false,"datatype":"String"},{"name":"limit","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"substring","type":"FUNCTION","datatype":"String","parameters":[{"name":"start","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"end","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"toLowerCase","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toLocaleLowerCase","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toUpperCase","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toLocaleUpperCase","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Number","bases":["Object"],"fields":[{"name":"MIN_VALUE","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"MAX_VALUE","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"NEGATIVE_INFINITY","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"POSITIVE_INFINITY","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"toFixed","type":"FUNCTION","datatype":"String","parameters":[{"name":"fractionDigits","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"toExponential","type":"FUNCTION","datatype":"String","parameters":[{"name":"fractionDigits","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"toPrecision","type":"FUNCTION","datatype":"String","parameters":[{"name":"fractionDigits","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Boolean","bases":["Object"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Array","bases":["Object"],"fields":[{"name":"length","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"concat","type":"FUNCTION","datatype":"Array","parameters":[{"name":"args","type":"ARGUMENT","restParameter":false,"datatype":"Array"}],"access":"public","static":false},{"name":"join","type":"FUNCTION","datatype":"Array","parameters":[{"name":"seperator","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"pop","type":"FUNCTION","datatype":"Array","parameters":[],"access":"public","static":false},{"name":"push","type":"FUNCTION","datatype":"Object","parameters":[{"name":"args","type":"ARGUMENT","restParameter":false,"datatype":"Object"}],"access":"public","static":false},{"name":"reverse","type":"FUNCTION","datatype":"Array","parameters":[],"access":"public","static":false},{"name":"shift","type":"FUNCTION","datatype":"Array","parameters":[],"access":"public","static":false},{"name":"slice","type":"FUNCTION","datatype":"Array","parameters":[{"name":"start","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"end","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"sort","type":"FUNCTION","datatype":"Array","parameters":[{"name":"funct","type":"ARGUMENT","restParameter":false,"datatype":"Function"}],"access":"public","static":false},{"name":"splice","type":"FUNCTION","datatype":"Array","parameters":[{"name":"start","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"deletecount","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"items","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"unshift","type":"FUNCTION","datatype":"Array","parameters":[{"name":"start","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"forEach","type":"FUNCTION","datatype":"Array","parameters":[{"name":"item","type":"ARGUMENT","restParameter":false,"datatype":"Object"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Inte32Array","bases":["Array"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Float32Array","bases":["Array"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Function","bases":["Object"],"fields":[{"name":"length","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"apply","type":"FUNCTION","datatype":"Object","parameters":[{"name":"thisArg","type":"ARGUMENT","restParameter":false,"datatype":"Object"},{"name":"argArray","type":"ARGUMENT","restParameter":false,"datatype":"Array"}],"access":"public","static":false},{"name":"call","type":"FUNCTION","datatype":"Object","parameters":[{"name":"thisObject","type":"ARGUMENT","restParameter":false,"datatype":"Object"},{"name":"args","type":"ARGUMENT","restParameter":false,"datatype":"Array"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Date","bases":["Object"],"fields":[],"methods":[{"name":"UTC","type":"FUNCTION","datatype":"Number","parameters":[{"name":"hour","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"min","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"parse","type":"FUNCTION","datatype":"Number","parameters":[{"name":"string","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"toDateString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toTimeString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toLocaleString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toLocaleDateString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"toLocaleTimeString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false},{"name":"valueOf","type":"FUNCTION","datatype":"Object","parameters":[],"access":"public","static":false},{"name":"getFullYear","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getTime","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCFullYear","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getMonth","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCMonth","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getDate","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCDate","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getDay","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCDay","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getHours","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCHours","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getMinutes","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCMinutes","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getSeconds","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCSeconds","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getMilliseconds","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getUTCMilliseconds","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"getTimezoneOffset","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"setTime","type":"FUNCTION","datatype":"Number","parameters":[{"name":"value","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setMilliseconds","type":"FUNCTION","datatype":"Number","parameters":[{"name":"value","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCMilliseconds","type":"FUNCTION","datatype":"Number","parameters":[{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setSeconds","type":"FUNCTION","datatype":"Number","parameters":[{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCSeconds","type":"FUNCTION","datatype":"Number","parameters":[{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setMinutes","type":"FUNCTION","datatype":"Number","parameters":[{"name":"min","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCMinute","type":"FUNCTION","datatype":"Number","parameters":[{"name":"min","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setHours","type":"FUNCTION","datatype":"Number","parameters":[{"name":"hour","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"min","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCHours","type":"FUNCTION","datatype":"Number","parameters":[{"name":"hour","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"min","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"sec","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"ms","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setDate","type":"FUNCTION","datatype":"Number","parameters":[{"name":"date","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCDate","type":"FUNCTION","datatype":"Number","parameters":[{"name":"date","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setMonth","type":"FUNCTION","datatype":"Number","parameters":[{"name":"month","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"date","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCMonth","type":"FUNCTION","datatype":"Number","parameters":[{"name":"month","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"date","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setFullYear","type":"FUNCTION","datatype":"Number","parameters":[{"name":"year","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"month","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"date","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"setUTCFullYear","type":"FUNCTION","parameters":[{"name":"year","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"month","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"date","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"toUTCString","type":"FUNCTION","datatype":"String","parameters":[],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Global","bases":["Object"],"fields":[{"name":"NaN","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"Infinity","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"eval","type":"FUNCTION","datatype":"Object","parameters":[{"name":"s","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"parseInt","type":"FUNCTION","datatype":"Number","parameters":[{"name":"s","type":"ARGUMENT","restParameter":false,"datatype":"String"},{"name":"radix","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"parseFloat","type":"FUNCTION","datatype":"Number","parameters":[{"name":"s","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"escape","type":"FUNCTION","datatype":"String","parameters":[{"name":"s","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"unescape","type":"FUNCTION","datatype":"String","parameters":[{"name":"s","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"isNaN","type":"FUNCTION","datatype":"Boolean","parameters":[{"name":"number","type":"ARGUMENT","restParameter":false,"datatype":"Object"}],"access":"public","static":false},{"name":"isFinite","type":"FUNCTION","datatype":"Boolean","parameters":[{"name":"number","type":"ARGUMENT","restParameter":false,"datatype":"Object"}],"access":"public","static":false},{"name":"decodeURI","type":"FUNCTION","datatype":"String","parameters":[{"name":"encodedURI","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"decodeURIComponent","type":"FUNCTION","datatype":"String","parameters":[{"name":"uriComponent","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"encodeURIComponent","type":"FUNCTION","datatype":"String","parameters":[{"name":"uriComponent","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"encodeURI","type":"FUNCTION","datatype":"String","parameters":[{"name":"URI","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Math","bases":["Object"],"fields":[{"name":"E","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"LN10","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"LN2","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"LOG2E","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"LOG10E","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"PI","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"SQRT1_2","type":"FIELD","datatype":"Number","access":"public","static":false},{"name":"SQRT2","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"abs","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"acos","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"asin","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"atan","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"atan2","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"y","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"ceil","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"cos","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"exp","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"floor","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"log","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"max","type":"FUNCTION","datatype":"Number","parameters":[{"name":"a","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"b","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"min","type":"FUNCTION","datatype":"Number","parameters":[{"name":"a","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"b","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"pow","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"y","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"random","type":"FUNCTION","datatype":"Number","parameters":[],"access":"public","static":false},{"name":"round","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"sin","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"sqrt","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"tan","type":"FUNCTION","datatype":"Number","parameters":[{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"RegExp","bases":["Object"],"fields":[{"name":"source","type":"FIELD","datatype":"String","access":"public","static":false},{"name":"global","type":"FIELD","datatype":"Boolean","access":"public","static":false},{"name":"ignoreCase","type":"FIELD","datatype":"Boolean","access":"public","static":false},{"name":"multiline","type":"FIELD","datatype":"Boolean","access":"public","static":false},{"name":"lastIndex","type":"FIELD","datatype":"Number","access":"public","static":false}],"methods":[{"name":"exec","type":"FUNCTION","datatype":"Array","parameters":[{"name":"string","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false},{"name":"test","type":"FUNCTION","datatype":"Boolean","parameters":[{"name":"string","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false}]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"Error","bases":["Object"],"fields":[{"name":"name","type":"FIELD","datatype":"String","access":"public","static":false},{"name":"message","type":"FIELD","datatype":"String","access":"public","static":false}],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"EvalError","bases":["Error"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"RangeError","bases":["Error"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"ReferenceError","bases":["Error"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"SyntaxError","bases":["Error"],"fields":[],"methods":[]}
		, {"type":"CLASS","proto":true,"ecma":true,"name":"TypeError","bases":["Error"],"fields":[],"methods":[]}		
		, {"type":"CLASS","proto":true,"coco":true,"name":"CocoFont","bases":["Object"],"fields":[],"methods":[{"name":"fillText","type":"FUNCTION","datatype":"null","parameters":[{"name":"buffer","type":"ARGUMENT","restParameter":false,"datatype":"ArrayBuffer"},{"name":"width","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"text","type":"ARGUMENT","restParameter":false,"datatype":"String"},{"name":"x","type":"ARGUMENT","restParameter":false,"datatype":"Number"},{"name":"y","type":"ARGUMENT","restParameter":false,"datatype":"Number"}],"access":"public","static":false},{"name":"measureText","type":"FUNCTION","datatype":"Number","parameters":[{"name":"text","type":"ARGUMENT","restParameter":false,"datatype":"String"}],"access":"public","static":false}]}
	];  
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.getClassSymbol = function(id)
	{
		for(i in _this.codeSymbols)
		{
			if(!isFinite(i)) continue;
			var cls = _this.codeSymbols[i];
			if(cls.type=="CLASS" && cls.name==id)
				return cls;
		}		
	};
	     
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.getMemberSymbol = function(cls, id)
	{
		var i,L;
		
		for(i=0,L=cls.fields.length;i<L;i++)
			if(cls.fields[i].name==id)
				return cls.fields[i];

		for(i=0,L=cls.methods.length;i<L;i++)
			if(cls.methods[i].name==id || cls.methods[i].name=="__set_"+id || cls.methods[i].name=="__get_"+id)			
				return cls.methods[i];
				
		if(cls.bases)
		{
			for(i in cls.bases)
			{
				if(!isFinite(i)) continue;
				var base = _this.getClassSymbol(cls.bases[i]);
				if(!base) return null;
				var symbol = _this.getMemberSymbol(base, id);
				if(symbol) return symbol;
			}
		}	
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.getSymbol = function(Node)
	{
		var path = ".*{.scopeId === " + Node.scopeId + "}";
		var list = JSPath.apply(path, _this.scopeTable);
	};
	     
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertScope = function(id, node)
	{ 
		var tokenType = node.type;
		var isGlobalScope = _compiler.scopeChain.length == 1;		
		
		id = node[0] ? node[0].scopeId : node.scopeId;
		
		if (tokenType === jsdef.SCRIPT && !isGlobalScope) 
			tokenType = jsdef.FUNCTION;
		
		var offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);			
		this.scopeTable.push({
			file		: _compiler.currFile || undefined							  
			, line		: node.lineno - _compiler.currFileStartLine
			, start		: node.start - offset
			, end		: node.end - offset
			, length	: node.end -node.start 
			, scopeId	: id				  
			, name		: isGlobalScope ? "__GLOBAL__" : node.name
			, token		: tokenType				
			, global	: _compiler.isGlobalScope()
		});
	};
													
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.getSymbolTableScopeId = function() 
	{
		var currentScope = _compiler.CurrentScope(), scopeId = -1;
		if(currentScope)
		{
			switch (currentScope.type) 
			{
				case jsdef.SCRIPT:
				case jsdef.BLOCK:
					return currentScope.scopeId;
				case jsdef.CLASS:
					return currentScope.body.scopeId;
			}
		}
		return -1;
	};  
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.NewDebugSymbol = function(symbolType, node, identifier, symbol)
	{		
		var offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);		
		var Symbol = {		
			file	: _compiler.currFile || undefined,			
			type	: symbolType,																
			lineno	: node.lineno - _compiler.currFileStartLine,
			start	: node.start - offset,
			end		: node.end - offset,
			scopeId : node.scopeId,
			name	: identifier,
			symbol	: symbol			
		};
		_this.debugSymbols.push(Symbol);		
		return Symbol;
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.NewCodeVariableSymbol = function(varItem, qualifier)
	{		           		
		if(!varItem.vartype) varItem.vartype = _this.detectDataType(varItem);		
		if(!varItem.vartype) return;                                                                                    		
		var offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(varItem.lineno-_compiler.currFileStartLine)+1);
		var name = varItem.identifier || varItem.name;
		var qualifier = qualifier || (name.indexOf("_ENUM")!=-1 ? "ENUM" : undefined);
		var global = qualifier && qualifier=="ARGUMENT" ? false : _compiler.isGlobalScope(); 
		var scopeId = varItem.scopeId;                                             		
		var access = "public";
		if(varItem.private) access = "private";
		if(varItem.protected) access = "protected";
		
		var Symbol = {		
			file		: _compiler.currFile || undefined,			
			type		: "VAR",		
			qualifier	: qualifier,
			class		: _compiler.currentClass || undefined,				 
			classId		: _compiler.currentClass ? _compiler.classId : undefined,
			lineno		: varItem.lineno - _compiler.currFileStartLine,
			start		: varItem.start - offset,
			end			: varItem.end - offset,
			scopeId		: scopeId,
			global		: global,
			access		: access,
			name		: name,
			datatype	: varItem.vartype,
			value		: varItem._value
		}; 
				
		return _this.insertCodeSymbol(Symbol);		
	}; 
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertCodeSymbol = function(Symbol)
	{
		//Check if symbol was defined during first pass
		var i,s,found=-1;
		for(i in _this.codeSymbols)
		{			                       
			if(!isFinite(i)) continue;
			s = _this.codeSymbols[i];
			if(s.file==Symbol.file && s.name==Symbol.name && s.type==Symbol.type)
			{ 
				found=i;
				break;
			}
		} 
		if(found!=-1 && s.ecma) return s;
		
		if(found!=-1) 
			_this.codeSymbols[found] = Symbol;
		else	
			_this.codeSymbols.push(Symbol);				
			
		return Symbol;
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertVariable = function(varItem) 
	{
		if(varItem._symbol && varItem.identifier!=varItem._symbol)
		{				
			_this.NewDebugSymbol("IDENTIFIER", varItem, varItem.identifier, varItem._symbol);	
		}		
		_this.NewCodeVariableSymbol(varItem);
	};
			
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertBlockVariable = function(node, newIdentifier, srcIdentifier) 
	{		
		if(srcIdentifier!=newIdentifier)
		{
			_this.NewDebugSymbol("IDENTIFIER", node, srcIdentifier, newIdentifier);
		}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertIdentifier = function(node, out, access) 
	{	
		var symbol = out.join("");
		if(node.value && node.value!=symbol)	
		{			
			_this.NewDebugSymbol("IDENTIFIER", node, node.value, symbol);
		}
	};
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertReference = function(node, out)
	{			
		if(node[0] && node[0].value=="prototype")
		{
			//_this.insertPrototypeMember(node, out);
		}
		else
		{
			if(node.value && node.value!="prototype")
				_this.NewDebugSymbol("REFERENCE", node, node.value, out.join(""));
		}
	};
		
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertFunction = function(node)
	{
		if(!node.name) return;
		
		var offset = 0;
		var scopeId = node.scopeId; //_this.getSymbolTableScopeId();
		
		// Arguments
		var paramsList = [];
		for (var i=0, len=node.paramsList.length; i<len; i++) 
		{ 
			offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.paramsList[i].lineno-_compiler.currFileStartLine)+1);
			paramsList.push({
				  name: node.paramsList[i].value
				, type: "ARGUMENT"
				, lineno: node.paramsList[i].lineno - _compiler.currFileStartLine
				, start: node.paramsList[i].start  - offset
				, end: node.paramsList[i].end - offset
				, restParameter: !!node.paramsList[i].restParameter				
				, scopeId: scopeId
				, datatype: node.paramsList[i].vartype || undefined
			});			 
			_this.NewCodeVariableSymbol(node.paramsList[i],"ARGUMENT");
		}		
		
		//Record Function Symbol
		var access = "public";
		if(node.private) access = "private";
		if(node.protected) access = "protected";
		
		offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);				
		var FunctionSymbol = {		
			  file			: _compiler.currFile || undefined
			, type			: "FUNCTION"
			, qualifier		: undefined
			, class			: _compiler.currentClass || undefined
			, classId		: _compiler.currentClass ? _compiler.classId : undefined
			, lineno		: node.lineno - _compiler.currFileStartLine
			, start			: node.start - offset
			, end			: node.end - offset
			, scopeId		: scopeId
			, global		: _compiler.isGlobalScope()
			, access		: access
			, name			: node.name
			, datatype		: node.returntype || undefined
			, value			: undefined
			, paramsList	: paramsList
		};
		
		_this.insertCodeSymbol(FunctionSymbol);		
	};
		
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertClass = function(node) 
	{
		var offset=0;

		//Fields
		var classFields = [];
		if (node.body.varDecls) {
			for (var i = 0, len = node.body.varDecls.length; i < len; i++) {
				for (var j = 0; j < node.body.varDecls[i].length; j++) {
					
					var access = "public";
					if(node.body.varDecls[i]["private"]) access = "private";
					if(node.body.varDecls[i]["protected"]) access = "protected";
					offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.body.varDecls[i][j].lineno-_compiler.currFileStartLine)+1);
					
					classFields.push({
						  name: node.body.varDecls[i][j].name
						, type: "FIELD"
						, lineno: node.body.varDecls[i][j].lineno - _compiler.currFileStartLine
						, start: node.body.varDecls[i][j].start - offset
						, end: node.body.varDecls[i][j].end - offset						
						, scopeId : node.body.varDecls[i][j].scopeId
						, datatype: node.body.varDecls[i][j].vartype
						, access: access
						, "static": node.body.varDecls[i]["static"]
					}); 
				}
			}
		}
		
		//Methods and nested Classes
		var classMethods = [];
		var nestedClasses = [];
		if (node.body.funDecls) {
			for (var i = 0, len = node.body.funDecls.length; i < len; i++) {
				if (node.body.funDecls[i].type === jsdef.FUNCTION || node.body.funDecls[i].type === jsdef.PROPERTY) {
					var paramsList = [], methodParams = node.body.funDecls[i].paramsList;
					for (var j=0, _len=methodParams.length; j<_len; j++) {												
						offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(methodParams[j].lineno-_compiler.currFileStartLine)+1);
						paramsList.push({
							  name: methodParams[j].value
							, type: "ARGUMENT"
							, lineno: methodParams[j].lineno - _compiler.currFileStartLine
							, start: methodParams[j].start - offset
							, end: methodParams[j].end - offset
							, scopeId: methodParams[j].scopeId
							, restParameter: !!methodParams[j].restParameter
							, datatype: methodParams[j].vartype || undefined
						}); 
						_this.NewCodeVariableSymbol(methodParams[j],"ARGUMENT");						
					}
					
					offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.body.funDecls[i].lineno-_compiler.currFileStartLine)+1);
					var access = "public";
					if(node.body.funDecls[i]["private"]) access = "private";
					if(node.body.funDecls[i]["protected"]) access = "protected";
					
					if(node.body.funDecls[i].type === jsdef.PROPERTY)
					{  
						var prop = {
							  name: node.body.funDecls[i].value
							, type: "PROPERTY"							
							, getter: node.body.funDecls[i].getter===true
							, setter: node.body.funDecls[i].setter===true
							, lineno: node.body.funDecls[i].lineno - _compiler.currFileStartLine
							, start: node.body.funDecls[i].start - offset
							, end: node.body.funDecls[i].end - offset						
							, scopeId : node.body.funDecls[i].scopeId
							, datatype: node.body.funDecls[i].vartype
							, access: access							
							, "static": node.body.funDecls[i]["static"]
						};
						
						propExists = false;					
						for(p in classFields)
						{
							if(!isFinite(p)) continue;
							if(classFields[p].type=="PROPERTY" && classFields[p].name==prop.name)
							{
								if(node.body.funDecls[i].getter) classFields[p].getter = true;
								if(node.body.funDecls[i].setter) classFields[p].setter = true;
								propExists=true;
							}
						} 
						
						if(!propExists)
							classFields.push(prop);
						
						continue;
					}					
					
					classMethods.push({
						  name: node.body.funDecls[i].name
						, type: "FUNCTION"
						, lineno: node.body.funDecls[i].lineno - _compiler.currFileStartLine
						, start: node.body.funDecls[i].start - offset
						, end: node.body.funDecls[i].end - offset
						, scopeId: node.body.funDecls[i].scopeId
						, datatype:  node.body.funDecls[i].returntype || node.body.funDecls[i].vartype || undefined
						, parameters: paramsList
						, access: access
						, "static": node.body.funDecls[i]["static"]
					});
				}
				else if (node.body.funDecls[i].type === jsdef.CLASS) {
					offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.body.funDecls[i].lineno-_compiler.currFileStartLine)+1);
					var access = "public";
					if(node.body.funDecls[i]["private"]) access = "private";
					if(node.body.funDecls[i]["protected"]) access = "protected";
					nestedClasses.push({
						  name: node.body.funDecls[i].name
						, type: "CLASS"
						, lineno: node.body.funDecls[i].lineno - _compiler.currFileStartLine
						, start: node.body.funDecls[i].start - offset
						, end: node.body.funDecls[i].end - offset
						, scopeId: node.body.scopeId
						, access: access
						, "static": node.body.funDecls[i]["static"]
					});
				}
			}
		}
		
		//Record Class Symbol						
		offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);				
		var ClassSymbol = {		
			file	: _compiler.currFile || undefined,						
			type	: "CLASS",
			name	: node.name,			
			lineno	: node.lineno - _compiler.currFileStartLine,
			start	: node.start - offset,
			end		: node.end - offset,
			scopeId	: node.scopeId,
			bases	: node["extends"] ? [ node["extends"].value ] : undefined,
			fields	: classFields,			
			methods	: classMethods					
		}; 
				
		_this.insertCodeSymbol(ClassSymbol);
	};
		
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this.insertPrototypeMember = function(node, out)
	{
		var classSymbol = null;
		
		// =======================================================================
		// Ensure class exists
		// =======================================================================
		function getClassSymbol(node)
		{			
			var cls = _this.getClassSymbol(node.value);
			if(cls) return cls;
					
			var offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);
			var classSymbol = {		
				file	: _compiler.currFile || undefined,						
				type	: "CLASS",
				proto 	: true,
				jsdef	: jsdef.CLASS,
				name	: node.value,			
				lineno	: node.lineno - _compiler.currFileStartLine,
				start	: node.start - offset,
				end		: node.end - offset,
				bases	: ["Object"],
				fields	: [],
				methods	: []
			};		
			_this.insertCodeSymbol(classSymbol);			
			
			// Upgrade constructor
			for(i in _this.codeSymbols)
			{
				if(!isFinite(i))continue;
				if(_this.codeSymbols[i].type=="FUNCTION" && _this.codeSymbols[i].name==node.value)
				{
					_this.codeSymbols[i].type = "PROTOTYPE";
					break;
				}
			}			
			
			return classSymbol;
		} 
		
		// =======================================================================
		// Prototype Field 
		// =======================================================================
		function addProtoField(node, datatype, value)
		{
			if(!classSymbol) return; 		
			var offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);			
			classSymbol.fields.push({
				  name: node.value
				, lineno: node.lineno - _compiler.currFileStartLine
				, start: node.start - offset
				, end: node.end - offset				
				, datatype: datatype || undefined
				, value: value || undefined				
				, access: "public"
				, "static": false
			});
		}  
		
		// =======================================================================
		// Prototype Method 
		// =======================================================================
		function addProtoMethod(ast, returnType, value)
		{
			if(!classSymbol) return; 			                                                                      
			var node = ast[0];		
			var offset = (!_compiler.currFile ? 0 : _compiler.currFileOffset-(node.lineno-_compiler.currFileStartLine)+1);
			classSymbol.methods.push({
				  name: node.value
				, lineno: node.lineno - _compiler.currFileStartLine
				, start: node.start - offset
				, end: node.end - offset
				, datatype: node.returntype || undefined
				, parameters: ast[1].paramsList				
				, access: "public"
				, "static": false
			});
		}  
		
		// =======================================================================
		// Read prototype member
		// =======================================================================
		switch(node.value)
		{
			// Special case setter/getter
			// Code generation missing?
			case "__defineGetter__":
			case "__defineSetter__":
				break;
				
			default:				
								
				switch(node[1].type)
				{
					// Class1.prototype = new Class2;
					case jsdef.NEW:
					case jsdef.NEW_WITH_ARGS:
						classSymbol = getClassSymbol(node[0][0]);
						classSymbol.bases = [ node[1][0].value ]; 
						break;
						
					// Class1.prototype.xxx = 5;
					case jsdef.NUMBER:
						classSymbol = getClassSymbol(node[0][0][0]);
						addProtoField(node[0], "Number", node[1].value);
						break;
						
					// Class1.prototype.xxx = "string";
					case jsdef.STRING:
						classSymbol = getClassSymbol(node[0][0][0]);
						addProtoField(node[0], "String", node[1].value);
						break;
						
					// Class1.prototype.xxx = true;
					case jsdef.TRUE:
					case jsdef.FALSE:
						classSymbol = getClassSymbol(node[0][0][0]);
						addProtoField(node[0], "Boolean", node[1].value);
						break;
					
					// Class1.prototype.xxx = null;	
					case jsdef.NULL:
						classSymbol = getClassSymbol(node[0][0][0]);
						addProtoField(node[0], "Object", "null");
						break;
						
					// Class1.prototype.xxx = function()
					case jsdef.FUNCTION:						
						classSymbol = getClassSymbol(node[0][0][0]);						
						addProtoMethod(node);
						break;
						
					// Class1.prototype.xxx;
					case jsdef.IDENTIFIER:
						break;
						
					// Class1.prototype.xxx = [];
					case jsdef.ARRAY_INIT:
						classSymbol = getClassSymbol(node[0][0][0]);
						addProtoField(node[0], "Array", "[]");
						break;
					
					// Class1.prototype.xxx = {};
					case jsdef.OBJECT_INIT:
						classSymbol = getClassSymbol(node[0][0][0]);
						addProtoField(node[0], "Object", "{}");
						break;			
					
					// Class1.prototype.__defineSetter__("prop", function(){});
					case jsdef.GETTER:
					case jsdef.SETTER:						
						break;
									
					default:
						break;
				}
		}  
		
		//if(classSymbol) _this.TRACE(classSymbol);
	};
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// Experimental: heuristics based variable datatype detection when not pluggable type system is used.
	this.detectDataType = function(varItem)
	{		
		if(!varItem.value) return;
		
		var dt = undefined;
		
		switch(varItem.value.type)
		{
		case jsdef.NEW_WITH_ARGS:
		case jsdef.NEW: 
			dt = varItem.value[0].value;
			break;
			
		case jsdef.ARRAY_INIT:
			dt = "Array";
			break;
			
		case jsdef.OBJECT_INIT:
			dt = "Object";
			break;
			
		case jsdef.NULL:
		case jsdef.OR: // a = a || null;						
			dt = "Object";
			break;
			
		case jsdef.STRING:
			dt = "String";
			break;
			
		case jsdef.DATE:
			dt = "Date";
			break;
	
		case jsdef.REGEXP:
			dt = "RegExp";
			break;
		
		// Numbers and numeric operators result in Number!
		case jsdef.NUMBER:
		case jsdef.ADD:	
		case jsdef.DECREMENT:
		case jsdef.DIV:	
		case jsdef.EXPONENT:
		case jsdef.INCREMENT:
		case jsdef.LSH:
		case jsdef.MINUS:
		case jsdef.MOD:
		case jsdef.MUL:	
		case jsdef.PLUS:
		case jsdef.RSH:
		case jsdef.SUB:	
		case jsdef.URSH:
		case jsdef.UNARY_PLUS:
		case jsdef.UNARY_MINUS:						
			dt = "Number";
			break;
						
		// Booleans and logic operators result in Boolean!
		case jsdef.FALSE:
		case jsdef.TRUE:
		case jsdef.BITWISE_OR:
		case jsdef.BITWISE_XOR:
		case jsdef.BITWISE_AND:
		case jsdef.STRICT_EQ:
		case jsdef.EQ:
		case jsdef.STRICT_NE:
		case jsdef.NE:
		case jsdef.LE:
		case jsdef.LT:
		case jsdef.GE:
		case jsdef.GT:
			dt = "Boolean";
			break;
					
		// ======== DATATYPE HEURISTICS ======== //
			
		// a = Math.cos(x)	
		case jsdef.CALL:
			if(varItem.value[0] && varItem.value[0][0] && varItem.value[0][0].value=="Math") dt = "Number";
			break;														
			
		// a.b
		case jsdef.DOT:							
			// Enum Heuristics
			if(varItem.value.length==2 && varItem.value[0].value.indexOf("_ENUM")==0)
				dt = varItem.value[0].value;
			break;
	
		// a[i]
		case jsdef.INDEX:
			//TODO: Detect array type.
			break;
			
		// a = b;				
		case jsdef.IDENTIFIER:
			//TODO: Detect identifier type.
			break;
			
		case jsdef.FUNCTION:
			//TODO: Detect function return type.
			break;
			
		case jsdef.GROUP:
			//TODO: Detect group return type.
			break;
									
		default:
			break;
		}						
		
		return dt;		
	}		
}









