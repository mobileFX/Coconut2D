
function __init_moz_narcissus(GLOBAL)
{
	GLOBAL.moz_narcissus = {};
	GLOBAL.moz_narcissus.jsdefNames = {};
	GLOBAL.mos_jsdef = {};

	var options = {};

	// Global variables to hide from the interpreter
	options.hiddenHostGlobals = { Narcissus: true };

	// Desugar SpiderMonkey language extensions?
	options.desugarExtensions = false;

	// Allow HTML comments?
	options.allowHTMLComments = false;

	// Allow non-standard Mozilla extensions?
	options.mozillaMode = false;

	// Allow experimental paren-free mode?
	options.parenFreeMode = false;

	var tokens = [
	    // End of source.
	    "END",

	    // Operators and punctuators.  Some pair-wise order matters, e.g. (+, -)
	    // and (UNARY_PLUS, UNARY_MINUS).
	    "\n", ";",
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
	    "!", "~", "UNARY_PLUS", "UNARY_MINUS",
	    "++", "--",
	    ".",
	    "[", "]",
	    "{", "}",
	    "(", ")",

	    // Nonterminal tree node type codes.
	    "SCRIPT", "BLOCK", "LABEL", "FOR_IN", "CALL", "NEW_WITH_ARGS", "INDEX",
	    "ARRAY_INIT", "OBJECT_INIT", "PROPERTY_INIT", "GETTER", "SETTER",
	    "GROUP", "LIST", "LET_BLOCK", "ARRAY_COMP", "GENERATOR", "COMP_TAIL",

	    // Contextual keywords.
	    "IMPLEMENTS", "INTERFACE", "LET", "MODULE", "PACKAGE", "PRIVATE",
	    "PROTECTED", "PUBLIC", "STATIC", "USE", "YIELD",

	    // Terminals.
	    "IDENTIFIER", "NUMBER", "STRING", "REGEXP",

	    // Keywords.
	    "break",
	    "case", "catch", "const", "continue",
	    "debugger", "default", "delete", "do",
	    "else", "export",
	    "false", "finally", "for", "function",
	    "if", "import", "in", "instanceof",
	    "new", "null",
	    "return",
	    "switch",
	    "this", "throw", "true", "try", "typeof",
	    "var", "void",
	    "while", "with",
	];

	var strictKeywords = {
	    __proto__: null,
	    "implements": true,
	    "interface": true,
	    "let": true,
	    "module": true,
	    "package": true,
	    "private": true,
	    "protected": true,
	    "public": true,
	    "static": true,
	    "use": true,
	    "yield": true
	};

	var statementStartTokens = [
	    "break",
	    "const", "continue",
	    "debugger", "do",
	    "for",
	    "if",
	    "let",
	    "return",
	    "switch",
	    "throw", "try",
	    "var",
	    "yield",
	    "while", "with",
	];

	// Whitespace characters (see ECMA-262 7.2)
	var whitespaceChars = [
	    // normal whitespace:
	    "\u0009", "\u000B", "\u000C", "\u0020", "\u00A0", "\uFEFF",

	    // high-Unicode whitespace:
	    "\u1680", "\u180E",
	    "\u2000", "\u2001", "\u2002", "\u2003", "\u2004", "\u2005", "\u2006",
	    "\u2007", "\u2008", "\u2009", "\u200A",
	    "\u202F", "\u205F", "\u3000"
	];

	var whitespace = {};
	for (var i = 0; i < whitespaceChars.length; i++) {
	    whitespace[whitespaceChars[i]] = true;
	}

	// Operator and punctuator mapping from token to tree node type name.
	// NB: because the lexer doesn't backtrack, all token prefixes must themselves
	// be valid tokens (e.g. !== is acceptable because its prefixes are the valid
	// tokens != and !).
	var opTypeNames = {
	    '\n':   "NEWLINE",
	    ';':    "SEMICOLON",
	    ',':    "COMMA",
	    '?':    "HOOK",
	    ':':    "COLON",
	    '||':   "OR",
	    '&&':   "AND",
	    '|':    "BITWISE_OR",
	    '^':    "BITWISE_XOR",
	    '&':    "BITWISE_AND",
	    '===':  "STRICT_EQ",
	    '==':   "EQ",
	    '=':    "ASSIGN",
	    '!==':  "STRICT_NE",
	    '!=':   "NE",
	    '<<':   "LSH",
	    '<=':   "LE",
	    '<':    "LT",
	    '>>>':  "URSH",
	    '>>':   "RSH",
	    '>=':   "GE",
	    '>':    "GT",
	    '++':   "INCREMENT",
	    '--':   "DECREMENT",
	    '+':    "PLUS",
	    '-':    "MINUS",
	    '*':    "MUL",
	    '/':    "DIV",
	    '%':    "MOD",
	    '!':    "NOT",
	    '~':    "BITWISE_NOT",
	    '.':    "DOT",
	    '[':    "LEFT_BRACKET",
	    ']':    "RIGHT_BRACKET",
	    '{':    "LEFT_CURLY",
	    '}':    "RIGHT_CURLY",
	    '(':    "LEFT_PAREN",
	    ')':    "RIGHT_PAREN"
	};

	// Hash of keyword identifier to tokens index.  NB: we must null __proto__ to
	// avoid toString, etc. namespace pollution.
	var keywords = {__proto__: null};
	var mozillaKeywords = {__proto__: null};

	// Define const END, etc., based on the token names.  Also map name to index.
	var tokenIds = {};

	var hostSupportsEvalConst = (function() {
	    try {
	        return eval("(function(s) { eval(s); return x })('const x = true;')");
	    } catch (e) {
	        return false;
	    }
	})();

	// Building up a string to be eval'd in different contexts.
	var consts = hostSupportsEvalConst ? "const " : "var ";
	for (var i = 0, j = tokens.length; i < j; i++) {
	    if (i > 0)
	        consts += ", ";
	    var t = tokens[i];
	    var name;
	    if (/^[a-z]/.test(t)) {
	        name = t.toUpperCase();
	        if (name === "LET" || name === "YIELD")
	            mozillaKeywords[name] = i;
	        if (strictKeywords[name])
	            strictKeywords[name] = i;
	        keywords[t] = i;
	    } else {
	        name = (/^\W/.test(t) ? opTypeNames[t] : t);
	    }
	    consts += name + " = " + i;
	    tokenIds[name] = i;
	    tokens[t] = i;
	    GLOBAL.mos_jsdef[name] = i;
	    GLOBAL.moz_narcissus.jsdefNames[i] = name;
	}
	consts += ";";

	var isStatementStartCode = {__proto__: null};
	for (i = 0, j = statementStartTokens.length; i < j; i++)
	    isStatementStartCode[keywords[statementStartTokens[i]]] = true;

	// Map assignment operators to their indexes in the tokens array.
	var assignOps = ['|', '^', '&', '<<', '>>', '>>>', '+', '-', '*', '/', '%'];

	for (i = 0, j = assignOps.length; i < j; i++) {
	    t = assignOps[i];
	    assignOps[t] = tokens[t];
	}

	function defineGetter(obj, prop, fn, dontDelete, dontEnum) {
	    Object.defineProperty(obj, prop,
	                          { get: fn, configurable: !dontDelete, enumerable: !dontEnum });
	}

	function defineGetterSetter(obj, prop, getter, setter, dontDelete, dontEnum) {
	    Object.defineProperty(obj, prop, {
	        get: getter,
	        set: setter,
	        configurable: !dontDelete,
	        enumerable: !dontEnum
	    });
	}

	function defineMemoGetter(obj, prop, fn, dontDelete, dontEnum) {
	    Object.defineProperty(obj, prop, {
	        get: function() {
	            var val = fn();
	            defineProperty(obj, prop, val, dontDelete, true, dontEnum);
	            return val;
	        },
	        configurable: true,
	        enumerable: !dontEnum
	    });
	}

	function defineProperty(obj, prop, val, dontDelete, readOnly, dontEnum) {
	    Object.defineProperty(obj, prop,
	                          { value: val, writable: !readOnly, configurable: !dontDelete,
	                            enumerable: !dontEnum });
	}

	// Returns true if fn is a native function.  (Note: SpiderMonkey specific.)
	function isNativeCode(fn) {
	    // Relies on the toString method to identify native code.
	    return ((typeof fn) === "function") && fn.toString().match(/\[native code\]/);
	}

	var Fpapply = Function.prototype.apply;

	function apply(f, o, a) {
	    return Fpapply.call(f, [o].concat(a));
	}

	var applyNew;

	// ES5's bind is a simpler way to implement applyNew
	if (Function.prototype.bind) {
	    applyNew = function applyNew(f, a) {
	        return new (f.bind.apply(f, [,].concat(Array.prototype.slice.call(a))))();
	    };
	} else {
	    applyNew = function applyNew(f, a) {
	        switch (a.length) {
	          case 0:
	            return new f();
	          case 1:
	            return new f(a[0]);
	          case 2:
	            return new f(a[0], a[1]);
	          case 3:
	            return new f(a[0], a[1], a[2]);
	          default:
	            var argStr = "a[0]";
	            for (var i = 1, n = a.length; i < n; i++)
	                argStr += ",a[" + i + "]";
	            return eval("new f(" + argStr + ")");
	        }
	    };
	}

	function getPropertyDescriptor(obj, name) {
	    while (obj) {
	        if (({}).hasOwnProperty.call(obj, name))
	            return Object.getOwnPropertyDescriptor(obj, name);
	        obj = Object.getPrototypeOf(obj);
	    }
	}

	function getPropertyNames(obj) {
	    var table = Object.create(null, {});
	    while (obj) {
	        var names = Object.getOwnPropertyNames(obj);
	        for (var i = 0, n = names.length; i < n; i++)
	            table[names[i]] = true;
	        obj = Object.getPrototypeOf(obj);
	    }
	    return Object.keys(table);
	}

	function getOwnProperties(obj) {
	    var map = {};
	    for (var name in Object.getOwnPropertyNames(obj))
	        map[name] = Object.getOwnPropertyDescriptor(obj, name);
	    return map;
	}

	function blacklistHandler(target, blacklist) {
	    var mask = Object.create(null, {});
	    var redirect = Dict.create(blacklist).mapObject(function(name) { return mask; });
	    return mixinHandler(redirect, target);
	}

	function whitelistHandler(target, whitelist) {
	    var catchall = Object.create(null, {});
	    var redirect = Dict.create(whitelist).mapObject(function(name) { return target; });
	    return mixinHandler(redirect, catchall);
	}

	/*
	 * Mixin proxies break the single-inheritance model of prototypes, so
	 * the handler treats all properties as own-properties:
	 *
	 *                  X
	 *                  |
	 *     +------------+------------+
	 *     |                 O       |
	 *     |                 |       |
	 *     |  O         O    O       |
	 *     |  |         |    |       |
	 *     |  O    O    O    O       |
	 *     |  |    |    |    |       |
	 *     |  O    O    O    O    O  |
	 *     |  |    |    |    |    |  |
	 *     +-(*)--(w)--(x)--(y)--(z)-+
	 */

	function mixinHandler(redirect, catchall) {
	    function targetFor(name) {
	        return hasOwn(redirect, name) ? redirect[name] : catchall;
	    }

	    function getMuxPropertyDescriptor(name) {
	        var desc = getPropertyDescriptor(targetFor(name), name);
	        if (desc)
	            desc.configurable = true;
	        return desc;
	    }

	    function getMuxPropertyNames() {
	        var names1 = Object.getOwnPropertyNames(redirect).filter(function(name) {
	            return name in redirect[name];
	        });
	        var names2 = getPropertyNames(catchall).filter(function(name) {
	            return !hasOwn(redirect, name);
	        });
	        return names1.concat(names2);
	    }

	    function enumerateMux() {
	        var result = Object.getOwnPropertyNames(redirect).filter(function(name) {
	            return name in redirect[name];
	        });
	        for (name in catchall) {
	            if (!hasOwn(redirect, name))
	                result.push(name);
	        };
	        return result;
	    }

	    function hasMux(name) {
	        return name in targetFor(name);
	    }

	    return {
	        getOwnPropertyDescriptor: getMuxPropertyDescriptor,
	        getPropertyDescriptor: getMuxPropertyDescriptor,
	        getOwnPropertyNames: getMuxPropertyNames,
	        defineProperty: function(name, desc) {
	            Object.defineProperty(targetFor(name), name, desc);
	        },
	        "delete": function(name) {
	            var target = targetFor(name);
	            return delete target[name];
	        },
	        // FIXME: ha ha ha
	        fix: function() { },
	        has: hasMux,
	        hasOwn: hasMux,
	        get: function(receiver, name) {
	            var target = targetFor(name);
	            return target[name];
	        },
	        set: function(receiver, name, val) {
	            var target = targetFor(name);
	            target[name] = val;
	            return true;
	        },
	        enumerate: enumerateMux,
	        keys: enumerateMux
	    };
	}

	function makePassthruHandler(obj) {
	    // Handler copied from
	    // http://wiki.ecmascript.org/doku.php?id=harmony:proxies&s=proxy%20object#examplea_no-op_forwarding_proxy
	    return {
	        getOwnPropertyDescriptor: function(name) {
	            var desc = Object.getOwnPropertyDescriptor(obj, name);

	            // a trapping proxy's properties must always be configurable
	            desc.configurable = true;
	            return desc;
	        },
	        getPropertyDescriptor: function(name) {
	            var desc = getPropertyDescriptor(obj, name);

	            // a trapping proxy's properties must always be configurable
	            desc.configurable = true;
	            return desc;
	        },
	        getOwnPropertyNames: function() {
	            return Object.getOwnPropertyNames(obj);
	        },
	        defineProperty: function(name, desc) {
	            Object.defineProperty(obj, name, desc);
	        },
	        "delete": function(name) { return delete obj[name]; },
	        fix: function() {
	            if (Object.isFrozen(obj)) {
	                return getOwnProperties(obj);
	            }

	            // As long as obj is not frozen, the proxy won't allow itself to be fixed.
	            return undefined; // will cause a TypeError to be thrown
	        },

	        has: function(name) { return name in obj; },
	        hasOwn: function(name) { return ({}).hasOwnProperty.call(obj, name); },
	        get: function(receiver, name) { return obj[name]; },

	        // bad behavior when set fails in non-strict mode
	        set: function(receiver, name, val) { obj[name] = val; return true; },
	        enumerate: function() {
	            var result = [];
	            for (name in obj) { result.push(name); };
	            return result;
	        },
	        keys: function() { return Object.keys(obj); }
	    };
	}

	var hasOwnProperty = ({}).hasOwnProperty;

	function hasOwn(obj, name) {
	    return hasOwnProperty.call(obj, name);
	}

	function Dict(table, size) {
	    this.table = table || Object.create(null, {});
	    this.size = size || 0;
	}

	Dict.create = function(table) {
	    var init = Object.create(null, {});
	    var size = 0;
	    var names = Object.getOwnPropertyNames(table);
	    for (var i = 0, n = names.length; i < n; i++) {
	        var name = names[i];
	        init[name] = table[name];
	        size++;
	    }
	    return new Dict(init, size);
	};

	Dict.prototype = {
	    has: function(x) { return hasOwnProperty.call(this.table, x); },
	    set: function(x, v) {
	        if (!hasOwnProperty.call(this.table, x))
	            this.size++;
	        this.table[x] = v;
	    },
	    get: function(x) { return this.table[x]; },
	    getDef: function(x, thunk) {
	        if (!hasOwnProperty.call(this.table, x)) {
	            this.size++;
	            this.table[x] = thunk();
	        }
	        return this.table[x];
	    },
	    forEach: function(f) {
	        var table = this.table;
	        for (var key in table)
	            f.call(this, key, table[key]);
	    },
	    map: function(f) {
	        var table1 = this.table;
	        var table2 = Object.create(null, {});
	        this.forEach(function(key, val) {
	            table2[key] = f.call(this, val, key);
	        });
	        return new Dict(table2, this.size);
	    },
	    mapObject: function(f) {
	        var table1 = this.table;
	        var table2 = Object.create(null, {});
	        this.forEach(function(key, val) {
	            table2[key] = f.call(this, val, key);
	        });
	        return table2;
	    },
	    toObject: function() {
	        return this.mapObject(function(val) { return val; });
	    },
	    choose: function() {
	        return Object.getOwnPropertyNames(this.table)[0];
	    },
	    remove: function(x) {
	        if (hasOwnProperty.call(this.table, x)) {
	            this.size--;
	            delete this.table[x];
	        }
	    },
	    copy: function() {
	        var table = Object.create(null, {});
	        for (var key in this.table)
	            table[key] = this.table[key];
	        return new Dict(table, this.size);
	    },
	    keys: function() {
	        return Object.keys(this.table);
	    },
	    toString: function() { return "[object Dict]" }
	};

	var _WeakMap = typeof WeakMap === "function" ? WeakMap : (function() {
	    // shim for ES6 WeakMap with poor asymptotics
	    function WeakMap(array) {
	        this.array = array || [];
	    }

	    function searchMap(map, key, found, notFound) {
	        var a = map.array;
	        for (var i = 0, n = a.length; i < n; i++) {
	            var pair = a[i];
	            if (pair.key === key)
	                return found(pair, i);
	        }
	        return notFound();
	    }

	    WeakMap.prototype = {
	        has: function(x) {
	            return searchMap(this, x, function() { return true }, function() { return false });
	        },
	        set: function(x, v) {
	            var a = this.array;
	            searchMap(this, x,
	                      function(pair) { pair.value = v },
	                      function() { a.push({ key: x, value: v }) });
	        },
	        get: function(x) {
	            return searchMap(this, x,
	                             function(pair) { return pair.value },
	                             function() { return null });
	        },
	        "delete": function(x) {
	            var a = this.array;
	            searchMap(this, x,
	                      function(pair, i) { a.splice(i, 1) },
	                      function() { });
	        },
	        toString: function() { return "[object WeakMap]" }
	    };

	    return WeakMap;
	})();

	// non-destructive stack
	function Stack(elts) {
	    this.elts = elts || null;
	}

	Stack.prototype = {
	    push: function(x) {
	        return new Stack({ top: x, rest: this.elts });
	    },
	    top: function() {
	        if (!this.elts)
	            throw new Error("empty stack");
	        return this.elts.top;
	    },
	    isEmpty: function() {
	        return this.top === null;
	    },
	    find: function(test) {
	        for (var elts = this.elts; elts; elts = elts.rest) {
	            if (test(elts.top))
	                return elts.top;
	        }
	        return null;
	    },
	    has: function(x) {
	        return Boolean(this.find(function(elt) { return elt === x }));
	    },
	    forEach: function(f) {
	        for (var elts = this.elts; elts; elts = elts.rest) {
	            f(elts.top);
	        }
	    }
	};

	if (!Array.prototype.copy) {
	    defineProperty(Array.prototype, "copy",
	                   function() {
	                       var result = [];
	                       for (var i = 0, n = this.length; i < n; i++)
	                           result[i] = this[i];
	                       return result;
	                   }, false, false, true);
	}

	if (!Array.prototype.top) {
	    defineProperty(Array.prototype, "top",
	                   function() {
	                       return this.length && this[this.length-1];
	                   }, false, false, true);
	}


	// Build up a trie of operator tokens.
	var opTokens = {};
	for (var op in opTypeNames) {
	    if (op === '\n' || op === '.')
	        continue;

	    var node = opTokens;
	    for (var i = 0; i < op.length; i++) {
	        var ch = op[i];
	        if (!(ch in node))
	            node[ch] = {};
	        node = node[ch];
	        node.op = op;
	    }
	}

	/*
	 * Since JavaScript provides no convenient way to determine if a
	 * character is in a particular Unicode category, we use
	 * metacircularity to accomplish this (oh yeaaaah!)
	 */
	function isValidIdentifierChar(ch, first) {
	    // check directly for ASCII
	    if (ch <= "\u007F") {
	        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch === '$' || ch === '_' ||
	            (!first && (ch >= '0' && ch <= '9'))) {
	            return true;
	        }
	        return false;
	    }

	    // create an object to test this in
	    var x = {};
	    x["x"+ch] = true;
	    x[ch] = true;

	    // then use eval to determine if it's a valid character
	    var valid = false;
	    try {
	        valid = (Function("x", "return (x." + (first?"":"x") + ch + ");")(x) === true);
	    } catch (ex) {}

	    return valid;
	}

	function isIdentifier(str) {
	    if (typeof str !== "string")
	        return false;

	    if (str.length === 0)
	        return false;

	    if (!isValidIdentifierChar(str[0], true))
	        return false;

	    for (var i = 1; i < str.length; i++) {
	        if (!isValidIdentifierChar(str[i], false))
	            return false;
	    }

	    return true;
	}

	/*
	 * Tokenizer :: (source, filename, line number, boolean) -> Tokenizer
	 */
	function Tokenizer(s, f, l, allowHTMLComments) {
	    this.cursor = 0;
	    this.source = String(s);
	    this.tokens = [];
	    this.tokenIndex = 0;
	    this.lookahead = 0;
	    this.scanNewlines = false;
	    this.filename = f || "";
	    this.lineno = l || 1;
	    this.allowHTMLComments = allowHTMLComments;
	    this.blockComments = null;
	}

	Tokenizer.prototype = {

	    //Object.defineProperty(this, "b", { get: function () { return this.a + 1; } });

	    get done() {
	        // We need to set scanOperand to true here because the first thing
	        // might be a regexp.
	        return this.peek(true) === END;
	    },

	    get token() {
	        return this.tokens[this.tokenIndex];
	    },

	    match: function (tt, scanOperand, keywordIsName) {
	        return this.get(scanOperand, keywordIsName) === tt || this.unget();
	    },

	    mustMatch: function (tt, keywordIsName) {
	        if (!this.match(tt, false, keywordIsName)) {
	            throw this.newSyntaxError("Missing " +
	                                      tokens[tt].toLowerCase());
	        }
	        return this.token;
	    },

	    peek: function (scanOperand) {
	        var tt, next;
	        if (this.lookahead) {
	            next = this.tokens[(this.tokenIndex + this.lookahead) & 3];
	            tt = (this.scanNewlines && next.lineno !== this.lineno)
	                ? NEWLINE
	                : next.type;
	        } else {
	            tt = this.get(scanOperand);
	            this.unget();
	        }
	        return tt;
	    },

	    peekOnSameLine: function (scanOperand) {
	        this.scanNewlines = true;
	        var tt = this.peek(scanOperand);
	        this.scanNewlines = false;
	        return tt;
	    },

	    lastBlockComment: function() {
	        var length = this.blockComments.length;
	        return length ? this.blockComments[length - 1] : null;
	    },

	    // Eat comments and whitespace.
	    skip: function () {
	        var input = this.source;
	        this.blockComments = [];
	        for (;;) {
	            var ch = input[this.cursor++];
	            var next = input[this.cursor];
	            // handle \r, \r\n and (always preferable) \n
	            if (ch === '\r') {
	                // if the next character is \n, we don't care about this at all
	                if (next === '\n') continue;

	                // otherwise, we want to consider this as a newline
	                ch = '\n';
	            }

	            if (ch === '\n' && !this.scanNewlines) {
	                this.lineno++;
	            } else if (ch === '/' && next === '*') {
	                var commentStart = ++this.cursor;
	                for (;;) {
	                    ch = input[this.cursor++];
	                    if (ch === undefined)
	                        throw this.newSyntaxError("Unterminated comment");

	                    if (ch === '*') {
	                        next = input[this.cursor];
	                        if (next === '/') {
	                            var commentEnd = this.cursor - 1;
	                            this.cursor++;
	                            break;
	                        }
	                    } else if (ch === '\n') {
	                        this.lineno++;
	                    }
	                }
	                this.blockComments.push(input.substring(commentStart, commentEnd));
	            } else if ((ch === '/' && next === '/') ||
	                       (this.allowHTMLComments && ch === '<' && next === '!' &&
	                        input[this.cursor + 1] === '-' && input[this.cursor + 2] === '-' &&
	                        (this.cursor += 2))) {
	                this.cursor++;
	                for (;;) {
	                    ch = input[this.cursor++];
	                    next = input[this.cursor];
	                    if (ch === undefined)
	                        return;

	                    if (ch === '\r') {
	                        // check for \r\n
	                        if (next !== '\n') ch = '\n';
	                    }

	                    if (ch === '\n') {
	                        if (this.scanNewlines) {
	                            this.cursor--;
	                        } else {
	                            this.lineno++;
	                        }
	                        break;
	                    }
	                }
	            } else if (!(ch in whitespace)) {
	                this.cursor--;
	                return;
	            }
	        }
	    },

	    // Lex the exponential part of a number, if present. Return true iff an
	    // exponential part was found.
	    lexExponent: function() {
	        var input = this.source;
	        var next = input[this.cursor];
	        if (next === 'e' || next === 'E') {
	            this.cursor++;
	            ch = input[this.cursor++];
	            if (ch === '+' || ch === '-')
	                ch = input[this.cursor++];

	            if (ch < '0' || ch > '9')
	                throw this.newSyntaxError("Missing exponent");

	            do {
	                ch = input[this.cursor++];
	            } while (ch >= '0' && ch <= '9');
	            this.cursor--;

	            return true;
	        }

	        return false;
	    },

	    lexZeroNumber: function (ch) {
	        var token = this.token, input = this.source;
	        token.type = NUMBER;

	        ch = input[this.cursor++];
	        if (ch === '.') {
	            do {
	                ch = input[this.cursor++];
	            } while (ch >= '0' && ch <= '9');
	            this.cursor--;

	            this.lexExponent();
	            token.value = parseFloat(
	                input.substring(token.start, this.cursor));
	        } else if (ch === 'x' || ch === 'X') {
	            do {
	                ch = input[this.cursor++];
	            } while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') ||
	                     (ch >= 'A' && ch <= 'F'));
	            this.cursor--;

	            token.value = parseInt(input.substring(token.start, this.cursor));
	        } else if (ch >= '0' && ch <= '7') {
	            do {
	                ch = input[this.cursor++];
	            } while (ch >= '0' && ch <= '7');
	            this.cursor--;

	            token.value = parseInt(input.substring(token.start, this.cursor));
	        } else {
	            this.cursor--;
	            this.lexExponent();     // 0E1, &c.
	            token.value = 0;
	        }
	    },

	    lexNumber: function (ch) {
	        var token = this.token, input = this.source;
	        token.type = NUMBER;

	        var floating = false;
	        do {
	            ch = input[this.cursor++];
	            if (ch === '.' && !floating) {
	                floating = true;
	                ch = input[this.cursor++];
	            }
	        } while (ch >= '0' && ch <= '9');

	        this.cursor--;

	        var exponent = this.lexExponent();
	        floating = floating || exponent;

	        var str = input.substring(token.start, this.cursor);
	        token.value = floating ? parseFloat(str) : parseInt(str);
	    },

	    lexDot: function (ch) {
	        var token = this.token, input = this.source;
	        var next = input[this.cursor];
	        if (next >= '0' && next <= '9') {
	            do {
	                ch = input[this.cursor++];
	            } while (ch >= '0' && ch <= '9');
	            this.cursor--;

	            this.lexExponent();

	            token.type = NUMBER;
	            token.value = parseFloat(
	                input.substring(token.start, this.cursor));
	        } else {
	            token.type = DOT;
	            token.assignOp = null;
	            token.value = '.';
	        }
	    },

	    lexString: function (ch) {
	        var token = this.token, input = this.source;
	        token.type = STRING;

	        var hasEscapes = false;
	        var delim = ch;
	        if (input.length <= this.cursor)
	            throw this.newSyntaxError("Unterminated string literal");
	        while ((ch = input[this.cursor++]) !== delim) {
	            if (this.cursor == input.length)
	                throw this.newSyntaxError("Unterminated string literal");
	            if (ch === '\\') {
	                hasEscapes = true;
	                if (++this.cursor == input.length)
	                    throw this.newSyntaxError("Unterminated string literal");
	            }
	        }

	        token.value = hasEscapes
	            ? eval(input.substring(token.start, this.cursor))
	            : input.substring(token.start + 1, this.cursor - 1);
	    },

	    lexRegExp: function (ch) {
	        var token = this.token, input = this.source;
	        token.type = REGEXP;

	        do {
	            ch = input[this.cursor++];
	            if (ch === '\\') {
	                this.cursor++;
	            } else if (ch === '[') {
	                do {
	                    if (ch === undefined)
	                        throw this.newSyntaxError("Unterminated character class");

	                    if (ch === '\\')
	                        this.cursor++;

	                    ch = input[this.cursor++];
	                } while (ch !== ']');
	            } else if (ch === undefined) {
	                throw this.newSyntaxError("Unterminated regex");
	            }
	        } while (ch !== '/');

	        do {
	            ch = input[this.cursor++];
	        } while (ch >= 'a' && ch <= 'z');

	        this.cursor--;

	        token.value = eval(input.substring(token.start, this.cursor));
	    },

	    lexOp: function (ch) {
	        var token = this.token, input = this.source;

	        // A bit ugly, but it seems wasteful to write a trie lookup routine
	        // for only 3 characters...
	        var node = opTokens[ch];
	        var next = input[this.cursor];
	        if (next in node) {
	            node = node[next];
	            this.cursor++;
	            next = input[this.cursor];
	            if (next in node) {
	                node = node[next];
	                this.cursor++;
	                next = input[this.cursor];
	            }
	        }

	        var op = node.op;
	        if (assignOps[op] && input[this.cursor] === '=') {
	            this.cursor++;
	            token.type = ASSIGN;
	            token.assignOp = tokenIds[opTypeNames[op]];
	            op += '=';
	        } else {
	            token.type = tokenIds[opTypeNames[op]];
	            token.assignOp = null;
	        }

	        token.value = op;
	    },

	    // FIXME: Unicode escape sequences
	    lexIdent: function (ch, keywordIsName) {
	        var token = this.token;
	        var id = ch;

	        while ((ch = this.getValidIdentifierChar(false)) !== null) {
	            id += ch;
	        }

	        token.type = IDENTIFIER;
	        token.value = id;

	        if (keywordIsName)
	            return;

	        var kw;

	        if (this.parser.mozillaMode) {
	            kw = mozillaKeywords[id];
	            if (kw) {
	                token.type = kw;
	                return;
	            }
	        }

	        if (this.parser.x.strictMode) {
	            kw = strictKeywords[id];
	            if (kw) {
	                token.type = kw;
	                return;
	            }
	        }

	        kw = keywords[id];
	        if (kw)
	            token.type = kw;
	    },

	    /*
	     * Tokenizer.get :: ([boolean[, boolean]]) -> token type
	     *
	     * Consume input *only* if there is no lookahead.
	     * Dispatch to the appropriate lexing function depending on the input.
	     */
	    get: function (scanOperand, keywordIsName) {
	        var token;
	        while (this.lookahead) {
	            --this.lookahead;
	            this.tokenIndex = (this.tokenIndex + 1) & 3;
	            token = this.tokens[this.tokenIndex];
	            if (token.type !== NEWLINE || this.scanNewlines)
	                return token.type;
	        }

	        this.skip();

	        this.tokenIndex = (this.tokenIndex + 1) & 3;
	        token = this.tokens[this.tokenIndex];
	        if (!token)
	            this.tokens[this.tokenIndex] = token = {};

	        var input = this.source;
	        if (this.cursor >= input.length)
	            return token.type = END;

	        token.start = this.cursor;
	        token.lineno = this.lineno;

	        var ich = this.getValidIdentifierChar(true);
	        var ch = (ich === null) ? input[this.cursor++] : null;
	        if (ich !== null) {
	            this.lexIdent(ich, keywordIsName);
	        } else if (scanOperand && ch === '/') {
	            this.lexRegExp(ch);
	        } else if (ch in opTokens) {
	            this.lexOp(ch);
	        } else if (ch === '.') {
	            this.lexDot(ch);
	        } else if (ch >= '1' && ch <= '9') {
	            this.lexNumber(ch);
	        } else if (ch === '0') {
	            this.lexZeroNumber(ch);
	        } else if (ch === '"' || ch === "'") {
	            this.lexString(ch);
	        } else if (this.scanNewlines && (ch === '\n' || ch === '\r')) {
	            // if this was a \r, look for \r\n
	            if (ch === '\r' && input[this.cursor] === '\n') this.cursor++;
	            token.type = NEWLINE;
	            token.value = '\n';
	            this.lineno++;
	        } else {
	            throw this.newSyntaxError("Illegal token");
	        }

	        token.end = this.cursor;
	        return token.type;
	    },

	    /*
	     * Tokenizer.unget :: void -> undefined
	     *
	     * Match depends on unget returning undefined.
	     */
	    unget: function () {
	        if (++this.lookahead === 4) throw "PANIC: too much lookahead!";
	        this.tokenIndex = (this.tokenIndex - 1) & 3;
	    },

	    newSyntaxError: function (m) {
	        m = (this.filename ? this.filename + ":" : "") + this.lineno + ": " + m;
	        var e = new SyntaxError(m, this.filename, this.lineno);
	        e.source = this.source;
	        e.cursor = this.lookahead
	            ? this.tokens[(this.tokenIndex + this.lookahead) & 3].start
	            : this.cursor;
	        return e;
	    },


	    /* Gets a single valid identifier char from the input stream, or null
	     * if there is none.
	     */
	    getValidIdentifierChar: function(first) {
	        var input = this.source;
	        if (this.cursor >= input.length) return null;
	        var ch = input[this.cursor];

	        // first check for \u escapes
	        if (ch === '\\' && input[this.cursor+1] === 'u') {
	            // get the character value
	            try {
	                ch = String.fromCharCode(parseInt(
	                    input.substring(this.cursor + 2, this.cursor + 6),
	                    16));
	            } catch (ex) {
	                return null;
	            }
	            this.cursor += 5;
	        }

	        var valid = isValidIdentifierChar(ch, first);
	        if (valid) this.cursor++;
	        return (valid ? ch : null);
	    }
	};

	// Set constants in the local scope.
	eval(consts);

	/*
	 * pushDestructuringVarDecls :: (node, hoisting node) -> void
	 *
	 * Recursively add all destructured declarations to varDecls.
	 */
	function pushDestructuringVarDecls(n, s) {
	    for (var i in n) {
	        var sub = n[i];
	        if (sub.type === IDENTIFIER) {
	            s.varDecls.push(sub);
	        } else {
	            pushDestructuringVarDecls(sub, s);
	        }
	    }
	}

	function Parser(tokenizer) {
	    tokenizer.parser = this;
	    this.t = tokenizer;
	    this.x = null;
	    this.unexpectedEOF = false;
	    options.mozillaMode && (this.mozillaMode = true);
	    options.parenFreeMode && (this.parenFreeMode = true);
	}

	function StaticContext(parentScript, parentBlock, inModule, inFunction, strictMode) {
	    this.parentScript = parentScript;
	    this.parentBlock = parentBlock || parentScript;
	    this.inModule = inModule || false;
	    this.inFunction = inFunction || false;
	    this.inForLoopInit = false;
	    this.topLevel = true;
	    this.allLabels = new Stack();
	    this.currentLabels = new Stack();
	    this.labeledTargets = new Stack();
	    this.defaultLoopTarget = null;
	    this.defaultTarget = null;
	    this.strictMode = strictMode;
	}

	StaticContext.prototype = {
	    // non-destructive update via prototype extension
	    update: function(ext) {
	        var desc = {};
	        for (var key in ext) {
	            desc[key] = {
	                value: ext[key],
	                writable: true,
	                enumerable: true,
	                configurable: true
	            }
	        }
	        return Object.create(this, desc);
	    },
	    pushLabel: function(label) {
	        return this.update({ currentLabels: this.currentLabels.push(label),
	                             allLabels: this.allLabels.push(label) });
	    },
	    pushTarget: function(target) {
	        var isDefaultLoopTarget = target.isLoop;
	        var isDefaultTarget = isDefaultLoopTarget || target.type === SWITCH;

	        if (this.currentLabels.isEmpty()) {
	            if (isDefaultLoopTarget) this.update({ defaultLoopTarget: target });
	            if (isDefaultTarget) this.update({ defaultTarget: target });
	            return this;
	        }

	        target.labels = new Dict();
	        this.currentLabels.forEach(function(label) {
	            target.labels.set(label, true);
	        });
	        return this.update({ currentLabels: new Stack(),
	                             labeledTargets: this.labeledTargets.push(target),
	                             defaultLoopTarget: isDefaultLoopTarget
	                             ? target
	                             : this.defaultLoopTarget,
	                             defaultTarget: isDefaultTarget
	                             ? target
	                             : this.defaultTarget });
	    },
	    nest: function() {
	        return this.topLevel ? this.update({ topLevel: false }) : this;
	    },
	    canImport: function() {
	        return this.topLevel && !this.inFunction;
	    },
	    canExport: function() {
	        return this.inModule && this.topLevel && !this.inFunction;
	    },
	    banWith: function() {
	        return this.strictMode || this.inModule;
	    },
	    modulesAllowed: function() {
	        return this.topLevel && !this.inFunction;
	    }
	};

	var Pp = Parser.prototype;

	Pp.mozillaMode = false;

	Pp.parenFreeMode = false;

	Pp.withContext = function(x, f) {
	    var x0 = this.x;
	    this.x = x;
	    var result = f.call(this);
	    // NB: we don't bother with finally, since exceptions trash the parser
	    this.x = x0;
	    return result;
	};

	Pp.newNode = function newNode(opts) {
	    return new Node(this.t, opts);
	};

	Pp.fail = function fail(msg) {
	    throw this.t.newSyntaxError(msg);
	};

	Pp.match = function match(tt, scanOperand, keywordIsName) {
	    return this.t.match(tt, scanOperand, keywordIsName);
	};

	Pp.mustMatch = function mustMatch(tt, keywordIsName) {
	    return this.t.mustMatch(tt, keywordIsName);
	};

	Pp.peek = function peek(scanOperand) {
	    return this.t.peek(scanOperand);
	};

	Pp.peekOnSameLine = function peekOnSameLine(scanOperand) {
	    return this.t.peekOnSameLine(scanOperand);
	};

	Pp.done = function done() {
	    return this.t.done;
	};

	/*
	 * Script :: (boolean, boolean, boolean) -> node
	 *
	 * Parses the toplevel and module/function bodies.
	 */
	Pp.Script = function Script(inModule, inFunction, expectEnd) {
	    var node = this.newNode(scriptInit());
	    var x2 = new StaticContext(node, node, inModule, inFunction);
	    this.withContext(x2, function() {
	        this.Statements(node, true);
	    });
	    if (expectEnd && !this.done())
	        this.fail("expected end of input");
	    return node;
	};

	/*
	 * Pragma :: (expression statement node) -> boolean
	 *
	 * Checks whether a node is a pragma and annotates it.
	 */
	function Pragma(n) {
	    if (n.type === SEMICOLON) {
	        var e = n.expression;
	        if (e.type === STRING && e.value === "use strict") {
	            n.pragma = "strict";
	            return true;
	        }
	    }
	    return false;
	}

	/*
	 * Node :: (tokenizer, optional init object) -> node
	 */
	function Node(t, init) {
	    var token = t.token;
	    if (token) {
	        // If init.type exists it will override token.type.
	        this.type = token.type;
	        this.value = token.value;
	        this.lineno = token.lineno;

	        // Start and end are file positions for error handling.
	        this.start = token.start;
	        this.end = token.end;
	    } else {
	        this.lineno = t.lineno;
	    }

	    this.filename = t.filename;
	    this.children = [];

	    for (var prop in init)
	        this[prop] = init[prop];

		this.source = function()
		{
			return t.source.substr(this.start, this.end-this.start);
		}
	}

	/*
	 * SyntheticNode :: (optional init object) -> node
	 */
	function SyntheticNode(init) {
	    this.children = [];
	    for (var prop in init)
	        this[prop] = init[prop];
	    this.synthetic = true;
	}

	var Np = Node.prototype = SyntheticNode.prototype = {};
	Np.constructor = Node;

	var TO_SOURCE_SKIP = {
	    type: true,
	    value: true,
	    lineno: true,
	    start: true,
	    end: true,
	    tokenizer: true,
	    assignOp: true
	};
	function unevalableConst(code) {
	    var token = tokens[code];
	    var constName = opTypeNames.hasOwnProperty(token)
	        ? opTypeNames[token]
	        : token in keywords
	        ? token.toUpperCase()
	        : token;
	    return { toSource: function() { return constName } };
	}
	Np.toSource = function toSource() {
	    var mock = {};
	    var self = this;
	    mock.type = unevalableConst(this.type);
	    // avoid infinite recursion in case of back-links
	    if (this.generatingSource)
	        return mock.toSource();
	    this.generatingSource = true;
	    if ("value" in this)
	        mock.value = this.value;
	    if ("lineno" in this)
	        mock.lineno = this.lineno;
	    if ("start" in this)
	        mock.start = this.start;
	    if ("end" in this)
	        mock.end = this.end;
	    if (this.assignOp)
	        mock.assignOp = unevalableConst(this.assignOp);
	    for (var key in this) {
	        if (this.hasOwnProperty(key) && !(key in TO_SOURCE_SKIP))
	            mock[key] = this[key];
	    }
	    try {
	        return mock.toSource();
	    } finally {
	        delete this.generatingSource;
	    }
	};

	// Always use push to add operands to an expression, to update start and end.
	Np.push = function (kid) {
	    // kid can be null e.g. [1, , 2].
	    if (kid !== null) {
	        if (kid.start < this.start)
	            this.start = kid.start;
	        if (this.end < kid.end)
	            this.end = kid.end;
	    }
	    return this.children.push(kid);
	}

	Node.indentLevel = 0;

	function tokenString(tt) {
	    var t = tokens[tt];
	    return /^\W/.test(t) ? opTypeNames[t] : t.toUpperCase();
	}

	Np.toString = function () {
	    var a = [];
	    for (var i in this) {
	        if (this.hasOwnProperty(i) && i !== 'type' && i !== 'target')
	            a.push({id: i, value: this[i]});
	    }
	    a.sort(function (a,b) { return (a.id < b.id) ? -1 : 1; });
	    var INDENTATION = "    ";
	    var n = ++Node.indentLevel;
	    var s = "{\n" + INDENTATION.repeat(n) + "type: " + tokenString(this.type);
	    for (i = 0; i < a.length; i++)
	        s += ",\n" + INDENTATION.repeat(n) + a[i].id + ": " + a[i].value;
	    n = --Node.indentLevel;
	    s += "\n" + INDENTATION.repeat(n) + "}";
	    return s;
	}

	Np.synth = function(init) {
	    var node = new SyntheticNode(init);
	    node.filename = this.filename;
	    node.lineno = this.lineno;
	    node.start = this.start;
	    node.end = this.end;
	    return node;
	};

	/*
	 * Helper init objects for common nodes.
	 */

	var LOOP_INIT = { isLoop: true };

	function blockInit() {
	    return { type: BLOCK, varDecls: [] };
	}

	function scriptInit() {
	    return { type: SCRIPT,
	             funDecls: [],
	             varDecls: [],
	             modDefns: new Dict(),
	             modAssns: new Dict(),
	             modDecls: new Dict(),
	             modLoads: new Dict(),
	             impDecls: [],
	             expDecls: [],
	             exports: new Dict(),
	             hasEmptyReturn: false,
	             hasReturnWithValue: false,
	             hasYield: false };
	}

	defineGetter(Np, "length",
	                         function() {
	                             throw new Error("Node.prototype.length is gone; " +
	                                             "use n.children.length instead");
	                         });

	defineProperty(String.prototype, "repeat",
	                           function(n) {
	                               var s = "", t = this + s;
	                               while (--n >= 0)
	                                   s += t;
	                               return s;
	                           }, false, false, true);

	Pp.MaybeLeftParen = function MaybeLeftParen() {
	    if (this.parenFreeMode)
	        return this.match(LEFT_PAREN) ? LEFT_PAREN : END;
	    return this.mustMatch(LEFT_PAREN).type;
	};

	Pp.MaybeRightParen = function MaybeRightParen(p) {
	    if (p === LEFT_PAREN)
	        this.mustMatch(RIGHT_PAREN);
	}

	/*
	 * Statements :: (node[, boolean]) -> void
	 *
	 * Parses a sequence of Statements.
	 */
	Pp.Statements = function Statements(n, topLevel) {
	    var prologue = !!topLevel;
	    try {
	        while (!this.done() && this.peek(true) !== RIGHT_CURLY) {
	            var n2 = this.Statement();
	            n.push(n2);
	            if (prologue && Pragma(n2)) {
	                this.x.strictMode = true;
	                n.strict = true;
	            } else {
	                prologue = false;
	            }
	        }
	    } catch (e) {
	        if (this.done())
	            this.unexpectedEOF = true;
	        throw e;
	    }
	}

	Pp.Block = function Block() {
	    this.mustMatch(LEFT_CURLY);
	    var n = this.newNode(blockInit());
	    var x2 = this.x.update({ parentBlock: n }).pushTarget(n);
	    this.withContext(x2, function() {
	        this.Statements(n);
	    });
	    this.mustMatch(RIGHT_CURLY);
	    return n;
	}

	var DECLARED_FORM = 0, EXPRESSED_FORM = 1, STATEMENT_FORM = 2;

	/*
	 * Export :: (binding node, boolean) -> Export
	 *
	 * Static semantic representation of a module export.
	 */
	function Export(node, isDefinition) {
	    this.node = node;                 // the AST node declaring this individual export
	    this.isDefinition = isDefinition; // is the node an 'export'-annotated definition?
	    this.resolved = null;             // resolved pointer to the target of this export
	}

	/*
	 * registerExport :: (Dict, EXPORT node) -> void
	 */
	function registerExport(exports, decl) {
	    function register(name, exp) {
	        if (exports.has(name))
	            throw new SyntaxError("multiple exports of " + name);
	        exports.set(name, exp);
	    }

	    switch (decl.type) {
	      case MODULE:
	      case FUNCTION:
	        register(decl.name, new Export(decl, true));
	        break;

	      case VAR:
	        for (var i = 0; i < decl.children.length; i++)
	            register(decl.children[i].name, new Export(decl.children[i], true));
	        break;

	      case LET:
	      case CONST:
	        throw new Error("NYI: " + tokens[decl.type]);

	      case EXPORT:
	        for (var i = 0; i < decl.pathList.length; i++) {
	            var path = decl.pathList[i];
	            switch (path.type) {
	              case OBJECT_INIT:
	                for (var j = 0; j < path.children.length; j++) {
	                    // init :: IDENTIFIER | PROPERTY_INIT
	                    var init = path.children[j];
	                    if (init.type === IDENTIFIER)
	                        register(init.value, new Export(init, false));
	                    else
	                        register(init.children[0].value, new Export(init.children[1], false));
	                }
	                break;

	              case DOT:
	                register(path.children[1].value, new Export(path, false));
	                break;

	              case IDENTIFIER:
	                register(path.value, new Export(path, false));
	                break;

	              default:
	                throw new Error("unexpected export path: " + tokens[path.type]);
	            }
	        }
	        break;

	      default:
	        throw new Error("unexpected export decl: " + tokens[exp.type]);
	    }
	}

	/*
	 * Module :: (node) -> Module
	 *
	 * Static semantic representation of a module.
	 */
	function Module(node) {
	    var exports = node.body.exports;
	    var modDefns = node.body.modDefns;

	    var exportedModules = new Dict();

	    exports.forEach(function(name, exp) {
	        var node = exp.node;
	        if (node.type === MODULE) {
	            exportedModules.set(name, node);
	        } else if (!exp.isDefinition && node.type === IDENTIFIER && modDefns.has(node.value)) {
	            var mod = modDefns.get(node.value);
	            exportedModules.set(name, mod);
	        }
	    });

	    this.node = node;
	    this.exports = exports;
	    this.exportedModules = exportedModules;
	}

	/*
	 * Statement :: () -> node
	 *
	 * Parses a Statement.
	 */
	Pp.Statement = function Statement() {
	    var i, label, n, n2, p, c, ss, tt = this.t.get(true), tt2, x0, x2, x3;

	    var comments = this.t.blockComments;

	    // Cases for statements ending in a right curly return early, avoiding the
	    // common semicolon insertion magic after this switch.
	    switch (tt) {
	      case IMPORT:
	        if (!this.x.canImport())
	            this.fail("illegal context for import statement");
	        n = this.newNode();
	        n.pathList = this.ImportPathList();
	        this.x.parentScript.impDecls.push(n);
	        break;

	      case EXPORT:
	        if (!this.x.canExport())
	            this.fail("export statement not in module top level");
	        switch (this.peek()) {
	          case MODULE:
	          case FUNCTION:
	          case LET:
	          case VAR:
	          case CONST:
	            n = this.Statement();
	            n.blockComments = comments;
	            n.exported = true;
	            this.x.parentScript.expDecls.push(n);
	            registerExport(this.x.parentScript.exports, n);
	            return n;
	        }
	        n = this.newNode();
	        n.pathList = this.ExportPathList();
	        this.x.parentScript.expDecls.push(n);
	        registerExport(this.x.parentScript.exports, n);
	        break;

	      case FUNCTION:
	        // DECLARED_FORM extends funDecls of x, STATEMENT_FORM doesn't.
	        return this.FunctionDefinition(true, this.x.topLevel ? DECLARED_FORM : STATEMENT_FORM, comments);

	      case LEFT_CURLY:
	        n = this.newNode(blockInit());
	        x2 = this.x.update({ parentBlock: n }).pushTarget(n).nest();
	        this.withContext(x2, function() {
	            this.Statements(n);
	        });
	        this.mustMatch(RIGHT_CURLY);
	        return n;

	      case IF:
	        n = this.newNode();
	        n.condition = this.HeadExpression();
	        x2 = this.x.pushTarget(n).nest();
	        this.withContext(x2, function() {
	            n.thenPart = this.Statement();
	            n.elsePart = this.match(ELSE, true) ? this.Statement() : null;
	        });
	        return n;

	      case SWITCH:
	        // This allows CASEs after a DEFAULT, which is in the standard.
	        n = this.newNode({ cases: [], defaultIndex: -1 });
	        n.discriminant = this.HeadExpression();
	        x2 = this.x.pushTarget(n).nest();
	        this.withContext(x2, function() {
	            this.mustMatch(LEFT_CURLY);
	            while ((tt = this.t.get()) !== RIGHT_CURLY) {
	                switch (tt) {
	                  case DEFAULT:
	                    if (n.defaultIndex >= 0)
	                        this.fail("More than one switch default");
	                    // FALL THROUGH
	                  case CASE:
	                    n2 = this.newNode();
	                    if (tt === DEFAULT)
	                        n.defaultIndex = n.cases.length;
	                    else
	                        n2.caseLabel = this.Expression(COLON);
	                    break;

	                  default:
	                    this.fail("Invalid switch case");
	                }
	                this.mustMatch(COLON);
	                n2.statements = this.newNode(blockInit());
	                while ((tt=this.peek(true)) !== CASE && tt !== DEFAULT &&
	                       tt !== RIGHT_CURLY)
	                    n2.statements.push(this.Statement());
	                n.cases.push(n2);
	            }
	        });
	        return n;

	      case FOR:
	        n = this.newNode(LOOP_INIT);
	        n.blockComments = comments;
	        if (this.match(IDENTIFIER)) {
	            if (this.t.token.value === "each")
	                n.isEach = true;
	            else
	                this.t.unget();
	        }
	        if (!this.parenFreeMode)
	            this.mustMatch(LEFT_PAREN);
	        x2 = this.x.pushTarget(n).nest();
	        x3 = this.x.update({ inForLoopInit: true });
	        n2 = null;
	        if ((tt = this.peek(true)) !== SEMICOLON) {
	            this.withContext(x3, function() {
	                if (tt === VAR || tt === CONST) {
	                    this.t.get();
	                    n2 = this.Variables();
	                } else if (tt === LET) {
	                    this.t.get();
	                    if (this.peek() === LEFT_PAREN) {
	                        n2 = this.LetBlock(false);
	                    } else {
	                        // Let in for head, we need to add an implicit block
	                        // around the rest of the for.
	                        this.x.parentBlock = n;
	                        n.varDecls = [];
	                        n2 = this.Variables();
	                    }
	                } else {
	                    n2 = this.Expression();
	                }
	            });
	        }
	        if (n2 && this.match(IN)) {
	            n.type = FOR_IN;
	            this.withContext(x3, function() {
	                n.object = this.Expression();
	                if (n2.type === VAR || n2.type === LET) {
	                    c = n2.children;

	                    // Destructuring turns one decl into multiples, so either
	                    // there must be only one destructuring or only one
	                    // decl.
	                    if (c.length !== 1 && n2.destructurings.length !== 1) {
	                        // FIXME: this.fail ?
	                        throw new SyntaxError("Invalid for..in left-hand side",
	                                              this.filename, n2.lineno);
	                    }
	                    if (n2.destructurings.length > 0) {
	                        n.iterator = n2.destructurings[0];
	                    } else {
	                        n.iterator = c[0];
	                    }
	                    n.varDecl = n2;
	                } else {
	                    if (n2.type === ARRAY_INIT || n2.type === OBJECT_INIT) {
	                        n2.destructuredNames = this.checkDestructuring(n2);
	                    }
	                    n.iterator = n2;
	                }
	            });
	        } else {
	            x3.inForLoopInit = false;
	            n.setup = n2;
	            this.mustMatch(SEMICOLON);
	            if (n.isEach)
	                this.fail("Invalid for each..in loop");
	            this.withContext(x3, function() {
	                n.condition = (this.peek(true) === SEMICOLON)
	                    ? null
	                    : this.Expression();
	                this.mustMatch(SEMICOLON);
	                tt2 = this.peek(true);
	                n.update = (this.parenFreeMode
	                            ? tt2 === LEFT_CURLY || isStatementStartCode[tt2]
	                            : tt2 === RIGHT_PAREN)
	                    ? null
	                    : this.Expression();
	            });
	        }
	        if (!this.parenFreeMode)
	            this.mustMatch(RIGHT_PAREN);
	        this.withContext(x2, function() {
	            n.body = this.Statement();
	        });
	        return n;

	      case WHILE:
	        n = this.newNode({ isLoop: true });
	        n.blockComments = comments;
	        n.condition = this.HeadExpression();
	        x2 = this.x.pushTarget(n).nest();
	        this.withContext(x2, function() {
	            n.body = this.Statement();
	        });
	        return n;

	      case DO:
	        n = this.newNode({ isLoop: true });
	        n.blockComments = comments;
	        x2 = this.x.pushTarget(n).next();
	        this.withContext(x2, function() {
	            n.body = this.Statement();
	        });
	        this.mustMatch(WHILE);
	        n.condition = this.HeadExpression();
	        // <script language="JavaScript"> (without version hints) may need
	        // automatic semicolon insertion without a newline after do-while.
	        // See http://bugzilla.mozilla.org/show_bug.cgi?id=238945.
	        this.match(SEMICOLON);
	        return n;

	      case BREAK:
	      case CONTINUE:
	        n = this.newNode();
	        n.blockComments = comments;

	        // handle the |foo: break foo;| corner case
	        x2 = this.x.pushTarget(n);

	        if (this.peekOnSameLine() === IDENTIFIER) {
	            this.t.get();
	            n.label = this.t.token.value;
	        }

	        if (n.label) {
	            n.target = x2.labeledTargets.find(function(target) {
	                return target.labels.has(n.label)
	            });
	        } else if (tt === CONTINUE) {
	            n.target = x2.defaultLoopTarget;
	        } else {
	            n.target = x2.defaultTarget;
	        }

	        if (!n.target)
	            this.fail("Invalid " + ((tt === BREAK) ? "break" : "continue"));
	        if (!n.target.isLoop && tt === CONTINUE)
	            this.fail("Invalid continue");

	        break;

	      case TRY:
	        n = this.newNode({ catchClauses: [] });
	        n.blockComments = comments;
	        n.tryBlock = this.Block();
	        while (this.match(CATCH)) {
	            n2 = this.newNode();
	            p = this.MaybeLeftParen();
	            switch (this.t.get()) {
	              case LEFT_BRACKET:
	              case LEFT_CURLY:
	                // Destructured catch identifiers.
	                this.t.unget();
	                n2.varName = this.DestructuringExpression(true);
	                break;
	              case IDENTIFIER:
	                n2.varName = this.t.token.value;
	                break;
	              default:
	                this.fail("missing identifier in catch");
	                break;
	            }
	            if (this.match(IF)) {
	                if (!this.mozillaMode)
	                    this.fail("Illegal catch guard");
	                if (n.catchClauses.length && !n.catchClauses.top().guard)
	                    this.fail("Guarded catch after unguarded");
	                n2.guard = this.Expression();
	            }
	            this.MaybeRightParen(p);
	            n2.block = this.Block();
	            n.catchClauses.push(n2);
	        }
	        if (this.match(FINALLY))
	            n.finallyBlock = this.Block();
	        if (!n.catchClauses.length && !n.finallyBlock)
	            this.fail("Invalid try statement");
	        return n;

	      case CATCH:
	      case FINALLY:
	        this.fail(tokens[tt] + " without preceding try");

	      case THROW:
	        n = this.newNode();
	        n.exception = this.Expression();
	        break;

	      case RETURN:
	        n = this.ReturnOrYield();
	        break;

	      case WITH:
	        if (this.x.banWith())
	            this.fail("with statements not allowed in strict code or modules");
	        n = this.newNode();
	        n.blockComments = comments;
	        n.object = this.HeadExpression();
	        x2 = this.x.pushTarget(n).next();
	        this.withContext(x2, function() {
	            n.body = this.Statement();
	        });
	        return n;

	      case VAR:
	      case CONST:
	        n = this.Variables();
	        break;

	      case LET:
	        if (this.peek() === LEFT_PAREN) {
	            n = this.LetBlock(true);
	            return n;
	        }
	        n = this.Variables();
	        break;

	      case DEBUGGER:
	        n = this.newNode();
	        break;

	      case NEWLINE:
	      case SEMICOLON:
	        n = this.newNode({ type: SEMICOLON });
	        n.blockComments = comments;
	        n.expression = null;
	        return n;

	      case IDENTIFIER:
	      case USE:
	      case MODULE:
	        switch (this.t.token.value) {
	          case "use":
	            if (!isPragmaToken(this.peekOnSameLine())) {
	                this.t.unget();
	                break;
	            }
	            return this.newNode({ type: USE, params: this.Pragmas() });

	          case "module":
	            if (!this.x.modulesAllowed())
	                this.fail("module declaration not at top level");
	            this.x.parentScript.hasModules = true;
	            tt = this.peekOnSameLine();
	            if (tt !== IDENTIFIER && tt !== LEFT_CURLY) {
	                this.t.unget();
	                break;
	            }
	            n = this.newNode({ type: MODULE });
	            n.blockComments = comments;
	            this.mustMatch(IDENTIFIER);
	            label = this.t.token.value;

	            if (this.match(LEFT_CURLY)) {
	                n.name = label;
	                n.body = this.Script(true, false);
	                n.module = new Module(n);
	                this.mustMatch(RIGHT_CURLY);
	                this.x.parentScript.modDefns.set(n.name, n);
	                return n;
	            }

	            this.t.unget();
	            this.ModuleVariables(n);
	            return n;

	          default:
	            tt = this.peek();
	            // Labeled statement.
	            if (tt === COLON) {
	                label = this.t.token.value;
	                if (this.x.allLabels.has(label))
	                    this.fail("Duplicate label: " + label);
	                this.t.get();
	                n = this.newNode({ type: LABEL, label: label });
	                n.blockComments = comments;
	                x2 = this.x.pushLabel(label).nest();
	                this.withContext(x2, function() {
	                    n.statement = this.Statement();
	                });
	                n.target = (n.statement.type === LABEL) ? n.statement.target : n.statement;
	                return n;
	            }
	            // FALL THROUGH
	        }
	        // FALL THROUGH

	      default:
	        // Expression statement.
	        // We unget the current token to parse the expression as a whole.
	        n = this.newNode({ type: SEMICOLON });
	        this.t.unget();
	        n.blockComments = comments;
	        n.expression = this.Expression();
	        n.end = n.expression.end;
	        break;
	    }

	    n.blockComments = comments;
	    this.MagicalSemicolon();
	    return n;
	}

	/*
	 * isPragmaToken :: (number) -> boolean
	 */
	function isPragmaToken(tt) {
	    switch (tt) {
	      case IDENTIFIER:
	      case STRING:
	      case NUMBER:
	      case NULL:
	      case TRUE:
	      case FALSE:
	        return true;
	    }
	    return false;
	}

	/*
	 * Pragmas :: () -> Array[Array[token]]
	 */
	Pp.Pragmas = function Pragmas() {
	    var pragmas = [];
	    do {
	        pragmas.push(this.Pragma());
	    } while (this.match(COMMA));
	    this.MagicalSemicolon();
	    return pragmas;
	}

	/*
	 * Pragmas :: () -> Array[token]
	 */
	Pp.Pragma = function Pragma() {
	    var items = [];
	    var tt;
	    do {
	        tt = this.t.get(true);
	        items.push(this.t.token);
	    } while (isPragmaToken(this.peek()));
	    return items;
	}

	/*
	 * MagicalSemicolon :: () -> void
	 */
	Pp.MagicalSemicolon = function MagicalSemicolon() {
	    var tt;
	    if (this.t.lineno === this.t.token.lineno) {
	        tt = this.peekOnSameLine();
	        if (tt !== END && tt !== NEWLINE && tt !== SEMICOLON && tt !== RIGHT_CURLY)
	            this.fail("missing ; before statement");
	    }
	    this.match(SEMICOLON);
	}

	/*
	 * ReturnOrYield :: () -> (RETURN | YIELD) node
	 */
	Pp.ReturnOrYield = function ReturnOrYield() {
	    var n, b, tt = this.t.token.type, tt2;

	    var parentScript = this.x.parentScript;

	    if (tt === RETURN) {
	        if (!this.x.inFunction)
	            this.fail("Return not in function");
	    } else /* if (tt === YIELD) */ {
	        if (!this.x.inFunction)
	            this.fail("Yield not in function");
	        parentScript.hasYield = true;
	    }
	    n = this.newNode({ value: undefined });

	    tt2 = (tt === RETURN) ? this.peekOnSameLine(true) : this.peek(true);
	    if (tt2 !== END && tt2 !== NEWLINE &&
	        tt2 !== SEMICOLON && tt2 !== RIGHT_CURLY
	        && (tt !== YIELD ||
	            (tt2 !== tt && tt2 !== RIGHT_BRACKET && tt2 !== RIGHT_PAREN &&
	             tt2 !== COLON && tt2 !== COMMA))) {
	        if (tt === RETURN) {
	            n.value = this.Expression();
	            parentScript.hasReturnWithValue = true;
	        } else {
	            n.value = this.AssignExpression();
	        }
	    } else if (tt === RETURN) {
	        parentScript.hasEmptyReturn = true;
	    }

	    return n;
	}

	/*
	 * ModuleExpression :: () -> (STRING | IDENTIFIER | DOT) node
	 */
	Pp.ModuleExpression = function ModuleExpression() {
	    return this.match(STRING) ? this.newNode() : this.QualifiedPath();
	}

	/*
	 * ImportPathList :: () -> Array[DOT node]
	 */
	Pp.ImportPathList = function ImportPathList() {
	    var a = [];
	    do {
	        a.push(this.ImportPath());
	    } while (this.match(COMMA));
	    return a;
	}

	/*
	 * ImportPath :: () -> DOT node
	 */
	Pp.ImportPath = function ImportPath() {
	    var n = this.QualifiedPath();
	    if (!this.match(DOT)) {
	        if (n.type === IDENTIFIER)
	            this.fail("cannot import local variable");
	        return n;
	    }

	    var n2 = this.newNode();
	    n2.push(n);
	    n2.push(this.ImportSpecifierSet());
	    return n2;
	}

	/*
	 * ExplicitSpecifierSet :: (() -> node) -> OBJECT_INIT node
	 */
	Pp.ExplicitSpecifierSet = function ExplicitSpecifierSet(SpecifierRHS) {
	    var n, n2, id, tt;

	    n = this.newNode({ type: OBJECT_INIT });
	    this.mustMatch(LEFT_CURLY);

	    if (!this.match(RIGHT_CURLY)) {
	        do {
	            id = this.Identifier();
	            if (this.match(COLON)) {
	                n2 = this.newNode({ type: PROPERTY_INIT });
	                n2.push(id);
	                n2.push(SpecifierRHS());
	                n.push(n2);
	            } else {
	                n.push(id);
	            }
	        } while (!this.match(RIGHT_CURLY) && this.mustMatch(COMMA));
	    }

	    return n;
	}

	/*
	 * ImportSpecifierSet :: () -> (IDENTIFIER | OBJECT_INIT) node
	 */
	Pp.ImportSpecifierSet = function ImportSpecifierSet() {
	    var self = this;
	    return this.match(MUL)
	        ? this.newNode({ type: IDENTIFIER, name: "*" })
	    : ExplicitSpecifierSet(function() { return self.Identifier() });
	}

	/*
	 * Identifier :: () -> IDENTIFIER node
	 */
	Pp.Identifier = function Identifier() {
	    this.mustMatch(IDENTIFIER);
	    return this.newNode({ type: IDENTIFIER });
	}

	/*
	 * IdentifierName :: () -> IDENTIFIER node
	 */
	Pp.IdentifierName = function IdentifierName() {
	    this.mustMatch(IDENTIFIER, true);
	    return this.newNode({ type: IDENTIFIER });
	}

	/*
	 * QualifiedPath :: () -> (IDENTIFIER | DOT) node
	 */
	Pp.QualifiedPath = function QualifiedPath() {
	    var n, n2;

	    n = this.Identifier();

	    while (this.match(DOT)) {
	        if (this.peek() !== IDENTIFIER) {
	            // Unget the '.' token, which isn't part of the QualifiedPath.
	            this.t.unget();
	            break;
	        }
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.Identifier());
	        n = n2;
	    }

	    return n;
	}

	/*
	 * ExportPath :: () -> (IDENTIFIER | DOT | OBJECT_INIT) node
	 */
	Pp.ExportPath = function ExportPath() {
	    var self = this;
	    if (this.peek() === LEFT_CURLY)
	        return this.ExplicitSpecifierSet(function() { return self.QualifiedPath() });
	    return this.QualifiedPath();
	}

	/*
	 * ExportPathList :: () -> Array[(IDENTIFIER | DOT | OBJECT_INIT) node]
	 */
	Pp.ExportPathList = function ExportPathList() {
	    var a = [];
	    do {
	        a.push(this.ExportPath());
	    } while (this.match(COMMA));
	    return a;
	}

	/*
	 * FunctionDefinition :: (boolean,
	 *                        DECLARED_FORM or EXPRESSED_FORM or STATEMENT_FORM,
	 *                        [string] or null or undefined)
	 *                    -> node
	 */
	Pp.FunctionDefinition = function FunctionDefinition(requireName, functionForm, comments) {
	    var tt;
	    var f = this.newNode({ params: [], paramComments: [] });
	    if (typeof comments === "undefined")
	        comments = null;
	    f.blockComments = comments;
	    if (f.type !== FUNCTION)
	        f.type = (f.value === "get") ? GETTER : SETTER;
	    if (this.match(MUL))
	        f.isExplicitGenerator = true;
	    if (this.match(IDENTIFIER, false, true))
	        f.name = this.t.token.value;
	    else if (requireName)
	        this.fail("missing function identifier");

	    var inModule = this.x.inModule;
	    x2 = new StaticContext(null, null, inModule, true, this.x.strictMode);
	    this.withContext(x2, function() {
	        this.mustMatch(LEFT_PAREN);
	        if (!this.match(RIGHT_PAREN)) {
	            do {
	                tt = this.t.get();
	                f.paramComments.push(this.t.lastBlockComment());
	                switch (tt) {
	                  case LEFT_BRACKET:
	                  case LEFT_CURLY:
	                    // Destructured formal parameters.
	                    this.t.unget();
	                    f.params.push(this.DestructuringExpression());
	                    break;
	                  case IDENTIFIER:
	                    f.params.push(this.t.token.value);
	                    break;
	                  default:
	                    this.fail("missing formal parameter");
	                }
	            } while (this.match(COMMA));
	            this.mustMatch(RIGHT_PAREN);
	        }

	        // Do we have an expression closure or a normal body?
	        tt = this.t.get(true);
	        if (tt !== LEFT_CURLY)
	            this.t.unget();

	        if (tt !== LEFT_CURLY) {
	            f.body = this.AssignExpression();
	        } else {
	            f.body = this.Script(inModule, true);
	        }
	    });

	    if (tt === LEFT_CURLY)
	        this.mustMatch(RIGHT_CURLY);

	    f.end = this.t.token.end;
	    f.functionForm = functionForm;
	    if (functionForm === DECLARED_FORM)
	        this.x.parentScript.funDecls.push(f);

	    if (this.x.inModule && !f.isExplicitGenerator && f.body.hasYield)
	        this.fail("yield in non-generator function");

	    if (f.isExplicitGenerator || f.body.hasYield)
	        f.body = this.newNode({ type: GENERATOR, body: f.body });

	    return f;
	}

	/*
	 * ModuleVariables :: (MODULE node) -> void
	 *
	 * Parses a comma-separated list of module declarations (and maybe
	 * initializations).
	 */
	Pp.ModuleVariables = function ModuleVariables(n) {
	    var n1, n2;
	    do {
	        n1 = this.Identifier();
	        if (this.match(ASSIGN)) {
	            n2 = this.ModuleExpression();
	            n1.initializer = n2;
	            if (n2.type === STRING)
	                this.x.parentScript.modLoads.set(n1.value, n2.value);
	            else
	                this.x.parentScript.modAssns.set(n1.value, n1);
	        }
	        n.push(n1);
	    } while (this.match(COMMA));
	}

	/*
	 * Variables :: () -> node
	 *
	 * Parses a comma-separated list of var declarations (and maybe
	 * initializations).
	 */
	Pp.Variables = function Variables(letBlock) {
	    var n, n2, ss, i, s, tt;

	    tt = this.t.token.type;
	    switch (tt) {
	      case VAR:
	      case CONST:
	        s = this.x.parentScript;
	        break;
	      case LET:
	        s = this.x.parentBlock;
	        break;
	      case LEFT_PAREN:
	        tt = LET;
	        s = letBlock;
	        break;
	    }

	    n = this.newNode({ type: tt, destructurings: [] });

	    do {
	        tt = this.t.get();
	        if (tt === LEFT_BRACKET || tt === LEFT_CURLY) {
	            // Need to unget to parse the full destructured expression.
	            this.t.unget();

	            var dexp = this.DestructuringExpression(true);

	            n2 = this.newNode({ type: IDENTIFIER,
	                                name: dexp,
	                                readOnly: n.type === CONST });
	            n.push(n2);
	            pushDestructuringVarDecls(n2.name.destructuredNames, s);
	            n.destructurings.push({ exp: dexp, decl: n2 });

	            if (this.x.inForLoopInit && this.peek() === IN) {
	                continue;
	            }

	            this.mustMatch(ASSIGN);
	            if (this.t.token.assignOp)
	                this.fail("Invalid variable initialization");

	            n2.blockComment = this.t.lastBlockComment();
	            n2.initializer = this.AssignExpression();

	            continue;
	        }

	        if (tt !== IDENTIFIER)
	            this.fail("missing variable name");

	        n2 = this.newNode({ type: IDENTIFIER,
	                            name: this.t.token.value,
	                            readOnly: n.type === CONST });
	        n.push(n2);
	        s.varDecls.push(n2);

	        if (this.match(ASSIGN)) {
	            var comment = this.t.lastBlockComment();
	            if (this.t.token.assignOp)
	                this.fail("Invalid variable initialization");

	            n2.initializer = this.AssignExpression();
	        } else {
	            var comment = this.t.lastBlockComment();
	        }
	        n2.blockComment = comment;
	    } while (this.match(COMMA));

	    return n;
	}

	/*
	 * LetBlock :: (boolean) -> node
	 *
	 * Does not handle let inside of for loop init.
	 */
	Pp.LetBlock = function LetBlock(isStatement) {
	    var n, n2;

	    // t.token.type must be LET
	    n = this.newNode({ type: LET_BLOCK, varDecls: [] });
	    this.mustMatch(LEFT_PAREN);
	    n.variables = this.Variables(n);
	    this.mustMatch(RIGHT_PAREN);

	    if (isStatement && this.peek() !== LEFT_CURLY) {
	        /*
	         * If this is really an expression in let statement guise, then we
	         * need to wrap the LET_BLOCK node in a SEMICOLON node so that we pop
	         * the return value of the expression.
	         */
	        n2 = this.newNode({ type: SEMICOLON, expression: n });
	        isStatement = false;
	    }

	    if (isStatement)
	        n.block = this.Block();
	    else
	        n.expression = this.AssignExpression();

	    return n;
	}

	Pp.checkDestructuring = function checkDestructuring(n, simpleNamesOnly) {
	    if (n.type === ARRAY_COMP)
	        this.fail("Invalid array comprehension left-hand side");
	    if (n.type !== ARRAY_INIT && n.type !== OBJECT_INIT)
	        return;

	    var lhss = {};
	    var nn, n2, idx, sub, cc, c = n.children;
	    for (var i = 0, j = c.length; i < j; i++) {
	        if (!(nn = c[i]))
	            continue;
	        if (nn.type === PROPERTY_INIT) {
	            cc = nn.children;
	            sub = cc[1];
	            idx = cc[0].value;
	        } else if (n.type === OBJECT_INIT) {
	            // Do we have destructuring shorthand {foo, bar}?
	            sub = nn;
	            idx = nn.value;
	        } else {
	            sub = nn;
	            idx = i;
	        }

	        if (sub.type === ARRAY_INIT || sub.type === OBJECT_INIT) {
	            lhss[idx] = this.checkDestructuring(sub, simpleNamesOnly);
	        } else {
	            if (simpleNamesOnly && sub.type !== IDENTIFIER) {
	                // In declarations, lhs must be simple names
	                this.fail("missing name in pattern");
	            }

	            lhss[idx] = sub;
	        }
	    }

	    return lhss;
	}

	Pp.DestructuringExpression = function DestructuringExpression(simpleNamesOnly) {
	    var n = this.PrimaryExpression();
	    // Keep the list of lefthand sides for varDecls
	    n.destructuredNames = this.checkDestructuring(n, simpleNamesOnly);
	    return n;
	}

	Pp.GeneratorExpression = function GeneratorExpression(e) {
	    return this.newNode({ type: GENERATOR,
	                          expression: e,
	                          tail: this.ComprehensionTail() });
	}

	Pp.ComprehensionTail = function ComprehensionTail() {
	    var body, n, n2, n3, p;

	    // t.token.type must be FOR
	    body = this.newNode({ type: COMP_TAIL });

	    do {
	        // Comprehension tails are always for..in loops.
	        n = this.newNode({ type: FOR_IN, isLoop: true });
	        if (this.match(IDENTIFIER)) {
	            // But sometimes they're for each..in.
	            if (this.mozillaMode && this.t.token.value === "each")
	                n.isEach = true;
	            else
	                this.t.unget();
	        }
	        p = this.MaybeLeftParen();
	        switch(this.t.get()) {
	          case LEFT_BRACKET:
	          case LEFT_CURLY:
	            this.t.unget();
	            // Destructured left side of for in comprehension tails.
	            n.iterator = this.DestructuringExpression();
	            break;

	          case IDENTIFIER:
	            n.iterator = n3 = this.newNode({ type: IDENTIFIER });
	            n3.name = n3.value;
	            n.varDecl = n2 = this.newNode({ type: VAR });
	            n2.push(n3);
	            this.x.parentScript.varDecls.push(n3);
	            // Don't add to varDecls since the semantics of comprehensions is
	            // such that the variables are in their own function when
	            // desugared.
	            break;

	          default:
	            this.fail("missing identifier");
	        }
	        this.mustMatch(IN);
	        n.object = this.Expression();
	        this.MaybeRightParen(p);
	        body.push(n);
	    } while (this.match(FOR));

	    // Optional guard.
	    if (this.match(IF))
	        body.guard = this.HeadExpression();

	    return body;
	}

	Pp.HeadExpression = function HeadExpression() {
	    var p = this.MaybeLeftParen();
	    var n = this.ParenExpression();
	    this.MaybeRightParen(p);
	    if (p === END && !n.parenthesized) {
	        var tt = this.peek();
	        if (tt !== LEFT_CURLY && !isStatementStartCode[tt])
	            this.fail("Unparenthesized head followed by unbraced body");
	    }
	    return n;
	}

	Pp.ParenExpression = function ParenExpression() {
	    // Always accept the 'in' operator in a parenthesized expression,
	    // where it's unambiguous, even if we might be parsing the init of a
	    // for statement.
	    var x2 = this.x.update({
	        inForLoopInit: this.x.inForLoopInit && (this.t.token.type === LEFT_PAREN)
	    });
	    var n = this.withContext(x2, function() {
	        return this.Expression();
	    });
	    if (this.match(FOR)) {
	        if (n.type === YIELD && !n.parenthesized)
	            this.fail("Yield expression must be parenthesized");
	        if (n.type === COMMA && !n.parenthesized)
	            this.fail("Generator expression must be parenthesized");
	        n = this.GeneratorExpression(n);
	    }

	    return n;
	}

	/*
	 * Expression :: () -> node
	 *
	 * Top-down expression parser matched against SpiderMonkey.
	 */
	Pp.Expression = function Expression() {
	    var n, n2;

	    n = this.AssignExpression();
	    if (this.match(COMMA)) {
	        n2 = this.newNode({ type: COMMA });
	        n2.push(n);
	        n = n2;
	        do {
	            n2 = n.children[n.children.length-1];
	            if (n2.type === YIELD && !n2.parenthesized)
	                this.fail("Yield expression must be parenthesized");
	            n.push(this.AssignExpression());
	        } while (this.match(COMMA));
	    }

	    return n;
	}

	Pp.AssignExpression = function AssignExpression() {
	    var n, lhs;

	    // Have to treat yield like an operand because it could be the leftmost
	    // operand of the expression.
	    if (this.match(YIELD, true))
	        return this.ReturnOrYield();

	    n = this.newNode({ type: ASSIGN });
	    lhs = this.ConditionalExpression();

	    if (!this.match(ASSIGN)) {
	        return lhs;
	    }

	    n.blockComment = this.t.lastBlockComment();

	    switch (lhs.type) {
	      case OBJECT_INIT:
	      case ARRAY_INIT:
	        lhs.destructuredNames = this.checkDestructuring(lhs);
	        // FALL THROUGH
	      case IDENTIFIER: case DOT: case INDEX: case CALL:
	        break;
	      default:
	        this.fail("Bad left-hand side of assignment");
	        break;
	    }

	    n.assignOp = lhs.assignOp = this.t.token.assignOp;
	    n.push(lhs);
	    n.push(this.AssignExpression());

	    return n;
	}

	Pp.ConditionalExpression = function ConditionalExpression() {
	    var n, n2;

	    n = this.OrExpression();
	    if (this.match(HOOK)) {
	        n2 = n;
	        n = this.newNode({ type: HOOK });
	        n.push(n2);
	        /*
	         * Always accept the 'in' operator in the middle clause of a ternary,
	         * where it's unambiguous, even if we might be parsing the init of a
	         * for statement.
	         */
	        var x2 = this.x.update({ inForLoopInit: false });
	        this.withContext(x2, function() {
	            n.push(this.AssignExpression());
	        });
	        if (!this.match(COLON))
	            this.fail("missing : after ?");
	        n.push(this.AssignExpression());
	    }

	    return n;
	}

	Pp.OrExpression = function OrExpression() {
	    var n, n2;

	    n = this.AndExpression();
	    while (this.match(OR)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.AndExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.AndExpression = function AndExpression() {
	    var n, n2;

	    n = this.BitwiseOrExpression();
	    while (this.match(AND)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.BitwiseOrExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.BitwiseOrExpression = function BitwiseOrExpression() {
	    var n, n2;

	    n = this.BitwiseXorExpression();
	    while (this.match(BITWISE_OR)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.BitwiseXorExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.BitwiseXorExpression = function BitwiseXorExpression() {
	    var n, n2;

	    n = this.BitwiseAndExpression();
	    while (this.match(BITWISE_XOR)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.BitwiseAndExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.BitwiseAndExpression = function BitwiseAndExpression() {
	    var n, n2;

	    n = this.EqualityExpression();
	    while (this.match(BITWISE_AND)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.EqualityExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.EqualityExpression = function EqualityExpression() {
	    var n, n2;

	    n = this.RelationalExpression();
	    while (this.match(EQ) || this.match(NE) ||
	           this.match(STRICT_EQ) || this.match(STRICT_NE)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.RelationalExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.RelationalExpression = function RelationalExpression() {
	    var n, n2;

	    /*
	     * Uses of the in operator in shiftExprs are always unambiguous,
	     * so unset the flag that prohibits recognizing it.
	     */
	    var x2 = this.x.update({ inForLoopInit: false });
	    this.withContext(x2, function() {
	        n = this.ShiftExpression();
	        while ((this.match(LT) || this.match(LE) || this.match(GE) || this.match(GT) ||
	                (!this.x.inForLoopInit && this.match(IN)) ||
	                this.match(INSTANCEOF))) {
	            n2 = this.newNode();
	            n2.push(n);
	            n2.push(this.ShiftExpression());
	            n = n2;
	        }
	    });

	    return n;
	}

	Pp.ShiftExpression = function ShiftExpression() {
	    var n, n2;

	    n = this.AddExpression();
	    while (this.match(LSH) || this.match(RSH) || this.match(URSH)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.AddExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.AddExpression = function AddExpression() {
	    var n, n2;

	    n = this.MultiplyExpression();
	    while (this.match(PLUS) || this.match(MINUS)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.MultiplyExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.MultiplyExpression = function MultiplyExpression() {
	    var n, n2;

	    n = this.UnaryExpression();
	    while (this.match(MUL) || this.match(DIV) || this.match(MOD)) {
	        n2 = this.newNode();
	        n2.push(n);
	        n2.push(this.UnaryExpression());
	        n = n2;
	    }

	    return n;
	}

	Pp.UnaryExpression = function UnaryExpression() {
	    var n, n2, tt;

	    switch (tt = this.t.get(true)) {
	      case DELETE: case VOID: case TYPEOF:
	      case NOT: case BITWISE_NOT: case PLUS: case MINUS:
	        if (tt === PLUS)
	            n = this.newNode({ type: UNARY_PLUS });
	        else if (tt === MINUS)
	            n = this.newNode({ type: UNARY_MINUS });
	        else
	            n = this.newNode();
	        n.push(this.UnaryExpression());
	        break;

	      case INCREMENT:
	      case DECREMENT:
	        // Prefix increment/decrement.
	        n = this.newNode();
	        n.push(this.MemberExpression(true));
	        break;

	      default:
	        this.t.unget();
	        n = this.MemberExpression(true);

	        // Don't look across a newline boundary for a postfix {in,de}crement.
	        if (this.t.tokens[(this.t.tokenIndex + this.t.lookahead - 1) & 3].lineno ===
	            this.t.lineno) {
	            if (this.match(INCREMENT) || this.match(DECREMENT)) {
	                n2 = this.newNode({ postfix: true });
	                n2.push(n);
	                n = n2;
	            }
	        }
	        break;
	    }

	    return n;
	}

	Pp.MemberExpression = function MemberExpression(allowCallSyntax) {
	    var n, n2, name, tt;

	    if (this.match(NEW)) {
	        n = this.newNode();
	        n.push(this.MemberExpression(false));
	        if (this.match(LEFT_PAREN)) {
	            n.type = NEW_WITH_ARGS;
	            n.push(this.ArgumentList());
	        }
	    } else {
	        n = this.PrimaryExpression();
	    }

	    while ((tt = this.t.get()) !== END) {
	        switch (tt) {
	          case DOT:
	            n2 = this.newNode();
	            n2.push(n);
	            n2.push(this.IdentifierName());
	            break;

	          case LEFT_BRACKET:
	            n2 = this.newNode({ type: INDEX });
	            n2.push(n);
	            n2.push(this.Expression());
	            this.mustMatch(RIGHT_BRACKET);
	            break;

	          case LEFT_PAREN:
	            if (allowCallSyntax) {
	                n2 = this.newNode({ type: CALL });
	                n2.push(n);
	                n2.push(this.ArgumentList());
	                break;
	            }

	            // FALL THROUGH
	          default:
	            this.t.unget();
	            return n;
	        }

	        n = n2;
	    }

	    return n;
	}

	Pp.ArgumentList = function ArgumentList() {
	    var n, n2;

	    n = this.newNode({ type: LIST });
	    if (this.match(RIGHT_PAREN, true))
	        return n;
	    do {
	        n2 = this.AssignExpression();
	        if (n2.type === YIELD && !n2.parenthesized && this.peek() === COMMA)
	            this.fail("Yield expression must be parenthesized");
	        if (this.match(FOR)) {
	            n2 = this.GeneratorExpression(n2);
	            if (n.children.length > 1 || this.peek(true) === COMMA)
	                this.fail("Generator expression must be parenthesized");
	        }
	        n.push(n2);
	    } while (this.match(COMMA));
	    this.mustMatch(RIGHT_PAREN);

	    return n;
	}

	Pp.PrimaryExpression = function PrimaryExpression() {
	    var n, n2, tt = this.t.get(true);

	    switch (tt) {
	      case FUNCTION:
	        n = this.FunctionDefinition(false, EXPRESSED_FORM);
	        break;

	      case LEFT_BRACKET:
	        n = this.newNode({ type: ARRAY_INIT });
	        while ((tt = this.peek(true)) !== RIGHT_BRACKET) {
	            if (tt === COMMA) {
	                this.t.get();
	                n.push(null);
	                continue;
	            }
	            n.push(this.AssignExpression());
	            if (tt !== COMMA && !this.match(COMMA))
	                break;
	        }

	        // If we matched exactly one element and got a FOR, we have an
	        // array comprehension.
	        if (n.children.length === 1 && this.match(FOR)) {
	            n2 = this.newNode({ type: ARRAY_COMP,
	                                expression: n.children[0],
	                                tail: this.ComprehensionTail() });
	            n = n2;
	        }
	        this.mustMatch(RIGHT_BRACKET);
	        break;

	      case LEFT_CURLY:
	        var id, fd;
	        n = this.newNode({ type: OBJECT_INIT });

	        object_init:
	        if (!this.match(RIGHT_CURLY)) {
	            do {
	                tt = this.t.get();
	                if ((this.t.token.value === "get" || this.t.token.value === "set") &&
	                    this.peek() === IDENTIFIER) {
	                    n.push(this.FunctionDefinition(true, EXPRESSED_FORM));
	                } else {
	                    var comments = this.t.blockComments;
	                    switch (tt) {
	                      case IDENTIFIER: case NUMBER: case STRING:
	                        id = this.newNode({ type: IDENTIFIER });
	                        break;
	                      case RIGHT_CURLY:
	                        break object_init;
	                      default:
	                        if (this.t.token.value in keywords) {
	                            id = this.newNode({ type: IDENTIFIER });
	                            break;
	                        }
	                        this.fail("Invalid property name");
	                    }
	                    if (this.match(COLON)) {
	                        n2 = this.newNode({ type: PROPERTY_INIT });
	                        n2.push(id);
	                        n2.push(this.AssignExpression());
	                        n2.blockComments = comments;
	                        n.push(n2);
	                    } else {
	                        // Support, e.g., |var {x, y} = o| as destructuring shorthand
	                        // for |var {x: x, y: y} = o|, per proposed JS2/ES4 for JS1.8.
	                        if (this.peek() !== COMMA && this.peek() !== RIGHT_CURLY)
	                            this.fail("missing : after property");
	                        n.push(id);
	                    }
	                }
	            } while (this.match(COMMA));
	            this.mustMatch(RIGHT_CURLY);
	        }
	        break;

	      case LEFT_PAREN:
	        n = this.ParenExpression();
	        this.mustMatch(RIGHT_PAREN);
	        n.parenthesized = true;
	        break;

	      case LET:
	        n = this.LetBlock(false);
	        break;

	      case NULL: case THIS: case TRUE: case FALSE:
	      case IDENTIFIER: case NUMBER: case STRING: case REGEXP:
	        n = this.newNode();
	        break;

	      default:
	        this.fail("missing operand; found " + tokens[tt]);
	        break;
	    }

	    return n;
	}

	/*
	 * parse :: (source, filename, line number) -> node
	 */
	function parse(s, f, l) {
	    var t = new Tokenizer(s, f, l, options.allowHTMLComments);
	    var p = new Parser(t);
	    return p.Script(false, false, true);
	}

	/*
	 * parseFunction :: (source, boolean,
	 *                   DECLARED_FORM or EXPRESSED_FORM or STATEMENT_FORM,
	 *                   filename, line number)
	 *               -> node
	 */
	function parseFunction(s, requireName, form, f, l) {
	    var t = new Tokenizer(s, f, l);
	    var p = new Parser(t);
	    p.x = new StaticContext(null, null, false, false, false);
	    return p.FunctionDefinition(requireName, form);
	}

	/*
	 * parseStdin :: (source, {line number}, string, (string) -> boolean) -> program node
	 */
	function parseStdin(s, ln, prefix, isCommand) {
	    // the special .begin command is only recognized at the beginning
	    if (s.match(/^[\s]*\.begin[\s]*$/)) {
	        ++ln.value;
	        return parseMultiline(ln, prefix);
	    }

	    // commands at the beginning are treated as the entire input
	    if (isCommand(s.trim()))
	        s = "";

	    for (;;) {
	        try {
	            var t = new Tokenizer(s, "stdin", ln.value, false);
	            var p = new Parser(t);
	            var n = p.Script(false, false);
	            ln.value = t.lineno;
	            return n;
	        } catch (e) {
	            if (!p.unexpectedEOF)
	                throw e;

	            // commands in the middle are not treated as part of the input
	            var more;
	            do {
	                if (prefix)
	                    putstr(prefix);
	                more = readline();
	                if (!more)
	                    throw e;
	            } while (isCommand(more.trim()));

	            s += "\n" + more;
	        }
	    }
	}

	/*
	 * parseMultiline :: ({line number}, string | null) -> program node
	 */
	function parseMultiline(ln, prefix) {
	    var s = "";
	    for (;;) {
	        if (prefix)
	            putstr(prefix);
	        var more = readline();
	        if (more === null)
	            return null;
	        // the only command recognized in multiline mode is .end
	        if (more.match(/^[\s]*\.end[\s]*$/))
	            break;
	        s += "\n" + more;
	    }
	    var t = new Tokenizer(s, "stdin", ln.value, false);
	    var p = new Parser(t);
	    var n = p.Script(false, false);
	    ln.value = t.lineno;
	    return n;
	}

	function preprocess(ast)
	{
		var jsdef = GLOBAL.mos_jsdef;

		var SET_METADATA = function(node, metaname, metadata)
		{
			Object.defineProperty(node, metaname, {enumerable:false, writable:false, configurable:false, value:metadata});
		};

		var reduceProps = function(ast)
		{
			if(!ast) return;

			var _this = this;
			var out = [];

			switch (ast.type)
			{
				case jsdef.NEW:
				case jsdef.NEW_WITH_ARGS:
					out.push({ast:ast.children[0], value:ast.children[0].children[0].value});
					break;

				case jsdef.IDENTIFIER:
				case jsdef.TRUE:
				case jsdef.FALSE:
				case jsdef.NULL:
					out.push({ast:ast, value:ast.value});
					break;

				case jsdef.DOT:
				case jsdef.INDEX:
				case jsdef.GROUP:
				case jsdef.CALL:
					out = out.concat(reduceProps(ast.children[0]));
					break;

				case jsdef.THIS:
					out.push({ast:ast.children[0], value:"@@THIS@@"});
					break;

				case jsdef.SUPER:
					out.push({ast:ast.children[0], value:"@@SUPER@@"});
					break;

				default:
					break;
			}

			if (ast.type == jsdef.DOT)
				out.push({ast:ast.children[1], value:ast.children[1].value});

			else if (ast.type == jsdef.INDEX)
				out.push({ast:ast, value:"@@INDEX@@"} );

			return out;
		};

		var currFunction = null;
		var currClass = null;
		var currState = null;
		var currDot = [];
		var dic={};

	    // Descent the ast.
		function descend(node)
		{
			node.__visited=true;

			node.nodeName = GLOBAL.moz_narcissus.jsdefNames[node.type];

			switch(node.type)
			{
			case jsdef.FUNCTION:
				currFunction = node;
				node.returnPaths = [];
    			break;

    		case jsdef.INDEX:
			case jsdef.GROUP:
			case jsdef.CALL:
				currDot.push(node);
				break;

			case jsdef.DOT:
				// Pre-process DOT for speed.
				currDot.push(node);

				SET_METADATA(node, "identifiers_list", reduceProps(node));
				SET_METADATA(node, "identifier_first", node.identifiers_list[0].ast);
				SET_METADATA(node, "identifier_last", node.identifiers_list[node.identifiers_list.length-1].ast);

				var values = [];
				for(var i=0,L=node.identifiers_list.length;i<L;i++)	values.push(node.identifiers_list[i].value);
				node.value = values.join(".");
				for(var i=node.identifiers_list.length;i--;)
				{
					if(node.identifiers_list[i].value!="@@INDEX@@")
					{
						SET_METADATA(node, "identifier_last", node.identifiers_list[i].ast);
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
							SET_METADATA(node[item], "parent", node);
							nodes.push(node[item]);
						}
				}
			}
			nodes = null;

            // Enrich ast node with usefull data and delete its reference to tokenizer.
			node.nodeType = GLOBAL.moz_narcissus.jsdefNames[node.type];
			if(node.source) node.source = node.source();

			// Non-enumerable node metadata
			SET_METADATA(node, "inClass", currClass);
			SET_METADATA(node, "inState", currState);
			SET_METADATA(node, "inFunction", currFunction);
			SET_METADATA(node, "inDot", currDot.length>0 && currDot[currDot.length-1].type==jsdef.DOT ? currDot[currDot.length-1] : null);
			SET_METADATA(node, "inIndex", currDot.length>0 && currDot[currDot.length-1].type==jsdef.INDEX ? currDot[currDot.length-1] : null);
			SET_METADATA(node, "inGroup", currDot.length>0 && currDot[currDot.length-1].type==jsdef.GROUP ? currDot[currDot.length-1] : null);
			SET_METADATA(node, "inCall", currDot.length>0 && currDot[currDot.length-1].type==jsdef.CALL ? currDot[currDot.length-1] : null);

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

		descend(ast);
	}

	GLOBAL.moz_narcissus.parse = function(code, file)
	{
	    var t = new Tokenizer(code, file, 0);
	    var p = new Parser(t);
	    var n = p.Script(false, false);
	    preprocess(n);
	    return n;
	}

}

__init_moz_narcissus(this);
