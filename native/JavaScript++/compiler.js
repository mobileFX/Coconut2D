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
 *********************************************************************************
 * This compiler is based on Roger Poon's JavaScript++ (http://www.jspplang.org/)
 * work and it is a rather simplified version of Roger's work in order to make it
 * easier to integrate with Coconut2D IDE. The language syntax has been largely
 * simplified to allow JavaScript++ to C++ code generation in order to be able
 * to produce native code for iOS and Android devices.
 *********************************************************************************
 *
 * ***** END LICENSE BLOCK ***** */

// ==================================================================================================================================
//	   ______                _____           _       __     ______                      _ __
//	  / ____/___  _________ / ___/__________(_)___  / /_   / ____/___  ____ ___  ____  (_) /__  _____
//	 / /   / __ \/ ___/ __ \\__ \/ ___/ ___/ / __ \/ __/  / /   / __ \/ __ `__ \/ __ \/ / / _ \/ ___/
//	/ /___/ /_/ / /__/ /_/ /__/ / /__/ /  / / /_/ / /_   / /___/ /_/ / / / / / / /_/ / / /  __/ /
//	\____/\____/\___/\____/____/\___/_/  /_/ .___/\__/   \____/\____/_/ /_/ /_/ .___/_/_/\___/_/
//	                                      /_/                                /_/
// ==================================================================================================================================

/*
	Disclaimer:

	I had many problems integrating original JavaScript++ implementation properly with the IDE and during the process I produced bugs
	or found bugs that I could not overcome, so I decided to get deeper into Roger's code, understand the principles of his compiler
	and the Narcissus parser in depth, and re-write most of the compiler from scratch. The end result works but it is intermediate,
	my goal is to fall back to JavaScript++ original implementation and I have schedulled a meeting with Roger on Feb 2014.

	Some important architectural differencies are:

	1. I pre-process the AST nodes and assign a ".parent" which makes it easier to debug the compiler.
	2. I pre-process and reduce the jsdef.DOT list into a AST.identifiers_list[] array (special items for @@INDEX@@, @@THIS@@, @@SUPER@@)
	3. Scopes have ".parentScope" property for faster traversal.
	4. Every jsdef.IDENTIFIER node is "recognized" and linked with its defining Symbol. A Symbol describes an identifier and has
	   a reference to the AST definition node (class, function, function argument, var, enum), a refernce to the execution scope
	   and detailed file and position information.
	5. The compiler is "second-pass" aware in order to resolve all identifiers into symbols regardless of cyclic references.
	6. RULE: All Symbols have the same structure.
	7. Unfortunately I could only preserve the basic syntax and things such as nested classes, inside, exports, imports, etc. I have
	   temporarily removed them in order to clean-up the code.
	8. Beutifier has been beutified and removed de-obfuscators.
	9. Original SymbolsTable and TypeSystem were removed and are now integrated within the compiler.
   10. Added "externs.jspp" for parsing externs such as ECMA objects (Global, Object, Array, String, Boolean, etc.).
   11. Added support for typed arrays using C++ syntax: Array<Class>
   12. Several syntax restrictions have been added in order to make it possible to generate C++ code from JavaScript++ code. For example
       you cannot define arbitrary objects inside JavaScript++ classes like "var x = {};" because it is not possible to generate C++ for
       this (yet).
   13. Prototypes are converted at compile-time to Classes and type detection heuristics are used.
   14. Enums are detected if they follow a consistent syntax "var enum_name = { a:<number>, b:<number>, ... };" and they are converted
       into a class.

	Elias G. Politakis - 11/12/2013
	epolitakis@mobilefx.com

*/

function Compiler(ast, infolder, outfolder, exportSymbols, selectedClass)
{
	// ast				: the abstract syntax tree root node as produced by the parser
	// infoder			: the root input folder containing the source files
	// outfolder		: the root output folder where generated files will be placed
	// selectedClass	: used if we want to parse-only a single class for intelliSence use.

	var _this = this;

	_this.symbolId = -1;
	_this.scopeId = -1;
	_this.currFile = null;
	_this.secondPass = false;
	_this.ast = ast;
    _this.infolder = infolder;
    _this.outfolder = outfolder;
	_this.tokenizer = null;
	_this.fileClasses = {};
	_this.includes = [];
	_this.no_errors = 0;
	_this.errors = [];
	_this.warnings = [];
	_this.scopesStack = [];
	_this.scopesTable = [];
	_this.debugSymbolsTable = [];
	_this.currClassName = null;
	_this.classes = {};
	_this.line_start = -1;
	_this.UNTYPED = "untyped";
	_this.exportSymbols = exportSymbols;
	_this.selectedClass = selectedClass;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Symbol constructors
	function Scope() {}
	function ClassSymbol() {}
	function FunctionSymbol() {}
	function VarSymbol() {}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.types =
	{
		"Array"		: { "default": "[]" },
		"Boolean"	: { "default": "false" },
		"Date"		: {	"default": "new Date" },
		"Function"	: {	"default": "function(){}" },
		"Null"		: { "default": "null" },
		"Number"	: {	"default": "0" },
		"Float"		: { "default": "0" },
		"Integer"	: { "default": "0" },
		"Object"	: { "default": "{}" },
		"RegExp"	: { "default": "/(?:)/" },
		"String"	: { "default": '""' }
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typerules =
	{
		explicit:
		{
			"__UNARY__"		: ["Boolean", "Number", "String"],
			"Array"			: [],
			"Boolean"		: ["Number", "String"],
			"Date"			: ["Number", "String"],
			"Function"		: ["String"],
			"null"			: [],
			"Number"		: ["Boolean", "String"],
			"Object"		: [],
			"RegExp"		: ["Boolean", "Date", "Number", "String"],
			"String"		: ["Boolean", "Date", "Function", "Number", "RegExp"]
		},

		implicit:
		{
			PLUS:	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" }, "String": { "String": "String" } },
			MINUS:	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			MUL: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			DIV: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			MOD:	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			BIT: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number" } },
			ASSIGN: { "Number":	 { "Boolean": "Number",	"Number": "Number" }, "Boolean": { "Boolean": "Number", "Number": "Number" }
			}
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IDE icons that can be set to exported memberlist items in exportCoconutIDESymbols()
	_this.CODE_SYMBOLS_ENUM =
	{
	    SYMBOL_ARGUMENT					   : 0,
	    SYMBOL_ARRAY                       : 1,
	    SYMBOL_BASE_CLASS                  : 2,
	    SYMBOL_BASE_CONSTANT               : 3,
	    SYMBOL_BASE_EVENT                  : 4,
	    SYMBOL_BASE_PRIVATE_FIELD          : 5,
	    SYMBOL_BASE_PRIVATE_FUNCTION       : 6,
	    SYMBOL_BASE_PROTECTED_FIELD        : 7,
	    SYMBOL_BASE_PROTECTED_FUNCTION     : 8,
	    SYMBOL_BASE_PUBLIC_FIELD           : 9,
	    SYMBOL_BASE_PUBLIC_FUNCTION        : 10,
	    SYMBOL_CLASS                       : 11,
	    SYMBOL_CONDITIONAL_BLOCK           : 12,
	    SYMBOL_CONSTANT                    : 13,
	    SYMBOL_CONSTRUCTOR                 : 14,
	    SYMBOL_ENUM                        : 15,
	    SYMBOL_ENUM_ITEM                   : 16,
	    SYMBOL_ERROR                       : 17,
	    SYMBOL_EVENT                       : 18,
	    SYMBOL_FOLDER                      : 19,
	    SYMBOL_HTML                        : 20,
	    SYMBOL_HTML_STYLE                  : 21,
	    SYMBOL_HTML_STYLE_CLASS            : 22,
	    SYMBOL_HTML_STYLE_ID               : 23,
	    SYMBOL_HTML_STYLE_RULE             : 24,
	    SYMBOL_INTERFACE                   : 25,
	    SYMBOL_LOCALS                      : 26,
	    SYMBOL_OBJECT                      : 27,
	    SYMBOL_PACKAGE                     : 28,
	    SYMBOL_PRIVATE_FIELD               : 29,
	    SYMBOL_PRIVATE_FUNCTION            : 30,
	    SYMBOL_PROPERTY                    : 31,
	    SYMBOL_PROTECTED_FIELD             : 32,
	    SYMBOL_PROTECTED_FUNCTION          : 33,
	    SYMBOL_PUBLIC_FIELD                : 34,
	    SYMBOL_PUBLIC_FUNCTION             : 35,
	    SYMBOL_SCRIPT_LIBRARY              : 36,
	    SYMBOL_SYMBOLS                     : 37,
	    SYMBOL_VARIABLE                    : 38,
	    SYMBOL_WAIT                        : 39,
	    SYMBOL_WARNING                     : 40,
	    SYMBOL_WATCH                       : 41
	};

	// ==================================================================================================================================
	//	   ______                      _ __
	//	  / ____/___  ____ ___  ____  (_) /__
	//	 / /   / __ \/ __ `__ \/ __ \/ / / _ \
	//	/ /___/ /_/ / / / / / / /_/ / / /  __/
	//	\____/\____/_/ /_/ /_/ .___/_/_/\___/
	//	                    /_/
	// ==================================================================================================================================

	_this.compile = function()
	{
		// Pre-preocess ast
		_this.preprocess(ast);

		// First pass to record symbols
		_this.generate(ast);

		if(!_this.selectedClass)
		{
			// Reset for second pass
			_this.symbolId = -1;
			_this.scopeId = -1;
			_this.secondPass = true;
			_this.errors = [];
			_this.warnings = [];
			_this.scopesStack = [];
			_this.scopesTable = [];
			_this.debugSymbolsTable = [];
			_this.currClassName = null;
			_this.line_start = -1;

			// Second pass to generate actual code
			_this.generate(ast);
		}

		// Post-process to extract code and debug symbols
		_this.exportCoconutIDESymbols();
	};

	// ==================================================================================================================================
	//	    ____
	//	   / __ \________  ____  _________  ________  __________
	//	  / /_/ / ___/ _ \/ __ \/ ___/ __ \/ ___/ _ \/ ___/ ___/
	//	 / ____/ /  /  __/ /_/ / /  / /_/ / /__/  __(__  |__  )
	//	/_/   /_/   \___/ .___/_/   \____/\___/\___/____/____/
	//	               /_/
	// ==================================================================================================================================

	_this.preprocess = function(ast, pass)
	{
		var _this = this;
		_this.tokenizer = ast.tokenizer;

	    // Descent the ast to redeuce properties for
	    // DOTs and set parent node to all ast nodes.

		function descend(node)
		{
			node.__visited=true;

			if(node.type==jsdef.CLASS)
			{
				if(!_this.fileClasses[node.file]) _this.fileClasses[node.file]={};
				_this.fileClasses[node.file][node.name] = node;
			}

			// Add some information to DOT and its nodes for speed.
			if(node.type==jsdef.DOT)
			{
				node.identifiers_list = _this.reduceProps(node);
				node.identifier_first = node.identifiers_list[0].ast;
				node.identifier_last = node.identifiers_list[node.identifiers_list.length-1].ast;

				var values = [];
				for(var i=0,L=node.identifiers_list.length;i<L;i++)	values.push(node.identifiers_list[i].value);
				node.value = values.join(".");

				for(var i=node.identifiers_list.length;i--;)
				{
					if(node.identifiers_list[i].value!="@@INDEX@@")
					{
						node.identifier_last = node.identifiers_list[i].ast;
						break;
					}
				}
			}

			var nodes = [];

			for(var item in node)
			{
				switch(item)
				{
					case "tokenizer":
					case "identifiers_list":
					case "identifier_first":
					case "identifier_last":
						break;

					default:

						if(typeof node[item] === 'object'  && !node[item].__visited)
						{
							descend(node[item]);
							node[item].parent = node;
							nodes.push(node[item]);
						}
				}
			}
			nodes = null;

			node.nodeType = GLOBAL.narcissus.jsdefNames[node.type];
			node.source = _this.tokenizer.source.slice(node.start, node.end);
			var o_start = (node.__filePosOffset - (node.line_start - node.__fileLineOffset)+1);
			var o_end = (node.__filePosOffset - (node.line_end - node.__fileLineOffset)+1);
			node.start -= o_start;
			node.end -= o_end;
			node.__start -= o_start;
			node.__end -= o_start;
			node.line_start -= node.__fileLineOffset;
			node.line_end -= node.__fileLineOffset;
			node.tokenizer = null;
			delete node.tokenizer;
		}

		descend(ast);
		return ast;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.reduceProps = function(ast)
	{
		var _this = this;
		var out = [];

		switch (ast[0].type)
		{
			case jsdef.IDENTIFIER:
			case jsdef.TRUE:
			case jsdef.FALSE:
			case jsdef.NULL:
				out.push({ast:ast[0], value:ast[0].value});
				break;

			case jsdef.DOT:
			case jsdef.INDEX:
			case jsdef.GROUP:
			case jsdef.CALL:
				out = out.concat(_this.reduceProps(ast[0]));
				break;

			case jsdef.THIS:
				out.push({ast:ast[0], value:"@@THIS@@"});
				break;

			case jsdef.SUPER:
				out.push({ast:ast[0], value:"@@SUPER@@"});
				break;

			default:
				break;
		}

		if (ast.type == jsdef.DOT)
			out.push({ast:ast[1], value:ast[1].value});

		else if (ast.type == jsdef.INDEX)
			out.push({ast:ast, value:"@@INDEX@@"} );

		return out;
	};

	// ==================================================================================================================================
	//	   _____                          __  ___
	//	  / ___/_________  ____  ___     /  |/  /___ _______________  _____
	//	  \__ \/ ___/ __ \/ __ \/ _ \   / /|_/ / __ `/ ___/ ___/ __ \/ ___/
	//	 ___/ / /__/ /_/ / /_/ /  __/  / /  / / /_/ / /__/ /  / /_/ (__  )
	//	/____/\___/\____/ .___/\___/  /_/  /_/\__,_/\___/_/   \____/____/
	//	               /_/
	// ==================================================================================================================================

	_this.NewScope = function(ast)
	{
		var scope = null;

		if(_this.secondPass)
		{
			scope = ast.scope;
		}
		else
		{
			var parentScope = _this.scopesStack.length ? _this.scopesStack[_this.scopesStack.length-1] : null;

			scope = new Scope();

			var name = _this.scopesStack.length==0 ? "GLOBAL_SCOPE" : ast.name;
			if(!name) name = ast.parent.value;
			if(_this.currClassName) name = _this.currClassName + ":" + name;

			scope.scopeId		= (++_this.scopeId);
			scope.name			= _this.scopesStack.length==0 ? "GLOBAL_SCOPE" : name;
			scope.parentScope	= parentScope;
			scope.childScopes	= [];
			scope.ast			= ast;
			scope.className		= _this.currClassName;
			scope.type			= ast.type;
			scope.nodeType		= ast.nodeType;
			scope.isGlobal		= _this.scopesStack.length==0;
			scope.isClass		= ast.type==jsdef.CLASS;
			scope.isMethod		= ast.type==jsdef.FUNCTION;
			scope.file			= ast.file;
			scope.path			= ast.path;
			scope.start			= ast.start;
			scope.end			= ast.end;
			scope.line_start	= ast.line_start;
			scope.line_end		= ast.line_end;
			scope.vars			= new Object();
			scope.methods		= new Object();
			scope.vartypes		= new Object();

			if(parentScope) parentScope.childScopes.push(scope);
			ast.scope = scope;
		}

		_this.scopesTable.push(scope);
		_this.scopesStack.push(scope);
		return scope;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.ExitScope = function()
	{
		return _this.scopesStack.pop();
	};

	// ==================================================================================================================================
	//	   _____                 __          __   __                __
	//	  / ___/__  ______ ___  / /_  ____  / /  / /   ____  ____  / /____  ______  _____
	//	  \__ \/ / / / __ `__ \/ __ \/ __ \/ /  / /   / __ \/ __ \/ //_/ / / / __ \/ ___/
	//	 ___/ / /_/ / / / / / / /_/ / /_/ / /  / /___/ /_/ / /_/ / ,< / /_/ / /_/ (__  )
	//	/____/\__, /_/ /_/ /_/_.___/\____/_/  /_____/\____/\____/_/|_|\__,_/ .___/____/
	//	     /____/                                                       /_/
	// ==================================================================================================================================

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.LookupIdentifier = function(scope, identifier, ast, noWarning)
	{
		if(!identifier || !scope) return;

		function __doLookupSymbol(scope, identifier, ast)
		{
			var symbol = null;

			// If the identifier is not in a DOT or if the identifier
			// is the first item in a DOT then we perform a scope lookup.
			// Otherwise, we perform a dot symbol Lookup.

			var parent = ast ? ast.parent : null;
			while(parent && !parent.identifiers_list) { parent = parent.parent; }
			var searchScope = (!parent || (parent && parent.identifiers_list && parent.identifiers_list[0].value==identifier));

			// Lookup scope chain (classes, base clasees, methods, base class methods, variables, etc.)
			if(searchScope)	symbol = _this.LookupScopeChain(identifier, scope, true);

			// Lookup DOT chain.
			if(!symbol && _this.secondPass && parent && parent.identifiers_list)
			{
				symbol = _this.LookupLastDotIdentifier(parent, scope);
			}

			return symbol;
		}

		var symbol = null;
		switch(identifier)
		{
			case "prototype":		symbol = _this.getClass("Prototype"); break;
			case "@@THIS@@": 		symbol = _this.getCurrentClass(); break;
			case "@@SUPER@@":		symbol = _this.getCurrentClass().baseSymbol; break;
			case "window":			symbol = _this.getClass("HTMLWindow"); break;
			case "document":		symbol = _this.getClass("HTMLDocument"); break;
			case "canvas":			symbol = _this.getClass("HTMLCanvasElement"); break;
			case "global":			symbol = _this.getClass("Global"); break;
			case "engine":			symbol = _this.getClass("CocoEngine"); break;

			case "CallbackManager":	symbol = _this.getClass("CallbackManager");

			default:
				symbol = _this.getClass(identifier) || __doLookupSymbol(scope, identifier, ast);
				break;
		}

		if(!noWarning && _this.secondPass && !symbol)
		{
			if(_this.isInside(ast, null, "isPrototype", true))
			{
				return null;
			}

			if(_this.currClassName)
				_this.NewError("Symbol not found: " + identifier, ast || scope);
		}

		return symbol;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.LookupLastDotIdentifier = function(ast, scope)
	{
		if(!ast || !scope || !ast.identifiers_list) return null;

		var dot = ast.source;
		var identifier = ast.identifiers_list[ast.identifiers_list.length-1].value;
		var symbol = null;

		// Start descending dot chain.
		for(var i=0; i<ast.identifiers_list.length;i++)
		{
			var vartype = null;
			var nodeSymbol = _this.LookupIdentifier(scope, ast.identifiers_list[i].value, null, true);
			if(!nodeSymbol) break;
			if(i==ast.identifiers_list.length-1)
			{
				symbol = nodeSymbol;
				break;
			}
			if(nodeSymbol.type==jsdef.CLASS)
			{
				// Reached a class, can't go deeper.
				symbol = _this.LookupIdentifier(nodeSymbol.scope, identifier, null, true);
				break;
			}
			else if(i<ast.identifiers_list.length-1 && ast.identifiers_list[i+1].value=="@@INDEX@@")
			{
				vartype = nodeSymbol.subtype;
				i++;
				if(i==ast.identifiers_list.length-1)
				{
					symbol = _this.getClass(vartype);
					return symbol;
				}
			}
			else
			{
				vartype = nodeSymbol.vartype;
			}
			if(!vartype) break;
			var cls = _this.getClass(vartype);
			if(!cls) break;
			scope = cls.scope;
		}
		return symbol;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.LookupScopeChain = function(identifier, scope, deep)
	{
		if(!scope) return;
		var symbol = null;

        // Search scope methods
		if(!symbol) for(var name in scope.methods)
		{
			if(name==identifier)
			{
				symbol = scope.methods[name];
				break;
			}
		}

		// Search scope vars and enums
		if(!symbol) for(var name in scope.vars)
		{
			if(name==identifier)
			{
				symbol = scope.vars[name];
				break;
			}
		}

      	// Search base class method
		if(!symbol && scope.isMethod && scope.ast.symbol && scope.ast.symbol.baseSymbol)
		{
			symbol = _this.LookupScopeChain(identifier, scope.ast.symbol.baseSymbol.scope, deep);
		}

		// Search base class members
		if(!symbol && scope.isClass && scope.ast.symbol && scope.ast.symbol.baseSymbol)
		{
			symbol = _this.LookupScopeChain(identifier, scope.ast.symbol.baseSymbol.scope, deep);
		}

		// Found it!
		if(symbol) return symbol;

   		// Identifier not found in current scope, move to parent scope.
		if(deep && scope.parentScope)
			return _this.LookupScopeChain(identifier, scope.parentScope, deep);
	};

	// ==================================================================================================================================
	//	    __  ___
	//	   /  |/  /___ _______________  _____
	//	  / /|_/ / __ `/ ___/ ___/ __ \/ ___/
	//	 / /  / / /_/ / /__/ /  / /_/ (__  )
	//	/_/  /_/\__,_/\___/_/   \____/____/
	//
	// ==================================================================================================================================

	_this.NewWarning = function (e, node)
	{
		if(_this.selectedClass || _this.no_errors>0) return;
		trace("@@ WARNING: " + e + " in file " + node.path + " at line " + node.line_start);
		jsppCallback("warning", node.path, "", node.line_start, 0, e);
		_this.warnings.push(e);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewError = function (e, node)
	{
		if(_this.selectedClass || _this.no_errors>0) return;
		trace("@@ ERROR: " + e + " in file " + node.path + " at line " + node.line_start);
		jsppCallback("error", node.path, "", node.line_start, 0, e);
		_this.errors.push(e);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getCurrentClass = function()
	{
		return _this.classes[_this.currClassName];
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getCurrentScope = function()
	{
		return _this.scopesStack[_this.scopesStack.length-1];
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getClass = function(vartype)
	{
		if(!vartype) return null;
		vartype = _this.getVarType(vartype);
		var cls = (vartype && _this.classes.hasOwnProperty(vartype) ? _this.classes[vartype] : null);
		return cls;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getClassScope = function()
	{
		var scope = _this.getCurrentScope();
		while(scope)
		{
			if(scope.isClass)
				return scope;
			scope = scope.parentScope;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isInside = function(ast, jsdefType, propName, propValue)
	{
		if(!ast) return false;
		for(var p=ast.parent;p!=null;p=p.parent)
		{
			if(jsdefType !=null && p.type==jsdefType)
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
			else if(propName && propValue)
			{
				if(p[propName]==propValue)
					return true;
			}
		}
		return false;
	};

	// ==================================================================================================================================
	// ==================================================================================================================================
	// ==================================================================================================================================
	// ==================================================================================================================================
	//	   ______          __        ______                           __
	//	  / ____/___  ____/ /__     / ____/__  ____  ___  _________ _/ /_____  _____
	//	 / /   / __ \/ __  / _ \   / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/
	//	/ /___/ /_/ / /_/ /  __/  / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /
	//	\____/\____/\__,_/\___/   \____/\___/_/ /_/\___/_/   \__,_/\__/\____/_/
	//
	// ==================================================================================================================================
	// ==================================================================================================================================
	// ==================================================================================================================================
	// ==================================================================================================================================

	_this.generate = function(ast)
	{
		var _this = this, out = [], ast = ast || _this.ast, scope;

		var generate = function()
		{
			return _this.generate.apply(_this, Array.prototype.slice.call(arguments,0));
		};

		// Add debug line
		if(_this.line_start != ast.line_start)
		{
			_this.line_start != -1 && out.push("\n");
			out.push("\/\/@line " + ast.line_start + "\n");
			_this.line_start = ast.line_start;
		}

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

		case jsdef.INCLUDE:
			_this.includes.push(ast.include);
			break;

		case jsdef.CLASS:

		 	_this.currClassName = ast.name;

		 	// Class must know its includes
		 	ast.includes = _this.includes;
		 	ast.fileClasses = _this.fileClasses;

			var constructor = null;
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";
			var baseClass = ast.extends ? ast.extends.value : undefined;
			var baseClassSymbol = _this.getClass(baseClass);
			var baseClassId = baseClassSymbol ? baseClassSymbol.ast.symbol.classId : null;
			var isGlobalClass = (ast.name=="Global");
			var scope = (isGlobalClass ? _this.scopesStack[0] : _this.NewScope(ast));

			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId	= (++_this.symbolId);
				classSymbol.name		= ast.name;
				classSymbol.vartype		= ast.name;
				classSymbol.classId		= classId;
				classSymbol.base		= baseClass;
				classSymbol.baseSymbol	= baseClassSymbol;
				classSymbol.type		= ast.type;
				classSymbol.nodeType	= ast.nodeType;
				classSymbol.isPrototype = false;
				classSymbol.isEnum		= false;
				classSymbol.ast			= ast;
				classSymbol.scope		= scope;
				classSymbol.file		= ast.file;
				classSymbol.path		= ast.path;
				classSymbol.start		= ast.start;
				classSymbol.end			= ast.end;
				classSymbol.line_start	= ast.line_start;
				classSymbol.line_end	= ast.line_end;
				classSymbol.scopeId		= scope.scopeId;
				classSymbol.vars		= scope.vars;
				classSymbol.methods	 	= scope.methods;
			}
			ast.symbol = classSymbol;
			_this.classes[ast.name] = classSymbol;
			if(baseClass) scope.vartypes[baseClass] = true;

			// Roger Poon JavaScript++ class definition
			out.push("function " + ast.name + "(){");
			out.push("var __SUPER__" + (baseClassId ? "," + baseClassId : "") + ";");
			out.push("return ((function(){");
			out.push("var " + classId + "=this,");
			out.push("__PDEFINE__={}.constructor.defineProperty,");
			out.push("__NOENUM__={enumerable:false};");
			out.push("if(typeof __PDEFINE__!='function')__PDEFINE__=null;");
			out.push("/*@cc_on @if(1)try{({}).constructor.defineProperty({},'x',{})}catch(e){__PDEFINE__=null}@end @*/");
			out.push("this.__SUPER__=__SUPER__;");
			out.push("__PDEFINE__&&__PDEFINE__(this,'__SUPER__',__NOENUM__);");
			out.push("this.__CLASS__='" + ast.name + "';");
			out.push("this.__PROTECTED__={};");
			out.push("__PDEFINE__&&__PDEFINE__(this,'__PROTECTED__',__NOENUM__);");

			//Inherit public and protected members
			if(baseClass)
			{
				if(_this.secondPass && baseClass && !_this.getClass(baseClass))
					_this.NewError("Base class not found: " + baseClass, ast);

				var prop = "__TMP_MEMBER__", superClassTmp = "__TMP_SUPER__", varArray = "__TMP_ARRAY__";

				//Public members
				out.push("var " + superClassTmp + "=__SUPER__," + varArray + "=[];");
				out.push("for(var " + prop + " in " + superClassTmp + ")");
				out.push(varArray + ".push(" + prop + "+'=" + superClassTmp + ".'+" + prop + ");");
				out.push(varArray + ".length&&eval('var '+" + varArray + ".join()+';');");

				//Protected members
				out.push(superClassTmp + "=__SUPER__.__PROTECTED__;" + varArray + ".length=0;");
				out.push("for(var " + prop + " in " + superClassTmp + "){");
				out.push(varArray + ".push(" + prop + "+'=" + superClassTmp + ".'+" + prop + ");");
				out.push("this.__PROTECTED__[" + prop + "]=" + superClassTmp + "[" + prop +"];}");
				out.push(varArray + ".length&&eval('var '+" + varArray + ".join()+';');");
			}

			// Class Methods
			for(var item in ast.body)
			{
				if(!isFinite(item)) continue;
				var member = ast.body[item];
				switch(member.type)
				{
					case jsdef.FUNCTION:
						if(member.name=="Constructor") { member.isConstructor=true; constructor = member; continue; }
						out.push(generate(member));
						break;
				}
			}

			// Class Fields
			for(var item in ast.body)
			{
				if(!isFinite(item)) continue;
				var member = ast.body[item];
				switch(member.type)
				{
					case jsdef.CONST:
					case jsdef.VAR:
						out.push(generate(member));
						break;
				}
			}

			// Constructor
			out.push(constructor ? generate(constructor) : "this.Constructor=function(){return " + classId + "};");
			out.push("__PDEFINE__&&__PDEFINE__(this,'Constructor',__NOENUM__);");

			out.push("return this");
			out.push("}).call(");

	   		// Class initialization
			if(baseClass)
				out.push("(function(o){return (F.prototype=__SUPER__=" + baseClassId + "__=o,new F);function F(){}})(new " + baseClass + ")");
			else
				out.push("{}");
			out.push("))");
			out.push(".Constructor.apply(this,[].slice.call(arguments))}");

			_this.currClassName = null;

			if(!isGlobalClass)
				_this.ExitScope();

			///////////////////////////////////////////////
			// Save compiled object JavaScript code.
			///////////////////////////////////////////////
			if(!_this.selectedClass && _this.secondPass && ast.path && ast.file!="externs.jspp" && _this.infolder && _this.outfolder)
			{
				var file = ast.path;
				file = file.replace(_this.infolder, _this.outfolder).replace(".jspp", ".jobj");
				var buff = do_js_beautify(out.join("\n"), 1, false, false, true);
				buff = RxReplace(buff, "//@line \\d+[\\s\\t\\n\\r]+//@line (\\d+)", "mg", "//@line $1");
				buff = RxReplace(buff, "//@line \\d+[\\s\\t\\n\\r]+\\{", "mg", "{");
				jsppCallback("module", ast.path, file, 0, 0, buff);
				trace("Generated file: " + file);
			}
			break;

		// ==================================================================================================================================
		//	    ______                 __  _
		//	   / ____/_  ______  _____/ /_(_)___  ____
		//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \
		//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / /
		//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/
		//
		// ==================================================================================================================================

		case jsdef.FUNCTION:

			ast.isPointer = __isPointer(ast.returntype);

			var methodScope = _this.NewScope(ast);
			var parentScope = methodScope.parentScope;
			var isClass = parentScope.isClass;
			var className = isClass ? parentScope.name : null;
			var classId = isClass ? parentScope.ast.symbol.classId : null;
			var isGlobal = !isClass && parentScope.isGlobal;
			var isAnonymous = (ast.name==null || ast.name.length==0);
			var fnName = (ast.name ? ast.name : "");
			var baseMethodSymbol = null;

			if(_this.currClassName) _this.debugSymbolsTable.push("<!-- " + className + " :: " + fnName + " -->\n");

			// Link method symbol with base class method symbol for speed.
			if(isClass && parentScope.ast.symbol.baseSymbol)
				baseMethodSymbol = _this.LookupIdentifier(parentScope.ast.symbol.baseSymbol.scope, ast.name, ast, true);

			if(!_this.secondPass && !isAnonymous && Object.prototype.hasOwnProperty.call(parentScope.methods,fnName))
				_this.NewError("Redeclaration of function " + fnName, ast);

			// Function Symbol
			var functionSymbol = new FunctionSymbol();
			{
				functionSymbol.symbolId		= (++_this.symbolId);
				functionSymbol.name			= fnName;
				functionSymbol.type			= ast.type;
				functionSymbol.nodeType		= ast.nodeType;
				functionSymbol.className	= isClass ? className : null;
				functionSymbol.classId		= isClass ? classId : null;
				functionSymbol.public		= ast.public==true;
				functionSymbol.private		= ast.private==true;
				functionSymbol.protected	= ast.protected==true;
				functionSymbol.static		= ast.static==true;
				functionSymbol.ast			= ast;
				functionSymbol.scope		= methodScope;
				functionSymbol.baseSymbol	= baseMethodSymbol;
				functionSymbol.file			= ast.file;
				functionSymbol.path			= ast.path;
				functionSymbol.start		= isClass && !isAnonymous ? ast.__start : ast.start;
				functionSymbol.end			= isClass && !isAnonymous ? ast.__end : ast.end;
				functionSymbol.line_start	= ast.line_start;
				functionSymbol.line_end		= ast.line_end;
				functionSymbol.scopeId		= methodScope.scopeId;
				functionSymbol.vartype		= ast.returntype;
				functionSymbol.subtype		= ast.subtype ? ast.subtype : _this.getSubType(ast.returntype);
				functionSymbol.paramsList	= ast.paramsList;
				functionSymbol.arguments	= {};
			}

			ast.symbol = functionSymbol;
			parentScope.methods[ast.name] = functionSymbol;

			if(functionSymbol.subtype)
				parentScope.vartypes[functionSymbol.subtype] = true;
			else if(functionSymbol.vartype)
				parentScope.vartypes[functionSymbol.vartype] = true;

			// Arguments List
			var paramsList = "(";
			for(var i=0; i<ast.paramsList.length; i++)
			{
				var param = ast.paramsList[i];
				param.isPointer = __isPointer(param.vartype);
				paramsList += param.name;
				if(i!=ast.paramsList.length-1) paramsList +=", ";

				if(_this.secondPass && _this.currClassName)
				{
					if(!param.vartype)
						_this.NewError("Type declaration missing " + param.name, param);
					else if(!_this.getClass(param.vartype))
						_this.NewError("Class not found: " + param.vartype, param);
				}

	            // Argument Symbol
				var varSymbol = new VarSymbol();
				{
					varSymbol.symbolId		= (++_this.symbolId);
					varSymbol.name			= param.name;
					varSymbol.value			= null;
					varSymbol.type			= param.type;
					varSymbol.nodeType		= param.nodeType;
					varSymbol.classId		= null;
					varSymbol.public		= false;
					varSymbol.private		= false;
					varSymbol.protected		= false;
					varSymbol.static		= false;
					varSymbol.optional		= param.optional;
					varSymbol.constant		= false;
					varSymbol.ast			= param;
					varSymbol.scope			= methodScope;
					varSymbol.baseSymbol	= null;
					varSymbol.file			= param.file;
					varSymbol.path			= param.path;
					varSymbol.start			= param.start;
					varSymbol.end			= param.end;
					varSymbol.line_start	= param.line_start;
					varSymbol.line_end		= param.line_end;
					varSymbol.scopeId		= methodScope.scopeId;
					varSymbol.vartype		= param.vartype;
					varSymbol.subtype		= param.subtype ? param.subtype : _this.getSubType(param.vartype);
					varSymbol.pointer		= param.isPointer;
				}
				param.symbol = varSymbol;
				methodScope.vars[param.name] = varSymbol;
				functionSymbol.arguments[varSymbol.name] = varSymbol;

				if(varSymbol.subtype)
					parentScope.vartypes[varSymbol.subtype] = true;
				else if(varSymbol.vartype)
						parentScope.vartypes[varSymbol.vartype] = true;

			}
			paramsList += ")";

	        // Global scope function
	        if(isGlobal)
	        {
	  			out.push("function " + fnName + paramsList + "{");
				out.push(generate(ast.body));
				out.push("}");
	        }

	        // Class member function
	        else if(isClass)
	        {
	  			// Function definition
	  			if(ast.isConstructor)
	  			{
	  			 	out.push("this.Constructor=function(){");
					for(var i=0; i<ast.paramsList.length; i++)
					{
						var param = ast.paramsList[i];
						out.push("var " + param.name + "=arguments[" + i + "];");
					}
	  			}
	  			else
	  			{
	  				if(ast.public)
	  				{
	  					out.push("var " + fnName + " = this." + fnName + "=function" + paramsList + "{");
	  				}
	  				else if(ast.private)
	  				{
	  					out.push("var " + fnName + "=function" + paramsList + "{");
	  				}
	  				else if(ast.protected)
	  				{
	  					out.push("this.__PROTECTED__." + fnName + "=function" + paramsList + "{");
	  				}
	  			}

				// Function Body
				out.push(generate(ast.body));

				// Default return value
				if(ast.isConstructor)
				{
					out.push("return " + classId);
				}
				else
				{
					var vartype = _this.getVarType(ast.returntype);
					if(_this.types.hasOwnProperty(vartype))
						out.push("return " + _this.types[vartype].default);
				}

				if(_this.secondPass && ast.returntype && !_this.getClass(ast.returntype))
					_this.NewError("Return type not found " + ast.returntype, ast);

				out.push("};");
	        }

	        // Anonymous function
	        else if(isAnonymous)
	        {
	  			out.push("function " + fnName + paramsList + "{");
				out.push(generate(ast.body));
				out.push("}");
	        }

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

			ast.scope = _this.getCurrentScope();
			var classSymbol = ast.scope.isClass ? ast.scope.ast : null;
			var firstItem = true;

			if(ast.scope.isClass)
			{
				// Declare class variable depending on its modifier
				if(ast.public)
				{
					out.push("this.");
				}
				else if(ast.private)
				{
					out.push("var ");
				}
				else if(ast.protected)
				{
					out.push("this.__PROTECTED__.");
				}
			}
			else
			{
				// Standard var declaration
				out.push("var ");
			}

			// Process var items to record symbols and generate code
			for(var item in ast)
			{
				if(!isFinite(item)) continue;

				if(!ast[item].vartype && _this.currClassName)
					_this.NewError("Type declaration missing " + ast[item].name, ast);

				if(_this.secondPass && _this.currClassName && !_this.getClass(ast[item].vartype))
					_this.NewError("Class not found: " + ast[item].vartype, ast[item]);

				if(!_this.secondPass)
				{
					if(Object.prototype.hasOwnProperty.call(ast.scope.vars,ast[item].name))
						_this.NewError("Redeclaration of variable " + ast[item].name + " in current scope", ast[item]);

	       			var classScope = _this.getClassScope();
					if(classScope && !_this.isInside(ast[item], jsdef.BLOCK) && Object.prototype.hasOwnProperty.call(classScope.vars, ast[item].name))
					{
						_this.NewWarning("Found declaration of variable " + ast[item].name + " in class scope", ast[item]);
					}
				}

				ast[item].isPointer = __isPointer(ast[item].vartype);

				var varSymbol = new VarSymbol();
				{
					varSymbol.symbolId		= (++_this.symbolId);
					varSymbol.name			= ast[item].name;
					varSymbol.value			= null;
					varSymbol.type			= ast[item].type;
					varSymbol.nodeType		= ast[item].nodeType;
					varSymbol.classId		= ast.scope.isClass ? ast.scope.ast.symbol.classId : null;
					varSymbol.public		= ast.public;
					varSymbol.private		= ast.private;
					varSymbol.protected		= ast.protected;
					varSymbol.static		= ast.static;
					varSymbol.optional		= false;
					varSymbol.constant		= ast.type==jsdef.CONST;
					varSymbol.ast			= ast[item];
					varSymbol.scope			= ast.scope;
					varSymbol.baseSymbol	= null;
					varSymbol.file			= ast[item].file;
					varSymbol.path			= ast[item].path;
					varSymbol.start			= ast[item].start;
					varSymbol.end			= ast[item].end;
					varSymbol.line_start	= ast[item].line_start;
					varSymbol.line_end		= ast[item].line_end;
					varSymbol.scopeId		= ast.scope.scopeId;
					varSymbol.vartype		= ast[item].vartype;
					varSymbol.subtype		= ast[item].subtype ? ast[item].subtype : _this.getSubType(ast[item].vartype);
					varSymbol.pointer		= ast[item].isPointer;
				};

				ast[item].symbol = varSymbol;
				ast.scope.vars[ast[item].name] = varSymbol;
				if(classSymbol)
				{
					if(varSymbol.subtype)
						classSymbol.scope.vartypes[varSymbol.subtype] = true;
					else if(varSymbol.vartype)
						classSymbol.scope.vartypes[varSymbol.vartype] = true;
				}

				if(!firstItem) out.push(", ");
				out.push(ast[item].name);

				if(ast[item].initializer)
				{
					// Generate initializer
					if(_this.currClassName && ast.type!=jsdef.CONST && ast.scope.isClass)
						_this.NewError("Invalid member class initializer, should be in constructor: " + ast[item].name, ast[item]);

					out.push("=");
					out.push(generate(ast[item].initializer));
				}
				else
				{
					var vartype = _this.getVarType(ast[item].vartype);
					if(_this.types.hasOwnProperty(vartype))
						out.push("="+_this.types[vartype].default);
					else if(ast.scope.isClass)
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
			out.push("__SUPER__");
			ast.symbol = _this.getCurrentClass().baseSymbol;
			ast.runtime = "__SUPER__." + ast.symbol.classId;
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.THIS:
			if(_this.isInside(ast, jsdef.FUNCTION) && _this.isInside(ast, jsdef.CLASS))
			{
				ast.symbol = _this.getCurrentClass();
				ast.runtime = ast.symbol.classId;
				var scope = _this.getClassScope();
				out.push(scope.ast.symbol.classId);
			}
			else
				out.push("this");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DOT:
			out.push(generate(ast[0]));
			out.push(".");
			out.push(generate(ast[1]));
			_this.addDebugSymbol(ast, out.join(""));
			if(_this.secondPass) ast[0].vartype = _this.getTypeName(ast[0]);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.INDEX:
			out.push(generate(ast[0]));
			ast.generated_index = "[" + generate(ast[1]) + "]";
			out.push(ast.generated_index);
			if(_this.secondPass) ast[0].vartype = _this.getTypeName(ast[0]);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.IDENTIFIER:

			var isDot = false;
			if(_this.secondPass)
			{
				// Link identifier with symbol.
				if(!ast.symbol)
					ast.symbol = _this.LookupIdentifier(_this.getCurrentScope(), ast.value, ast);

				// If the identifier is class member then produce a DOT with the classId.
				if(_this.currClassName && ast.symbol && !ast.symbol.private && ast.symbol.classId && ast.symbol.type!=jsdef.CLASS)
				{

					var p = ast.parent;
					while(p)
					{
						if(p.type==jsdef.DOT && p.identifiers_list[0].value!=ast.value)
						{
							isDot = true;
							break;
						}
						p = p.parent;
					}
					if(!isDot)
					{
						// Nasty Hack: if file is different between ast node and symbol, assume base class.
						if(_this.getCurrentClass() && ast.symbol.path!=ast.path)
							out.push(_this.getCurrentClass().classId + ".__SUPER__.");
						else
							out.push(ast.symbol.classId+".");
					}
				}
			}
			out.push(ast.value);

			// Debug Symbol
			if(ast.symbol)
			{
				ast.symbol.runtime = out.join("");
				_this.addDebugSymbol(ast, ast.symbol.runtime);
			}
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
			ast.name = "SCRIPT";
			var body = [];
			if(_this.scopesStack.length==0) body.push("var global=(function(){return this}).call();");
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
			ast.name = "BLOCK";
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

			if(_this.secondPass && _this.currClassName)
				_this.checkFunctionCall(ast);

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
			out.push("[");
			var firstItem = true;
			for(var item in ast)
			{
				if(!isFinite(item)) continue;
				if(!firstItem) out.push(",");
				out.push(generate(ast[item]));
				firstItem = false;
			}
			out.push("]");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.OBJECT_INIT:
			if(_this.secondPass && _this.currClassName) _this.NewError("Illegal object initialization inside class", ast);
			_this.processEnum(ast);
			out.push("{");
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
			out.push(generate(ast[0]));
			out.push(ast.value);
			if(ast.value != "=") out.push("=");
			out.push(generate(ast[1]));

			if(ast[0][0] && ast[0][0][1] && ast[0][0][1].value=="prototype")
				_this.processPrototype(ast);

			if(ast[0].type==jsdef.THIS)
			{
				_this.NewError({type:ReferenceError, message:"Cannot assign to 'this'"},ast);
			}
			else if(ast[0].type != jsdef.IDENTIFIER && ast[0].type != jsdef.DOT && ast[0].type != jsdef.INDEX)
			{
				_this.NewError({type:ReferenceError, message:"Invalid left-hand assignment"},ast);
			}
		    _this.typeCheck(ast, _this.getTypeName(ast[0]), _this.getTypeName(ast[1]));

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
			out.push("for(" + (ast.iterator.type == jsdef.VAR ?	"var " + ast.iterator[0].value : ast.iterator.value));
			out.push(" in " + (ast.object ? generate(ast.object) : "") + ")");
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

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.STRING:

			switch(ast.value)
			{
			case "#ignore_errors_begin":
				_this.no_errors++;
				break;

			case "#ignore_errors_end":
				_this.no_errors--;
				break;

			default:
				out.push('"' + ast.value + '"');
			}

			// When file changes we must reset the scopeId counter.
			if(_this.currFile!=ast.path)
			{
				_this.scopeId = -1;
				_this.currFile = ast.path;
				_this.includes = [];
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.REGEXP:
			if(ast.value[0] == "x") ast.value[2] = ast.value[2].replace(/\s+|#.*/gm, "");
			if(ast.value[1] == "/")
			{
				try
				{
					out.push(RegExp(ast.value[2]) + ast.value[3]);
				}
				catch(e)
				{
					//Catch malformed regex patterns, etc.
					this.NewError({type: e.constructor, message: e.message}, ast);
				}
			}
			else
			{
				var rePattern = ast.value[2].replace(new RegExp("\/", "gmi"), "\\/");
				try
				{
					RegExp(rePattern);
					out.push("/" + rePattern + "/" + ast.value[3]);
				}
				catch(e)
				{
					this.NewError({type: e.constructor, message: e.message }, ast);
				}
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
		case jsdef.DEBUGGER:			out.push("debugger;"); break;
		case jsdef.EXPONENT:			out.push("Math.pow(" + generate(ast[0]) + "," + generate(ast[1]) + ")");break;
		case jsdef.MOD:					out.push(generate(ast[0])); out.push("%"); out.push(generate(ast[1])); break;
		case jsdef.NEW: 				out.push("new "); out.push(generate(ast[0])); break;
		case jsdef.THROW:				out.push("throw "); out.push(generate(ast.exception)); out.push(";"); break;

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
		case jsdef.NULL:				out.push("null"); break;
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
			//debugger;
		}

		return out.join("");
	};

	// ==================================================================================================================================
	//	    ______                         __           ________
	//	   / ____/___  __  ______ ___     / /_____     / ____/ /___ ___________
	//	  / __/ / __ \/ / / / __ `__ \   / __/ __ \   / /   / / __ `/ ___/ ___/
	//	 / /___/ / / / /_/ / / / / / /  / /_/ /_/ /  / /___/ / /_/ (__  |__  )
	//	/_____/_/ /_/\__,_/_/ /_/ /_/   \__/\____/   \____/_/\__,_/____/____/
	//
	// ==================================================================================================================================

	_this.processEnum = function(ast)
	{
		var _this = this;
		if(ast.parent.type!=jsdef.IDENTIFIER) return null;
		var symbol = _this.LookupIdentifier(_this.getCurrentScope(), ast.parent.value, ast.parent, true);
		if(!symbol) return null;

		// Sanity check for enum
		var isEnum = true;
		var vartype = null;
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
		    if(ast[item][1].type==jsdef.NUMBER)
		    {
		    	if(!vartype) vartype = "Number";
		    	if(vartype!="Number") return null;
		    	continue;
		    }
		    if(ast[item][1].type==jsdef.STRING)
		    {
		    	if(!vartype) vartype = "String";
		    	if(vartype!="String") return null;
		    	continue;
		    }
		    isEnum=false;
		    break;
		}
		if(!isEnum) return null;

		// Object Initialization is Enum, delete old symbol (identifier in global scope),
		// define a new class and add enum items as public static member fields.

		delete _this.scopesStack[0].vars[ast.parent.value];

		var className = ast.parent.name;
		var classId = "__CLASS__" + className.toUpperCase() + "__";

		var scope = _this.NewScope(ast);
		_this.scopesStack.pop();

		scope.name			= className;
		scope.parentScope	= _this.scopesStack[0];
		scope.ast			= ast;
		scope.type			= jsdef.CLASS;
		scope.nodeType		= "CLASS";
		scope.isGlobal		= false;
		scope.isClass		= true;
		scope.isMethod		= false;
		scope.file			= ast.file;
		scope.path			= ast.path;
		scope.start			= ast.start;
		scope.end			= ast.end;
		scope.line_start	= ast.line_start;
		scope.line_end		= ast.line_end;
		scope.scopeId		= scope.scopeId;
		scope.vars			= {};
		scope.methods		= {};

		var classSymbol = new ClassSymbol();
		{
			classSymbol.symbolId	= (++_this.symbolId);
			classSymbol.name		= className;
			classSymbol.vartype		= className;
			classSymbol.classId		= classId;
			classSymbol.base		= null;
			classSymbol.baseSymbol	= null;
			classSymbol.type		= jsdef.CLASS;
			classSymbol.nodeType	= "CLASS";
			classSymbol.isPrototype = false;
			classSymbol.isEnum		= true;
			classSymbol.ast			= ast;
			classSymbol.scope		= scope;
			classSymbol.file		= ast.file;
			classSymbol.path		= ast.path;
			classSymbol.start		= ast.start;
			classSymbol.end			= ast.end;
			classSymbol.line_start	= ast.line_start;
			classSymbol.line_end	= ast.line_end;
			classSymbol.scopeId		= scope.scopeId;
			classSymbol.vars		= scope.vars;
			classSymbol.methods	 	= scope.methods;
		}
		ast.symbol = classSymbol;
		_this.classes[className] = classSymbol;

		for(var item in ast)
		{
			if(!isFinite(item)) continue;
			var varSymbol = new VarSymbol()
			{
				varSymbol.symbolId		= (++_this.symbolId);
				varSymbol.name			= ast[item][0].value;
				varSymbol.value			= ast[item][1].value;
				varSymbol.type			= jsdef.IDENTIFIER;
				varSymbol.nodeType		= "ENUM";
				varSymbol.classId		= classId;
				varSymbol.public		= true;
				varSymbol.private		= false;
				varSymbol.protected		= false;
				varSymbol.static		= true;
				varSymbol.optional		= false;
				varSymbol.constant		= true;
				varSymbol.ast			= ast[item];
				varSymbol.scope			= scope;
				varSymbol.baseSymbol	= null;
				varSymbol.file			= ast[item];
				varSymbol.start			= ast[item].start;
				varSymbol.end			= ast[item].end;
				varSymbol.line_start	= ast[item].line_start;
				varSymbol.line_end		= ast[item].line_end;
				varSymbol.scopeId		= scope.scopeId;
				varSymbol.vartype		= className;
				varSymbol.subtype		= ast[item].subtype ? ast[item].subtype : _this.getSubType(vartype);
				varSymbol.pointer		= false;
			}
			classSymbol.vars[varSymbol.name] = varSymbol;
		}

		return classSymbol;
	};

	// ==================================================================================================================================
	//	    ____             __        __                      __           ________
	//	   / __ \_________  / /_____  / /___  ______  ___     / /_____     / ____/ /___ ___________
	//	  / /_/ / ___/ __ \/ __/ __ \/ __/ / / / __ \/ _ \   / __/ __ \   / /   / / __ `/ ___/ ___/
	//	 / ____/ /  / /_/ / /_/ /_/ / /_/ /_/ / /_/ /  __/  / /_/ /_/ /  / /___/ / /_/ (__  |__  )
	//	/_/   /_/   \____/\__/\____/\__/\__, / .___/\___/   \__/\____/   \____/_/\__,_/____/____/
	//	                               /____/_/
	// ==================================================================================================================================

	_this.processPrototype = function(ast)
	{
		var _this = this;
		var className = ast[0][0][0].value;
		var classId = "__CLASS__" + className.toUpperCase() + "__";

		ast.isPrototype = true;

		// Upgrade prototype Function to Class.
		if(!_this.getClass(className))
		{
			var constructor = _this.scopesStack[0].methods[className];
			if(!constructor) return _this.NewError("Constructor function not found: " + className, ast);

			constructor.classId = classId;
			constructor.className = className;

			trace("Converting prototype symbol to class symbol: " + className);

			var scope = _this.NewScope(ast);
			_this.scopesStack.pop();

			scope.name			= className;
			scope.parentScope	= _this.scopesStack[0];
			scope.ast			= constructor;
			scope.type			= jsdef.CLASS;
			scope.nodeType		= "CLASS";
			scope.isGlobal		= false;
			scope.isClass		= true;
			scope.isMethod		= false;
			scope.file			= constructor.file;
			scope.path			= constructor.path;
			scope.start			= constructor.start;
			scope.end			= constructor.end;
			scope.line_start	= constructor.line_start;
			scope.line_end		= constructor.line_end;
			scope.scopeId		= scope.scopeId;
			scope.vars			= {};
			scope.methods		= {};

			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId	= (++_this.symbolId);
				classSymbol.name		= className;
				classSymbol.vartype		= className;
				classSymbol.classId		= classId;
				classSymbol.base		= null;
				classSymbol.baseSymbol	= null;
				classSymbol.type		= jsdef.CLASS;
				classSymbol.nodeType	= "CLASS";
				classSymbol.isPrototype = true;
				classSymbol.isEnum		= false;
				classSymbol.ast			= constructor;
				classSymbol.scope		= scope;
				classSymbol.file		= constructor.file;
				classSymbol.path		= constructor.path;
				classSymbol.start		= constructor.start;
				classSymbol.end			= constructor.end;
				classSymbol.line_start	= constructor.line_start;
				classSymbol.line_end	= constructor.line_end;
				classSymbol.scopeId		= scope.scopeId;
				classSymbol.vars		= scope.vars;
				classSymbol.methods	 	= scope.methods;
			}
			constructor.symbol = classSymbol;
			_this.classes[className] = classSymbol;
		}
		else
		{
			classSymbol = _this.getClass(className);
		}

		if(ast[1].type==jsdef.FUNCTION)
		{
			var methodName = ast[0][1].value;
			ast[1].name = methodName;
			ast[1].symbol.name = methodName;
			ast[1].symbol.scope.name = methodName;
			for(item in classSymbol.methods)
			{
				if(classSymbol.methods[item]===ast[1].symbol)
				{
					delete classSymbol.methods[item];
					classSymbol.methods[methodName] = ast[1].symbol;
					break;
				}
			}
		}
		else
		{
			var varSymbol = new VarSymbol();

			varSymbol.symbolId		= (++_this.symbolId);
			varSymbol.name			= ast[0][1].value;
			varSymbol.type			= ast[0][1].type;
			varSymbol.nodeType		= ast[0][1].nodeType;
			varSymbol.classId		= classId;
			varSymbol.public		= true;
			varSymbol.private		= false;
			varSymbol.protected		= false;
			varSymbol.static		= false;
			varSymbol.optional		= false;
			varSymbol.constant		= false;
			varSymbol.ast			= ast[0];
			varSymbol.scope			= classSymbol.scope;
			varSymbol.baseSymbol	= null;
			varSymbol.file			= ast[0].file;
			varSymbol.path			= ast[0].path;
			varSymbol.start			= ast[0].start;
			varSymbol.end			= ast[0].end;
			varSymbol.line_start	= ast[0].line_start;
			varSymbol.line_end		= ast[0].line_end;
			varSymbol.scopeId		= classSymbol.scopeId;
			varSymbol.vartype		= null;
			varSymbol.subtype		= null;
			varSymbol.pointer		= ast[0].isPointer;

			ast[0].symbol = varSymbol;
			classSymbol.vars[varSymbol.name] = varSymbol;

			switch(ast[1].type)
			{
				case jsdef.TRUE:
					varSymbol.vartype = "Boolean";
					varSymbol.value = true;
					break;

				case jsdef.FALSE:
					varSymbol.vartype = "Boolean";
					varSymbol.value = false;
					break;

				case jsdef.STRING:
					varSymbol.vartype = "String";
					varSymbol.value = ast[1].value;
					break;

				case jsdef.NUMBER:
					varSymbol.vartype = "Number";
					varSymbol.value = ast[1].value;
					break;

				case jsdef.NEW:
				case jsdef.NEW_WITH_ARGS:
					varSymbol.vartype = ast[1][0].value;
					break;

				case jsdef.ARRAY_INIT:
					varSymbol.vartype = "Array";
					break;
			}
		}
	};

	// ==================================================================================================================================
	//	  ______                    _____            __
	//	 /_  __/_  ______  ___     / ___/__  _______/ /____  ____ ___
	//	  / / / / / / __ \/ _ \    \__ \/ / / / ___/ __/ _ \/ __ `__ \
	//	 / / / /_/ / /_/ /  __/   ___/ / /_/ (__  ) /_/  __/ / / / / /
	//	/_/  \__, / .___/\___/   /____/\__, /____/\__/\___/_/ /_/ /_/
	//	    /____/_/                  /____/
	// ==================================================================================================================================

	_this.getVarType = function(vartype)
	{
		if(!vartype) return null;
		// Detect typed arrays Array<String>, Array<Float>, etc.
		if(vartype.charAt(vartype.length-1)!='>') return vartype;
		vartype = vartype.substr(0, vartype.indexOf('<'));
		return vartype;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// For typed arrays (eg. Array<Integer>, Array<String>, Array<MyClass> return subtype.
	_this.getSubType = function(vartype)
	{
		if(!vartype) return null;

		switch(vartype)
		{
		case "Array":
			return "Object";

		case "ArrayBuffer":
		case "ArrayBufferView":
		case "Float32Array":
		case "Int32Array":
		case "Uint8Array":
			return "Number";
		}

		if(vartype.charAt(vartype.length-1)!='>') return null;

		var subtype = vartype.substr(vartype.indexOf('<'));
		return subtype;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getTypeName = function(ast)
	{
		var _this = this;
		if(!_this.secondPass || !_this.currClassName) return;

		switch(ast.type)
		{
		//=============================================================================================================================
		case jsdef.ARRAY_INIT:		return "Array"
		case jsdef.BITWISE_NOT:		return "Number";
		case jsdef.DELETE:          return "Boolean";
		case jsdef.EQ:              return "Boolean";
		case jsdef.FALSE:           return "Boolean";
		case jsdef.GE:              return "Boolean";
		case jsdef.GT:              return "Boolean";
		case jsdef.IN:              return "Boolean";
		case jsdef.INSIDE:          return "Boolean";
		case jsdef.INSTANCEOF:      return "Boolean";
		case jsdef.LE:              return "Boolean";
		case jsdef.LT:              return "Boolean";
		case jsdef.NE:              return "Boolean";
		case jsdef.NOT:             return "Boolean";
		case jsdef.NULL:			return "Null";
		case jsdef.NUMBER:			return "Number";
		case jsdef.OBJECT_INIT:		return "Object";
		case jsdef.REGEXP:			return "RegExp";
		case jsdef.STRICT_EQ:       return "Boolean";
		case jsdef.STRICT_NE:       return "Boolean";
		case jsdef.STRING:			return "String";
		case jsdef.TRUE:			return "Boolean";
		case jsdef.TYPEOF:			return "String";
		case jsdef.GROUP: 			return _this.getTypeName(ast[0]);
		case jsdef.COMMA: 			return _this.getTypeName(ast[+ast.length-1]);
		case jsdef.VOID:			return _this.UNTYPED;
		case jsdef.THIS:			return _this.currClassName || "Function";

		//=============================================================================================================================
		case jsdef.PLUS:
		case jsdef.MINUS:
		case jsdef.MUL:
		case jsdef.DIV:
		case jsdef.MOD:
			var operation = "", op = "";
			if (ast.type == jsdef.PLUS) op = "PLUS";
			else if (ast.type == jsdef.MINUS) op = "MINUS";
			else if (ast.type == jsdef.MUL) op = "MUL";
			else if (ast.type == jsdef.DIV) op = "DIV";
			else if (ast.type == jsdef.MOD) op = "MOD";
			operation = this.typerules.implicit[op];
			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);
			if(operation[type1])
			{
				if(operation[type1].hasOwnProperty(type2))
					return operation[type1][type2];
				else
					return _this.typeCheck(ast, type1, type2);
			}
			return _this.typeCheck(ast, type1, type2, "Illegal operation "+op+" on: "+type1+" and "+type2);

		//=============================================================================================================================
		case jsdef.INCREMENT:
		case jsdef.DECREMENT:
		case jsdef.UNARY_PLUS:
		case jsdef.UNARY_MINUS:
			var type = _this.getTypeName(ast[0]);
			if (~this.typerules.explicit.__UNARY__.indexOf(type))
			{
				return "Number";
			}
			else
			{
				var op = "";
				if (ast.type == jsdef.INCREMENT)
					_this.NewError({type:TypeError, message:"Illegal operation INCREMENT on: "+type}, ast);
				else if (ast.type == jsdef.DECREMENT)
					_this.NewError({type:TypeError, message:"Illegal operation DECREMENT on: "+type}, ast);
				else _this.typeCheck(ast, type, "Number");
			}
			return type;

		//=============================================================================================================================
		case jsdef.BITWISE_AND:
		case jsdef.BITWISE_OR:
		case jsdef.BITWISE_XOR:
		case jsdef.LSH:
		case jsdef.RSH:
		case jsdef.URSH:
			var operation = "", op = "";
			if (ast.type == jsdef.BITWISE_AND) op = "&";
			else if (ast.type == jsdef.BITWISE_OR) op = "|";
			else if (ast.type == jsdef.BITWISE_XOR) op = "^";
			else if (ast.type == jsdef.LSH) op = "<<";
			else if (ast.type == jsdef.RSH) op = ">>";
			else if (ast.type == jsdef.URSH) op = ">>>";
			operation = this.typerules.implicit.BIT;
			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);
			return operation[type1] ?
				   (operation[type1].hasOwnProperty(type2) ? operation[type1][type2] : typeCheck(ast, type1, type2))
				   : _this.typeCheck(ast, type1, type2, "Illegal operation "+op+" on: "+type1+" and "+type2);

		//=============================================================================================================================
		case jsdef.AND:
		case jsdef.OR:
			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);
			return _this.typeCheck(ast, type1, type2);

		//=============================================================================================================================
		case jsdef.HOOK:
			var type1 = _this.getTypeName(ast[1]);
			var	type2 = _this.getTypeName(ast[2]);
			return _this.typeCheck(ast, type1, type2, "Type mismatch: "+type1+" and "+type2);

		//=============================================================================================================================
		case jsdef.IDENTIFIER:
			if(_this.getClass(ast.value)) return "Class";
			if(ast.symbol.type==jsdef.FUNCTION) return "Function";
			return ast.symbol.vartype;

		//=============================================================================================================================
		case jsdef.NEW:           	return ast[0].symbol.name;
		case jsdef.NEW_WITH_ARGS:	return ast[0].symbol.name;

		//=============================================================================================================================
		case jsdef.CALL:
			if(ast[0].type==jsdef.DOT)
			{
				var symbol = _this.LookupLastDotIdentifier(ast[0], _this.getCurrentScope());
				if(!symbol) { _this.NewError("Symbol not found: " + ast[0].identifier_last, nodeType, ast[0]); return null; }
				return symbol.vartype;
			}
			return ast[0].symbol.vartype;

		//=============================================================================================================================
		case jsdef.INDEX:
			if(ast[0].type==jsdef.DOT)
			{
				var symbol = _this.LookupLastDotIdentifier(ast[0], _this.getCurrentScope());
				if(!symbol) { _this.NewError("Symbol not found: " + ast[0].identifier_last, nodeType, ast[0]); return null; }
				return symbol.subtype;
			}
			return ast[0].symbol.subtype;
			break;

		//=============================================================================================================================
		case jsdef.DOT:
			var symbol = _this.LookupLastDotIdentifier(ast, _this.getCurrentScope());
			if(!symbol) { _this.NewError("Symbol not found: " + ast.identifier_last, nodeType, ast); return null; }
			return symbol.vartype;

		//=============================================================================================================================
		default:
			//debugger;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.checkFunctionCall = function(ast)
	{
		var fnSymbol = null;

		if(ast[0].type==jsdef.IDENTIFIER)
		{
			fnSymbol = ast[0].symbol;
		}
		else
		{
			fnSymbol = ast[0].identifier_last.symbol;
		}
		if(fnSymbol  && fnSymbol instanceof FunctionSymbol)
		{
			var i=0, item, arg, param, type1, type2;

			for(item in fnSymbol.arguments)
			{
				arg = fnSymbol.arguments[item];
				type1 = arg.vartype;

				if(i<ast[1].length)
				{
					type2 = _this.getTypeName(ast[1][i]);
					_this.typeCheck(ast, type1, type2, "Argument type mismatch: "+type1+" and "+type2);
				}
				else if(!arg.optional)
				{
					_this.NewError("Argument not optional: " + ast.source, ast);
				}
				i++;
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typeCheck = function(ast, type1, type2, customError)
	{
		//** Need to rewrite using convertion tables

		var _this = this;
		if(!_this.currClassName) return;
		if(type1==type2) return type1;
		type1=_this.getVarType(type1);
		type2=_this.getVarType(type2);
		if(type1==type2) return type1;

		if(!type1 || type1=="null")  { _this.NewError("Invalid left type", ast); return type1; }
		if(!type2 || type2=="null")  { _this.NewError("Invalid right type", ast); return type2; }

		if(__isPointer(type1) && type2=="Null") return type1;

		if(type1=="Object") return type1;
		if(type1=="Integer" && type2=="Number") return type1;
		if(type1=="Number" && type2=="Integer") return type1;
		if(type1=="Number" && type2=="Float") return type1;
		if(type1=="Integer" && type2=="Float") return type1;
		if(type1=="Float" && type2=="Number") return type1;
		if(type1=="Float" && type2=="Integer") return type1;
		if(type1=="Integer" && type2=="Float") { _this.NewWarning("Precision loss converting Float to Integer", ast); return type1; }
		if(type1=="String" && type2=="Null") { _this.NewWarning("String set to null, set to empty string instead", ast); return type1; }
		if(type1=="Integer" && type2=="Object") { _this.NewError("Invalid Object to Integer convertion", ast); return type1; }
		if(type1=="Float" && type2=="Object") { _this.NewError("Invalid Object to Float convertion", ast); return type1; }
		if(type1=="Number" && type2=="Object") { _this.NewError("Invalid Object to Number convertion", ast); return type1; }

		if(type1=="Boolean" && type2=="Number")
		{
			_this.NewError("Invalid Number to Boolean convertion", ast); return type1;
		}

		var cls1 = _this.getClass(type1);
		if(!cls1) { _this.NewError("Class not found: " + type1, ast); return type1; }

		var cls2 = _this.getClass(type2);
		if(!cls2) { _this.NewError("Class not found: " + type2, ast); return type1; }

		// Inheritance
		while(cls2)
		{
			if(cls1.name==cls2.name) return type1;
			cls2 = cls2.baseSymbol;
		}

		_this.NewError("Type mismatch: "+type1+" and "+type2, ast);
		return type1;
	};

	// ==================================================================================================================================
	//	    ______                      __     ________  ______   _____                 __          __
	//	   / ____/  ______  ____  _____/ /_   /  _/ __ \/ ____/  / ___/__  ______ ___  / /_  ____  / /____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/   / // / / / __/     \__ \/ / / / __ `__ \/ __ \/ __ \/ / ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   _/ // /_/ / /___    ___/ / /_/ / / / / / / /_/ / /_/ / (__  )
	//	/_____/_/|_/ .___/\____/_/   \__/  /___/_____/_____/   /____/\__, /_/ /_/ /_/_.___/\____/_/____/
	//	          /_/                                               /____/
	// ==================================================================================================================================

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Export identifier symbols that are used during debugging.
	_this.addDebugSymbol = function(ast, runtime)
	{
		if(!_this.secondPass || !_this.exportSymbols) return;
		var identifier = "";

		if(ast.type==jsdef.IDENTIFIER && !_this.isInside(ast,jsdef.DOT))
		{
			identifier = ast.value;
			_this.debugSymbolsTable.push("<DEBUG_SYMBOL file='" + ast.path + "' start='" + ast.start + "' end='" + ast.end + "' line='" + ast.line_start + "' identifier='" + identifier + "' runtime='" + runtime +"'/>\n");
		}
		else if(ast.type==jsdef.DOT && _this.currClassName && !_this.isInside(ast, jsdef.DOT)) // Process top-level DOTs only, skip inner DOTs.
		{
			var v_identifiers = [], v_runtime = [], buff = [];
			for(var i=0;i<ast.identifiers_list.length;i++)
			{
				var f = ast.identifiers_list[i].ast;
				var value = ast.identifiers_list[i].value.replace("@@THIS@@", "this");
				if(i==0)
				{
					v_identifiers.push(value);
					v_runtime.push(f.symbol.runtime);
				}
				else if(f.type==jsdef.INDEX)
				{
					v_identifiers[v_identifiers.length-1] += f.generated_index;
					v_runtime[v_runtime.length-1] += f.generated_index;
				}
				else
				{
					v_identifiers.push(value);
					v_runtime.push(value);
				}
				buff.push("<DEBUG_SYMBOL file='" + ast.path + "' start='" + f.start + "' end='" + f.end + "' line='" + f.line_start + "' identifier='" + v_identifiers.join(".") + "' runtime='" + v_runtime.join(".") +"'/>\n");
			}
			// Reverse debug symbols for faster search and append them to debug symbols table.
			_this.debugSymbolsTable = _this.debugSymbolsTable.concat(buff.reverse());
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Export class, function and identifier symbols that are used during code editing by intelliSence.
	_this.exportCoconutIDESymbols = function()
	{
		if(!_this.exportSymbols) return;

		var xml, cls, item, arg, args, argsList, xmlArgsList, hasArgs, scope, icon, sig, mbrList, mbrLists, scopeVars,
			classSymbol, methodSymbol, argumentSymbol, varSymbol, externs, modifier, codeSymbols, varsxml,
			debugSymbols = "<DEBUG_SYMBOLS>" + _this.debugSymbolsTable.join("") + "</DEBUG_SYMBOLS>";

		// ======================================================================================
		// Export Code Symbols, CodeMax MemberLists and Externs (all in one loop to save time)
		// ======================================================================================

		externs = ["// Auto-generated Project Externs (used by IDE intelliSence)\n\n"];
		mbrLists = [];
		xml = [];
		xml.push("<CODE_SYMBOLS" + (_this.selectedClass ? " update='" + _this.selectedClass + "'" : "") + ">\n");

		for(cls in _this.classes)
		{
			if(_this.selectedClass && _this.selectedClass!=cls) continue;

			classSymbol = _this.classes[cls];
			externs.push("class "+ classSymbol.name + (classSymbol.base ? " : " + classSymbol.base : "") + "\n{\n");

			mbrList = [];
			mbrList.push("<memberlist name='Class " + classSymbol.name + "'>");
			xml.push(_this.objectToXML(classSymbol, classSymbol.name, false));
			{
				xml.push("<METHODS>\n");
				for(item in classSymbol.methods)
				{
					methodSymbol = classSymbol.methods[item];
					if(methodSymbol.name)
					{
						args = [];
						argsList = [];
						xmlArgsList = [];
						for(arg in methodSymbol.arguments)
						{
							argumentSymbol = methodSymbol.arguments[arg];
							args.push(_this.objectToXML(argumentSymbol, arg, true));
							argsList.push(argumentSymbol.name + (argumentSymbol.vartype ? ":" + argumentSymbol.vartype : ""));
							xmlArgsList.push(argumentSymbol.name + argumentSymbol.ast.xmlvartype);
						}
						hasArgs = (args.length>0);
						xml.push(_this.objectToXML(methodSymbol, methodSymbol.name, !hasArgs));
						if(hasArgs)
						{
							xml.push("<ARGUMENTS>\n");
							xml.push(args.join(""));
							xml.push("</ARGUMENTS>\n");
							xml.push("</" + methodSymbol.name +">\n");
						}
						sig = methodSymbol.name + "(" + xmlArgsList.join(", ") + ")" + methodSymbol.ast.xmlvartype;
						modifier = "public";
						icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FUNCTION;
						if(methodSymbol.private) { icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FUNCTION; modifier = "private"; }
						if(methodSymbol.protected) { icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FUNCTION; modifier = "protected"; }
						if(methodSymbol.name=="Constructor") icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTRUCTOR;
						mbrList.push('\t<member name="' + methodSymbol.name + '" proto="' + sig + '" help="' +  classSymbol.name + " :: " + sig + '" image="' + icon + '"/>');

						sig = methodSymbol.name + "(" + argsList.join(", ") + ")" + (methodSymbol.vartype ? " :" + methodSymbol.vartype : "");
						externs.push("\t" + modifier + " function "+ sig + " {}\n");
					}
				}
				xml.push("</METHODS>\n");

				xml.push("<VARS>\n");
				for(item in classSymbol.vars)
				{
					varSymbol = classSymbol.vars[item];
					xml.push(_this.objectToXML(varSymbol, item, true));
					icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;
					modifier = "public";
					if(varSymbol.private) { icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FIELD; modifier = "private"; }
					if(varSymbol.protected) { icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FIELD; modifier = "protected"; }
					if(varSymbol.constant) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTANT;
					sig = varSymbol.name + varSymbol.ast.xmlvartype;
					mbrList.push('\t<member name="' + varSymbol.name + '" proto="' + sig + '" help="' + classSymbol.name + " :: " + sig + '" image="' + icon + '"/>');
					externs.push("\t" + modifier + " var " + varSymbol.name + (varSymbol.vartype ? " :"+ varSymbol.vartype : "") + ";\n");

				}
				xml.push("</VARS>\n");
			}
			xml.push("</" + classSymbol.name + ">\n");
			mbrList.push("</memberlist>");
			mbrLists.push(mbrList.join("\n"));
			externs.push("} //" + classSymbol.name + "\n\n");
		}
		xml.push("</CODE_SYMBOLS>\n");
		codeSymbols = xml.join("");
		externs = externs.join("");
		mbrLists = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<MEMBER_LISTS" + (_this.selectedClass ? " update='" + _this.selectedClass + "'" : "") +">\n" + mbrLists.join("\n") + "</MEMBER_LISTS>";

		// ======================================================================================
		// Export Scopes and Scope Vars
		// ======================================================================================
		xml = [];
		xml.push("<SCOPES" + (_this.selectedClass ? " update='" + _this.selectedClass + "'" : "") + ">\n");
		for(scope in _this.scopesTable)
		{
			scope = _this.scopesTable[scope];

			if(!scope.path) continue;
			if(_this.selectedClass && _this.selectedClass!=scope.className) continue;

			varsxml = [];
			for(item in scope.vars)
			{
				varSymbol = scope.vars[item];
				if(varSymbol.vartype)
				{
					icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;
					if(varSymbol.private) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FIELD;
					if(varSymbol.protected) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FIELD;
					if(varSymbol.constant) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTANT;
					varsxml.push("\t<SYMBOL symbolId='"+varSymbol.symbolId + "' name='" + varSymbol.name + "' type='" + varSymbol.type + "' vartype='" + varSymbol.vartype.replace('<','&lt;').replace('>','&gt;') + "' subtype='" + varSymbol.subtype + "'/>\n");
				}
			}

			for(item in scope.methods)
			{
				methodSymbol = scope.methods[item];
				icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;
				if(methodSymbol.private) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FIELD;
				if(methodSymbol.protected) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FIELD;
				if(methodSymbol.constant) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTANT;
				varsxml.push("\t<SYMBOL symbolId='"+methodSymbol.symbolId + "' name='" + methodSymbol.name + "' type='" + methodSymbol.type + "' vartype='" + (!methodSymbol.vartype ? "" : methodSymbol.vartype.replace('<','&lt;').replace('>','&gt;')) + "' subtype='" + methodSymbol.subtype + "'/>\n");
			}
			xml.push(_this.objectToXML(scope, "SCOPE", varsxml.length==0, (!scope.parentScope ? "" : "parent='"+scope.parentScope.scopeId+"'")));
			if(varsxml.length)
			{
				xml.push(varsxml.join(""));
				xml.push("</SCOPE>\n");
			}
		}
		xml.push("</SCOPES>\n");
		scopeVars = xml.join("");

		// ======================================================================================
		// Export to IDE
		// ======================================================================================

		if(!_this.selectedClass)
			jsppCallback("resetSymbols");

		jsppCallback("setCodeSymbols", "", "", 0, 0, codeSymbols);
		jsppCallback("setScopes", "", "", 0, 0, scopeVars);
		jsppCallback("setMemberLists", "", "", 0, 0, mbrLists);

 		if(!_this.selectedClass)
		{
			jsppCallback("setExterns", "", "", 0, 0, externs);
			jsppCallback("setDebugSymbols", "", "", 0, 0, debugSymbols);
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.objectToXML = function(obj, tag, close, more)
	{
		var v, xml = [];
		xml.push("<"+tag);
		for(var item in obj)
		{
			if(typeof obj[item]=="object") continue;
			v = obj[item];
			if(v==null || v==undefined || v==NaN) continue;
			if(typeof v == "string" && v.charAt(v.length-1)=='>')
			{
				v = v.replace("<", "&lt;");
				v = v.replace(">", "&gt;");
			}
			xml.push(item + "='" + v + "'");
		}
		if(more) xml.push(more);
		xml.push(close ? "/>\n" : ">\n");
		return xml.join(" ");
	};
}








