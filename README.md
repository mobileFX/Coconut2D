![Coconut2D_CrossPlatformRuntime](.SDK/Documentation/Introduction/Coconut2D_CrossPlatformRuntime.jpg)

[<img src=".SDK/Documentation/Introduction/donate.png">](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LARX2LEJ4LM6Q)

1. The Coconut 2D Project idea
==============================

Coconut2D is a software project for creating HTML5, iOS, Android and PC games that your really design and code once, and play everywhere!

![Process](.SDK/Documentation/Introduction/Process.png)

This GitHub Repository contains the Open Source **Coconut2D SDK**, which is the Toolchain and Core Frameworks of Coconut2D project. Please note that this repository does not contain Coconut2D Studio IDE which is a commercial product (or at least will be when we manage to finish it :)

2. Coconut2D SDK Architecture
==============================

Coconut2D virtualizes the **HTML5 Canvas** and uses **Object Oriented JavaScript** as the single code-base language. Developers can write and debug their games in Object Oriented JavaScript against the virtual HTML5 Canvas using Coconut2D Studio IDE.

Once a games is ready for release, it can be compiled to **HTML5 and ECMA JavaScript** code, as well as **Native C++11** code for iOS, Android and x86 apps. We developed a state of the art open source compiler, that generates cross-browser ECMA JavaScript and portable C++11 code from Object Oriented JavaScript source code.

![Architecture](.SDK/Documentation/Introduction/Architecture.jpg)

2.1. Coconut2D Frameworks
-------------------------

We encapsulated all **Core Frameworks**, such as **Animations**, **2D Game Engine**, **User Interface**, **Networking**, etc. inside a **Common Runtime Layer (CRL)** also written in Object Oriented JavaScript.

| Framework	               | Description                                                              |
|--------------------------|--------------------------------------------------------------------------|
|org.coconut2d.sdk.anim    | Core Animations Framework, implements `Game Engine`.                     |
|org.coconut2d.sdk.ui      | User Interface Framework, implements Controls, Buttons, Forms, etc.      |
|org.coconut2d.sdk.game2d  | 2D Games Framework, implements Sprite, TiledLayer, Parallax Layers, etc. |
|org.coconut2d.sdk.html5   | HTML5 Emulation Framework (Window, Document, Elements, Events)           |
|org.coconut2d.sdk.webgl   | HTML5 WebGL Emulation Framework, implements WebGL Context.               |
|org.coconut2d.sdk.net     | Networking Framework (XMLHttp, Facebook, Twitter, etc.)                  |
|org.coconut2d.sdk.server  | node.js Server Side Framework, implements basic HTTP Server.             |
|org.coconut2d.sdk.tests   | General Purpose Testing Framework.                                       |                                                                                                  |
|org.emscripten.box2d      | Emscripten derived Box2D Physics Framework (compiled from C++)           |

2.2. Coconut2D Layering
-----------------------

![Layering](.SDK/Documentation/Introduction/Layering.jpg)

2.3. 2D Game Engine
-------------------

**Coconut2D Game Engine** is a **Finite State Machine Automaton** controlled by a new programming entity called **State**. States define a singularity in the execution context of Game Loop, they have explicit **enter** and **exit** points and they offer distinction between **tick** and **paint**.

To unify Native and HTML5 worlds under a single API while getting the best performance every time, we designed a set of **Native Device Wrappers** that virtualize the **HTML5 Canvas** across desktop, tablet, mobile and other devices.

3. Technologies
================

3.1. Renderering Engines
-------------------------

Coconut2D core rendering engine is OpenGL ES2 but we have implemented special renderers for WebGL, CanvasRenderingContext2D and CSS3 for supporting Mobile HTML5 Browsers.


3.2. Integrating with Emscripten
--------------------------------

Especially for HTML5, a game can also be compiled to C++ and post-compiled with **Emscripten** to JavaScript byte code. Compiled JavaScript can be up to x10 times faster than "regular" handwritten JavaScript and runs on all browsers.

Emscripten is a C++ to JavaScript compiler developed by Alon Zakai (Kripken). Coconut2D uses Emscripten both for binding 3rd party C++ libraries (such as Box2D Physics) with generated ECMA JavaScript code, and also for post-compiling and optimizing a game for HTML5 Browsers.

3.3. Compiling iOS Apps on Windows
----------------------------------

Coconut2D Studio IDE is capable of compiling C++11 code directly into a native iOS, Android and x86 applications. Especially for iOS apps, they are trully compiled on Windows, using a special port of the LLVM compiler developed by Pierre-Marie Baty; that is the same compiler Apple uses in XCode. iOS compilation process of Coconut2D Studio also code signs your apps with your official developer certificate.

3.4. Object Oriented JavaScript
-------------------------------

![CocoScript](.SDK/Documentation/Introduction/CocoScript.png)
-----

![CocoScriptCode](.SDK/Documentation/Introduction/CocoScriptCode.png)

Language Features:

* Real Classes as first-class citizens
* Constructor with constructor arguments and inline base class initialization
* Destructor (invoked on delete)
* Public, Private, Protected Access Modifiers
* Published Access Modififer for Design-Time binding
* Abstract Functions
* Static Functions and Fields
* Virtual Functions and base class access with super keyword
* Function Overloads
* Constants and Enums
* Properties (setter, getter)
* Events Registration and Notification System
* Interfaces and implements keyword
* Structs (with super fast instantiation)
* States (for Game Loop FSM)
* Class and Interface Inheritance Model
* Class Delegation Model
* Strong Type System
* Explicit Integer, Float, Time, String, Boolean and Date datatypes
* Stream and DataStream datatype
* Typed Arrays and Arrays of Objects
* Conditional Compilation and Compiler Directives (eg. #ifdef BOX_2D )
* Export of Debug Symbol Tables for real Debugging
* Export of Code Symbols for IntelliSyntax Editing
* Export of State Machine and Class Diagrams
* Compiles to ECMA JavaScript cross-browser code
* Compiles to C++11 Portable Code

```JavaScript


grammar CocoScript
<
	MATCHCASE,
	FILE_EXT_LIST=".jspp",
	REPARSE_PATTERN="\b(var|const)\s+.*?;"
>
{

	//----------------------------------------------------------------------
	// Compilation Unit
	//----------------------------------------------------------------------

	compilation_unit ::= [ { pragma_statement  } ]
						 [ module_statement ]
						 [ { code_unit } ];

	code_unit ::= include_statement
	            | type_declaration
	            | global_scope_if_directive
	            | variable_declaration
	            | const_declaration
	            | method_declaration;

	//----------------------------------------------------------------------
	// Whitespace & Comments
	//----------------------------------------------------------------------

	whitespace <WHITESPACE> ::= '[\s\n\r]+';
	comment <COMMENT> ::= '//+[^\n\r]*$';
	multiline_comment <MULTILINE_COMMENT> ::= '/+\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+/+';

	//----------------------------------------------------------------------
	// Pragma Statement
	//----------------------------------------------------------------------

	pragma_statement <TERMINAL,STATEMENT> ::= "#pragma" uncaptured_ident ";";

	//----------------------------------------------------------------------
	// Include Statement
	//----------------------------------------------------------------------

	include_statement <TERMINAL,STATEMENT> ::= "#include" STRING_LITERAL;

	//----------------------------------------------------------------------
	// Module Statement (for Node.js)
	//----------------------------------------------------------------------

	module_statement <MODULE,STATEMENT> 			::= "#module" module_name ";";
	module_name <TERMINAL, MODULE_NAME> ::= ident;

	//----------------------------------------------------------------------
	// Compiler Directives
	//----------------------------------------------------------------------

	global_scope_if_directive <STATEMENT,FRIENDLYNAME="#if directive"> ::=

	    "#if" "(" expression ")"
	        [ compilation_unit ]
	    [
	    "#else"
	        [ compilation_unit ]
	    ]
	    "#endif";

	//------------------------------------------------------------
	class_scope_if_directive <STATEMENT,FRIENDLYNAME="#if directive"> ::=

	    "#if" "(" expression ")"
	        [ class_field_declarations ]
	    [
	    "#else"
	        [ class_field_declarations ]
	    ]
	    "#endif";

	//------------------------------------------------------------
	scope_if_directive <STATEMENT,FRIENDLYNAME="#if directive"> ::=

	    "#if" "(" expression ")"
	        [ STATEMENT ]
	    [
	    "#else"
	        [ STATEMENT ]
	    ]
	    "#endif";

	//------------------------------------------------------------
	// Embedded Code (does not work with #pragma export_native)
	//------------------------------------------------------------

	embedded_javascript ::= '__javascript\s*\{\s*[\w\W]*?\s*\}\s*__end';
	embedded_cpp 		::= '__cpp\s*\{\s*[\w\W]*?\s*\}\s*__end';
	embedded_java		::= '__java\s*\{\s*[\w\W]*?\s*\}\s*__end';
	embedded_html		::= '__html\s*\{\s*[\w\W]*?\s*\}\s*__end';

	//============================================================================================================================
	//
	// Type Declarations
	//
	//============================================================================================================================

	type_declaration ::= ( 	  class_declaration
					   		| interface_declaration
					   		| struct_declaration
					   		| enum_declaration
					   		| callback_declaration
						 ) [";"] ;

	//----------------------------------------------------------------------
	// CLASS
	//----------------------------------------------------------------------

	class_declaration <CLASS,SCOPE,STATEMENT> ::= 	[ { class_modifier } ] "class" class_name
													[ COLON class_base ]
													[ "implements" { class_interface, ","} ]
													"{"
														[ class_field_declarations ]
													"}";

	class_modifier <TERMINAL,CLASS_MODIFIER> 	::= "control" | "emscripten" | "export" | "state" | "export";
	class_name <TERMINAL,CLASS_NAME> 			::= ident;
	class_base <TERMINAL,CLASS_BASE> 			::= qualified_name | typed_array | dictionary | ARRAY;
	class_interface <TERMINAL,CLASS_INTERFACE> 	::= qualified_name;

	class_field_declarations ::= { class_field_declaration };

	class_field_declaration ::=   constructor_declaration
							  	| destructon_declaration
  								| variable_declaration
  								| const_declaration
								| property_declaration
							  	| method_declaration
							  	| enum_declaration
							  	| event_declaration
							  	| state_declaration
							  	| struct_declaration
							  	| class_declaration
							  	| class_scope_if_directive
							  	| ";" ;

	constructor_declaration <STATEMENT,METHOD,CONSTRUCTOR> 	::= public_modifier "function" constructor_name
															    "(" [parameter_list] ")"
															    [ base_class_initializer ]
															    STATEMENTS;

	destructon_declaration <STATEMENT,METHOD,DESTRUCTOR> 	::= public_modifier "function" destructor_name "(" ")"
															    STATEMENTS;

	constructor_name <TERMINAL,METHOD_NAME>	::= "Constructor";
	destructor_name <TERMINAL,METHOD_NAME>	::= "Destructor";
	public_modifier <METHOD_MODIFIER> 		::= "public";
	base_class_initializer 					::= COLON ident "(" expression_list ")";

	//----------------------------------------------------------------------
	// EVENT
	//----------------------------------------------------------------------

	event_declaration <EVENT,SCOPE,STATEMENT> 	::= event_modifier "event" event_name "(" [ event_parameter_list ] ")";

	event_modifier <TERMINAL,EVENT_MODIFIER>	::= "public";
	event_name <TERMINAL,EVENT_NAME> 			::= ident;

	event_parameter_list						::= { event_parameter, ","} ;
	event_parameter <EVENT_ARG> 				::= event_param_name COLON event_param_type;
	event_param_type <TERMINAL,EVENT_ARG_TYPE>	::= type;
	event_param_name <TERMINAL,EVENT_ARG_NAME>	::= ident;

	//----------------------------------------------------------------------
	// STRUCT
	//----------------------------------------------------------------------

	struct_declaration <STRUCT,SCOPE,STATEMENT> ::=	 [ struct_modifier ] "struct" struct_name
													 "{"
													 	{ (struct_item | struct_union) }
													 "}";

	struct_modifier <TERMINAL,STRUCT_MODIFIER> 		::= "export";
	struct_name <TERMINAL,STRUCT_NAME> 				::= ident;

	struct_item <STRUCT_ITEM>						::= struct_item_name COLON struct_item_type ";";
	struct_item_name <TERMINAL,STRUCT_ITEM_NAME>	::= ident;
	struct_item_type <TERMINAL,STRUCT_ITEM_TYPE> 	::= type;

	struct_union 									::= "union" ident
														"{"
															{ (struct_item | struct_union) }
														"}" ";";

	//----------------------------------------------------------------------
	// ENUM
	//----------------------------------------------------------------------

	enum_declaration <ENUM,SCOPE,STATEMENT> ::=  [enum_modifier] "enum" enum_name
												 "{"
													{ enum_item,  "," }
												 "}";

	enum_modifier <TERMINAL,ENUM_MODIFIER> 		::= "export";
	enum_name <TERMINAL,ENUM_NAME> 				::= ident;

	enum_item <ENUM_ITEM>						::= enum_item_name "=" enum_item_value;
	enum_item_name <TERMINAL,ENUM_ITEM_NAME> 	::= ident;
	enum_item_value <TERMINAL,ENUM_ITEM_VALUE> 	::= [UNARY_OP] NUMERIC_LITERAL;

	//----------------------------------------------------------------------
	// STATE
	//----------------------------------------------------------------------

	state_declaration <STATE,SCOPE,STATEMENT> ::=	state_modifier "state" state_name
													"{"
														{ state_field_declarations }
													"}";

	state_field_declarations ::=  variable_declaration | const_declaration | state_method_declaration;

	state_method_declaration <METHOD,STATE_METHOD,SCOPE,STATEMENT> ::=	"function" state_method_name
																		"(" [parameter_list] ")"
																		[ STATEMENTS ];

	state_method_name <TERMINAL,METHOD_NAME> 	::= "enter" | "exit" | "tick" | "paint";


	state_modifier <TERMINAL,STATE_MODIFIER> 	::= access_modifiers;
	state_name <TERMINAL,STATE_NAME> 			::= ident;

	//----------------------------------------------------------------------
	// INTERFACE
	//----------------------------------------------------------------------

	interface_declaration <INTERFACE,SCOPE,STATEMENT> ::= 	"interface" interface_name
															[ COLON { interface_base, ","} ]
															"{"
																[ interface_field_declarations ]
															"}" ;

	interface_field_declarations ::=  { interface_field_declaration };

	interface_field_declaration   ::= variable_declaration
									| const_declaration
									| method_declaration
									| ";";

	interface_name <TERMINAL,INTERFACE_NAME> 	::= ident;
	interface_base <TERMINAL,INTERFACE_BASE> 	::= qualified_name;

	//----------------------------------------------------------------------
	// FUNCTION
	//----------------------------------------------------------------------

	method_declaration <METHOD,SCOPE,STATEMENT> 		::=	[{ method_modifier }] "function" method_name
															"(" [parameter_list] ")"
															[ COLON method_type ]
															[ STATEMENTS ];

	method_modifier <TERMINAL,METHOD_MODIFIER> 			::= "public" | "private" | "protected" | "static" | "abstract" | "virtual";
	method_name <TERMINAL,METHOD_NAME> 					::= ident;
	method_type <TERMINAL,METHOD_TYPE> 					::= type;

	parameter_list 										::= { parameter, ","} ;
	parameter <METHOD_ARG> 								::= optional_parameter | required_parameter | rest_arguments;
	required_parameter									::= param_name COLON param_type;
	optional_parameter									::= "optional" required_parameter [ "=" expression ];
	param_type <TERMINAL,METHOD_ARG_TYPE> 				::= type;
	param_name <TERMINAL,METHOD_ARG_NAME> 				::= ident;
	rest_arguments 										::= "..." [COLON scalar_type];

	//----------------------------------------------------------------------
	// CALLBACK
	//----------------------------------------------------------------------

	callback_declaration <CALLBACK,STATEMENT> 			::= "callback" callback_name "(" [callback_parameter_list] ")";

	callback_name <TERMINAL,CALLBACK_NAME>				::= ident;
	callback_parameter_list								::= { callback_parameter, ","} ;
	callback_parameter <CALLBACK_ARG> 					::= callback_param_name COLON callback_param_type;
	callback_param_name <TERMINAL,CALLBACK_ARG_NAME> 	::= ident;
	callback_param_type <TERMINAL,CALLBACK_ARG_TYPE> 	::= type;

	//----------------------------------------------------------------------
	// VAR
	//----------------------------------------------------------------------

	variable_declaration <STATEMENT,VAR> 				::= [{ var_modifier }] "var" variable_declarators ";";
	const_declaration <STATEMENT,VAR,CONST>				::= [{ var_modifier }] "const" variable_declarators ";";

	variable_declarators 								::= { variable_declarator, var_separator } ;
	variable_declarator 								::= var_name COLON var_type [ "=" var_init ];

	var_modifier <VAR_MODIFIER>							::= "static" | "public" | "private" | "protected" | "published" | "reference" | "delegate" | "optional";
	var_type <TERMINAL,VAR_TYPE>						::= type;
	var_name <VAR_NAME> 								::= ident;
	var_init <VAR_INITIALIZER>							::= expression;
	var_separator<VAR_NEXT>								::= ",";

	context_var <VAR>									::= var_name COLON var_type;

	//----------------------------------------------------------------------
	// PROPERTY
	//----------------------------------------------------------------------

	property_declaration <STATEMENT,SCOPE,PROPERTY> ::= { property_modifier } "property" property_name
														"{"
															property_getter
															[ property_setter ]
														"}";

	property_modifier <PROPERTY_MODIFIER>			::= "static" | "public" | "private" | "protected" | "published";
	property_name <PROPERTY_NAME>					::= ident;

	property_getter <METHOD,PROPERTY_GETTER>		::= "function" "get" "(" ")" COLON method_type STATEMENTS;
	property_setter <METHOD,PROPERTY_SETTER>		::= "function" "set" "(" parameter_list ")" STATEMENTS;

	//----------------------------------------------------------------------
	// (type declaration related productions)
	//----------------------------------------------------------------------

	access_modifiers	::= "public" | "private" | "protected";

	//============================================================================================================================
	//
	// Statements
	//
	//============================================================================================================================

	STATEMENTS ::= EMPTY_BLOCK | STATEMENTS_BLOCK;

	EMPTY_BLOCK					::= "{" "}";
	STATEMENTS_BLOCK<SCOPE> 	::= "{" { STATEMENT } "}";

	STATEMENT ::= STATEMENTS
	            | break
	            | continue
	            | delete
	            | do
	            | for
	            | for_in
	            | if_else
	            | return
	            | switch
	            | while
	            | try
	            | throw
	            | label
	            | variable_declaration
	            | const_declaration
	            | EXPRESSION
	            | scope_if_directive
	            | embedded_javascript
	            | embedded_java
	            | embedded_cpp
	            | embedded_html
	            ;

	//------------------------------------------------------------
	EXPRESSION <STATEMENT,ERROR="Invalid Expression"> ::= expression ";";

	//------------------------------------------------------------
	try <STATEMENT,SCOPE,FRIENDLYNAME="try statement"> ::=
	    "try"
	        STATEMENT
	    [ catch ]
	    [ finally ];

	catch <SCOPE> ::=
	    "catch" "(" context_var ")"
	    STATEMENT;

	finally <SCOPE> ::=
	    "finally"
	    STATEMENT;

	//------------------------------------------------------------
	throw <STATEMENT,FRIENDLYNAME="throw statement"> ::=
	    "throw" expression ";";

	//------------------------------------------------------------
	break <STATEMENT, FRIENDLYNAME="break statement"> ::=
	    "break" [ident] ";";

	//------------------------------------------------------------
	continue <STATEMENT, FRIENDLYNAME="continue statement"> ::=
	    "continue" [ident] ";";

	//------------------------------------------------------------
	delete <STATEMENT, FRIENDLYNAME="delete statement"> ::=
	    "delete" ["[" "]"] reference_expr ";";

	//------------------------------------------------------------
	for <STATEMENT, FRIENDLYNAME="for statement">	::=
	    "for" "(" [for_init] ";" [expression] ";" [expression_list] ")"
			STATEMENT;

	for_init ::= for_var | expression_list;

	for_var <STATEMENT,VAR> ::= "var" variable_declarators;

	//------------------------------------------------------------
	for_in <STATEMENT, SCOPE, FRIENDLYNAME="for in statement"> ::=
	    "for" "(" for_var "in" expression ")"
	    	STATEMENT;

	//------------------------------------------------------------
	if_else <STATEMENT, FRIENDLYNAME="if statement"> ::=
	    "if" "(" expression ")"
	        STATEMENT
	    [
	     "else"
	        STATEMENT
	    ];

	//------------------------------------------------------------
	label <STATEMENT, FRIENDLYNAME="label statement"> ::=
	    ident COLON STATEMENT ;

	//------------------------------------------------------------
	return <STATEMENT, FRIENDLYNAME="return statement"> ::=
	    "return" [expression] ";";

	//------------------------------------------------------------
	switch <STATEMENT, FRIENDLYNAME="switch statement"> ::=
	    "switch" "(" expression ")"
	    "{"
	        [{ case }]
	        [default]
	    "}";

	case <STATEMENT,SCOPE> ::=
	    "case" expression COLON
	        [ { STATEMENT } ];

	default <STATEMENT,SCOPE> ::=
	    "default" COLON
	        [ { STATEMENT } ];

	//------------------------------------------------------------
	do <STATEMENT, FRIENDLYNAME="do-while loop statement"> ::=
	    "do"
	        STATEMENT
	    "while" "(" expression ")" ";";

	//------------------------------------------------------------
	while <STATEMENT, FRIENDLYNAME="while loop statement"> ::=
	    "while" "(" expression ")"
	        [ STATEMENT ] [";"];

	//============================================================================================================================
	//
	// Expressions
	//
	//============================================================================================================================

	//----------------------------------------------------------------------
	// Operators (avoiding op precedence for speed)
	//----------------------------------------------------------------------

	OPERATOR <OPERATOR> ::= "="    | "*="  | "/="  | "%="
		                  | "+="   | "-="  | "<<=" | ">>="
		                  | ">>>=" | "&="  | "^="  | "|="
		                  | "||"   | "&&"  | "|"   | "^"
		                  | "&"    | "=="  | "!="  | "<"
		                  | ">"    | ">="  | "<="  | "==="
		                  | "!=="  | ">>>" | ">>"  | "<<"
		                  | "+"    | "-"   | "/"   | "*"
		                  | "%"    | "~"   | "instanceof"
		                  ;

	UNARY_OP  <OPERATOR> ::= "-" | "~" | "+";
	PREFIX_OP <OPERATOR> ::= "++" | "--" | "typeof";

	//----------------------------------------------------------------------
	// Expressions
	//----------------------------------------------------------------------

	expression <SHOWDELIMITERS> ::= { ternary_expr, OPERATOR };

	ternary_expr ::= { factor_expr, "." }
					 [ "?" expression COLON expression ]
					 [ ( "(" [expression_list] ")" ) ];

	factor_expr ::=	  ( TRUE | FALSE | UNDEFINED | NULL )
					| ( "!" expression )
					| ( "(" expression ")" )
					| ( UNARY_OP expression )
					| ( new_array_expr )
					| new_expr
					| ( STRING_LITERAL | NUMERIC_LITERAL )
					| ( [ PREFIX_OP ] reference_expr [ PREFIX_OP ] )
					| ( [ PREFIX_OP ] "(" reference_expr ")" [ PREFIX_OP ] )
					| JSON
					;

	new_expr 						::= "new" (typed_array | dictionary | expression);
	new_array_expr 					::= "[" [ expression_list ] "]";
	expression_list 				::= { expression, ","};

	// reference term must not begin with keyword but may end with keyword (eg. a.default)
	reference_expr <DOT>      		::= { reference_term, "." };
	reference_term 					::= ident [ { ( subscript_expr ) | ( call_expr ) } ];

	call_expr <CALL>				::= "(" [ expression_list ] ")";
	subscript_expr <SUBSCRIPT>		::= "[" expression "]";

	//============================================================================================================================
	// JSON (Allowed only with #pragma json)
	//============================================================================================================================

	JSON ::= [ JSON_OBJECT ];
	JSON_OBJECT ::= "{" [ { JSON_MEMBER, "," } ] "}";
	JSON_ARRAY ::= "[" { JSON_VALUE, "," } "]";
	JSON_MEMBER ::= STRING_LITERAL COLON JSON_VALUE;
	JSON_VALUE ::= FALSE | TRUE | NULL | JSON_OBJECT | JSON_ARRAY | NUMERIC_LITERAL | STRING_LITERAL | expression;

	//============================================================================================================================
	//
	// Terminals
	//
	//============================================================================================================================

	ident 				<TERMINAL, IDENTIFIER> 	::= ^keyword identifier;
	uncaptured_ident 	<TERMINAL> 				::= ^keyword identifier;

	type 				<TERMINAL> 				::= typed_array | dictionary | ident;

	typed_array 		<TERMINAL> 				::= ARRAY "<" uncaptured_ident ">";
	dictionary 			<TERMINAL> 				::= DICTIONARY "<" uncaptured_ident "," uncaptured_ident ">";
	qualified_name 		<TERMINAL> 				::= ^ARRAY ^DICTIONARY { ident, "." };

	//============================================================================================================================
	//
	// Literals
	//
	//============================================================================================================================

	NUMERIC_LITERAL <TERMINAL> 			::= '(?:0[xX][0-9a-fA-F]+)|(?:\d+(?:\.\d+){0,1}[fd]{0,1})';
	STRING_LITERAL 	<TERMINAL,STRING> 	::= '\x22(?!\x22)(?:\\.|[^\x22])*\x22|\x27(?!\x27)(?:\\.|[^\x27])*\x27|([\x27\x22]{3})((?:(?!\1)[\s\S])*)\1|\x22\x22|\x27\x27';
	identifier 							::= '[a-zA-Z_\$][a-zA-Z0-9_\$]*';

	GLOBAL 		<TERMINAL, CLASS_GLOBAL>			::= "Global";			// The name of the Global Scope or Global Class
	VOID 		<TERMINAL, CLASS_VOID>				::= "void";				// The name of the void VarType
	EVENT_BASE 	<TERMINAL, CLASS_EVENT_BASE>		::= "CocoEvent";		// The name of Events base Class

	ARRAY 		<TERMINAL, CLASS_ARRAY> 			::= "Array";			// The name of the typed array / vector Class Template
	DICTIONARY 	<TERMINAL, CLASS_DICTIONARY>		::= "Dictionary";		// The name of the typed dictionary / map Class Template

	THIS 		<TERMINAL, IDENTIFIER_THIS>			::= "this";				// The "this" identifier
	SUPER 		<TERMINAL, IDENTIFIER_SUPER>		::= "super";			// The "supper" identifier
	UNDEFINED 	<TERMINAL, IDENTIFIER_VOID>			::= "undefined";		// The "undefined" identifier
	NULL 		<TERMINAL, IDENTIFIER_NULL>			::= "null";				// The "null" identifier
	TRUE 		<TERMINAL, IDENTIFIER_TRUE>			::= "true";				// The "true" identifier
	FALSE 		<TERMINAL, IDENTIFIER_FALSE>		::= "false";			// The "false" identifier

	COMMIT_REPARSE	<COMMIT_STATEMENT>				::= ";";				// The commit statement punctuation
	COLON 			<MEMBERLIST_VARTYPES>			::= ":";				// The list vartypes punctuation

	//============================================================================================================================
	//
	// VarTypes
	//
	//============================================================================================================================

	// Scalars

	scalar_type <SCALARS> ::= "Boolean"
							| "Color"
							| "Date"
							| "Float"
							| "Integer"
							| "Number"
							| "String"
							| "Time"
							;

	// Classes (internally defined)

	vartypes <VARTYPES>	::=   "Array"
							| "Dictionary"

							| "Boolean"
							| "Date"
							| "String"

							| "Number"
							| "Float"
							| "Integer"
							| "Color"
							| "Time"


							| "Class"
							| "Object"
							| "Function"
							| "Null"

							| "Global"
							| "RegExp"
							| "CocoAction"
							| "DataView"
							| "Gradient"
							| "Math"

							| "Error"
							| "EvalError"
							| "TypeError"
							| "SyntaxError"
							| "RangeError"
							| "ReferenceError"

							| "ArrayBuffer"
							| "ArrayBufferView"

							| "Float32Array"
							| "Float64Array"

							| "Uint8Array"
							| "Uint16Array"
							| "Uint32Array"
							| "Uint64Array"

							| "Int8Array"
							| "Int16Array"
							| "Int32Array"
							| "Int64Array"
							;

	// VarTypes with SubTypes

	FLOAT	<SUBTYPE, VARTYPE="Float">		::= "ArrayBuffer" | "ArrayBufferView" | "Float32Array" | "Float64Array";
	INTEGER	<SUBTYPE, VARTYPE="Integer">	::= "Int8Array" | "Int16Array" | "Int32Array" | "Int64Array" | "Uint8Array" | "Uint16Array" | "Uint32Array" | "Uint64Array";

	//============================================================================================================================
	//
	// Keywords
	//
	//============================================================================================================================

	keyword <KEYWORDS> ::= 	  "abstract"
							| "break"
							| "callback"
							| "case"
							| "catch"
							| "class"
							| "compiler_break"
							| "const"
							| "continue"
							| "control"
							| "debugger"
							| "default"
							| "delegate"
							| "delete"
							| "do"
							| "else"
							| "emscripten"
							| "enum"
							| "event"
							| "export"
							| "finally"
							| "for"
							| "function"
							| "if"
							| "implements"
							| "import"
							| "in"
							| "inline"
							| "instanceof"
							| "interface"
							| "let"
							| "namespace"
							| "new"
							| "optional"
							| "private"
							| "property"
							| "protected"
							| "public"
							| "published"
							| "reference"
							| "return"
							| "state"
							| "static"
							| "struct"
							| "switch"
							| "thread"
							| "throw"
							| "try"
							| "typeof"
							| "union"
							| "use"
							| "var"
							| "virtual"
							| "void"
							| "volatile"
							| "while"
							| "with"
							;

};

```

We also developed **CocoPlayer**, a Simulator powered by **Google V8 JavaScript VM Engine** where developers can test, debug and profile their games and apps. CocoPlayer is capable of simulating various screen resolutions taking into account the different dpi of numerous iOS and Android devices. The full-fledged Object Oriented JavaScript Debugger is one of Coconut2D Studio's unique features!

4. Work in Progress
====================
![WIP](.SDK/Documentation/Introduction/WIP.png)

5. Sample Games
================

![Sample](.SDK/Documentation/Introduction/Game1.png)

![Sample](.SDK/Documentation/Introduction/Game2.png)

![Sample](.SDK/Documentation/Introduction/Game3.png)

![Sample](.SDK/Documentation/Introduction/Game4.png)

6. Credits
===========

6.1. Authors
------------

* Elias G. Politakis (epolitakis@mobilefx.com)
* George Mathioudakis (YiamiYo@mobilefx.com)

6.2. Coconut2D Team
-------------------

![CocoTeam](.SDK/Documentation/Introduction/CocoTeam1.jpg)

![CocoTeam](.SDK/Documentation/Introduction/CocoTeam2.png)

* Lina Kalostipi (Coconut2D Commercial Product Manager)
* Elias G. Politakis (Architect)
* George Mathioudakis (Lead Developer)
* Irida Kalostipi (Sample Games Programmer)
* Despina Leonti (Illustrator - Sample Games Designer)
* Sakis Garnelis (Animator - Concept Designer)

6.3. Coconut2D Video
--------------------

[![Coconut2D Technology](.SDK/Documentation/Introduction/Designer_1920x960.png)](https://www.youtube.com/watch?v=6WGuwU_KDBQ&list=UUsdcgU-EYQA8b-dbjJdqTgA)

6.4. Coconut2D on Social Media
------------------------------

[![facebook](.SDK/Documentation/Introduction/facebook.png)](https://www.facebook.com/pages/mobileFX/106630919428634)

[![twitter](.SDK/Documentation/Introduction/twitter.png)](https://twitter.com/mobilefx)

6.5. Contribute / Donate
------------------------

If this project is useful for you, you can help us sustain it either by contributing or by donating with Paypal.

[<img src=".SDK/Documentation/Introduction/donate.png">](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=LARX2LEJ4LM6Q)



[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/mobileFX/coconut2d/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

