// Cross-engine port of the SpiderMonkey Narcissus parser.
//  * Original: http://mxr.mozilla.org/mozilla/source/js/narcissus/ as of 2010-02-09
//  * Modifications: Copyright (c) 2010 Guillaume Lathoud, MIT License.
//    See ./CHANGELOG.TXT for a summary of the changes.
//
//  * Supported Environments:
//    Google V8 Engine, Firefox 3.6, Safari 4, Google Chrome 4
//
//  * Not supported yet:
//    Opera 10.10

/* ***** BEGIN LICENSE BLOCK *****
  * Version: MPL 1.1/GPL 2.0/LGPL 2.1
  *
  * The contents of this file are subject to the Mozilla Public License Version
  * 1.1 (the "License"); you may not use this file except in compliance with
  * the License. You may obtain a copy of the License at
  * http://www.mozilla.org/MPL/
  *
  * Software distributed under the License is distributed on an "AS IS" basis,
  * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
  * for the specific language governing rights and limitations under the
  * License.
  *
  * The Original Code is the Narcissus JavaScript engine.
  *
  * The Initial Developer of the Original Code is
  * Brendan Eich <brendan@mozilla.org>.
  * Portions created by the Initial Developer are Copyright (C) 2004
  * the Initial Developer. All Rights Reserved.
  *
  * Contributor(s):
  *
  * Alternatively, the contents of this file may be used under the terms of
  * either the GNU General Public License Version 2 or later (the "GPL"), or
  * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
  * in which case the provisions of the GPL or the LGPL are applicable instead
  * of those above. If you wish to allow use of your version of this file only
  * under the terms of either the GPL or the LGPL, and not to allow others to
  * use your version of this file under the terms of the MPL, indicate your
  * decision by deleting the provisions above and replace them with the notice
  * and other provisions required by the GPL or the LGPL. If you do not delete
  * the provisions above, a recipient may use your version of this file under
  * the terms of any one of the MPL, the GPL or the LGPL.
  *
  * ***** END LICENSE BLOCK ***** */

/*
  * Narcissus - JS implemented in JS.
  *
  * Well-known constants and lookup tables.  Many consts are generated from the
  * tokens table via eval to minimize redundancy, so consumers must be compiled
  * separately to take advantage of the simple switch-case constant propagation
  * done by SpiderMonkey.
  */ 
  
(function (GLOBAL) {

    GLOBAL.narcissus = GLOBAL.narcissus || {};

    var jsdef = GLOBAL.narcissus.jsdef = {};

    var tokens = jsdef.tokens = [
        // End of source.
        "END",

        // Operators and punctuators.  Some pair-wise order matters, e.g. (+, -)
        // and (UNARY_PLUS, UNARY_MINUS).
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
        "SCRIPT", "BLOCK", "LABEL", "FOR_IN", "CALL", "NEW_WITH_ARGS", "INDEX",
        "ARRAY_INIT", "OBJECT_INIT", "PROPERTY_INIT", "GETTER", "SETTER",
        "GROUP", "LIST", "FOR_INSIDE", "ARRAY_COMP",

        // Terminals.
        "IDENTIFIER", "NUMBER", "STRING", "REGEXP",

        // Keywords.
        "break",
        "class", "property","interface","abstract","virtual",       
        "case", "catch", "const", "continue",
        "debugger", "default", "delete", "do",
        "else", "enum", "export", "extends", "extension",
        "false", "finally", "for", "function",
        "if", "import", "in", "inside", "instanceof", "is",
        "namespace", "new", "null",
        "private", "protected", "public",
        "return",
        "static", "super", "switch",
        "this", "throw", "true", "try", "typeof", "#typesys",
        "var", "void", "as", "let",
        "while", "with"
    ];

    // Operator and punctuator mapping from token to tree node type name.
    // NB: superstring tokens (e.g., ++) must come before their substring token
    // counterparts (+ in the example), so that the opRegExp regular expression
    // synthesized from this list makes the longest possible match.
    var opTypeNamesArr = jsdef.opTypeNamesArr = [
        [   '\n',   "NEWLINE"],
        [   ';',    "SEMICOLON"],
        [   ',',    "COMMA"],
        [   '...',  "RANGE"],
        [   '?',    "HOOK"],
        [   ':',    "COLON"],
        [   '||',   "OR"],
        [   '&&',   "AND"],
        [   '|',    "BITWISE_OR"],
        [   '^',    "BITWISE_XOR"],
        [   '&',    "BITWISE_AND"],
        [   '===',  "STRICT_EQ"],
        [   '==',   "EQ"],
        [   '=',    "ASSIGN"],
        [   '!==',  "STRICT_NE"],
        [   '!=',   "NE"],
        [   '<<',   "LSH"],
        [   '<=',   "LE"],
        [   '<',    "LT"],
        [   '>>>',  "URSH"],
        [   '>>',   "RSH"],
        [   '>=',   "GE"],
        [   '>',    "GT"],
        [   '++',   "INCREMENT"],
        [   '--',   "DECREMENT"],
        [   '**',   "EXPONENT"],
        [   '+',    "PLUS"],
        [   '-',    "MINUS"],
        [   '*',    "MUL"],
        [   '/',    "DIV"],
        [   '%',    "MOD"],
        [   '!',    "NOT"],
        [   '~',    "BITWISE_NOT"],
        [   '.',    "DOT"],
        [   '[',    "LEFT_BRACKET"],
        [   ']',    "RIGHT_BRACKET"],
        [   '{',    "LEFT_CURLY"],
        [   '}',    "RIGHT_CURLY"],
        [   '(',    "LEFT_PAREN"],
        [   ')',    "RIGHT_PAREN"],
        ['#typesys',"TYPESYS"]
    ];

    var opTypeNames = jsdef.opTypeNames = (function () {
        var ret = {}, x;
        for (var i = 0; i < opTypeNamesArr.length; i++){
            x = opTypeNamesArr[i];
            ret[x[0]] = x[1];            
        }
        return ret;
    })();


    // Define const END, etc., based on the token names.  Also map name to index.

    var keywords = jsdef.keywords = (function () {

        // Hash of keyword identifier to tokens index.  NB: we must null __proto__ to
        // avoid toString, etc. namespace pollution.
        //  var _keywords = {__proto__: null};

        // G. Lathoud's addition: This works however only on SpiderMonkey and the like,
        // so let's resort to a more basic approach with hasOwnProperty (see further below).
        // (this helps on Rhino 1.6).

        var _keywords = {};
        
        GLOBAL.narcissus.jsdefNames={};

        for (var i = 0, j = tokens.length; i < j; i++) {


            var a_const;

            var t = tokens[i];
            if (/^[a-z]/.test(t)) {
                a_const = t.toUpperCase();
                _keywords[t] = i;
            } else {
                a_const = (/^\W/.test(t) ? opTypeNames[t] : t);
            }

            jsdef[a_const] = i >> 0;

            tokens[t] = i; 
            
            GLOBAL.narcissus.jsdefNames[i] = a_const;
            
            //trace("// jsdef." + a_const + " = " + i);
        }

        return function (/*string*/id) {
            return _keywords.hasOwnProperty(id) && _keywords[id];
        };
    })();

    // Map assignment operators to their indexes in the tokens array.
    var assignOps = jsdef.assignOps = ['|', '^', '&', '<<', '>>', '>>>', '+', '-', '*', '/', '%', '&&', '||', '**', '?'];

    for (var i = 0, j = assignOps.length; i < j; i++) {
        var t = assignOps[i];
        assignOps[t] = tokens[t];
    }
})(this);

// jsdef.END = 0
// jsdef.NEWLINE = 1
// jsdef.SEMICOLON = 2
// jsdef.RANGE = 3
// jsdef.COMMA = 4
// jsdef.ASSIGN = 5
// jsdef.HOOK = 6
// jsdef.COLON = 7
// jsdef.CONDITIONAL = 8
// jsdef.OR = 9
// jsdef.AND = 10
// jsdef.BITWISE_OR = 11
// jsdef.BITWISE_XOR = 12
// jsdef.BITWISE_AND = 13
// jsdef.EQ = 14
// jsdef.NE = 15
// jsdef.STRICT_EQ = 16
// jsdef.STRICT_NE = 17
// jsdef.LT = 18
// jsdef.LE = 19
// jsdef.GE = 20
// jsdef.GT = 21
// jsdef.LSH = 22
// jsdef.RSH = 23
// jsdef.URSH = 24
// jsdef.PLUS = 25
// jsdef.MINUS = 26
// jsdef.MUL = 27
// jsdef.DIV = 28
// jsdef.MOD = 29
// jsdef.NOT = 30
// jsdef.BITWISE_NOT = 31
// jsdef.UNARY_PLUS = 32
// jsdef.UNARY_MINUS = 33
// jsdef.UNARY_EXISTS = 34
// jsdef.INCREMENT = 35
// jsdef.DECREMENT = 36
// jsdef.DOT = 37
// jsdef.LEFT_BRACKET = 38
// jsdef.RIGHT_BRACKET = 39
// jsdef.LEFT_CURLY = 40
// jsdef.RIGHT_CURLY = 41
// jsdef.LEFT_PAREN = 42
// jsdef.RIGHT_PAREN = 43
// jsdef.EXPONENT = 44
// jsdef.SCRIPT = 45
// jsdef.BLOCK = 46
// jsdef.LABEL = 47
// jsdef.FOR_IN = 48
// jsdef.CALL = 49
// jsdef.NEW_WITH_ARGS = 50
// jsdef.INDEX = 51
// jsdef.ARRAY_INIT = 52
// jsdef.OBJECT_INIT = 53
// jsdef.PROPERTY_INIT = 54
// jsdef.GETTER = 55
// jsdef.SETTER = 56
// jsdef.GROUP = 57
// jsdef.LIST = 58
// jsdef.FOR_INSIDE = 59
// jsdef.ARRAY_COMP = 60
// jsdef.IDENTIFIER = 61
// jsdef.NUMBER = 62
// jsdef.STRING = 63
// jsdef.REGEXP = 64
// jsdef.BREAK = 65
// jsdef.CLASS = 66
// jsdef.PROPERTY = 67
// jsdef.INTERFACE = 68
// jsdef.ABSTRACT = 69
// jsdef.VIRTUAL = 70
// jsdef.CASE = 71
// jsdef.CATCH = 72
// jsdef.CONST = 73
// jsdef.CONTINUE = 74
// jsdef.DEBUGGER = 75
// jsdef.DEFAULT = 76
// jsdef.DELETE = 77
// jsdef.DO = 78
// jsdef.ELSE = 79
// jsdef.ENUM = 80
// jsdef.EXPORT = 81
// jsdef.EXTENDS = 82
// jsdef.EXTENSION = 83
// jsdef.FALSE = 84
// jsdef.FINALLY = 85
// jsdef.FOR = 86
// jsdef.FUNCTION = 87
// jsdef.IF = 88
// jsdef.IMPORT = 89
// jsdef.IN = 90
// jsdef.INSIDE = 91
// jsdef.INSTANCEOF = 92
// jsdef.IS = 93
// jsdef.NAMESPACE = 94
// jsdef.NEW = 95
// jsdef.NULL = 96
// jsdef.PRIVATE = 97
// jsdef.PROTECTED = 98
// jsdef.PUBLIC = 99
// jsdef.RETURN = 100
// jsdef.STATIC = 101
// jsdef.SUPER = 102
// jsdef.SWITCH = 103
// jsdef.THIS = 104
// jsdef.THROW = 105
// jsdef.TRUE = 106
// jsdef.TRY = 107
// jsdef.TYPEOF = 108
// jsdef.TYPESYS = 109
// jsdef.VAR = 110
// jsdef.VOID = 111
// jsdef.AS = 112
// jsdef.LET = 113
// jsdef.WHILE = 114
// jsdef.WITH = 115
  






