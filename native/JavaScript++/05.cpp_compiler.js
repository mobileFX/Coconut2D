
/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
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
//	       _______                __           ______         
//	      / / ___/  __    __     / /_____     / ____/__    __ 
//	 __  / /\__ \__/ /___/ /_   / __/ __ \   / /  __/ /___/ /_
//	/ /_/ /___/ /_  __/_  __/  / /_/ /_/ /  / /__/_  __/_  __/
//	\____//____/ /_/   /_/     \__/\____/   \____//_/   /_/   
//	                                                          
// ==================================================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function CPPCompiler(ast, options) 
{
	var _this = this;
    
	_this.ast = ast;
	_this.errors = [];
	_this.warnings = [];             
	_this.scopes = [];
	_this.currClassName = null;
	_this.classes = {};	
	_this.lineno = -1;
    _this.HPP = [];

	_this.currFile = "";
	_this.currFileStartLine = 0;
	_this.currFileOffset = 0;
	_this.FILE_DELIM = "script_begin:///";	
	
	_this.types = {
		"Boolean"	: { "default": "false" },
		"Function"	: {	"default": "NULL" },
		"Null"		: { "default": "NULL" },
		"Number"	: {	"default": "0" },
		"Float"		: { "default": "0.0" },
		"Integer"	: { "default": "0" },
		"Object"	: { "default": "NULL" },
		"String"	: { "default": '""' }
	};	
			
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewWarning = function (e, node) 
	{
		trace("@@ WARNING: " + e + " in file " + node.file + " at line " + node.fileLine);
		_this.warnings.push(e);
	};
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewError = function (e, node)
	{
		trace("@@ ERROR: " + e + " in file " + node.file + " at line " + node.fileLine);
		_this.errors.push(e);
	}; 
		
	// ==================================================================================================================================
	//	   _____                          __  ___                          
	//	  / ___/_________  ____  ___     /  |/  /___ _______________  _____
	//	  \__ \/ ___/ __ \/ __ \/ _ \   / /|_/ / __ `/ ___/ ___/ __ \/ ___/
	//	 ___/ / /__/ /_/ / /_/ /  __/  / /  / / /_/ / /__/ /  / /_/ (__  ) 
	//	/____/\___/\____/ .___/\___/  /_/  /_/\__,_/\___/_/   \____/____/  
	//	               /_/                                                 
	// ==================================================================================================================================	

	_this.NewScope = function(node) 
	{
		var scope = null;
		
		if(_this.pass==2)
		{
			scope = node.__scope;
		}
		else
		{		
			scope = 
			{         
				name			: _this.scopes.length==0 ? "GLOBAL_SCOPE" : node.name,
				parent			: _this.scopes.length ? _this.scopes[_this.scopes.length-1] : null,
				ast				: node,
				type			: node.type,
				nodeType		: node.nodeType,			            	
				isGlobal		: _this.scopes.length==0,
				isClass			: node.type==jsdef.CLASS,
				isMethod		: node.type==jsdef.FUNCTION,			            	
				file			: node.file,
				start			: node.start-node.fileOffset,
				end				: node.end-node.fileOffset,
				lineno			: node.fileLine,			
				scopeId			: node.scopeId,
				vars			: {},
				methods			: {}			
			};
			node.__scope = scope;
		}
		_this.scopes.push(scope);
		return scope;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.ExitScope = function() 
	{
		return _this.scopes.pop();		
	};
	
	// ==================================================================================================================================
	//	   _____                 __          __   __                __                   
	//	  / ___/__  ______ ___  / /_  ____  / /  / /   ____  ____  / /____  ______  _____
	//	  \__ \/ / / / __ `__ \/ __ \/ __ \/ /  / /   / __ \/ __ \/ //_/ / / / __ \/ ___/
	//	 ___/ / /_/ / / / / / / /_/ / /_/ / /  / /___/ /_/ / /_/ / ,< / /_/ / /_/ (__  ) 
	//	/____/\__, /_/ /_/ /_/_.___/\____/_/  /_____/\____/\____/_/|_|\__,_/ .___/____/  
	//	     /____/                                                       /_/            
	// ==================================================================================================================================	
	
	// We link an identifier with a Symbol to get access to its datatype, scope, etc.
	_this.LookupSymbol = function(scope, identifier, node)
	{		
		if(!identifier || !scope) return;
		
		var symbol = null;                                                       
		
		// Is this identifier a class?
		if(_this.classes[identifier])
			return _this.classes[identifier]; 
		 
		// Lookup scope chain
		_this.LookupScopeChain(identifier, scope, function(data)
		{ 
			symbol = data;						
		}, true); 
		         
		// Lookup DOT chain.
		if(!symbol && node && this.pass==2)
		{
			// Find a dot stack in our parent chain.
			var parent = node.parent;
			while(parent && !parent.dotStack) { parent = parent.parent; }
			if(parent && parent.dotStack)
			{				
				// Start descending dot chain.
				for(var i=0; i<parent.dotStack.length;i++)
				{
					var parentSymbol = _this.LookupSymbol(scope, parent.dotStack[i], null);
					if(!parentSymbol) break;
					if(parent.dotStack[i]==identifier)
					{                                
						symbol = parentSymbol;
						break;						
					}
					var cls = _this.classes[ parentSymbol.vartype ];
					if(!cls) break;	
					scope = cls.scope;					
				}
			}			
		} 
		
		if(this.pass==2 && !symbol)
		{
			_this.NewWarning("Symbol not found: " + identifier, node || scope);
		}
		
		return symbol;		
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.LookupScopeChain = function (findIdentifier, scope, callback, deep) 
	{
		if(!scope) return;		
		var found = false;
		var data = null;		

		if(!found) for(var name in scope.methods)
		{
			if(name==findIdentifier)
			{
				found = true;  
				data = scope.methods[name];
				break;
			}			
		}
		
		if(!found) for(var name in scope.vars)
		{
			if(name==findIdentifier)
			{
				found = true;  
				data = scope.vars[name];
				break;
			}			
		}

		if(!found && scope.isMethod && scope.ast.symbol && scope.ast.symbol.baseSymbol) 
		{
			debugger;
		}				
		
		if(!found && scope.isClass && scope.ast.symbol && scope.ast.symbol.baseSymbol) 
		{
			data = _this.LookupScopeChain(findIdentifier, scope.ast.symbol.baseSymbol.scope, callback, deep);
			if(data) return data;				
		}
		
		if(found)
		{
			if(callback) callback(data);
			return data;
		}

		if(deep && scope.parent)		
			return _this.LookupScopeChain(findIdentifier, scope.parent, callback, deep);		
	};

	// ==================================================================================================================================
	//	    __  ___                          
	//	   /  |/  /___ _______________  _____
	//	  / /|_/ / __ `/ ___/ ___/ __ \/ ___/
	//	 / /  / / /_/ / /__/ /  / /_/ (__  ) 
	//	/_/  /_/\__,_/\___/_/   \____/____/  
	//	                                     
	// ==================================================================================================================================	
	
	_this.getCurrentClass = function()	{ return _this.classes[_this.currClassName]; };
	_this.CurrentScope = function() 	{ return _this.scopes[_this.scopes.length-1];};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.ClassScope = function()
	{
		var scope = _this.CurrentScope(); 
		while(scope)
		{
			if(scope.isClass)
				return scope;
			scope = scope.parent;
		}
	};
		
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isInside = function(ast, jsdefType, propName, propValue)
	{ 		
		for(var p=ast.parent;p!=null;p=p.parent)
		{
			if(p.type==jsdefType)
			{
				if(propName && propValue)
				{
					if(p[propName]==propValue)
						return true;
				}			
				else
				{
					return true;
				}
			}
		}
		return false;				
	};	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPPCompiler.prototype.compile = function (ast) 
{
	var _this = this, out = [], HPP = _this.HPP, ast = ast || _this.ast, scope;	
	
	var generate = function()
	{
		return _this.compile.apply(_this, Array.prototype.slice.call(arguments,0));
	};
	
	/*
	if(_this.lineno != ast.lineno) 
	{
		_this.lineno != -1 && out.push("\n");		
		out.push("\/\/@line " + ast.fileLine + "\n");
		_this.lineno = ast.lineno;
	} 
	*/   

	switch(ast.type) 
	{

	// ==================================================================================================================================
	//	   ________               
	//	  / ____/ /___ ___________
	//	 / /   / / __ `/ ___/ ___/
	//	/ /___/ / /_/ (__  |__  ) 
	//	\____/_/\__,_/____/____/  
	//	                          
	// ==================================================================================================================================
	
	case jsdef.CLASS:

	 	_this.currClassName = ast.name;
	 	
		var constructor = null;
		var classId = "__CLASS" + ast.body.scopeId + "__"; // "__CLASS__" + ast.name.toUpperCase() + "__",
		var baseClass = ast.extends ? ast.extends.value : undefined;
		var baseClassId = baseClass ? _this.classes[baseClass].ast.symbol.classId : null;
		var scope = _this.NewScope(ast);		
		
		var classSymbol =
		{
			name			: ast.name,
			classId			: classId,
			base			: baseClass, 
			baseSymbol		: _this.classes[baseClass],
			type			: ast.type,
			nodeType		: ast.nodeType,
			ast				: ast,
			scope			: scope,			
			file			: ast.file,
			start			: ast.start-ast.fileOffset,
			end				: ast.end-ast.fileOffset,
			lineno			: ast.fileLine,			
			scopeId			: ast.scopeId,
			vars			: scope.vars,
			methods	 		: scope.methods	
		}		
		_this.classes[ast.name] = classSymbol;		
		ast.symbol = classSymbol;		
			
		HPP.push("#ifndef __" + ast.name.toUpperCase() + "_HPP__\n");
		HPP.push("#define __" + ast.name.toUpperCase() + "_HPP__\n");		
		HPP.push("\n\nclass " + ast.name + (superClass ? " : public " + superClass : "") + "\n{\npublic:\n");
		out.push('#include "' + ast.name + '.hpp"\n');		
		
		for(var item in ast.body) 
		{
			if(!isFinite(item)) continue;
			currentItem = ast.body[item];			
			switch(currentItem.type)
			{
				case jsdef.FUNCTION:
					if(currentItem.name == "Constructor")
					{
						currentItem.name = ast.name;
						currentItem.isConstructor = true;						
					}					
					else if(currentItem.name == "dispose")
					{
						currentItem.name = "~"+ast.name;
						currentItem.isConstructor = true;						
					}
					out.push(generate(currentItem));
					break;
					
				case jsdef.VAR:
					HPP.push(generate(currentItem));
					break;
			}
		}
		
		HPP.push("};\n\n#endif\n");		
		
		_this.currClassName = null;
		_this.ExitScope();		
		break;  
				
	// ==================================================================================================================================
	//	    ______                 __  _                 
	//	   / ____/_  ______  _____/ /_(_)___  ____  _____
	//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \/ ___/
	//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / (__  ) 
	//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/____/  
	//	                                                 
	// ==================================================================================================================================

	case jsdef.FUNCTION:
        		
		if(!ast.returntype) ast.returntype = "void";
		ast.isPointer = __isPointer(ast.returntype);
		
		var methodScope = _this.NewScope(ast);		 
		var parentScope = methodScope.parent;
		var isClass = parentScope.isClass; 
		var classId = isClass ? parentScope.ast.symbol.classId : null;
		var isGlobal = !isClass && parentScope.isGlobal;
		var fnName = (ast.name ? ast.name : "");		
		var baseMethodSymbol = null;

		// Link method symbol with base class method symbol for speed.
		if(isClass && parentScope.ast.symbol.baseSymbol)
			baseMethodSymbol = _this.LookupSymbol(parentScope.ast.symbol.baseSymbol.scope, ast.name, ast);
				
		// Function Symbol
		var functionSymbol = 		
		{
			name		: fnName,              
			type		: ast.type,
			nodeType	: ast.nodeType,			         
			className	: isClass ? parentScope.name : null,
			classId		: isClass ? classId : null,			
			public		: ast.public==true,
			private		: ast.private==true,
			protected	: ast.protected==true,
			static		: ast.static==true,			
			ast			: ast,              			
			scope		: methodScope,
			baseSymbol	: baseMethodSymbol,			
			file		: ast.file,
			start		: ast.start-ast.fileOffset,
			end			: ast.end-ast.fileOffset,
			lineno		: ast.fileLine,			
			scopeId		: ast.scopeId,			
			vartype		: ast.returntype,
			subtype		: ast.subtype,    
			paramsList	: ast.paramsList
		};		
		methodScope.parent.methods[ast.name] = functionSymbol;
		
		// Arguments List
		var paramsList = "(";	
		for(var i=0; i<ast.paramsList.length; i++)
		{
			var param = ast.paramsList[i];
			param.isPointer = __isPointer(param.vartype);
			paramsList += param.vartype + (param.isPointer? "*" : "") + " " + param.name;
			if(i!=ast.paramsList.length-1) paramsList +=", ";			

            // Argument Symbol
			var varSymbol =
			{
				name		: param.name,
				type		: param.type,
				nodeType	: param.nodeType,			
				classId		: null,
				public		: false,
				private		: false,
				protected	: false,
				static		: false,
				ast			: param,              
				scope		: methodScope,			
				file		: param.file,
				start		: param.start-param.fileOffset,
				end			: param.end-param.fileOffset,
				lineno		: param.fileLine,			
				scopeId		: param.scopeId,			
				vartype		: param.vartype,
				subtype		: param.subtype,    
				pointer		: param.isPointer
			};
			methodScope.vars[param.name] = varSymbol;
		}
		paramsList += ")";
        
		FN = (ast.isConstructor ? "" : ast.returntype + (ast.isPointer?"*":"") + " ") + ast.name + paramsList + ";\n";
		HPP.push(FN);
		
		out.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
		out.push( (ast.isConstructor ? "" : ast.returntype +(ast.isPointer?"*":"") + " ") + _this.currClassName+"::" + ast.name + paramsList);
        out.push("\n{\n");
		out.push(generate(ast.body));
		out.push("}\n"); 
		
		_this.ExitScope();		
		break;   
		
	// ==================================================================================================================================
	//	 _    __           _       __    __         
	//	| |  / /___ ______(_)___ _/ /_  / /__  _____
	//	| | / / __ `/ ___/ / __ `/ __ \/ / _ \/ ___/
	//	| |/ / /_/ / /  / / /_/ / /_/ / /  __(__  ) 
	//	|___/\__,_/_/  /_/\__,_/_.___/_/\___/____/  
	//	                                            
	// ==================================================================================================================================   
	
	case jsdef.VAR:				
	case jsdef.CONST:
		
		var scope = _this.CurrentScope();			
		var classSymbol = scope.isClass ? scope.ast : null;
		var firstItem = true;
		
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			
			ast[item].isPointer = __isPointer(ast[item].vartype);
			
			var varSymbol =
			{
				name		: ast[item].name,
				type		: ast[item].type,
				nodeType	: ast[item].nodeType,			
				classId		: scope.isClass ? scope.ast.symbol.classId : null,
				public		: ast.public,
				private		: ast.private,
				protected	: ast.protected,
				static		: ast.static,				
				ast			: ast[item],              
				scope		: scope,			
				file		: ast[item].file,
				start		: ast[item].start-ast[item].fileOffset,
				end			: ast[item].end-ast[item].fileOffset,
				lineno		: ast[item].fileLine,			
				scopeId		: ast[item].scopeId,			
				vartype		: ast[item].vartype,
				subtype		: ast[item].subtype,    
				pointer		: ast[item].isPointer			
			};			
			scope.vars[ast[item].name] = varSymbol;

			if(firstItem) out.push(ast[item].vartype); 
			if(!firstItem) out.push(", ");							
			if(ast[item].isPointer) out.push("*");
			out.push(" ");			
			out.push(ast[item].name);
			
			if(ast[item].initializer)
			{				
				// Generate initializer
				out.push(" = ");
				out.push(generate(ast[item].initializer));
			} 
			else 
			{   
				var vartype = ast[item].vartype;
				if(vartype && vartype.indexOf("<")!=-1) 
					vartype = vartype.substr(0, vartype.indexOf("<"));
				
				if(_this.types.hasOwnProperty(vartype))
					out.push("="+_this.types[vartype].default);
				else if(scope.isClass)
					out.push("=null");
			}
						
			firstItem = false;
		} 
		out.push(";");
		break;						
	
	// ==================================================================================================================================
	//	    ____    __           __  _ _____          
	//	   /  _/___/ /__  ____  / /_(_) __(_)__  _____
	//	   / // __  / _ \/ __ \/ __/ / /_/ / _ \/ ___/
	//	 _/ // /_/ /  __/ / / / /_/ / __/ /  __/ /    
	//	/___/\__,_/\___/_/ /_/\__/_/_/ /_/\___/_/     
	//	                                              
	// ==================================================================================================================================
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.SUPER:
		out.push("super");
		break; 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.THIS:
		out.push("this");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.IDENTIFIER:
		// Link identifier with symbol.
		if(!ast.symbol) 
			ast.symbol = _this.LookupSymbol(_this.CurrentScope(), ast.value, ast);
		out.push(ast.value); 
		break;		

	// ==================================================================================================================================
	//	   ______      ____    
	//	  / ____/___ _/ / /____
	//	 / /   / __ `/ / / ___/
	//	/ /___/ /_/ / / (__  ) 
	//	\____/\__,_/_/_/____/  
	//	                       
	// ==================================================================================================================================

	case jsdef.SCRIPT:          
		ast.name = "SCRIPT" + ast.scopeId;
		var body = [];
		var scope = _this.NewScope(ast);		
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			body.push(generate(ast[item]));
		}
		_this.ExitScope();
		out = out.concat(body);		
		break;            
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.BLOCK:
		ast.name = "BLOCK" + ast.scopeId;
		_this.NewScope(ast);
		out.push("{\n");
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			out.push(generate(ast[item]));
		}
		out.push("}\n");
		_this.ExitScope();
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.CALL:
		out.push(generate(ast[0]));
		ast[0].type == jsdef.REGEXP && out.push(".exec");
		out.push("(");
		out.push(generate(ast[1]));
		out.push(")");
		break;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.LIST:
	case jsdef.COMMA:
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			if(!firstItem) out.push(", ");
			out.push(generate(ast[item]));
			firstItem = false;
		}
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.GROUP:
		out.push("(");
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			out.push(generate(ast[item]));
		}
		out.push(")");
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.ARRAY_INIT:
		out.push("//<<{");
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			if(!firstItem) out.push(",");
			out.push(generate(ast[item]));
			firstItem = false;
		}
		out.push("}>>//");
		break; 
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.OBJECT_INIT:
		out.push("{ ");
		var firstItem = true;
		for(var item in ast) 
		{
			if(!isFinite(item)) continue;
			if(!firstItem) out.push(", ");
			ast[item].parent = ast;
			out.push(generate(ast[item]));			
			firstItem=false;
		}		
		out.push("}");
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.PROPERTY_INIT:		
		out.push(generate(ast[0]) + ":");
		out.push(generate(ast[1]));
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.ASSIGN:				
		if(ast[1].type==jsdef.ARRAY_INIT)
		{ 
			var isEmpty = true;
			for(var i in ast[1])
			{
				if(!isFinite(i)) continue;
				isEmpty=false;
				break;				
			}
			if(isEmpty)
			{
				// Skip statement generation.				
				return null;
			}
		}
		
		if(ast[0].type==jsdef.THIS) 
		{
			_this.NewError({type:ReferenceError, message:"Cannot assign to '_this'"},ast);
		}
		else if(ast[0].type != jsdef.IDENTIFIER && ast[0].type != jsdef.DOT && ast[0].type != jsdef.INDEX) 
		{
			_this.NewError({type:ReferenceError, message:"Invalid left-hand assignment"},ast);
		}  
		
		out.push(generate(ast[0])); 		 
		out.push(ast.value);
		if(ast.value != "=") out.push("=");
		out.push(generate(ast[1]));		
		break; 
		
	// ==================================================================================================================================
	//	   ______                ___ __  _                   __    
	//	  / ____/___  ____  ____/ (_) /_(_)___  ____  ____ _/ /____
	//	 / /   / __ \/ __ \/ __  / / __/ / __ \/ __ \/ __ `/ / ___/
	//	/ /___/ /_/ / / / / /_/ / / /_/ / /_/ / / / / /_/ / (__  ) 
	//	\____/\____/_/ /_/\__,_/_/\__/_/\____/_/ /_/\__,_/_/____/  
	//	                                                           
	// ==================================================================================================================================

	case jsdef.IF:
		out.push("if(");
		out.push(generate(ast.condition));
		out.push(") ");
		out.push(generate(ast.thenPart));		
		if(ast.elsePart) 
		{
			out.push("else ");  			
			out.push(generate(ast.elsePart));			
		}
		break;   
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.SWITCH:
		out.push("switch(" + generate(ast.discriminant) + "){");
		for(var _case in ast.cases) 
		{
			if(!isFinite(_case)) continue;
			out.push(generate(ast.cases[_case]));
			out.push("break;");
		}
		out.push("}");
		break; 

	// ==================================================================================================================================
	//	    ____              __                    
	//	   / __/___  _____   / /   ____  ____  ____ 
	//	  / /_/ __ \/ ___/  / /   / __ \/ __ \/ __ \
	//	 / __/ /_/ / /     / /___/ /_/ / /_/ / /_/ /
	//	/_/  \____/_/     /_____/\____/\____/ .___/ 
	//	                                   /_/      
	// ==================================================================================================================================		

	case jsdef.FOR:
		var setupFor = ast.setup ? generate(ast.setup) : ";";
		setupFor=setupFor.trim();
		out.push("for(" + setupFor + (setupFor.slice(-1) == ";" ? "": ";"));
		out.push((ast.condition ? generate(ast.condition) : "") + ";");
		out.push((ast.update ? generate(ast.update) : "") + ")");
		out.push(generate(ast.body));
		break;  
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.FOR_IN:
		out.push("for(" + (ast.iterator.type == jsdef.VAR ?	"auto " + ast.iterator[0].value : ast.iterator.value));
		out.push(" : " + (ast.object ? generate(ast.object) : "") + ")");
		out.push(generate(ast.body));
		break;  
				
	// ==================================================================================================================================
	//	    __  ____                ____                                 
	//	   /  |/  (_)____________  / / /___ _____  ___  ____  __  _______
	//	  / /|_/ / / ___/ ___/ _ \/ / / __ `/ __ \/ _ \/ __ \/ / / / ___/
	//	 / /  / / (__  ) /__/  __/ / / /_/ / / / /  __/ /_/ / /_/ (__  ) 
	//	/_/  /_/_/____/\___/\___/_/_/\__,_/_/ /_/\___/\____/\__,_/____/  
	//	                                                                 
	// ==================================================================================================================================	

	case jsdef.STRING:

		out.push('"' + ast.value + '"');

		//Detect file change in input stream and mark file line and offset
		var f = '"'+ast.value + '"';
		if(f.indexOf(_this.FILE_DELIM)!=-1)
		{
			_this.currFile = f.substr(_this.FILE_DELIM.length+1, f.lastIndexOf('"')-_this.FILE_DELIM.length-1 );
			_this.currFileStartLine = ast.lineno;
			_this.currFileOffset = ast.start + f.length +2;								
			trace("Compiling file: " + _this.currFile + " (L:"+_this.currFileStartLine+" P:"+_this.currFileOffset + ")");
		}			
		break;	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.TRY:
		out.push("try");
		out.push(generate(ast.tryBlock));
		for(var catchClause in ast.catchClauses) 
		{
			if(!isFinite(catchClause)) continue;
			out.push("catch(" + ast.catchClauses[catchClause].varName + ")");
			out.push(generate(ast.catchClauses[catchClause].block));
			ast.finallyBlock && out.push("finally" + generate(ast.finallyBlock));
		}
		break;		

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.DOT:						
		// Dots are special case because we need to decide when to use dot "." or pointer "->"
		
		out.push(generate(ast[0]));		
		
		if(_this.pass==1)
		{
			out.push(".");
		}              
		else
		{ 
			if(out.join("")=="this")
				out.push("->");
			else				
			
			switch(ast[0].type)
			{
			case jsdef.DOT:				
				if(ast[0][1].symbol && ast[0][1].symbol.pointer)
					out.push("->");					
				else				
					out.push(".");
				break;			
				
			case jsdef.INDEX:
				if(__isPointer(ast[0][0].symbol.subtype))
					out.push("->");					
				else				
					out.push(".");
				break;
				
			case jsdef.IDENTIFIER:
				
				if(!ast[0].symbol)                                         
				{					
					out.push(".");
					break;
				}
				
				if(ast[0].symbol.pointer)
					out.push("->");					
				else				
					out.push(".");
				break; 
				
			case jsdef.CALL:
				switch(ast[0][0].type)
				{
				case jsdef.DOT:
					if(ast[0][0][1].symbol.pointer)
						out.push("->");					
					else				
						out.push(".");
					break;			
					
				case jsdef.INDEX:
					if(__isPointer(ast[0][0][0].symbol.subtype))
						out.push("->");					
					else				
						out.push(".");
					break;
					
				case jsdef.IDENTIFIER:
					if(ast[0][0].symbol.pointer)
						out.push("->");					
					else				
						out.push(".");
					break; 
					   
				default:
					out.push(".");
					break;
				}
				break;
							
			default:
				out.push(".");					
				break;			
			}
		}
			
		out.push(generate(ast[1]));		
		break;
		
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	  
	case jsdef.DEBUGGER:			out.push("assert(false);"); break; 
	case jsdef.EXPONENT:			out.push("std::pow(" + generate(ast[0]) + "," + generate(ast[1]) + ")");break;
	case jsdef.MOD:					out.push("(int)" + generate(ast[0])); out.push("%"); out.push("(int)" + generate(ast[1])); break;
	case jsdef.NEW: 				out.push("new "); out.push(generate(ast[0]) +"()"); break;
	case jsdef.THROW:				out.push("throw CocoException("); out.push(generate(ast.exception)); out.push(");"); break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	  
	case jsdef.AND:					out.push(generate(ast[0])); out.push("&&"); out.push(generate(ast[1])); break;
	case jsdef.BITWISE_AND:			out.push(generate(ast[0])); out.push("&"); out.push(generate(ast[1])); break;  		
	case jsdef.BITWISE_NOT:			out.push("~"); out.push(generate(ast[0])); break;  		
	case jsdef.BITWISE_OR:			out.push(generate(ast[0])); out.push("|"); out.push(generate(ast[1])); break; 		
	case jsdef.BITWISE_XOR:			out.push(generate(ast[0])); out.push("^"); out.push(generate(ast[1])); break;    		
	case jsdef.BREAK:				out.push("break;"); break;
	case jsdef.CASE:				out.push("case " + generate(ast.caseLabel) + ":"); out.push(generate(ast.statements)); break;    
	case jsdef.CONTINUE:			out.push("continue;"); break;
	case jsdef.DECREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("--"); } else { out.push("--"); out.push(generate(ast[0])); } break;
	case jsdef.DEFAULT:				out.push("default:"); out.push(generate(ast.statements)); break; 
	case jsdef.DELETE: 				out.push("delete "); out.push(generate(ast[0])); break;
	case jsdef.DIV:					out.push(generate(ast[0])); out.push("/"); out.push(generate(ast[1])); break;  
	case jsdef.DO: 					ast.body.isLoop = true; out.push("do"); out.push(generate(ast.body)); out.push("while(" + generate(ast.condition) + ");"); break;
	case jsdef.EQ: 					out.push(generate(ast[0])); out.push("==");	 out.push(generate(ast[1])); break; 		
	case jsdef.FALSE:				out.push("false"); break;    
	case jsdef.GE:					out.push(generate(ast[0])); out.push(">=");  out.push(generate(ast[1])); break;  		
	case jsdef.GT:					out.push(generate(ast[0])); out.push(">");   out.push(generate(ast[1])); break; 		
	case jsdef.HOOK:				out.push(generate(ast[0])); out.push("?"); out.push(generate(ast[1])); out.push(":"); out.push(generate(ast[2])); break;
	case jsdef.INCREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("++"); } else { out.push("++"); out.push(generate(ast[0])); } break;
	case jsdef.INDEX: 				out.push(generate(ast[0])); out.push("["); out.push(generate(ast[1])); out.push("]"); break;
	case jsdef.INSTANCEOF: 			out.push(generate(ast[0])); out.push(" instanceof "); out.push(generate(ast[1])); break;
	case jsdef.LABEL:				out.push(ast.label + ":"); out.push(generate(ast.statement)); break;			
	case jsdef.LE:					out.push(generate(ast[0])); out.push("<=");  out.push(generate(ast[1])); break;
	case jsdef.LSH:					out.push(generate(ast[0])); out.push("<<"); out.push(generate(ast[1])); break; 		
	case jsdef.LT:					out.push(generate(ast[0])); out.push("<");   out.push(generate(ast[1])); break; 	
	case jsdef.MINUS: 				out.push(generate(ast[0])); out.push("-"); out.push(generate(ast[1])); break;  
	case jsdef.MUL: 				out.push(generate(ast[0])); out.push("*"); out.push(generate(ast[1])); break;   
	case jsdef.NE:					out.push(generate(ast[0])); out.push("!=");	 out.push(generate(ast[1])); break; 		
	case jsdef.NEW_WITH_ARGS:		out.push("new "); out.push(generate(ast[0])); out.push("("); out.push(generate(ast[1])); out.push(")"); break;
	case jsdef.NOT:					out.push("!"); out.push(generate(ast[0])); break;
	case jsdef.NULL:				out.push("NULL"); break;	
	case jsdef.NUMBER:				out.push(ast.value); break; 
	case jsdef.OR:					out.push(generate(ast[0])); out.push("||"); out.push(generate(ast[1]));	break;
	case jsdef.PLUS: 				out.push(generate(ast[0])); out.push("+"); out.push(generate(ast[1])); break;	
	case jsdef.RETURN:				out.push("return"); if(ast.value.type) out.push(" " + generate(ast.value)); out.push(";\n"); break;
	case jsdef.RSH:					out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break; 		
	case jsdef.SEMICOLON:			var expr = (ast.expression ? generate(ast.expression) : ""); if(expr) out.push(expr + ";\n"); break;
	case jsdef.STRICT_EQ:			out.push(generate(ast[0])); out.push("=="); out.push(generate(ast[1])); break; 		
	case jsdef.STRICT_NE:			out.push(generate(ast[0]));	out.push("!="); out.push(generate(ast[1])); break;  		
	case jsdef.TRUE:				out.push("true"); break;
	case jsdef.TYPEOF:				out.push("typeof "); out.push(generate(ast[0])); break;			
	case jsdef.UNARY_MINUS:			out.push(" -"); out.push(generate(ast[0])); break;
	case jsdef.UNARY_PLUS:			out.push(" +"); out.push(generate(ast[0])); break;		
	case jsdef.URSH:				out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break;
	case jsdef.VOID:				out.push("void "); out.push(generate(ast[0])); break;	
	case jsdef.WHILE:				ast.body.isLoop=true; out.push("while(" + generate(ast.condition) + ")"); out.push(generate(ast.body)); break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	default:
		debugger;
	}
		
	return out.join("");
}; 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPPCompiler.prototype.pass = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPPCompiler.prototype.reduceDotProps = function(ast) 
{
	var out = [];
	
	switch (ast[0].type) 
	{
		case jsdef.IDENTIFIER:
		case jsdef.TRUE:
		case jsdef.FALSE:
		case jsdef.NULL:
			out.push(ast[0].value);
			break; 
			
		case jsdef.INDEX:
		case jsdef.GROUP:
		case jsdef.DOT:
		case jsdef.CALL:
			out = out.concat(this.reduceDotProps(ast[0]));
			break;					
			
		case jsdef.THIS:
			out.push("@@THIS@@");
			break;
			
		case jsdef.SUPER:
			out.push("@@SUPER@@");
			break;
			
		default:    
			break;
	}
				
	if (ast.type == jsdef.DOT) 
		out.push(ast[1].value);
	else if (ast.type == jsdef.INDEX)    
		out.push("@@INDEX@@");				
	
	return out;
}; 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPPCompiler.prototype.preprocess = function(ast, pass) 
{
	var _this = this;
	_this.pass = pass;
	 	 
    // Descent the ast to redeuce properties for 
    // DOTs and set parent node to all ast nodes. 
    
	function descend(node)
	{                               
		node.__visited=true;
		
		if(node.type==jsdef.DOT)
			node.dotStack = _this.reduceDotProps(node);			
		
		for(var item in node) 
		{
			if(node[item] instanceof Node && !node[item].__visited)
			{			
				descend(node[item]);  								
				node[item].parent = node;
			}
		}
	} 
	
	descend(ast);	
	
	return ast;
};



