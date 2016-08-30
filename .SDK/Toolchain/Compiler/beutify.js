/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2016 www.mobilefx.com
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
 *  CONVERT AS3 Classes to CocoScript classes
 *********************************************************************************
 *
 * ***** END LICENSE BLOCK ***** */

function beutifyJSPP(code, options)
{
	narcissus.__messages = true;
	narcissus.__cpp = false;
	var ast = narcissus.jsparse(code);
	return _this.generate(ast);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.generate = function(ast)
	{
		var out = [];

		switch(ast.type)
		{
		case jsdef.CLASS:
		    out.push("class " + ast.name + " {\n");
		    for(var i = 0; i < ast.body.varDecls.length; i++)
		    	out.push("\t" + _this.generate(ast.body.varDecls[i]));
		    for(var i = 0; i < ast.body.funDecls.length; i++)
		    	out.push("\t" + _this.generate(ast.body.funDecls[i]));
		    out.push("}\n");
			break;

		case jsdef.FUNCTION:
		    if(ast.private) out.push("private ");
            else if(ast.protected) out.push("protected ");
            else if(ast.public) out.push("public ");
            if(ast.static) out.push("static ");
            else if(ast.virtual) out.push("virtual ");
            out.push("function " + ast.name + "(");
			for(var i = 0; i < ast.paramsList.length; i++)
			{
				var p = ast.paramsList[i];
				out.push(p.name + ":" + p.vartype + (i != ast.paramsList.length - 1 ? ", " : ""));
			}
			out.push(")" + (ast.returntype ? ": " + ast.returntype : "") + " {\n" + _this.generate(ast.body) + "}\n");
			break;

		case jsdef.SCRIPT:
		    for(var item in ast)
		    {
		    	if(!isFinite(item)) break;
		    	out.push(_this.generate(ast[item]));
		    }
			break;

		case jsdef.CONST:
		case jsdef.VAR:
            if(ast.private) out.push("private ");
            else if(ast.protected) out.push("protected ");
            else if(ast.public) out.push("public ");
            if(ast.static) out.push("static ");
            if(ast.type == jsdef.VAR) out.push("var ");
            else if(ast.type == jsdef.CONST) out.push("const ");
            out.push(ast[0].name + ": " + ast[0].vartype + (ast[0].initializer ? " = " + _this.generate(ast[0].initializer) : "") + ";\n");
			break;

        case jsdef.LIST:
        case jsdef.COMMA:
            var firstItem = true;
            for(item in ast)
            {
            	if(!isFinite(item)) break;
            	out.push((firstItem ? "" : ", ") + _this.generate(ast[item]));
            	firstItem = false;
            }
        	break;

        case jsdef.BLOCK:
            out.push("{");
            for(item in ast)
            {
            	if(!isFinite(item)) break;
            	out.push("\t" + _this.generate(ast[item]));
            }
            out.push("}");
        	break;

        case jsdef.GROUP:
            out.push("(");
            for(item in ast)
            {
            	if(!isFinite(item)) break;
            	out.push(_this.generate(ast[item]));
            }
            out.push(")");
        	break;

        case jsdef.SWITCH:
            out.push("switch(" + _this.generate(ast.discriminant) + ") {\n");
            for(c in ast.cases)
            {
            	if(!isFinite(c)) break;
            	out.push("\t" + _this.generate(ast.cases[c]));
            }
            out.push("}\n");
        	break;

        case jsdef.ARRAY_INIT:
        	out.push("[");
        	var firstItem = true;
        	for(item in ast)
        	{
        		if(!isFinite(item)) break;
        		out.push((firstItem ? "" : ", ") + _this.generate(ast[item]));
        		firstItem = false;
        	}
        	out.push("]");
        	break;

        case jsdef.IDENTIFIER:			out.push(ast.value); break;
        case jsdef.CALL:				out.push(_this.generate(ast[0]) + "(" + _this.generate(ast[1]) + ")"); break;
        case jsdef.IF:					out.push("if(" + _this.generate(ast.condition) + ")" + _this.generate(ast.thenPart) + (ast.elsePart ? _this.generate(ast.elsePart) : "")); break;
        case jsdef.FOR:					out.push("for(" + (ast.setup ? _this.generate(ast.setup) : "") + (ast.condition ? _this.generate(ast.condition) : "") + ";" + (ast.update ? _this.generate(ast.update) : "") + ")" + _this.generate(ast.body)); break;
       	case jsdef.FOR_IN:				out.push("for(" + (ast.iterator.type == jsdef.VAR ? "var " + ast.iterator[0].value : ast.iterator.value) + " in " + _this.generate(ast.object) + ")" + _this.generate(ast.body)); break;
        case jsdef.IS:					out.push(_this.generate(ast[0]) + " instanceof " + _this.generate(ast[1])); break;
        case jsdef.DELETE: 				out.push("delete " + _this.generate(ast[0])); break;
        case jsdef.STRING:				out.push("\"" + ast.value + "\""); break;
        case jsdef.INDEX:				out.push(_this.generate(ast[0]) + "[" + _this.generate(ast[1]) + "]"); break;
        case jsdef.THIS:				out.push("this"); break;
        case jsdef.SUPER:				out.push("super"); break;
        case jsdef.DOT:					out.push(_this.generate(ast[0]) + "." + _this.generate(ast[1])); break;
		case jsdef.ASSIGN:				out.push(_this.generate(ast[0]) + "=" + _this.generate(ast[1])); break;
		case jsdef.MUL:					out.push(_this.generate(ast[0]) + "*" + _this.generate(ast[1])); break;
		case jsdef.DIV:					out.push(_this.generate(ast[0]) + "/" + _this.generate(ast[1])); break;
		case jsdef.MINUS:				out.push(_this.generate(ast[0]) + "-" + _this.generate(ast[1])); break;
		case jsdef.PLUS:				out.push(_this.generate(ast[0]) + "+" + _this.generate(ast[1])); break;
		case jsdef.MOD:					out.push(_this.generate(ast[0]) + "%" + _this.generate(ast[1])); break;;
		case jsdef.AND:					out.push(_this.generate(ast[0])); out.push("&&"); out.push(_this.generate(ast[1])); break;
		case jsdef.BITWISE_AND:			out.push(_this.generate(ast[0])); out.push("&"); out.push(_this.generate(ast[1])); break;
		case jsdef.BITWISE_NOT:			out.push("~"); out.push(_this.generate(ast[0])); break;
		case jsdef.BITWISE_OR:			out.push(_this.generate(ast[0])); out.push("|"); out.push(_this.generate(ast[1])); break;
		case jsdef.BITWISE_XOR:			out.push(_this.generate(ast[0])); out.push("^"); out.push(_this.generate(ast[1])); break;
		case jsdef.BREAK:				out.push("break;\n"); break;
		case jsdef.CASE:				out.push("case " + _this.generate(ast.caseLabel) + ":"); out.push(_this.generate(ast.statements)); break;
		case jsdef.CONTINUE:			out.push("continue;"); break;
		case jsdef.DECREMENT:			if(ast.postfix) { out.push(_this.generate(ast[0])); out.push("--"); } else { out.push("--"); out.push(_this.generate(ast[0])); } break;
		case jsdef.DEFAULT:				out.push("default:"); out.push(_this.generate(ast.statements)); break;
		case jsdef.DO: 					ast.body.isLoop = true; out.push("do"); out.push(_this.generate(ast.body)); out.push("while(" + _this.generate(ast.condition) + ");\n"); break;
		case jsdef.EQ: 					out.push(_this.generate(ast[0])); out.push("==");	 out.push(_this.generate(ast[1])); break;
		case jsdef.EXPONENT:			out.push("Math.pow(" + _this.generate(ast[0]) + "," + _this.generate(ast[1]) + ")");break;
		case jsdef.FALSE:				out.push("false"); break;
		case jsdef.GE:					out.push(_this.generate(ast[0])); out.push(">=");  out.push(_this.generate(ast[1])); break;
		case jsdef.GT:					out.push(_this.generate(ast[0])); out.push(">");   out.push(_this.generate(ast[1])); break;
		case jsdef.HOOK:				out.push(_this.generate(ast[0])); out.push("?"); out.push(_this.generate(ast[1])); out.push(":"); out.push(_this.generate(ast[2])); break;
		case jsdef.INCREMENT:			if(ast.postfix) { out.push(_this.generate(ast[0])); out.push("++"); } else { out.push("++"); out.push(_this.generate(ast[0])); } break;
		case jsdef.INSTANCEOF: 			out.push(_this.generate(ast[0])); out.push(" instanceof "); out.push(_this.generate(ast[1])); break;
		case jsdef.LABEL:				out.push(ast.label + ":"); out.push(_this.generate(ast.statement)); break;
		case jsdef.LE:					out.push(_this.generate(ast[0])); out.push("<=");  out.push(_this.generate(ast[1])); break;
		case jsdef.LSH:					out.push(_this.generate(ast[0])); out.push("<<"); out.push(_this.generate(ast[1])); break;
		case jsdef.LT:					out.push(_this.generate(ast[0])); out.push("<");   out.push(_this.generate(ast[1])); break;
		case jsdef.NE:					out.push(_this.generate(ast[0])); out.push("!=");	 out.push(_this.generate(ast[1])); break;
		case jsdef.NEW: 				out.push("new " + ast[0].vartype); break;
		case jsdef.NOT:					out.push("!"); out.push(_this.generate(ast[0])); break;
		case jsdef.NULL:				out.push("null"); break;
		case jsdef.NUMBER:				out.push(ast.value); break;
		case jsdef.OR:					out.push(_this.generate(ast[0])); out.push("||"); out.push(_this.generate(ast[1]));	break;
		case jsdef.RETURN:				out.push("return"); if(ast.value) out.push(" " + _this.generate(ast.value)); out.push(";\n"); break;
		case jsdef.RSH:					out.push(_this.generate(ast[0])); out.push(">>"); out.push(_this.generate(ast[1])); break;
		case jsdef.SEMICOLON:			var expr = (ast.expression ? _this.generate(ast.expression) : ""); if(expr) out.push(expr + ";\n"); break;
		case jsdef.STRICT_EQ:			out.push(_this.generate(ast[0])); out.push("==="); out.push(_this.generate(ast[1])); break;
		case jsdef.STRICT_NE:			out.push(_this.generate(ast[0]));	out.push("!=="); out.push(_this.generate(ast[1])); break;
		case jsdef.THROW:				out.push("throw "); out.push(_this.generate(ast.exception)); out.push(";\n"); break;
		case jsdef.TRUE:				out.push("true"); break;
		case jsdef.TYPEOF:				out.push("typeof "); out.push(_this.generate(ast[0])); break;
		case jsdef.UNARY_MINUS:			out.push(" -"); out.push(_this.generate(ast[0])); break;
		case jsdef.UNARY_PLUS:			out.push(" +"); out.push(_this.generate(ast[0])); break;
		case jsdef.URSH:				out.push(_this.generate(ast[0])); out.push(">>"); out.push(_this.generate(ast[1])); break;
		case jsdef.VOID:				out.push("void "); out.push(_this.generate(ast[0])); break;
		case jsdef.WHILE:				ast.body.isLoop=true; out.push("while(" + _this.generate(ast.condition) + ")"); out.push(_this.generate(ast.body)); break;
		case jsdef.NEW_WITH_ARGS:       out.push("new " + ast[0].vartype + "(" + _this.generate(ast[1]) + ")"); break;

		default:
			debugger;
		}
		return out.join("");
	}
}
