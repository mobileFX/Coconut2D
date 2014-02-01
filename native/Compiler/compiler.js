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
 *********************************************************************************
 *
 * IMPORTANT CREDIT:
 *
 * This compiler is based on Roger Poon's JavaScript++ (http://www.jspplang.org/)
 * work but it has been rather simplified in order to make it easier to integrate
 * with Coconut2D IDE, and to allow JavaScript++ to C++ code generation in order
 * to produce native code for iOS and Android devices.
 *
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
	DISCLAIMER:

	I had many problems integrating properly the original JavaScript++ implementation with the IDE and during the process I produced
	or found bugs that I could not overcome, so I decided to get deeper into Roger's code, understand the principles of his compiler
	and the Narcissus parser in depth, and re-write most of the compiler from scratch. The end result works but it is intermediate;
	My goal is to fall back to JavaScript++ original implementation and I have schedulled a meeting with Roger on Feb 2014.

	Some important architectural differencies are:

	== 11/12/2013 ==

	1. I pre-process the AST nodes mostly to assign a ".parent" which makes it easier to debug the compiler, among other node caching.
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

   == 05/01/2014 ==

   15. Added Finite State Machine (FSM) semantics for making game development easier. A class has "state" modifier and inside it there
   	   can be defined public/private/protected states with enter(), exit(), tick() and paint() methods. A state is a block container of
   	   other isolated variables and functions too and has access to class scope.
   16. Added virtual and abstract modifiers.
   18. Expanded "Destructors" that are required if a class has object members (which are automatically set to null by compiler).
   19. Implemented smart "delete" statement, if an object is detected it calls its destructor and for typed arrays (of objects) the
   	   array items are being destructed one by one.
   20. Added "#include" and other compiler directives (mostly required by the IDE)

   == 01/02/2014 ==

   21. Added Enums in classes
   22. Added function overloading at compile time. Overloaded functions are named <function_name>$<index> and the compiler determines which overload to use.
   23. Added static functions (not proper implementation yet but works)
   24. Added properties.
   25. Implemented PRIVATE the same way as PROTECTED
   26. Completely re-wrote jsdef.IDENTIFIER generator (MAJOR REWRITE!)
   27. Re-engineered jsdef.CLASS generator
   28. Added C++ generator (detects pointers!!) for seamlessly compiling JavaScript++ to native C++ for iOS and Android.



	Elias G. Politakis
	epolitakis@mobilefx.com

   TODO LIST:
   ==========

   - Bug in V8 prevents breakpoints if block statements starts with jsdef.NEW/NEW_WITH_ARGS assignment (jsflags --inline-new=false)
   - Proper support for ENUMS
   - Add interfaces
   - Add events
   - IMPORTANT: Need to detect jsdef.NEW and jsdef.NEW_WITH_ARGS inside method calls that produce memory leaks in
   				C++ and issue warnings. Possible define a weak_new operator and pass delete obligation to consumer?

*/

function Compiler(ast, infolder, outfolder, compilerFolder, exportSymbols, selectedClass)
{
	// ast				: The abstract syntax tree root node as produced by the parser
	// infoder			: The root input folder containing the source files
	// outfolder		: The root output folder where generated files will be placed
	// selectedClass	: Used if we want to parse-only a single class for intelliSence use

	var _this = this;

	_this.symbolId = -1;					// Symbols Counter
	_this.scopeId = -1;                     // Scopes Counter (resets per file)
	_this.currFile = null;                  // Current File being processed
	_this.secondPass = false;               // Flag that indicates compiler's second pass
	_this.ast = ast;                        // The Abstract Syntax Tree root node (jsdef.SCRIPT)
    _this.infolder = infolder;              // The root input source code folder (eg. D:/Project/src)
    _this.outfolder = outfolder;            // The root output folder for generated files (eg. D:/Project/bin)
    _this.compilerFolder = compilerFolder;	// The root output folder for symbols
	_this.tokenizer = null;                 // Reference to tokenizer (reserved for future use)
	_this.fileClasses = {};                 // Map of classes per file (usage: _this.fileClasses[file][class] = ast; )
	_this.includes = [];                    // List of include files for current file being processed (resets per file)
	_this.no_errors = 0;                    // Semaphore that controls errors generation (used by ""#ignore_errors" directive)
	_this.scopesStack = [];                 // Stack of Scopes (scopes are pushed and popped from it during generation)
	_this.scopesTable = [];                 // Table of Scopes (scopes are only pushed)
	_this.debugSymbolsTable = [];           // Map of source code to runtime debug symbols, used by IDE debugger (eg. class foo { public var x; } , x at runtime is __CLASS_FOO__.x )
	_this.currClassName = null;             // The current class being processed (also indicates whether a JS++ class is being processed or just plain JavaScript code)
	_this.classes = {};                     // Map of class symbols
	_this.line_start = -1;                  // Souce Line counter: source code lines "//@line xxx" are emitted in generated code for IDE debugger
	_this.UNTYPED = "Untyped";              // Untyped identifier vartype, used in Type Check System
	_this.exportSymbols = exportSymbols;    // Flag that indicates whether symbols should be exported or not
	_this.selectedClass = selectedClass;    // If set it indicates that we only need to process a single class (used by IDE intelliSence for parsing classes as you type them)
	_this.in_state = false;    				// Flag that indicates we are processing a state
	_this.in_property = false;    			// Flag that indicates we are processing a property
	_this.states = {};						// Map of states

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Symbol constructors
	function Scope() 			{}
	function ClassSymbol() 		{}
	function FunctionSymbol() 	{}
	function PropSymbol() 		{}
	function VarSymbol()		{}
	function StateSymbol() 		{}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewWarning = function (e, ast)
	{
		if(!ast.__warnings) ast.__warnings = {};
		if(!ast.__warnings[e]) ast.__warnings[e] = 0;
		ast.__warnings[e]++;
		if(ast.__warnings[e]>1) return;
		if(_this.selectedClass || _this.no_errors>0) return;
		trace("@@ WARNING: " + e + " in file " + ast.path + " at line " + ast.line_start);
		jsppCallback("warning", ast.path, "", ast.line_start, 0, e);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewError = function (e, ast)
	{
		if(!ast.__errors) ast.__errors = {};
		if(!ast.__errors[e]) ast.__errors[e] = 0;
		ast.__errors[e]++;
		if(ast.__errors[e]>1) return;
		if(_this.selectedClass || _this.no_errors>0) return;
		trace("@@ ERROR: " + e + " in file " + ast.path + " at line " + ast.line_start);
		jsppCallback("error", ast.path, "", ast.line_start, 0, e);
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
			_this.scopesStack = [];
			_this.scopesTable = [];
			_this.debugSymbolsTable = [];
			_this.currClassName = null;
			_this.line_start = -1;
			_this.states = {};

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
		var currFunction = null;
		var currClass = null;
		var currDot = [];

	    // Descent the ast.
		function descend(node)
		{
			node.__visited=true;

			switch(node.type)
			{
			case jsdef.CLASS:
				if(!_this.fileClasses[node.file]) _this.fileClasses[node.file]={};
				_this.fileClasses[node.file][node.name] = node;
				currClass = node;
				break;

			case jsdef.FUNCTION:
				currFunction = node;
				node.returnPaths = [];
    			break;

    		case jsdef.PROPERTY:
				currFunction = node;
				node.returnPaths = [];
    			break;

    		case jsdef.RETURN:
    			if(currFunction)
    				currFunction.returnPaths.push(node);
    			break;

    		case jsdef.INDEX:
			case jsdef.GROUP:
			case jsdef.CALL:
				currDot.push(node);
				break;

			case jsdef.DOT:
				// Pre-process DOT for speed.
				currDot.push(node);
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
				break;
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
					case "returnPaths":
					case "inClass":
					case "inFunction":
					case "inDot":
					case "source":
					case "nodeType":
						break;

					default:

						if(typeof node[item] == 'object'  && node[item] && !node[item].__visited)
						{
							descend(node[item]);
							node[item].parent = node;
							nodes.push(node[item]);
						}
				}
			}
			nodes = null;

            // Enrich ast node with usefull data and delete its reference to tokenizer.
			node.nodeType = GLOBAL.narcissus.jsdefNames[node.type];
			node.inClass = currClass;
			node.inFunction = currFunction;
			node.inDot = currDot.length>0 && currDot[currDot.length-1].type==jsdef.DOT ? currDot[currDot.length-1] : null;
			node.inIndex = currDot.length>0 && currDot[currDot.length-1].type==jsdef.INDEX ? currDot[currDot.length-1] : null;
			node.inGroup = currDot.length>0 && currDot[currDot.length-1].type==jsdef.GROUP ? currDot[currDot.length-1] : null;
			node.inCall = currDot.length>0 && currDot[currDot.length-1].type==jsdef.CALL ? currDot[currDot.length-1] : null;
			var o_start = (node.__filePosOffset - (node.line_start - node.__fileLineOffset)+1);
			var o_end = (node.__filePosOffset - (node.line_end - node.__fileLineOffset)+1);
			node.source = _this.tokenizer.source.slice(node.start, node.end);
			node.s = node.start;
			node.e = node.end;
			node.start -= o_start;
			node.end -= o_end;
			node.line_start -= node.__fileLineOffset;
			node.line_end -= node.__fileLineOffset;
			node.tokenizer = null;

			delete node.tokenizer;

			switch(node.type)
			{
    		case jsdef.INDEX:
			case jsdef.GROUP:
			case jsdef.CALL:
			case jsdef.DOT:
				currDot.pop();
				break;

			case jsdef.CLASS:
				currClass=null;
				break;

			case jsdef.FUNCTION:
				currFunction=null;
				break;
			}
		}

		descend(ast);
		return ast;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Reduces a DOT to a list of identifiers
	//
	// eg. from this:	"this.__children[__this.currentChild.index+getNextChild()-2].keyframe(sprite.getNextFame()).frameIndex"
	//     to this:		"@@THIS@@.__children.@@INDEX@@.keyframe.frameIndex"
	//
	_this.reduceProps = function(ast)
	{
		var _this = this;
		var out = [];

		switch (ast[0].type)
		{
			case jsdef.NEW:
			case jsdef.NEW_WITH_ARGS:
				out.push({ast:ast[0], value:ast[0][0].value});
				break;

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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Every time we enter a closure (class, script, block, switch, loop, etc) we create a new scope.
    // A scope is linked to its ast so that at second pass we do not regenerate them.
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
			scope.isState		= ast.type==jsdef.STATE;
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

        // Push scope to scope stack and scope table.
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

	// The purpose of the following functions is to link an IDENTIFIER with its defining SYMBOL,
	// or in other words to "recognize" an identifier's type. If a program is written correctly
	// all identifiers should be recognized.

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
			var searchScope = (!ast || (!ast.inDot || (ast.inDot && ast.inDot.identifiers_list[0].value==identifier)));

			// Lookup scope chain (classes, base clasees, methods, base class methods, variables, etc.)
			if(searchScope)
				symbol = _this.LookupScopeChain(identifier, scope, true);

			// Lookup DOT chain.
			if(!symbol && _this.secondPass && ast && ast.inDot)
				symbol = _this.LookupLastDotIdentifier(ast.inDot, scope);

			return symbol;
		}

		var symbol = null;
		switch(identifier)
		{
			case "prototype":		symbol = _this.getClass("Prototype"); break;
			case "@@THIS@@": 		symbol = _this.getCurrentClass(); break;
			case "@@SUPER@@":		symbol = _this.getCurrentClass().baseSymbol; break;

			default:
				symbol = _this.getClass(identifier) || __doLookupSymbol(scope, identifier, ast);
				break;
		}

		if(!noWarning && _this.secondPass && !symbol)
		{
			if(ast.file.substr(ast.file.length-3)==".js" || _this.isInside(ast, null, "isPrototype", true))
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
			else if(ast.identifiers_list[i+1].value=="@@INDEX@@")
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
		if(symbol)
			return symbol;

		// Identifier not found in current scope, move to parent scope.
		if(deep && scope.parentScope)
			return  _this.LookupScopeChain(identifier, scope.parentScope, deep);
	};

	// ==================================================================================================================================
	//	    __  ___
	//	   /  |/  /___ _______________  _____
	//	  / /|_/ / __ `/ ___/ ___/ __ \/ ___/
	//	 / /  / / /_/ / /__/ /  / /_/ (__  )
	//	/_/  /_/\__,_/\___/_/   \____/____/
	//
	// ==================================================================================================================================

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
		return _this.currClassName && _this.currClassName!="Global" ? _this.classes[_this.currClassName].scope : null;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isInside = function(ast, jsdefType, propName, propValue, stop_jsdefType)
	{
		if(!ast) return false;
		for(var p=ast.parent;p!=null;p=p.parent)
		{
			if(p.type==stop_jsdefType)
				return false;

			if(p.type==jsdefType)
			{
				if(propName && propValue)
				{
					if(p[propName]==propValue)
						return p;
				}
				else
				{
					return p;
				}
			}
			else if(propName && propValue)
			{
				if(p[propName]==propValue)
					return p;
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
	//  Where magic happens!
	//
	// ==================================================================================================================================
	// ==================================================================================================================================
	// ==================================================================================================================================
	// ==================================================================================================================================

    // Recursively descend into the AST and generate plain JavaScript code!

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

		case jsdef.CLASS:

		 	_this.currClassName = ast.name;

		 	// Class must know its includes
		 	ast.includes = _this.includes;
		 	ast.fileClasses = _this.fileClasses;

			var constructor = null;
			var destructor = null;
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";
			var baseClass = ast.extends ? ast.extends : undefined;
			var baseClassSymbol = _this.getClass(baseClass);
			var baseClassId = baseClassSymbol ? baseClassSymbol.ast.symbol.classId : null;
			var baseConstructor = baseClassSymbol ? baseClassSymbol.methods["Constructor"] : null;
			var isGlobalClass = (ast.name=="Global");
			var scope = (isGlobalClass ? _this.scopesStack[0] : _this.NewScope(ast));

			if(baseClass && baseClass==ast.name)
			{
				_this.NewError("Illegal base class: " + baseClass, ast);
				return;
			}

			// Class Symbol
			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId	= (++_this.symbolId);
				classSymbol.name		= ast.name;
				classSymbol.vartype		= ast.name;
				classSymbol.subtype		= ast.subtype;
				classSymbol.classId		= classId;
				classSymbol.base		= baseClass;
				classSymbol.baseSymbol	= baseClassSymbol;
				classSymbol.type		= ast.type;
				classSymbol.nodeType	= ast.nodeType;
				classSymbol.isPrototype = false;
				classSymbol.isEnum		= false;
				classSymbol.isState		= ast.state;
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
				classSymbol.runtime		= ast.name;
			}

			// Save symbol
			ast.symbol = classSymbol;
			_this.classes[ast.name] = classSymbol;
			_this.scopesStack[0].vars[classSymbol.name] = classSymbol;

			// Record vartype usage in class level (used to check #includes)
			if(baseClass) scope.vartypes[baseClass] = true;

			/*//////////////////////////////////////////////////////////////////////////////////////////////

			Defining a class and inheritance in plain JavaScript:
			=====================================================

			The basic idea (as derived from Roger Poon's JavaScript++) is to have an outer JavaScript function
			returning an inner function that represents the Class.	When calling the outer function with the
			"new" operator the result is an instnace of the inner function.	To implement inheritance we use the
			good old prototypes, as demonstrated below. Our compiler's work is to construct the inner and outer
			functions based on the AST class definition and to properly apply inheritance.

			function Class1()
			{
				function Class1(base)
				{
					this.x = 1;
					return this;
				}
				var base = new Class2;
				Class1.prototype = base;
				return new Class1(base);
			}

			function Class2()
			{
				function Class2(base)
				{
					this.y = 2;
					return this;
				}
				var base = new Class3;
				Class2.prototype = base;
				return new Class2(base);
			}

			function Class3()
			{
				function Class3(base)
				{
					this.z = 3;
					return this;
				}
				return new Class3(null);
			}

			var o1 = new Class1;
			console.log(o1.x + ", " + o1.y + ", " + o1.z);
			o1.x=100; o1.y=200; o1.z=300;
			console.log(o1.x + ", " + o1.y + ", " + o1.z);

			var o2 = new Class1;
			console.log(o2.x + ", " + o2.y + ", " + o2.z);
			console.log(o1.x + ", " + o1.y + ", " + o1.z);

			var o3 = new Class2;
			console.log(o3.x + ", " + o3.y + ", " + o3.z);


			The original CocoScript was based on Roger's JavaScript++ implementation but class
			initialization was too cryptic for me to undestand and debug. Also, when a class was
			inheriting from another class, the base class was appearing in global scope and I could
			not find out why. Even though it is highly likely that I produced most of the bugs while
			tampering with Roger's work, more and more bugs that kept appearing and a very severe
			instantiation issue with CocoAudio cloning, lead me to assume that anonymous function
			were not creating instances properly and I decided to re-write class generation.
			Also with anonymous functions I had problems getting a "typeof" class name at runtime
			and viewing object type in V8 debugger.

			//////////////////////////////////////////////////////////////////////////////////////////////*/

			// Get constructor arguments list
			var constructorArguments = [];
			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				var member = ast.body[item];
				if(member.type==jsdef.FUNCTION && member.name=="Constructor" && member.params.length)
				{
					for(i=0;i<member.params.length;i++)
						constructorArguments.push(classId + "$" + member.params[i] + "__");
					break;
				}
			}
			constructorArguments = constructorArguments.join(", ");

			// Generate the outer function
			out.push("function " + ast.name + "(" + constructorArguments + "){");
			out.push("var __BASE__ = null;");

			// Generate the inner function
			out.push("function " + ast.name + "(__BASE__" + (constructorArguments ? ", " + constructorArguments : "") + "){");

			// Generate self (this)
			out.push("var " + classId + " = this;");

			// Generate protected and private member banks
			out.push("__PDEFINE__=Object.defineProperty,");
			out.push("__NOENUM__={enumerable:false};");
            out.push("this.__PRIVATE__={}; this.__PROTECTED__={};");
			out.push("__PDEFINE__(this,'__PROTECTED__',__NOENUM__);");
			out.push("__PDEFINE__(this,'__PRIVATE__',__NOENUM__);");

			// Inherit public and protected members
			if(baseClass)
			{
				if(_this.secondPass && baseClass && !_this.getClass(baseClass))
					_this.NewError("Base class not found: " + baseClass, ast);

				out.push("var __SUPER__ = this.__SUPER__ = __BASE__;");

				/*
				//Public members
				out.push("var __TMP_ARRAY__=[];");
				out.push("for(var __MEMBER__ in __SUPER__){");
				out.push("__TMP_ARRAY__.push(__MEMBER__ + ' = __SUPER__.' + __MEMBER__);}");
				out.push("__TMP_ARRAY__.length && eval('var '+__TMP_ARRAY__.join(',')+';');");

				//Protected members
				out.push("__TMP_ARRAY__=[];");
				out.push("for(var __MEMBER__ in __SUPER__.__PROTECTED__){");
				//out.push("__TMP_ARRAY__.push(__MEMBER__ + ' = __SUPER__.' + __MEMBER__);}"); // Not sure why..
				out.push("__TMP_ARRAY__.push('this.__PROTECTED__.' + __MEMBER__ + ' = __SUPER__.__PROTECTED__.' + __MEMBER__);}");
				out.push("__TMP_ARRAY__.length && eval('var '+__TMP_ARRAY__.join(',')+';');");
				*/
			}

			// Generate Class Methods
			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				var member = ast.body[item];
				switch(member.type)
				{
					case jsdef.FUNCTION:
					case jsdef.PROPERTY:
						if(member.name=="Constructor")
						{
							member.isConstructor=true;
							constructor = member;
							continue;
						}
						if(member.name=="Destructor")
						{
							member.isDestructor=true;
							destructor = member;
							continue;
						}
						out.push(generate(member));
						break;
				}
			}

			// Generate Class Fields
			for(var item in ast.body)
			{
				if(!isFinite(item)) break;
				var member = ast.body[item];
				switch(member.type)
				{
					case jsdef.STATE:
					case jsdef.CONST:
					case jsdef.VAR:
					case jsdef.ENUM:
						out.push(generate(member));
						break;
				}
			}

			// Generate Destructor
			// (the idea is to call the destructor of any object class member variables and set them to null)
			out.push("var Destructor = this.Destructor = function(){");
			if(destructor) out.push(generate(destructor.body));

			if(_this.secondPass)
			{
				out.push("{");
				for(item in classSymbol.vars)
					out.push(classSymbol.vars[item].runtime+"=null;");
				if(baseClass)
					out.push("__SUPER__ && ((__SUPER__.hasOwnProperty('Destructor') && __SUPER__.Destructor()) || !__SUPER__.hasOwnProperty('Destructor')) && (delete __SUPER__);");
				out.push("}");
			}
			out.push("return true};");

			// Generate Constructor and call it
			out.push(constructor ? generate(constructor) : "this.Constructor=function(){};");
			out.push("__PDEFINE__(this,'Constructor',__NOENUM__);");
			out.push("this.Constructor(" + constructorArguments + ");");

            // Close inner function
			out.push("return this;}");

			// Close outer function
			if(baseClass)
			{
				out.push("__BASE__ = new " + baseClass + "(" + constructorArguments + ");");
				out.push(ast.name + ".prototype = __BASE__;");
			}
			out.push("return new " + ast.name + "(__BASE__" + (constructorArguments ? ", " + constructorArguments : "") + ");}");

			// Type Checks
			if(_this.secondPass)
			{
				// Check that abstract methods are implemented
				if(baseClass && baseClassSymbol)
				{
					// Check base class constructor arguments
					if(constructor && baseConstructor && baseConstructor.paramsList.length > constructor.paramsList.length)
						_this.NewError("Constructor arguments missmatch: " + ast.name, ast);

					for(item in baseClassSymbol.methods)
					{
						var baseMethodSymbol = baseClassSymbol.methods[item];
						if(baseMethodSymbol.abstract && !classSymbol.methods.hasOwnProperty(baseMethodSymbol.name))
							_this.NewError("Missing abstract method: " + baseMethodSymbol.name, ast);
					}
				}

				// If this class has object members we need a Destructor
				var hasObjectMembers = false;
				for(item in classSymbol.vars)
				{
					if(classSymbol.vars[item].pointer)
					{
						hasObjectMembers = true;
						break;
					}
				}
				if(hasObjectMembers && !destructor)
					_this.NewError("Missing Destructor: " + ast.name, ast);
			}

            // Done!
			_this.currClassName = null;

			if(!isGlobalClass)
				_this.ExitScope();

			/////////////////////////////////////////////////////
			// Ask IDE to save compiled JavaScript object code.
			/////////////////////////////////////////////////////
			if(!_this.selectedClass && _this.secondPass && ast.path && ast.file!="externs.jspp" && _this.infolder && _this.outfolder)
			{
				var file = ast.path;
				file = file.replace(_this.infolder, _this.outfolder).replace(".jspp", ".jobj");
				buff = out.join("\n");
				var buff = do_js_beautify(out.join("\n"), 1, false, false, true);
				buff = RxReplace(buff, "//@line \\d+[\\s\\t\\n\\r]+//@line (\\d+)", "mg", "//@line $1"); 	// Empty Lines
				buff = RxReplace(buff, "(__PDEFINE__|__PROTECTED__|__PRIVATE__) \=[\\s\\t\\n\\r]+\{[\\s\\t\\n\\r]+\}", "mg", "$1 = {}");
				buff = RxReplace(buff, "__NOENUM__ \=[\\s\\t\\n\\r]+\{[^}]+\}", "mg", "__NOENUM__ = {enumerable:false}");
				buff = RxReplace(buff, ";[\\s\\t\\n\\r]*function F\\(\\)[\\s\\t\\n\\r]*\{[\\s\\t\\n\\r]*\}", "mg", "; function F(){}");
				buff = RxReplace(buff, "\\([\\s\\t\\n\\r]+", "mg", "(");
				buff = RxReplace(buff, "\\{[\\s\\t\\n\\r]*\\}", "mg", "{}");
				buff = RxReplace(buff, "(^[\\s\\t\\n\\r]*$)+", "mg", "");
				jsppCallback("module", ast.path, file, 0, 0, buff);
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
			var parentScope = methodScope.parentScope;	// Could be State, Property or Class scope
			var classScope = _this.getClassScope();		// Class scope
			var classSymbol	=  classScope ? classScope.ast.symbol : null;
			var className = classScope ? classScope.ast.name : null;
			var classId = classScope ? classScope.ast.symbol.classId : null;
			var isGlobal = !classScope && parentScope.isGlobal;
			var isAnonymous = (ast.name==null || ast.name.length==0);
			var fnName = (ast.name ? ast.name : "");
			var baseMethodSymbol = null;

			if(_this.currClassName) _this.debugSymbolsTable.push("<!-- " + className + " :: " + fnName + " -->\n");

            // Check for function overloading
			if(!isAnonymous && Object.prototype.hasOwnProperty.call(parentScope.methods, fnName))
			{
				var fn_ast = parentScope.methods[fnName].ast;
				if(!_this.secondPass)
				{
					// The function is overloaded! First we need to change the compiled function
					// name using the pattern <function_name>$<index> where index is the overload
					// index of the function in the ast.overloads[] list. We keep a list of all
					// overloaded functions in the first AST node we find during the first pass.
					// During generation the functions are generated as foo, foo$1, foo$2, etc.
					// and the compiler during identifier recognition decides which overload
					// function to bind.

					if(!fn_ast.overloads) fn_ast.overloads = [];
					fn_ast.overloads.push(ast);
					ast.overloadOf = fn_ast;
					fnName += "$" + fn_ast.overloads.length;
				}
				else if(fn_ast.overloads)
				{
					fnName = ast.symbol.name;
				}
			}

			// Link method symbol with base class method symbol for speed.
			if(parentScope.isClass && parentScope.ast.symbol.baseSymbol)
				baseMethodSymbol = _this.LookupIdentifier(parentScope.ast.symbol.baseSymbol.scope, fnName, ast, true);

			// Function Symbol
			var functionSymbol = new FunctionSymbol();
			{
				functionSymbol.symbolId		= (++_this.symbolId);
				functionSymbol.name			= fnName;
				functionSymbol.type			= ast.type;
				functionSymbol.nodeType		= ast.nodeType;
				functionSymbol.className	= parentScope ? className : null;
				functionSymbol.classId		= classScope ? classId : null;
				functionSymbol.public		= ast.public==true;
				functionSymbol.private		= ast.private==true;
				functionSymbol.protected	= ast.protected==true;
				functionSymbol.static		= ast.static==true;
				functionSymbol.optional		= false;
				functionSymbol.virtual		= ast.virtual==true;
				functionSymbol.abstract		= ast.abstract==true;
				functionSymbol.ast			= ast;
				functionSymbol.scope		= methodScope;
				functionSymbol.baseSymbol	= baseMethodSymbol;
				functionSymbol.file			= ast.file;
				functionSymbol.path			= ast.path;
				functionSymbol.start		= ast.start;
				functionSymbol.end			= ast.end;
				functionSymbol.line_start	= ast.line_start;
				functionSymbol.line_end		= ast.line_end;
				functionSymbol.scopeId		= methodScope.scopeId;
				functionSymbol.vartype		= ast.returntype;
				functionSymbol.subtype		= ast.subtype ? ast.subtype : _this.getSubType(ast.returntype);
				functionSymbol.paramsList	= ast.paramsList;
				functionSymbol.arguments	= {};

    			if(classId && ast.public)			functionSymbol.runtime = classId + "." + fnName;
				else if(classId && ast.private)		functionSymbol.runtime = classId + ".__PRIVATE__." + fnName;
				else if(classId && ast.protected)	functionSymbol.runtime = classId + ".__PROTECTED__." + fnName;
				else								functionSymbol.runtime = fnName;
			}

           	// Save symbol
			ast.symbol = functionSymbol;
			parentScope.methods[fnName] = functionSymbol;

			// Record vartype usage in class level (used to check #includes)
			if(functionSymbol.subtype)
				parentScope.vartypes[functionSymbol.subtype] = true;
			else if(functionSymbol.vartype)
				parentScope.vartypes[functionSymbol.vartype] = true;

			// Process the Arguments List
			var paramsList = "";
			for(var i=0; i<ast.paramsList.length; i++)
			{
				var param = ast.paramsList[i];
				param.isPointer = __isPointer(param.vartype);
				paramsList += param.name;
				if(i!=ast.paramsList.length-1) paramsList +=", ";

                // Type Checks
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
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
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
					varSymbol.runtime		= param.name;
				}

				// Detect if identifier vartype is a typed array and get its subtype.
				if(!varSymbol.subtype && varSymbol.vartype)
				{
					var vtcls = _this.getClass(varSymbol.vartype);
					if(vtcls && vtcls.subtype)
						varSymbol.subtype = vtcls.subtype;
				}

				// Save the argument symbol
				param.symbol = varSymbol;
				methodScope.vars[param.name] = varSymbol;
				functionSymbol.arguments[varSymbol.name] = varSymbol;

    			// Record vartype usage in class level (used to check #includes)
    			/*
				if(varSymbol.subtype)
					parentScope.vartypes[varSymbol.subtype] = true;
				else if(varSymbol.vartype)
						parentScope.vartypes[varSymbol.vartype] = true;
						*/

			}
			paramsList = "(" + paramsList + ")";

	        // Generate Global scope function (plain JavaScript function)
	        if(isGlobal)
	        {
	  			out.push("function " + fnName + paramsList + "{");
				out.push(generate(ast.body));
				out.push("}");
	        }

	        // Generate Class member function
	        else if(classScope)
	        {
	  			// Function definition
	  			if(ast.isConstructor)
	  			{
	  			 	out.push("this.Constructor=function(){");

					// Generate constructor arguments as variables
					for(var i=0; i<ast.paramsList.length; i++)
						out.push("var " + ast.paramsList[i].name + "=arguments[" + i + "];");
	  			}
	  			else
	  			{
	  				if(_this.in_property)		out.push(_this.in_property + " function" + paramsList + "{");
	  				else if(ast.public)			out.push("var " + fnName + " = this." + fnName + " = function" + paramsList + "{");
	  				else if(ast.private)		out.push("this.__PRIVATE__." + fnName + " = function" + paramsList + "{");
	  				else if(ast.protected)		out.push("this.__PROTECTED__." + fnName + " = function" + paramsList + "{");
	  				else _this.NewError("No access modifier defined for function: " + fnName, ast);
	  			}

				// Generate Function Body
				ast.fnBody = generate(ast.body);
				out.push(ast.fnBody);

				// Generate default return value
				if(!ast.isConstructor && !ast.isDestructor)
				{
					var vartype = _this.getVarType(ast.returntype);
					if(_this.types.hasOwnProperty(vartype))
						out.push("return " + _this.types[vartype].default);
				}

				out.push("}");
				if(!_this.in_property) out.push(";");

				// We check overloaded functions once they are all generated.
				if(_this.secondPass && ast.overloadOf && fnName==ast.overloadOf.name+"$"+ast.overloadOf.overloads.length)
				{
					// Get all overloaded functions in one list
					var overloads = [ast.overloadOf].concat(ast.overloadOf.overloads);

					// Overloaded functions must all have a different signature.
					for(var i=0;i<overloads.length;i++)
					{
						// Make sure all overloads know they are overloaded.
						overloads[i].symbol.overloads = overloads;

						for(var j=i+1;j<overloads.length;j++)
						{
							if(overloads[i]!=overloads[j] && overloads[i].paramsList.length==overloads[j].paramsList.length)
							{
								var redeclaration = true;
								for(var k=0; k<overloads[i].paramsList.length; k++)
								{
									//if(_this.typeCheck(overloads[j].paramsList[k], overloads[i].paramsList[k].vartype, overloads[j].paramsList[k].vartype, null, true))
									if(overloads[i].paramsList[k].vartype!=overloads[j].paramsList[k].vartype)
									{
										redeclaration=false;
										break;
									}
								}
								if(redeclaration)
								{
									_this.NewError("Redeclaration of function " + overloads[j].name, overloads[i]);
								}
							}
						}
					}
				}

				// Check function return paths
				if(_this.secondPass && ast.file && ast.file!="externs.jspp")
				{
					if(!ast.isConstructor && baseMethodSymbol && !baseMethodSymbol.virtual)
						_this.NewError("Base class method is not virtual: " + fnName, ast);

					if(ast.returntype && ast.returnPaths.length==0)
						_this.NewError("Function must return a value: " + fnName, ast);

					if(ast.returntype && !_this.getClass(ast.returntype))
						_this.NewError("Return type not found " + ast.returntype, ast);

					for(var i=0;i<ast.returnPaths.length;i++)
					{
						if(ast.returntype && !ast.returnPaths[i].value)
							_this.NewError("Function must return a value: " + fnName, ast);

						else if(!ast.returntype && ast.returnPaths[i].value)
							_this.NewError("Function does not return a value: " + fnName, ast);

						else
						{
							var type = _this.getTypeName(ast.returnPaths[i].value);
							_this.typeCheck(ast.returnPaths[i].value, ast.returntype, type);
						}
					}
				}
	        }

	        // Generate Anonymous function
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
			var classScope = _this.getClassScope();
			var classSymbol = ast.scope.isClass ? ast.scope.ast.symbol : null;
			var classId	= classSymbol ? classSymbol.classId : null;
			var firstItem = true;
			var extern_symbol = null;

			if(ast.scope.isClass && !ast.inFunction)
			{
				// Declare class variable depending on its modifier
				if(ast.public)			out.push("this.");
				else if(ast.private)	out.push("this.__PRIVATE__.");
				else if(ast.protected)	out.push("this.__PROTECTED__.");
			}
			else
			{
				// Standard var declaration
				out.push("var ");
			}

			// Process var items to record symbols and generate code
			for(var item in ast)
			{
				if(!isFinite(item)) break;

				// Variables defined in JavaScript global scope such as plain JavaScript files are untyped.
				// Such variables are window, document, canvas, gl, engine, etc. You can define their type
				// inside externs.jspp and the compiler will automatically link the extern_symbol.
				var extern_symbol = null;

                // Type Checks
				if(!ast[item].vartype && _this.currClassName)
					_this.NewError("Type declaration missing " + ast[item].name, ast);

				if(_this.secondPass && _this.currClassName && !_this.getClass(ast[item].vartype))
					_this.NewError("Class not found: " + ast[item].vartype, ast[item]);

				if(Object.prototype.hasOwnProperty.call(ast.scope.vars, ast[item].name))
				{
					// If a var is wrapped inside "#ignore_errors" directive we do not complain for redeclaration.
					if(_this.no_errors)
						extern_symbol = ast.scope.vars[ast[item].name];

					else if(!_this.secondPass)
						_this.NewError("Redeclaration of variable " + ast[item].name + " in current scope", ast[item]);
				}

				if(!_this.secondPass)
			 	{
					if(classScope && Object.prototype.hasOwnProperty.call(classScope.vars, ast[item].name) && !_this.isInside(ast[item], jsdef.BLOCK))
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
					varSymbol.classId		= classId;
					varSymbol.public		= ast.public;
					varSymbol.private		= ast.private;
					varSymbol.protected		= ast.protected;
					varSymbol.static		= ast.static;
					varSymbol.optional		= false;
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
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

					if(classId && ast.public)			varSymbol.runtime = classId + "." + ast[item].name;
					else if(classId && ast.private)		varSymbol.runtime = classId + ".__PRIVATE__." + ast[item].name;
					else if(classId && ast.protected)	varSymbol.runtime = classId + ".__PROTECTED__." + ast[item].name;
					else								varSymbol.runtime = ast[item].name;
				}

				// Update vartype from extern
				if(extern_symbol)
				{
					varSymbol.vartype = extern_symbol.vartype;
					varSymbol.subtype = extern_symbol.subtype;
					varSymbol.isPointer = __isPointer(varSymbol.vartype);
				}

				// Detect if identifier vartype is a typed array and get subtype.
				if(!varSymbol.subtype && varSymbol.vartype)
				{
					var vtcls = _this.getClass(varSymbol.vartype);
					if(vtcls && vtcls.subtype)
						varSymbol.subtype = vtcls.subtype;
				}

                // Save var in scopes
				ast[item].symbol = varSymbol;
				ast.scope.vars[ast[item].name] = varSymbol;

				// Record vartype usage in class level (used to check #includes)
				if(classScope)
				{
					if(varSymbol.subtype)
						classScope.vartypes[varSymbol.subtype] = true;
					else if(varSymbol.vartype)
						classScope.vartypes[varSymbol.vartype] = true;
				}

				if(!firstItem) out.push(", ");
				out.push(ast[item].name);
				if(ast.scope.isState) out.push(" = this." + ast[item].name);

				if(ast[item].initializer)
				{
					// Generate initializer
					if(_this.currClassName && ast.type!=jsdef.CONST && (ast.scope.isClass || ast.scope.isState) && !ast.inFunction)
					{
						if(_this.in_state)
							_this.NewError("Invalid state variable initializer, should be in state enter() function : " + ast[item].name, ast[item]);
						else
							_this.NewError("Invalid class member initializer, should be in constructor: " + ast[item].name, ast[item]);
					}

					out.push("=");
					out.push(generate(ast[item].initializer));
				}
				else
				{
					var vartype = _this.getVarType(ast[item].vartype);
					if(_this.types.hasOwnProperty(vartype))
						out.push("="+_this.types[vartype].default);
					else if(ast.scope.isClass || ast.scope.isState)
						out.push("=null");
				}

				firstItem = false;
			}

			out.push(";");
			break;

		// ==================================================================================================================================
		//	    ______
		//	   / ____/___  __  ______ ___  _____
		//	  / __/ / __ \/ / / / __ `__ \/ ___/
		//	 / /___/ / / / /_/ / / / / / (__  )
		//	/_____/_/ /_/\__,_/_/ /_/ /_/____/
		//
		// ==================================================================================================================================

		case jsdef.ENUM:

			var scope = _this.getCurrentScope();
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";

			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId	= (++_this.symbolId);
				classSymbol.name		= ast.name;
				classSymbol.vartype		= ast.name;
				classSymbol.classId		= classId;
				classSymbol.base		= null;
				classSymbol.baseSymbol	= null;
				classSymbol.type		= jsdef.CLASS;
				classSymbol.nodeType	= "CLASS";
				classSymbol.isPrototype = false;
				classSymbol.isEnum		= true;
				classSymbol.isState		= false;
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
				classSymbol.runtime		= ast.name;
			}

			// Save symbol
			ast.symbol = classSymbol;
			_this.classes[classSymbol.name] = classSymbol;

            // Generate enum
			if(ast.public)			out.push("this.");
			else if(ast.private)	out.push("this.__PRIVATE__.");
			else if(ast.protected)	out.push("this.__PROTECTED__.");
			out.push(ast.name + " = {");
			var firstItem = true;
			for(item in ast)
			{
				if(!isFinite(item)) break;

				// Enum Item Symbol
				var varSymbol = new VarSymbol()
				{
					varSymbol.symbolId		= (++_this.symbolId);
					varSymbol.name			= ast[item].name;
					varSymbol.value			= ast[item].value;
					varSymbol.type			= ast[item].type;
					varSymbol.nodeType		= ast[item].nodeType;
					varSymbol.classId		= classId;
					varSymbol.public		= true;
					varSymbol.private		= false;
					varSymbol.protected		= false;
					varSymbol.static		= true;
					varSymbol.optional		= false;
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
					varSymbol.constant		= true;
					varSymbol.ast			= ast[item];
					varSymbol.scope			= scope;
					varSymbol.baseSymbol	= null;
					varSymbol.file			= ast[item].file;
					varSymbol.path			= ast[item].path;
					varSymbol.start			= ast[item].start;
					varSymbol.end			= ast[item].end;
					varSymbol.line_start	= ast[item].line_start;
					varSymbol.line_end		= ast[item].line_end;
					varSymbol.scopeId		= scope.scopeId;
					varSymbol.vartype		= ast.name;
					varSymbol.subtype		= ast[item].subtype ? ast[item].subtype : _this.getSubType(vartype);
					varSymbol.pointer		= false;

					if(ast.public)			varSymbol.runtime = "this." + ast.name + "." + varSymbol.name;
					else if(ast.private)	varSymbol.runtime = "this.__PRIVATE__." + ast.name + "." + varSymbol.name;
					else if(ast.protected)	varSymbol.runtime = "this.__PROTECTED__." + ast.name + "." + varSymbol.name;
				}
				classSymbol.vars[varSymbol.name] = varSymbol;

				if(!firstItem) out.push(", ");
				out.push(ast[item].name + ":" + ast[item].value);
				firstItem = false;
			}
			out.push("};");
			break;

		// ==================================================================================================================================
		//	    ____                             __
		//	   / __ \_________  ____  ___  _____/ /___  __
		//	  / /_/ / ___/ __ \/ __ \/ _ \/ ___/ __/ / / /
		//	 / ____/ /  / /_/ / /_/ /  __/ /  / /_/ /_/ /
		//	/_/   /_/   \____/ .___/\___/_/   \__/\__, /
		//	                /_/                  /____/
		// ==================================================================================================================================
		case jsdef.PROPERTY:

			ast.isPointer = __isPointer(ast.vartype);

			if(!_this.currClassName)
				_this.NewError("Invalid property outside class", ast);

			var propertyScope = ast.scope = _this.NewScope(ast);
			var parentScope = propertyScope.parentScope;	// Could be State scope or Class scope
			var classScope = _this.getClassScope();			// Class scope
			var className = classScope ? classScope.ast.name : null;
			var classId = classScope ? classScope.ast.symbol.classId : null;
			var classSymbol = classScope.ast.symbol;
			var propertyName = (ast.name ? ast.name : "");

            // Check for redeclaration
			if(!_this.secondPass && Object.prototype.hasOwnProperty.call(parentScope.vars, propertyName))
				_this.NewError("Redeclaration of property " + propertyName, ast);

           	// Define property symbol
			var propSymbol = new PropSymbol();
			{
				propSymbol.symbolId		= (++_this.symbolId);
				propSymbol.name			= propertyName;
				propSymbol.value		= null;
				propSymbol.type			= ast.type;
				propSymbol.nodeType		= ast.nodeType;
				propSymbol.classId		= classId;
				propSymbol.public		= ast.public;
				propSymbol.private		= ast.private;
				propSymbol.protected	= ast.protected;
				propSymbol.static		= ast.static;
				propSymbol.optional		= false;
				propSymbol.virtual		= ast.virtual;
				propSymbol.abstract		= ast.abstract;
				propSymbol.constant		= false;
				propSymbol.ast			= ast;
				propSymbol.scope		= ast.scope;
				propSymbol.baseSymbol	= null;
				propSymbol.file			= ast.file;
				propSymbol.path			= ast.path;
				propSymbol.start		= ast.start;
				propSymbol.end			= ast.end;
				propSymbol.line_start	= ast.line_start;
				propSymbol.line_end		= ast.line_end;
				propSymbol.scopeId		= ast.scope.scopeId;
				propSymbol.vartype		= ast.vartype;
				propSymbol.subtype		= ast.subtype ? ast.subtype : _this.getSubType(ast.vartype);
				propSymbol.pointer		= ast.isPointer;

				if(ast.public)				propSymbol.runtime = classId + "." + propertyName;
				else if(ast.private)		propSymbol.runtime = classId + ".__PRIVATE__." + propertyName;
				else if(ast.protected)		propSymbol.runtime = classId + ".__PROTECTED__." + propertyName;
				else						propSymbol.runtime = propertyName;
			}

           	// Save symbol
			ast.symbol = propSymbol;
			classSymbol.scope.vars[propertyName] = propSymbol;

			// Generate code
			var definition;

			if(ast.public)			definition = "this";
			else if(ast.private)	definition = "this.__PRIVATE__";
			else if(ast.protected)	definition = "this.__PROTECTED__";

			out.push("Object.defineProperty(" + definition + ", '" + propertyName + "', {enumerable:true,");

			_this.in_property = "get: ";
			out.push(generate(ast.getter) + (ast.setter?",":""));

			if(ast.setter)
			{
				_this.in_property = "set: ";
				out.push(generate(ast.setter));
			}

			out.push("});");

			_this.in_property = null;
			_this.ExitScope();
			break;

		// ==================================================================================================================================
		//	    ___________ __  ___   _____ __        __
		//	   / ____/ ___//  |/  /  / ___// /_____ _/ /____
		//	  / /_   \__ \/ /|_/ /   \__ \/ __/ __ `/ __/ _ \
		//	 / __/  ___/ / /  / /   ___/ / /_/ /_/ / /_/  __/
		//	/_/    /____/_/  /_/   /____/\__/\__,_/\__/\___/
		//
		// ==================================================================================================================================

		case jsdef.STATE:

			if(!_this.currClassName)
				_this.NewError("Invalid state outside class", ast);

			if(_this.states.hasOwnProperty(ast.name))
				_this.NewError("Duplicate state name: " + ast.name, ast);

			var hasTick = false;
			var classSymbol = _this.getCurrentScope().ast.symbol;
			_this.in_state = ast.name;

			ast.scope = _this.NewScope(ast);

            // A state must be defined inside a state machine class.
			if(!classSymbol.ast.state)
				_this.NewError("Invalid state context, missing state class modifier", ast);

			// State Symbol
			var stateSymbol = new StateSymbol()
			{
				stateSymbol.symbolId		= (++_this.symbolId);
				stateSymbol.name			= ast.name;
				stateSymbol.value			= ast.name;
				stateSymbol.type			= jsdef.STATE;
				stateSymbol.nodeType		= ast.nodeType;
				stateSymbol.classId			= classSymbol.classId;
				stateSymbol.state			= true;
				stateSymbol.public			= ast.public==true;
				stateSymbol.private			= ast.private==true;
				stateSymbol.protected		= ast.protected==true;
				stateSymbol.static			= true;
				stateSymbol.optional		= false;
				stateSymbol.virtual			= false;
				stateSymbol.abstract		= false;
				stateSymbol.constant		= false;
				stateSymbol.ast				= ast;
				stateSymbol.scope			= ast.scope;
				stateSymbol.baseSymbol		= null;
				stateSymbol.file			= ast.file;
				stateSymbol.path			= ast.path;
				stateSymbol.start			= ast.start;
				stateSymbol.end				= ast.end;
				stateSymbol.line_start		= ast.line_start;
				stateSymbol.line_end		= ast.line_end;
				stateSymbol.scopeId			= ast.scope.scopeId;
				stateSymbol.vartype			= "State";
				stateSymbol.subtype			= null;
				stateSymbol.pointer			= true;

				if(ast.public)			stateSymbol.runtime = classSymbol.classId + "." + ast.name;
				else if(ast.private)	stateSymbol.runtime = classSymbol.classId + ".__PRIVATE__." + ast.name;
				else if(ast.protected)	stateSymbol.runtime = classSymbol.classId + ".__PROTECTED__." + ast.name;
				else					stateSymbol.runtime = ast.name;
			}

			ast.symbol = stateSymbol;
			classSymbol.scope.vars[ast.name] = stateSymbol;
			//if(classSymbol.baseSymbol) classSymbol.baseSymbol.vars[ast.name] = stateSymbol;
			_this.states[ast.name] = stateSymbol;

			if(ast.public)			out.push("this.");
			else if(ast.private)	out.push("this.__PRIVATE__.");
			else if(ast.protected)	out.push("this.__PROTECTED__.");

            //TODO: The following code does not hit breakpoints for the first function of the State in v8/Chrome.

			out.push(ast.name + " = (function(){");

			out.push("this.__name = '" + ast.name + "';");

			for(item in ast.body)
			{
				if(!isFinite(item)) break;
				switch(ast.body[item].type)
				{
				case jsdef.CONST:
				case jsdef.VAR:
					out.push(generate(ast.body[item]));
					break;

				case jsdef.FUNCTION:
					if(ast.body[item].name=="tick") hasTick = true;
					out.push(generate(ast.body[item]));
 					break;
				}
			}
			out.push("return this}).call(new State);");

            // Tick function must be implemented.
			if(!hasTick)
				_this.NewError("Missing state tick function: " + ast.name, ast);

			_this.in_state = false;
			_this.ExitScope();
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
			if(_this.secondPass)
			{
				ast.symbol = _this.getCurrentClass().baseSymbol;
				ast.runtime = "__SUPER__." + ast.symbol.classId;
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.THIS:
			if( ast.inFunction && ast.inClass)
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

			//==================================================================================
			// First pass or not inside a class?
			//==================================================================================
			if(!_this.currClassName || !_this.secondPass)
			{
				// Generate identifier and be gone.
				out.push(ast.value);
				break;
			}

			//==================================================================================
			// Lookup the symbol for this identifier.
			//==================================================================================

			if(!ast.symbol)
				ast.symbol = _this.LookupIdentifier(_this.getCurrentScope(), ast.value, ast);

			if(!ast.symbol)
			{
				ast.runtime = ast.value;
				out.push(ast.runtime);
				_this.NewError("Symbol not found: " + ast.value, ast);
				break;
			}

			//==================================================================================
			// Check array length and suggest size() for C++ compatibility
			//==================================================================================
			if(ast.value=="length" && ast.inDot && ast.inDot.identifier_first.symbol &&
			   ast.inDot.identifier_first.symbol.vartype.indexOf("Array")==0)
			{
				_this.NewError("Please use size() for array length.", ast);
			}

			//==================================================================================
			// Treat subtype of typed arrays and vartype/subtype for #includes
			//==================================================================================
			switch(ast.value)
			{
			case "Float32Array":	ast.symbol.subtype = "Float"; break;
			case "Int32Array":		ast.symbol.subtype = "int"; break;
			case "Uint8Array":		ast.symbol.subtype = "uint8_t"; break;
			default:

				// Add vartype to class vartypes lists (used to determine #includes)
				var classScope = _this.getClassScope();
				if(classScope)
				{
					if(ast.symbol.subtype)
						classScope.vartypes[ast.symbol.subtype] = true;
					else if(ast.symbol.vartype)
						classScope.vartypes[ast.symbol.vartype] = true;
				}
			}

			//==================================================================================
			// Is this identifier a standard var declaration?
			//==================================================================================
			if(!ast.symbol.public && !ast.symbol.private && !ast.symbol.protected)
			{
				out.push(ast.value);
				break;
			}

			//==================================================================================
			// If the identifier's symbol is an overloaded function we need
			// to determine from the execution context which overload to use.
			//
			// We need to consider the places where an overloaded function might appea:
			// 1) as right-value in an assignment (function pointer):	var fn:Function = foo;
			// 2) as an argument in a function call					: 	goo(foo);
			// 3) as a call (that could be in a DOT)				:	foo() + object.foo()
			//
			//==================================================================================
			if(ast.symbol.overloads)
			{
				var astCALL=null;

				// Function pointer inside a call.
				// We need a static overload.

				if(ast.parent.type==jsdef.LIST)
				{
					for(var i=ast.symbol.overloads.length-1;i>=0;i--)
					{
						if(ast.symbol.overloads[i].symbol.static)
						{
							ast.symbol = ast.symbol.overloads[i].symbol;
							ast.value = ast.symbol.name;
							break;
						}
					}
					if(!ast.symbol.static)
						_this.NewError("Overloaded function pointer must be static.", ast);
				}

				// A jsdef.CALL to an overload function.
				// Determine overload from args.

				else if(astCALL=_this.isInside(ast, jsdef.CALL))
				{
					var overload_matched = false;

					// Test every overloaded function
					for(var i=ast.symbol.overloads.length-1;i>=0;i--)
					{
						if(ast.symbol.overloads[i].paramsList.length==astCALL[1].length)
						{
							// Test every argument
							var maching_args = true;
							for(var j=0;j<astCALL[1].length;j++)
							{
								var type1 = _this.getTypeName(astCALL[0][j]);
								var type2 = ast.symbol.overloads[i].paramsList[j].vartype;
								if(!_this.typeCheck(ast, type1, type2, null, true))
								{
									maching_args=false;
									break;
								}
							}
							if(maching_args)
							{
								// Found the proper overloaded function!!
								ast.symbol = ast.symbol.overloads[i].symbol;
								ast.value = ast.symbol.name;
								overload_matched = true;
								break;
							}
						}
					}

					if(!overload_matched)
						_this.NewError("Invalid call to overloaded method.", ast);
				}
			}

			//==================================================================================
			// Purpose of the following code is to emit the runtime code
			// for the current identifier. If the identifier is a class
			// member such as a method, variable, property or state, then
			// we need to emit a canonical name such as:
			//
			// __CLASS_NAME__.[<public>|__PRIVATE__|__PROTECTED__].<identifier>
			//
			// An exception to this rule is when the identifier is part of
			// a DOT and in particular if the identifier is !not! the first
			// identifier of the DOT, in which case we emit only its name
			// as the preceding identifiers should have emitted the proper
			// runtime code.
			//==================================================================================

			if(!ast.inDot || (ast.inDot && ast.inDot.identifier_first==ast))
			{
				ast.runtime = ast.symbol.runtime;

				// Identifier defined in base class?
				var cls = _this.getCurrentClass();
				if(!ast.symbol.isEnum && ast.symbol.ast.file.indexOf(".jspp")!=-1
					&& cls && cls.baseSymbol && cls.baseSymbol.file!="externs.jspp"
					&& cls.baseSymbol==ast.symbol.ast.inClass.symbol)
				{
					ast.runtime = _this.getCurrentClass().classId + ".__SUPER__." + ast.value;
				}
			}

			// Generate identifier
			if(!ast.inDot)
			{
				out.push(ast.runtime);
			}
			else
			{
				if(ast.inDot.identifier_first==ast)
				{
					out.push(ast.runtime);
				}

				// The rest case assume identifier is not the first in DOT.

				else if(ast.symbol.public)
				{
					out.push(ast.value);
				}
				else if(ast.symbol.protected)
				{
					out.push("__PROTECTED__." + ast.value);
				}
				else if(ast.symbol.private)
				{
					out.push("__PRIVATE__." + ast.value);
				}
			}

			//==================================================================================
			// Check member access
			//==================================================================================
			if(ast.symbol.private && ast.inClass!=ast.symbol.ast.inClass)
			{
				_this.NewError("Invalid private member access: " + ast.value, ast);
			}
			else if(ast.symbol.protected && ast.inClass!=ast.symbol.ast.inClass && ast.inClass.symbol.baseSymbol!=ast.symbol.ast.inClass.symbol)
			{
				_this.NewError("Invalid protected member access: " + ast.value, ast);
			}

			//==================================================================================
			// Generate debug symbol
			//==================================================================================
			ast.runtime = out.join("");
			_this.addDebugSymbol(ast, ast.runtime);

			//==================================================================================
			// Done generating identifier
			//==================================================================================
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
			if(!ast.parent || (ast.parent && ast.parent.type!=jsdef.FUNCTION))
				_this.NewScope(ast);
			for(var item in ast)
			{
				if(!isFinite(item)) break;
				body.push(generate(ast[item]));
			}
			if(!ast.parent || (ast.parent && ast.parent.type!=jsdef.FUNCTION))
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
				if(!isFinite(item)) break;
				out.push(generate(ast[item]));
			}
			out.push("}\n");
			_this.ExitScope();
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CALL:
			var f = generate(ast[0]);
			var cls = _this.getClass(f);
			if(cls)
			{
				// Typcast
				ast.isTypeCasting = true;
				out.push(generate(ast[1]));
			}
			else
			{
				out.push(f);
				ast[0].type == jsdef.REGEXP && out.push(".exec");
				out.push("(");
				out.push(generate(ast[1]));
				out.push(")");
				_this.checkFunctionCall(ast);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.LIST:
		case jsdef.COMMA:
			var firstItem = true;
			for(var item in ast)
			{
				if(!isFinite(item)) break;
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
				if(!isFinite(item)) break;
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
				if(!isFinite(item)) break;
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
				if(!isFinite(item)) break;
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
				_this.NewError("Cannot assign to 'this'", ast);
			}
			else if(ast[0].type != jsdef.IDENTIFIER && ast[0].type != jsdef.DOT && ast[0].type != jsdef.INDEX)
			{
				_this.NewError("Invalid left-hand assignment", ast);
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
				if(!isFinite(_case)) break;
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
				_this.scopeId = _this.scopesStack.length-1;
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
					this.NewError(e.message, ast);
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
					this.NewError(e.message, ast);
				}
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.TRY:
			out.push("try");
			out.push(generate(ast.tryBlock));
			for(var catchClause in ast.catchClauses)
			{
				if(!isFinite(catchClause)) break;
				out.push("catch(" + ast.catchClauses[catchClause].varName + ")");
				out.push(generate(ast.catchClauses[catchClause].block));
				ast.finallyBlock && out.push("finally" + generate(ast.finallyBlock));
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DELETE:
			var expr = generate(ast[0]);
			if(_this.currClassName && _this.secondPass && ast[0].symbol)
			{
				out.push("{");
				if(ast[0].symbol.subtype && __isPointer(ast[0].symbol.subtype))
				{
					out.push("(function(o){for(var i=o.length;i--;){o[i] && ((o[i].hasOwnProperty('Destructor') && o[i].Destructor()) || !o[i].hasOwnProperty('Destructor')) && (delete o[i]);o[i]=null;}})(" + expr + ");");
				}
				out.push("$ && (($.hasOwnProperty('Destructor') && $.Destructor()) || !$.hasOwnProperty('Destructor')) && (delete $);$=null".replace(new RegExp("\\$", "g"), expr));
				out.push("}");
			}
			else
				out.push("delete " + expr);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.MUL:					_this.arithmeticOp(ast, "*", out); break;
		case jsdef.DIV:					_this.arithmeticOp(ast, "/", out); break;
		case jsdef.MINUS: 				_this.arithmeticOp(ast, "-", out); break;
		case jsdef.PLUS: 				_this.arithmeticOp(ast, "+", out); break;
		case jsdef.MOD:					_this.arithmeticOp(ast, "%", out); break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.AND:					out.push(generate(ast[0])); out.push("&&"); out.push(generate(ast[1])); break;
		case jsdef.BITWISE_AND:			out.push(generate(ast[0])); out.push("&"); out.push(generate(ast[1])); break;
		case jsdef.BITWISE_NOT:			out.push("~"); out.push(generate(ast[0])); break;
		case jsdef.BITWISE_OR:			out.push(generate(ast[0])); out.push("|"); out.push(generate(ast[1])); break;
		case jsdef.BITWISE_XOR:			out.push(generate(ast[0])); out.push("^"); out.push(generate(ast[1])); break;
		case jsdef.BREAK:				out.push("break;"); break;
		case jsdef.CASE:				out.push("case " + generate(ast.caseLabel) + ":"); out.push(generate(ast.statements)); break;
		case jsdef.CONTINUE:			out.push("continue;"); break;
		case jsdef.DEBUGGER:			out.push("debugger;"); break;
		case jsdef.DECREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("--"); } else { out.push("--"); out.push(generate(ast[0])); } break;
		case jsdef.DEFAULT:				out.push("default:"); out.push(generate(ast.statements)); break;
		case jsdef.DO: 					ast.body.isLoop = true; out.push("do"); out.push(generate(ast.body)); out.push("while(" + generate(ast.condition) + ");"); break;
		case jsdef.EQ: 					out.push(generate(ast[0])); out.push("==");	 out.push(generate(ast[1])); break;
		case jsdef.EXPONENT:			out.push("Math.pow(" + generate(ast[0]) + "," + generate(ast[1]) + ")");break;
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
		case jsdef.NE:					out.push(generate(ast[0])); out.push("!=");	 out.push(generate(ast[1])); break;
		case jsdef.NEW: 				out.push("new "); out.push(generate(ast[0])); break;
		case jsdef.NOT:					out.push("!"); out.push(generate(ast[0])); break;
		case jsdef.NULL:				out.push("null"); break;
		case jsdef.NUMBER:				out.push(ast.value); break;
		case jsdef.OR:					out.push(generate(ast[0])); out.push("||"); out.push(generate(ast[1]));	break;
		case jsdef.RETURN:				out.push("return"); if(ast.value) out.push(" " + generate(ast.value)); out.push(";\n"); break;
		case jsdef.RSH:					out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break;
		case jsdef.SEMICOLON:			var expr = (ast.expression ? generate(ast.expression) : ""); if(expr) out.push(expr + ";\n"); break;
		case jsdef.STRICT_EQ:			out.push(generate(ast[0])); out.push("=="); out.push(generate(ast[1])); break;
		case jsdef.STRICT_NE:			out.push(generate(ast[0]));	out.push("!="); out.push(generate(ast[1])); break;
		case jsdef.THROW:				out.push("throw "); out.push(generate(ast.exception)); out.push(";"); break;
		case jsdef.TRUE:				out.push("true"); break;
		case jsdef.TYPEOF:				out.push("typeof "); out.push(generate(ast[0])); break;
		case jsdef.UNARY_MINUS:			out.push(" -"); out.push(generate(ast[0])); break;
		case jsdef.UNARY_PLUS:			out.push(" +"); out.push(generate(ast[0])); break;
		case jsdef.URSH:				out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break;
		case jsdef.VOID:				out.push("void "); out.push(generate(ast[0])); break;
		case jsdef.WHILE:				ast.body.isLoop=true; out.push("while(" + generate(ast.condition) + ")"); out.push(generate(ast.body)); break;

		case jsdef.NEW_WITH_ARGS:
			out.push("new ");
			out.push(generate(ast[0]));
			out.push("(");
			out.push(generate(ast[1]));
			out.push(")");
			_this.checkFunctionCall(ast);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		default:
			//debugger;
		}

		return out.join("");
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.arithmeticOp = function(ast, op, out)
	{

		var g0 = _this.generate(ast[0]);
		var g1 = _this.generate(ast[1]);
		/*
		if(_this.secondPass)
		{
			var t0 = _this.getTypeName(ast[0]);
			var t1 = _this.getTypeName(ast[1]);
			if(t0=="Time" || t1=="Time")
			{
				var decimals = "1e8";
				g0 = "(Math.round((" + g0 + ")*" + decimals + "))";
				g1 = "(Math.round((" + g1 + ")*" + decimals + "))";
				out.push("((");
				out.push(g0);
				out.push(op);
				out.push(g1);
				out.push(")/" + decimals + ")");
				return;
			}
		}
		*/
		out.push(g0);
		out.push(op);
		out.push(g1);
	}

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
			if(!isFinite(item)) break;
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
		var classId = className;//"__CLASS__" + className.toUpperCase() + "__";

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
			classSymbol.runtime		= className;
		}
		ast.symbol = classSymbol;
		_this.classes[className] = classSymbol;
		_this.scopesStack[0].vars[className] = classSymbol;

		for(var item in ast)
		{
			if(!isFinite(item)) break;
			var varSymbol = new VarSymbol()
			{
				varSymbol.symbolId		= (++_this.symbolId);
				varSymbol.name			= ast[item][0].value;
				varSymbol.value			= ast[item][1].value;
				varSymbol.type			= jsdef.ENUM_ITEM;
				varSymbol.nodeType		= "ENUM_ITEM";
				varSymbol.classId		= classId;
				varSymbol.public		= true;
				varSymbol.private		= false;
				varSymbol.protected		= false;
				varSymbol.static		= true;
				varSymbol.optional		= false;
				varSymbol.virtual		= false;
				varSymbol.abstract		= false;
				varSymbol.constant		= true;
				varSymbol.ast			= ast[item];
				varSymbol.scope			= scope;
				varSymbol.baseSymbol	= null;
				varSymbol.file			= ast[item].file;
				varSymbol.path			= ast[item].path;
				varSymbol.start			= ast[item].start;
				varSymbol.end			= ast[item].end;
				varSymbol.line_start	= ast[item].line_start;
				varSymbol.line_end		= ast[item].line_end;
				varSymbol.scopeId		= scope.scopeId;
				varSymbol.vartype		= className;
				varSymbol.subtype		= ast[item].subtype ? ast[item].subtype : _this.getSubType(vartype);
				varSymbol.pointer		= false;
				varSymbol.runtime 		= varSymbol.name;
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
			varSymbol.virtual		= false;
			varSymbol.abstract		= false;
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
			varSymbol.runtime 		= classSymbol.classId + "." + varSymbol.name;

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
			MUL: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number","Float":"Number", "Time":"Number"  } },
			DIV: 	{ "Boolean": { "Boolean": "Number", "Number": "Number" }, "Number": { "Boolean": "Number", "Number": "Number", "Float":"Number", "Time":"Number" } },
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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		if(!_this.secondPass || !_this.currClassName || !ast) return;

		switch(ast.type)
		{
		//=============================================================================================================================
		case jsdef.ARRAY_INIT:		return "Array"
		case jsdef.ASSIGN:   		return _this.getTypeName(ast[0]);
		case jsdef.BITWISE_NOT:		return "Number";
		case jsdef.COMMA: 			return _this.getTypeName(ast[+ast.length-1]);
		case jsdef.DELETE:          return "Boolean";
		case jsdef.EQ:              return "Boolean";
		case jsdef.FALSE:           return "Boolean";
		case jsdef.GE:              return "Boolean";
		case jsdef.GROUP: 			return _this.getTypeName(ast[0]);
		case jsdef.GT:              return "Boolean";
		case jsdef.IN:              return "Boolean";
		case jsdef.INSIDE:          return "Boolean";
		case jsdef.INSTANCEOF:      return "Boolean";
		case jsdef.LE:              return "Boolean";
		case jsdef.LT:              return "Boolean";
		case jsdef.NE:              return "Boolean";
		case jsdef.NEW:           	return ast[0].symbol.name;
		case jsdef.NEW_WITH_ARGS:	return ast[0].symbol.name;
		case jsdef.NOT:             return "Boolean";
		case jsdef.NULL:			return "Null";
		case jsdef.NUMBER:			return "Number";
		case jsdef.OBJECT_INIT:		return "Object";
		case jsdef.REGEXP:			return "RegExp";
		case jsdef.STATE:			return "State";
		case jsdef.STRICT_EQ:       return "Boolean";
		case jsdef.STRICT_NE:       return "Boolean";
		case jsdef.STRING:			return "String";
		case jsdef.SUPER:			return ast.symbol.vartype;
		case jsdef.THIS:			return _this.currClassName || "Function";
		case jsdef.TRUE:			return "Boolean";
		case jsdef.TYPEOF:			return "String";
		case jsdef.VOID:			return _this.UNTYPED;

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
					_this.NewError("Illegal operation INCREMENT on: "+type, ast);
				else if (ast.type == jsdef.DECREMENT)
					_this.NewError("Illegal operation DECREMENT on: "+type, ast);
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
				   (operation[type1].hasOwnProperty(type2) ? operation[type1][type2] : _this.typeCheck(ast, type1, type2))
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
			if(!ast.symbol) return _this.UNTYPED;
			if(ast.symbol.type==jsdef.FUNCTION) return "Function";
			return ast.symbol.vartype;

		//=============================================================================================================================
		case jsdef.CALL:
			if(ast[0].type==jsdef.DOT)
			{
				var symbol = _this.LookupLastDotIdentifier(ast[0], _this.getCurrentScope());
				if(!symbol)
				{
					_this.NewError("Symbol not found: " + ast[0].identifier_last, ast[0]);
					return null;
				}
				return symbol.vartype;
			}
			return ast[0].symbol.vartype;

		//=============================================================================================================================
		case jsdef.INDEX:
			if(ast[0].type==jsdef.DOT)
			{
				var symbol = _this.LookupLastDotIdentifier(ast[0], _this.getCurrentScope());
				if(!symbol)
				{
					_this.NewError("Symbol not found: " + ast[0].identifier_last, ast[0]);
					return null;
				}
				return symbol.subtype;
			}
			return ast[0].symbol.subtype;
			break;

		//=============================================================================================================================
		case jsdef.DOT:
			var symbol = _this.LookupLastDotIdentifier(ast, _this.getCurrentScope());
			if(!symbol)
			{
				_this.NewError("Symbol not found: " + ast.source, ast);
				return null;
			}
			return symbol.vartype;

		//=============================================================================================================================
		default:
			//debugger;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.checkFunctionCall = function(ast)
	{
		if(!_this.secondPass || !_this.currClassName) return;

		var fnSymbol;

		if(ast.type==jsdef.NEW || ast.type==jsdef.NEW_WITH_ARGS)
		{
			fnSymbol = ast[0].symbol.methods['Constructor'];
		}
		else
		{
			switch(ast[0].type)
			{
			case jsdef.DOT:
				fnSymbol = ast[0].identifier_last.symbol;
				break;

			case jsdef.IDENTIFIER:
				fnSymbol = ast[0].symbol;
				break;

			case jsdef.SUPER:
				fnSymbol = ast[0].symbol.methods['Constructor'];
				break;

			default:
				//debugger;
			}
		}

		if(fnSymbol  && fnSymbol instanceof FunctionSymbol)
		{
			var i=0, item, arg, param, type1, type2;

			if(ast[1] && ast[1].length>fnSymbol.paramsList.length)
				_this.NewError("Too many arguments: " + ast.source, ast);

			for(item in fnSymbol.arguments)
			{
				arg = fnSymbol.arguments[item];
				type1 = arg.vartype;

				if(ast[1] && i<ast[1].length)
				{
					type2 = _this.getTypeName(ast[1][i]);
					_this.typeCheck(ast[1][i], type1, type2, "Argument type mismatch: "+type1+" and "+type2);
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
	_this.typeCheck = function(ast, type1, type2, customError, checkOnly)
	{
		//** Need to rewrite using Roger's convertion tables

		var _this = this;
		if(!_this.currClassName || !_this.secondPass) return;

		// Fast type checking
		if(type1==type2) return type1;

		// Resolve vartype and retry
		type1=_this.getVarType(type1);
		type2=_this.getVarType(type2);
		if(type1==type2) return type1;

		// Invalid left/right type
		if(!type1 || type1=="null" || type1==this.UNTYPED)
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid left type: " + (ast[0] ? ast[0] : ast).source, ast);
			return type1;
		}

		if(!type2 || type2=="null" || type2==_this.UNTYPED)
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid right type: " + (ast[1] ? ast[1] : ast).source, ast);
			return type2;
		}

        // Null
		if((__isPointer(type1) || type1 == "CocoAction") && type2=="Null") return type1;
		if(type1 == "CocoAction" && type2 == "Function") return type1;

  		// Object
		if(type1=="Object") return type1;

		// Number
		if(type1=="Number" && type2=="Integer") return type1;
		if(type1=="Number" && type2=="Float") return type1;
		if(type1=="Number" && type2=="Time") return type1;
		if(type1=="Number" && type2=="Object")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid Object to Number convertion", ast);
			return type1;
		}

		// Integer
		if(type1=="Integer" && type2=="Number") return type1;
		if(type1=="Integer")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Integer convertion", ast);
			return type1;
		};

		// Float
		if(type1=="Float" && type2=="Number") return type1;
        if(type1=="Float")
        {
        	if(checkOnly) return false;
        	_this.NewError(customError || "Invalid "+type2+" to Float convertion", ast);
        	return type1;
        };

		// Time
		if(type1=="Time" && type2=="Number") return type1;
		if(type1=="Time")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Time convertion", ast);
			return type1;
		};

		// Date
		if(type1=="Date" && type2=="Null") return type1;

        // String
		if(type1=="String" && type2=="Null")
		{
			if(ast.type==jsdef.NEW_WITH_ARGS) return type1;
			_this.NewWarning(customError || "String set to null, set to empty string instead", ast); return type1;
		}

    	// Boolean
		if(type1=="Boolean" && type2=="Number")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid Number to Boolean convertion", ast); return type1;
		}

		// State
		if(type1=="State" && type2=="Null") return type1;

        // UDT
		var cls1 = _this.getClass(type1);
		if(!cls1)
		{
			_this.NewError(customError || "Class not found: " + type1, ast);
			return type1;
		}

		var cls2 = _this.getClass(type2);
		if(!cls2)
		{
			_this.NewError(customError || "Class not found: " + type2, ast);
			return type1;
		}

		// Inheritance
		while(cls2)
		{
			if(cls1.name==cls2.name) return type1;
			cls2 = cls2.baseSymbol;
		}

		if(checkOnly) return false;
		_this.NewError(customError || "Type mismatch: " + type1 + " and " + type2, ast);
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

		if(ast.type==jsdef.IDENTIFIER && !ast.inDot)
		{
			identifier = ast.value;
			_this.debugSymbolsTable.push("<DEBUG_SYMBOL file='" + ast.path + "' s='" + ast.s + "' e='" + ast.e + "' start='" + ast.start + "' end='" + ast.end + "' line='" + ast.line_start + "' identifier='" + identifier + "' runtime='" + runtime +"'/>\n");
		}
		else if(ast.type==jsdef.IDENTIFIER && ast.inDot)
		{
			// Taken care by DOT
		}
		else if(ast.type==jsdef.DOT && _this.currClassName && !_this.isInside(ast, jsdef.DOT)) // Process top-level DOTs only, skip inner DOTs.
		{
			var v_identifiers = [], v_runtime = [], buff = [];
			for(var i=0;i<ast.identifiers_list.length;i++)
			{
				var f = ast.identifiers_list[i].ast;
				var value = ast.identifiers_list[i].value.replace("@@THIS@@", "this");
				if(f.type==jsdef.NEW || f.type==jsdef.NEW_WITH_ARGS)
				{
					v_identifiers.push(value);
					v_runtime.push(value);
				}
				else if(i==0)
				{
					v_identifiers.push(value);
					if(f.symbol)
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
				buff.push("<DEBUG_SYMBOL file='" + ast.path + "' s='" + ast.s + "' e='" + ast.e + "' start='" + f.start + "' end='" + f.end + "' line='" + f.line_start + "' identifier='" + v_identifiers.join(".") + "' runtime='" + v_runtime.join(".") +"'/>\n");
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

		var i, xml, cls, item, arg, args, argsList, xmlArgsList, hasArgs, scope, icon, sig, mbrList, mbrLists, scopeVars,
			classSymbol, methodSymbol, argumentSymbol, varSymbol, externs, modifier, codeSymbols, varsxml, states,
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
					if(varSymbol.type==jsdef.CLASS)
					{
						icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CLASS;
						modifier = "public";
						sig = varSymbol.name + varSymbol.ast.xmlvartype;
						mbrList.push('\t<member name="' + varSymbol.name + '" proto="' + sig + '" help="' + classSymbol.name + " :: " + sig + '" image="' + icon + '"/>');
					}
					else
					{
						icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;
						modifier = "public";
						if(varSymbol.private) { icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FIELD; modifier = "private"; }
						if(varSymbol.protected) { icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FIELD; modifier = "protected"; }
						if(varSymbol.constant) icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTANT;
						sig = varSymbol.name + varSymbol.ast.xmlvartype;
						mbrList.push('\t<member name="' + varSymbol.name + '" proto="' + sig + '" help="' + classSymbol.name + " :: " + sig + '" image="' + icon + '"/>');
						externs.push("\t" + modifier + " var " + varSymbol.name + (varSymbol.vartype ? " :"+ varSymbol.vartype : "") + ";\n");
					}

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
		for(i=0;i<_this.scopesTable.length;i++)
		{
			scope = _this.scopesTable[i];
			if(_this.selectedClass && _this.selectedClass!=scope.className) continue;

			varsxml = [];
			for(item in scope.vars)
			{
				varSymbol = scope.vars[item];
				if(!varSymbol.name || !varSymbol.vartype) continue;
				varsxml.push("\t<SYMBOL symbolId='"+varSymbol.symbolId + "' name='" + varSymbol.name +
							 "' type='" + varSymbol.nodeType + "' vartype='" + varSymbol.vartype.replace('<','&lt;').replace('>','&gt;') +
							 "' subtype='" + (varSymbol.subtype ? varSymbol.subtype : "") + "'/>\n");
			}

			for(item in scope.methods)
			{
				methodSymbol = scope.methods[item];
				if(!methodSymbol.name) continue;
				varsxml.push("\t<SYMBOL symbolId='"+methodSymbol.symbolId + "' name='" + methodSymbol.name + "' type='" + methodSymbol.nodeType +
							 "' vartype='" + (!methodSymbol.vartype ? "" : methodSymbol.vartype.replace('<','&lt;').replace('>','&gt;')) +
							 "' subtype='" + (methodSymbol.subtype ? methodSymbol.subtype : "") + "'/>\n");
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
		// Export States
		// ======================================================================================
		states = [];
		for(var item in _this.states)
		{
			states.push(item);
		}
		states = states.join(";");

		// ======================================================================================
		// Export to IDE
		// ======================================================================================

        //write("C:/Users/Admin/Desktop/codeSymbols.xml", codeSymbols);
        //write("C:/Users/Admin/Desktop/scopes.xml", scopeVars);
        //write("C:/Users/Admin/Desktop/members.xml", mbrLists);
        //write("C:/Users/Admin/Desktop/debugSymbols.xml", debugSymbols);

		if(!_this.selectedClass)
			jsppCallback("resetSymbols");

		jsppCallback("setCodeSymbols", "", "", 0, 0, codeSymbols);
		jsppCallback("setScopes", "", "", 0, 0, scopeVars);
		jsppCallback("setMemberLists", "", "", 0, 0, mbrLists);
		jsppCallback("setStates", "", "", 0, 0, states);

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
			if(v==null || v==undefined || v==NaN || v=="NaN") continue;
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
