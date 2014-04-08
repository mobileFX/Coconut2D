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
 *  CONVERT AS3 Classes to CocoScript classes
 *********************************************************************************
 *
 * ***** END LICENSE BLOCK ***** */

function AS3Compiler(ast)
{
	var _this = this;
	//_this.symbolId = -1;					// Symbols Counter
	//_this.scopeId = -1;                     // Scopes Counter (resets per file)
	//_this.currFile = null;                  // Current File being processed
	//_this.secondPass = false;               // Flag that indicates compiler's second pass
	//_this.ast = ast;                        // The Abstract Syntax Tree root node (jsdef.SCRIPT)
	//_this.tokenizer = null;                 // Reference to tokenizer (reserved for future use)
	_this.fileClasses = {};                 // Map of classes per file (usage: _this.fileClasses[file][class] = ast; )
	//_this.includes = [];                    // List of include files for current file being processed (resets per file)
	//_this.no_errors = 0;                    // Semaphore that controls errors generation (used by ""#ignore_errors" directive)
	//_this.scopesStack = [];                 // Stack of Scopes (scopes are pushed and popped from it during generation)
	//_this.scopesTable = [];                 // Table of Scopes (scopes are only pushed)
	//_this.debugSymbolsTable = [];           // Map of source code to runtime debug symbols, used by IDE debugger (eg. class foo { public var x; } , x at runtime is __CLASS_FOO__.x )
	//_this.currClassName = null;             // The current class being processed (also indicates whether a JS++ class is being processed or just plain JavaScript code)
	//_this.classes = {};                     // Map of class symbols
	//_this.line_start = -1;                  // Souce Line counter: source code lines "//@line xxx" are emitted in generated code for IDE debugger
	//_this.UNTYPED = "Untyped";              // Untyped identifier vartype, used in Type Check System
	//_this.exportSymbols = exportSymbols;    // Flag that indicates whether symbols should be exported or not
	//_this.selectedClass = selectedClass;    // If set it indicates that we only need to process a single class (used by IDE intelliSence for parsing classes as you type them)
	//_this.in_state = false;    				// Flag that indicates we are processing a state
	//_this.in_property = false;    			// Flag that indicates we are processing a property
	//_this.states = {};						// Map of states
	//_this.importJSProto = importJSProto;	// Import JavaScript Prototypes to JavaScript Classes

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.compile = function()
	{
		_this.preprocess(ast);
		for(file in _this.fileClasses)
		{
			var buffer = [];
            for(c in _this.fileClasses[file])
            	buffer.push(_this.generate(_this.fileClasses[file][c]));
			write(RxReplace(RxReplace(file, "C\\:\\/Users\\/admin\\/Desktop\\/Box2D\\.as3\\/", "mg", "C:/Users/YiamiYo/Desktop/Coconut/Projects/Coco.project/web/src/Coconut2D/Box2D/"), "\\.as$", "mg", ".jspp"), do_js_beautify(buffer.join("\n")));
		}
		_this.generate(ast);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.preprocess = function(ast)
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
				if(!_this.fileClasses[node.path]) _this.fileClasses[node.path]={};
				_this.fileClasses[node.path][node.name] = node;
				node.initializers = [];
				for(var i = 0; i < node.body.funDecls.length; i++)
					if(node.body.funDecls[i].name == node.name)
					{
						node.conDecl = node.body.funDecls[i];
						node.body.funDecls[i].isConstructor = true;
					}
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
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	_this.generate = function(ast)
	{
		var out = [];

		switch(ast.type)
		{
		case jsdef.CLASS:
		    out.push("class " + ast.name + (ast.extends ? " : " + ast.extends : "") + " {\n");
		    for(var i = 0; i < ast.body.varDecls.length; i++)
		    	out.push("\t" + _this.generate(ast.body.varDecls[i]));
		    if(!ast.conDecl && ast.initializers.length)
		    	out.push("\tpublic function Constructor() {\n" + ast.initializers.join("") + "}\n");
		    for(var i = 0; i < ast.body.funDecls.length; i++)
		    	out.push("\t" + _this.generate(ast.body.funDecls[i]));
		    out.push("}\n");
		    //IDECallback("module_as3", ast.path, 0, 0, out.join(""));
			break;

		case jsdef.FUNCTION:
		    if(ast.private) out.push("private ");
            else if(ast.protected) out.push("protected ");
            else if(ast.public) out.push("public ");
            if(ast.static) out.push("static ");
            else if(ast.virtual) out.push("virtual ");
            out.push("function " + (ast.isConstructor ? "Constructor" : ast.name) + "(");
			for(var i = 0; i < ast.paramsList.length; i++)
			{
				var p = ast.paramsList[i];
				out.push(p.name + ":" + p.vartype + (i != ast.paramsList.length - 1 ? ", " : ""));
			}
			out.push(")" + (ast.returntype ? ": " + ast.returntype : "") + " {\n" + (ast.isConstructor ? ast.parent.parent.initializers.join("") : "") + _this.generate(ast.body) + "}\n");
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
            var firstItem = true;
            if(ast.type == jsdef.VAR)
            {
            	out.push("var ");
            	for(var item in ast)
				{
					if(!isFinite(item)) break;
					if(!firstItem)
						out.push(", ");
					out.push(ast[item].name + ": " + ast[item].vartype);
					if(ast.parent && ast.parent.parent && ast.parent.parent.type == jsdef.CLASS && ast[item].initializer)
						ast.parent.parent.initializers.push(ast[item].name + " = " + _this.generate(ast[item].initializer) + ";\n");
					else
						out.push((ast[item].initializer ? " = " + _this.generate(ast[item].initializer) : ""));
					firstItem = false;
				}
				out.push(";\n");
            }
            else if(ast.type == jsdef.CONST)
           		out.push("const " + ast[0].name + ": " + ast[0].vartype + (ast[0].initializer ? " = " + _this.generate(ast[0].initializer) : "") + ";\n");

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
        case jsdef.FOR:					out.push("for(" + (ast.setup ? _this.generate(ast.setup) : "") + (ast.setup && ast.setup.type == jsdef.VAR ? "" : ";") + (ast.condition ? _this.generate(ast.condition) : "") + ";" + (ast.update ? _this.generate(ast.update) : "") + ")" + _this.generate(ast.body)); break;
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
		case jsdef.NEW:					out.push("new " + (ast.vartype ? ast.vartype : ast[0].value)); break;
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
		case jsdef.NEW_WITH_ARGS:       out.push("new " + (ast.vartype ? ast.vartype : ast[0].value) + "(" + _this.generate(ast[1]) + ")"); break;

		default:
			trace(jsdef.tokens[ast.type] + " not generated!\n");
		}
		return out.join("");
	}

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
}
