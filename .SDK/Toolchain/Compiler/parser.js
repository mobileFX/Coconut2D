// ==================================================================================================================================
//	    _   __                _                         ____
//	   / | / /___ ___________(_)___________  _______   / __ \____ ______________  _____
//	  /  |/ / __ `/ ___/ ___/ / ___/ ___/ / / / ___/  / /_/ / __ `/ ___/ ___/ _ \/ ___/
//	 / /|  / /_/ / /  / /__/ (__  |__  ) /_/ (__  )  / ____/ /_/ / /  (__  )  __/ /
//	/_/ |_/\__,_/_/   \___/_/____/____/\__,_/____/  /_/    \__,_/_/  /____/\___/_/
//
// ==================================================================================================================================
//
//	The following parser is based on JavaScript++ Parser created by Roger Poon
//	which in turn was based on the Narcissus parser.
//
//	Cross-engine port of the SpiderMonkey Narcissus parser.
//	* Original: http://mxr.mozilla.org/mozilla/source/js/narcissus/ as of 2010-02-09
//	* Modifications: Copyright (c) 2010 Guillaume Lathoud, MIT License.
//
//	**** BEGIN ORIGINAL LICENSE BLOCK *****
//
//	Version: MPL 1.1/GPL 2.0/LGPL 2.1
//
//	The contents of this file are subject to the Mozilla Public License Version
//	1.1 (the "License"); you may not use this file except in compliance with
//	the License. You may obtain a copy of the License at
//	http://www.mozilla.org/MPL/
//
//	Software distributed under the License is distributed on an "AS IS" basis,
//	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
//	for the specific language governing rights and limitations under the
//	License.
//
//	The Original Code is the Narcissus JavaScript engine.
//
//	The Initial Developer of the Original Code is
//	Brendan Eich <brendan@mozilla.org>.
//	Portions created by the Initial Developer are Copyright (C) 2004
//	the Initial Developer. All Rights Reserved.
//
//	Contributor(s):
//
//	Alternatively, the contents of this file may be used under the terms of
//	either the GNU General Public License Version 2 or later (the "GPL"), or
//	the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
//	in which case the provisions of the GPL or the LGPL are applicable instead
//	of those above. If you wish to allow use of your version of this file only
//	under the terms of either the GPL or the LGPL, and not to allow others to
//	use your version of this file under the terms of the MPL, indicate your
//	decision by deleting the provisions above and replace them with the notice
//	and other provisions required by the GPL or the LGPL. If you do not delete
//	the provisions above, a recipient may use your version of this file under
//	the terms of any one of the MPL, the GPL or the LGPL.
//
//	***** END ORIGINAL LICENSE BLOCK *****

var GLOBAL = this;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function __init_narcissus(GLOBAL)
{
	GLOBAL.narcissus = {};
	var jsdef = GLOBAL.jsdef = GLOBAL.narcissus.jsdef = {};

	var tokens = jsdef.tokens =
	[
        // End of source.
        "END",

        // Operators and punctuators.
        "\n", ";", "...",
        ",",
        "=",
        "?", ":", "CONDITIONAL",
        "||",
        "&&",
        "|",
        "^",
        "&",
        "==", "!=", "===", "!==",
        "<", "<=", ">=", ">",
        "<<", ">>", ">>>",
        "+", "-",
        "*", "/", "%",
        "!", "~", "UNARY_PLUS", "UNARY_MINUS", "UNARY_EXISTS",
        "++", "--",
        ".",
        "[", "]",
        "{", "}",
        "(", ")",
        "**",

        // Nonterminal tree node type codes.
		"SCRIPT",
		"BLOCK",
		"LABEL",
		"FOR_IN",
		"CALL",
		"NEW_WITH_ARGS",
		"INDEX",
		"ARRAY_INIT",
		"OBJECT_INIT",
		"PROPERTY_INIT",
		"GROUP",
		"LIST",
		"FOR_INSIDE",
		"ARRAY_COMP",
		"ENUM_ITEM",
		"CONSTRUCTOR_CALL",

        // Terminals.
        "IDENTIFIER",
        "NUMBER",
        "STRING",
        "REGEXP",

        // OOP
        "struct",
		"class",
		"interface",
		"control",
		"emscripten",

		"implements",

		"public",
		"private",
		"protected",
		"published",

		"static",
		"abstract",
		"virtual",
		"reference",

		"delegate",
		"optional",
		"super",

		// TODO
		"namespace",
		"thread",
		"volatile",
		"inline",

		// Functions
		"function",
		"state",
		"property",
		"event",
		"callback",

        // Keywords.
		"break",
		"case",
		"catch",
		"const",
		"continue",
		"debugger",
		"default",
		"delete",
		"do",
		"else",
		"enum",
		"false",
		"finally",
		"for",
		"if",
		"in",
		"let",
		"new",
		"null",
		"return",
		"switch",
		"this",
		"throw",
		"true",
		"try",
		"var",
		"while",
		"with",

		// Invalid in JSPP
		"instanceof",
		"typeof",
		"void",

		// AS3
        "as",
		"import",
		"package",
		"use"
	];

	// Operator and punctuator mapping from token to tree node type name.
	// NB: superstring tokens (e.g., ++) must come before their substring token
	// counterparts (+ in the example), so that the opRegExp regular expression
	// synthesized from this list makes the longest possible match.

	var opTypeNamesArr = jsdef.opTypeNamesArr = [
        ['\n', "NEWLINE"],
        [';', "SEMICOLON"],
        [',', "COMMA"],
        ['...', "RANGE"],
        ['?', "HOOK"],
        [':', "COLON"],
        ['||', "OR"],
        ['&&', "AND"],
        ['|', "BITWISE_OR"],
        ['^', "BITWISE_XOR"],
        ['&', "BITWISE_AND"],
        ['===', "STRICT_EQ"],
        ['==', "EQ"],
        ['=', "ASSIGN"],
        ['!==', "STRICT_NE"],
        ['!=', "NE"],
        ['<<', "LSH"],
        ['<=', "LE"],
        ['<', "LT"],
        ['>>>', "URSH"],
        ['>>', "RSH"],
        ['>=', "GE"],
        ['>', "GT"],
        ['++', "INCREMENT"],
        ['--', "DECREMENT"],
        ['**', "EXPONENT"],
        ['+', "PLUS"],
        ['-', "MINUS"],
        ['*', "MUL"],
        ['/', "DIV"],
        ['%', "MOD"],
        ['!', "NOT"],
        ['~', "BITWISE_NOT"],
        ['.', "DOT"],
        ['[', "LEFT_BRACKET"],
        [']', "RIGHT_BRACKET"],
        ['{', "LEFT_CURLY"],
        ['}', "RIGHT_CURLY"],
        ['(', "LEFT_PAREN"],
        [')', "RIGHT_PAREN"]
	];

	var opTypeNames = jsdef.opTypeNames = (function ()
	{
		var ret = {}, x;
		for(var i = 0; i < opTypeNamesArr.length; i++)
		{
			x = opTypeNamesArr[i];
			ret[x[0]] = x[1];
		}
		return ret;
	})();

	// Define const END, etc., based on the token names.  Also map name to index.

	var keywords = jsdef.keywords = (function ()
	{
		// Hash of keyword identifier to tokens index.  NB: we must null __proto__ to
		// avoid toString, etc. namespace pollution.
		//  var _keywords = {__proto__: null};
		// G. Lathoud's addition: This works however only on SpiderMonkey and the like,
		// so let's resort to a more basic approach with hasOwnProperty (see further below).
		// (this helps on Rhino 1.6).
		var _keywords = {};
		GLOBAL.narcissus.jsdefNames = {};
		for(var i = 0, j = tokens.length; i < j; i++)
		{
			var a_const;
			var t = tokens[i];
			if(/^[a-z]/.test(t))
			{
				a_const = t.toUpperCase();
				_keywords[t] = i;
			}
			else
			{
				a_const = (/^\W/.test(t) ? opTypeNames[t] : t);
			}
			jsdef[a_const] = i >> 0;
			tokens[t] = i;
			GLOBAL.narcissus.jsdefNames[i] = a_const;
			//trace("// jsdef." + a_const + " = " + i);
		}
		return function ( /*string*/ id)
		{
			return _keywords.hasOwnProperty(id) && _keywords[id];
		};
	})();

	// Map assignment operators to their indexes in the tokens array.
	var assignOps = jsdef.assignOps = ['|', '^', '&', '<<', '>>', '>>>', '+', '-', '*', '/', '%', '&&', '||', '**', '?'];
	for(var i = 0, j = assignOps.length; i < j; i++)
	{
		var t = assignOps[i];
		assignOps[t] = tokens[t];
	}

	// ==================================================================================================================================
	//	    _   __                _
	//	   / | / /___ ___________(_)___________  _______
	//	  /  |/ / __ `/ ___/ ___/ / ___/ ___/ / / / ___/
	//	 / /|  / /_/ / /  / /__/ (__  |__  ) /_/ (__  )
	//	/_/ |_/\__,_/_/   \___/_/____/____/\__,_/____/
	//
	// ==================================================================================================================================

	var jsdef = GLOBAL.narcissus.jsdef;

	// Build a regexp that recognizes operators and punctuators (except newline).
	var opRegExpSrc = (function ()
	{
		var ret = "^",
			a, i;
		for(var a = 0; a < jsdef.opTypeNamesArr.length; a++)
		{
			i = jsdef.opTypeNamesArr[a][0];
			if(i == '\n')
				continue;
			if(ret != "^")
				ret += "|^";
			ret += i.replace(/[?|^&(){}\[\]+\-*\/\.]/g, "\\$&");
		}
		return ret;
	})();

	var opRegExp = new RegExp(opRegExpSrc);
	var fpRegExp = /^\d+\.(?!\.)\d*(?:[eE][-+]?\d+)?|^\d+(?:\.\d*)?[eE][-+]?\d+|^\.\d+(?:[eE][-+]?\d+)?/;
	//var reRegExp = /^(?:m(x)?|(?=\/))([^\w\s\\])((?:\\.|(?!\2)[^\\])*)\2([a-z]*)/;
	var scopeId = 1;

	// ==================================================================================================================================
	//	  ______      __              _
	//	 /_  __/___  / /_____  ____  (_)___  ___  _____
	//	  / / / __ \/ //_/ _ \/ __ \/ /_  / / _ \/ ___/
	//	 / / / /_/ / ,< /  __/ / / / / / /_/  __/ /
	//	/_/  \____/_/|_|\___/_/ /_/_/ /___/\___/_/
	//
	// ==================================================================================================================================
	/*@@ Tokenizer @@*/

	function Tokenizer(s, f, l)
	{
		this.cursor = 0;
		this.source = String(s);
		this.tokens = [];
		this.tokenIndex = 0;
		this.lookahead = 0;
		this.scanNewlines = false;
		this.scanOperand = true;
		this.line_start = l || 0;
		this.__fileLineOffset = 0;
		this.__filePosOffset = 0;
	}

	Tokenizer.prototype =
	{
		input: function ()
		{
			return this.source.substring(this.cursor);
		},

		done: function ()
		{
			return this.peek() == jsdef.END;
		},

		token: function ()
		{
			return this.tokens[this.tokenIndex];
		},

		match: function (tt)
		{
			return this.get() == tt || this.unget();
		},

		mustMatch: function (tt)
		{
			if(!this.match(tt))
				throw this.newSyntaxError("Missing " + jsdef.tokens[tt].toLowerCase());
			return this.token();
		},

		peek: function ()
		{
			var tt, next;
			if(this.lookahead)
			{
				next = this.tokens[(this.tokenIndex + this.lookahead) & 3];
				if(this.scanNewlines && next.line_start != this.line_start)
					tt = jsdef.NEWLINE;
				else
					tt = next.type;
			}
			else
			{
				tt = this.get();
				this.unget();
			}
			return tt;
		},

		peekOnSameLine: function ()
		{
			this.scanNewlines = true;
			var tt = this.peek();
			this.scanNewlines = false;
			return tt;
		},

		get: function ()
		{
			var token;
			while(this.lookahead)
			{
				--this.lookahead;
				this.tokenIndex = (this.tokenIndex + 1) & 3;
				token = this.tokens[this.tokenIndex];
				if(token.type != jsdef.NEWLINE || this.scanNewlines)
				{
					return token.type;
				}
			}
			for(;;)
			{
				var input = this.input();
				var match = (this.scanNewlines ? /^[ \t]+/ : /^\s+/).exec(input);
				if(match)
				{
					var spaces = match[0];
					this.cursor += spaces.length;
					var newlines = spaces.match(/\n/g);
					if(newlines)
						this.line_start += newlines.length;
					input = this.input();
				}
				if(!(match = /^\/(?:\*(?:[\S\s])*?\*\/|\/.*)/.exec(input)))
					break;
				var comment = match[0];
				this.cursor += comment.length;
				newlines = comment.match(/\n/g);
				if(newlines)
					this.line_start += newlines.length;

				//JSDoc
				if((match = /[\s\t]*\x2f\x2a\x2a([\n\N\w\W.]+?)[\s\t]+\x2a\x2f/mg.exec(comment)))
				{
					this.comment = match[0];
					this.commentLine = this.line_start;
				}
			}
			this.tokenIndex = (this.tokenIndex + 1) & 3;
			token = this.tokens[this.tokenIndex];
			if(!token)
				this.tokens[this.tokenIndex] = token = {};
			if(!input)
			{
				return token.type = jsdef.END;
			}
			if((match = fpRegExp.exec(input)))
			{
				token.type = jsdef.NUMBER;
				token.value = match[0];//parseFloat(match[0]);
			}
			else if((match = /^0[xX][\da-fA-F]+|^0[0-7]*|^\d+/.exec(input)))
			{
				token.type = jsdef.NUMBER;
				token.value = parseInt(match[0]);
			}
			else if((match = /^[$\w]+/.exec(input)))// && !reRegExp.test(input))
			{
				var id = match[0];
				token.type = jsdef.keywords(id) || jsdef.IDENTIFIER;
				token.value = id;
			}
			else if((match = RegExp("^\\x22(?!\\x22)(?:\\\\.|[^\\x22])*\\x22|^\\x27(?!\\x27)(?:\\\\.|[^\\x27])*\\x27|^([\\x27\\x22]{3})((?:(?!\\1)[\\s\\S])*)\\1|^\\x22\\x22|^\\x27\\x27", "").exec(input)))
			{
				token.type = jsdef.STRING;

				if(match[1])
				{
					this.line_start += match[2].split(/\r?\n/gm).length - 1;
					token.value = match[2].split(/\r?\n\r?/gm);
				}
				else
				{
					this.line_start += match[0].split(/\r?\n/gm).length - 1;
					token.value = match[0].replace(RegExp("^['\\x22]|['\\x22]$", "gm"), "");
				}

				///////////////////////////////////////////////////////////////////
				// "#export native";
				if(token.value && token.value.indexOf(this.__EXPORT_NATIVE) != -1)
				{
					this.EXPORT_NATIVE = true;
					if(match.input.substr(match.index + match[0].length, 1)!=";")
						throw this.newSyntaxError("Missing ; after include directive.");
				}

				///////////////////////////////////////////////////////////////////
				// "#export web";
				if(token.value && token.value.indexOf(this.__EXPORT_WEB) != -1)
				{
					this.EXPORT_WEB = true;
					if(match.input.substr(match.index + match[0].length, 1)!=";")
						throw this.newSyntaxError("Missing ; after include directive.");
				}

				///////////////////////////////////////////////////////////////////
				// File
				if(token.value && token.value.indexOf(this.__FILE_DELIM) != -1)
				{
					scopeId = 1;
					this.__path = token.value.substr(this.__FILE_DELIM.length);
					var v = this.__path.split("/");
					this.__file = v[v.length-1];
					this.__fileLineOffset = this.line_start+1;
					this.__filePosOffset = this.cursor + token.value.length + 4;
					this.EXPORT_NATIVE = false;
					this.EXPORT_WEB = false;
					trace("+ parsing: " + this.__file);

				}
				///////////////////////////////////////////////////////////////////
			}
			/*
			else if(this.scanOperand && (match = reRegExp.exec(input)))
			{
				token.type = jsdef.REGEXP;
				token.value = [match[1], match[2], match[3], match[4]];
			}
			*/
			else if((match = opRegExp.exec(input)))
			{
				var op = match[0];
				if(jsdef.assignOps[op] && input[op.length] == '=')
				{
					token.type = jsdef.ASSIGN;
					token.assignOp = jsdef[jsdef.opTypeNames[op]];
					match[0] += '=';
				}
				else
				{
					token.type = jsdef[jsdef.opTypeNames[op]];
					if(this.scanOperand && (token.type == jsdef.PLUS || token.type == jsdef.MINUS || token.type == jsdef.HOOK))
					{
						if(token.type == jsdef.HOOK)
						{
							token.type = jsdef.tokens.indexOf("UNARY_EXISTS");
						}
						else
						{
							token.type += jsdef.UNARY_PLUS - jsdef.PLUS;
						}
					}
					token.assignOp = null;
				}
				token.value = op;
			}
			else if(this.scanNewlines && (match = /^\n/.exec(input)))
			{
				token.type = jsdef.NEWLINE;
			}
			else
			{
				throw this.newSyntaxError("Illegal token");
			}

			token.start = this.cursor;
			this.cursor += match[0].length;
			token.end = this.cursor;
			token.line_start = this.line_start;
			token.line_end = this.line_start;

			return token.type;
		},

		unget: function ()
		{
			if(++this.lookahead == 4) throw "PANIC: too much lookahead!";
			this.tokenIndex = (this.tokenIndex - 1) & 3;
		},

		copyModifiers: function(t, n)
		{
			n.static 	= t.static;
			n.reference	= t.reference;
			n.public 	= t.public;
			n.private 	= t.private;
			n.protected = t.protected;
			n.published	= t.published;
			n.virtual 	= t.virtual;
			n.abstract 	= t.abstract;
			n.delegate 	= t.delegate;
			n.callback	= t.callback;
		},

		setModifiers: function(n)
		{
			n.static 	= this.static;
			n.reference = this.reference;
			n.public 	= this.public;
			n.private 	= this.private;
			n.protected = this.protected;
			n.published	= this.published;
			n.virtual 	= this.virtual;
			n.abstract 	= this.abstract;
			n.delegate 	= this.delegate;
			n.callback	= this.callback;
			this.resetModifiers();
		},

		resetModifiers: function()
		{
			this.static 	= false;
			this.reference	= false;
			this.private 	= false;
			this.public 	= false;
			this.protected 	= false;
			this.published	= false;
			this.virtual 	= false;
			this.abstract 	= false;
			this.delegate 	= false;
			this.callback	= false;
		},

		newSyntaxError: function(m)
		{
			var f = this.__path;
			var l = (this.line_start - this.__fileLineOffset);
			var e = new SyntaxError(m + ', filename:' + f + ', line:' + l);
			//e.cursor = this.cursor;
			trace("@@ ERROR: " + m + " in file " + f  + " at line " + l);
			//IDECallback("error", f, "", l, 0, m);
			IDECallback("error", f, l, 0, m);
			return e;
		}

	};

	Tokenizer.prototype.__EXPORT_WEB = "#export web";
	Tokenizer.prototype.__EXPORT_NATIVE = "#export native";
	Tokenizer.prototype.__FILE_DELIM = "script_begin:///";
	Tokenizer.prototype.__file = "";
	Tokenizer.prototype.__path = "";
	Tokenizer.prototype.__fileLineOffset = 0;
	Tokenizer.prototype.__filePosOffset = 0;

	Tokenizer.prototype.NewScopeId = function()
	{
		return (++scopeId);
	}

	Tokenizer.prototype.ScopeId = function()
	{
		return (scopeId);
	}

	// ==================================================================================================================================
	//	    ___   ___________   _   __          __
	//	   /   | / ___/_  __/  / | / /___  ____/ /__
	//	  / /| | \__ \ / /    /  |/ / __ \/ __  / _ \
	//	 / ___ |___/ // /    / /|  / /_/ / /_/ /  __/
	//	/_/  |_/____//_/    /_/ |_/\____/\__,_/\___/
	//
	// ==================================================================================================================================
	/*@@ Node @@*/

	var __node_id = 0;

	// Node extends Array, which we extend slightly with a top-of-stack method.
	Array.prototype.top = function ()
	{
		return this.length && this[this.length - 1];
	};

	function Node(t, type)
	{
		this.nodeId = (++__node_id);
		this.xmlvartype="";

		if(!t)
		{
			this.scopeId =0;
			this.type = type;
			return;
		}

		var token = t.token();

		this.scopeId = t.ScopeId();
		this.xmlvartype="";
		this.EXPORT_NATIVE = t.EXPORT_NATIVE;
		this.EXPORT_WEB = t.EXPORT_WEB;

		if(token)
		{
			this.type = type || token.type;
			this.value = token.value;

			this.start = token.start;
			this.end = token.end;

			this.line_start = token.line_start;
			this.line_end = token.line_start;

			this.file = t.__file;
			this.path = t.__path;
			this.__fileLineOffset = t.__fileLineOffset;
			this.__filePosOffset = t.__filePosOffset;
		}
		else
		{
			this.type = type;
			this.line_start = t.line_start;
		}

		this.tokenizer = t;

		for(var i = 2; i < arguments.length; i++)
			this.push(arguments[i]);
	}

	GLOBAL.Node = Node;

	var Np = Node.prototype = new Array;
	Np.constructor = Node;

	Np.push = function (kid)
	{
		if(!kid)
			throw this.tokenizer.newSyntaxError("Empty child expression");
		if(kid.start < this.start)
			this.start = kid.start;
		if(this.end < kid.end)
		{
			this.end = kid.end;
			this.line_end = kid.line;
		}
		return Array.prototype.push.call(this, kid);
	};

	function nest(t, x, node, func, end)
	{
		x.stmtStack.push(node);
		var n = func(t, x);
		x.stmtStack.pop();
		end && t.mustMatch(end);
		return n;
	}

	var blockId = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function CompilerContext(inFunction)
	{
		this.inFunction = inFunction;
		this.stmtStack = [];
		this.funDecls = [];
		this.varDecls = [];
	}
	var CCp = CompilerContext.prototype;
	CCp.bracketLevel = CCp.curlyLevel = CCp.parenLevel = CCp.hookLevel = 0;
	CCp.ecmaStrictMode = CCp.inForLoopInit = false;
	var contextId = 0;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function Script(t, x)
	{
		var n = Statements(t, x);
		n.type = jsdef.SCRIPT;
		n.funDecls = x.funDecls;
		n.varDecls = x.varDecls;
		n.contextId = ++contextId;
		n.scopeId = t.NewScopeId();
		return n;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function Statements(t, x)
	{
		var n = new Node(t, jsdef.BLOCK);
		x.stmtStack.push(n);
		while(!t.done() && t.peek() != jsdef.RIGHT_CURLY)
		{
			var stm = Statement(t, x);
			if(stm) n.push(stm);
		}
		x.stmtStack.pop();
		n.blockId = ++blockId;
		n.scopeId = t.NewScopeId();
		n.end = t.cursor;
		n.line_end = t.line_start;
		return n;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function Block(t, x)
	{
		var start = t.start;
		var line_start = t.line_start;
		t.mustMatch(jsdef.LEFT_CURLY);
		var n = Statements(t, x);
		t.mustMatch(jsdef.RIGHT_CURLY);
		n.start = start;
		n.line_start = line_start;
		n.end = t.end;
		n.line_end = t.line_start;
		return n;
	}

	// ==================================================================================================================================
	//	    _   __                                                ____       _____       _ __  _
	//	   / | / /___ _____ ___  ___  _________  ____ _________  / __ \___  / __(_)___  (_) /_(_)___  ____
	//	  /  |/ / __ `/ __ `__ \/ _ \/ ___/ __ \/ __ `/ ___/ _ \/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	 / /|  / /_/ / / / / / /  __(__  ) /_/ / /_/ / /__/  __/ /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	/_/ |_/\__,_/_/ /_/ /_/\___/____/ .___/\__,_/\___/\___/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//	                               /_/
	// ==================================================================================================================================
	/*@@ NAMESPACE @@*/

	function NamespaceDefinition(t, x)
	{
		var f = new Node(t);
		if(t.match(jsdef.IDENTIFIER))
			f.name = t.token().value;
		t.mustMatch(jsdef.LEFT_CURLY);
		var x2 = new CompilerContext(false);
		f.body = Script(t, x2);
		t.mustMatch(jsdef.RIGHT_CURLY);
		f.end = t.cursor;
		f.line_end = t.line_start;
		return f;
	}

	// ==================================================================================================================================
	//	   _____ __                  __  ____       _____       _ __  _
	//	  / ___// /________  _______/ /_/ __ \___  / __(_)___  (_) /_(_)___  ____
	//	  \__ \/ __/ ___/ / / / ___/ __/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	 ___/ / /_/ /  / /_/ / /__/ /_/ /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	/____/\__/_/   \__,_/\___/\__/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ STRUCT @@*/

	function StructDefinition(t, x)
	{
		var f = new Node(t);
		t.mustMatch(jsdef.IDENTIFIER);
		f.name = t.token().value;
		t.mustMatch(jsdef.LEFT_CURLY);
		for(;t.peek()!=jsdef.RIGHT_CURLY;t.peek()!=jsdef.RIGHT_CURLY && t.mustMatch(jsdef.SEMICOLON))
		{
			t.mustMatch(jsdef.IDENTIFIER);
			var a = new Node(t, jsdef.IDENTIFIER);
			a.name = t.token().value;
			t.mustMatch(jsdef.COLON);
			matchVartype(t, a, "vartype");
			f.push(a);
		}
		t.mustMatch(jsdef.RIGHT_CURLY);
		f.end = t.cursor;
		f.line_end = t.line_start;
		return f;
	}

	// ==================================================================================================================================
	//	   ________                ____       _____       _ __  _
	//	  / ____/ /___ ___________/ __ \___  / __(_)___  (_) /_(_)___  ____
	//	 / /   / / __ `/ ___/ ___/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	/ /___/ / /_/ (__  |__  ) /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	\____/_/\__,_/____/____/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ CLASS @@*/
	function ClassDefinition(t, x, requireName, classForm, isInterface)
	{
		var f = new Node(t);
		f.scopeId = t.ScopeId();
		f.interfaces = [];
		f.interface = isInterface;

		if(t.match(jsdef.IDENTIFIER))
			f.name = t.token().value;

		else if(requireName)
			throw t.newSyntaxError("Missing function identifier");

		if(t.match(jsdef.COLON))
		{
			matchVartype(t, f, "extends");
			if(f.extends.indexOf("<")!=-1)
			{
				f.extends = f.extends.substr(0, f.extends.indexOf("<"));
			}

			// Multiple inheritance
			while(t.get()==jsdef.COMMA)
			{
				t.mustMatch(jsdef.IDENTIFIER);
				f.extends += "," + t.token().value;
			}
			t.unget();
		}

		// Interfaces
        if(t.match(jsdef.IMPLEMENTS))
        {
        	t.mustMatch(jsdef.IDENTIFIER);
        	f.interfaces.push(t.token().value);
        	while(t.get() == jsdef.COMMA)
        	{
				t.mustMatch(jsdef.IDENTIFIER);
				f.interfaces.push(t.token().value);
        	}
        	t.unget();
        }

		t.setModifiers(f);
		t.mustMatch(jsdef.LEFT_CURLY);

		var x2 = new CompilerContext(true);

		var mods = [jsdef.CLASS,
					jsdef.FUNCTION,
					jsdef.PROPERTY,
					jsdef.STATE,
					jsdef.STATIC,
					jsdef.REFERENCE,
					jsdef.VIRTUAL,
					jsdef.ABSTRACT,
					jsdef.DELEGATE,
					jsdef.VAR,
					jsdef.EVENT,
					jsdef.CONST,
					jsdef.ENUM];

		var classNode = f;

		f.body = (function (t, x)
		{
			var n = new Node(t, jsdef.BLOCK);
			x.stmtStack.push(n);

			do {

				t.resetModifiers();

				//===============================================================================================
				function recognizeStatement(n)
				{
					if(mods.switch(t.peek())==-1)
						throw t.newSyntaxError("Invalid class initialization");

					if(t.match(jsdef.STATIC)) t.static = true;
					if(t.match(jsdef.REFERENCE)) t.reference = true;
					if(t.match(jsdef.VIRTUAL)) t.virtual = true;
					if(t.match(jsdef.ABSTRACT)) t.abstract = true;
					if(t.match(jsdef.DELEGATE)) t.delegate = true;

					if(t.match(jsdef.CONST))
					{
						if(isInterface) throw t.newSyntaxError("Invalid statement inside Interface");
						n.push(VariablesDefinition(t, x));
					}
					else if(t.match(jsdef.VAR))
					{
						if(isInterface) throw t.newSyntaxError("Invalid statement inside Interface");
						n.push(VariablesDefinition(t, x));
					}
					else if(t.match(jsdef.EVENT))
					{
						if(isInterface) throw t.newSyntaxError("Invalid statement inside Interface");
						if(!t.public) throw t.newSyntaxError("Events must be public");
						n.push(EventDefinition(t, x));
					}
					else if(t.match(jsdef.ENUM))
					{
						if(isInterface) throw t.newSyntaxError("Invalid statement inside Interface");
						n.push(EnumerationDefinition(t, x));
					}
					else if(t.match(jsdef.PROPERTY))
					{
						n.push(PropertyDefinition(t, x));
					}
					else if(t.match(jsdef.FUNCTION))
					{
						n.push(FunctionDefinition(t, x, false, DECLARED_FORM, classNode));
					}
					else if(t.match(jsdef.STATE))
					{
						if(isInterface) throw t.newSyntaxError("Invalid statement inside Interface");
						n.push(StateDefinition(t, x));
					}
					else if(t.match(jsdef.CLASS))
					{
						if(isInterface) throw t.newSyntaxError("Invalid statement inside Interface");
						n.push(ClassDefinition(t, x, false, DECLARED_FORM));
					}
				}

				//===============================================================================================

                if(t.token().type == jsdef.FUNCTION)
                {
                	throw t.newSyntaxError("Missing function access modifier");
                }
				else if(t.token().type == jsdef.PUBLIC)
				{
					t.public = true;
                    recognizeStatement(n);
				}
				else if(t.token().type == jsdef.PRIVATE)
				{
					t.private = true;
					recognizeStatement(n);
				}
				else if(t.token().type == jsdef.PROTECTED)
				{
					t.protected = true;
                    recognizeStatement(n);
				}
				else if(t.token().type == jsdef.PUBLISHED)
				{
					t.public = true;
					t.published = true;
                    recognizeStatement(n);
				}
				else if(t.token().type == jsdef.STATIC)
				{
					t.protected = true;
					t.static = true;
					recognizeStatement(n);
				}
				else if(t.token().type == jsdef.REFERENCE)
				{
					t.reference = true;
					recognizeStatement(n);
				}
				else if(t.token().type == jsdef.CLASS)
				{
					// Class within-class in not supported yet
					//n.push(ClassDefinition(t, x, true, DECLARED_FORM));
					throw t.newSyntaxError("Invalid class initialization");
				}
				else if(t.token().type != jsdef.SEMICOLON && t.token().type != jsdef.LEFT_CURLY)
				{
					throw t.newSyntaxError("Invalid class initialization");
				}
				x.stmtStack.pop();
			}
			while (t.get() != jsdef.RIGHT_CURLY);

			n.blockId = ++blockId;
			n.scopeId = t.NewScopeId();
			n.type = jsdef.SCRIPT;
			n.funDecls = x.funDecls;
			n.varDecls = x.varDecls;
			n.contextId = ++contextId;
			n.scopeId = t.NewScopeId();
			return n;

		})(t, x2);

		// Add public var __className to all classes
		if(!isInterface)
		{
			f.body.push(add_var_string_node(t, "__className", f.name));
		}

		f.end = t.cursor;
		f.body.end = t.cursor;

		f.line_end = t.line_start;
		f.body.line_end = t.line_start;

		f.classForm = classForm;
		if(classForm == DECLARED_FORM)
			x.funDecls.push(f);

		return f;
	}

	function add_var_string_node(t, varName, varValue)
	{
		var clsId = new Node(t, jsdef.CONST);
		clsId.value="var";
		clsId.public=true;
		clsId.__rtti = true;
		var vt = new Node(t, jsdef.IDENTIFIER);
		vt.name = vt.value = varName;
		vt.vartype = "String";
		clsId.push(vt);
		var init = new Node(t, jsdef.STRING);
		init.value = varValue;
		vt.initializer = init;
		return clsId;
	}

	// ==================================================================================================================================
	//	    ______                 __  _             ____       _____       _ __  _
	//	   / ____/_  ______  _____/ /_(_)___  ____  / __ \___  / __(_)___  (_) /_(_)___  ____
	//	  / /_  / / / / __ \/ ___/ __/ / __ \/ __ \/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	 / __/ / /_/ / / / / /__/ /_/ / /_/ / / / / /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	/_/    \__,_/_/ /_/\___/\__/_/\____/_/ /_/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ FUNCTION @@*/

	function FunctionDefinition(t, x, requireName, functionForm, classNode)
	{
		var f = new Node(t);

		if(t.match(jsdef.IDENTIFIER))
		{
			var v = t.token().value;
			if(t.peek() == jsdef.IDENTIFIER)
			{
				if(v == "get")
				{
					f.isGetter = true;
				}
				else if(v == "set")
				{
					f.isSetter = true;
				}
				else
					throw t.newSyntaxError("Invalid function identifier");

				t.match(jsdef.IDENTIFIER);
				f.name = t.token().value;
			}
			else f.name = v;
		}

		else if(requireName)
			throw t.newSyntaxError("Missing function identifier");

		f.__start = t.token().start;
		f.__end = t.token().end;

		t.mustMatch(jsdef.LEFT_PAREN);
		f.params = [];
		f.paramsList = [];
		f.scopeId = t.ScopeId();
		var n2;
		if(t.peek() == jsdef.RIGHT_PAREN)
		{
			t.mustMatch(jsdef.RIGHT_PAREN);
		}
		else
		{
			var tt, restParam = false;
			tt = t.get();
			do
			{
				var _optional = false;
				if(tt == jsdef.RANGE)
				{
					t.get();
					f.restArguments = true;
					restParam = true;
				}
				else if(tt == jsdef.OPTIONAL)
				{
					_optional = true;
					tt = t.get();
				}
				else if(tt != jsdef.IDENTIFIER)
				{
					throw t.newSyntaxError("Missing formal parameter");
				}
				n2 = new Node(t);
				n2.name = n2.value;
				n2.optional = _optional;
				n2.scopeId = t.ScopeId();
				if(t.match(jsdef.COLON))
				{
					if(t.token().assignOp) throw t.newSyntaxError("Invalid parameter initialization");
					matchVartype(t, n2, "vartype");
				}
				if(t.match(jsdef.ASSIGN))
				{
					if(t.token().assignOp || restParam)
						throw t.newSyntaxError("Invalid variable initialization");
					n2.initializer = Expression(t, x, jsdef.COMMA);
				}
				if(restParam) n2.restParameter = true;
				f.params.push(n2.value);
				f.paramsList.push(n2);
				if(restParam && t.peek() != jsdef.RIGHT_PAREN)
				{
					throw t.newSyntaxError("Rest parameters must be the last paramter");
				}
				else if(t.peek() != jsdef.RIGHT_PAREN)
				{
					t.mustMatch(jsdef.COMMA);
					//Rest parameters
					if(t.peek() == jsdef.RANGE)
					{
						t.mustMatch(jsdef.RANGE);
						f.restArguments = true;
						restParam = true;
					}
					else
					{
						var p = t.peek();
						if(p!=jsdef.IDENTIFIER && p!=jsdef.OPTIONAL)
							throw t.newSyntaxError("Missing formal parameter");
					}
				}
			}
			while ((tt = t.get()) != jsdef.RIGHT_PAREN);
		}

		switch(f.name)
		{
		case "Constructor": classNode.constructorNode=f;f.isConstructor = true; break;
		case "Destructor": classNode.destructorNode=f;f.isDestructor = true; break;
		}

		if(t.match(jsdef.COLON))
		{
			// Constructor arguments:
			// public function Constructor(arg1:String) : ClassTest3(arg1, "arg2")
			if(f.name=="Constructor" && classNode && t.peek()==jsdef.IDENTIFIER)
			{
				t.mustMatch(jsdef.IDENTIFIER);
				if(t.token().value==classNode.extends)
				{
					t.mustMatch(jsdef.LEFT_PAREN);

					// Create a pseudo-call
					classNode.base_init= new Node(t, jsdef.CONSTRUCTOR_CALL);

					// Save base class identifier
					var n2=new Node(t, jsdef.IDENTIFIER);
					n2.value = classNode.extends;
					classNode.base_init.push(n2);

					// Create a LIST
					var n3=new Node(t, jsdef.LIST);
					classNode.base_init.push(n3);

					while(t.peek()!=jsdef.RIGHT_PAREN)
					{
						t.get();
						var arg = new Node(t);
						n3.push(arg);
						if(t.peek()!=jsdef.COMMA)
							break;
						t.get();
					}
					t.mustMatch(jsdef.RIGHT_PAREN);
				}
				else
				{
					t.unget();
				}
			}

			// Standard Function Return Type
			else
			{
				matchVartype(t, f, "returntype");
				if(t.match(jsdef.NOT)) f.returntype += "!";
			}
		}

		if(t.commentLine+2>=f.line_start)
		{
			// Parse JSDoc comment into node
			JSDocParse(f, t.comment);
		}
		t.setModifiers(f);

		if(f.abstract || (classNode && classNode.type==jsdef.INTERFACE))
		{
			t.mustMatch(jsdef.SEMICOLON);
		}
		else
		{
			var x2;
			if(t.match(jsdef.LEFT_CURLY))
			{
				x2 = new CompilerContext(true);
				f.body = Script(t, x2);
				t.mustMatch(jsdef.RIGHT_CURLY);
			}
			else
			{
				x2 = new CompilerContext(true);
				var n3 = new Node(t);
				n3.type = jsdef.SCRIPT;
				n3.funDecls = x2.funDecls;
				n3.varDecls = x2.varDecls;
				n3.contextId = ++contextId;
				n3.scopeId = t.NewScopeId();
				t.expClosure = true;
				n3[0] = Expression(t, x2);
				if(n3[0].type != jsdef.RETURN)
				{
					throw t.newSyntaxError("Missing return in expression closure");
				}
				f.body = n3;
			}
		}

		f.end = t.cursor;
		if(f.body) f.body.end = t.cursor;

		f.line_end = t.line_start;
		if(f.body) f.body.line_end = t.line_start;

		f.functionForm = functionForm;
		if(functionForm == DECLARED_FORM)
			x.funDecls.push(f);

		return f;
	}

	// ==================================================================================================================================
	//	 _    __           _       __    __
	//	| |  / /___ ______(_)___ _/ /_  / /__  _____
	//	| | / / __ `/ ___/ / __ `/ __ \/ / _ \/ ___/
	//	| |/ / /_/ / /  / / /_/ / /_/ / /  __(__  )
	//	|___/\__,_/_/  /_/\__,_/_.___/_/\___/____/
	//
	// ==================================================================================================================================
	/*@@ VAR @@*/

	function VariablesDefinition(t, x)
	{
		var n = new Node(t);

		//Destructuring assignments
		if(t.match(jsdef.LEFT_BRACKET))
		{
			var n2 = new Node(t, jsdef.ARRAY_INIT),
				vartype = "";
			while((tt = t.peek()) != jsdef.RIGHT_BRACKET)
			{
				if(tt == jsdef.COMMA)
				{
					t.get();
					emptyEl = new Node(t, jsdef.VOID);
					emptyEl[0] = new Node(t, jsdef.NUMBER);
					emptyEl[0].value = 0;
					n2.push(emptyEl);
					continue;
				}
				if(t.match(jsdef.IDENTIFIER))
				{
					n2.push(new Node(t));
				}
				else
				{
					throw t.newSyntaxError("Invalid variable initialization");
				}
				if(!t.match(jsdef.COMMA))
					break;
			}
			t.mustMatch(jsdef.RIGHT_BRACKET);

			if(t.match(jsdef.COLON))
			{
				if(t.token().assignOp) throw t.newSyntaxError("Invalid variable initialization");
				matchVartype(t, n2, "vartype");
				if(t.match(jsdef.NOT)) n2.vartype += "!";
			}

			if(t.match(jsdef.ASSIGN))
			{
				if(t.token().assignOp)
					throw t.newSyntaxError("Invalid variable initialization");
				n2.initializer = Expression(t, x, jsdef.COMMA);
			}
			n.push(n2);
			x.varDecls.push(n2);
		}

		//Regular variable declarations
		else
		{
			do
			{
				t.setModifiers(n);
				t.mustMatch(jsdef.IDENTIFIER);
				var n2 = new Node(t), vartype = "";
				n2.name = n2.value;
				if(t.match(jsdef.COLON))
				{
					if(t.token().assignOp) throw t.newSyntaxError("Invalid variable initialization");
                    matchVartype(t, n2, "vartype");
					if(t.match(jsdef.NOT)) n2.vartype += "!";
				}
				if(t.match(jsdef.ASSIGN))
				{
					if(t.token().assignOp) throw t.newSyntaxError("Invalid variable initialization");
					n2.initializer = Expression(t, x, jsdef.COMMA);
					if(!n2.vartype) n2.vartype = detectDataType(n2.initializer);
				}
				n2.readOnly = (n.type == jsdef.CONST);
				n.push(n2);
				x.varDecls.push(n);
			}
			while (t.match(jsdef.COMMA));
		}
		return n;
	}

	/*@@ matchVartype @@*/
	function matchVartype(t, node, typeProp, skip)
	{
		node[typeProp] = null;
		node["subtype"] = null;

		t.mustMatch(jsdef.IDENTIFIER);
		var vartype = t.token().value;
		var subtype = "";
		node[typeProp] = vartype;

		// Typed Array
		if(!skip && t.match(jsdef.LT))
		{
			t.mustMatch(jsdef.IDENTIFIER);
			subtype = new Node(t).value;
			node.subtype = subtype;
			t.mustMatch(jsdef.GT);
			node[typeProp] = vartype + "<" + subtype + ">";
			if(typeProp=="returntype")
				node["vartype"] = vartype + "<" + subtype + ">";
		}
	}

	// ==================================================================================================================================
	//	   ______      ________             __   ____       _____       _ __  _
	//	  / ____/___ _/ / / __ )____ ______/ /__/ __ \___  / __(_)___  (_) /_(_)___  ____
	//	 / /   / __ `/ / / __  / __ `/ ___/ //_/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	/ /___/ /_/ / / / /_/ / /_/ / /__/ ,< / /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	\____/\__,_/_/_/_____/\__,_/\___/_/|_/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ CALLBACK @@*/

	function CallbackDefinition(t,x)
	{
		//callback CocoEventHandler(Sender:CocoEventSource, Event:CocoEvent) :Boolean {}
		f = new Node(t,jsdef.CALLBACK);
		t.mustMatch(jsdef.IDENTIFIER);
		f.name = t.token().value;
		t.mustMatch(jsdef.LEFT_PAREN);
		f.params=[];
		f.paramsList=[];
		while(t.peek()==jsdef.IDENTIFIER)
		{
			t.mustMatch(jsdef.IDENTIFIER);
			n2 = new Node(t);
			n2.value = t.token().value;
			t.mustMatch(jsdef.COLON);
			t.mustMatch(jsdef.IDENTIFIER);
			n2.vartype = t.token().value;
			f.params.push(n2.value);
			f.paramsList.push(n2);
			if(t.peek()!=jsdef.COMMA) break;
			t.mustMatch(jsdef.COMMA);
		}
		t.mustMatch(jsdef.RIGHT_PAREN);
		if(t.peek()==jsdef.COLON)
		{
			t.mustMatch(jsdef.COLON);
			matchVartype(t, f, "returntype");
		}
		t.mustMatch(jsdef.LEFT_CURLY);
		t.mustMatch(jsdef.RIGHT_CURLY);
		return f;
	}

	// ==================================================================================================================================
	//	    ______                 __  ____       _____       _ __  _
	//	   / ____/   _____  ____  / /_/ __ \___  / __(_)___  (_) /_(_)___  ____
	//	  / __/ | | / / _ \/ __ \/ __/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	 / /___ | |/ /  __/ / / / /_/ /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	/_____/ |___/\___/_/ /_/\__/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ EVENT @@*/

	function EventDefinition(t,x)
	{
		t.mustMatch(jsdef.IDENTIFIER);

		var e = new Node(t, jsdef.EVENT);
		e.value = t.token().value;
		e.name = e.value;
		e.vartype = "CocoEvent";
		e.paramsList = [];
		e.params = [];

		var idf = new Node(t, jsdef.IDENTIFIER);
		idf.value = e.name;
		e.push(idf);

		var list = new Node(t, jsdef.LIST);
		e.push(list);

		t.mustMatch(jsdef.LEFT_PAREN);
		for(;t.peek()!=jsdef.RIGHT_PAREN;t.peek()!=jsdef.RIGHT_PAREN && t.mustMatch(jsdef.COMMA))
		{
			t.mustMatch(jsdef.IDENTIFIER);
			var a = new Node(t, jsdef.IDENTIFIER);
			a.name = t.token().value;
			t.mustMatch(jsdef.COLON);
			matchVartype(t, a, "vartype");
			list.push(a);
			e.paramsList.push(a);
			e.params.push(a.name);
		}
		t.mustMatch(jsdef.RIGHT_PAREN);
		return e;
	}

	// ==================================================================================================================================
	//	    ______                                      __  _
	//	   / ____/___  __  ______ ___  ___  _________ _/ /_(_)___  ____
	//	  / __/ / __ \/ / / / __ `__ \/ _ \/ ___/ __ `/ __/ / __ \/ __ \
	//	 / /___/ / / / /_/ / / / / / /  __/ /  / /_/ / /_/ / /_/ / / / /
	//	/_____/_/ /_/\__,_/_/ /_/ /_/\___/_/   \__,_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ ENUM @@*/

	function EnumerationDefinition(t,x)
	{
		var n = new Node(t, jsdef.ENUM);
		t.setModifiers(n);
		t.mustMatch(jsdef.IDENTIFIER);
		n.name = t.token().value;
		n.vartype = n.name;
		n.__start = t.token().start;
		n.__end = t.token().end;
		t.mustMatch(jsdef.LEFT_CURLY)
		for(;;)
		{
			t.mustMatch(jsdef.IDENTIFIER);
			var f = new Node(t, jsdef.ENUM_ITEM);
			f.name = t.token().value;
			f.vartype = n.name;
            t.mustMatch(jsdef.ASSIGN);
            var m = false;
            if(t.match(jsdef.UNARY_MINUS))
            	m = true;
            t.mustMatch(jsdef.NUMBER);
            f.value = (m ? "-" : "") + t.token().value;
            n.push(f);
            if(!t.match(jsdef.COMMA))
            	break;
		}
		t.mustMatch(jsdef.RIGHT_CURLY);
		n.end = t.cursor;
		n.line_end = t.line_start;
		return n;
	}

	// ==================================================================================================================================
	//	    ____                             __        ____       _____       _ __  _
	//	   / __ \_________  ____  ___  _____/ /___  __/ __ \___  / __(_)___  (_) /_(_)___  ____
	//	  / /_/ / ___/ __ \/ __ \/ _ \/ ___/ __/ / / / / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	 / ____/ /  / /_/ / /_/ /  __/ /  / /_/ /_/ / /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	/_/   /_/   \____/ .___/\___/_/   \__/\__, /_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//	                /_/                  /____/
	// ==================================================================================================================================
	/*@@ PROPERTY @@*/

	function PropertyDefinition(t, x)
	{
		var p = new Node(t, jsdef.PROPERTY);
		t.setModifiers(p);
		t.mustMatch(jsdef.IDENTIFIER);
		p.name = t.token().value;
		p.__start = t.token().start;
		p.__end = t.token().end;
		t.mustMatch(jsdef.LEFT_CURLY)
		x2 = new CompilerContext(true);
		p.body = Script(t, x2);
		t.mustMatch(jsdef.RIGHT_CURLY);
		for(item in p.body)
		{
			if(!isFinite(item)) break;
			if(p.body[item].type==jsdef.FUNCTION)
			{
				if(p.body[item].name=="set")
				{
					p.setter = p.body[item];
					t.copyModifiers(p, p.setter);
					continue;
				}
				else if(p.body[item].name=="get")
				{
					p.getter = p.body[item];
					t.copyModifiers(p, p.getter);
					continue;
				}
			}
			throw t.newSyntaxError("Invalid inside property definition");
		}

		if(!p.getter)
			throw t.newSyntaxError("Missing property getter");

		//p.body = null;
		p.vartype = p.getter.returntype;
		p.subtype = p.getter.subtype;
		return p;
	}

	// ==================================================================================================================================
	//	   _____ __        __       ____       _____       _ __  _
	//	  / ___// /_____ _/ /____  / __ \___  / __(_)___  (_) /_(_)___  ____
	//	  \__ \/ __/ __ `/ __/ _ \/ / / / _ \/ /_/ / __ \/ / __/ / __ \/ __ \
	//	 ___/ / /_/ /_/ / /_/  __/ /_/ /  __/ __/ / / / / / /_/ / /_/ / / / /
	//	/____/\__/\__,_/\__/\___/_____/\___/_/ /_/_/ /_/_/\__/_/\____/_/ /_/
	//
	// ==================================================================================================================================
	/*@@ STATE @@*/

	function StateDefinition(t, x)
	{
		var n = new Node(t, jsdef.STATE);
		n.vartype = "State";
		t.setModifiers(n);
		t.mustMatch(jsdef.IDENTIFIER);
		n.name = t.token().value;
		n.__start = t.token().start;
		n.__end = t.token().end;
		t.mustMatch(jsdef.LEFT_CURLY)
		x2 = new CompilerContext(true);
		n.body = Script(t, x2);
		for(item in n.body)
		{
			if(!isFinite(item)) break;
			var f = n.body[item];
			switch(f.type)
			{
			case jsdef.FUNCTION:

				switch(f.name)
				{
				case "enter": f.public=true; break;
				case "exit":  f.public=true; break;
				case "tick":  f.public=true; break;
				case "paint": f.public=true; break;
				case "paintCanvas": f.public=true; break;
				default:
					throw t.newSyntaxError("Invalid function inside State");
				}
				break;

			case jsdef.VAR:
				break;

			default:
				throw t.newSyntaxError("Invalid statement inside State");
			}
		}
		t.mustMatch(jsdef.RIGHT_CURLY);
		n.end = t.cursor;
		n.body.end = t.cursor;
		n.line_end = t.line_start;
		n.body.line_end = t.line_start;
		return n;
	}

	// ==================================================================================================================================
	//	   _____ __        __                            __          ____
	//	  / ___// /_____ _/ /____  ____ ___  ___  ____  / /______   / __ \____ ______________  _____
	//	  \__ \/ __/ __ `/ __/ _ \/ __ `__ \/ _ \/ __ \/ __/ ___/  / /_/ / __ `/ ___/ ___/ _ \/ ___/
	//	 ___/ / /_/ /_/ / /_/  __/ / / / / /  __/ / / / /_(__  )  / ____/ /_/ / /  (__  )  __/ /
	//	/____/\__/\__,_/\__/\___/_/ /_/ /_/\___/_/ /_/\__/____/  /_/    \__,_/_/  /____/\___/_/
	//
	// ==================================================================================================================================
	/*@@ Statements Parser @@*/

	var DECLARED_FORM = 0,
		EXPRESSED_FORM = 1,
		STATEMENT_FORM = 2;

	function Statement(t, x)
	{
		var i, label, n, n2, ss, tt = t.get();

		// Cases for statements ending in a right curly return early,
		// avoiding the common semicolon insertion magic after this switch.

		switch(tt)
		{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NAMESPACE:
			return NamespaceDefinition(t, x);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.STRUCT:
			return StructDefinition(t,x);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CLASS:
			return ClassDefinition(t, x, true, (x.stmtStack.length > 1) ? STATEMENT_FORM : DECLARED_FORM);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CONTROL:
			t.get();
			var n = ClassDefinition(t, x, true);
			n.control = true;
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.EMSCRIPTEN:
			t.get();
			var n = ClassDefinition(t, x, true);
			n.emscripten = true;
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.INTERFACE:
			return ClassDefinition(t, x, true, (x.stmtStack.length > 1) ? STATEMENT_FORM : DECLARED_FORM, true);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.FUNCTION:
			return FunctionDefinition(t, x, true, (x.stmtStack.length > 1) ? STATEMENT_FORM : DECLARED_FORM);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.VAR:
		case jsdef.CONST:
			n = VariablesDefinition(t, x);
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CALLBACK:
			return CallbackDefinition(t, x);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.ENUM:
			n = EnumerationDefinition(t,x);
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.STATE:
			switch(t.peek())
			{
			case jsdef.CLASS:
				t.get();
				var n = ClassDefinition(t, x, true);
				n.state = true;
				return n;

			case jsdef.FUNCTION:
				t.get();
				var n = FunctionDefinition(t, x, true, DECLARED_FORM);
				n.state = true;
				return n;
			}
			return StateDefinition(t, x);

		// ==================================================================================================================================
		//	    ___        __  _                _____           _       __     _____
		//	   /   | _____/ /_(_)___  ____     / ___/__________(_)___  / /_   |__  /
		//	  / /| |/ ___/ __/ / __ \/ __ \    \__ \/ ___/ ___/ / __ \/ __/    /_ <
		//	 / ___ / /__/ /_/ / /_/ / / / /   ___/ / /__/ /  / / /_/ / /_    ___/ /
		//	/_/  |_\___/\__/_/\____/_/ /_/   /____/\___/_/  /_/ .___/\__/   /____/
		//	                                                 /_/
		// ==================================================================================================================================
		/*@@ AS3 Parser @@*/

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case jsdef.PACKAGE:
        	while(t.peek() != jsdef.LEFT_CURLY)
        		t.get();
			return null;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case jsdef.USE:
        case jsdef.IMPORT:
        	while(t.get() != jsdef.SEMICOLON);
			return null;

		// ==================================================================================================================================
		//	    ______________  ______           __                  _____           _       __     _____ __        __                            __
		//	   / ____/ ____/  |/  /   |         / /___ __   ______ _/ ___/__________(_)___  / /_   / ___// /_____ _/ /____  ____ ___  ___  ____  / /______
		//	  / __/ / /   / /|_/ / /| |    __  / / __ `/ | / / __ `/\__ \/ ___/ ___/ / __ \/ __/   \__ \/ __/ __ `/ __/ _ \/ __ `__ \/ _ \/ __ \/ __/ ___/
		//	 / /___/ /___/ /  / / ___ |   / /_/ / /_/ /| |/ / /_/ /___/ / /__/ /  / / /_/ / /_    ___/ / /_/ /_/ / /_/  __/ / / / / /  __/ / / / /_(__  )
		//	/_____/\____/_/  /_/_/  |_|   \____/\__,_/ |___/\__,_//____/\___/_/  /_/ .___/\__/   /____/\__/\__,_/\__/\___/_/ /_/ /_/\___/_/ /_/\__/____/
		//	                                                                      /_/
		// ==================================================================================================================================
		/*@@ ECMA Parser @@*/

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.LEFT_CURLY:
			n = Statements(t, x);
			t.mustMatch(jsdef.RIGHT_CURLY);
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.IF:
			n = new Node(t);
			n.condition = ParenExpression(t, x);
			x.stmtStack.push(n);
			n.thenPart = Statement(t, x);
			n.elsePart = t.match(jsdef.ELSE) ? Statement(t, x) : null;
			x.stmtStack.pop();
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.SWITCH:
			n = new Node(t);
			t.mustMatch(jsdef.LEFT_PAREN);
			n.discriminant = Expression(t, x);
			t.mustMatch(jsdef.RIGHT_PAREN);
			n.cases = [];
			n.defaultIndex = -1;
			x.stmtStack.push(n);
			t.mustMatch(jsdef.LEFT_CURLY);
			while((tt = t.get()) != jsdef.RIGHT_CURLY)
			{
				switch(tt)
				{
				case jsdef.DEFAULT:
					if(n.defaultIndex >= 0) throw t.newSyntaxError("More than one switch default");
					// FALL THROUGH
				case jsdef.CASE:
					n2 = new Node(t);
					n2.scopeId = t.ScopeId();
					if(tt == jsdef.DEFAULT)
						n.defaultIndex = n.cases.length;
					else
						n2.caseLabel = Expression(t, x, jsdef.COLON);
					break;
				default:
					throw t.newSyntaxError("Invalid switch case");
				}
				t.mustMatch(jsdef.COLON);
				n2.statements = new Node(t, jsdef.BLOCK);
				while((tt = t.peek()) != jsdef.CASE && tt != jsdef.DEFAULT && tt != jsdef.RIGHT_CURLY)
					n2.statements.push(Statement(t, x));
				n.cases.push(n2);
			}
			x.stmtStack.pop();
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.FOR:
			n = new Node(t);
			n.isLoop = true;
			t.mustMatch(jsdef.LEFT_PAREN);
			if((tt = t.peek()) != jsdef.SEMICOLON)
			{
				x.inForLoopInit = true;
				if(tt == jsdef.VAR || tt == jsdef.LET)
				{
					t.get();
					n2 = VariablesDefinition(t, x);
				}
				else
				{
					n2 = Expression(t, x);
				}
				x.inForLoopInit = false;
			}
			if(n2 && t.match(jsdef.IN))
			{
				n.type = jsdef.FOR_IN;
				if(n2.type == jsdef.VAR || n2.type == jsdef.LET)
				{
					if(n2.length != 1)
					{
						throw new SyntaxError("Invalid for..in left-hand side", t.filename, n2.line_start);
					}
					n.iterator = n2;
					n.varDecl = n2;
				}
				else
				{
					n.iterator = n2;
					n.varDecl = null;
				}
				n.object = Expression(t, x);
			}
			else
			{
				n.setup = n2 || null;
				t.mustMatch(jsdef.SEMICOLON);
				n.condition = (t.peek() == jsdef.SEMICOLON) ? null : Expression(t, x);
				t.mustMatch(jsdef.SEMICOLON);
				n.update = (t.peek() == jsdef.RIGHT_PAREN) ? null : Expression(t, x);
			}
			t.mustMatch(jsdef.RIGHT_PAREN);
			n.body = nest(t, x, n, Statement);
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.WHILE:
			n = new Node(t);
			n.isLoop = true;
			n.condition = ParenExpression(t, x);
			n.body = nest(t, x, n, Statement);
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DO:
			n = new Node(t);
			n.isLoop = true;
			n.body = nest(t, x, n, Statement, jsdef.WHILE);
			n.condition = ParenExpression(t, x);
			if(!x.ecmaStrictMode)
			{
				// <script language="JavaScript"> (without version hints) may need
				// automatic semicolon insertion without a newline after do-while.
				// See http://bugzilla.mozilla.org/show_bug.cgi?id=238945.
				t.match(jsdef.SEMICOLON);
				return n;
			}
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.BREAK:
		case jsdef.CONTINUE:
			n = new Node(t);
			if(t.peekOnSameLine() == jsdef.IDENTIFIER)
			{
				t.get();
				n.label = t.token().value;
			}
			ss = x.stmtStack;
			i = ss.length;
			label = n.label;
			if(label)
			{
				do
				{
					if(--i < 0)
						throw t.newSyntaxError("Label not found");
				}
				while (ss[i].label != label);
			}
			else
			{
				do
				{
					if(--i < 0)
					{
						throw t.newSyntaxError("Invalid " + ((tt == jsdef.BREAK) ? "break" : "continue"));
					}
				}
				while (!ss[i].isLoop && (tt != jsdef.BREAK || ss[i].type != jsdef.SWITCH));
			}
			n.target = ss[i];
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.TRY:
			n = new Node(t);
			n.tryBlock = Block(t, x);
			n.catchClauses = [];
			while(t.match(jsdef.CATCH))
			{
				n2 = new Node(t);
				t.mustMatch(jsdef.LEFT_PAREN);
				n2.varName = t.mustMatch(jsdef.IDENTIFIER).value;
				if(t.match(jsdef.IF))
				{
					if(x.ecmaStrictMode)
						throw t.newSyntaxError("Illegal catch guard");
					if(n.catchClauses.length && !n.catchClauses.top().guard)
						throw t.newSyntaxError("Guarded catch after unguarded");
					n2.guard = Expression(t, x);
				}
				else
				{
					n2.guard = null;
				}
				t.mustMatch(jsdef.RIGHT_PAREN);
				n2.block = Block(t, x);
				n.catchClauses.push(n2);
			}
			if(t.match(jsdef.FINALLY))
				n.finallyBlock = Block(t, x);
			if(!n.catchClauses.length && !n.finallyBlock)
				throw t.newSyntaxError("Invalid try statement");
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.CATCH:
		case jsdef.FINALLY:
			throw t.newSyntaxError(jsdef.tokens[tt] + " without preceding try");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.THROW:
			n = new Node(t);
			n.exception = Expression(t, x);
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.RETURN:
			if(!x.inFunction)
				throw t.newSyntaxError("Invalid return");
			n = new Node(t);
			tt = t.peekOnSameLine();
			if(tt != jsdef.END && tt != jsdef.NEWLINE && tt != jsdef.SEMICOLON && tt != jsdef.RIGHT_CURLY)
				n.value = Expression(t, x);
			if(!(n.value instanceof Node))
				n.value = null;
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.WITH:
			n = new Node(t);
			n.object = ParenExpression(t, x);
			n.body = nest(t, x, n, Statement);
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.LET:
			n = VariablesDefinition(t, x);
			n.block = true;
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.DEBUGGER:
			n = new Node(t);
			break;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case jsdef.NEWLINE:
		case jsdef.SEMICOLON:
			n = new Node(t, jsdef.SEMICOLON);
			n.expression = null;
			return n;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		default:
			if(tt == jsdef.IDENTIFIER)
			{
				t.scanOperand = false;
				tt = t.peek();
				t.scanOperand = true;
				if(tt == jsdef.COLON)
				{
					label = t.token().value;
					ss = x.stmtStack;
					for(i = ss.length - 1; i >= 0; --i)
					{
						if(ss[i].label == label)
							throw t.newSyntaxError("Duplicate label");
					}
					t.get();
					n = new Node(t, jsdef.LABEL);
					n.label = label;
					n.statement = nest(t, x, n, Statement);
					return n;
				}
			}
			n = new Node(t, jsdef.SEMICOLON);
			t.unget();
			n.expression = Expression(t, x);

			n.end = t.cursor;// n.expression.end;
			n.line_end = t.line_start;// n.expression.line_end;
			break;
		}
		if(t.line_start == t.token().line_start)
		{
			tt = t.peekOnSameLine();
			if(tt != jsdef.END && tt != jsdef.NEWLINE && tt != jsdef.SEMICOLON && tt != jsdef.RIGHT_CURLY)
				throw t.newSyntaxError("Missing ; before statement");
		}
		t.match(jsdef.SEMICOLON);

		n.end = t.cursor;
		n.line_end = t.line_start;

		return n;
	}
	// ==================================================================================================================================
	//	    ____        __        __                      ____       __            __  _
	//	   / __ \____ _/ /_____ _/ /___  ______  ___     / __ \___  / /____  _____/ /_(_)___  ____
	//	  / / / / __ `/ __/ __ `/ __/ / / / __ \/ _ \   / / / / _ \/ __/ _ \/ ___/ __/ / __ \/ __ \
	//	 / /_/ / /_/ / /_/ /_/ / /_/ /_/ / /_/ /  __/  / /_/ /  __/ /_/  __/ /__/ /_/ / /_/ / / / /
	//	/_____/\__,_/\__/\__,_/\__/\__, / .___/\___/  /_____/\___/\__/\___/\___/\__/_/\____/_/ /_/
	//	                          /____/_/
	// ==================================================================================================================================
    /*@@ Type Inferencing @@*/

    // Experimental: heuristics based variable datatype detection when not pluggable type system is used.
    function detectDataType(varItem)
    {
        if(!varItem.value) return;
        var dt = undefined;

        switch(varItem.type)
        {
    	case jsdef.STRING:
            dt = "String";
            break;

    	case jsdef.DATE:
            dt = "Date";
            break;

    	case jsdef.REGEXP:
            dt = "RegExp";
            break;

        // Numbers and numeric operators result in Number!
        case jsdef.NUMBER:
        case jsdef.ADD:
        case jsdef.DECREMENT:
        case jsdef.DIV:
        case jsdef.EXPONENT:
        case jsdef.INCREMENT:
        case jsdef.LSH:
        case jsdef.MINUS:
        case jsdef.MOD:
        case jsdef.MUL:
        case jsdef.PLUS:
        case jsdef.RSH:
        case jsdef.SUB:
        case jsdef.URSH:
        case jsdef.UNARY_PLUS:
        case jsdef.UNARY_MINUS:
            dt = "Number";
            break;

        // Booleans and logic operators result in Boolean!
        case jsdef.FALSE:
        case jsdef.TRUE:
        case jsdef.BITWISE_OR:
        case jsdef.BITWISE_XOR:
        case jsdef.BITWISE_AND:
        case jsdef.STRICT_EQ:
        case jsdef.EQ:
        case jsdef.STRICT_NE:
        case jsdef.NE:
        case jsdef.LE:
        case jsdef.LT:
        case jsdef.GE:
        case jsdef.GT:
            dt = "Boolean";
            break;
        }

        return dt;
    }

	// ==================================================================================================================================
	//	    ______                               _                ____
	//	   / ____/  ______  ________  __________(_)___  ____     / __ \____ ______________  _____
	//	  / __/ | |/_/ __ \/ ___/ _ \/ ___/ ___/ / __ \/ __ \   / /_/ / __ `/ ___/ ___/ _ \/ ___/
	//	 / /____>  </ /_/ / /  /  __(__  |__  ) / /_/ / / / /  / ____/ /_/ / /  (__  )  __/ /
	//	/_____/_/|_/ .___/_/   \___/____/____/_/\____/_/ /_/  /_/    \__,_/_/  /____/\___/_/
	//	          /_/
	// ==================================================================================================================================
	/*@@ Expression Parser @@*/

	function ParenExpression(t, x)
	{
		t.mustMatch(jsdef.LEFT_PAREN);
		var n = Expression(t, x);
		t.mustMatch(jsdef.RIGHT_PAREN);
		return n;
	}

	var opPrecedence =
	{
		SEMICOLON: 0,
		COMMA: 1,
		ASSIGN: 2,
		HOOK: 2,
		COLON: 2,
		// The above all have to have the same precedence, see bug 330975.
		OR: 4,
		AND: 5,
		BITWISE_OR: 6,
		BITWISE_XOR: 7,
		BITWISE_AND: 8,
		EQ: 9,
		NE: 9,
		STRICT_EQ: 9,
		STRICT_NE: 9,
		LT: 10,
		LE: 10,
		GE: 10,
		GT: 10,
		IN: 10,
		INSIDE: 10,
		INSTANCEOF: 10,
		IS: 10,
		LSH: 11,
		RSH: 11,
		URSH: 11,
		PLUS: 12,
		MINUS: 12,
		MUL: 13,
		DIV: 13,
		MOD: 13,
		REGEXP_MATCH: 13,
		DELETE: 14,
		VOID: 14,
		TYPEOF: 14, // PRE_INCREMENT: 14, PRE_DECREMENT: 14,
		NOT: 14,
		BITWISE_NOT: 14,
		UNARY_PLUS: 14,
		UNARY_MINUS: 14,
		UNARY_EXISTS: 14,
		RANGE: 14,
		EXPONENT: 14,
		INCREMENT: 15,
		DECREMENT: 15, // postfix
		PUBLIC: 16,
		PRIVATE: 16,
		PROTECTED: 16,
		PUBLISHED: 16,
		STATIC: 16,
		REFERENCE:16,
		NEW: 17,
		DOT: 18
	};

	// Map operator type code to precedence.
	for(var i in opPrecedence)
		if(jsdef[i]) opPrecedence[jsdef[i]] = opPrecedence[i];

	var opArity =
	{
		COMMA: -2,
		ASSIGN: 2,
		HOOK: 3,
		OR: 2,
		AND: 2,
		BITWISE_OR: 2,
		BITWISE_XOR: 2,
		BITWISE_AND: 2,
		EQ: 2,
		NE: 2,
		STRICT_EQ: 2,
		STRICT_NE: 2,
		LT: 2,
		LE: 2,
		GE: 2,
		GT: 2,
		IN: 2,
		INSIDE: 2,
		INSTANCEOF: 2,
		IS: 2,
		LSH: 2,
		RSH: 2,
		URSH: 2,
		PLUS: 2,
		MINUS: 2,
		MUL: 2,
		DIV: 2,
		MOD: 2,
		EXPONENT: 2,
		DELETE: 1,
		VOID: 1,
		TYPEOF: 1,
		// PRE_INCREMENT: 1, PRE_DECREMENT: 1,
		NOT: 1,
		BITWISE_NOT: 1,
		UNARY_PLUS: 1,
		UNARY_MINUS: 1,
		UNARY_EXISTS: 1,
		INCREMENT: 1,
		DECREMENT: 1, // postfix
		NEW: 1,
		NEW_WITH_ARGS: 2,
		DOT: 2,
		INDEX: 2,
		CALL: 2,
		ARRAY_INIT: 1,
		OBJECT_INIT: 1,
		GROUP: 1,
		REGEXP_MATCH: 1,
		RANGE: 2,
		PUBLIC: 1,
		PRIVATE: 1,
		PROTECTED: 1,
		PUBLISHED: 1,
		STATIC: 1,
		REFERENCE: 1
	};

	// Map operator type code to arity.
	for(var i in opArity)
		if(jsdef[i]) opArity[jsdef[i]] = opArity[i];

	function Expression(t, x, stop)
	{
		var n, id, tt, operators = [],
			operands = [];
		var bl = x.bracketLevel,
			cl = x.curlyLevel,
			pl = x.parenLevel,
			hl = x.hookLevel;

		function reduce()
		{
			var n = operators.pop();
			var op = n.type;
			var arity = opArity[op];
			if(arity == -2)
			{
				// Flatten left-associative trees.
				var left = operands.length >= 2 && operands[operands.length - 2];
				if(left.type == op)
				{
					var right = operands.pop();
					left.push(right);
					return left;
				}
				arity = 2;
			}
			// Always use push to add operands to n, to update start and end.
			var a = operands.splice(operands.length - arity, arity);
			for(var i = 0; i < arity; i++)
				n.push(a[i]);

			// Include closing bracket or postfix operator in [start,end).
			if(n.end < t.token().end)
			{
				n.end = t.token().end;
				n.line_end = t.line_start;
			}
			operands.push(n);
			return n;
		}
		loop: while((tt = t.get()) != jsdef.END)
		{
			if(tt == stop &&
				x.bracketLevel == bl && x.curlyLevel == cl && x.parenLevel == pl &&
				x.hookLevel == hl)
			{
				// Stop only if tt matches the optional stop parameter, and that
				// token is not quoted by some kind of bracket.
				break;
			}
			switch(tt)
			{
			case jsdef.SEMICOLON:
				// NB: cannot be empty, Statement handled that.
				break loop;

			case jsdef.ASSIGN:
			case jsdef.HOOK:
			case jsdef.COLON:
				if(t.scanOperand)
					break loop;
				// Use >, not >=, for right-associative jsdef.ASSIGN and jsdef.HOOK/jsdef.COLON.
				while(opPrecedence[operators.top().type] > opPrecedence[tt] ||
					(tt == jsdef.COLON && operators.top().type == jsdef.ASSIGN))
				{
					reduce();
				}
				if(tt == jsdef.COLON)
				{
					n = operators.top();
					if(n.type != jsdef.HOOK)
						throw t.newSyntaxError("Invalid label");
					--x.hookLevel;
				}
				else
				{
					operators.push(new Node(t));
					if(tt == jsdef.ASSIGN)
						operands.top().assignOp = t.token().assignOp;
					else ++x.hookLevel; // tt == jsdef.HOOK
				}
				t.scanOperand = true;
				break;

			case jsdef.IN:
				// An in operator should not be parsed if we're parsing the head of
				// a for (...) loop, unless it is in the then part of a conditional
				// expression, or parenthesized somehow.
				if(x.inForLoopInit && !x.hookLevel && !x.bracketLevel && !x.curlyLevel && !x.parenLevel)
				{
					break loop;
				}
				// FALL THROUGH

			case jsdef.COMMA:
				// Treat comma as left-associative so reduce can fold left-heavy
				// jsdef.COMMA trees into a single array.
				// FALL THROUGH

			case jsdef.LT:

				if(tt==jsdef.LT && operators.top().type==jsdef.NEW && operands.top().value=="Array")
				{
					matchVartype(t, operators.top(), "subtype", true);
					operators.top().vartype = "Array<" + operators.top().subtype + ">";
					operands.top().subtype = operators.top().subtype;
					operands.top().vartype = operators.top().vartype;
					//operands.top().value = operands.top().vartype;
					t.mustMatch(jsdef.GT);
					break;
				}

			case jsdef.OR:
			case jsdef.AND:
			case jsdef.BITWISE_OR:
			case jsdef.BITWISE_XOR:
			case jsdef.BITWISE_AND:
			case jsdef.EQ:
			case jsdef.NE:
			case jsdef.STRICT_EQ:
			case jsdef.STRICT_NE:
			case jsdef.LE:
			case jsdef.GE:
			case jsdef.GT:
			case jsdef.INSTANCEOF:
			case jsdef.IS:
			case jsdef.LSH:
			case jsdef.RSH:
			case jsdef.URSH:
			case jsdef.PLUS:
			case jsdef.MINUS:
			case jsdef.MUL:
			case jsdef.DIV:
			case jsdef.MOD:
			case jsdef.EXPONENT:
			case jsdef.DOT:
			case jsdef.RANGE:
			case jsdef.AS:
				if(t.scanOperand)
					break loop;
				while(opPrecedence[operators.top().type] >= opPrecedence[tt])
					reduce();
				if(tt == jsdef.RANGE && !x.inArrayInit)
				{
					throw t.newSyntaxError("Invalid ... operator");
				}
				if(tt == jsdef.DOT)
				{
					t.mustMatch(jsdef.IDENTIFIER);
					operands.push(new Node(t, jsdef.DOT, operands.pop(), new Node(t)));
				}
				else if(tt == jsdef.AS)
				{
					var n = new Node(t);
					matchVartype(t, n, "vartype");
				}
				else
				{
					operators.push(new Node(t));
					t.scanOperand = true;
				}
				break;

			case jsdef.NEW:
				if(!t.scanOperand)
					break loop;
				var n = new Node(t);
				operators.push(n);
				break;

			case jsdef.DELETE:
			case jsdef.VOID:
			case jsdef.TYPEOF:
			case jsdef.NOT:
			case jsdef.BITWISE_NOT:
			case jsdef.UNARY_PLUS:
			case jsdef.UNARY_MINUS:
			case jsdef.REGEXP_MATCH:
			case jsdef.UNARY_EXISTS:
				if(!t.scanOperand)
					break loop;
				operators.push(new Node(t));
				break;

			case jsdef.INCREMENT:
			case jsdef.DECREMENT:
				if(t.scanOperand)
				{
					operators.push(new Node(t)); // prefix increment or decrement
				}
				else
				{
					// Don't cross a line boundary for postfix {in,de}crement.
					if(t.tokens[(t.tokenIndex + t.lookahead - 1) & 3].line_start !=t.line_start)
					{
						break loop;
					}
					// Use >, not >=, so postfix has higher precedence than prefix.
					while(opPrecedence[operators.top().type] > opPrecedence[tt])
						reduce();
					n = new Node(t, tt, operands.pop());
					n.postfix = true;
					operands.push(n);
				}
				break;

			case jsdef.PROPERTY:
				break;

			case jsdef.FUNCTION:
				if(!t.scanOperand)
					break loop;
				operands.push(FunctionDefinition(t, x, false, EXPRESSED_FORM));
				t.scanOperand = false;
				break;

			case jsdef.CLASS:
				if(!t.scanOperand)
					break loop;
				operands.push(ClassDefinition(t, x, false, EXPRESSED_FORM));
				t.scanOperand = false;
				break;

			case jsdef.NULL:
			case jsdef.THIS:
			case jsdef.TRUE:
			case jsdef.FALSE:
			case jsdef.IDENTIFIER:
			case jsdef.NUMBER:
			case jsdef.STRING:
			case jsdef.REGEXP:
			case jsdef.SUPER:  //TODO: much change super to support super.super.super...
				if(!t.scanOperand)
					break loop;
				operands.push(new Node(t));
				t.scanOperand = false;
				break;

			//"return" as an expression for expression closures
			//e.g. [1,2,3].map(function() return 1 + 1)
			case jsdef.RETURN:
				if(!x.inFunction || !t.expClosure)
					throw t.newSyntaxError("Invalid return");
				n = new Node(t);
				tt = t.peekOnSameLine();
				if(tt != jsdef.END && tt != jsdef.NEWLINE && tt != jsdef.SEMICOLON && tt != jsdef.RIGHT_CURLY)
					n.value = Expression(t, x);
				operands.push(n);
				t.scanOperand = false;
				break;

			case jsdef.LEFT_BRACKET:
				if(t.scanOperand)
				{
					// Array initialiser.  Parse using recursive descent, as the
					// sub-grammar here is not an operator grammar.
					n = new Node(t, jsdef.ARRAY_INIT);
					x.inArrayInit = true;
					var counter = 0,
						n2, emptyEl;
					while((tt = t.peek()) != jsdef.RIGHT_BRACKET)
					{
						counter++;
						if(tt == jsdef.COMMA)
						{
							t.get();
							//n.push(null); //Removed from Narcissus as it won't parse [a,,b]
							//Parse empty elements [,,,] as void 0
							emptyEl = new Node(t, jsdef.VOID);
							emptyEl[0] = new Node(t, jsdef.NUMBER);
							emptyEl[0].value = 0;
							n.push(emptyEl);
							continue;
						}
						n.push(Expression(t, x, jsdef.COMMA));
						//Array comprehensions
						if(counter == 1 && t.peek() == jsdef.FOR)
						{
							n.type = jsdef.ARRAY_COMP;
							n2 = new Node(t);
							t.mustMatch(jsdef.FOR);
							t.mustMatch(jsdef.LEFT_PAREN);
							if(t.match(jsdef.VAR) || t.match(jsdef.LET))
							{
								x.inForLoopInit = true;
								n2.iterator = VariablesDefinition(t, x);
								x.inForLoopInit = false;
							}
							else if(t.match(jsdef.IDENTIFIER))
							{
								x.inForLoopInit = true;
								t.unget();
								n2.iterator = Expression(t, x);
								x.inForLoopInit = false;
							}
							else
							{
								throw t.newSyntaxError("Missing ] after element list");
							}
							if(t.match(jsdef.IN))
							{
								n2.type = jsdef.FOR_IN;
								n2.object = Expression(t, x);
							}
							else
							{
								throw t.newSyntaxError("Missing ] after element list");
							}
							t.mustMatch(jsdef.RIGHT_PAREN);
							n.push(n2);
							while(t.peek() != jsdef.RIGHT_BRACKET)
							{
								n2 = new Node(t);
								if(t.match(jsdef.IF))
								{
									n2.type = jsdef.IF;
									t.mustMatch(jsdef.LEFT_PAREN);
									n2.condition = Expression(t, x);
									t.mustMatch(jsdef.RIGHT_PAREN);
								}
								else if(t.match(jsdef.FOR))
								{
									t.mustMatch(jsdef.LEFT_PAREN);
									if(t.match(jsdef.VAR) || t.match(jsdef.LET))
									{
										x.inForLoopInit = true;
										n2.iterator = VariablesDefinition(t, x);
										x.inForLoopInit = false;
									}
									else if(t.match(jsdef.IDENTIFIER))
									{
										x.inForLoopInit = true;
										t.unget();
										n2.iterator = Expression(t, x);
										x.inForLoopInit = false;
									}
									else
									{
										throw t.newSyntaxError("Missing ] after element list");
									}
									if(t.match(jsdef.IN))
									{
										n2.type = jsdef.FOR_IN;
										n2.object = Expression(t, x);
									}
									else
									{
										throw t.newSyntaxError("Missing ] after element list");
									}
									t.mustMatch(jsdef.RIGHT_PAREN);
								}
								else
								{
									throw t.newSyntaxError("Missing ] after element list");
								}
								n.push(n2);
							}
							break;
						}
						if(!t.match(jsdef.COMMA))
							break;
					}
					t.mustMatch(jsdef.RIGHT_BRACKET);
					operands.push(n);
					x.inArrayInit = false;
					t.scanOperand = false;
				}
				else
				{
					// Property indexing operator.
					operators.push(new Node(t, jsdef.INDEX));
					t.scanOperand = true;
					++x.bracketLevel;
				}
				break;

			case jsdef.RIGHT_BRACKET:
				if(t.scanOperand || x.bracketLevel == bl)
					break loop;
				while(reduce().type != jsdef.INDEX)
					continue;
				--x.bracketLevel;
				break;

			case jsdef.LEFT_CURLY:
				if(!t.scanOperand)
					break loop;
				// Object initialiser.  As for array initialisers (see above),
				// parse using recursive descent.
				++x.curlyLevel;
				n = new Node(t, jsdef.OBJECT_INIT);
				object_init: if(!t.match(jsdef.RIGHT_CURLY))
				{
					do
					{
						tt = t.get();
						if((t.token().value == "get" || t.token().value == "set") &&
							t.peek() == jsdef.IDENTIFIER)
						{
							if(x.ecmaStrictMode)
								throw t.newSyntaxError("Illegal property accessor");
							n.push(FunctionDefinition(t, x, true, EXPRESSED_FORM));
						}
						else
						{
							switch(tt)
							{
							case jsdef.IDENTIFIER:
							case jsdef.NUMBER:
							case jsdef.STRING:
								id = new Node(t);
								break;
							case jsdef.RIGHT_CURLY:
								if(x.ecmaStrictMode)
									throw t.newSyntaxError("Illegal trailing ,");
								break object_init;
							default:
								throw t.newSyntaxError("Invalid property name");
							}
							t.mustMatch(jsdef.COLON);
							n.push(new Node(t, jsdef.PROPERTY_INIT, id,
								Expression(t, x, jsdef.COMMA)));
						}
					} while (t.match(jsdef.COMMA));
					t.mustMatch(jsdef.RIGHT_CURLY);
				}
				operands.push(n);
				t.scanOperand = false;
				--x.curlyLevel;
				break;

			case jsdef.RIGHT_CURLY:
				if(!t.scanOperand && x.curlyLevel != cl)
					throw "PANIC: right curly botch";
				break loop;

			case jsdef.LEFT_PAREN:
				if(t.scanOperand)
				{
					operators.push(new Node(t, jsdef.GROUP));
				}
				else
				{
					while(opPrecedence[operators.top().type] > opPrecedence[jsdef.NEW])
						reduce();
					// Handle () now, to regularize the n-ary case for n > 0.
					// We must set scanOperand in case there are arguments and
					// the first one is a regexp or unary+/-.
					n = operators.top();
					t.scanOperand = true;
					if(t.match(jsdef.RIGHT_PAREN))
					{
						if(n.type == jsdef.NEW)
						{
							--operators.length;
							n.push(operands.pop());
						}
						else if(n.type == jsdef.IDENTIFIER)
						{
							--operators.length;
						}
						else
						{
							n = new Node(t, jsdef.CALL, operands.pop(),
								new Node(t, jsdef.LIST));
						}
						operands.push(n);
						t.scanOperand = false;
						break;
					}
					if(n.type == jsdef.NEW)
						n.type = jsdef.NEW_WITH_ARGS;
					else
						operators.push(new Node(t, jsdef.CALL));
				}
				++x.parenLevel;
				break;

			case jsdef.RIGHT_PAREN:
				if(t.scanOperand || x.parenLevel == pl)
					break loop;
				while((tt = reduce().type) != jsdef.GROUP && tt != jsdef.CALL &&
					tt != jsdef.NEW_WITH_ARGS)
				{
					continue;
				}
				if(tt != jsdef.GROUP)
				{
					n = operands.top();
					if(n[1].type != jsdef.COMMA)
						n[1] = new Node(t, jsdef.LIST, n[1]);
					else
						n[1].type = jsdef.LIST;
				}
				--x.parenLevel;
            	break;

			// Automatic semicolon insertion means we may scan across a newline
			// and into the beginning of another statement.  If so, break out of
			// the while loop and let the t.scanOperand logic handle errors.
			default:
				break loop;
			}
		}

		if(x.hookLevel != hl) throw t.newSyntaxError("Missing : after ?");
		if(x.parenLevel != pl) throw t.newSyntaxError("Missing ) in parenthetical");
		if(x.bracketLevel != bl) throw t.newSyntaxError("Missing ] in index expression");
		if(t.scanOperand) throw t.newSyntaxError("Missing operand");

		// Resume default mode, scanning for operands, not operators.
		t.scanOperand = true;
		t.unget();
		while(operators.length)
			reduce();

		return operands.pop();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	function jsparse(code, as3)
	{
        if(as3)
        {
		    code = RxReplace(code, "\\bVector\\.\\<", "mg", "Array<");
			code = RxReplace(code, "\\:\\s*void", "mg", "");
			//code = RxReplace(code, "\\:\\s*\\*", "mg", ":Object");
			code = RxReplace(code, "(\\w+)\\s*\\:\\s*\\*", "mg", "$1:b2C$1");
			code = RxReplace(code, "for\\s*each\\(", "mg", "for(");
			code = RxReplace(code, "\\bextends\\b", "mg", ":");
			code = RxReplace(code, "\\bimplements\\b", "mg", ":");
			code = RxReplace(code, "\\bb2internal\\b", "mg", "public");
			code = RxReplace(code, "\\binternal\\b", "mg", "private");
			code = RxReplace(code, "\\boverride\\s+\\b", "mg", "");
			code = RxReplace(code, "(?:public|private|protected)?\\s*interface\\s+(\\w+)", "mg", "class $1");
			code = RxReplace(code, "(?:public|private|protected)?\\s*class\\s+(\\w+)", "mg", "class $1");
			code = RxReplace(code, "\\bpublic\\s+namespace[\\W\\w]*?;", "mg", "");
			code = RxReplace(code, "\\b(virtual|static)\\s+(public|private|protected)\\s+", "mg", "$2 $1 ");
			code = RxReplace(code, "\\b(uint|int)\\b", "mg", "Integer");
			code = RxReplace(code, "\\.length\\b", "mg", ".size()"); // TOCHECK
			code = RxReplace(code, "(public|private|protected)?\\s*(function\\s+\\w+\\([\\s\\:\\,\\w]*?\\)\\s*(?:\\:\\s*\\w+)?)\\s*\\;", "mg", "public virtual $2 {}");
			write("C:/Users/admin/Desktop/code.as3", code);
        }

		var t = new Tokenizer(code);
		var x = new CompilerContext(false);
		var n = Script(t, x);
		if(!t.done()) throw t.newSyntaxError("Syntax error");
		return n;
	}

	GLOBAL.narcissus.jsparse = jsparse;

}
__init_narcissus(this);
