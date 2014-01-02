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
//	       _______                __           ______
//	      / / ___/  __    __     / /_____     / ____/__    __
//	 __  / /\__ \__/ /___/ /_   / __/ __ \   / /  __/ /___/ /_
//	/ /_/ /___/ /_  __/_  __/  / /_/ /_/ /  / /__/_  __/_  __/
//	\____//____/ /_/   /_/     \__/\____/   \____//_/   /_/
//
// ==================================================================================================================================

// This code transforms a JS++ ast to C++ .hpp and .cpp files.
// Used by Coconut2D IDE in conjunction with the Coconut2D Native SDK for porting JavaScript++ to iOS and Android devices.
// Please send bugs/suggestions to elias.politakis@mobilefx.com

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function CPPCompiler(ast, infolder, outfolder)
{
	var _this = this;

	_this.ast = ast;
	_this.classList = {};
	_this.infolder = infolder;
	_this.outfolder	= outfolder;
	_this.includes = [];
	_this.errors = [];
	_this.warnings = [];
	_this.in_state = false;
	_this.currFileName = null;
	_this.currClassName = null;
	_this.NULL_GEN = { CPP:"", HPP:"" };

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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPPCompiler.prototype.getClassList = function()
{
	var _this = this;
	var out = [];
	for(item in _this.classList)
	{
		out.push( "class " + item + ";" );
	}
	return out.join("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPPCompiler.prototype.compile = function (ast)
{
	var _this = this, CPP = [], HPP = [], ast = ast || _this.ast;

	var generate = function()
	{
		return _this.compile.apply(_this, Array.prototype.slice.call(arguments,0));
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

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.INCLUDE:
		if(ast.include.indexOf(".jspp")!=-1)
		{
			ast.include = ast.include.replace(".jspp", ".hpp");
			_this.includes.push(ast);
		}
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.CLASS:

		if(!ast.scope) return _this.NULL_GEN;
		//if(ast.file=="externs.jspp") return _this.NULL_GEN;

	 	_this.currClassName = ast.name;
	 	_this.classList[ast.name] = ast;

		HPP.push("#ifndef __" + ast.name.toUpperCase() + "_HPP__\n");
		HPP.push("#define __" + ast.name.toUpperCase() + "_HPP__\n\n");

		_HPP_INCLUDES = {};
		_HPP_INCLUDES["Coconut2D.hpp"] = true;

		for(vartype in ast.scope.vartypes)
		{
			for(file in ast.fileClasses)
			{
				if(file=="externs.jspp") continue;
				if(ast.fileClasses[file][vartype])
				{
					_HPP_INCLUDES[file.replace(".jspp", ".hpp")]=true;
				}
			}
		}

		for(item in _HPP_INCLUDES)
			HPP.push('#include "' + item + '"\n');

		HPP.push("\n\nclass " + ast.name + (ast.symbol.base ? " : public " + ast.symbol.base : "") + "\n{\npublic:\n");
		CPP.push('#include "' + ast.name + '.hpp"\n');

		var result;
		for(var item in ast.body)
		{
			if(!isFinite(item)) continue;
			if(ast.body[item].type==jsdef.FUNCTION && ast.body[item].name=="Constructor")
			{
				ast.constructor = ast.body[item];
				break;
			}
		}
		for(var item in ast.body)
		{
			if(!isFinite(item)) continue;
			switch(ast.body[item].type)
			{
			case jsdef.VAR:
				result = generate(ast.body[item]);
				CPP.push(result.CPP);
				HPP.push(result.HPP);
				break;
			}
		}
		for(var item in ast.body)
		{
			if(!isFinite(item)) continue;
			switch(ast.body[item].type)
			{
			case jsdef.STATE:
			case jsdef.FUNCTION:
				result = generate(ast.body[item]);
				CPP.push(result.CPP);
				HPP.push(result.HPP);
				break;
			}
		}
		HPP.push("};\n\n#endif\n");
		_this.currClassName = null;

		var file, path = ast.path.substring(0, ast.path.lastIndexOf("/")+1).replace(_this.infolder, _this.outfolder);

		file = path + ast.name + ".cpp";
		jsppCallback("module", ast.path, file, 0, 0, formatCPP(CPP.join("")));
		trace("Generated " + file);

		file = path + ast.name + ".hpp";
		jsppCallback("module", ast.path, file, 0, 0, formatCPP(HPP.join("")));
		trace("Generated " + file);

		break;

	// ==================================================================================================================================
	//	    ______                 __  _
	//	   / ____/_  ______  _____/ /_(_)___  ____  _____
	//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \/ ___/
	//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / (__  )
	//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/____/
	//
	// ==================================================================================================================================

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.FUNCTION:

		if(!_this.currClassName) return _this.NULL_GEN;

		if(!ast.returntype) ast.returntype = "void";
		var name = (ast.isConstructor ? _this.currClassName : (ast.isDestructor ? "~" + _this.currClassName : ast.name));
		var param, cppParamsList = "(", hppParamList = "(";

		for(var i=0; i<ast.paramsList.length; i++)
		{
			param = ast.paramsList[i];
			cppParamsList += param.vartype + (param.isPointer ? "*" : "") + " " + param.name;
			var def = (_this.types.hasOwnProperty(param.vartype) ? _this.types[param.vartype].default : "NULL");
			hppParamList += param.vartype + (param.isPointer ? "*" : "") + " " + param.name + (param.optional ? "=" + def : "");
			if(i!=ast.paramsList.length-1)
			{
				cppParamsList +=", ";
				hppParamList +=", ";
			}
		}
		cppParamsList += ")";
		hppParamList += ")";

		var fn = (ast.virtual ? "virtual " : "") + (ast.isConstructor || ast.isDestructor ? "" : ast.returntype + (ast.isPointer ? "*" : "") + " ") + name + hppParamList;
		HPP.push(fn);

        if(_this.in_state)
        {
        	HPP.push("{");
        	HPP.push(generate(ast.body).CPP);
        	HPP.push("}\n");
        }
        else
        {
        	HPP.push(";");
			CPP.push("\n////////////////////////////////////////////////////////////////////////////////////////////////////\n");
			CPP.push( (ast.isConstructor || ast.isDestructor ? "" : ast.returntype +(ast.isPointer?"*":"") + " ") + _this.currClassName+"::" + name + cppParamsList);
	        CPP.push("\n{\n");
			CPP.push(generate(ast.body).CPP);
			CPP.push("}\n");
        }
		break;


	// ==================================================================================================================================
	//	   _____ __        __
	//	  / ___// /_____ _/ /____  _____
	//	  \__ \/ __/ __ `/ __/ _ \/ ___/
	//	 ___/ / /_/ /_/ / /_/  __(__  )
	//	/____/\__/\__,_/\__/\___/____/
	//
	// ==================================================================================================================================

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.STATE:

	    if(!_this.currClassName || !ast.scope) return _this.NULL_GEN;

	    _this.in_state = true;

		HPP.push("struct " + ast.name + " : State {");
		HPP.push(_this.currClassName + "* self;");
		var result;
		for(var item in ast.body)
		{
			if(!isFinite(item)) continue;
			switch(ast.body[item].type)
			{
			case jsdef.VAR:
				result = generate(ast.body[item]);
				HPP.push(result.HPP);
				break;
			}
		}
		HPP.push(ast.name + "(" + _this.currClassName + "* self) : self(self) {}\n");
		for(var item in ast.body)
		{
			if(!isFinite(item)) continue;
			switch(ast.body[item].type)
			{
			case jsdef.FUNCTION:
				result = generate(ast.body[item]);
				HPP.push(result.HPP);
				break;
			}
		}
		HPP.push("} *" + ast.name + " = new struct " + ast.name + "(this);");

        _this.in_state = false;

		break;

	// ==================================================================================================================================
	//	 _    __           _       __    __
	//	| |  / /___ ______(_)___ _/ /_  / /__  _____
	//	| | / / __ `/ ___/ / __ `/ __ \/ / _ \/ ___/
	//	| |/ / /_/ / /  / / /_/ / /_/ / /  __(__  )
	//	|___/\__,_/_/  /_/\__,_/_.___/_/\___/____/
	//
	// ==================================================================================================================================

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.VAR:
	case jsdef.CONST:

		var _CPP = [];
		var _HPP = [];
		var firstItem = true;

		if(ast.scope.isClass || _this.in_state)
		{
			for(var item in ast)
			{
				if(!isFinite(item)) continue;
				_HPP.push(ast[item].vartype + (ast[item].isPointer ? "* " : " ") + ast[item].name + ";\n");
				// Initializer explicitly in constructor please!!
			}
		}
		else
		{
			for(var item in ast)
			{
				if(!isFinite(item)) continue;
				if(firstItem) _CPP.push(ast[item].vartype);
				if(!firstItem) _CPP.push(", ");
				_CPP.push((ast[item].isPointer ? "* " : " ") + ast[item].name);
				if(ast[item].initializer)
				{
					_CPP.push("=");
					_CPP.push(generate(ast[item].initializer).CPP);
				}
				else
				{
					var vartype = ast[item].vartype;
					if(vartype && vartype.indexOf("<")!=-1)
						vartype = vartype.substr(0, vartype.indexOf("<"));
					if(_this.types.hasOwnProperty(vartype))
						_CPP.push("="+_this.types[vartype].default);
					else if(ast.scope.isClass)
						_CPP.push("=null");
				}
				firstItem=false;
			}
			_CPP.push(";");
		}

		if(ast.scope.isClass || _this.in_state)
			HPP.push(_HPP.join(""));
		else
			CPP.push(_CPP.join(""));
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
		CPP.push("super");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.THIS:
		CPP.push(_this.in_state ? "self" : "this");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.IDENTIFIER:
		if(_this.in_state && ast.symbol.ast.parent.scope && ast.symbol.ast.parent.scope.isClass)
		{
			if(ast.parent.type == jsdef.DOT)
			{
				if(ast.parent[0] == ast) CPP.push("self->");
			}
			else CPP.push("self->");
		}
		CPP.push(ast.value);
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
		var result;
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
		    result = generate(ast[item]);
			HPP.push(result.HPP);
			CPP.push(result.CPP);
		}
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.BLOCK:
		CPP.push("{\n");
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
			CPP.push(generate(ast[item]).CPP);
		}
		CPP.push("}\n");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.CALL:
		CPP.push(generate(ast[0]).CPP);
		CPP.push("(");
		CPP.push(generate(ast[1]).CPP);
		CPP.push(")");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.LIST:
	case jsdef.COMMA:
		var firstItem = true;
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
			if(!firstItem) CPP.push(", ");
			CPP.push(generate(ast[item]).CPP);
			firstItem = false;
		}
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.GROUP:
		CPP.push("(");
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
			CPP.push(generate(ast[item]).CPP);
		}
		CPP.push(")");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.ARRAY_INIT:
		CPP.push("//<<{");
		var firstItem = true;
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
			if(!firstItem) CPP.push(",");
			CPP.push(generate(ast[item]).CPP);
			firstItem = false;
		}
		CPP.push("}>>//");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.OBJECT_INIT:
		CPP.push("{ ");
		var firstItem = true;
		for(var item in ast)
		{
			if(!isFinite(item)) continue;
			if(!firstItem) CPP.push(", ");
			ast[item].parent = ast;
			CPP.push(generate(ast[item]).CPP);
			firstItem=false;
		}
		CPP.push("}");
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.PROPERTY_INIT:
		CPP.push(generate(ast[0]).CPP + ":");
		CPP.push(generate(ast[1]).CPP);
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
			if(isEmpty) return _this.NULL_GEN;
		}

		CPP.push(generate(ast[0]).CPP);
		CPP.push(ast.value);
		if(ast.value != "=") CPP.push("=");
		CPP.push(generate(ast[1]).CPP);
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
		CPP.push("if(");
		CPP.push(generate(ast.condition).CPP);
		CPP.push(")\n");
		CPP.push(generate(ast.thenPart).CPP);
		if(ast.elsePart)
		{
			CPP.push("else ");
			CPP.push(generate(ast.elsePart).CPP);
		}
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.SWITCH:
		CPP.push("switch(" + generate(ast.discriminant).CPP + "){");
		for(var _case in ast.cases)
		{
			if(!isFinite(_case)) continue;
			CPP.push(generate(ast.cases[_case]).CPP);
			CPP.push("break;");
		}
		CPP.push("}");
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
		var setupFor = ast.setup ? generate(ast.setup).CPP : ";";
		setupFor=setupFor.trim();
		CPP.push("for(" + setupFor + (setupFor.slice(-1) == ";" ? "": ";"));
		CPP.push((ast.condition ? generate(ast.condition).CPP : "") + ";");
		CPP.push((ast.update ? generate(ast.update).CPP : "") + ")\n");
		CPP.push(generate(ast.body).CPP);
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.FOR_IN:
		CPP.push("for(" + (ast.iterator.type == jsdef.VAR ?	"auto " + ast.iterator[0].value : ast.iterator.value));
		CPP.push(" : " + (ast.object ? generate(ast.object).CPP : "") + ")\n");
		CPP.push(generate(ast.body).CPP);
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

		switch(ast.value)
		{
		case "#ignore_errors_begin":
		case "#ignore_errors_end":
			break;

		default:
			CPP.push('"' + ast.value + '"');
		}

		if(_this.currFileName!=ast.path)
		{
			_this.currFileName = ast.path;
			_this.includes = [];
		}

		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.TRY:
		CPP.push("try");
		CPP.push(generate(ast.tryBlock).CPP);
		for(var catchClause in ast.catchClauses)
		{
			if(!isFinite(catchClause)) continue;
			CPP.push("catch(" + ast.catchClauses[catchClause].varName + ")");
			CPP.push(generate(ast.catchClauses[catchClause].block).CPP);
			ast.finallyBlock && CPP.push("finally" + generate(ast.finallyBlock).CPP);
		}
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.INDEX:
		var out = [];
		var type = ast[0].vartype;
		var pointerAccess = !__isVector(type);
		if(pointerAccess) out.push("(*");
		out.push(generate(ast[0]).CPP);
		if(pointerAccess) out.push(")");
		out.push("[");
		out.push(generate(ast[1]).CPP);
		out.push("]");
		CPP.push(out.join(""));
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.DOT:
		CPP.push(generate(ast[0]).CPP);
		CPP.push(__isPointer(ast[0].vartype) ? "->" : ".");
		CPP.push(generate(ast[1]).CPP);
		break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.DEBUGGER:			CPP.push("assert(false);"); break;
	case jsdef.EXPONENT:			CPP.push("std::pow(" + generate(ast[0]).CPP + "," + generate(ast[1]).CPP + ")");break;
	case jsdef.MOD:					CPP.push("(int)" + generate(ast[0]).CPP); CPP.push("%"); CPP.push("(int)" + generate(ast[1]).CPP); break;
	case jsdef.NEW: 				CPP.push("new "); CPP.push(generate(ast[0]).CPP +"()"); break;
	case jsdef.THROW:				CPP.push("throw CocoException("); CPP.push(generate(ast.exception).CPP); CPP.push(");"); break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case jsdef.AND:					CPP.push(generate(ast[0]).CPP); CPP.push("&&"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.BITWISE_AND:			CPP.push(generate(ast[0]).CPP); CPP.push("&"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.BITWISE_NOT:			CPP.push("~"); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.BITWISE_OR:			CPP.push(generate(ast[0]).CPP); CPP.push("|"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.BITWISE_XOR:			CPP.push(generate(ast[0]).CPP); CPP.push("^"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.BREAK:				CPP.push("break;"); break;
	case jsdef.CASE:				CPP.push("case " + generate(ast.caseLabel).CPP + ":"); CPP.push(generate(ast.statements).CPP); break;
	case jsdef.CONTINUE:			CPP.push("continue;"); break;
	case jsdef.DECREMENT:			if(ast.postfix) { CPP.push(generate(ast[0]).CPP); CPP.push("--"); } else { CPP.push("--"); CPP.push(generate(ast[0]).CPP); } break;
	case jsdef.DEFAULT:				CPP.push("default:"); CPP.push(generate(ast.statements).CPP); break;
	case jsdef.DELETE: 				CPP.push("delete "); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.DIV:					CPP.push( "(float)(" + generate(ast[0]).CPP + ")"); CPP.push("/"); CPP.push( "(float)(" + generate(ast[1]).CPP + ")"); break;
	case jsdef.DO: 					ast.body.isLoop = true; CPP.push("do"); CPP.push(generate(ast.body).CPP); CPP.push("while(" + generate(ast.condition).CPP + ");"); break;
	case jsdef.EQ: 					CPP.push(generate(ast[0]).CPP); CPP.push("==");	 CPP.push(generate(ast[1]).CPP); break;
	case jsdef.FALSE:				CPP.push("false"); break;
	case jsdef.GE:					CPP.push(generate(ast[0]).CPP); CPP.push(">=");  CPP.push(generate(ast[1]).CPP); break;
	case jsdef.GT:					CPP.push(generate(ast[0]).CPP); CPP.push(">");   CPP.push(generate(ast[1]).CPP); break;
	case jsdef.HOOK:				CPP.push(generate(ast[0]).CPP); CPP.push("?"); CPP.push(generate(ast[1]).CPP); CPP.push(":"); CPP.push(generate(ast[2]).CPP); break;
	case jsdef.INCREMENT:			if(ast.postfix) { CPP.push(generate(ast[0]).CPP); CPP.push("++"); } else { CPP.push("++"); CPP.push(generate(ast[0]).CPP); } break;
	case jsdef.INSTANCEOF: 			CPP.push(generate(ast[0]).CPP); CPP.push(" instanceof "); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.LABEL:				CPP.push(ast.label + ":"); CPP.push(generate(ast.statement).CPP); break;
	case jsdef.LE:					CPP.push(generate(ast[0]).CPP); CPP.push("<=");  CPP.push(generate(ast[1]).CPP); break;
	case jsdef.LSH:					CPP.push(generate(ast[0]).CPP); CPP.push("<<"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.LT:					CPP.push(generate(ast[0]).CPP); CPP.push("<");   CPP.push(generate(ast[1]).CPP); break;
	case jsdef.MINUS: 				CPP.push(generate(ast[0]).CPP); CPP.push("-"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.MUL: 				CPP.push(generate(ast[0]).CPP); CPP.push("*"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.NE:					CPP.push(generate(ast[0]).CPP); CPP.push("!=");	 CPP.push(generate(ast[1]).CPP); break;
	case jsdef.NEW_WITH_ARGS:		CPP.push("new "); CPP.push(generate(ast[0]).CPP); CPP.push("("); CPP.push(generate(ast[1]).CPP); CPP.push(")"); break;
	case jsdef.NOT:					CPP.push("!"); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.NULL:				CPP.push("NULL"); break;
	case jsdef.NUMBER:				CPP.push(ast.value); break;
	case jsdef.OR:					CPP.push(generate(ast[0]).CPP); CPP.push("||"); CPP.push(generate(ast[1]).CPP);	break;
	case jsdef.PLUS: 				CPP.push(generate(ast[0]).CPP); CPP.push("+"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.RETURN:				CPP.push("return"); if(ast.value) CPP.push(" " + generate(ast.value).CPP); CPP.push(";\n"); break;
	case jsdef.RSH:					CPP.push(generate(ast[0]).CPP); CPP.push(">>"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.SEMICOLON:			var expr = (ast.expression ? generate(ast.expression).CPP : ""); if(expr) CPP.push(expr + ";\n"); break;
	case jsdef.STRICT_EQ:			CPP.push(generate(ast[0]).CPP); CPP.push("=="); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.STRICT_NE:			CPP.push(generate(ast[0]).CPP);	CPP.push("!="); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.TRUE:				CPP.push("true"); break;
	case jsdef.TYPEOF:				CPP.push("typeof "); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.UNARY_MINUS:			CPP.push(" -"); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.UNARY_PLUS:			CPP.push(" +"); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.URSH:				CPP.push(generate(ast[0]).CPP); CPP.push(">>"); CPP.push(generate(ast[1]).CPP); break;
	case jsdef.VOID:				CPP.push("void "); CPP.push(generate(ast[0]).CPP); break;
	case jsdef.WHILE:				ast.body.isLoop=true; CPP.push("while(" + generate(ast.condition).CPP + ")"); CPP.push(generate(ast.body).CPP); break;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	default:
		//debugger;
	}

	return {CPP:CPP.join(""), HPP:HPP.join("")};
};

