/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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
	_this.ECMA_TYPES = ["Object", "Global", "Array", "Function", "String", "Boolean", "Number", "Date", "Math", "RegExp", "Error", "EvalError", "RangeError", "ReferenceError", "SyntaxError", "TypeError", "ArrayBuffer", "ArrayBufferView", "DataView", "Int8Array", "Int16Array", "Int32Array", "Int64Array", "Uint8Array", "Uint16Array", "Uint32Array", "Uint64Array", "Float32Array", "Float64Array"];
	_this.TYPED_ARRAYS = ["ArrayBuffer", "ArrayBufferView", "Int8Array", "Int16Array", "Int32Array", "Int64Array", "Uint8Array", "Uint16Array", "Uint32Array", "Uint64Array", "Float32Array", "Float64Array"];
	_this.NUMERIC_TYPES = ["Number","Float","Integer"];
	_this.SCALAR_TYPES = ["Class","Boolean","Number","String","Integer","Float","void","undefined","null", "CocoAction"];

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.TYPEDEFS =
	{
		"int8_t"		: "Integer",
		"int16_t"   	: "Integer",
		"int32_t"   	: "Integer",
		"int64_t"   	: "Integer",
		"uint8_t"   	: "Integer",
		"uint16_t"  	: "Integer",
		"uint32_t"  	: "Integer",
		"uint64_t"  	: "Integer",
		"Color"			: "Integer",
		"Time"			: "Float",
		"CartesianX"	: "Integer",
		"CartesianY"	: "Integer",
		"Currency"		: "Float",
		"Cents" 		: "Integer",
		"Coins"			: "Integer",
		"Gradient"		: "String"
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.TYPEDARRAY_SUBTYPES =
	{
		"Array":			"Object",
		"ArrayBuffer":		"Number",
		"ArrayBufferView":	"Number",
		"Int8Array":		"int8_t",
		"Int16Array":		"int16_t",
		"Int32Array":		"Integer",
		"Int64Array":		"int64_t",
		"Uint8Array":		"uint8_t",
		"Uint16Array":		"uint16_t",
		"Uint32Array":		"uint32_t",
		"Uint64Array":		"uint64_t",
		"Float32Array":		"Float",
		"Float64Array":		"Float"
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.DEFAULT_VALUES =
	{
		"Array"		: { "default": "null" },
		"Boolean"	: { "default": "false" },
		"Date"		: {	"default": "null" },
		"Function"	: {	"default": "null" },
		"Null"		: { "default": "null" },
		"Number"	: {	"default": "0" },
		"Integer"	: { "default": "0" },
		"Float"		: { "default": "0.0" },
		"Object"	: { "default": "null" },
		"RegExp"	: { "default": "null" },
		"String"	: { "default": '""' }
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.TYPECAST_RULES =
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
			"Integer"		: ["Boolean", "Integer", "Float" ],
			"Float"			: ["Number", "Integer" ],
			"Object"		: [],
			"RegExp"		: ["Boolean", "Date", "Number", "String"],
			"String"		: ["Boolean", "Date", "Function", "Number", "RegExp"]
		},

		implicit:
		{
			/*
			==========================================================================
			        A    =      B        =>  C
		    ==========================================================================
		     */
			ASSIGN:
			{
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Integer"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						},
				"String":
						{
							"String"	: "String",
							"Integer"	: "String",
							"Float"		: "String"
						}
			},
			/*
			==========================================================================
			   C = A    +      B        =>  C
		    ==========================================================================
		     */
			PLUS:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float"

						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						}
			},
			/*
			==========================================================================
			   C = A    -      B        =>  C
		    ==========================================================================
		     */
			MINUS:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float"
						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						}
			},
			/*
			==========================================================================
			   C = A    *      B        =>  C
		    ==========================================================================
		     */
			MUL:
			{
				"Number":
						{
							"Number"	: "Number",
							"Integer"	: "Integer",
							"Float"		: "Float"
						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Float"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						}
			},
			/*
			==========================================================================
			   C = A    /      B        =>  C
		    ==========================================================================
		     */
			DIV:
			{
				"Number":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						},
				"Integer":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						},
				"Float":
						{
							"Number"	: "Float",
							"Integer"	: "Float",
							"Float"		: "Float"
						}
			},
			/*
			==========================================================================
			   C = A    ^      B        =>  C
		    ==========================================================================
		     */
			MOD:
			{
				"Number":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Integer"
						},
				"Integer":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Integer"
						},
				"Float":
						{
							"Number"	: "Integer",
							"Integer"	: "Integer",
							"Float"		: "Integer"
						}
			},

			/* ======================================================================= */
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
	_this.typeDef = function(vartype)
	{
		if(!vartype) return null;
		vartype = _this.getVarType(vartype.trim());
		vartype = _this.TYPEDEFS[vartype] || vartype;
		return vartype;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isScalar = function (vartype)
	{
		vartype = _this.typeDef(vartype);
		return _this.SCALAR_TYPES.indexOf(vartype)!=-1;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isPointer = function (vartype)
	{
		return !(_this.isScalar(vartype) || _this.isEnum(vartype));
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isECMA = function(vartype)
	{
		vartype = _this.typeDef(vartype);
		return vartype && _this.ECMA_TYPES.indexOf(vartype)!=-1;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isTypedArray = function(vartype)
	{
		vartype = _this.typeDef(vartype);
		return vartype && _this.TYPED_ARRAYS.indexOf(vartype)!=-1;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isEnum  = function(vartype)
	{
		var cls = _this.classes[vartype];
		return cls && cls.enum ? true : false;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.enumDefault = function(vatype, cpp)
	{
		var cls = _this.classes[vatype];
		if(!cls || !cls.enum) return;
		var item;
		for(item in cls.vars) break;
		return cls.name + (cpp ? "::" : ".") + item;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.isNumber = function(vartype)
	{
		vartype = _this.typeDef(vartype);
		return vartype && (_this.NUMERIC_TYPES.indexOf(vartype)!=-1 || _this.isEnum(vartype));
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
	_this.getVarType = function(vartype)
	{
		if(!vartype) return null;
		if(vartype.charAt(vartype.length-1)!='>') return vartype;
		vartype = vartype.substr(0, vartype.indexOf('<'));
		return vartype;
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.getSubType = function(vartype)
	{
		if(!vartype) return null;
		var subtype = _this.TYPEDARRAY_SUBTYPES[vartype];
		if(subtype) return subtype;
		if(vartype.charAt(vartype.length-1)!='>') return null;
		var subtype = /<(\w+)(?:\*)*>/.exec(vartype)[1];
		return subtype;
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

		vartype = _this.typeDef(vartype);

		if(__exists(_this.DEFAULT_VALUES, vartype) && __exists(_this.DEFAULT_VALUES[vartype], "default"))
			return _this.DEFAULT_VALUES[vartype].default;

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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.VTCPP = function(vartype, jsdef_NEW)
	{
		if(!vartype || vartype=="void")
			return "void";

		if(_this.isTypedArray(vartype))
			return vartype+(jsdef_NEW?"":"*");

		var v = _this.getVarType(vartype);
		var s = _this.getSubType(vartype);

		if(s && _this.isPointer(s))
			s += "*";

		v = v + (s ? "<"+s+">" : "");

		var cls = _this.getClass(v);
		if(cls.callback)
			return v;

		if(!jsdef_NEW)
			v += (_this.isPointer(v) || s!=null ? "*" : "");

		return v;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.VALUECPP = function(v, subtype)
	{
		if(subtype=="Float" && !isNaN(parseFloat(v)) && v.indexOf('.')==-1)
			return v + ".0f";

		return v;
	};

	// ==================================================================================================================================
	//	    ____           __          __             _    __           __
	//	   /  _/___  _____/ /_  ______/ /__  _____   | |  / /___ ______/ /___  ______  ___
	//	   / // __ \/ ___/ / / / / __  / _ \/ ___/   | | / / __ `/ ___/ __/ / / / __ \/ _ \
	//	 _/ // / / / /__/ / /_/ / /_/ /  __(__  )    | |/ / /_/ / /  / /_/ /_/ / /_/ /  __/
	//	/___/_/ /_/\___/_/\__,_/\__,_/\___/____/     |___/\__,_/_/   \__/\__, / .___/\___/
	//	                                                                /____/_/
	// ==================================================================================================================================

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

	// ==================================================================================================================================
	//	    ___   ___________   _    __           __
	//	   /   | / ___/_  __/  | |  / /___ ______/ /___  ______  ___
	//	  / /| | \__ \ / /     | | / / __ `/ ___/ __/ / / / __ \/ _ \
	//	 / ___ |___/ // /      | |/ / /_/ / /  / /_/ /_/ / /_/ /  __/
	//	/_/  |_/____//_/       |___/\__,_/_/   \__/\__, / .___/\___/
	//	                                          /____/_/
	// ==================================================================================================================================

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
		return (ast.vartype ? ast.vartype : (ast.vartype = _this.getTypeNameResolver(ast)));
	};

	_this.getTypeNameResolver = function(ast)
	{
		var _this = this;

		switch(ast.type)
		{
		//=============================================================================================================================
		case jsdef.ARRAY_INIT:		return "Array";
		case jsdef.COMMA: 			return _this.getTypeName(ast[+ast.length-1]);
		case jsdef.DELETE:          return "Boolean";
		case jsdef.GROUP: 			return _this.getTypeName(ast[0]);
		case jsdef.IN:              return "Boolean";
		case jsdef.INSIDE:          return "Boolean";
		case jsdef.INSTANCEOF:      return "Boolean";
		case jsdef.OBJECT_INIT:		return "Object";
		case jsdef.TYPEOF:			return "String";

		//=============================================================================================================================
		case jsdef.FALSE:           return "Boolean";
		case jsdef.TRUE:			return "Boolean";

		//=============================================================================================================================

		case jsdef.ASSIGN:   		return _this.getTypeName(ast[0]);
		case jsdef.BITWISE_NOT:		return "Integer";

		//=============================================================================================================================
		case jsdef.EQ:              return "Boolean";
		case jsdef.GT:              return "Boolean";
		case jsdef.GE:              return "Boolean";
		case jsdef.LT:              return "Boolean";
		case jsdef.LE:              return "Boolean";
		case jsdef.NE:              return "Boolean";
		case jsdef.NOT:             return "Boolean";

		case jsdef.STRICT_EQ:       return "Boolean";
		case jsdef.STRICT_NE:       return "Boolean";

		//=============================================================================================================================
		case jsdef.SUPER:			return ast.symbol.vartype;
		case jsdef.THIS:			return _this.currClassName || "Function";

		//=============================================================================================================================
		case jsdef.NULL:			return "Null";
		case jsdef.VOID:			return _this.UNTYPED;
		case jsdef.STRING:			return "String";
		case jsdef.REGEXP:			return "RegExp";
		case jsdef.STATE:			return "State";

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

			if(!ast[0].symbol && ast.inFunction)
			{
				ast[0].symbol = _this.LookupIdentifier(ast.inFunction.scope, ast[0].value, ast[0], true);
			}

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
			var operation = _this.TYPECAST_RULES.implicit[op];
			var type1 = _this.getTypeName(ast[0]);
			var type2 = _this.getTypeName(ast[1]);

			if(operation[type1])
			{
				if(operation[type1].hasOwnProperty(type2))
					return operation[type1][type2];
				else
					return _this.typeCheck(ast, type1, type2, null, false, false, op);
			}

			return _this.typeCheck(ast, type1, type2, "Illegal operation " + op + " on: " + type1 + " and " + type2);

		//=============================================================================================================================
		case jsdef.INCREMENT:
		case jsdef.DECREMENT:
		case jsdef.UNARY_PLUS:
		case jsdef.UNARY_MINUS:

			var type = _this.getTypeName(ast[0]);
			if (~_this.TYPECAST_RULES.explicit.__UNARY__.indexOf(type))
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
			var operation = _this.TYPECAST_RULES.implicit.BIT;
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

			var type = _this.getTypeName(ast[0]);

			// Callback?
			var cls = _this.getClass(type);
			if(cls && cls.callback) return cls.returntype;

			return type;

		//=============================================================================================================================
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

			var symbol = ast.identifier_last && ast.identifier_last.symbol ? ast.identifier_last.symbol : null;

			if(!symbol && (!ast.identifier_last || !ast.identifier_last.symbol))
				symbol = _this.LookupLastDotIdentifier(ast, _this.getCurrentScope());

			if(!symbol)
			{
				_this.NewError("Symbol not found: " + ast.source, ast);
				return null;
			}

			return symbol.vartype;

		default:
			break;

		}
	};

	// ==================================================================================================================================
	//	    ______                 __  _                ______                 ________              __
	//	   / ____/_  ______  _____/ /_(_)___  ____     /_  __/_  ______  ___  / ____/ /_  ___  _____/ /__
	//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \     / / / / / / __ \/ _ \/ /   / __ \/ _ \/ ___/ //_/
	//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / /    / / / /_/ / /_/ /  __/ /___/ / / /  __/ /__/ ,<
	//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/    /_/  \__, / .___/\___/\____/_/ /_/\___/\___/_/|_|
	//	                                                  /____/_/
	// ==================================================================================================================================

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

	// ==================================================================================================================================
	//	  ______                    ________              __
	//	 /_  __/_  ______  ___     / ____/ /_  ___  _____/ /__
	//	  / / / / / / __ \/ _ \   / /   / __ \/ _ \/ ___/ //_/
	//	 / / / /_/ / /_/ /  __/  / /___/ / / /  __/ /__/ ,<
	//	/_/  \__, / .___/\___/   \____/_/ /_/\___/\___/_/|_|
	//	    /____/_/
	// ==================================================================================================================================

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typeCheckItems = function(ast, ast0, ast1, strictNumbers, operator)
	{
		if(strictNumbers==null)
			strictNumbers = true;

		var type1 = _this.getTypeName(ast0);
		var type2 = _this.getTypeName(ast1);
		_this.typeCheck(ast, type1, type2, null, null, strictNumbers, operator);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.typeCheck = function(ast, _type1, _type2, customError, checkOnly, strictNumbers, operator)
	{
		var _this = this;
		if(!_this.currClassName || !_this.secondPass) return _type1;

		// Fast type checking
		if(_type1==_type2) return _type1;

		// Casting to Object is wildcard
		if(_type1=="Object" || _type2=="Object") return _type1;

		// Extract Vartype and Subtype
		var type1  = _this.getVarType(_type1);
		var type2  = _this.getVarType(_type2);
		var stype1 = _this.getSubType(_type1);
		var stype2 = _this.getSubType(_type2);
		if(type1==type2 && stype1==stype2) return _type1;

		// Array type check
		if(type1=="Array" && type2=="Array")
		{
			if(stype1==stype2) return _type1;
			if(stype2=="Object") return _type1;
			if(stype1=="Object") return _type2; // Nasty hack for arrays used by ECMA objects

			// Subtypes with inheritance relation
 			if(_this.isDerivativeOf(stype1, stype2))
				return _type1;

			if(checkOnly) return false;
			_this.NewError(customError || "Cannot convert " + _type2 + " to " + _type1 + ": " + (ast[0] ? ast[0] : ast).source, ast);
			return _type1;
		}

		// Resolve typeDefs
		type1 = _this.typeDef(type1);
		type2 = _this.typeDef(type2);
		if(_type1==_type2) return _type1;

		// Implicit Convertion Table for Scalars
		var operation = _this.TYPECAST_RULES.implicit[operator||"ASSIGN"];
		if(operation[type1] && operation[type1].hasOwnProperty(type2))
		{
			// Implicit Convertion Allowed
			return operation[type1][type2];
		}

		// Eums
		if(_this.isEnum(type1) && _this.isNumber(type2)) return _type1;
		if(_this.isNumber(type1) && _this.isEnum(type2)) return _type1;

		// Null
		if(_this.isPointer(type1) && type2=="Null") return _type1;
		if(_this.isPointer(type2) && type1=="Null") return _type2;

		// Inheritance and Interfaces
		var cls1 = _this.getClass(type1);
		if(!cls1) { _this.NewError(customError || "Class not found: " + type1, ast); return _type1; }

		if(cls1.callback)
		{
			if(type2=="Null") return _type1;

			if(type1!=type2)
			{
				if(!_this.compareMethodSignatures(ast.symbol, cls1, true))
					_this.NewError(customError || "Invalid callback function: " + type2, ast);

				return _type1;
			}

			return _type1;
		}

		var cls2 = _this.getClass(type2);
		if(!cls2) { _this.NewError(customError || "Class not found: " + type2, ast); return _type1; }

		if(_this.classTypeCheck(cls1, cls2, ast))
			return _type1;

		if(checkOnly) return false;
		_this.NewError(customError || "Cannot convert " + _type2 + " to " + _type1 + ": " + (ast[0] ? ast[0] : ast).source, ast);
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
			for(var base=cls2;base!=null;base=base.baseSymbol)
			{
				for(i=0;i<base.interfaces.length;i++)
				{
					var ic = _this.getClass(base.interfaces[i]);
					if(_this.classTypeCheck(cls1, ic, ast))
						return cls1.name;
				}
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

			// Type cast to integer (or derivative) by flooring
			gen = "(((" + gen + ")+0.5)|0)";
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
			// Do not typecast for typedef-ed types
			if(_this.typeDef(ast.__typecast)==_this.typeDef(vartype)) return;

			if(_this.isDerivativeOf(ast.__typecast, "Integer")) 	return __cast_to_integer();
			if(_this.isDerivativeOf(ast.__typecast, "Float"))		return __cast_to_float();
			if(_this.isDerivativeOf(ast.__typecast, "String"))		return __cast_to_string();
		}

		//===============================================================================
		if(ast.__typecast_explicit) // Explicit Type Cast Call
		{
			if(vartype==ast.__typecast && ast.parent && ast.parent.parent)
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
			if(id && id.symbol && id.symbol.struct)
			{
				// Struct copy constructor
				return gen;
			}
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
				var no_pointer = cpp_typecast.substr(0, cpp_typecast.indexOf(">")+1);
				gen = "new " + no_pointer + "(" + gen + ")";
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
			// Handle Number type
			if(vartype=="Number" && _this.RX_NUMERIC_LITERAL.test(gen) && !isNaN(gen))
			{
				if(_this.RX_PARTIAL_FLOAT.test(gen))
					vartype = "Float";
				else
					vartype = "Integer";
			}

			// Do not typecast for typedef-ed types
			if(_this.typeDef(cpp_typecast)==_this.typeDef(cpp_vartype)) return;

			// Function Pointer (Callback / Lambda)
			var cls = _this.getClass(typecast);
			if(cls && cls.callback)
			{
				return;
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
