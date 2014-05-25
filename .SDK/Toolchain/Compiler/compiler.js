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

	== 01/03/2014 ==

	29. Added support for new Array<subtype>. In C++ arrays are now pointers and need to be deleted.
	30. Arrays must be typed inside classes

	== 18/03/2014 ==

	31. Proper implementation for static
	32. Proper implementation for virtual by separating __BASE__ and __SUPER__ (NEED TESTING)
	33. Enums can be outside classes too (not recommended) and can have negative numbers

	== 17/04/2014 ==

	33. Re-engineered several inheritance related fragments of the code and extended the test-cases
	34. Proper implementation for static methods
	35. Changed constructor argumetns support and added C++ like base class constructor initialization
	36. Added compiler plugin support and moved exports and typesystem to plugins
	37. Separated exports per type and added Class Diagram explort for NClass

	== 27/04/2014 ==

	38. Added interndaces. A class can implement any number of interfaces using "implements" keyword
	    followed by a comma separated list of iterfaces. Interface inheritance is also supported.
	    Type checking has been extended to accomodate interfaces and type casting between classes
	    and interfaces. Casting an interface to a class is not supported and produces type cast error.

	40. Added delegates. A class-member object variable can de defined as "public|private|protected delegate var obj:ClassXXX"
		and the compiler will link at compile-time the public members of ClassXXX with the host class and generate the appropriate
		delegation wrappers. Works with overloaded function as well.

	== 22/05/2014 ==

	41. Implemented events both in JavaScript and C++. Events are supported through the CocoEventSource base class that
		all event sources must extend. Event listeners must implement the IEventListener interface. An event is declared
		by


	Elias G. Politakis
	epolitakis@mobilefx.com

	TODO LIST:
	==========

	- Bug in V8 prevents breakpoints if block statements starts with jsdef.NEW/NEW_WITH_ARGS assignment (jsflags --inline-new=false)
	- Proper support for ENUMS (need to check class-level enums)
	- Consts must become read-only properties
	- Delegation properties delegation and checks
	- x = new Array<type> must check against x symbol for subtype
	- Return path does not produce errors\
	- IMPORTANT: Need to detect jsdef.NEW and jsdef.NEW_WITH_ARGS inside method calls that produce memory leaks in
			     C++ and issue warnings. Possible define a weak_new operator and pass delete obligation to consumer?
	- IMPORTANT: State exit must deallocate local state variables.
	- CocoUIPageView::invalidateControls
	- check for loops that have i < somehting.size()

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Compiler(ast)
{
	// ast				: The abstract syntax tree root node as produced by the parser
	// selectedClass	: Used if we want to parse-only a single class for intelliSence use

	var _this = this;

	_this.ast = ast;                        // The Abstract Syntax Tree root node (jsdef.SCRIPT)
	_this.classes = {};                     // Map of class symbols
	_this.classFiles = {};					// Used in order to have multiple classes in one file
	_this.currClassName = null;             // The current class being processed (also indicates whether a JS++ class is being processed or just plain JavaScript code)
	_this.currFile = null;                  // Current File being processed
	_this.exportSymbols = false;		    // Flag that indicates whether symbols should be exported or not
	_this.fileClasses = {};                 // Map of classes per file (usage: _this.fileClasses[file][class] = ast; )
	_this.in_property = false;    			// Flag that indicates we are processing a property
	_this.in_state = false;    				// Flag that indicates we are processing a state
	_this.includes = [];                    // List of include files for current file being processed (resets per file)
	_this.line_start = -1;                  // Souce Line counter: source code lines "//@line xxx" are emitted in generated code for IDE debugger
	_this.lineNumbers = true;				// Supress line-number generation
	_this.no_errors = 0;                    // Semaphore that controls errors generation (used by ""#ignore_errors" directive)
	_this.scopeId = -1;                     // Scopes Counter (resets per file)
	_this.scopesStack = [];                 // Stack of Scopes (scopes are pushed and popped from it during generation)
	_this.scopesTable = [];                 // Table of Scopes (scopes are only pushed)
	_this.secondPass = false;               // Flag that indicates compiler's second pass
	_this.selectedClass = null;			    // If set it indicates that we only need to process a single class (used by IDE intelliSence for parsing classes as you type them)
	_this.states = {};						// Map of states
	_this.symbolId = -1;					// Symbols Counter
	_this.tokenizer = null;                 // Reference to tokenizer (reserved for future use)
	_this.UNTYPED = "Untyped";              // Untyped identifier vartype, used in Type Check System
	_this.eventId = 0;						// Counter for UID of events
	_this.derivatives = {};					// Classes with derivatives (base classes)

	// Include priority (1: needed in .cpp, 2: needed in .hpp)
	_this.INCLUDE_IN_CPP = 1;
	_this.INCLUDE_IN_HPP = 2;

	_this.DELETE_BASE = "__BASE__ && ((__BASE__.hasOwnProperty('Destructor') && __BASE__.Destructor()) || !__BASE__.hasOwnProperty('Destructor')) && (delete __BASE__);";
	_this.SEPARATOR = "\n\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n\n";
	_this.ADD_EVENT = "addEventListener";
	_this.REMOVE_EVENT = "removeEventListener";
	_this.DISPATCH_EVENT = "dispatchEvent";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Extend the compiler with plugins
	CompilerExportsPlugin(_this);
	CompilerTypeSystemPlugin(_this);
	CompilerAnalyzerPlugin(_this);
	CompilerCppPlugin(_this);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Symbol constructors
	var Scope 			= _this.Scope 			= function Scope() 				{}
	var ClassSymbol 	= _this.ClassSymbol 	= function ClassSymbol() 		{}
	var FunctionSymbol 	= _this.FunctionSymbol 	= function FunctionSymbol() 	{}
	var PropSymbol 		= _this.PropSymbol 		= function PropSymbol() 		{}
	var VarSymbol 		= _this.VarSymbol 		= function VarSymbol()			{}
	var StateSymbol 	= _this.StateSymbol 	= function StateSymbol() 		{}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewWarning = function (e, ast)
	{
		if(_this.selectedClass || _this.no_errors>0) return;
		if(!ast.__warnings) ast.__warnings = {};
		if(!ast.__warnings[e]) ast.__warnings[e] = 0;
		ast.__warnings[e]++;
		if(ast.__warnings[e]>1) return;
		trace(" !WARNING: " + e + "\n " + ast.path + " : line " + ast.line_start + "\n");
		IDECallback("warning", ast.path, ast.line_start, 0, e);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.NewError = function (e, ast)
	{
		if(_this.selectedClass || _this.no_errors>0) return;
		if(!ast.__errors) ast.__errors = {};
		if(!ast.__errors[e]) ast.__errors[e] = 0;
		ast.__errors[e]++;
		if(ast.__errors[e]>1) return;
		trace(" !ERROR: " + e + "\n " + ast.path + " : line " + ast.line_start + "\n");
		IDECallback("error", ast.path, ast.line_start, 0, e);
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.addCodeToClassFile = function(file, code)
	{
		if(_this.secondPass)
		{
			if(_this.classFiles[file]==null)
				_this.classFiles[file] = "";
			_this.classFiles[file] += "\n\n" + code;
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.write_javascript = function()
	{
		for(var p in _this.classFiles)
		{
			if(p != "externs.jspp")
			{
				var buff = _this.classFiles[p];
				if(!buff) continue;
				var buff = do_js_beautify(buff, 1, false, false, true);
				buff = RxReplace(buff, "//@line \\d+[\\s\\t\\n\\r]+//@line (\\d+)", "mg", "//@line $1"); 	// Empty Lines
				buff = RxReplace(buff, "__PDEFINE__\\(([\\w\\W\\n\\N]+?)\\);", "mg", "__PDEFINE__($1);", true);
				buff = RxReplace(buff, "(__PDEFINE__|__PROTECTED__|__PRIVATE__) \=[\\s\\t\\n\\r]+\{[\\s\\t\\n\\r]+\}", "mg", "$1 = {}");
				buff = RxReplace(buff, "__NOENUM__ \=[\\s\\t\\n\\r]+\{[^}]+\}", "mg", "__NOENUM__ = {enumerable:false}");
				buff = RxReplace(buff, ";[\\s\\t\\n\\r]*function F\\(\\)[\\s\\t\\n\\r]*\{[\\s\\t\\n\\r]*\}", "mg", "; function F(){}");
				buff = RxReplace(buff, "\\([\\s\\t\\n\\r]+", "mg", "(");
				buff = RxReplace(buff, "\\{[\\s\\t\\n\\r]*\\}", "mg", "{}");
				buff = RxReplace(buff, "(^[\\s\\t\\n\\r]*$)+", "mg", "");
				buff = RxReplace(buff, "[\\n\\s\\r\\t]+\\{[\\n\\s\\r\\t]*\\};", "mg", " {};");
				IDECallback("module_jspp", p, 0, 0, buff);
			}
		}
	};

	// ==================================================================================================================================
	//	   ______                      _ __
	//	  / ____/___  ____ ___  ____  (_) /__
	//	 / /   / __ \/ __ `__ \/ __ \/ / / _ \
	//	/ /___/ /_/ / / / / / / /_/ / / /  __/
	//	\____/\____/_/ /_/ /_/ .___/_/_/\___/
	//	                    /_/
	// ==================================================================================================================================

	_this.compile = function(exportSymbols, selectedClass, genrate_native)
	{
		_this.exportSymbols = exportSymbols;
		_this.selectedClass = selectedClass;

		// Pre-preocess ast
		_this.preprocess();

		// First pass to record symbols
		_this.generate(ast);

		if(!_this.selectedClass)
		{
			// Reset for second pass
			_this.eventId = 0;
			_this.symbolId = -1;
			_this.scopeId = -1;
			_this.secondPass = true;
			_this.scopesStack = [];
			_this.scopesTable = [];
			_this.debugSymbolsTable = [];
			_this.currClassName = null;
			_this.line_start = -1;
			_this.states = {};

			// Link base classes
			for(var c in _this.classes)
				if(_this.classes[c].base && !_this.classes[c].baseSymbol)
					_this.classes[c].baseSymbol = _this.classes[_this.classes[c].base];

			// Second pass to generate actual code
			_this.generate(ast);
			_this.write_javascript();
		}

		// Generate C++ code
		if(genrate_native)
		{
			_this.prepare_native_files();
			_this.generate_cpp(ast);
			_this.export_cpp_files();
		}

		// Detect memory leaks
		_this.detectMemoryLeaks();

		// Post-process to extract code and debug symbols
		_this.EXPORT_TO_IDE();
	};

	// ==================================================================================================================================
	//	    ____
	//	   / __ \________  ____  _________  ________  __________
	//	  / /_/ / ___/ _ \/ __ \/ ___/ __ \/ ___/ _ \/ ___/ ___/
	//	 / ____/ /  /  __/ /_/ / /  / /_/ / /__/  __(__  |__  )
	//	/_/   /_/   \___/ .___/_/   \____/\___/\___/____/____/
	//	               /_/
	// ==================================================================================================================================

	_this.preprocess = function()
	{
		_this.tokenizer = ast.tokenizer;

		var currFunction = null;
		var currClass = null;
		var currState = null;
		var currDot = [];
		var dic={};

		trace("+ Processing AST ...");

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

			case jsdef.STATE:
				currState = node;
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

				_this.SET_METADATA(node, "identifiers_list", _this.reduceProps(node));
				_this.SET_METADATA(node, "identifier_first", node.identifiers_list[0].ast);
				_this.SET_METADATA(node, "identifier_last", node.identifiers_list[node.identifiers_list.length-1].ast);

				var values = [];
				for(var i=0,L=node.identifiers_list.length;i<L;i++)	values.push(node.identifiers_list[i].value);
				node.value = values.join(".");
				for(var i=node.identifiers_list.length;i--;)
				{
					if(node.identifiers_list[i].value!="@@INDEX@@")
					{
						_this.SET_METADATA(node, "identifier_last", node.identifiers_list[i].ast);
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
					// Object Node properties that we do not want to descend
					case "constructorNode":
					case "destructorNode":
					case "identifier_first":
					case "identifier_last":
					case "identifiers_list":
					case "inClass":
					case "inDot":
					case "inFunction":
					case "overloadOf":
					case "overloads":
					case "params":
					case "parent":
					case "returnPaths":
					case "scope":
					case "tokenizer":
					case "jsdoc":
					case "interfaces":

					// Scallar Node properties that we do not want to descend
					case "__end":
					case "__fileLineOffset":
					case "__filePosOffset":
					case "__start":
					case "__visited":
					case "abstract":
					case "blockId":
					case "contextId":
					case "defaultIndex":
					case "end":
					case "extends":
					case "file":
					case "constructor":
					case "destructor":
					case "isLoop":
					case "length":
					case "line_end":
					case "line_start":
					case "name":
					case "nodeType":
					case "optional":
					case "path":
					case "postfix":
					case "private":
					case "protected":
					case "public":
					case "push":
					case "readOnly":
					case "returntype":
					case "scopeId":
					case "source":
					case "start":
					case "state":
					case "static":
					case "subtype":
					case "top":
					case "type":
					case "vartype":
					case "virtual":

						break;

					// Object Node properties we WANT to descend
					default:

						if(!isFinite(item) && (typeof node[item] == 'object'))
							dic[item]=true;

						if(typeof node[item] == 'object'  && node[item] && !node[item].__visited)
						{
							descend(node[item]);
							_this.SET_METADATA(node[item], "parent", node);
							nodes.push(node[item]);
						}
				}
			}
			nodes = null;

            // Enrich ast node with usefull data and delete its reference to tokenizer.
			node.nodeType = GLOBAL.narcissus.jsdefNames[node.type];
			node.source = _this.tokenizer.source.slice(node.start, node.end);
			node.line_start -= node.__fileLineOffset;
			node.line_end -= node.__fileLineOffset;
			node.start -= node.__filePosOffset;
			node.end -= node.__filePosOffset;

			// Non-enumerable node metadata
			_this.SET_METADATA(node, "inClass", currClass);
			_this.SET_METADATA(node, "inState", currState);
			_this.SET_METADATA(node, "inFunction", currFunction);
			_this.SET_METADATA(node, "inDot", currDot.length>0 && currDot[currDot.length-1].type==jsdef.DOT ? currDot[currDot.length-1] : null);
			_this.SET_METADATA(node, "inIndex", currDot.length>0 && currDot[currDot.length-1].type==jsdef.INDEX ? currDot[currDot.length-1] : null);
			_this.SET_METADATA(node, "inGroup", currDot.length>0 && currDot[currDot.length-1].type==jsdef.GROUP ? currDot[currDot.length-1] : null);
			_this.SET_METADATA(node, "inCall", currDot.length>0 && currDot[currDot.length-1].type==jsdef.CALL ? currDot[currDot.length-1] : null);

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

			case jsdef.STATE:
				currState=null;
				break;

			case jsdef.CLASS:
				currClass=null;
				break;

			case jsdef.FUNCTION:
				currFunction=null;
				break;
			}
		}

		descend(_this.ast);

		// Enable this code to detect Node object properties
		// added by parser that could be excluded in descend.

		var fields = [];
		for(item in dic)
			fields.push('case "' + item + '":');
		if(fields.length)
		{
			// Add those properties to switch above
			//trace(fields.sort().join("\n"));
		}

		trace("+ Generating Code ...");
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
	_this.NewScope = function(ast, force, type)
	{
		var scope = null;

		if(!type) type = ast.type;

		if(!force && _this.secondPass)
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
			scope.type			= type;
			scope.nodeType		= ast.nodeType;
			scope.isGlobal		= _this.scopesStack.length==0;
			scope.isClass		= type==jsdef.CLASS;
			scope.isMethod		= type==jsdef.FUNCTION;
			scope.isState		= type==jsdef.STATE;
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

		if(ast.inFunction && ast.inFunction.symbol)
			ast.inFunction.symbol.scopes.push(scope);

		return scope;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getNodeScope = function(node)
	{
		var p = node;
		while(p && !p.scope)
		{
			p=p.parent;
		}
		return (p ? p.scope : null);
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

	/*@@ LookupIdentifier @@*/

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
			if(ast.file.substr(ast.file.length-3)==".js" || _this.isInside(ast, null, "_prototype", true))
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
		var last_identifier = ast.identifiers_list[ast.identifiers_list.length-1].value;
		var symbol = null;

		// Start descending dot chain.
		for(var i=0; i<ast.identifiers_list.length;i++)
		{
			var vartype = null;
			var identifier = ast.identifiers_list[i].value;
			var nodeSymbol = _this.LookupIdentifier(scope, identifier, null, true);
			if(!nodeSymbol) break;
			if(i==ast.identifiers_list.length-1)
			{
				symbol = nodeSymbol;
				break;
			}
			else if(ast.identifiers_list[i+1].value=="@@INDEX@@")
			{
				if(!nodeSymbol.subtype)	nodeSymbol = _this.getClass(nodeSymbol.vartype);
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
		if(!symbol && scope.isClass && scope.ast && scope.ast.symbol && scope.ast.symbol.baseSymbol)
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
	_this.getBaseClass = function(vartype)
	{
		var cls = _this.getClass(vartype);
		if(cls && cls.baseSymbol) return cls.baseSymbol;
		return null;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getClassScope = function()
	{
		return _this.currClassName && _this.currClassName!="Global" ? _this.classes[_this.currClassName].scope : null;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isMember = function(name, cls)
	{
		var symbol = cls ? (cls.methods[name] || cls.vars[name]) : null;
		return (!symbol ? null : (cls.classId + (symbol.private ? ".__PRIVATE__" : (symbol.protected ? ".__PROTECTED__" : "") )));
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isBaseMember = function(name, cls, baseOnly)
	{
		var basePath = [];
		function __isBaseMember(base)
		{
			if(!base) return false;
			basePath.push(base.classId);
			var symbol = base.methods[name] || base.vars[name] || null;
			if(symbol)
			{
				if(symbol.private) basePath.push("__PRIVATE__");
				else if(symbol.protected) basePath.push("__PROTECTED__");
				return true;
			}
			else
			{
				return __isBaseMember(base.baseSymbol);
			}
		}
		return __isBaseMember(baseOnly ? cls.baseSymbol : cls) ? basePath.join(".") : null;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isDerivativeOf = function(derivateClassName, baseClassName)
	{
		var cls = _this.getClass(derivateClassName);
		for(i=0;i<cls.bases.length;i++)
			if(cls.bases[i].name==baseClassName)
				return true;
		return false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.baseClassDot = function(classSymbol, baseSymbol)
	{
		var basePath = [];
		function __getBase(base)
		{
			if(!base) return false;
			basePath.push(base.classId);
			if(base==baseSymbol) return true;
			return __getBase(base.baseSymbol);
		}
		return __getBase(classSymbol) ? basePath.join(".") : null;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getCallIdentifier = function(ast)
	{
		if(ast[0].type==jsdef.DOT)
			return ast[0].identifier_last;

		if(ast[0].type==jsdef.IDENTIFIER)
			return ast[0];
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getCallList = function(ast, index)
	{
		var list = null;
		if(ast.inCall) list = ast.inCall[1];
		if(ast.inDot) list = _this.isInside(ast, jsdef.CALL)[1];
		if(list && list.type==jsdef.LIST) return list;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getCallListParam = function(ast, index)
	{
		var list = _this.getCallList(ast);
		if(list) return list[index];
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
		if(_this.lineNumbers && _this.line_start != ast.line_start)
		{
			_this.line_start != -1 && out.push("\n");
			out.push("\/\/@line " + ast.line_start + "\n");
			_this.line_start = ast.line_start;
		}

		switch(ast.type)
		{
		// ==================================================================================================================================
		//	    _   _____    __  ______________ ____  ___   ____________
		//	   / | / /   |  /  |/  / ____/ ___// __ \/   | / ____/ ____/
		//	  /  |/ / /| | / /|_/ / __/  \__ \/ /_/ / /| |/ /   / __/
		//	 / /|  / ___ |/ /  / / /___ ___/ / ____/ ___ / /___/ /___
		//	/_/ |_/_/  |_/_/  /_/_____//____/_/   /_/  |_\____/_____/
		//
		// ==================================================================================================================================
		/*@@ NAMESPACE @@*/

		case jsdef.NAMESPACE:
			break;

		// ==================================================================================================================================
		//	   _____ __                  __
		//	  / ___// /________  _______/ /_
		//	  \__ \/ __/ ___/ / / / ___/ __/
		//	 ___/ / /_/ /  / /_/ / /__/ /_
		//	/____/\__/_/   \__,_/\___/\__/
		//
		// ==================================================================================================================================
		/*@@ STRUCT @@*/

		case jsdef.STRUCT:
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";
			var scope = _this.NewScope(ast);
			ast.fileClasses = _this.fileClasses;

			out.push("var " + ast.name + " = {");

			// Struct Symbol
			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId				= (++_this.symbolId);
				classSymbol.name					= ast.name;
				classSymbol.vartype					= ast.name;
				classSymbol.subtype					= null;
				classSymbol.classId					= classId;
				classSymbol.base					= null;
				classSymbol.baseSymbol				= null;
				classSymbol.bases 					= [];
				classSymbol.derivatives				= {};
				classSymbol.interfaces				= []
				classSymbol.events					= {};
				classSymbol.__event_bindings		= [];
				classSymbol.__event_unbindings		= [];
				classSymbol.__event_fire			= [];
				classSymbol.type					= jsdef.CLASS;
				classSymbol.nodeType				= "STRUCT";
				classSymbol.extern					= (ast.file=="externs.jspp");
				classSymbol.control					= false;
				classSymbol._prototype				= false;
				classSymbol.enum					= false;
				classSymbol.state					= false;
				classSymbol.callback				= false;
				classSymbol.interface				= false;
				classSymbol.struct					= true;
				classSymbol.ast						= ast;
				classSymbol.scope					= scope;
				classSymbol.vartypes				= scope.vartypes;
				classSymbol.file					= ast.file;
				classSymbol.path					= ast.path;
				classSymbol.start					= ast.start;
				classSymbol.end						= ast.end;
				classSymbol.line_start				= ast.line_start;
				classSymbol.line_end				= ast.line_end;
				classSymbol.scopeId					= scope.scopeId;
				classSymbol.vars					= scope.vars;
				classSymbol.methods	 				= scope.methods;
				classSymbol.runtime					= ast.name;
				classSymbol.icon					= _this.CODE_SYMBOLS_ENUM.SYMBOL_OBJECT;
				classSymbol.EXPORT_NATIVE 			= ast.EXPORT_NATIVE;
				classSymbol.EXPORT_WEB 				= ast.EXPORT_WEB;
			}

			// Save symbol
			ast.symbol = classSymbol;
			_this.classes[ast.name] = classSymbol;
			_this.scopesStack[0].vars[classSymbol.name] = classSymbol;

			// Set members
			var items = [];
			for(item in ast)
			{
				if(!isFinite(item)) break;
				ast[item].pointer = _this.isPointer(ast[item].vartype);

				// Var Symbol
				var varSymbol = new VarSymbol();
				{
					varSymbol.symbolId		= (++_this.symbolId);
					varSymbol.name			= ast[item].name;
					varSymbol.value			= _this.getDefaultVartypeValue(ast[item].vartype);
					varSymbol.type			= ast[item].type;
					varSymbol.nodeType		= ast[item].nodeType;
					varSymbol.classId		= classId;
					varSymbol.extern		= (ast.file=="externs.jspp");
					varSymbol.public		= true;
					varSymbol.private		= false;
					varSymbol.protected		= false;
					varSymbol.static		= false;
					varSymbol.optional		= false;
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
					varSymbol.delegate		= false;
					varSymbol.event			= false;
					varSymbol.constant		= false;
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
					varSymbol.pointer		= ast[item].pointer;
					varSymbol.icon 			= _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;
					varSymbol.modifier 		= "public";
					varSymbol.runtime 		= classId + "." + ast[item].name;
				}

	            if(ast[item].vartype == "Array" && !ast[item].subtype)
	            	_this.NewError("Untyped Array " + ast[item].name, ast[item]);

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
				_this.record_vartype_use(ast, varSymbol, classSymbol.scope, _this.INCLUDE_IN_HPP);

				// Generate
				items.push(ast[item].name + ": null");
			}

			out.push(items.join(",") + "};");

			_this.ExitScope();
			_this.addCodeToClassFile(ast.path, out.join("\n"));
			break;

		// ==================================================================================================================================
		//	   ________
		//	  / ____/ /___ ___________
		//	 / /   / / __ `/ ___/ ___/
		//	/ /___/ / /_/ (__  |__  )
		//	\____/_/\__,_/____/____/
		//
		//
		// Open Readme.txt to understand how classes are implemented.
		//
		// ==================================================================================================================================
		/*@@ CLASS @@*/

		case jsdef.INTERFACE:
		case jsdef.CLASS:

			_this.currClassName = ast.name;

		 	// Class must know its includes
		 	ast.fileClasses = _this.fileClasses;

			var constructor = null;
			var destructor = null;
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";
			var baseClass = ast.extends ? ast.extends : undefined;
			var baseClassSymbol = _this.getClass(baseClass);
			var baseClassId = baseClassSymbol ? baseClassSymbol.ast.symbol.classId : null;
			var baseConstructor = baseClassSymbol ? baseClassSymbol.methods["Constructor"] : null;
			var isGlobalClass = (ast.name=="Global");
			var scope = ast.scope = (isGlobalClass ? _this.scopesStack[0] : _this.NewScope(ast));
			var staticMembers = {};

			// Sanity check: is this class reimplemented?
			if(!_this.secondPass)
			{
				var redef = _this.getClass(ast.name);
				if(redef)
				{
					_this.NewError("Invalid class redefinition: " + ast.name, redef.ast);
					_this.NewError("Invalid class redefinition: " + ast.name, ast);
					return;
				}
			}

			// Sanity check: is this class inheriting from itself?
			if(baseClass && baseClass==ast.name)
			{
				_this.NewError("Illegal base class: " + baseClass, ast);
				return;
			}

			// Sanity check: base class exists?
			if(_this.secondPass && baseClass && !baseClassSymbol)
			{
				_this.NewError("Base class not found: " + baseClass, ast);
				return;
			}

			// Class Symbol
			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId				= (++_this.symbolId);
				classSymbol.name					= ast.name;
				classSymbol.vartype					= ast.name;
				classSymbol.subtype					= ast.subtype;
				classSymbol.classId					= classId;
				classSymbol.base					= baseClass;
				classSymbol.baseSymbol				= baseClassSymbol;
				classSymbol.bases 					= [baseClassSymbol];//Must be filled with all the base classes
				classSymbol.derivatives				= {};
				classSymbol.interfaces				= ast.interfaces;
				classSymbol.events					= {};
				classSymbol.__event_descriptors		= [];
				classSymbol.__event_bindings		= [];
				classSymbol.__event_unbindings		= [];
				classSymbol.__event_fire			= [];
				classSymbol.type					= jsdef.CLASS;
				classSymbol.nodeType				= "CLASS";
				classSymbol.extern					= (ast.file=="externs.jspp");
				classSymbol.control					= ast.control;
				classSymbol._prototype				= false;
				classSymbol.enum					= false;
				classSymbol.state					= ast.state;
				classSymbol.callback				= false;
				classSymbol.interface				= ast.type==jsdef.INTERFACE;
				classSymbol.ast						= ast;
				classSymbol.scope					= scope;
				classSymbol.vartypes				= scope.vartypes;
				classSymbol.file					= ast.file;
				classSymbol.path					= ast.path;
				classSymbol.start					= ast.start;
				classSymbol.end						= ast.end;
				classSymbol.line_start				= ast.line_start;
				classSymbol.line_end				= ast.line_end;
				classSymbol.scopeId					= scope.scopeId;
				classSymbol.vars					= scope.vars;
				classSymbol.methods	 				= scope.methods;
				classSymbol.runtime					= ast.name;
				classSymbol.icon					= ast.type==jsdef.INTERFACE ? _this.CODE_SYMBOLS_ENUM.SYMBOL_INTERFACE : _this.CODE_SYMBOLS_ENUM.SYMBOL_CLASS;
				classSymbol.EXPORT_NATIVE 			= ast.EXPORT_NATIVE;
				classSymbol.EXPORT_WEB 				= ast.EXPORT_WEB;
			}

			// Keep a list of derivative classes to handle cyclic-references in C++ (error: base class has incomplete type)
			if(baseClassSymbol)
			{
				baseClassSymbol.derivatives[classSymbol.name] = classSymbol;
				_this.derivatives[baseClassSymbol.name] = true;
			}

			// Save symbol
			ast.symbol = classSymbol;
			_this.classes[ast.name] = classSymbol;
			_this.scopesStack[0].vars[classSymbol.name] = classSymbol;

			// Record vartype usage in class level (used to check #includes)
			if(baseClass)
				_this.record_vartype_use(ast, {vartype:baseClass, subtype:null}, scope, _this.INCLUDE_IN_HPP);

			// Record interfaces
			for(i=0;i<classSymbol.interfaces.length;i++)
				_this.record_vartype_use(ast, {vartype:classSymbol.interfaces[i]}, classSymbol.scope, _this.INCLUDE_IN_HPP);

			if(_this.secondPass)
			{
				if(baseClass && !baseClassSymbol)
					_this.NewError("Base class not found: " + baseClass, ast);

				// Collect all base classes (in reverse order from bottom to top)
				var base = classSymbol;

				classSymbol.bases=[];
				while(((base=base.baseSymbol)!=null))
				{
					classSymbol.bases.push(base);
				}
				classSymbol.bases = classSymbol.bases.reverse();
			}

			// Generate constructor arguments list for this class
			var thisConstructorArguments = [];
			if(ast.constructorNode && ast.constructorNode.params.length)
			{
				for(i=0;i<ast.constructorNode.params.length;i++)
					thisConstructorArguments.push(classId + "$" + ast.constructorNode.params[i] + "__");
			}
			thisConstructorArguments = thisConstructorArguments.join(", ");

			// Generate the outer function
			out.push("function " + ast.name + "(" + thisConstructorArguments + "){");
			out.push("var __BASE__ = null;");

			// Generate the inner function
			out.push("function __" + ast.name + "(" + thisConstructorArguments + "){");

			// Generate a __CLASS_<CLASSID>__ for keeping "this".
			// When this class becomes a prototype of another class,
			// then __CLASS_<CLASSID>__ will act as the base class.
			// Especially for virtual methods that we need to call
			// the original implementation using "super.<method>" we
			// will make this call using __CLASS_<CLASSID>__.<method>

			//out.push("var Class = this.Class = '" + ast.name + "';");
			out.push("var __PDEFINE__ = Object.defineProperty;");
			out.push("var __NOENUM__ = {enumerable:false};");
			out.push("var " + classId + " = this." + classId + " = this;");

			// "this" is no more - we take control of "this" and
			// we NEVER generate "this" inside member body code.
			// "this" is used only for declaring members.
			// The inheritance mechanism sets top-level "this" to
			// all base classes. Enable comment below to trace
			// how this "changes" at runtime.

			out.push("var __THIS__ = this;");
			out.push("this.toString = function(){return '" + ast.name + "'};");
			out.push("__PDEFINE__(this,'__THIS__', {enumerable:false, get: function(){return __THIS__;}, set:function(v){__THIS__=v;}});");
			//out.push("__PDEFINE__(this,'__THIS__', {enumerable:false, get: function(){return __THIS__;}, set:function(v){trace('chaning \"this\" of base class [" + classSymbol.name + "] to top-level class [' + v.Class + ']' );__THIS__=v;}});");

			// Define the bank for the virtual public and private methods.
			// You are not expected to understand how this works but the
			// main idea is that we keep a copy of the original methods
			// in __VIRTUAL__ so that we can call them when needed.
			// Hava a look in jsdef.FUNCTION and jsdef.IDENTIFIER for
			// more information about virtual methods.

			out.push("var __VIRTUAL__ = this.__VIRTUAL__ = { __PROTECTED__:{} };");

			// For proper implementation of Private and Protected members, we use two
			// banks, the __PRIVATE__ and __PROTECTED__ respectively. All private or
			// public entities such as vars, consts, enums, functions, states, properties,
			// are saved in those two banks. Public entities are saved directly on the
			// class and on a var (var x = this.x = <public>).
			// Low-level classes that do not inherit from anything need to define the
			// __PRIVATE__ and __PROTECTED__ banks. Be carefull NOT TO REDEFINE the
			// banks if your class inherits from another class.

            if(!baseClassSymbol)
            {
	            out.push("var __PRIVATE__ = this.__PRIVATE__ = {};");
	            out.push("var __PROTECTED__ = this.__PROTECTED__ = {};");
				out.push("__PDEFINE__(this,'__PRIVATE__',__NOENUM__);");
				out.push("__PDEFINE__(this,'__PROTECTED__',__NOENUM__);");
            }
            else
            {
	            out.push("var __PRIVATE__ = this.__PRIVATE__;");
	            out.push("var __PROTECTED__ = this.__PROTECTED__;");

	            for(i=0;i<classSymbol.bases.length;i++)
	            {
	            	// Special case when base is an ECMA or native Class (eg. Array)
	            	if(classSymbol.bases[i].extern)
	            	{
	            		out.push("var " + classSymbol.bases[i].classId + " = this;");
	            	}
					// Standard CocoScript case when a Class inherits from a CocoScript class
	            	else
	            	{
	            		var baseAccessPath = _this.baseClassDot(classSymbol,classSymbol.bases[i]);
	            		out.push("var " + classSymbol.bases[i].classId + " = this." + classSymbol.bases[i].classId + " = " + baseAccessPath + ";");

	            		// Replace __THIS__ of the base class
	            		out.push(baseAccessPath + ".__THIS__ = " + classSymbol.classId + ";");

	            	}
	            }
            }

			/////////////////////////////////////////////////////////////////////////////////
			// Overloads can cause problems if they are positioned in source code below any
			// functions that use/call them. Therefore we mush perform an intermediate pass
			// between the first pass and the second pass if overloads are detected in the
			// class in order to fully-process overloads and derive their symbols.
			/////////////////////////////////////////////////////////////////////////////////
			if(_this.secondPass && ast.requires_third_pass)
			{
				_this.no_errors++; // Supress any errors
				for(item in ast.body)
				{
					if(!isFinite(item)) break;
					member = ast.body[item];
					if(member.type!=jsdef.FUNCTION) continue;
					if(member.isConstructor || member.isDestructor) continue;
					generate(member); // <- generating functions will process overloads
				}
				_this.no_errors--; // Restore errors generation
			}

			/////////////////////////////////////////////////////////////////////////////////
			// Generate Class Body
			/////////////////////////////////////////////////////////////////////////////////

			var out_constants 		= [];
			var out_enums 			= [];
			var out_vars			= [];
			var out_functions		= [];
			var out_properties 		= [];
			var out_states 			= [];

			for(item in ast.body)
			{
				if(!isFinite(item)) break;

				member = ast.body[item];

				switch(member.type)
				{
					//------------------------------------------
					case jsdef.CONST:
					{
						if(member.static)
							staticMembers[member.nodeId] = generate(member);
						else
							out_constants.push(generate(member));
					}
					break;

					//------------------------------------------
					case jsdef.ENUM:
					{
						out_enums.push(generate(member));
					}
					break;

					//------------------------------------------
					case jsdef.VAR:
					{
						if(member.static)
							staticMembers[member.nodeId] = generate(member);
						else
							out_vars.push(generate(member));
					}
					break;

					//------------------------------------------
					case jsdef.EVENT:
					{
						out_vars.push(generate(member));
					}
					break;

					//------------------------------------------
					case jsdef.FUNCTION:
					{
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
						if(member.static)
							staticMembers[member.nodeId] = generate(member);
						else
							out_functions.push(generate(member));
					}
					break;

					//------------------------------------------
					case jsdef.PROPERTY:
					{
						if(member.static)
							staticMembers[member.nodeId] = generate(member);
						else
							out_properties.push(generate(member));
					}
					break;

					//------------------------------------------
					case jsdef.STATE:
					{
						out_states.push(generate(member));
					}
					break;

				} //switch

			} //for


			/////////////////////////////////////////////////////////////////////////////////
			// Process Delegates
			/////////////////////////////////////////////////////////////////////////////////
			// Delegates are objects defined as vars inside a class thet extend class members.
			// A class acts as a wrapper for delegate objects and at compile-time we need to
			// generate wrapper methods for the delegated members.

			if(_this.secondPass)
			{
				for(item in classSymbol.vars)
				{
					if(!classSymbol.vars[item].delegate) continue;

					// Get delegated object variable
					var delegator = classSymbol.vars[item];

					// Create a new method scope
					var methodScope = _this.NewScope(delegator, true);

					// Get delegated object variable class symbol
					var cls = _this.getClass(delegator.vartype);

					// Loop on public methods
					for(member in cls.methods)
					{
						var delegatorFunctionSymbol = cls.methods[member];
						if(!delegatorFunctionSymbol.public) continue;
						if(delegatorFunctionSymbol.static) continue;
						if(delegatorFunctionSymbol.abstract) continue;

						var fnName = delegatorFunctionSymbol.name;
						var paramsList = delegatorFunctionSymbol.__untypedParamsList;

						// Create the wrapper call
						var wrapper = "";
		  				     if(delegator.public)			wrapper = "this." + fnName + " = function" + paramsList;
		  				else if(delegator.private)			wrapper = "this.__PRIVATE__." + fnName + " = function" + paramsList;
		  				else if(delegator.protected)		wrapper = "this.__PROTECTED__." + fnName + " = function" + paramsList;
						wrapper += "{return " + delegator.runtime + "." + fnName + paramsList + ";}";

						// Insert wrapper before any other function (so that it can be overwrittern)
						out_functions.insert(0,wrapper);

						// Extend Code Symbols
						var functionSymbol = new FunctionSymbol();
						{
							for(var key in delegatorFunctionSymbol)
								functionSymbol[key] = delegatorFunctionSymbol[key];

							functionSymbol.delegated 		= delegatorFunctionSymbol;
							functionSymbol.symbolId			= (++_this.symbolId);
							functionSymbol.name				= delegatorFunctionSymbol.name;
							functionSymbol.type				= delegatorFunctionSymbol.type;
							functionSymbol.nodeType			= delegatorFunctionSymbol.nodeType;
							functionSymbol.className		= classSymbol.name;
							functionSymbol.classId			= classSymbol.classId;
							functionSymbol.restArguments	= delegatorFunctionSymbol.restArguments;
							functionSymbol.public			= delegator.public;
							functionSymbol.private			= delegator.private;
							functionSymbol.protected		= delegator.protected;
							functionSymbol.static			= false;
							functionSymbol.optional			= false;
							functionSymbol.virtual			= delegator.virtual;
							functionSymbol.abstract			= false;
							functionSymbol.ast				= delegatorFunctionSymbol.ast;
							functionSymbol.scope			= methodScope;
							functionSymbol.baseSymbol		= delegatorFunctionSymbol.baseSymbol;
							functionSymbol.file				= delegator.file;
							functionSymbol.path				= delegator.path;
							functionSymbol.start			= delegator.start;
							functionSymbol.end				= delegator.end;
							functionSymbol.line_start		= delegator.line_start;
							functionSymbol.line_end			= delegator.line_end;
							functionSymbol.scopeId			= methodScope.scopeId;
							functionSymbol.vartype			= delegatorFunctionSymbol.vartype;
							functionSymbol.subtype			= delegatorFunctionSymbol.subtype;
							functionSymbol.paramsList		= delegatorFunctionSymbol.paramsList;
							functionSymbol.arguments		= delegatorFunctionSymbol.arguments;

							if(functionSymbol.public)			functionSymbol.modifier = "public";
							else if(functionSymbol.private)		functionSymbol.modifier = "private";
							else if(functionSymbol.protected)	functionSymbol.modifier = "protected";
							else								functionSymbol.modifier = "";

							functionSymbol.runtime_delegated = delegator.runtime;
							functionSymbol.runtime = delegator.runtime + "." + fnName;
						}

						// Finally save the functionSymbol in the class
						classSymbol.methods[fnName] = functionSymbol;
					}

					_this.ExitScope();
				}
			}

			/////////////////////////////////////////////////////////////////////////////////
			// Synthesize class body, keep the entities organized.
			/////////////////////////////////////////////////////////////////////////////////
			out.push( out_constants.join("\n") 	);
			out.push( out_enums.join("\n") 		);
			out.push( out_vars.join("\n") 		);
			out.push( out_functions.join("\n") 	);
			out.push( out_properties.join("\n") );
			out.push( out_states.join("\n") 	);

			/////////////////////////////////////////////////////////////////////////////////
			// Generate Destructor
			/////////////////////////////////////////////////////////////////////////////////
			if(destructor)
				out.push(generate(destructor));

			/////////////////////////////////////////////////////////////////////////////////
			// Generate Constructor
			/////////////////////////////////////////////////////////////////////////////////
			out.push(constructor ? generate(constructor) : "this.Constructor=function(){};");
			out.push("__PDEFINE__(this,'Constructor',__NOENUM__);");
			out.push("this.Constructor(" + thisConstructorArguments + ");");

            // Close inner function
			out.push("return this;}");

			// Close outer function
			if(baseClass)
			{
				if(baseConstructor && _this.secondPass)
				{
					var baseConstructorArguments = [];

					// Generate base class constructor arguments call list
					// eg. public function Constructor(arg1:String) : BaseClass(arg1, "arg2")

					if(baseConstructor.paramsList.length && !baseConstructor.paramsList[0].optional && !ast.base_init)
					{
						_this.NewError("Base constructor arguments missmatch: " + baseClass, ast);
					}

					if(ast.base_init)
					{
						_this.checkFunctionSignature(ast.base_init, baseConstructor);

						_this.lineNumbers = false;
						for(var item in ast.base_init[1])
						{
							if(!isFinite(item)) break;
							var arg = ast.base_init[1][item];
							if(arg.type==jsdef.IDENTIFIER)
							{
								baseConstructorArguments.push(classId + "$" + arg.value + "__");
							}
							else
							{
								var gen = _this.generate(arg);
								baseConstructorArguments.push(gen);
							}
						}
						_this.lineNumbers = true;
						baseConstructorArguments = baseConstructorArguments.join(", ");
					}
					else
					{
						baseConstructorArguments = thisConstructorArguments;
					}
				}
				out.push("__" + ast.name + ".prototype = new " + baseClass + "(" + baseConstructorArguments + ");");
			}
			out.push("__" + ast.name + ".prototype.constructor = __" + ast.name + ";");
			out.push("return new __" + ast.name + "(" + thisConstructorArguments + ");}");

			/////////////////////////////////////////////////////////////////////////////////
			// Generate Static class members on outer Class function
			/////////////////////////////////////////////////////////////////////////////////

			// We will use __PRIVATE__ and __PROTECTED__ to store static members on
			// outer class function, like we did with instance members on the inner
			// class function. This was most of the rest code will simply work for
			// private and protected entities.

			out.push(ast.name + ".__PRIVATE__ = {};");
			out.push(ast.name + ".__PROTECTED__ = {};");

			// We loop on all bases (in reverse order) and generate
			// their static members in this class scope.

			if(_this.secondPass && classSymbol.bases.length>0)
			{
				for(i=0;i<classSymbol.bases.length;i++)
				{
					var base = classSymbol.bases[i];

					if(base.extern)
						continue;

					// Vars
					for(item in base.vars)
					{
						var member = base.vars[item];
						if(!member.static || member.type==jsdef.STATE) continue;
						switch(member.type)
						{
							case jsdef.PROPERTY:
								staticMembers[member.ast.nodeId] = generate(member.ast);
								break;

							case jsdef.IDENTIFIER: // of jsdef.VAR
								staticMembers[member.ast.nodeId] = generate(member.ast.parent);
								break;
						}
					}

					// Methods
					for(item in base.methods)
					{
						var member = base.methods[item];
						if(!member.static) continue;
						staticMembers[member.ast.nodeId] = generate(member.ast);
					}
				}
			}

			// Finally add our own static members
			for(item in staticMembers)
			{
				out.push( staticMembers[item] );
			}

			/////////////////////////////////////////////////////////////////////////////////
			// Class-specific Type Checks
			/////////////////////////////////////////////////////////////////////////////////
			if(_this.secondPass)
			{
				// Check that abstract methods are implemented
				if(baseClass && baseClassSymbol && !baseClassSymbol.interface)
				{
					for(item in baseClassSymbol.methods)
					{
						var baseMethodSymbol = baseClassSymbol.methods[item];
						if(baseMethodSymbol.abstract && !classSymbol.methods.hasOwnProperty(baseMethodSymbol.name))
							_this.NewError("Missing abstract method: " + baseMethodSymbol.name, ast);
					}
				}

				// ================================================================
				// If this class has object members we need a Destructor
				// ================================================================
				var hasObjectMembers = false;
				for(item in classSymbol.vars)
				{
					if(classSymbol.vars[item].pointer)
					{
						hasObjectMembers = true;
						break;
					}
				}
				if(hasObjectMembers && !destructor && !classSymbol.extern)
					_this.NewError("Missing Destructor: " + ast.name, ast);

				// ================================================================
				// Check interface
				// ================================================================
				if(ast.type==jsdef.INTERFACE)
				{
					for(item in classSymbol.methods)
					{
						var method = classSymbol.methods[item];
						if(!method.public || method.static)
							_this.NewError("Invalid interface method modifiers: " + method.name, method.ast);
					}

					for(item in classSymbol.vars)
					{
						_this.NewError("Invalid interface member: " + item, classSymbol.vars[item].ast);
					}
				}

				// ================================================================
				// Check interface implementation
				// ================================================================
				if(classSymbol.interfaces.length)
				{
					function checkInterface(interfaceName)
					{
						// Get interface
						var interfaceClass = _this.getClass(interfaceName);
						if(!interfaceClass) _this.NewError("Interface not found: " + interfaceName, ast);

						// Interface inheritance: check base interfaces
						if(interfaceClass.baseSymbol)
							checkInterface(interfaceClass.baseSymbol.name);

						// Check if the class implements all interface methods
						for(item in interfaceClass.methods)
						{
							var interfaceMethod = interfaceClass.methods[item];
							if(!__exists(classSymbol.methods, interfaceMethod.name))
							{
								_this.NewError("Interface method not found: " + interfaceName + "::" + interfaceMethod.name, ast);
							}
							else
							{
								var localMethod = classSymbol.methods[interfaceMethod.name];
								if(localMethod.__signature!=interfaceMethod.__signature)
									_this.NewError("Invalid interface method signature: " + interfaceName + "::" + interfaceMethod.name, localMethod.ast);
							}
						}
					}

					// Check interfaces one by one
					for(i=0;i<classSymbol.interfaces.length;i++)
					{
						checkInterface(classSymbol.interfaces[i]);
					}
				}

				// ================================================================
				// Check Events
				// ================================================================
				if(_this.secondPass)
				{
					var list = [].concat(classSymbol.__event_bindings).concat(classSymbol.__event_unbindings);
					for(i=0;i<list.length;i++)
					{
						var event_ast = list[i];
						var eventSourceClassName = event_ast.parent.identifier_first.symbol.vartype;
						var eventSourceClassSymbol = _this.getClass(eventSourceClassName);
						var eventClassName = _this.getTypeName(_this.getCallListParam(event_ast,0));
						var eventClassSymbol = _this.getClass(eventClassName);
						var eventHandlerFunctionSymbol = event_ast.inDot.parent[1][1].symbol;
						var event_handler_uid = "__EH" + _this.eventId + "_" + classSymbol.name + "_" + eventHandlerFunctionSymbol.name + "_L" + event_ast.line_start + "__";

						// Search event bindings for same addEventListener
						if(event_ast.value==_this.ADD_EVENT || event_ast.value==_this.REMOVE_EVENT)
						{
							for(j=0;j<classSymbol.__event_bindings.length;j++)
							{
								var eb = classSymbol.__event_bindings[j];
								if(eb==event_ast) continue;
								if(!eb.__event_descriptor) continue;
								var ed = eb.__event_descriptor;
								if(ed.event_source==eventSourceClassSymbol &&
								   ed.event_symbol==eventClassSymbol &&
								   ed.event_handler==eventHandlerFunctionSymbol)
								{
									ed.uid += "L" + event_ast.line_start + "__";
									ed.uid = ed.uid.replace(/__L/g, "_L");
									event_handler_uid = ed.event_handler_uid;
									event_ast.__event_descriptor = ed;
									if(!ed.event_source)	ed.event_source		= eventSourceClassSymbol;
									if(!ed.event_symbol)	ed.event_symbol		= eventClassSymbol;
									if(!ed.event_listener)	ed.event_listener	= classSymbol;
									if(!ed.event_handler)	ed.event_handler	= eventHandlerFunctionSymbol;
									break;
								}
							}
						}

						if(!eventClassSymbol)
						{
							_this.NewError("Event class " + eventName + " not found", event_ast);
							continue;
						}

						if(!event_ast.__event_descriptor)
						{
							event_ast.__event_descriptor =
							{
								id					: _this.eventId++,
								uid					: event_handler_uid,
								event_source		: eventSourceClassSymbol,
								event_symbol		: eventClassSymbol,
								event_listener		: classSymbol,
								event_handler		: eventHandlerFunctionSymbol,
								type				: event_ast.value
							};
						}
					}

					// Check dispatchEvent that matches event descriptor
					for(i=0;i<classSymbol.__event_fire.length;i++)
					{
						var event_ast = classSymbol.__event_fire[i];
						var eventSourceClassName = classSymbol.name;
						var eventSourceClassSymbol = classSymbol;
						var eventClassName = _this.getTypeName(_this.getCallListParam(event_ast,0));
						var eventClassSymbol = _this.getClass(eventClassName);
						var list = _this.getCallList(event_ast);

						if(!eventClassSymbol)
						{
							_this.NewError("Event class not found", event_ast);
							continue;
						}

						event_ast.__event_descriptor =
						{
							id					: _this.eventId++,
							uid					: null,
							event_source		: eventSourceClassSymbol,
							event_symbol		: eventClassSymbol,
							event_listener		: classSymbol,
							event_handler		: null,
							type				: event_ast.value
						};

						j=0;
						for(item in eventClassSymbol.vars)
						{
							var type1 = eventClassSymbol.vars[item].vartype;
							var type2 = _this.getTypeName(list[j+1]);
							_this.typeCheck(event_ast, type1, type2, "Event handler argument type mismatch: "+type1+" and "+type2 + " at " + list[j+1].source);
							j++;
						}
					}
				}
			}

			/////////////////////////////////////////////////////////////////////////////////
            // Done!
			/////////////////////////////////////////////////////////////////////////////////
			_this.currClassName = null;

			if(!isGlobalClass)
			{
				_this.ExitScope();

				if(ast.type!=jsdef.INTERFACE)
					_this.addCodeToClassFile(ast.path, out.join("\n"));
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
		/*@@ FUNCTION @@*/

		case jsdef.FUNCTION:

			ast.pointer = _this.isPointer(ast.returntype);

			var methodScope = ast.scope = _this.NewScope(ast);
			var parentScope = methodScope.parentScope;	// Could be State, Property or Class scope
			var classScope = _this.getClassScope();		// Class scope
			var classSymbol	=  classScope ? classScope.ast.symbol : null;
			var className = classScope ? classScope.ast.name : null;
			var classId = classScope ? classScope.ast.symbol.classId : null;
			var isGlobal = !classScope && parentScope.isGlobal;
			var isAnonymous = (ast.name==null || ast.name.length==0);
			var fnName = (ast.name ? ast.name : "");
			var baseMethodSymbol = null;

			// Add an XML comment to indicate function section in debug symbols XML
			if(_this.currClassName && (!classSymbol || (classSymbol && !classSymbol.ast.requires_third_pass)))
				_this.debugSymbolsTable.push("<!-- " + className + " :: " + fnName + " -->\n");

            // Check for function overloading
			if(!isAnonymous && __exists(parentScope.methods, fnName))
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

					if(fn_ast.overloads==null)
					{
						classSymbol.ast.requires_third_pass=true; // Indicates we will need a 3rd pass
						fn_ast.overload_name = fnName;
						fn_ast.overloads = [];
					}

					fn_ast.overloads.push(ast);
					ast.overloadOf = fn_ast;
					fnName += "$" + fn_ast.overloads.length;
					ast.overload_name = fnName;
				}
				else if(fn_ast.overloads)
				{
					fnName = ast.symbol.name;
				}
			}

			// Link method symbol with base class method symbol for speed.
			if(parentScope.isClass && parentScope.ast.symbol.baseSymbol)
			{
				baseMethodSymbol = _this.LookupIdentifier(parentScope.ast.symbol.baseSymbol.scope, fnName, ast, true);
			}

			// Function Symbol
			var functionSymbol = new FunctionSymbol();
			{
				functionSymbol.symbolId				= (++_this.symbolId);
				functionSymbol.name					= fnName;
				functionSymbol.type					= ast.type;
				functionSymbol.nodeType				= "FUNCTION";
				functionSymbol.className			= parentScope ? className : null;
				functionSymbol.classId				= classScope ? classId : null;
				functionSymbol.extern				= (ast.file=="externs.jspp");
				functionSymbol.restArguments		= ast.restArguments;
				functionSymbol.public				= ast.public==true;
				functionSymbol.private				= ast.private==true;
				functionSymbol.protected			= ast.protected==true;
				functionSymbol.static				= ast.static==true;
				functionSymbol.optional				= false;
				functionSymbol.virtual				= ast.virtual==true || fnName=="Destructor" || (classSymbol && classSymbol.interface);
				functionSymbol.abstract				= ast.abstract==true || (classSymbol && classSymbol.interface);
				functionSymbol.ast					= ast;
				functionSymbol.scope				= methodScope;
				functionSymbol.scopes 				= [methodScope];
				functionSymbol.baseSymbol			= baseMethodSymbol;
				functionSymbol.file					= ast.file;
				functionSymbol.path					= ast.path;
				functionSymbol.start				= ast.start;
				functionSymbol.end					= ast.end;
				functionSymbol.line_start			= ast.line_start;
				functionSymbol.line_end				= ast.line_end;
				functionSymbol.scopeId				= methodScope.scopeId;
				functionSymbol.vartype				= ast.returntype;
				functionSymbol.subtype				= ast.subtype ? ast.subtype : _this.getSubType(ast.returntype);
				functionSymbol.paramsList			= ast.paramsList;
				functionSymbol.overloads			= ast.overloads;
				functionSymbol.arguments			= {};
				functionSymbol.description			= ast.jsdoc ? ast.jsdoc.descr : (className ? fnName + " is member function of class " + className : null);
				functionSymbol.icon 				= _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FUNCTION;

				if(functionSymbol.public)			functionSymbol.modifier = "public";
				else if(functionSymbol.private)		functionSymbol.modifier = "private";
				else if(functionSymbol.protected)	functionSymbol.modifier = "protected";
				else								functionSymbol.modifier = "";

				if(ast.private)						functionSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FUNCTION;
				else if(ast.protected)				functionSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FUNCTION;
				if(fnName=="Constructor") 			functionSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTRUCTOR;

    			if(classId && ast.public)			functionSymbol.runtime = (_this.in_state ? "this" : classId) + "." + fnName;
				else if(classId && ast.private)		functionSymbol.runtime = (_this.in_state ? "this" : classId) + ".__PRIVATE__." + fnName;
				else if(classId && ast.protected)	functionSymbol.runtime = (_this.in_state ? "this" : classId) + ".__PROTECTED__." + fnName;
				else								functionSymbol.runtime = fnName;
			}

           	// Save symbol
			ast.symbol = functionSymbol;
			if(fnName)
				parentScope.methods[fnName] = functionSymbol;

			// Record vartype usage in class level (used to check #includes)
			if(classScope)
				_this.record_vartype_use(ast, functionSymbol, parentScope, _this.INCLUDE_IN_CPP);

			// Process the Arguments List
			var paramsList = "";
			var typedParamsList = "";
			for(var i=0; i<ast.paramsList.length; i++)
			{
				var param = ast.paramsList[i];
				param.pointer = _this.isPointer(param.vartype);

				paramsList += param.name;

				typedParamsList += (param.optional ? "optional " : "") +
								   param.name + ":" + param.vartype;

				if(i!=ast.paramsList.length-1)
				{
					paramsList +=", ";
					typedParamsList +=", ";
				}

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
					varSymbol.extern		= functionSymbol.extern;
					varSymbol.public		= false;
					varSymbol.private		= false;
					varSymbol.protected		= false;
					varSymbol.static		= false;
					varSymbol.optional		= param.optional;
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
					varSymbol.delegate		= false;
					varSymbol.event			= false;
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
					varSymbol.pointer		= param.pointer;
					varSymbol.runtime		= param.name;
					varSymbol.description	= ast.jsdoc && ast.jsdoc.args && ast.jsdoc.args[param.name] ? ast.jsdoc.args[param.name].vardescr : null;
					varSymbol.icon			=  _this.CODE_SYMBOLS_ENUM.SYMBOL_ARGUMENT;
					varSymbol.modifier		= "";
				}

				if(_this.secondPass && !param.vartype && classId)
				{
					_this.NewError("Missing argument type: " + varSymbol.name, param);
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
    			if(classScope)
    				_this.record_vartype_use(ast, varSymbol, parentScope, _this.INCLUDE_IN_HPP);
			}

			paramsList = "(" + paramsList + ")";
			typedParamsList = "(" + typedParamsList + ")";

			// =================================================================
			// Add an "arguments" variable in function scope
			// =================================================================
			var varSymbol = new VarSymbol();
			{
				varSymbol.symbolId		= (++_this.symbolId);
				varSymbol.name			= "arguments";
				varSymbol.value			= null;
				varSymbol.type			= jsdef.IDENTIFIER;
				varSymbol.nodeType		= "IDENTIFIER";
				varSymbol.classId		= null;
				varSymbol.extern		= functionSymbol.extern;
				varSymbol.public		= false;
				varSymbol.private		= false;
				varSymbol.protected		= false;
				varSymbol.static		= false;
				varSymbol.optional		= false;
				varSymbol.virtual		= false;
				varSymbol.abstract		= false;
				varSymbol.delegate		= false;
				varSymbol.event			= false;
				varSymbol.constant		= false;
				varSymbol.ast			= null;
				varSymbol.scope			= methodScope;
				varSymbol.baseSymbol	= null;
				varSymbol.file			= ast.file;
				varSymbol.path			= ast.path;
				varSymbol.start			= ast.start;
				varSymbol.end			= ast.end;
				varSymbol.line_start	= ast.line_start;
				varSymbol.line_end		= ast.line_end;
				varSymbol.scopeId		= methodScope.scopeId;
				varSymbol.vartype		= "Array";
				varSymbol.subtype		= "Object";
				varSymbol.pointer		= true;
				varSymbol.runtime		= "arguments";
				varSymbol.description	= null;
				varSymbol.icon			=  _this.CODE_SYMBOLS_ENUM.SYMBOL_ARGUMENT;
				varSymbol.modifier		= "";
			}

			// Save the argument symbol
			methodScope.vars["arguments"] = varSymbol;

			// =================================================================
			// Process overloaded functions once all overloads are generated.
			// =================================================================

			if(_this.secondPass && ast.overloadOf && ast.overload_name==ast.overloadOf.name+"$"+ast.overloadOf.overloads.length && !ast.symbol.overloads)
			{
				// Get all overloaded functions in one list
				var overloads = [ast.overloadOf].concat(ast.overloadOf.overloads);
				for(var i=0;i<overloads.length;i++)
				{
					overloads[i].overloads = overloads;
					overloads[i].symbol.overloads = overloads;
				}

				// Overloaded functions must all have a different signature.
				for(var i=0;i<overloads.length;i++)
				{
					for(var j=0;j<overloads.length;j++)
					{
						if(i==j) continue;
						if(overloads[i].symbol.__typedParamsList==overloads[j].symbol.__typedParamsList)
						{
							_this.NewError("Redeclaration of function " + overloads[i].symbol.name, overloads[i]);
							_this.NewError("Redeclaration of function " + overloads[j].symbol.name, overloads[j]);
						}
					}
				}

				delete overloads;
				delete names;
			}

			// =================================================================
			// Generate Function Body (and save it to AST for later use)
			// Function body is generated in advance because if function
			// is virtual we will need a non-standard function generation.
			// Function body is complete, including curly brackets.
			// =================================================================

			// If the function has rest arguments then we convert function arguments array to standard JavaScript array.
			var rest_arguments_array = functionSymbol.restArguments ? "arguments = Array.prototype.slice.call(arguments, 0);" : "";

			if(!_this.in_property && (ast.abstract || (classSymbol && classSymbol.interface)))
			{
				if(ast.abstract && ast.body)
					_this.NewError("Invalid abstract function: " + fnName, ast);

				if(classSymbol.interface && ast.body)
					_this.NewError("Invalid interface function: " + fnName, ast);

				ast.generated_code =  "{" + rest_arguments_array;
			}
			else
			{
				ast.generated_code = "{" + rest_arguments_array + generate(ast.body);
			}

			// Generate default return value
			if(!ast.isConstructor && !ast.isDestructor)
			{
				var vartype = _this.getVarType(ast.returntype);
				if(_this.types.hasOwnProperty(vartype))
					ast.generated_code += "\nreturn " + _this.types[vartype].default;
			}

			// Function end closure
			if(_this.lineNumbers && _this.line_start != ast.line_end)
			{
				_this.line_start != -1 && out.push("\n");
				ast.generated_code += ("\/\/@line " + ast.line_end + "\n");
				_this.line_start = ast.line_end;
			}

			ast.generated_code += "\n}";

			/////////////////////////////////////////////////////////////////////////////////////////
	        // Global Function (plain JavaScript function)
			/////////////////////////////////////////////////////////////////////////////////////////

	        if(isGlobal)
	        {
	  			out.push("function " + fnName + paramsList);
				out.push(ast.generated_code);

				functionSymbol.__typedParamsList = paramsList;
				functionSymbol.__untypedParamsList = paramsList;
				functionSymbol.__signature = fnName + paramsList;
				functionSymbol.__cnSignature = fnName + paramsList;
	        }

			/////////////////////////////////////////////////////////////////////////////////////////
	        // Anonymous function
			/////////////////////////////////////////////////////////////////////////////////////////

	        else if(isAnonymous)
	        {
	  			out.push("function " + fnName + paramsList);
				out.push(ast.generated_code);
	        }

			/////////////////////////////////////////////////////////////////////////////////////////
	        // Class member function
			/////////////////////////////////////////////////////////////////////////////////////////

	        else if(classScope)
	        {

	        	// ** WARNING **
	        	// DO NOT REGENERATE THE FUNCTION CODE.
	        	// IT HAS ALREADY BEEN GENERATED AND STORED
	        	// INSIDE ast.generated_code

				// =================================================================
				// Generate Function Signature
				// =================================================================

				functionSymbol.__typedParamsList = typedParamsList;
				functionSymbol.__untypedParamsList = paramsList;

				functionSymbol.__cnSignature = (functionSymbol.public 		? "public " : "") +
											   (functionSymbol.private 		? "private " : "") +
											   (functionSymbol.protected 	? "protected " : "") +
											   (functionSymbol.static 		? "static " : "") +
											   (functionSymbol.abstract 	? "abstract " : "") +
											   (functionSymbol.virtual 		? "virtual " : "") +
											   (classSymbol 				? classSymbol.name+"::" : "") +
											   fnName + typedParamsList +
											   (functionSymbol.vartype 		? " :" +  functionSymbol.vartype : "");

				functionSymbol.__signature = fnName + typedParamsList +
										     (functionSymbol.vartype ? " :" +  functionSymbol.vartype : "");

				// =================================================================
		        // Constructor function
				// =================================================================
	            if(ast.isConstructor)
	            {
	            	out.push("this.Constructor = function" + paramsList);
	            	out.push(ast.generated_code);
	            	out.push(";");
	            }

				// =================================================================
		        // Destructor function
				// =================================================================
	            else if(ast.isDestructor)
	            {
	            	out.push("this.Destructor = function(){");
	            	out.push(ast.generated_code);
					if(_this.secondPass && !functionSymbol.extern)
					{
						out.push("{");

						// Call the destructor of any member variable which
						// is an object, delete it, and set it to null.
						for(item in classSymbol.vars)
						{
							if(classSymbol.vars[item].pointer)
							{
								out.push(classSymbol.vars[item].runtime+"=null;");
							}
						}

						// If there is a base class, call its destructor.
						if(baseClass)
						{
							out.push(_this.DELETE_BASE.replace(/__BASE__/g, classId+"."+baseClassId));
						}

						out.push("}");
					}
					out.push("return true};");
	            }

				// =================================================================
		        // Property setter / getter function
				// =================================================================
				else if(_this.in_property)
				{
		  			out.push(_this.in_property + " function" + paramsList);
	            	out.push(ast.generated_code);
				}

				// =================================================================
		        // State funciton
				// =================================================================
				else if(_this.in_state)
				{
		  			out.push("this." + fnName + " = function" + paramsList);
	            	out.push(ast.generated_code);
	            	out.push(";");
				}

				// =================================================================
		        // Static function
				// =================================================================
		        else if(ast.static)
	            {
					if(ast.public)			out.push(classSymbol.name+".");
					else if(ast.private)	out.push(classSymbol.name+".__PRIVATE__.");
					else if(ast.protected)	out.push(classSymbol.name+".__PROTECTED__.");
	            	out.push(fnName + " = function" + paramsList);
	            	out.push(ast.generated_code);
	            	out.push(";");
	            }

				// =================================================================
  				// Virtual Function
				// =================================================================

				/*@@ ( virtual ) @@*/

  				else if(baseMethodSymbol && baseMethodSymbol.virtual)
  				{
   					// Check for access errors
  					if(ast.private)
  						_this.NewError("Invalid private access modifier for virtual function: "+ast.name, ast);

  					if(baseMethodSymbol.public!=ast.public || baseMethodSymbol.protected!=ast.protected)
  						_this.NewError("Invalid access modifier alteration for virtual function: "+ast.name, ast);

	  				if(_this.secondPass)
	  				{
	  					// ---------------------------------------------------------------------
	  					// Firt we need to find the base class.
	  					// ---------------------------------------------------------------------
	  					var baseClass = _this.getClass(baseMethodSymbol.className);

	  					// Check if the virtual method has the right signature
	  					if(ast.symbol.__signature != baseMethodSymbol.__signature)
	  					{
	  						_this.NewError("Invalid virtual method signature: " + ast.name, ast);
	  						_this.NewError("Invalid virtual method signature: " + ast.name, baseMethodSymbol.ast);
	  					}

	  					// ---------------------------------------------------------------------
	  					// Finally we need to replace the base class virtual method
	  					// ---------------------------------------------------------------------
	  					if(ast.public)
	  					{
							var virtualRedefine = "this." + fnName + " = __VIRTUAL__." + fnName + " = ";

							for(i=classSymbol.bases.length;i--;)
							{
								var base = classSymbol.bases[i];

								// Check if the base class has this virtual method
								if(base.methods[fnName] && !base.methods[fnName].virtual)
								{
									break;
								}

								virtualRedefine += base.classId+"."+fnName+" = ";
							}
							virtualRedefine += "function" + paramsList + ast.generated_code + ";"
	  						out.push(virtualRedefine);
	  					}
		  				else if(ast.protected)
		  				{
							var virtualRedefine = "this.__PROTECTED__." + fnName + " = __VIRTUAL__.__PROTECTED__." + fnName + " = ";
							for(i=0;i<classSymbol.bases.length;i++)
							{
								var base = classSymbol.bases[i];
								virtualRedefine += base.classId+".__PROTECTED__."+fnName+" = ";
							}
							virtualRedefine += "function" + paramsList + ast.generated_code + ";"
	  						out.push(virtualRedefine);
		  				}
  					}
  				}
				// =================================================================
  				// Standard Function
				// =================================================================
  				else
  				{
  					if(ast.private && ast.symbol.virtual)
  						_this.NewError("Invalid private access modifier for virtual function: "+ast.name, ast);

  					if(!_this.in_property && !_this.in_state && !ast.public && !ast.private && !ast.protected)
  						_this.NewError("No access modifier defined for function: " + fnName, ast);

  					if(ast.virtual)
  					{
		  				     if(ast.public)			out.push("this." + fnName + " = __VIRTUAL__." + fnName + " = function" + paramsList);
		  				else if(ast.protected)		out.push("this.__PROTECTED__." + fnName + " = __VIRTUAL__.__PROTECTED__." + fnName + " = function" + paramsList);
  					}
  					else
  					{
		  				     if(ast.public)			out.push("this." + fnName + " = function" + paramsList);
		  				else if(ast.private)		out.push("this.__PRIVATE__." + fnName + " = function" + paramsList);
		  				else if(ast.protected)		out.push("this.__PROTECTED__." + fnName + " = function" + paramsList);
  					}

	            	out.push(ast.generated_code);
	            	out.push(";");
  				}

				// =================================================================
				// Check function return paths
				// =================================================================
				if(_this.secondPass && ast.file && !functionSymbol.extern && !classSymbol.interface)
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

	        } //if(classScope)

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
		/*@@ VAR @@*/

		case jsdef.VAR:
		case jsdef.CONST:

			ast.scope = _this.getCurrentScope();
			var classScope = _this.getClassScope();
			var classSymbol = ast.scope.isClass ? ast.scope.ast.symbol : null;
			var classId	= classSymbol ? classSymbol.classId : null;
			var extern_symbol = null;

			// Process var items to record symbols and generate code

			for(var item in ast)
			{
				if(!isFinite(item)) break;

				// Variables defined in JavaScript global scope such as plain JavaScript files are untyped.
				// Such variables are window, document, canvas, gl, engine, etc. You can define their type
				// inside externs.jspp and the compiler will automatically link the extern_symbol.

				var extern_symbol = null;

                // Type Checks
				if(_this.secondPass && !ast[item].vartype && _this.currClassName)
					_this.NewError("Type declaration missing " + ast[item].name, ast[item]);

				if(_this.secondPass && _this.currClassName && ast[item].vartype && !_this.getClass(ast[item].vartype))
					_this.NewError("Class not found: " + ast[item].vartype, ast[item]);

				if(__exists(ast.scope.vars, ast[item].name))
				{
					// If a var is wrapped inside "#ignore_errors" directive we do not complain for redeclaration.
					if(_this.no_errors)
					{
						extern_symbol = ast.scope.vars[ast[item].name];
					}

					else if(!_this.secondPass)
					{
						_this.NewError("Redeclaration of variable " + ast[item].name + " in current scope", ast[item]);
					}
				}

				if(!_this.secondPass)
			 	{
					if(classScope && __exists(classScope.vars, ast[item].name) && !_this.isInside(ast[item], jsdef.BLOCK))
					{
						_this.NewWarning("Found declaration of variable " + ast[item].name + " in class scope", ast[item]);
					}
				}

				ast[item].pointer = _this.isPointer(ast[item].vartype);

				// Var Symbol
				var varSymbol = new VarSymbol();
				{
					varSymbol.symbolId		= (++_this.symbolId);
					varSymbol.name			= ast[item].name;
					varSymbol.value			= (ast.type==jsdef.CONST || ast.type==jsdef.EVENT ? generate(ast[item].initializer) : null);
					varSymbol.type			= ast[item].type;
					varSymbol.nodeType		= "IDENTIFIER";
					varSymbol.classId		= classId;
					varSymbol.extern		= (ast.file=="externs.jspp");
					varSymbol.public		= ast.public;
					varSymbol.private		= ast.private;
					varSymbol.protected		= ast.protected;
					varSymbol.static		= ast.static;
					varSymbol.optional		= false;
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
					varSymbol.delegate		= ast.delegate;
					varSymbol.event			= false;
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
					varSymbol.pointer		= ast[item].pointer;
					varSymbol.description	= ast.jsdoc ? ast.jsdoc.descr : (classSymbol ? varSymbol.name + " is member var of class " + classSymbol.name : null);
					varSymbol.icon 			= _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;

					if(varSymbol.public)				varSymbol.modifier = "public ";
					else if(varSymbol.private)			varSymbol.modifier = "private ";
					else if(varSymbol.protected)		varSymbol.modifier = "protected ";
					else								varSymbol.modifier = "";
					if(varSymbol.static)				varSymbol.modifier += "static ";

					varSymbol.__signature = varSymbol.name + ":" + varSymbol.vartype;
					varSymbol.__cnSignature = varSymbol.__signature;
					if(classSymbol)
					{
						varSymbol.__cnSignature = varSymbol.modifier + classSymbol.name + "::" + varSymbol.name + ":" + varSymbol.vartype;
					}

					if(varSymbol.private)				varSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PRIVATE_FIELD;
					else if(varSymbol.protected)		varSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROTECTED_FIELD;

					if(varSymbol.constant)				varSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_CONSTANT;
					if(varSymbol.event)					varSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_EVENT;
					if(varSymbol.subtype)				varSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_ARRAY;

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
					varSymbol.pointer = _this.isPointer(varSymbol.vartype);
				}

                if(ast[item].vartype == "Array" && !ast[item].subtype)
                	_this.NewError("Untyped Array " + ast[item].name, ast[item]);

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
					_this.record_vartype_use(ast, varSymbol, classScope, (ast.inFunction ? _this.INCLUDE_IN_CPP : _this.INCLUDE_IN_HPP));
				}

				if(ast[item].initializer)
				{
					// Generate initializer
					if(_this.currClassName && ast.type!=jsdef.CONST && (ast.scope.isClass || ast.scope.isState) && !ast.inFunction && !ast.static)
					{
						if(_this.in_state)
							_this.NewError("Invalid state variable initializer, should be in state enter() function : " + ast[item].name, ast[item]);
						else if(ast.type!=jsdef.EVENT)
							_this.NewError("Invalid class member initializer, should be in constructor: " + ast[item].name, ast[item]);
					}

					ast[item].generated_code = generate(ast[item].initializer);

					// Check type
					var type = _this.getTypeName(ast[item].initializer);
					_this.typeCheck(ast, varSymbol.vartype, type, null, true);
				}
				else
				{
					var vartype = _this.getVarType(ast[item].vartype);
					if(_this.types.hasOwnProperty(vartype))
					{
						ast[item].generated_code = _this.types[vartype].default;
					}
					else if(ast.scope.isClass || ast.scope.isState)
					{
						ast[item].generated_code = "null";
					}
				}

				// Generate

				if(varSymbol.extern) continue;

				if(ast.scope.isClass && !ast.scope.isState && !ast.inFunction)
				{
					if(ast.static)
					{
						if(ast.public)			out.push(classSymbol.name+".");
						else if(ast.private)	out.push(classSymbol.name+".__PRIVATE__.");
						else if(ast.protected)	out.push(classSymbol.name+".__PROTECTED__.");

						out.push(ast[item].name);
						out.push("=" + ast[item].generated_code + ";");
					}
					else
					{
						// For inheritance to work with scalars (strings, numbers, etc.)
						// we need to use getters and setters because only objects are
						// referenced with prototype inheritance and a scalar var needs
						// to get wrapped inside an object. This makes var access very
						// slow, so we do it ONLY if the class is used as a base class
						// by other classes (aka has derivatives) and the variable is
						// not an object already. Also, we don't do it for consts.

						//if(_this.derivatives[classSymbol.name] /*&& !varSymbol.pointer*/ && ast.type!=jsdef.CONST)

						if(_this.derivatives[classSymbol.name] && ast.type!=jsdef.CONST)
						{
							out.push("__PRIVATE__.__" + varSymbol.name + "__ = " + ast[item].generated_code + ";");
							var pdefine = "__PDEFINE__(%, '" + varSymbol.name + "', { configurable:false, get: function(){ return __PRIVATE__.__" + varSymbol.name + "__; }, set: function(v) { __PRIVATE__.__" + varSymbol.name + "__ = v; }});";
							if(ast.public)			out.push(pdefine.replace("%", "this"));
							else if(ast.private)	out.push(pdefine.replace("%", "__PRIVATE__"));
							else if(ast.protected)	out.push(pdefine.replace("%", "__PROTECTED__"));
						}
						else
						{
							if(ast.public)			out.push("this.");
							else if(ast.private)	out.push("__PRIVATE__.");
							else if(ast.protected)	out.push("__PROTECTED__.");
							out.push(ast[item].name);
							out.push("=" + ast[item].generated_code + ";");
						}
					}
				}
				else
				{
					out.push("var ");
					out.push(ast[item].name);
					if(ast.scope.isState) out.push(" = this." + ast[item].name);
					out.push("=" + ast[item].generated_code + ";");
				}

			} //loop

			if(_this.secondPass && !_this.currClassName && !varSymbol.extern)
			{
				_this.addCodeToClassFile(ast.path, out.join(""));
			}

			break;

		// ==================================================================================================================================
		//	   ______      ______               __      ____       _____       _ __  _
		//	  / ____/___ _/ / / /_  ____ ______/ /__   / __ \___  / __(_)___  (_) /_(_)___  ____
		//	 / /   / __ `/ / / __ \/ __ `/ ___/ //_/  / / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
		//	/ /___/ /_/ / / / /_/ / /_/ / /__/ ,<    / /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
		//	\____/\__,_/_/_/_.___/\__,_/\___/_/|_|  /_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
		//
		// ==================================================================================================================================
		/*@@ CALLBACK @@*/

		case jsdef.CALLBACK:

			var scope = _this.NewScope(ast, false, jsdef.CLASS);
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";
			var baseClassSymbol = _this.getClass("Function");

			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId				= (++_this.symbolId);
				classSymbol.name					= ast.name;
				classSymbol.vartype					= ast.name;
				classSymbol.subtype					= null;
				classSymbol.classId					= classId;
				classSymbol.extern					= (ast.file=="externs.jspp");
				classSymbol.base					= "Function";
				classSymbol.baseSymbol				= baseClassSymbol;
				classSymbol.bases 					= [baseClassSymbol];
				classSymbol.derivatives				= {};
				classSymbol.interfaces				= [];
				classSymbol.events					= {};
				classSymbol.__event_bindings		= [];
				classSymbol.__event_unbindings		= [];
				classSymbol.__event_fire			= [];
				classSymbol.type					= jsdef.CLASS;
				classSymbol.nodeType				= "CALLBACK";
				classSymbol.control					= false;
				classSymbol._prototype				= false;
				classSymbol.enum					= false;
				classSymbol.state					= false;
				classSymbol.callback				= true;
				classSymbol.interface				= false;
				classSymbol.ast						= ast;
				classSymbol.scope					= scope;
				classSymbol.vartypes				= scope.vartypes;
				classSymbol.file					= ast.file;
				classSymbol.path					= ast.path;
				classSymbol.start					= ast.start;
				classSymbol.end						= ast.end;
				classSymbol.line_start				= ast.line_start;
				classSymbol.line_end				= ast.line_end;
				classSymbol.scopeId					= scope.scopeId;
				classSymbol.vars					= scope.vars;
				classSymbol.methods	 				= scope.methods;
				classSymbol.runtime					= ast.name;
				classSymbol.icon					= _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FUNCTION;
				classSymbol.EXPORT_NATIVE 			= ast.EXPORT_NATIVE;
				classSymbol.EXPORT_WEB 				= ast.EXPORT_WEB;
			}

			// Create callback signature and save it in the class
			var sig = [];
			for(item in ast.paramsList)
			{
				if(!isFinite(item)) break;
				var arg = ast.paramsList[item];
				sig.push(arg.value + ":" + arg.vartype);
			}
			classSymbol.__typedParamsList = "("+sig.join(", ")+")";

			// Save symbol
			ast.symbol = classSymbol;
			_this.classes[classSymbol.name] = classSymbol;
			_this.scopesStack[0].vars[classSymbol.name] = classSymbol;

			_this.ExitScope();

			break;

		// ==================================================================================================================================
		//	    ______                 __
		//	   / ____/   _____  ____  / /______
		//	  / __/ | | / / _ \/ __ \/ __/ ___/
		//	 / /___ | |/ /  __/ / / / /_(__  )
		//	/_____/ |___/\___/_/ /_/\__/____/
		//
		// ==================================================================================================================================
		/*@@ EVENT @@*/

		case jsdef.EVENT:

			if(!_this.currClassName)
				_this.NewError("Invalid property outside class", ast);

			var currentClass = _this.getCurrentClass();
			var className = _this.currClassName + ast.name + "Event";
			var classId = "__CLASS_" + _this.currClassName.toUpperCase() + ast.name.toUpperCase() + "EVENT__";
			var baseClass = "CocoEvent";
			var baseClassSymbol = _this.getClass(baseClass);

			// Record vartype usage in class level (used to check #includes)
			_this.record_vartype_use(ast, {vartype:className, subtype:null}, currentClass.scope, _this.INCLUDE_IN_HPP);

			// =======================================================================
			// Create event callback signature
			// =======================================================================
			var sig = ["sender:"+currentClass.name, "e:"+className];
			var __simpleEventParams = [];
			for(item in ast.paramsList)
			{
				if(!isFinite(item)) break;
				var arg = ast.paramsList[item];
				sig.push(arg.value + ":" + arg.vartype);
				__simpleEventParams.push(arg.value + ":" + arg.vartype);
			}
			var __typedParamsList = "("+sig.join(", ")+")";
			__simpleEventParams = "("+__simpleEventParams.join(", ")+")";

			// =======================================================================
			// Each Event generates a Class inheriting from CocoEvent.
			// The name of this class is <classname><eventname>Event
			// and we must generate a dummy AST node for the rest of
			// the code to work. We save the dymmy AST node on the
			// class symbol itself to preserve it through second pass.
			// =======================================================================

			var classSymbol = (_this.getClass(className) || new ClassSymbol());
			classSymbol.ast = classSymbol.ast || new Node(null, jsdef.CLASS);
			classSymbol.ast.parent = ast;
			classSymbol.ast.symbol = classSymbol;
			var scope = classSymbol.scope = _this.NewScope(classSymbol.ast);
			{
				classSymbol.symbolId				= (++_this.symbolId);
				classSymbol.name					= className;
				classSymbol.vartype					= className;
				classSymbol.subtype					= null;
				classSymbol.classId					= classId;
				classSymbol.extern					= (ast.file=="externs.jspp");
				classSymbol.base					= baseClass;
				classSymbol.baseSymbol				= baseClassSymbol;
				classSymbol.bases 					= [baseClassSymbol];
				classSymbol.derivatives				= {};
				classSymbol.interfaces				= [];
				classSymbol.events					= {};
				classSymbol.__event_bindings		= [];
				classSymbol.__event_unbindings		= [];
				classSymbol.__event_fire			= [];
				classSymbol.type					= jsdef.CLASS;
				classSymbol.nodeType				= "CLASS";
				classSymbol.control					= false;
				classSymbol._prototype	 			= false;
				classSymbol.enum					= false;
				classSymbol.state					= false;
				classSymbol.callback				= false;
				classSymbol.interface				= false;
				classSymbol.event					= true;	//todo:add to others
				classSymbol.file					= ast.file;
				classSymbol.path					= ast.path;
				classSymbol.start					= ast.start;
				classSymbol.end						= ast.end;
				classSymbol.line_start				= ast.line_start;
				classSymbol.line_end				= ast.line_end;
				classSymbol.scopeId					= classSymbol.scope.scopeId;
				classSymbol.vartypes				= classSymbol.scope.vartypes;
				classSymbol.vars					= classSymbol.scope.vars;
				classSymbol.methods	 				= classSymbol.scope.methods;
				classSymbol.runtime					= ast.name;
				classSymbol.icon					= _this.CODE_SYMBOLS_ENUM.SYMBOL_CLASS;
				classSymbol.__typedParamsList 		= __typedParamsList;
				classSymbol.EXPORT_NATIVE 			= ast.EXPORT_NATIVE;
				classSymbol.EXPORT_WEB 				= ast.EXPORT_WEB;
			}

			// We need to add var members in our new Event Class.
			for(item in ast.paramsList)
			{
				if(!isFinite(item)) break;
				var arg = ast.paramsList[item];
				var varSymbol = new VarSymbol();
				{
					varSymbol.symbolId				= (++_this.symbolId);
					varSymbol.name					= arg.value;
					varSymbol.value					= null;
					varSymbol.type					= arg.type;
					varSymbol.nodeType				= "IDENTIFIER";
					varSymbol.classId				= classSymbol.clssId;
					varSymbol.extern				= false
					varSymbol.public				= true;
					varSymbol.private				= false;
					varSymbol.protected				= false;
					varSymbol.static				= false;
					varSymbol.optional				= false;
					varSymbol.virtual				= false;
					varSymbol.abstract				= false;
					varSymbol.delegate				= false;
					varSymbol.event					= false;
					varSymbol.constant				= false;
					varSymbol.ast					= arg;
					varSymbol.scope					= classSymbol.scope;
					varSymbol.baseSymbol			= null;
					varSymbol.file					= arg.file;
					varSymbol.path					= arg.path;
					varSymbol.start					= arg.start;
					varSymbol.end					= arg.end;
					varSymbol.line_start			= arg.line_start;
					varSymbol.line_end				= arg.line_end;
					varSymbol.scopeId				= classSymbol.scope.scopeId;
					varSymbol.vartype				= arg.vartype;
					varSymbol.subtype				= arg.subtype ? arg.subtype : _this.getSubType(arg.vartype);
					varSymbol.pointer				= arg.pointer;
					varSymbol.icon 					= _this.CODE_SYMBOLS_ENUM.SYMBOL_PUBLIC_FIELD;
					varSymbol.modifier 				= "public";
					varSymbol.signature 			= varSymbol.name + ":" + varSymbol.vartype;
					varSymbol.runtime 				= arg.value;
				}
				classSymbol.vars[varSymbol.name]=varSymbol;

    			// Record vartype usage in class level (used to check #includes)
    			_this.record_vartype_use(ast, varSymbol, classSymbol.scope, _this.INCLUDE_IN_HPP);
			}

			// Save Event Class symbol
			ast.event_class_symbol = classSymbol;
			_this.classes[classSymbol.name] = classSymbol;
			_this.scopesStack[0].vars[classSymbol.name] = classSymbol;

			// =======================================================================
			// The event is also declared as a variable of vartype
			// <classname><eventname>Event on the current class
			// =======================================================================

			var varSymbol = new VarSymbol();
			{
				varSymbol.symbolId				= (++_this.symbolId);
				varSymbol.name					= ast.name;
				varSymbol.value					= null;
				varSymbol.type					= ast.type;
				varSymbol.nodeType				= ast.nodeType;
				varSymbol.classId				= currentClass.clssId;
				varSymbol.extern				= (ast.file=="externs.jspp");
				varSymbol.public				= true;
				varSymbol.private				= false;
				varSymbol.protected				= false;
				varSymbol.static				= false;
				varSymbol.optional				= false;
				varSymbol.virtual				= false;
				varSymbol.abstract				= false;
				varSymbol.delegate				= false;
				varSymbol.event					= true;
				varSymbol.constant				= false;
				varSymbol.ast					= ast;
				varSymbol.scope					= currentClass.scope;
				varSymbol.baseSymbol			= null;
				varSymbol.file					= ast.file;
				varSymbol.path					= ast.path;
				varSymbol.start					= ast.start;
				varSymbol.end					= ast.end;
				varSymbol.line_start			= ast.line_start;
				varSymbol.line_end				= ast.line_end;
				varSymbol.scopeId				= currentClass.scope.scopeId;
				varSymbol.vartype				= classSymbol.name;
				varSymbol.subtype				= null;
				varSymbol.pointer				= ast.pointer;
				varSymbol.description			= ast.jsdoc ? ast.jsdoc.descr : varSymbol.name + " is event of class " + currentClass.name;
				varSymbol.icon 					= _this.CODE_SYMBOLS_ENUM.SYMBOL_EVENT;
				varSymbol.modifier 				= "public";
				//varSymbol.__typedParamsList		= __typedParamsList;
				//varSymbol.signature 			= "event " + varSymbol.name + varSymbol.__typedParamsList;

				varSymbol.__signature = "event " + varSymbol.name + ":" + className;
				varSymbol.__cnSignature = "public event " + currentClass.name + "::" + varSymbol.name + __simpleEventParams;

				if(classId && ast.public)			varSymbol.runtime = classId + "." + ast.name;
				else if(classId && ast.private)		varSymbol.runtime = classId + ".__PRIVATE__." + ast.name;
				else if(classId && ast.protected)	varSymbol.runtime = classId + ".__PROTECTED__." + ast.name;
				else								varSymbol.runtime = ast.name;
			}

            // Save var in scopes
			ast.symbol = varSymbol;
			ast.scope = currentClass.scope;
			currentClass.scope.vars[ast.name] = varSymbol;
			currentClass.events[ast.name] = varSymbol;

			// =======================================================================
			// Register the event class in global scope
			// =======================================================================

			out.push("global." + classSymbol.name + " = function(){");

			// Add event parameters
			for(item in ast.paramsList)
			{
				if(!isFinite(item)) break;
				var arg = ast.paramsList[item];
				out.push("this." + arg.value + "=null;");
			}
			out.push("};");

			// Set CocoEvent as the prototype so that it can be inherited
			out.push("global." + classSymbol.name + ".prototype = new CocoEvent(\"" + varSymbol.name + "\", true, true);");

			// =======================================================================
			// Instantiate the event object as public var of this class
			// =======================================================================

			out.push("this." + varSymbol.name + " = new " + classSymbol.name + "();" );

			// Done.
			_this.ExitScope();

			break;

		// ==================================================================================================================================
		//	    ______
		//	   / ____/___  __  ______ ___  _____
		//	  / __/ / __ \/ / / / __ `__ \/ ___/
		//	 / /___/ / / / /_/ / / / / / (__  )
		//	/_____/_/ /_/\__,_/_/ /_/ /_/____/
		//
		// ==================================================================================================================================
		/*@@ ENUM @@*/

		case jsdef.ENUM:

			var scope = _this.NewScope(ast);
			var classId = "__CLASS__" + ast.name.toUpperCase() + "__";

			var classSymbol = new ClassSymbol();
			{
				classSymbol.symbolId				= (++_this.symbolId);
				classSymbol.name					= ast.name;
				classSymbol.vartype					= ast.name;
				classSymbol.subtype					= null;
				classSymbol.classId					= classId;
				classSymbol.extern					= (ast.file=="externs.jspp");
				classSymbol.base					= null;
				classSymbol.baseSymbol				= null;
				classSymbol.bases 					= [];
				classSymbol.derivatives				= {};
				classSymbol.interfaces				= [];
				classSymbol.events					= {};
				classSymbol.__event_bindings		= [];
				classSymbol.__event_unbindings		= [];
				classSymbol.__event_fire			= [];
				classSymbol.type					= jsdef.CLASS;
				classSymbol.nodeType				= "ENUM";
				classSymbol.control					= false;
				classSymbol._prototype				= false;
				classSymbol.enum					= true;
				classSymbol.state					= false;
				classSymbol.callback				= false;
				classSymbol.interface				= false;
				classSymbol.ast						= ast;
				classSymbol.scope					= scope;
				classSymbol.vartypes				= scope.vartypes;
				classSymbol.file					= ast.file;
				classSymbol.path					= ast.path;
				classSymbol.start					= ast.start;
				classSymbol.end						= ast.end;
				classSymbol.line_start				= ast.line_start;
				classSymbol.line_end				= ast.line_end;
				classSymbol.scopeId					= scope.scopeId;
				classSymbol.vars					= scope.vars;
				classSymbol.methods	 				= scope.methods;
				classSymbol.runtime					= ast.name;
				classSymbol.icon					= _this.CODE_SYMBOLS_ENUM.SYMBOL_ENUM;
				classSymbol.EXPORT_NATIVE 			= ast.EXPORT_NATIVE;
				classSymbol.EXPORT_WEB 				= ast.EXPORT_WEB;
			}

			// Save symbol
			ast.symbol = classSymbol;
			_this.classes[classSymbol.name] = classSymbol;
			_this.scopesStack[0].vars[classSymbol.name] = classSymbol;

            // Generate enum
            if(_this.currClassName)
            {
				if(ast.public)			out.push("this.");
				else if(ast.private)	out.push("this.__PRIVATE__.");
				else if(ast.protected)	out.push("this.__PROTECTED__.");
				out.push(ast.name + " = {");
            }
            else
			{
				out.push("var " + ast.name + " = {");
			}

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
					varSymbol.nodeType		= "ENUM_ITEM";
					varSymbol.classId		= classId;
					varSymbol.extern		= classSymbol.extern;
					varSymbol.enum			= true;
					varSymbol.public		= true;
					varSymbol.private		= false;
					varSymbol.protected		= false;
					varSymbol.static		= true;
					varSymbol.optional		= false;
					varSymbol.virtual		= false;
					varSymbol.abstract		= false;
					varSymbol.delegate		= false;
					varSymbol.event			= false;
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
					varSymbol.icon			= _this.CODE_SYMBOLS_ENUM.SYMBOL_ENUM_ITEM;
					varSymbol.modifier 		= "public";

					if(varSymbol.public)			varSymbol.runtime = "this." + ast.name + "." + varSymbol.name;
					else if(varSymbol.private)		varSymbol.runtime = "this.__PRIVATE__." + ast.name + "." + varSymbol.name;
					else if(varSymbol.protected)	varSymbol.runtime = "this.__PROTECTED__." + ast.name + "." + varSymbol.name;
					else							varSymbol.runtime = ast.name + "." + varSymbol.name;
				}
				classSymbol.vars[varSymbol.name] = varSymbol;

				if(!firstItem) out.push(", ");
				out.push(ast[item].name + ":" + ast[item].value);
				firstItem = false;
			}
			out.push("};");

			if(_this.secondPass && !_this.currClassName)
			{
				_this.addCodeToClassFile(ast.path, out.join("\n"));
			}

			_this.ExitScope();
			break;

		// ==================================================================================================================================
		//	    ____                             __
		//	   / __ \_________  ____  ___  _____/ /___  __
		//	  / /_/ / ___/ __ \/ __ \/ _ \/ ___/ __/ / / /
		//	 / ____/ /  / /_/ / /_/ /  __/ /  / /_/ /_/ /
		//	/_/   /_/   \____/ .___/\___/_/   \__/\__, /
		//	                /_/                  /____/
		// ==================================================================================================================================
		/*@@ PROPERTY @@*/

		case jsdef.PROPERTY:

			ast.pointer = _this.isPointer(ast.vartype);

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
			if(!_this.secondPass && __exists(parentScope.vars, propertyName))
				_this.NewError("Redeclaration of property " + propertyName, ast);

           	// Define property symbol
			var propSymbol = new PropSymbol();
			{
				propSymbol.symbolId		= (++_this.symbolId);
				propSymbol.name			= propertyName;
				propSymbol.value		= null;
				propSymbol.type			= ast.type;
				propSymbol.nodeType		= "PROPERTY";
				propSymbol.classId		= classId;
				propSymbol.extern		= (ast.file=="externs.jspp");
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
				propSymbol.pointer		= ast.pointer;
				propSymbol.description	= ast.jsdoc ? ast.jsdoc.descr : propSymbol.name + " is property of class " + classSymbol.name;
				propSymbol.icon 		= _this.CODE_SYMBOLS_ENUM.SYMBOL_PROPERTY;

				if(propSymbol.public)			propSymbol.modifier = "public ";
				else if(propSymbol.private)		propSymbol.modifier = "private ";
				else if(propSymbol.protected)	propSymbol.modifier = "protected ";
				else							propSymbol.modifier = "";
				if(propSymbol.static)			propSymbol.modifier += "static ";

				propSymbol.__signature = propSymbol.name + ":" + propSymbol.vartype;
				propSymbol.__cnSignature = propSymbol.modifier + "property " + classSymbol.name + "::" + propSymbol.name + ":" + propSymbol.vartype;

				if(propSymbol.private)			propSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROPERTY;
				else if(propSymbol.protected)	propSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_PROPERTY;

				if(ast.public)					propSymbol.runtime = classId + "." + propertyName;
				else if(ast.private)			propSymbol.runtime = classId + ".__PRIVATE__." + propertyName;
				else if(ast.protected)			propSymbol.runtime = classId + ".__PROTECTED__." + propertyName;
				else							propSymbol.runtime = propertyName;
			}

           	// Save symbol
			ast.symbol = propSymbol;
			classSymbol.scope.vars[propertyName] = propSymbol;

			// Generate code
			var definition;

			if(ast.static)
			{
				if(ast.public)			definition = classSymbol.name;
				else if(ast.private)	definition = classSymbol.name+".__PRIVATE__";
				else if(ast.protected)	definition = classSymbol.name+".__PROTECTED__";
			}
			else
			{
				if(ast.public)			definition = "this";
				else if(ast.private)	definition = "this.__PRIVATE__";
				else if(ast.protected)	definition = "this.__PROTECTED__";
			}

			out.push("Object.defineProperty(" + definition + ", '" + propertyName + "', {enumerable:true,");

			_this.in_property = "get: ";
			out.push(generate(ast.getter) + (ast.setter?",":""));

			if(ast.setter)
			{
				_this.in_property = "set: ";
				out.push(generate(ast.setter));
			}

			out.push("});");

			// Save generated code to ast for later use in inheritance
			ast.generated_code = out.join("\n");

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
		/*@@ STATE @@*/

		case jsdef.STATE:

			if(!_this.currClassName)
				_this.NewError("Invalid state outside class", ast);

			if(_this.states.hasOwnProperty(ast.name))
				_this.NewError("Duplicate state name: " + ast.name, ast);

			var hasTick = false;
			var hasPaint = false;
			var hasEnter = false;
			var hasExit = false;
			var classSymbol = _this.getCurrentScope().ast.symbol;
			var classId = classSymbol.classId;
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
				stateSymbol.nodeType		= "STATE";
				stateSymbol.classId			= classSymbol.classId;
				stateSymbol.extern			= (ast.file=="externs.jspp");
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
				stateSymbol.nextStates		= {};
				stateSymbol.description		= ast.jsdoc ? ast.jsdoc.descr : stateSymbol.name + " is engine state of class " + classSymbol.name;
				stateSymbol.icon 			= _this.CODE_SYMBOLS_ENUM.SYMBOL_OBJECT;

				if(stateSymbol.public)			stateSymbol.modifier = "public";
				else if(stateSymbol.private)	stateSymbol.modifier = "private";
				else if(stateSymbol.protected)	stateSymbol.modifier = "protected";
				else							stateSymbol.modifier = "";

				if(stateSymbol.private)			stateSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_OBJECT;
				else if(stateSymbol.protected)	stateSymbol.icon = _this.CODE_SYMBOLS_ENUM.SYMBOL_OBJECT;

				if(ast.public)					stateSymbol.runtime = classSymbol.classId + "." + ast.name;
				else if(ast.private)			stateSymbol.runtime = classSymbol.classId + ".__PRIVATE__." + ast.name;
				else if(ast.protected)			stateSymbol.runtime = classSymbol.classId + ".__PROTECTED__." + ast.name;
				else							stateSymbol.runtime = ast.name;
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
					if(ast.body[item].name=="enter") hasEnter = true;
					if(ast.body[item].name=="exit") hasExit = true;
					if(ast.body[item].name=="tick") hasTick = true;
					if(ast.body[item].name=="paint") hasPaint = true;
					out.push(generate(ast.body[item]));
 					break;
				}
			}
			out.push("return this}).call(new State);");

            // Check state implementation
			if(!hasEnter) _this.NewError("Missing state enter function: " + ast.name, ast);
			if(!hasExit) _this.NewError("Missing state exit function: " + ast.name, ast);
			if(!hasTick) _this.NewError("Missing state tick function: " + ast.name, ast);
			if(!hasPaint) _this.NewError("Missing state paint function: " + ast.name, ast);

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
			if(ast.inFunction && ast.inClass)
			{
				ast.symbol = _this.getCurrentClass().baseSymbol;
				ast.runtime = ast.symbol.classId;

				if(ast.inDot && ast==ast.inDot.identifier_first)
				{
					// *** WE NEED TO FIND THE BASE CLASS THAT IMPLEMENTS THE MEMBER THAT SUPER TRIES TO ACCESS  *** //

					var member = ast.inDot.identifiers_list[1].value;
					var dot_to_base = _this.isBaseMember(member, ast.inClass.symbol, true);
					out.push(dot_to_base);

				}
				else
				{
					_this.NewError("Invalid use of super.", ast);
				}
			}
			else
			{
				_this.NewError("Invalid super outside class", ast);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.THIS:
			if(ast.inFunction && ast.inClass)
			{
				ast.symbol = _this.getCurrentClass();
				ast.runtime = ast.symbol.classId;

				if(ast.inDot && ast==ast.inDot.identifier_first)
				{
					// *** WE DO NOT GENERATE THIS IF IT IS THE FIRST IDENTIFIER IN A DOT *** //
				}
				else
				{
					out.push("__THIS__");
				}
			}
			else
			{
				out.push("this");
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DOT:

			// jsdef.THIS does not produce output,
			// so we have to be carefull with ast[0]
			var gen = generate(ast[0]);
			if(gen)
			{
				out.push(gen);
				out.push(".");
			}
			out.push(generate(ast[1]));
			if(_this.secondPass)
			{
				_this.addDebugSymbol(ast, out.join(""));
				ast[0].vartype = _this.getTypeName(ast[0]);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.INDEX:
			out.push(generate(ast[0]));
			ast.generated_index = "[" + generate(ast[1]) + "]";
			out.push(ast.generated_index);
			if(_this.secondPass) ast[0].vartype = _this.getTypeName(ast[0]);
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*@@ IDENTIFIER @@*/
		case jsdef.IDENTIFIER:

			// First pass or not inside a class?
			if(!_this.secondPass || _this.no_errors>0)
			{
				// Generate identifier and be gone.
				out.push(ast.value);
				break;
			}

			// #######################################################################################################################################################
			// #	   ___     __                __                  _     __           __  _ _____              _____                 __          __
			// #	  <  /    / /   ____  ____  / /____  ______     (_)___/ /__  ____  / /_(_) __(_)__  _____   / ___/__  ______ ___  / /_  ____  / /
			// #	  / /    / /   / __ \/ __ \/ //_/ / / / __ \   / / __  / _ \/ __ \/ __/ / /_/ / _ \/ ___/   \__ \/ / / / __ `__ \/ __ \/ __ \/ /
			// #	 / /    / /___/ /_/ / /_/ / ,< / /_/ / /_/ /  / / /_/ /  __/ / / / /_/ / __/ /  __/ /      ___/ / /_/ / / / / / / /_/ / /_/ / /
			// #	/_(_)  /_____/\____/\____/_/|_|\__,_/ .___/  /_/\__,_/\___/_/ /_/\__/_/_/ /_/\___/_/      /____/\__, /_/ /_/ /_/_.___/\____/_/
			// #	                                   /_/                                                         /____/
			// #
			// #  Phase 1 is identifier symbol lookup.
			// #
			// #  The general idea is that we need to associate an identifier with an existing symbol (class, function, var, argument, property, state, etc).
			// #  This is done mostly by _this.LookupIdentifier() but there are some special cases we need to pay attention:
			// #  a) The first special case is Typed Arrays that we need to resolve their sub-type. For example Float32Array subtype is Float.
			// #  b) The second special case is Overloaded Functions; We need to examine AST siblings in order to identify the proper overload to use.
			// #
			// #######################################################################################################################################################

			//==================================================================================
			// Lookup the symbol for this identifier.
			//==================================================================================

			if(!ast.symbol)
			{
				ast.symbol = _this.LookupIdentifier(_this.getCurrentScope(), ast.value, ast);
			}

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
				case "Int8Array":		ast.symbol.subtype = "Integer"; break;
				case "Int16Array":		ast.symbol.subtype = "Integer"; break;
				case "Int32Array":		ast.symbol.subtype = "Integer"; break;
				case "Uint8Array":		ast.symbol.subtype = "Integer"; break;
				case "Uint16Array":		ast.symbol.subtype = "Integer"; break;
				case "Uint32Array":		ast.symbol.subtype = "Integer"; break;
				case "Float32Array":	ast.symbol.subtype = "Float"; break;
				case "Float64Array":	ast.symbol.subtype = "Float"; break;
				case "Array":			if(!ast.subtype) _this.NewError("Untyped Array", ast);
			}

			//==================================================================================
			// Add vartype to class vartypes lists (used to determine #includes)
			//==================================================================================
			_this.record_vartype_use(ast, ast.symbol, _this.getClassScope(), _this.INCLUDE_IN_CPP);

			//==================================================================================
			// Is this identifier a standard var declaration?
			//==================================================================================
			if(!ast.symbol.public && !ast.symbol.private && !ast.symbol.protected)
			{
				ast.runtime = ast.value;
				out.push(ast.runtime);
				//_this.addDebugSymbol(ast, ast.runtime);
				break;
			}

			//==================================================================================
			// If the identifier's symbol is an overloaded function we need
			// to determine from the execution context which overload to use.
			//
			// We need to consider the places where an overloaded function might appear:
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
								var type1 = _this.getTypeName(astCALL[1][j]);
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

								// *** Special Case ***
								// If the overloaded function belongs to a delegated object we
								// need to aquire the proper function symbol from the host class
								// that has the proper runtime information.

								if(ast.symbol.delegated)
								{
									ast.symbol = ast.symbol.scope.parentScope.methods[ast.symbol.overloads[i].symbol.name];
								}

								// otherwise we simply swap to the overloaded function symbol
								else
								{
									ast.symbol = ast.symbol.overloads[i].symbol;
								}

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

			// ###############################################################################################################################################################################################
			// #	   ___        ____                  __              _     __           __  _ _____                               __  _
			// #	  |__ \      / __ \___  _________  / /   _____     (_)___/ /__  ____  / /_(_) __(_)__  _____   _______  ______  / /_(_)___ ___  ___     ____ ______________  __________
			// #	  __/ /     / /_/ / _ \/ ___/ __ \/ / | / / _ \   / / __  / _ \/ __ \/ __/ / /_/ / _ \/ ___/  / ___/ / / / __ \/ __/ / __ `__ \/ _ \   / __ `/ ___/ ___/ _ \/ ___/ ___/
			// #	 / __/_    / _, _/  __(__  ) /_/ / /| |/ /  __/  / / /_/ /  __/ / / / /_/ / __/ /  __/ /     / /  / /_/ / / / / /_/ / / / / / /  __/  / /_/ / /__/ /__/  __(__  |__  )
			// #	/____(_)  /_/ |_|\___/____/\____/_/ |___/\___/  /_/\__,_/\___/_/ /_/\__/_/_/ /_/\___/_/     /_/   \__,_/_/ /_/\__/_/_/ /_/ /_/\___/   \__,_/\___/\___/\___/____/____/
			// #
			// #
			// #   Phase 2 is resolving identifier runtime access DOT path.
			// #
			// #   What this means?
			// #
			// #   First, it means you need to understand the difference between "identifer" and "symbol" before you continue reading, if you haven't already!!
			// #   + When you type something like "var x:Float=5;", you define "symbol x".
			// #   + When you later type "x++;" then this "x" is the "identifier x" which must be linked to "symbol x".
			// #   The symbol holds all the nessesary metdata about the identifier, such as its vartype, its containing class, its scope, etc.
			// #
			// #   Therefore, resolving the identifier runtime access DOT path is the process of deriving a DOT path (A.B.C.D.x) that will take you from where the "identifier x" is to where
			// #   "symbol x" is actually stored. This can be a different class, a base-class, a virtual method, an overloaded method, an enum, etc.
			// #
			// #   Typically this depends on "WHERE THE SYMBOL IS DEFINED" and "WHERE IT IS BEING ACCESSED FROM". If the symbol is defined in ClassA and it is being access from ClassB then
			// #   we need to construct an access path that will successfully read/write its data. However, there are severlar spacial cases about this. For example, the identifier might be
			// #   a virtual function which is a rather tricky case, or the identifier might be a member of a base-class (of a base-class, of a base-class, ..), which makes the access path
			// #   a bit longer.
			// #
			// #   To actually solve this problem we need to lay down some access rules:
			// #   =====================================================================
			// #
			// #   1. The DOT access-path pattern is: [__CLASS_XXX__][.__BASES__|.__VIRTUAL__][.__PRIVATE__|.__PROTECTED__].<symbol_name>
			// #
			// #	  __CLASS_XXX__    	: The name of the class where the symbol is defined.
			// #	  __BASES__        	: If the symbol is an inherited member, this is a dot-list of all the base classIds leading to the low-level base-class where the symbol is defined.
			// #	  __VIRTUAL__      	: (or) If the symbol is a virtual function symbol, we need to access it through the __VIRTUAL__ bank.
			// #	  __PRIVATE__      	: If the symbol is a private symbol, we need to access it through the __PRIVATE__ bank.
			// #	  __PROTECTED__    	: (or) If the symbol is a private symbol, we need to access it through the __PROTECTED__ bank.
			// #	  <symbol_name>  	: The symbol name. This can be different from the identifier name for overloaded functions.
			// #                          To understand what this means think of the XMLHttp.send() overloads that produce different symbol names:
			// #                          XMLHttp.send(), XMLHttp.send$1(String), XMLHttp.send$2(ArrayBufferView)
			// #
			// #   2. Access at the end of the day is controlled by public/private/protected modifiers
			// #   3. If the identifier is a class member (function, var, property, etc.) and the class derives from a base-class, we ALWAYS access the low-level base-class identifier.
			// #   4. To make our life easier, we do not generate "this" if it is the first identifier in a DOT. We let the second identifier of the DOT generate "this" if needed. This rule actually makes
			// #      our life much easier, especially if the DOT accesses an inherited member where generating "this" would require that we unwind the stack.
			// #   5. We generate "this" if and only if it is alone, eg. passed as argument: obj.setParent( this );
			// #   6. Enum Items are similar to "this" because programmers access enums either canonically "enum_name.enum_item" or straight "enum_item". Therefore we need to skip generating the enum class
			// #      name (yes, enums are classes and enum items static constants) if it is the first identifier in a DOT, and make sure that the enum-item will be generated fully qualified.
			// #   7. If access to the identifier is LOCAL (meaning that the identifier points to a class member) we prefix the local classId: __CLASS_XXX__
			// #   8. If access to the identifier is NOT-LOCAL (meaning that the identifier points to another class) we DO NOT prefix the classId.
			// #   9. Global scope knows nothing about inheritance, so if plain JavaScript code should be able to work with our classes seamlessly.
			// #
			// #   ** NONTE: ** The access-path of the symbol is calculated during symbol generation and stored in "symbol.runtime".
			// #                However, resolving an identifier linked to this symbol in most cases it requres further processing.
			// #				Both "symbol.runtime" and "ast.runtime" are exported as "debug symbols" so that when you debug and
			// #                you hover the mouse over an identifier, it can be recognized and evaluated getting a tooltip of its
			// #                value, or if it is an object display a list of its member values in the IDE expression viewer.
			// #
			// ###############################################################################################################################################################################################

			// =============================================================
			// Symbol is static member.
			// =============================================================
			if(ast.symbol.static && ast.inClass && !ast.symbol.extern && !ast.symbol.enum && ast.symbol.type!=jsdef.STATE)
			{
				var path = "";
				if(!ast.inDot) path += _this.currClassName + ".";
				if(ast.symbol.protected) path += "__PROTECTED__.";
				else if(ast.symbol.private) path += "__PRIVATE__.";
				path += ast.value;
				out.push(path);
			}

			// =============================================================
			// Identifier is not in a DOT.
			// =============================================================
			else if(!ast.inDot)
			{
				out.push(ast.symbol.runtime);
			}

			// =============================================================
			// Symbol is defined in externs and used in global scope.
			// =============================================================
			else if(ast.inDot && ast.symbol.extern && !ast.inClass)
			{
				out.push(ast.value);
			}

			// =============================================================
			// Symbol is defined in externs and used in derived-class scope.
			// Also, symbol inherits from a class also defined in externs.
			// (eg. TouchList which inherits from ECMA Array)
			// =============================================================
			else if(ast.inDot && ast.symbol.extern && ast.inClass && (path=_this.isBaseMember(ast.value, ast.inClass.symbol, true)))
			{
				out.push(ast.symbol.name);
			}

			// =============================================================
			// Symbol is defined in externs and used in class scope.
			// =============================================================
			else if(ast.inDot && ast.symbol.extern && ast.inClass)
			{
				out.push(ast.value);
			}

			// =============================================================
			// Identifier is FIRST in DOT
			// =============================================================
			else if(ast.inDot && ast==ast.inDot.identifier_first)
			{
				out.push(ast.symbol.runtime);
			}

			// =============================================================
			// Identifier NOT first in DOT.
			// Symbol is a virtual function.
			// The first DOT identifier is SUPER or THIS.
			// =============================================================

			// To invoke the virtual method through the __VIRTUAL__ bank,
			// the method has to be overwitten by this class. Otherwise
			// we invoke the method from its base class.

			else if(ast.inDot && ast!=ast.inDot.identifier_first && ast.symbol.type==jsdef.FUNCTION && ast.symbol.virtual && __exists(ast.inClass.symbol.methods, ast.value) && (ast.inDot.identifier_first.type==jsdef.SUPER || ast.inDot.identifier_first.type==jsdef.THIS))
			{
				ast.runtime = "__VIRTUAL__."
				if(ast.symbol.protected) ast.runtime += "__PROTECTED__.";
				ast.runtime += ast.value;
				out.push(ast.runtime);
			}

			// =============================================================
			// Identifier NOT first in DOT.
			// Identifier is ENUM ITEM.
			// =============================================================
			else if(ast.inDot && ast!=ast.inDot.identifier_first && ast.symbol.enum)
			{
				// TODO: Test class/global enums in CocoTest
				// TODO: Test class public/private/protected enums in CocoTest
				out.push(ast.value);
			}

			// =============================================================
			// Identifier NOT first in DOT.
			// First in DOT is THIS.
			// =============================================================

			else if(ast.inDot && ast!=ast.inDot.identifier_first && ast.inDot.identifier_first.type==jsdef.THIS)
			{
				// Is it a base symbol?
				var path = _this.isBaseMember(ast.value, ast.inClass.symbol, false);
				if(path)
				{
					out.push(path+"."+ast.value);
				}
				else
				{
					// Process access modifiers
					if(ast.symbol.public)
					{
						out.push(ast.value);
					}
					else if(ast.symbol.private)
					{
						out.push("__PRIVATE__." + ast.value);
					}
					else if(ast.symbol.protected)
					{
						out.push("__PROTECTED__." + ast.value);
					}
				}
			}

			// =============================================================
			// Identifier NOT first in DOT.
			// =============================================================
			else if(ast.inDot && ast!=ast.inDot.identifier_first)
			{
				// Process access modifiers
				if(ast.symbol.public)
				{
					out.push(ast.value);
				}
				else if(ast.symbol.private)
				{
					out.push("__PRIVATE__." + ast.value);
				}
				else if(ast.symbol.protected)
				{
					out.push("__PROTECTED__." + ast.value);
				}
			}

			//==================================================================================
			// Check member access
			//==================================================================================
			if(!ast.symbol.delegated)
			{
				if(ast.symbol.private && ast.inClass!=ast.symbol.ast.inClass)
				{
					_this.NewError("Invalid private member access: " + ast.value, ast);
				}
				else if(ast.symbol.protected && ast.inClass!=ast.symbol.ast.inClass && !_this.isBaseMember(ast.value, ast.inClass.symbol))
				{
					_this.NewError("Invalid protected member access: " + ast.value, ast);
				}
			}

			//==================================================================================
			// If the identifier is addEventListener then we need to store this ast in its class
			//==================================================================================
			if(ast.symbol && ast.symbol.name==_this.ADD_EVENT)
			{
				if(_this.isDerivativeOf(ast.inDot[0].symbol.vartype, "CocoEventSource"))
				{
					ast.__event = true;
					_this.getCurrentClass().__event_bindings.push(ast);
				}
			}
			if(ast.symbol && ast.symbol.name==_this.REMOVE_EVENT)
			{
				if(_this.isDerivativeOf(ast.inDot[0].symbol.vartype, "CocoEventSource"))
				{
					ast.__event = true;
					_this.getCurrentClass().__event_unbindings.push(ast);
				}
			}
			if(ast.symbol && ast.symbol.name==_this.DISPATCH_EVENT)
			{
				if(_this.isDerivativeOf(_this.getCurrentClass().name, "CocoEventSource"))
				{
					ast.__event = true;
					_this.getCurrentClass().__event_fire.push(ast);
				}
			}

			//==================================================================================
			// Generate debug symbol and cache identifier in current scope for speed
			//==================================================================================
			ast.runtime = out.join("");
			_this.addDebugSymbol(ast, ast.runtime);
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

			if(_this.lineNumbers && _this.line_start != ast.line_end)
			{
				_this.line_start != -1 && out.push("\n");
				out.push("\/\/@line " + ast.line_end + "\n");
				_this.line_start = ast.line_end;
			}

			out.push("}\n");
			_this.ExitScope();
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CALL:
			var call0 = generate(ast[0]);
			var call1 = generate(ast[1]);
			var cls = _this.getClass(call0);
			if(!_this.secondPass) break;

			// EVENT HACK: for Coconut2D events append execution context __THIS__ to arguments.
			if(ast[0][1] && ast[0][1].__event && (ast[0][1].value==_this.ADD_EVENT || ast[0][1].value==_this.REMOVE_EVENT))
			{
				call1+=", __THIS__";
			}

			// EVENT HACK: dispatchEvent loads values to event prior to firing
			if(ast[0][1] && ast[0][1].__event && ast[0][1].value==_this.DISPATCH_EVENT)
			{
				var call = _this.isInside(ast[0][1], jsdef.CALL);
				var evCls = _this.getClass(_this.getTypeName(call[1][0]));
				var evObj = generate(call[1][0]);
				var index = 1;
				for(item in evCls.vars)
					out.push(evObj+"."+item+"="+generate(call[1][index++])+";");
			}

			// Detect callbacks from variables or maybe we should call everything with ".call(scope"
			var callbackCall = _this.secondPass && ast[0].symbol && ast[0].symbol instanceof VarSymbol && ast[0].symbol.file != "externs.jspp";

			if(_this.secondPass && cls)
			{
				// Typcast
				ast.typecasting = true;
				ast.castFromType = _this.getTypeName(ast[1][0]);
				ast.castToType = call0;
				out.push("("+call1+")");
			}
			else
			{
				out.push(call0);
				if(callbackCall) out.push(".call(global" + (call1.trim() ? "," : ""));
				else out.push("(");
				out.push(call1);
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

			if(_this.secondPass && _this.currClassName)
				_this.NewError("Illegal object initialization inside class", ast);

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
			//out.push(generate(ast[0]) + ":");
			out.push(ast[0].value+":");
			out.push(generate(ast[1]));
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.ASSIGN:
			out.push(generate(ast[0]));
			out.push(ast.value);
			if(ast.value != "=") out.push("=");
			out.push(generate(ast[1]));

			if(_this.secondPass)
			{
				if(ast[0].type==jsdef.THIS)
				{
					_this.NewError("Cannot assign to 'this'", ast);
				}
				else if(ast[0].type != jsdef.IDENTIFIER && ast[0].type != jsdef.DOT && ast[0].type != jsdef.INDEX)
				{
					_this.NewError("Invalid left-hand assignment", ast);
				}
			    _this.typeCheck(ast, _this.getTypeName(ast[0]), _this.getTypeName(ast[1]));
			}

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
			if(ast.setup && ast.setup.type==jsdef.VAR && ast.setup.length>1)
				_this.NewError("Invalid multiple variable initializers in for.", ast);
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
			}

			out.push('"' + ast.value + '"');

			if(ast.value.indexOf("#include ")!=-1)
			{
				_this.includes.push('"' + ast.value + '";');
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
				/*
				if(ast[0].symbol.subtype && _this.isPointer(ast[0].symbol.subtype))
				{
					out.push("(function(o){if(!o) return;for(var i=o.length;i--;){o[i] && ((o[i].hasOwnProperty('Destructor') && o[i].Destructor()) || !o[i].hasOwnProperty('Destructor')) && (delete o[i]);o[i]=null;}})(" + expr + ");");
				}
				*/
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
		case jsdef.NEW:

			var gen = generate(ast[0]);

			if(ast[0].symbol && ast[0].symbol.struct)
			{
				var items = [];
				for(item in ast[0].symbol.vars)
					items.push(ast[0].symbol.vars[item].name + ":null");
				out.push("{" + items.join(",") + "}");
			}
			else
			{
				out.push("new " + gen);
				_this.checkFunctionCall(ast);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NEW_WITH_ARGS:

			var gen0 = generate(ast[0]);
			var gen1 = generate(ast[1]);

			if(ast[0].symbol && ast[0].symbol.struct)
			{
				if(ast[1][0].symbol.vartype==ast[0].symbol.name)
				{
					var items = []
					for(item in ast[0].symbol.vars)
					{
						var name = ast[0].symbol.vars[item].name;
						items.push(name + ":" + ast[1][0].value + "." + name);
					}
					out.push("{" + items.join(",") + "}");
				}
				else
				{
					_this.NewError("Invalid struct initialization: " + ast[0].symbol.name, ast[0]);
				}
			}
			else
			{
				out.push("new " +  gen0 + "(" + gen1 + ")");
				_this.checkFunctionCall(ast);
			}
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.SEMICOLON:
			var expr = (ast.expression ? generate(ast.expression) : "");
			if(_this.secondPass && ast.expression && ast.expression[0] && ast.expression[0].type==jsdef.SUPER && ast.expression[1].symbol && ast.expression[1].symbol.type==jsdef.FUNCTION)
			{
				var params = [];
				for(item in ast.inFunction.symbol.paramsList)
				{
					if(!isFinite(item)) break;
					var param = ast.inFunction.symbol.paramsList[item];
					params.push(param.name);
				}
				expr += "(" + params.join(",") + ")";
			}
			if(expr) out.push(expr + ";\n");
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.INSTANCEOF:
			if(_this.secondPass && _this.currClassName) _this.NewError("Illegal inside class", ast);
			out.push(generate(ast[0]));
			out.push(" instanceof ");
			out.push(generate(ast[1]));
			break;

		case jsdef.TYPEOF:
			if(_this.secondPass && _this.currClassName) _this.NewError("Illegal inside class", ast);
			out.push("typeof ");
			out.push(generate(ast[0]));
			break;

		case jsdef.VOID:
			if(_this.secondPass && _this.currClassName) _this.NewError("Illegal inside class", ast);
			out.push("void ");
			out.push(generate(ast[0]));
			break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.AND:					out.push(generate(ast[0])); out.push("&&"); out.push(generate(ast[1])); break;
		case jsdef.OR:					out.push(generate(ast[0])); out.push("||"); out.push(generate(ast[1]));	break;

		case jsdef.BITWISE_AND:			out.push(generate(ast[0])); out.push("&"); out.push(generate(ast[1])); _this.typeCheckItems(ast, ast[0], ast[1]); break;
		case jsdef.BITWISE_NOT:			out.push("~"); out.push(generate(ast[0])); _this.typeCheckItems(ast, ast[0], ast[1]); break;
		case jsdef.BITWISE_OR:			out.push(generate(ast[0])); out.push("|"); out.push(generate(ast[1])); _this.typeCheckItems(ast, ast[0], ast[1]); break;
		case jsdef.BITWISE_XOR:			out.push(generate(ast[0])); out.push("^"); out.push(generate(ast[1])); _this.typeCheckItems(ast, ast[0], ast[1]); break;

		case jsdef.EQ: 					out.push(generate(ast[0])); out.push("=="); out.push(generate(ast[1])); _this.typeCheckItems(ast, ast[0], ast[1]); break;
		case jsdef.STRICT_EQ:			out.push(generate(ast[0])); out.push("=="); out.push(generate(ast[1])); _this.typeCheckItems(ast, ast[0], ast[1]); break;
		case jsdef.STRICT_NE:			out.push(generate(ast[0]));	out.push("!="); out.push(generate(ast[1])); break;
		case jsdef.GE:					out.push(generate(ast[0])); out.push(">="); out.push(generate(ast[1])); break;
		case jsdef.GT:					out.push(generate(ast[0])); out.push(">");  out.push(generate(ast[1])); break;
		case jsdef.LE:					out.push(generate(ast[0])); out.push("<="); out.push(generate(ast[1])); break;
		case jsdef.LT:					out.push(generate(ast[0])); out.push("<");  out.push(generate(ast[1])); break;
		case jsdef.NE:					out.push(generate(ast[0])); out.push("!=");	out.push(generate(ast[1])); break;

		case jsdef.LSH:					out.push(generate(ast[0])); out.push("<<"); out.push(generate(ast[1])); break;
		case jsdef.RSH:					out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break;
		case jsdef.URSH:				out.push(generate(ast[0])); out.push(">>"); out.push(generate(ast[1])); break;
		case jsdef.EXPONENT:			out.push("Math.pow(" + generate(ast[0]) + "," + generate(ast[1]) + ")");break;
		case jsdef.DECREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("--"); } else { out.push("--"); out.push(generate(ast[0])); } break;
		case jsdef.INCREMENT:			if(ast.postfix) { out.push(generate(ast[0])); out.push("++"); } else { out.push("++"); out.push(generate(ast[0])); } break;
		case jsdef.HOOK:				out.push(generate(ast[0])); out.push("?"); out.push(generate(ast[1])); out.push(":"); out.push(generate(ast[2])); break;
		case jsdef.LABEL:				out.push(ast.label + ":"); out.push(generate(ast.statement)); break;
		case jsdef.NOT:					out.push("!"); out.push(generate(ast[0])); break;
		case jsdef.UNARY_MINUS:			out.push(" -"); out.push(generate(ast[0])); break;
		case jsdef.UNARY_PLUS:			out.push(" +"); out.push(generate(ast[0])); break;

		case jsdef.BREAK:				out.push("break;"); break;
		case jsdef.CASE:				out.push("case " + generate(ast.caseLabel) + ":"); out.push(generate(ast.statements)); break;
		case jsdef.CONTINUE:			out.push("continue;"); break;
		case jsdef.DEBUGGER:			out.push("debugger;"); break;
		case jsdef.DEFAULT:				out.push("default:"); out.push(generate(ast.statements)); break;
		case jsdef.DO: 					ast.body.isLoop = true; out.push("do"); out.push(generate(ast.body)); out.push("while(" + generate(ast.condition) + ");"); break;
		case jsdef.FALSE:				out.push("false"); break;
		case jsdef.TRUE:				out.push("true"); break;
		case jsdef.NULL:				out.push("null"); break;
		case jsdef.NUMBER:				out.push(ast.value); break;
		case jsdef.RETURN:				out.push("return"); if(ast.value) out.push(" " + generate(ast.value)); out.push(";\n"); break;
		case jsdef.THROW:				out.push("throw "); out.push(generate(ast.exception)); out.push(";"); break;
		case jsdef.WHILE:				ast.body.isLoop=true; out.push("while(" + generate(ast.condition) + ")"); out.push(generate(ast.body)); break;
		}
		return out.join("");
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.arithmeticOp = function(ast, op, out)
	{
		var g0 = _this.generate(ast[0]);
		var g1 = _this.generate(ast[1]);
		out.push(g0);
		out.push(op);
		out.push(g1);
	};
}
