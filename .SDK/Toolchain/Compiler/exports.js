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

// ==================================================================================================================================
//	   ______                _____           _       __     ______                      _ __
//	  / ____/___  _________ / ___/__________(_)___  / /_   / ____/___  ____ ___  ____  (_) /__  _____
//	 / /   / __ \/ ___/ __ \\__ \/ ___/ ___/ / __ \/ __/  / /   / __ \/ __ `__ \/ __ \/ / / _ \/ ___/
//	/ /___/ /_/ / /__/ /_/ /__/ / /__/ /  / / /_/ / /_   / /___/ /_/ / / / / / / /_/ / / /  __/ /
//	\____/\____/\___/\____/____/\___/_/  /_/ .___/\__/   \____/\____/_/ /_/ /_/ .___/_/_/\___/_/
//	                                      /_/                                /_/
// ==================================================================================================================================

function CompilerExportsPlugin(compiler)
{
	var _this = this._this = compiler;
	_this.debugSymbolsTable = [];           // Map of source code to runtime debug symbols, used by IDE debugger (eg. class foo { public var x; } , x at runtime is __CLASS_FOO__.x )

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// IDE icons that can be set to exported memberlist items in EXPORT_TO_IDE()
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
	function xtype(vartype)
	{
		return vartype.replace('<','&lt;').replace('>','&gt;');
	}

	// ==================================================================================================================================
	//	    ______                      __     ______              ________                   __    _      __
	//	   / ____/  ______  ____  _____/ /_   / ____/__    __     / ____/ /___ ___________   / /   (_)____/ /_
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /  __/ /___/ /_   / /   / / __ `/ ___/ ___/  / /   / / ___/ __/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /__/_  __/_  __/  / /___/ / /_/ (__  |__  )  / /___/ (__  ) /_
	//	/_____/_/|_/ .___/\____/_/   \__/   \____//_/   /_/     \____/_/\__,_/____/____/  /_____/_/____/\__/
	//	          /_/
	// ==================================================================================================================================

	_this.getNativeClassList = function()
	{
		var classes = [];
		for(item in _this.classes)
		{
			var cls = _this.classes[item];
			if(!cls.EXPORT_NATIVE) continue;
			if(cls.enum) continue;
			if(cls.struct)
				classes.push("struct " + cls.name + ";");
			else
				classes.push("class " + cls.name + ";");
		}
		classes = classes.sort().join("\n");
		return classes;
	};

	// ==================================================================================================================================
	//	    ______                      __     ______              _______ __
	//	   / ____/  ______  ____  _____/ /_   / ____/__    __     / ____(_) /__  _____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /  __/ /___/ /_   / /_  / / / _ \/ ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /__/_  __/_  __/  / __/ / / /  __(__  )
	//	/_____/_/|_/ .___/\____/_/   \__/   \____//_/   /_/    /_/   /_/_/\___/____/
	//	          /_/
	// ==================================================================================================================================

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.prepare_native_files = function()
	{
		_this.native_files 	= {};
		for(item in _this.classes)
		{
			var cls = _this.classes[item];
			if(!cls.EXPORT_NATIVE) continue;

			var native_file =
			{
						file: "",
						path: "",
						name: "",
						classes: {},
						cpp:
						{
							vartypes: {},
							includes: {},
							body:[],
							out: null
						},
						hpp:
						{
							vartypes: {},
							includes: {},
							body:[],
							out: null
						}
			};

			native_file.file = cls.file;
			native_file.path = cls.path;
			native_file.name = cls.file.replace(".jspp", "");
			_this.native_files[cls.file] = native_file;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.export_cpp_files = function()
	{
		// ==========================================================================================
		// Organize classes per native file
		// ==========================================================================================
		trace("+ Assembing source code in .cpp and .hpp files ...");
		for(item in _this.classes)
		{
			// Get class symbol
			var cls = _this.classes[item];
			if(!cls.EXPORT_NATIVE) continue;

			// Get source file node
			var native_file = _this.native_files[cls.file];

			// Place class in native file node
			native_file.classes[cls.name] = cls;

			// Associate native file node with class symbol
			_this.SET_METADATA(cls, "native_file", native_file);

			// Store native file node in native_files
			_this.native_files[cls.file] = native_file;
		}

		// ==========================================================================================
		// Process each native file node and collect vartypes
		// ==========================================================================================
		trace("+ Processing vartypes used in each .cpp and .hpp file ...");
		for(file in _this.native_files)
		{
			// Get a native file
			var native_file = _this.native_files[file];

			// Collect vartypes from all classes in the native file node
			for(item in native_file.classes)
			{
				var cls = native_file.classes[item];

				for(vartype in cls.vartypes)
				{
					var include = cls.vartypes[vartype];
					if(include & _this.INCLUDE_IN_CPP) native_file.cpp.vartypes[vartype] = true;
					if(include & _this.INCLUDE_IN_HPP) native_file.hpp.vartypes[vartype] = true;
				}
			}
		}

		// ==========================================================================================
		// Break cyclic-references between base and derivative classes
		// (C++ compiler error: base class has incomplete type)
		// ==========================================================================================
		trace("+ Breaking cyclic-references between base and derivative classes ...");
		for(file in _this.native_files)
		{
			// Get a native file
			var native_file = _this.native_files[file];

			// Collect vartypes from all classes in the native file node
			for(item in native_file.classes)
			{
				var base = native_file.classes[item];
				for(vartype in base.derivatives)
				{
					if(__exists(native_file.cpp.vartypes, vartype))
						delete native_file.cpp.vartypes[vartype];

					if(__exists(native_file.hpp.vartypes, vartype))
						delete native_file.hpp.vartypes[vartype];
				}
			}
		}

		// ==========================================================================================
		// At this point we have collected all the generated cpp and hpp code for each original file
		// and we know what vartypes each file needs. Now we need to resolve vartypes into includes.
		// ==========================================================================================
		trace("+ Resolving vartypes to #includes ...");
		for(file in _this.native_files)
		{
			// Get a native file
			var native_file = _this.native_files[file];

			// Standard includes for .hpp
			native_file.hpp.includes['#include "Coconut2D.hpp"'] = true;

			// Standard includes for .cpp
			native_file.cpp.includes['#include "' + native_file.name + '.hpp"'] = true;

			for(vartype in native_file.hpp.vartypes)
			{
				if(!__exists(native_file.classes, vartype))
				{
					// Find the .hpp file where this vartype is defined
					include = find_include_file_where_vartype_is_defined(vartype, native_file);
					if(include)	native_file.hpp.includes[include] = true;
				}
			}

			for(vartype in native_file.cpp.vartypes)
			{
				if(!__exists(native_file.classes, vartype))
				{
					// Find the .hpp file where this vartype is defined
					include = find_include_file_where_vartype_is_defined(vartype, native_file);
					if(include)	native_file.cpp.includes[include] = true;
				}
			}
		}

		// ==========================================================================================
		// At this stage we are ready to generate the .cpp and .hpp files
		// ==========================================================================================
		trace("+ Creating .cpp and .hpp files ...");
		for(file in _this.native_files)
		{
			// Get a native file
			var native_file = _this.native_files[file];

			// Create .hpp
			var tag = "__" + native_file.name.toUpperCase() + "_HPP__";
			var includes = []; for(include in native_file.hpp.includes) { includes.push(include); }
			native_file.hpp.out = "/* Generated by Coconut2D C++ Compiler from file " + native_file.file + " */\n\n" +
								  "#ifndef " + tag + "\n#define " + tag + "\n\n" +
			 					  _this.SEPARATOR + includes.join("\n") +
			 					  _this.SEPARATOR + native_file.hpp.body.join(_this.SEPARATOR) +
			 					  "\n#endif // " + tag + "\n";

			// Create .cpp
			var buff = native_file.cpp.body.join(_this.SEPARATOR);
			var includes = []; for(include in native_file.cpp.includes) { includes.push(include); }
			native_file.cpp.out = "/* Generated by Coconut2D C++ Compiler from file " + native_file.file + " */\n\n" +
			 					  _this.SEPARATOR + includes.join("\n") +
			 					  _this.SEPARATOR + native_file.cpp.body.join(_this.SEPARATOR);

			// Save .cpp and .hpp files
			IDECallback("module_hpp", native_file.path, 0, 0, native_file.hpp.out);
			IDECallback("module_cpp", native_file.path, 0, 0, native_file.cpp.out);
		}

		// ==========================================================================================
		function find_include_file_where_vartype_is_defined(vartype)
		{
			// Search for vartype in a generated file.
			for(file in _this.native_files)
			{
				var native_file = _this.native_files[file];
				if(__exists(native_file.classes, vartype))
				{
					// Return the file as #include directive
					return '#include "' + native_file.name + '.hpp"';
				}
			}

			// Vartype not found. Search for vartype in non-generated files.
			for(file in _this.native_vartypes_includes)
			{
				if(__exists(_this.native_vartypes_includes[file], vartype))
				{
					// Return the file as #include directive
					return '#include "' + file + '"';
				}
			}

			// Nasty hack for State.
			//TODO: Should change this with detection code
			if(vartype=="State") return null;

			// Vartype not found anywhere.
			for(item in native_file.classes){break;}
			_this.NewWarning("Class " + vartype + " is used by CRL. It must be moved inside a Framework.", native_file.classes[item].ast);
			return '#include "' + vartype + '.hpp"';
		}
	};

	// ==================================================================================================================================
	//	    ______                      __     ____       __                   _____                 __          __
	//	   / ____/  ______  ____  _____/ /_   / __ \___  / /_  __  ______ _   / ___/__  ______ ___  / /_  ____  / /____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / / / / _ \/ __ \/ / / / __ `/   \__ \/ / / / __ `__ \/ __ \/ __ \/ / ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /_/ /  __/ /_/ / /_/ / /_/ /   ___/ / /_/ / / / / / / /_/ / /_/ / (__  )
	//	/_____/_/|_/ .___/\____/_/   \__/  /_____/\___/_.___/\__,_/\__, /   /____/\__, /_/ /_/ /_/_.___/\____/_/____/
	//	          /_/                                             /____/         /____/
	// ==================================================================================================================================

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

	// ==================================================================================================================================
	//	    ______                      __     ______          __        _____                 __          __
	//	   / ____/  ______  ____  _____/ /_   / ____/___  ____/ /__     / ___/__  ______ ___  / /_  ____  / /____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /   / __ \/ __  / _ \    \__ \/ / / / __ `__ \/ __ \/ __ \/ / ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /___/ /_/ / /_/ /  __/   ___/ / /_/ / / / / / / /_/ / /_/ / (__  )
	//	/_____/_/|_/ .___/\____/_/   \__/   \____/\____/\__,_/\___/   /____/\__, /_/ /_/ /_/_.___/\____/_/____/
	//	          /_/                                                      /____/
	// ==================================================================================================================================

	_this.exportCodeSymbols = function()
	{
		var xml = ["<CODE_SYMBOLS" + (_this.selectedClass ? " update='" + _this.selectedClass + "'" : "") + ">\n"];

		for(var cls in _this.classes)
		{
			if(_this.selectedClass && _this.selectedClass!=cls) continue;
			var classSymbol = _this.classes[cls];
			xml.push(_this.objectToXML(classSymbol, classSymbol.name, false));

			xml.push("<METHODS>\n");
			for(var item in classSymbol.methods)
			{
				var methodSymbol = classSymbol.methods[item];
				if(!methodSymbol.name) continue;

				var arguments = [];
				for(var arg in methodSymbol.arguments)
				{
					arguments.push(_this.objectToXML(methodSymbol.arguments[arg], arg, true));
				}

				xml.push(_this.objectToXML(methodSymbol, "METHOD", arguments.length==0));

				if(arguments.length>0)
				{
					xml.push("<ARGUMENTS>\n");
					xml.push(arguments.join(""));
					xml.push("</ARGUMENTS>\n");
					xml.push("</METHOD>\n");
				}
			}
			xml.push("</METHODS>\n");

			xml.push("<VARS>\n");
			for(var item in classSymbol.vars)
			{
				xml.push(_this.objectToXML(classSymbol.vars[item], item, true));
			}
			xml.push("</VARS>\n");

			xml.push("</" + classSymbol.name + ">\n");
		}
		xml.push("</CODE_SYMBOLS>\n");
		return xml.join("");
	};

	// ==================================================================================================================================
	//	    ______                      __     ______     __
	//	   / ____/  ______  ____  _____/ /_   / ____/  __/ /____  _________  _____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / __/ | |/_/ __/ _ \/ ___/ __ \/ ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /____>  </ /_/  __/ /  / / / (__  )
	//	/_____/_/|_/ .___/\____/_/   \__/  /_____/_/|_|\__/\___/_/  /_/ /_/____/
	//	          /_/
	// ==================================================================================================================================

	_this.exportExterns = function()
	{
		var externs = ["// Auto-generated Project Externs\n\n"];
		for(var cls in _this.classes)
		{
			if(_this.selectedClass && _this.selectedClass!=cls) continue;
			var classSymbol = _this.classes[cls];
			externs.push("class "+ classSymbol.name + (classSymbol.base ? " : " + classSymbol.base : "") + "\n{\n");

			for(var item in classSymbol.methods)
			{
				var methodSymbol = classSymbol.methods[item];
				if(!methodSymbol.name) continue;

				var arguments = [];
				for(var arg in methodSymbol.arguments)
				{
					var argumentSymbol = methodSymbol.arguments[arg];
					arguments.push(argumentSymbol.name + (argumentSymbol.vartype ? ":" + argumentSymbol.vartype : ""));
				}

				var signature = methodSymbol.name + "(" + arguments.join(", ") + ")" + (methodSymbol.vartype ? " :" + methodSymbol.vartype : "");
				externs.push("\t" + methodSymbol.modifier + " function "+ signature + " {}\n");
			}

			for(var item in classSymbol.vars)
			{
				var varSymbol = classSymbol.vars[item];
				externs.push("\t" + varSymbol.modifier + " var " + varSymbol.name + (varSymbol.vartype ? " :"+ varSymbol.vartype : "") + ";\n");
			}

			externs.push("} //" + classSymbol.name + "\n\n");
		}
		return externs.join("");
	};

	// ==================================================================================================================================
	//	    ______                      __     __  ___               __                 __    _      __
	//	   / ____/  ______  ____  _____/ /_   /  |/  /__  ____ ___  / /_  ___  _____   / /   (_)____/ /______
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /|_/ / _ \/ __ `__ \/ __ \/ _ \/ ___/  / /   / / ___/ __/ ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /  / /  __/ / / / / / /_/ /  __/ /     / /___/ (__  ) /_(__  )
	//	/_____/_/|_/ .___/\____/_/   \__/  /_/  /_/\___/_/ /_/ /_/_.___/\___/_/     /_____/_/____/\__/____/
	//	          /_/
	// ==================================================================================================================================

	_this.exportMemberLists = function()
	{
		var mbrLists = [];
		for(var cls in _this.classes)
		{
			if(_this.selectedClass && _this.selectedClass!=cls) continue;
			var classSymbol = _this.classes[cls];
			var mbrList = ["<memberlist name='Class " + classSymbol.name + "'>"];

			for(var item in classSymbol.methods)
			{
				var methodSymbol = classSymbol.methods[item];
				if(!methodSymbol.name) continue;

				// XML-ize vartypes and remove overload $<index>
				var signature = xtype(methodSymbol.__signature).replace(/\$\d+/, "");
				var cnSignature = xtype(methodSymbol.__cnSignature).replace(/\$\d+/, "");

				mbrList.push('\t<member name="' + methodSymbol.name.replace(/\$\d+/, "") + '" proto="' + signature + '" help="' + cnSignature + '" image="' + methodSymbol.icon + '"/>');
			}

			for(var item in classSymbol.vars)
			{
				var varSymbol = classSymbol.vars[item];

				var signature = xtype(varSymbol.signature || (varSymbol.name + varSymbol.ast.vartype));
				mbrList.push('\t<member name="' + varSymbol.name + '" proto="' + signature + '" help="' + classSymbol.name + " :: " + signature + '" image="' + varSymbol.icon + '"/>');
			}

			mbrList.push("</memberlist>");
			mbrLists.push(mbrList.join("\n"));
		}

		mbrLists = "<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n<MEMBER_LISTS" +
				   (_this.selectedClass ? " update='" + _this.selectedClass + "'" : "") +">\n" +
				   mbrLists.join("\n") +
				   "</MEMBER_LISTS>";

		return mbrLists;
	};

	// ==================================================================================================================================
	//	    ______                      __     _____
	//	   / ____/  ______  ____  _____/ /_   / ___/_________  ____  ___  _____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/   \__ \/ ___/ __ \/ __ \/ _ \/ ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_    ___/ / /__/ /_/ / /_/ /  __(__  )
	//	/_____/_/|_/ .___/\____/_/   \__/   /____/\___/\____/ .___/\___/____/
	//	          /_/                                      /_/
	// ==================================================================================================================================

	_this.exportScopes = function()
	{
		var xml = [];
		xml.push("<SCOPES" + (_this.selectedClass ? " update='" + _this.selectedClass + "'" : "") + ">\n");
		for(var i=0;i<_this.scopesTable.length;i++)
		{
			var scope = _this.scopesTable[i];
			if(_this.selectedClass && _this.selectedClass!=scope.className) continue;

			var varsxml = [];

			for(var item in scope.vars)
			{
				var varSymbol = scope.vars[item];
				if(!varSymbol.name || !varSymbol.vartype) continue;
				varsxml.push("\t<SYMBOL symbolId='"+varSymbol.symbolId + "' name='" + varSymbol.name +
							 "' type='" + varSymbol.nodeType + "' vartype='" + xtype(varSymbol.vartype) +
							 "' subtype='" + (varSymbol.subtype ? varSymbol.subtype : "") + "'/>\n");
			}

			for(var item in scope.methods)
			{
				var methodSymbol = scope.methods[item];
				if(!methodSymbol.name) continue;
				varsxml.push("\t<SYMBOL symbolId='"+methodSymbol.symbolId + "' name='" + methodSymbol.name + "' type='" + methodSymbol.nodeType +
							 "' vartype='" + (!methodSymbol.vartype ? "" : xtype(methodSymbol.vartype)) +
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

		return xml.join("");
	};

	// ==================================================================================================================================
	//	    ______                      __     ___________ __  ___   _____ __        __
	//	   / ____/  ______  ____  _____/ /_   / ____/ ___//  |/  /  / ___// /_____ _/ /____  _____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /_   \__ \/ /|_/ /   \__ \/ __/ __ `/ __/ _ \/ ___/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / __/  ___/ / /  / /   ___/ / /_/ /_/ / /_/  __(__  )
	//	/_____/_/|_/ .___/\____/_/   \__/  /_/    /____/_/  /_/   /____/\__/\__,_/\__/\___/____/
	//	          /_/
	// ==================================================================================================================================

	_this.exportStates = function()
	{
		states = [];
		for(var item in _this.states)
		{
			states.push(item);
		}
		states = states.join(";");
	};

	// ==================================================================================================================================
	//	    ______                      __     ________                   ____  _
	//	   / ____/  ______  ____  _____/ /_   / ____/ /___ ___________   / __ \(_)___ _____ __________ _____ ___
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / /   / / __ `/ ___/ ___/  / / / / / __ `/ __ `/ ___/ __ `/ __ `__ \
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /___/ / /_/ (__  |__  )  / /_/ / / /_/ / /_/ / /  / /_/ / / / / / /
	//	/_____/_/|_/ .___/\____/_/   \__/   \____/_/\__,_/____/____/  /_____/_/\__,_/\__, /_/   \__,_/_/ /_/ /_/
	//	          /_/                                                               /____/
	// ==================================================================================================================================

	// Export Class Diagram information to NClass format.
	// Custom mobileFX NClass binary works with GraphViz in 3rd party tools folder and generates a PDF and SVG output.

	_this.exportClassDiagram = function(options)
	{
		var index=0, dx=0,dy=0;

		// Choose Class Diagram detail with options

		if(!options) options = {};

		if(undefined==options.export_generalizations) 	options.export_generalizations 	= true;
		if(undefined==options.export_dependencies) 		options.export_dependencies 	= true;

		if(undefined==options.export_public) 			options.export_public			= true;
		if(undefined==options.export_private) 			options.export_private			= true;
		if(undefined==options.export_protected) 		options.export_protected		= true;
		if(undefined==options.export_static) 			options.export_static			= true;

		if(undefined==options.export_methods) 			options.export_methods			= true;
		if(undefined==options.export_vars) 				options.export_vars				= true;
		if(undefined==options.export_consts) 			options.export_consts			= false;
		if(undefined==options.export_properties) 		options.export_properties		= true;
		if(undefined==options.export_states) 			options.export_states			= true;
		if(undefined==options.export_enums) 			options.export_enums			= true;

		var NClassXML = [];
		NClassXML.push("<Project>");
		NClassXML.push("<Name>Coconut2D</Name>");
  		NClassXML.push('<ProjectItem type="NClass.DiagramEditor.ClassDiagram.Diagram" assembly="NClass.DiagramEditor, Version=0.0.0.0, Culture=neutral, PublicKeyToken=null">');
  		NClassXML.push('<Name>Class Diagram</Name>');
    	NClassXML.push('<Language>CSharp</Language>');
    	NClassXML.push('<Entities>');

		// Export Classes
		for(var cls in _this.classes)
		{
			var classSymbol = _this.classes[cls];
			if(classSymbol.file=="externs.jspp") continue;
			if(classSymbol.enum && !options.export_enums) continue;

			classSymbol.index = index++;

			if(classSymbol.enum)
			{
				NClassXML.push('<Entity type="Enum">');
	      		NClassXML.push('<Name>' + classSymbol.name + '</Name>');
	        	NClassXML.push('<Access>Public</Access>');
	        	NClassXML.push('<Location left="' + (dx*220) + '" top="' + (dy*280) +'" />');
				NClassXML.push('<Size width="0" height="0" />');
	        	NClassXML.push('<Collapsed>False</Collapsed>');
			}
			else if(classSymbol.state)
			{
				NClassXML.push('<Entity type="Class">');
	      		NClassXML.push('<Name>' + classSymbol.name + '</Name>');
	        	NClassXML.push('<Access>Public</Access>');
	        	NClassXML.push('<Location left="' + (dx*220) + '" top="' + (dy*280) +'" />');
				NClassXML.push('<Size width="0" height="0" />');
	        	NClassXML.push('<Collapsed>False</Collapsed>');
	        	NClassXML.push('<Modifier>None</Modifier>');
			}
			else
			{
				NClassXML.push('<Entity type="Class">');
	      		NClassXML.push('<Name>' + classSymbol.name + '</Name>');
	        	NClassXML.push('<Access>Public</Access>');
	        	NClassXML.push('<Location left="' + (dx*220) + '" top="' + (dy*280) +'" />');
				NClassXML.push('<Size width="0" height="0" />');
	        	NClassXML.push('<Collapsed>False</Collapsed>');
	        	NClassXML.push('<Modifier>None</Modifier>');
			}
        	dx++;
        	if(dx>10) { dy++; dx=0 };

			if(options.export_methods && !classSymbol.enum)
			{
				for(var item in classSymbol.methods)
				{
					var methodSymbol = classSymbol.methods[item];
					if(!methodSymbol.name) continue;

					if(methodSymbol.public && !options.export_public) continue;
					if(methodSymbol.private && !options.export_private) continue;
					if(methodSymbol.protected && !options.export_protected) continue;
					if(methodSymbol.static && !options.export_static) continue;

					var NCArgs = [];
					for(var arg in methodSymbol.arguments)
					{
						var argumentSymbol = methodSymbol.arguments[arg];
						NCArgs.push(argumentSymbol.ast.vartype.replace("<", "&lt;").replace(">", "&gt;") + " " + argumentSymbol.name);
					}

					var sig = methodSymbol.modifier + " " + (methodSymbol.vartype ? methodSymbol.vartype.replace("<", "&lt;").replace(">", "&gt;") : "void") + " " + methodSymbol.name + "(" + NCArgs.join(", ") + ")";

					switch(methodSymbol.name)
					{
						case "Constructor":
							NClassXML.push('<Member type="Constructor">' + sig + '</Member>');
							break;

						case "Destructor":
							NClassXML.push('<Member type="Destructor">' + sig + '</Member>');
							break;

						default:
							NClassXML.push('<Member type="Method">' + sig + '</Member>');
							break;
					}
				}
			}

			if(options.export_vars)
			{
				for(var item in classSymbol.vars)
				{
					var varSymbol = classSymbol.vars[item];

					if(varSymbol.public && !options.export_public) continue;
					if(varSymbol.private && !options.export_private) continue;
					if(varSymbol.protected && !options.export_protected) continue;
					if(varSymbol.static && !options.export_static) continue;

					if(!classSymbol.enum && varSymbol.constant && !options.export_consts) continue;
					if(varSymbol.property && !options.export_properties) continue;
					if(varSymbol.state && !options.export_states) continue;

					switch(varSymbol.type)
					{
						case jsdef.PROPERTY:
							var sig = varSymbol.modifier + " " + varSymbol.vartype.replace("<", "&lt;").replace(">", "&gt;") + " " + varSymbol.name + " { get; set; }";
							NClassXML.push('<Member type="Property">' + sig + '</Member>');
							break;

						case jsdef.STATE:
							var sig = varSymbol.modifier + " State " + varSymbol.name;
							NClassXML.push('<Member type="Method">' + sig + '</Member>');
							break;

						case jsdef.IDENTIFIER:
							var value = !isNaN(parseFloat(varSymbol.value)) ? "0x"+parseFloat(varSymbol.value).toString(16) : varSymbol.value;
							var sig = varSymbol.modifier + " " + (varSymbol.constant ? "const " : "") + varSymbol.vartype.replace("<", "&lt;").replace(">", "&gt;") + " " + varSymbol.name + (varSymbol.constant ? " = " + value : "");
							NClassXML.push('<Member type="Field">' + sig + '</Member>');
							break;

						case jsdef.ENUM_ITEM:
							NClassXML.push("<Value>"+varSymbol.name+"</Value>");
							break;
					}
				}
			}

			NClassXML.push('</Entity>');
		}

		NClassXML.push('</Entities>');
		NClassXML.push('<Relationships>');

		// Export Generalization (inheritance) relations
		if(options.export_generalizations)
		{
			for(var cls in _this.classes)
			{
				var classSymbol = _this.classes[cls];
				if(classSymbol.file=="externs.jspp") continue;
				if(!classSymbol.baseSymbol || classSymbol.baseSymbol.index==undefined) continue;

				NClassXML.push('<Relationship type="Generalization" first="' + classSymbol.index + '" second="' + classSymbol.baseSymbol.index + '">');
				NClassXML.push('<StartOrientation>Vertical</StartOrientation>');
				NClassXML.push('<EndOrientation>Vertical</EndOrientation>');
				NClassXML.push('</Relationship>');
			}
		}

		// Export Dependency relations
		if(options.export_dependencies)
		{
			for(var cls in _this.classes)
			{
				var classSymbol = _this.classes[cls];
				if(classSymbol.file=="externs.jspp") continue;
				if(!classSymbol.baseSymbol || classSymbol.baseSymbol.index==undefined) continue;
				for(vartype in classSymbol.scope.vartypes)
				{
					var depends = _this.classes[vartype];
					if(!depends) continue;
					if(depends.file=="externs.jspp") continue;
					if(depends.index==undefined) continue;
					if(classSymbol.baseSymbol==depends) continue;

					NClassXML.push('<Relationship type="Dependency" first="' + classSymbol.index + '" second="' + depends.index + '">');
					NClassXML.push('<StartOrientation>Horizontal</StartOrientation>');
					NClassXML.push('<EndOrientation>Horizontal</EndOrientation>');
					NClassXML.push('</Relationship>');
				}
			}
		}

		NClassXML.push('</Relationships>');
		NClassXML.push('</ProjectItem>');
		NClassXML.push('</Project>');

		return NClassXML.join("\n");
	};

	// ==================================================================================================================================
	//	    ______                      __     ____                                        __        __  _
	//	   / ____/  ______  ____  _____/ /_   / __ \____  _______  ______ ___  ___  ____  / /_____ _/ /_(_)___  ____
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / / / / __ \/ ___/ / / / __ `__ \/ _ \/ __ \/ __/ __ `/ __/ / __ \/ __ \
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /_/ / /_/ / /__/ /_/ / / / / / /  __/ / / / /_/ /_/ / /_/ / /_/ / / / /
	//	/_____/_/|_/ .___/\____/_/   \__/  /_____/\____/\___/\__,_/_/ /_/ /_/\___/_/ /_/\__/\__,_/\__/_/\____/_/ /_/
	//	          /_/
	// ==================================================================================================================================

	_this.exportClassReferenceDoc = function()
	{
		var INDEX = [];

		for(var cls in _this.classes)
		{
			var HTML = [];
			var METHODS = [];
			var VARS = [];
			var CONSTS = [];
			var STATES = [];
			var PROPERTIES = [];

			var classSymbol = _this.classes[cls];
			if(classSymbol.file=="externs.jspp") continue;
			for(var item in classSymbol.methods)
			{
				var methodSymbol = classSymbol.methods[item];
				if(!methodSymbol.name) continue;
				for(var arg in methodSymbol.arguments)
				{
					var argumentSymbol = methodSymbol.arguments[arg];
				}

				//var recordset = __execSQL("D:\test.db", "select * from Help where topicID='" + methodSymbol.runtime +"'");

			}
			for(var item in classSymbol.vars)
			{
				var varSymbol = classSymbol.vars[item];
			}
		}
	};

	// ==================================================================================================================================
	//	    ______                      __     ______                        _____ __        __          __  ___           __    _
	//	   / ____/  ______  ____  _____/ /_   / ____/___ _____ ___  ___     / ___// /_____ _/ /____     /  |/  /___ ______/ /_  (_)___  ___
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / / __/ __ `/ __ `__ \/ _ \    \__ \/ __/ __ `/ __/ _ \   / /|_/ / __ `/ ___/ __ \/ / __ \/ _ \
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /_/ / /_/ / / / / / /  __/   ___/ / /_/ /_/ / /_/  __/  / /  / / /_/ / /__/ / / / / / / /  __/
	//	/_____/_/|_/ .___/\____/_/   \__/   \____/\__,_/_/ /_/ /_/\___/   /____/\__/\__,_/\__/\___/  /_/  /_/\__,_/\___/_/ /_/_/_/ /_/\___/
	//	          /_/
	// ==================================================================================================================================
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.exportGameStateMachine = function()
	{
		// States changes with two possible ways:
		//
		// 1. A state function (enter, exit, tick, paint) calls setNextState()
		//
		// 2. A state function (enter, exit, tick, paint) calls CocoScene.gotoAndPlay|Stop(<CocoTimeLabel>)
		//    and the animation hits a KeyFrame with an action that calls setNextState() or it simply sets
		//    the next state.
		//
		// We need to identify those two patterns in the source code in order to derive the state diagram.

		var states = {};
		var currState = null;

		_this.descend("findStates", _this.ast, function(node)
		{
			if(node.type!=jsdef.STATE) return;

			currState=node.symbol;
			states[currState.name] = currState;

			// Now that we are on a state, we need to descen on its enter,exit,tick,paint
			// and look for "setNextState()" or "CocoScene.gotoAndPlay|Stop(<CocoTimeLabel>)"

			for(var item in node.symbol.scope.methods)
			{
				var method = node.symbol.scope.methods[item];
				_this.descend("findStateChangeFunctions_"+currState.name, method.ast.body, function(node2)
				{
					if(!(node2.symbol && node2.type==jsdef.IDENTIFIER)) return;

					switch(node2.symbol.name)
					{
						//===================================================================================================
						case "setNextState":
							var nextState = null;
							_this.descend("findStateIdentifier_"+currState.name, getInner(node2), function(node3)
							{
								if(nextState) return;
								if(node3.type==jsdef.IDENTIFIER && node3.symbol.type==jsdef.STATE)
								{
									nextState = node3.symbol;
									return true;
								}
							});
							if(nextState)
							{
								states[nextState.name]=nextState;
								currState.nextStates[nextState.name] = nextState;
							}
							break;

						//===================================================================================================
						case "gotoAndPlayByName":
						case "gotoAndStopByName":

							if(!node2.inDot) break;
							var keyFrameIndex = -1;

							// This works only for string literals
							// eg. gotoAndPlayByName("labelName")
							// First we need to get the label name.

							var label = getInner(node2)[1][0].value;

							// We need to scan all derived CocoScene classes
							// and find a class that defines the label on
							// the root CocoClip.

							for(className in _this.classes)
							{
								// Get a class and check its base class
								var cls = _this.classes[className];
								if(cls.base == "CocoScene")
								{
									// Now we need to find the constructor because
									// animations are set by the automatic generated
									// code in constructor.

									var constructor = null;
									for(item in cls.methods)
									{
										if(item!="Constructor") continue;
										constructor = cls.methods[item].ast;
										break;
									}
									if(!constructor) continue;

									// We have to scan the constructor statements for
									// the exact statement "__root.addLabelEx(labelName)"
									// We need to resolve the labelName to a keyframeIndex.

									for(item in constructor.body)
									{
										if(!isFinite(item)) continue;
										var addLabelEx = constructor.body[item] && constructor.body[item].expression && constructor.body[item].expression.type==jsdef.CALL ? constructor.body[item].expression[0] : null;
										if(addLabelEx && addLabelEx.type==jsdef.DOT && addLabelEx.identifier_first.value=="__root" && addLabelEx.identifier_last.value=="addLabelEx" && addLabelEx.parent[1][1].value==label)
										{
											keyFrameIndex=addLabelEx.parent[1][0].value;
											break;
										}
									}
									if(keyFrameIndex==-1) continue;

									// Let us find all clips name "Actions".
									// On "Actions" clips we normally place
									// KeyFrames with either actions or states.

									var actionNodes = [];
									_this.descend("findStateIdentifier_"+currState.name+"_"+label, constructor.body, function(node3)
									{
										if(node3.type==jsdef.IDENTIFIER && node3.value=="__instanceName" && node3.inDot && node3.inDot.parent[1] && node3.inDot.parent[1].value.toLowerCase()=="actions")
										{
											actionNodes.push(node3.inDot.identifier_first.value);
										}
									});

									// We have a list of all Action clips. We need to scan them for
									// KeyFrames that execute actions or change states where frameIndex
									// is grater or equal to the frameIndex of the labelName above.
									// The pattern we are looking for is
									// <instance>.__timeline.addKeyFrameEx(<state>,<action>,labelKeyFrameIndex,...)

									for(i=actionNodes.length-1; i>=actionNodes.length-1; i--)
									{
										var nextState = null;
										var actionNode = actionNodes[i];
										_this.descend("findStateIdentifier_"+currState.name+"_"+label+"_"+actionNode, constructor.body, function(node3)
										{
											if(nextState) return;
											if(node3.type==jsdef.IDENTIFIER && node3.value=="addKeyFrameEx" && node3.inDot && node3.inDot.identifier_first.value==actionNode && node3.inDot.parent[1][2].value>=keyFrameIndex)
											{
												// We have successfully identifier a KeyFrame definition.
												// We now need to determine if this KeyFrame invokes an
												// action or if it sets a next state.

												// Get the list of parameters of this KeyFrame
												var list = node3.inDot.parent[1];

												// If the first parameter is set, it is a state.
												if(list[0].identifier_last)
												{
													var nextState = list[0].identifier_last.symbol;
													states[nextState.name]=nextState;
													currState.nextStates[nextState.name] = nextState;
												}

												// If the second parameter is set, it is an action
												// we don't "else" so that we can examine both possibilites.
												if(list[1].type==jsdef.FUNCTION)
												{
													var fn = list[1].symbol.ast;
													//debugger;
												}
											}
										});
									}
								}
							}
							break;

					} // switch(node2.symbol.name)

				}); // _this.descend("findStateChangeFunctions_"+currState.name,

			}//for(var item in node.symbol.scope.methods)

			return true;
		});

		function getInner(node)
		{
			if(node.inCall) return node.inCall;
			if(node.inDot && node.inDot.parent.type==jsdef.CALL) return node.inDot.parent;
		}

		// We have a list of states that have a list of nextStates
		// Lets create a GraphViz script.

		var GgraphViz = ["","digraph G {",
						 "graph [layout=\"dot\",fontname=\"helvetica\"];",
						 "overlap=false;",
						 "forcelabels=true;",
						 "rankdir=LR;",
						 "ranksep=2.0;",
						 "node [shape=circle,fontname=\"helvetica\",fontsize=8];"
						 ];

		var relations = {};
		var i=0;
		for(item in states)
		{
			var currState = states[item];
			if(currState.stateId) continue;
			currState.stateId = "S"+(i++);
			GgraphViz.push(currState.stateId + ' [label="' + currState.name.replace("STATE_", "").replace(/_/g, "\\n") + '"];');
		}
		for(item in states)
		{
			var currState = states[item];
			for(next in currState.nextStates)
			{
				var nextState = states[next];
				relations[currState.stateId + " -> " + nextState.stateId] = true;
			}
		}
		for(relation in relations)
		{
			GgraphViz.push(relation);
		}
		GgraphViz.push("}");

		return GgraphViz.join("\n");
	};

	// ==================================================================================================================================
	//	    ______                      __     __           ________  ______
	//	   / ____/  ______  ____  _____/ /_   / /_____     /  _/ __ \/ ____/
	//	  / __/ | |/_/ __ \/ __ \/ ___/ __/  / __/ __ \    / // / / / __/
	//	 / /____>  </ /_/ / /_/ / /  / /_   / /_/ /_/ /  _/ // /_/ / /___
	//	/_____/_/|_/ .___/\____/_/   \__/   \__/\____/  /___/_____/_____/
	//	          /_/
	// ==================================================================================================================================

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Export class, function and identifier symbols that are used during code editing by intelliSence.
	_this.EXPORT_TO_IDE = function()
	{
		if(!_this.exportSymbols) return;

		//=======================================================
		// Export symbols to various forms
		//=======================================================

		var debugSymbols = "<DEBUG_SYMBOLS>" + _this.debugSymbolsTable.join("") + "</DEBUG_SYMBOLS>";
		var codeSymbols  = _this.exportCodeSymbols();
		var scopeVars	 = _this.exportScopes();
		var mbrLists     = _this.exportMemberLists();
		var externs      = _this.exportExterns();
		var states		 = _this.exportStates();

		//var stateMachine = compiler.exportGameStateMachine();
		//trace(stateMachine);
		//var diagram = _this.exportClassDiagram();
		//write("D:/mobileFX/Projects/Software/Coconut/Projects/Coco.project/.SDK/Documentation/ClassDiagrams/Coconut2D.ncp", diagram);
		//var reference	 = _this.exportClassReferenceDoc();
        //write("C:/Users/Admin/Desktop/codeSymbols.xml", codeSymbols);
        //write("C:/Users/Admin/Desktop/scopes.xml", scopeVars);
        //write("C:/Users/Admin/Desktop/members.xml", mbrLists);
        //write("C:/Users/Admin/Desktop/debugSymbols.xml", debugSymbols);

		//=======================================================
		// Send exported data to IDE
		//=======================================================

		if(!_this.selectedClass)
			IDECallback("resetSymbols");

		IDECallback("setCodeSymbols", "", 0, 0, codeSymbols);
		IDECallback("setScopes", "", 0, 0, scopeVars);
		IDECallback("setMemberLists", "", 0, 0, mbrLists);
		IDECallback("setStates", "", 0, 0, states);

 		if(!_this.selectedClass)
		{
			IDECallback("setExterns", "", 0, 0, externs);
			IDECallback("setDebugSymbols", "", 0, 0, debugSymbols);
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.objectToXML = function(obj, tag, close, more)
	{
		var v, xml = [];
		xml.push("<"+tag);
		for(var item in obj)
		{
			if(item.charAt(0)=="_") continue;
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

	/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.genericExport = function()
	{
		for(var cls in _this.classes)
		{
			var classSymbol = _this.classes[cls];
			if(classSymbol.file=="externs.jspp") continue;
			for(var item in classSymbol.methods)
			{
				var methodSymbol = classSymbol.methods[item];
				if(!methodSymbol.name) continue;
				for(var arg in methodSymbol.arguments)
				{
					var argumentSymbol = methodSymbol.arguments[arg];
				}
			}
			for(var item in classSymbol.vars)
			{
				var varSymbol = classSymbol.vars[item];
			}
		}
	};
	*/

}