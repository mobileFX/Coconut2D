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

function CompilerTypeSystemPlugin(compiler)
{
	var _this = this._this = compiler;

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
			"__UNARY__"		: ["Boolean", "Number", "String", "Integer", "Float"],
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

		var subtype = /<(\w+)(?:\*)*>/.exec(vartype)[1];
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
		case jsdef.FUNCTION:		return ast.symbol.vartype;
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
				return type;
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
			if(ast.symbol.type==jsdef.FUNCTION && ast.parent.type==jsdef.LIST) return "Function"; //Function Pointer
			if(ast.symbol.type==jsdef.FUNCTION) return ast.symbol.vartype;
			return ast.symbol.vartype;

		//=============================================================================================================================
		case jsdef.CALL:
			// Typecasting?
			if(_this.getClass(ast[0].value)) return ast[0].value;
			return _this.getTypeName(ast[0]);

		//=============================================================================================================================
		case jsdef.INDEX:
			var vartype = _this.getTypeName(ast[0]);
		    var cls = _this.getClass(vartype);
		    if(cls && cls.subtype) return cls.subtype;
			var subtype = _this.getSubType(vartype);
			return subtype;

		//=============================================================================================================================
		case jsdef.DOT:
			var symbol = _this.LookupLastDotIdentifier(ast, _this.getCurrentScope());
			if(!symbol)
			{
				_this.NewError("Symbol not found: " + ast.source, ast);
				return null;
			}
			return symbol.vartype;
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
			}
		}

		if(fnSymbol  && fnSymbol instanceof _this.FunctionSymbol)
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
	_this.searchIncludesForVartype = function(className, vt)
	{
		var already_searched = {};

		function __searchIncludesForVartype(className, vt)
		{
			// ECMA or extern datatype?
			var vcls = _this.getClass(vt);
			if(!vcls) return false;
			if(vcls.file=="externs.jspp") return true;
			if(vcls.isEnum) return true;

			// Get class from include name
			var cls = _this.getClass(className);
			if(!cls) return false;
			if(cls.file=="externs.jspp") return true;

			// Relaxed check of cyclic references
			if(already_searched[className]) return false;
			already_searched[className] = true;

			// Process class includes for vt
			var found = false;
			var includes = cls.ast.includes;
			if(!includes) return false;
			for(i=0;i<includes.length;i++)
			{
				var include = /\x22\#include\s+([^\x22]+)\.\w+?\x22/g.exec(includes[i])[1];
				if(include==vt)
				{
					found=true;
					break;
				}
			}

		    // Deep search of includes
		    if(!found)
		    {
					for(i=0;i<includes.length;i++)
					{
						var include = /\x22\#include\s+([^\x22]+)\.\w+?\x22/g.exec(includes[i])[1];
						if(__searchIncludesForVartype(include, vt))
						{
							found=true;
							break;
						}
					}
		    }

			// Reference to vt not found in includes chain
			return found;
		}

		return __searchIncludesForVartype(className, vt);
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
			_this.NewError(customError || "Invalid Object to Number convertion: " + ast.source, ast);
			return type1;
		}

		// Integer
		if(type1=="Integer" && type2=="Number") return type1;
		if(type1=="Integer")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Integer convertion: " + ast.source, ast);
			return type1;
		};

		// Float
		if(type1=="Float" && type2=="Number") return type1;
        if(type1=="Float")
        {
        	if(checkOnly) return false;
        	_this.NewError(customError || "Invalid "+type2+" to Float convertion: " + ast.source, ast);
        	return type1;
        };

		// Time
		if(type1=="Time" && type2=="Number") return type1;
		if(type1=="Time")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Time convertion: " + ast.source, ast);
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
			_this.NewError(customError || "Invalid Number to Boolean convertion: " + ast.source, ast); return type1;
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

		// Inheritance and Interfaces
		if(_this.classTypeCheck(cls1, cls2, ast))
			return type1;

		if(checkOnly) return false;
		_this.NewError(customError || "Type mismatch " + type1 + " and " + type2 + ": " + ast.source, ast);
		return type1;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Check two types if they are binary compatible
	_this.classTypeCheck = function(cls1, cls2, ast)
	{
		if(!cls1 || !cls2) return;

		// Check class inheritance
		if(cls1.type==jsdef.CLASS && cls2.type==jsdef.CLASS)
		{
			for(var base=cls2;base!=null;base=base.baseSymbol)
			{
				if(base.name==cls1.name)
					return cls1.name;
			}
		}

		// Check interface inheritance
		if(cls1.type==jsdef.INTERFACE && cls2.type==jsdef.INTERFACE)
		{
			for(var base=cls1;base!=null;base=base.baseSymbol)
			{
				if(base.name==cls2.name)
					return cls2.name;
			}
			for(var base=cls2;base!=null;base=base.baseSymbol)
			{
				if(base.name==cls1.name)
					return cls1.name;
			}
		}

		// Check class casting to interface
		if(cls1.type==jsdef.INTERFACE && cls2.type==jsdef.CLASS)
		{
			for(i=0;i<cls2.interfaces.length;i++)
			{
				var ic = _this.getClass(cls2.interfaces[i]);
				if(_this.classTypeCheck(cls1, ic, ast))
					return cls1.name;
			}
		}

		// Check casting interface to class
		if(cls1.type==jsdef.CLASS && cls2.type==jsdef.INTERFACE)
		{
			_this.NewError("Ambiguous casting of interface to class", ast);
		}
	}
}
