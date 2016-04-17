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
//	  ______                    _____            __
//	 /_  __/_  ______  ___     / ___/__  _______/ /____  ____ ___
//	  / / / / / / __ \/ _ \    \__ \/ / / / ___/ __/ _ \/ __ `__ \
//	 / / / /_/ / /_/ /  __/   ___/ / /_/ (__  ) /_/  __/ / / / / /
//	/_/  \__, / .___/\___/   /____/\__, /____/\__/\___/_/ /_/ /_/
//	    /____/_/                  /____/
// ==================================================================================================================================

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function CompilerTypeSystemPlugin(compiler)
{
	var _this = this._this = compiler;

	_this.warn_explicit_typecast = false;

	_this.RX_STRING_LETERAL = /^\x22(?!\x22)(?:\\.|[^\x22])*\x22|\x27(?!\x27)(?:\\.|[^\x27])*\x27|([\x27\x22]{3})((?:(?!\1)[\s\S])*)\1|\x22\x22|\x27\x27$/;
	_this.RX_INTEGER = /^[+-]?\d+$/;
	_this.RX_FLOAT = /^[+-]?\d+\.\d+$/;
	_this.RX_PARTIAL_FLOAT = /^[+-]?\d+\./;
	_this.RX_NUMERIC_LITERAL = /^(?:0[xX][0-9a-fA-F]+)|(?:\d+(?:\.\d+){0,1}[fd]{0,1})$/;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.types =
	{
		"Array"		: { "default": "null" },
		"Boolean"	: { "default": "false" },
		"Date"		: {	"default": "null" },
		"Function"	: {	"default": "null" },
		"Null"		: { "default": "null" },
		"Number"	: {	"default": "0" },
		"Float"		: { "default": "0.0" },
		"Time"		: { "default": "0.0" },
		"Integer"	: { "default": "0" },
		"Object"	: { "default": "null" },
		"RegExp"	: { "default": "null" },
		"String"	: { "default": '""' }
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typerules =
	{
		explicit:
		{
			"__UNARY__"		: ["Boolean", "Number", "String", "Integer", "Float", "Time"],
			"Array"			: [],
			"Boolean"		: ["Number", "String"],
			"Date"			: ["Number", "String"],
			"Function"		: ["String"],
			"null"			: [],
			"Number"		: ["Boolean", "String"],
			"Integer"		: ["Boolean", "Integer", "Float", "Time", "Color" ],
			"Float"			: ["Number", "Integer" ],
			"Object"		: [],
			"RegExp"		: ["Boolean", "Date", "Number", "String"],
			"String"		: ["Boolean", "Date", "Function", "Number", "RegExp"]
		},

		implicit:
		{
			ASSIGN:
			{
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Integer",
							"Time"		: "Integer",
							"Color"		: "Integer"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float",
							"Time"		: "Float",
							"Color"		: "Float"
						},
				"Time":
						{
							"Number"	: "Time",
							"Integer"	: "Time",
							"Float"		: "Time",
							"Time"		: "Time",
						},
				"Color":
						{
							"Number"	: "Color",
							"Integer"	: "Color",
							"Color"		: "Color",
							"Float"		: "Color"
						},
				"String":
						{
							"String"	: "String",
							"Integer"	: "String",
							"Float"		: "String",
							"Color"		: "String",
							"Time"		: "String"
						}
			},
			PLUS:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time",
							"Color"		: "Color"

						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time",
							"Color"		: "Color"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float",
							"Time"		: "Float",
							"Color"		: "Float"
						},
				"Time":
						{
							"Number"	: "Time",
							"Integer"	: "Time",
							"Float"		: "Time",
							"Time"		: "Time",
						},

				"Color":
						{
							"Number"	: "Color",
							"Integer"	: "Color",
							"Color"		: "Color"
						},
				"String":
						{
							"String"	: "String"
						}
			},

			MINUS:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time",
							"Color"		: "Color"

						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time",
							"Color"		: "Color"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float",
							"Time"		: "Float",
							"Color"		: "Float"
						},
				"Time":
						{
							"Number"	: "Time",
							"Integer"	: "Time",
							"Float"		: "Time",
							"Time"		: "Time",
						},

				"Color":
						{
							"Number"	: "Color",
							"Integer"	: "Color",
							"Color"		: "Color"
						},
				"String":
						{
							"String"	: "String"
						}
			},

			MUL:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time",
							"Color"		: "Color"

						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time",
							"Color"		: "Color"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float",
							"Time"		: "Float",
							"Color"		: "Float"
						},
				"Time":
						{
							"Number"	: "Time",
							"Integer"	: "Time",
							"Float"		: "Time",
							"Time"		: "Time",
						},

				"Color":
						{
							"Number"	: "Color",
							"Integer"	: "Color",
							"Color"		: "Color"
						},
				"String":
						{
							"String"	: "String"
						}
			},

			DIV:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time"
						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float",
							"Time"		: "Time"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float",
							"Time"		: "Float"
						},
				"Time":
						{
							"Number"	: "Time",
							"Integer"	: "Time",
							"Float"		: "Time",
							"Time"		: "Time"
						}
			},

			MOD: {},
			BIT:
			{
				"Boolean":
				{
					"Boolean": "Number",
					"Number": "Number"
				},
				"Number":
				{
					"Boolean": "Number",
					"Number": "Number"
				}
			}
		} // implicit
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.record_vartype_use = function(ast, symbol, parentScope, include)
	{
		if(!_this.secondPass || !symbol || !parentScope)
			return;

		// Get the vartype or subtype if defined.
		var subtype = _this.getSubType(symbol.returntype || symbol.vartype) || symbol.subtype;
		var vartype = subtype || symbol.vartype;
		if(!vartype) return;

		// We do not deal with scalar datatypes unless they are enums
		if(!_this.isEnum(vartype) && !_this.isPointer(vartype))
			return;

		// We skip ECMA types
		if(_this.isECMA(vartype))
			return;

		if(vartype == "CocoDataset" && parentScope.file == "CocoDataField.jspp") include = 1;

		// Record vartype usage
		if(!__exists(parentScope.vartypes, vartype))
			parentScope.vartypes[vartype] = include;
		else
			parentScope.vartypes[vartype] |= include;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isPointer = function (vartype)
	{
		if(!vartype)
			return false;

		vartype = _this.getVarType(vartype.trim());

		switch(vartype)
		{
		case "Class":
		case "Boolean":
		case "Number":
		case "String":
		case "Integer":
		case "Float":
		case "Time":
		case "Color":
		case "Gradient":
		case "void":
		case "undefined":
		case "null":
		case "CocoAction":
		case "int8_t":
		case "int16_t":
		case "int32_t":
		case "int64_t":
		case "uint8_t":
		case "uint16_t":
		case "uint32_t":
		case "uint64_t":

			return false;

		default:
			return !_this.isEnum(vartype);
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isEnum  = function(vartype)
	{
		var cls = _this.classes[vartype];
		return cls && cls.enum ? true : false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isECMA = function(vartype)
	{
		if(!vartype) return false;

		switch(vartype)
		{
		case "Object":
		case "Global":
		case "Array":
		case "Function":

		case "String":
		case "Boolean":
		case "Number":
		case "Date":
		case "Math":
		case "RegExp":

		case "Error":
		case "EvalError":
		case "RangeError":
		case "ReferenceError":
		case "SyntaxError":
		case "TypeError":

		//case "XMLHttpRequest": We exclude XMLHttpRequest because it is implemented inside a Framework and not in Common

		case "ArrayBuffer":
		case "ArrayBufferView":
		case "DataView":
		case "Int8Array":
		case "Int16Array":
		case "Int32Array":
		case "Int64Array":
		case "Uint8Array":
		case "Uint16Array":
		case "Uint32Array":
		case "Uint64Array":
		case "Float32Array":
		case "Float64Array":

			return true;
		}

		return false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isTypedArray = function(vartype)
	{
		if(!vartype)
			return false;

		switch(vartype)
		{
		case "ArrayBuffer":
		case "ArrayBufferView":
		case "Int8Array":
		case "Int16Array":
		case "Int32Array":
		case "Int64Array":
		case "Uint8Array":
		case "Uint16Array":
		case "Uint32Array":
		case "Uint64Array":
		case "Float32Array":
		case "Float64Array":
			return true;
		}
		return false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isVector = function(vartype)
	{
		if(!vartype) return false;
		if(vartype.indexOf("<")!=-1) return true;

		if(_this.isDerivativeOf(vartype, "Array"))
			return true;

		return false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isNumber = function(vartype)
	{
		switch(vartype)
		{
		case 'Number':
		case 'Float':
		case 'Integer':
		case 'Color':
		case 'Time':
		case 'int8_t':
		case 'int16_t':
		case 'int32_t':
		case 'int64_t':
		case 'uint8_t':
		case 'uint16_t':
		case 'uint32_t':
		case 'uint64_t':
			return true;
		}

		if(_this.isEnum(vartype))
			return true;

		return false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getVarType = function(vartype)
	{
		if(!vartype) return null;
		if(vartype.charAt(vartype.length-1)!='>') return vartype;
		vartype = vartype.substr(0, vartype.indexOf('<'));
		return vartype;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typeOf = function(value)
	{
		if(Array.isArray(value)) return "Array";
		switch(typeof(value))
		{
		case "string": return "String";
		case "number": return "Number";
		case "boolean": return "Boolean";
		default:
			return "Object";
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getDefaultVartypeValue = function(vartype)
	{
		if(!vartype) return null;
		if(vartype=="Time") return "0";
		if(__exists(_this.types, vartype) && __exists(_this.types[vartype], "default"))
			return _this.types[vartype].default;
		var cls = _this.getClass(vartype);
		if(!cls) return null;
		if(cls.enum)
		{
			for(item in cls.vars)
			{
				return cls.vars[item].value;
			}
		}
		return null;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getDefaultVartypeValueCPP = function(vartype)
	{
		if(_this.isEnum(vartype))
		{
			var cls = _this.getClass(vartype);
			return vartype + "(0)";
		}

		var v = _this.getDefaultVartypeValue(vartype);
		if(v==null || v=="null") return "nullptr";
		return v;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// For typed arrays (eg. Array<Integer>, Array<String>, Array<MyClass> return subtype.
	_this.getSubType = function(vartype)
	{
		if(!vartype) return null;

		switch(vartype)
		{
		case "Array":			return "Object";
		case "ArrayBuffer":		return "Number";
		case "ArrayBufferView":	return "Number";

		case "Int8Array":		return "int8_t";
		case "Int16Array":		return "int16_t";
		case "Int32Array":		return "Integer";
		case "Int64Array":		return "int64_t";
		case "Uint8Array":		return "uint8_t";
		case "Uint16Array":		return "uint16_t";
		case "Uint32Array":		return "uint32_t";
		case "Uint64Array":		return "uint64_t";
		case "Float32Array":	return "Float";
		case "Float64Array":	return "Float";
		}

		if(vartype.charAt(vartype.length-1)!='>') return null;
		var subtype = /<(\w+)(?:\*)*>/.exec(vartype)[1];
		return subtype;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.VTCPP = function(vartype, jsdef_NEW)
	{
		if(!vartype) return "void ";

		if(_this.isTypedArray(vartype))
			return vartype+(jsdef_NEW?"":"*");

		var v = _this.getVarType(vartype);
		var s = _this.getSubType(vartype);

		if(s && _this.isPointer(s))
			s += "*";

		v = v + (s ? "<"+s+">" : "");

		if(!jsdef_NEW)
			v += (_this.isPointer(v) || s!=null ? "* " :" ");

		return v;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.VALUECPP = function(v, subtype)
	{
		if(subtype=="Float" && !isNaN(parseFloat(v)) && v.indexOf('.')==-1)
			return v + ".0f";

		return v;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.jsdef_to_type = function(ast)
	{
		     if (ast.type == jsdef.PLUS) 			return "PLUS";
		else if (ast.type == jsdef.MINUS) 			return "MINUS";
		else if (ast.type == jsdef.MUL) 			return "MUL";
		else if (ast.type == jsdef.DIV) 			return "DIV";
		else if (ast.type == jsdef.MOD) 			return "MOD";
		else if (ast.type == jsdef.BITWISE_AND) 	return "BITWISE_AND";
		else if (ast.type == jsdef.BITWISE_OR) 		return "BITWISE_OR";
		else if (ast.type == jsdef.BITWISE_XOR) 	return "BITWISE_XOR";
		else if (ast.type == jsdef.LSH) 			return "LSH";
		else if (ast.type == jsdef.RSH) 			return "RSH";
		else if (ast.type == jsdef.URSH) 			return "URSH";

		return "UNKNOWN";
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getTypeName = function(ast)
	{
		if(!_this.secondPass || !ast) return;
		//if(!_this.secondPass || !_this.currClassName || !ast) return;
		return (ast.vartype ? ast.vartype : (ast.vartype = _this.getTypeNameResolver(ast)));
	};

	_this.getTypeNameResolver = function(ast)
	{
		var _this = this;

		switch(ast.type)
		{
		//=============================================================================================================================
		case jsdef.ARRAY_INIT:		return "Array";
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
		case jsdef.NOT:             return "Boolean";
		case jsdef.NULL:			return "Null";
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

		case jsdef.NUMBER:

			if(_this.RX_INTEGER.test(ast.value))
				return "Integer";

			if(_this.RX_FLOAT.test(ast.value))
				return "Float";

			return "Number";

		case jsdef.FUNCTION:
			return ast.symbol.vartype || "Function";


		//=============================================================================================================================
		case jsdef.NEW:
		case jsdef.NEW_WITH_ARGS:

			if(!ast[0].symbol) ast[0].symbol = _this.LookupIdentifier(ast.inFunction.scope, ast[0].value, ast[0], true);
			if(!ast[0].symbol)
			{
				_this.NewError("Symbol not found: " + ast[0].value, ast[0]);
				return null;
			}
			return ast[0].symbol.name;

		//=============================================================================================================================
		case jsdef.PLUS:
		case jsdef.MINUS:
		case jsdef.MUL:
		case jsdef.DIV:
		case jsdef.MOD:

			var op = _this.jsdef_to_type(ast);
			var operation = this.typerules.implicit[op];
			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);

			if(operation[type1])
			{
				if(operation[type1].hasOwnProperty(type2))
					return operation[type1][type2];
				else
					return _this.typeCheck(ast, type1, type2);
			}

			return _this.typeCheck(ast, type1, type2, "Illegal operation " + op + " on: " + type1 + " and " + type2);

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
				else
					_this.typeCheck(ast, type, "Number");
			}
			return type;

		//=============================================================================================================================
		case jsdef.BITWISE_AND:
		case jsdef.BITWISE_OR:
		case jsdef.BITWISE_XOR:
		case jsdef.LSH:
		case jsdef.RSH:
		case jsdef.URSH:

			var op = _this.jsdef_to_type(ast);
			var operation = this.typerules.implicit.BIT;
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

			// Maybe the identifier is not recognized yet; attempt to recognize it.
			if(!ast.symbol)
			{
				ast.symbol = _this.LookupIdentifier(_this.getCurrentScope(), ast.value, ast);
				if(!ast.symbol)
					return _this.UNTYPED;
			}

			if(ast.symbol.type==jsdef.FUNCTION && ast.parent.type==jsdef.LIST)
			{
				return ast.symbol.callback || "Function";  //Function Pointer
			}

			if(ast.symbol.type==jsdef.FUNCTION) return ast.symbol.vartype;
			return ast.symbol.vartype;

		//=============================================================================================================================
		case jsdef.CALL:
			// Typecasting?
			if(_this.getClass(ast[0].value)) return ast[0].value;
			return _this.getTypeName(ast[0]);

		case jsdef.LIST:
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
			var symbol = ast.identifier_last.symbol || _this.LookupLastDotIdentifier(ast, _this.getCurrentScope());
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
			fnSymbol = ast[0] && ast[0].symbol && ast[0].symbol.methods ? ast[0].symbol.methods['Constructor'] : null;
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

		_this.checkFunctionSignature(ast, fnSymbol);

		return fnSymbol;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.checkFunctionSignature = function(ast, fnSymbol)
	{
		if(!(fnSymbol  && fnSymbol instanceof _this.FunctionSymbol))
			return;

		var i=0, item, arg, param, type1, type2;

		if(ast[1] && ast[1].length>fnSymbol.paramsList.length && !fnSymbol.restArguments)
			_this.NewError("Too many arguments: " + ast.source, ast);

		for(item in fnSymbol.arguments)
		{
			arg = fnSymbol.arguments[item];
			type1 = arg.vartype;

			if(ast[1] && i<ast[1].length)
			{
				var arg_ast = ast[1][i];

				// Lookup constructor argument
				if(ast.type==jsdef.CONSTRUCTOR_CALL && !arg_ast.symbol)
				{
					arg_ast.symbol = _this.LookupIdentifier(fnSymbol.scope, arg_ast.value, arg_ast, true);
				}

				type2 = _this.getTypeName(arg_ast);
				_this.typeCheck(arg_ast, type1, type2, "Argument type mismatch: "+type1+" and "+type2 + " at " + arg_ast.source);
			}
			else if(!arg.optional)
			{
				_this.NewError("Argument not optional: " + ast.source, ast);
			}
			i++;
		}
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.compareMethodSignatures = function(methodSymbol, baseMethodSymbol, strict)
	{
		if(!_this.secondPass)
			return true;

		if(methodSymbol.paramsList.length!=baseMethodSymbol.paramsList.length)
			return false;

		for(var i=0;i<methodSymbol.paramsList.length;i++)
		{
			var type1 = baseMethodSymbol.paramsList[i].vartype;
			var type2 = methodSymbol.paramsList[i].vartype;

			if(strict && type1!=type2)
				return false;

			if(!_this.typeCheck(methodSymbol.paramsList[i].ast, type1, type2, null, true))
			{
				// Types are incompatible
				return false;
			}
		}

		return true;
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
			if(vcls.enum) return true;

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
	_this.typeCheckItems = function(ast, ast0, ast1, strictNumbers)
	{
		if(strictNumbers==null)
			strictNumbers = true;

		var type1 = _this.getTypeName(ast0);
		var type2 = _this.getTypeName(ast1);
		_this.typeCheck(ast, type1, type2, null, null, strictNumbers);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typeCheck = function(ast, _type1, _type2, customError, checkOnly, strictNumbers)
	{
		//** Need to rewrite using Roger's convertion tables

		var _this = this;
		if(!_this.currClassName || !_this.secondPass) return;

		// Fast type checking
		if(_type1==_type2) return _type1;

		// Resolve vartype and subtypes
		var type1  = _this.getVarType(_type1);
		var type2  = _this.getVarType(_type2);
		var stype1 = _this.getSubType(_type1);
		var stype2 = _this.getSubType(_type2);

		// Direct match?
		if(type1==type2 && stype1==stype2)
			return type1;

		// Arrays?
		if(type1==type2 && stype1!=stype2)
		{
			if(!_this.isDerivativeOf(type1, "Array"))
				_this.NewError("Class is not an Array derivative: " + _type1, ast);

			if(!_this.isDerivativeOf(type2, "Array"))
				_this.NewError("Class is not an Array derivative: " + _type2, ast);

			// Nasty hack for arrays used by ECMA objects
			if(stype1=="Object")
				return type2;

 			if(stype2=="Object")
 				return type1;

			// Subtypes must have inheritance relation
 			if(!_this.isDerivativeOf(stype1, stype2))
				_this.NewError(customError || "Cannot convert " + _type2 + " to " + _type1 + ": " + (ast[0] ? ast[0] : ast).source, ast);

			return _type1;
		}

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
		if((_this.isPointer(type1) || type1 == "CocoAction") && type2=="Null") return type1;
		if(type1 == "CocoAction" && type2 == "Function") return type1;

  		// Object
		if(type1=="Object") return type1;

		if(type1!="Object" && type2=="Object")
		{
			//_this.NewError("Please type-cast to " + type1 + ": " + ast.source, ast);
			return type1;
		}

		if(!strictNumbers && _this.isNumber(type1) && _this.isNumber(type2))
			return type1;

		// Number
		if(type1=="Number" && type2=="Integer") return type1;
		if(type1=="Number" && type2=="Float") return type1;
		if(type1=="Number" && type2=="Time") return type1;
		if(type1=="Number" && type2=="Color") return type1;
		if(type1=="Number" && type2=="Object")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid Object to Number convertion: " + ast.source, ast);
			return type1;
		}

		// Integer
		if(type1=="Integer" && type2=="Number") return type1;
		if(type1=="Integer" && type2=="Color") return type1;
		if(type1=="Integer")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Integer convertion: " + ast.source, ast);
			return type1;
		}

		// Float
		if(type1=="Float" && type2=="Number") return type1;
        if(type1=="Float")
        {
        	if(checkOnly) return false;
        	_this.NewError(customError || "Invalid "+type2+" to Float convertion: " + ast.source, ast);
        	return type1;
        }

		// Time
		if(type1=="Time" && type2=="Number") return type1;
		if(type1=="Time")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Time convertion: " + ast.source, ast);
			return type1;
		}

		// Color
		if(type1=="Color" && type2=="Number") return type1;
		if(type1=="Color" && type2=="Integer") return type1;
		if(type1=="Color")
		{
			if(checkOnly) return false;
			_this.NewError(customError || "Invalid "+type2+" to Color convertion: " + ast.source, ast);
			return type1;
		}
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

		// JSON support: typecast from Dictionary or Object to a Struct
		if(cls1.struct && (cls2.name=="Dictionary" || cls2.name=="Object"))
		{
			return type1;
		}
		if(cls2.struct && (cls1.name=="Dictionary" || cls1.name=="Object"))
		{
			return type1;
		}

		// Callbacks (need to check better)
		if(cls1.callback && cls2.vartype=="Function")
		{
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

		// Casting function to callback signature
		if(cls1.callback)
		{
			if(ast.symbol && ast.symbol.__typedParamsList && ast.symbol.__typedParamsList==cls1.__typedParamsList)
				return cls1.name;

			_this.NewError("Callback type mismatch " + cls1.name + " and " + cls2.name + ": " + ast.source, ast);
			return cls1.name;
		}

		// Check class inheritance
		if(!cls1.interface && !cls2.interface)
		{
			for(var base=cls2;base!=null;base=base.baseSymbol)
			{
				if(base.name==cls1.name)
					return cls1.name;
			}

			// This should be allowed but it might produce runtime error.
			for(var base=cls1;base!=null;base=base.baseSymbol)
			{
				if(base.name==cls2.name)
				{
					if(!ast.__typecast_explicit)
					{
						if(cls2.name=="HTMLElement" || cls1.name=="HTMLElement" || cls1.name=="Gradient" || cls2.name=="Gradient")
						{
							return cls1.name;
						}
						else
						{
							_this.NewWarning("Possible runtime error converting from " + cls2.name + " to " + cls1.name + ": " + ast.parent.source, ast);
						}
					}

					return cls2.name;
				}
			}
		}

		// Check interface inheritance
		if(cls1.interface && cls2.interface)
		{
			for(var base=cls2;base!=null;base=base.baseSymbol)
			{
				if(base.name==cls1.name)
					return cls1.name;
			}
		}

		// Check class casting to interface
		if(cls1.interface && !cls2.interface)
		{
			for(i=0;i<cls2.interfaces.length;i++)
			{
				var ic = _this.getClass(cls2.interfaces[i]);
				if(_this.classTypeCheck(cls1, ic, ast))
					return cls1.name;
			}
		}

		// Check casting interface to class
		if(!cls1.interface && cls2.interface)
		{
			if(!ast.__typecast_explicit)
				_this.NewError("Ambiguous casting of interface to class", ast);
			else
				return cls1.name;
		}
	};

	// ==================================================================================================================================
	//	  ______                    ______           __  _
	//	 /_  __/_  ______  ___     / ____/___ ______/ /_(_)___  ____ _
	//	  / / / / / / __ \/ _ \   / /   / __ `/ ___/ __/ / __ \/ __ `/
	//	 / / / /_/ / /_/ /  __/  / /___/ /_/ (__  ) /_/ / / / / /_/ /
	//	/_/  \__, / .___/\___/   \____/\__,_/____/\__/_/_/ /_/\__, /
	//	    /____/_/                                         /____/
	// ==================================================================================================================================

	_this.typeCast = function(ast, gen)
	{
		if(ast.file=="extern.jspp")
			return gen;

		var old = gen = gen.trim();

		var vartype = _this.getTypeName(ast);

		//===============================================================================
		if(ast.__typecast == "CocoAction")
		{
			//TODO
			return gen;
		}

		//===============================================================================
		function __cast_to_float()
		{
			vartype = "Float";

			// integer literal to float
			if(_this.RX_INTEGER.test(gen) && !isNaN(gen))
			{
				gen = gen + ".0";
				return;
			}
		}

		//===============================================================================
		function __cast_to_integer()
		{
			vartype = "Integer";

			/// integer literal to color
			if(ast.__typecast=="Color" && _this.RX_INTEGER.test(gen) && !isNaN(gen))
			{
				gen = "0x" + parseInt(gen).toString(16);
				return;
			}

			// integer literal to integer, pass...
			if(_this.RX_INTEGER.test(gen) && !isNaN(gen)) return;

			// float literal to integer
			if(_this.RX_PARTIAL_FLOAT.test(gen) && !isNaN(Math.round(gen)))
			{
				gen = Math.round(gen);
				return;
			}

			// Type cast to integer (or derivative)
			gen = "Math.round(" + gen + ")";
		}

		//===============================================================================
		function __cast_to_string()
		{
			vartype = "String";

			// string literal to string, pass...
			if(_this.RX_STRING_LETERAL.test(gen)) return;

			gen = "String(" + gen + ")";
		}

		//===============================================================================
		function __cast()
		{
			if(_this.isDerivativeOf(ast.__typecast, "Integer")) 	return __cast_to_integer();
			if(_this.isDerivativeOf(ast.__typecast, "Float"))		return __cast_to_float();
			if(_this.isDerivativeOf(ast.__typecast, "String"))		return __cast_to_string();
		}

		//===============================================================================
		if(ast.__typecast_explicit) // Explicit Type Cast Call
		{
			if(vartype==ast.__typecast)
				_this.NewWarning("Unnecessary explicit typecast: " + ast.parent.parent.source, ast);

			if(_this.warn_explicit_typecast && gen.indexOf("arguments[")!=0 && ast.__typecast!="String" && !_this.isPointer(ast.__typecast) && !_this.isEnum(ast.__typecast) && !_this.isEnum(vartype))
				_this.NewWarning("Explicit typecast: " + ast.parent.parent.source, ast);

			__cast();

			// Explicit typecast is wrapped in parenthesis
			if(gen==old)
				gen = "(" + gen + ")";
		}

		//===============================================================================
		else if(ast.__typecast_implicit) // Assign
		{
			if(ast.__typecast != vartype)
				__cast();
		}

		//===============================================================================
		else if(ast.__typecast_byval) // Function Call
		{
			if(ast.__typecast != vartype)
				__cast();
		}

		//===============================================================================
		// Type Check

		_this.typeCheck(ast, ast.__typecast, vartype);

		return gen;
	};

	// ==================================================================================================================================
	//	  ______                    ______           __  _                ______
	//	 /_  __/_  ______  ___     / ____/___ ______/ /_(_)___  ____ _   / ____/__    __
	//	  / / / / / / __ \/ _ \   / /   / __ `/ ___/ __/ / __ \/ __ `/  / /  __/ /___/ /_
	//	 / / / /_/ / /_/ /  __/  / /___/ /_/ (__  ) /_/ / / / / /_/ /  / /__/_  __/_  __/
	//	/_/  \__, / .___/\___/   \____/\__,_/____/\__/_/_/ /_/\__, /   \____//_/   /_/
	//	    /____/_/                                         /____/
	// ==================================================================================================================================

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.arithmeticOp_cpp = function(ast, op, out)
	{
		var type = _this.getTypeName(ast);
		var type1 = _this.getTypeName(ast[0]);
		var type2 = _this.getTypeName(ast[1]);

		var g0 = _this.generate_cpp(ast[0]).CPP;
		var g1 = _this.generate_cpp(ast[1]).CPP;

		if(type1!=type)
		{
			ast[0].__typecast = type;
			g0 = _this.typeCastCPP(ast[0], g0);
		}

		if(type2!=type)
		{
			ast[1].__typecast = type;
			g1 = _this.typeCastCPP(ast[1], g1);
		}

		out.push(g0);
		out.push(op);
		out.push(g1);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Called by:
	// 1. jsdef.VAR value initializer to cast initializer to expected vartype
	// 2. jsdef.CALL for explicit typecast
	// 3. jsdef.LIST during jsdef.CALL generation to type cast function call arguments to proper vartype
	// 4. jsdef.ASSIGN to type cast a value when it is assigned to a variable
	// 5. jsdef.RETURN to type cast a return value to function return vartype

	_this.typeCastCPP = function(ast, gen)
	{
		if(ast.__typecasted) return gen;
		ast.__typecasted = true;

		var old = gen = gen.trim();

		if(!_this.secondPass || gen=="nullptr" || ast.type==jsdef.NEW)
			return gen;

		var vartype = _this.getTypeName(ast);
		if(!vartype)
			return gen;

		var cpp_vartype = _this.VTCPP(vartype).trim();
		if(!cpp_vartype)
			return gen;

		var typecast = ast.__typecast;
		if(!typecast)
		{
			var id = _this.getCallIdentifier(ast);
			if(id && id.symbol.struct)
			{
				// Struct copy constructor
				return gen;
			}
			debugger;
			return gen;
		}

		var cpp_typecast = _this.VTCPP(typecast).trim();
		if(!cpp_typecast)
			return gen;

		//===============================================================================
		function __cast_to_string()
		{
			// string literal to string, pass...
			if(_this.RX_STRING_LETERAL.test(gen)) return;

			// String Constructor
			gen = cpp_typecast + "(" + gen + ")";
		}

		//===============================================================================
		function __cast_to_float()
		{
			// float literal to float, pass...
			if(_this.RX_PARTIAL_FLOAT.test(gen)) return;

			// integer literal to float
			if(_this.RX_INTEGER.test(gen))
			{
				gen = gen + ".0f";
				return;
			}

			// Type cast to float (or derivative)
			gen = "static_cast<" + cpp_typecast + ">(" + gen + ")";
		}

		//===============================================================================
		function __cast_to_integer()
		{
			/// integer literal to color
			if(cpp_typecast=="Color" && _this.RX_INTEGER.test(gen) && !isNaN(gen))
			{
				gen = "0x" + parseInt(gen).toString(16);
				return;
			}

			// integer literal to integer, pass...
			if(_this.RX_INTEGER.test(gen)) return;

			// float literal to integer
			if(_this.RX_PARTIAL_FLOAT.test(gen) && !isNaN(Math.round(gen)))
			{
				gen = Math.round(gen);
				return;
			}

			// Type cast to integer (or derivative)
			gen = "static_cast<" + cpp_typecast + ">(" + gen + ")";
		}

		//===============================================================================
		function __cast_to_pointer()
		{
			if(typecast=="TypedArray") return;
			if(typecast=="Object") return;
			if(typecast=="void") return;

			// Allow implicit convertion between base and derivative classes
			if(!ast.__typecast_explicit && _this.isDerivativeOf(vartype, typecast))
				return;

			// Casting untyped array to typed array
			if(ast.type==jsdef.ARRAY_INIT)
			{
				gen = "new " + typecast + "(" + gen + ")";
				return;
			}

			// Avoid array casting
			if(cpp_typecast.indexOf("Array")!=-1)
			{
				return;
			}

			// Cast pointer to class (upcast or downcast)
			if(ast.__typecast_explicit)
				gen = "reinterpret_cast<" + cpp_typecast + ">(" + gen + ")";
			else
				gen = "dynamic_cast<" + cpp_typecast + ">(" + gen + ")";
		}

		//===============================================================================
		function __cast_to_enum()
		{
			gen = "static_cast<" + cpp_typecast + ">(" + gen + ")";
		}

		//===============================================================================
		function __cast()
		{
			if(cpp_typecast=="CocoAction")
			{
				return;
			}

			// Handle Number type
			if(vartype=="Number" && _this.RX_NUMERIC_LITERAL.test(gen) && !isNaN(gen))
			{
				if(_this.RX_PARTIAL_FLOAT.test(gen))
					vartype = "Float";
				else
					vartype = "Integer";
			}

			if(_this.isDerivativeOf(cpp_typecast, "Integer")) 	return __cast_to_integer();
			if(_this.isDerivativeOf(cpp_typecast, "Float"))		return __cast_to_float();
			if(_this.isDerivativeOf(cpp_typecast, "String"))	return __cast_to_string();
			if(_this.isPointer(cpp_typecast))					return __cast_to_pointer();
			if(_this.isEnum(cpp_typecast))						return __cast_to_enum();

			if(cpp_typecast=="Number")
			{
				//trace("WARNING: Number Typecast " + ast.parent.parent.source);
				return;
			}

			// Unknown
			gen = "static_cast<" + cpp_typecast + ">(" + gen + ")";
		}

		//===============================================================================
		// Explicit Type Cast
		if(ast.__typecast_explicit)
		{
			__cast();

			// Explicit type cast is wrapped in parenthesis if not changed
			if(gen==old)
			{
				gen = "(" + gen + ")";
			}
		}

		//===============================================================================
		// ByVal Type Cast (Implicit, for function call arguments)
		else if(ast.__typecast_byval)
		{
			if(cpp_typecast!=cpp_vartype)
				__cast();
		}

		//===============================================================================
		// Implicit Type Cast
		else // Assign, Return, etc.
		{
			if(cpp_typecast!=cpp_vartype)
				__cast();
		}

		return gen;
	};
}
