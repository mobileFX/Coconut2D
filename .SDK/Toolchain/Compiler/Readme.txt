
	======================================================================
	A1. Defining a class and inheritance in plain JavaScript
	======================================================================

	The basic idea (as derived from Roger Poon's JavaScript++) is to have an outer JavaScript function
	returning an inner function that represents the Class. The reason we use the outer/inner functions
	is because we need to run special code that will actually prepare the object instance (eg. virtual
	functions) and this cannot be done by prototype alone. When calling the outer function with the
	"new" operator the result is an instnace of the inner function.	To implement inheritance we use the
	good old prototypes, as demonstrated below. Our compiler's work is to construct the inner and outer
	functions based on the AST class definition and to properly apply inheritance. Using the prototype
	ensures that each new class instance will start with an EXACT copy of the base class. The compiler
	applies minimal post-processing for inheritance-related things that are missing from the prototype
	mechanics such as virtual functions, overloaded methods, etc.

	But let's start with the basics. Copy-paste this code in Chrome or any other JavaScript testing
	tool and examine/run it to understand the principles of JavaScript inheritance:

	function Class1()
	{
		function Class1(base)
		{
			this.x = 1;
			return this;
		}
		var base = new Class2;
		Class1.prototype = base;
		return new Class1(base);
	}

	function Class2()
	{
		function Class2(base)
		{
			this.y = 2;
			return this;
		}
		var base = new Class3;
		Class2.prototype = base;
		return new Class2(base);
	}

	function Class3()
	{
		function Class3(base)
		{
			this.z = 3;
			return this;
		}
		return new Class3(null);
	}

	var o1 = new Class1;
	console.log(o1.x + ", " + o1.y + ", " + o1.z);
	o1.x=100; o1.y=200; o1.z=300;
	console.log(o1.x + ", " + o1.y + ", " + o1.z);

	var o2 = new Class1;
	console.log(o2.x + ", " + o2.y + ", " + o2.z);
	console.log(o1.x + ", " + o1.y + ", " + o1.z);

	var o3 = new Class2;
	console.log(o3.x + ", " + o3.y + ", " + o3.z);

	======================================================================
	A2. Public / Private / Protected Members
	======================================================================

	To implement public/private/ protected modifiers we define on the inner function the public members
	using "this.<member> = <implementation> and we use two "bank" objects __PRIVATE__ and __PROTECTED__
	for the rest. The principle is the following:

	function ClassOuter()
	{
		function ClassInner()
		{
			this.__PRIVATE__ = {};
			this.__PROTECTED__ = {};

			this.foo = function() {...}; 					// Public Method
			this.__PRIVATE__.goo = function() {...};		// Private Method
			this.__PROTECTED__.zoo = function() {...};		// Protected Method

			return this;
		}
	}

	======================================================================
	A3. Static Members
	======================================================================

	Static members are defined directly on the Outer class function:

	function ClassOuter()
	{
		function ClassInner()
		{
			return this;
		}
	}
	ClassOuter.__PRIVATE__ = {};
	ClassOuter.__PROTECTED__ = {};
	ClassOuter.foo = function() {...}; 					// Public Static Method
	ClassOuter.__PRIVATE__.goo = function() {...};		// Private Static Method
	ClassOuter.__PROTECTED__.zoo = function() {...};	// Protected Static Method

	======================================================================
	A4. Method Overloads
	======================================================================

	Overloads are methods with different signatures. To implement overloads we detect such methods at
	compile time and we append to their name $<index> in order to have unique names. The compiler
	automatically detects from the call which function needs to bind and generates the appropriate
	code.

	function ClassOuter()
	{
		function ClassInner(__BASE__)
		{
			this.foo = function()  {...};
			this.foo$1 = function(A)  {...};
			this.foo$2 = function(A,B,C)  {...};

			return this;
		}
		return new ClassInner(null);
	}

	======================================================================
	A5. Virtual Methods
	======================================================================

	In C++ a virtual method is being replaced by the the implementation of the derived class.
	Any call to the virtual method either by the derived class or by the base class, calls the
	implementation of the derived class, UNLESS you explicitly ask for BaseClass::VirtualMethod
	like the example in goo() below which calls "Class1::foo();". Access to the replaced method
	by the derived class is achieved only by using "super" keyword.

	#include <iostream>
	using namespace std;

	class Class1
	{
	public:
		void goo()
		{
			Class1::foo();
			foo();
		}
		virtual void foo()
		{
			cout << "Class1::foo\n";
		}
	};

	class Class2 : public Class1
	{
	public:
		void foo()
		{
			cout << "Class2::foo\n";
		}
	};

	int main()
	{
		Class2* obj = new Class2();
		obj->goo();
		obj->foo();
		obj->Class1::foo();   //TODO: should implement this at some point
		return 0;
	}

	To implement virtual methods in JavaScript we define the __VIRTUAL__ bank in the inner function
	and we keep a copy of all virtual functions original implementation in there. The derived class
	overwrites the virtual method to the base class inner function replacing "this.foo" but does not
	change the function copy inside "__VIRTUAL__.foo". If we want to call the original implementation
	of the function a statement like "super.foo" would call "__VIRTUAL__.foo".

	function Class1Outer()
	{
		function Class1Inner(__BASE__)
		{
			this.foo = this.__VIRTUAL__.foo = function(){...};
			this.__PROTECTED__.goo = this.__VIRTUAL__.__PROTECTED__.goo = function(){...};
			return this;
		}
		return new Class1Inner(null);
	}

	function Class2Outer()
	{
		function Class2Inner(__BASE__)
		{

			   Here we redefine foo
			   in base class
			    |
			__BASE__.foo = this.foo = this.__VIRTUAL__.foo = function(){ /* New definition of foo() */ };
			__BASE__.__PROTECTED__.goo = this.__PROTECTED__.goo = this.__VIRTUAL__.__PROTECTED__.goo = function(){ /* New definition of goo() */ };

			return this;
		}
		var base = new Class1Outer;
		Class2Inner.prototype = base;
		return new Class2Inner(base);
	}

	======================================================================
	A6. Who is "this"?, aka "Execution Context"
	======================================================================

	Having covered modifiers, statics, overloads and virtuals, we now need to think about the
	Execution Context, or in other words, the "this" keyword. To fully undestand the problem
	consider the following code. Class1 has a method that saves "this" to a variable.
	A derived class Class3 is calling this method to retreive "this" and access it.

	///////////////////////////////////////////////////////
	class Class1
	{
		public var saved:Object;
		public function Constructor(){}
		public function Destructor(){}

		public function save_this()
		{
			saved = this;	// <- what is this? can you guess?
		}
	}

	///////////////////////////////////////////////////////
	class Class2 : Class1
	{
	}

	///////////////////////////////////////////////////////
	class Class3 : Class2
	{
	}

	///////////////////////////////////////////////////////
	class TestThis
	{
		public function Constructor()
		{
			var t:Class3 = new Class3();
			t.save_this();
			trace( "Saved instance type: " + t.saved.toString() );
		}
	}

	Since we are using JavaScript prototype based inheritance, in every member function "this"
	points to the actual base-class instance stored on the prototype, and "this" is wrong!!
	The way to "fix" this problem is by keeping the execution contect in __THIS__ variable.
	Initially __THIS__ = this; but as an object inherits from another, it replaces the base
	object's __THIS__ with its own. Compiler-wise, we make sure we generate "__THIS__" instead
	of "this" in closures such as functions, properties, states, etc.

	Let me give you a quick hint before reading the next code:
	In a function when you type "var x" is different from "this.x"

	function foo()
	{
		var __THIS__;
		this.__THIS__;
	}

	We will take advantage of this distinction in order to define __THIS__ as a property so that
	the derivative class can change __THIS__ using the same semantics. So basically the inner
	function would look like:

	function outer()
	{
		function inner()
		{
			var __THIS__ = this;
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });
		}
	}

	By taking advantage of this distinction and the definitions above, a derivative class can now
	successfully overwrite the execution context of its base classes and the compiler will do the
	rest of the magic:

	///////////////////////////////////////////////////////
	function Class1()
	{
		function __Class1()
		{
			var __THIS__ = this;
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });

			this.save_this = function ()
			{
				__CLASS__Class1__.saved = __THIS__;
			};
		}
		return new __Class1();
	}

	///////////////////////////////////////////////////////
	function Class2()
	{
		function __Class2()
		{
			var __THIS__ = this;
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });


			// ****** This is how Class2 replaces the execution context of Class1 ****** //

			__CLASS__Class1__.__THIS__ = this;


		}
		__Class2.prototype = new Class1();
		return new __Class2();
	}

	///////////////////////////////////////////////////////
	function Class3()
	{
		function __Class3()
		{
			var __THIS__ = this;
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });

			// ****** This is how Class3 replaces the execution context of Class2 and Class1 ****** //

			__CLASS__Class3__.__CLASS__Class2__.__CLASS__Class1__.__THIS__ = this,
			__CLASS__Class3__.__CLASS__Class2__.__THIS__ = this;
		}
		__Class3.prototype = new Class2();
		return new __Class3();
	}


	======================================================================
	A7. Resolving identifier runtime access DOT path
	======================================================================

	What this means?

	First, it means you need to understand the difference between "identifer" and "symbol" before you continue reading!!!

	+ When you type something like "var x:Float=5;", you define "symbol x".
	+ When you later type "x++;" then this "x" is the "identifier x" which must be linked to "symbol x".

	The symbol holds all the nessesary metdata about the identifier, such as its vartype, its containing class, its scope, etc.

	Therefore, resolving the identifier runtime access DOT path is the process of deriving a DOT path (A.B.C.D.x) that will take you
	from where the "identifier x" is to where "symbol x" is actually stored. This can be a different class, a base-class, a virtual
	method, an overloaded method, an enum, etc.

	Typically this depends on "WHERE THE SYMBOL IS DEFINED" and "WHERE IT IS BEING ACCESSED FROM". If the symbol is defined in ClassA
	and it is being access from ClassB then we need to construct an access path that will successfully read/write its data. However,
	there are severlar spacial cases about this. For example, the identifier might be a virtual function which is a rather tricky case,
	or the identifier might be a member of a base-class (of a base-class, of a base-class, ..), which makes the access path	a bit longer.

	To actually solve this problem we need to lay down some access rules:
	=====================================================================

	1. The DOT access-path pattern is: [__CLASS_XXX__][.__BASES__|.__VIRTUAL__][.__PRIVATE__|.__PROTECTED__].<symbol_name>

	__CLASS_XXX__    	: The name of the class where the symbol is defined.
	__BASES__        	: If the symbol is an inherited member, this is a dot-list of all the base classIds leading to the low-level
						  base-class where the symbol is defined.
	__VIRTUAL__      	: (or) If the symbol is a virtual function symbol, we need to access it through the __VIRTUAL__ bank.
	__PRIVATE__      	: If the symbol is a private symbol, we need to access it through the __PRIVATE__ bank.
	__PROTECTED__    	: (or) If the symbol is a private symbol, we need to access it through the __PROTECTED__ bank.
	<symbol_name>  		: The symbol name. This can be different from the identifier name for overloaded functions.
	                       To understand what this means think of the XMLHttp.send() overloads that produce different symbol names:
	                       XMLHttp.send(), XMLHttp.send$1(String), XMLHttp.send$2(ArrayBufferView)

	2. Access at the end of the day is controlled by public/private/protected modifiers at compile-time.

	3. If the identifier is a class member (function, var, property, etc.) and the class derives from a base-class, we ALWAYS access the
	   low-level base-class identifier.

	4. To make our life easier, we do not generate "this" if it is the first identifier in a DOT. We let the second identifier of the DOT
	   generate "this" if needed. This rule actually makes our life much easier, especially if the DOT accesses an inherited member where
	   generating "this" would require that we unwind the stack.

	5. We generate "__THIS__" for "this" if and only if it is alone, eg. passed as argument: obj.setParent( this );

	6. Enum Items are similar to "this" because programmers access enums either canonically "enum_name.enum_item" or straight "enum_item".
	   Therefore we need to skip generating the enum class name (yes, enums are classes and enum items static constants) if it is the first
	   identifier in a DOT, and make sure that the enum-item will be generated fully qualified.

	7. If access to the identifier is LOCAL (meaning that the identifier points to a class member) we prefix the local classId: __CLASS_XXX__

	8. If access to the identifier is NOT-LOCAL (meaning that the identifier points to another class) we DO NOT prefix the classId.

	9. Global scope knows nothing about inheritance, so plain JavaScript code should be able to work with our classes seamlessly.

	** NONTE: **
	The access-path of the symbol is calculated during symbol generation and stored in "symbol.runtime". However, resolving an identifier
	linked to this symbol in most cases it requres further processing. Both "symbol.runtime" and "ast.runtime" are exported as "debug symbols"
	so that when you debug and you hover the mouse over an identifier, it can be recognized and evaluated getting a tooltip of its value, or
	if it is an object display a list of its member values in the IDE expression viewer.


	Elias G. Politakis
	mobileFX CTO/Partner
	epolitakis@mobilefx.com

	Credits:
	Roger Poon
	George Mathioudakis



	APPENDIX:

	a) CocoScript code
	b) Generated JavaScript code

	// ==================================================================================================================================
	//	   ______                _____           _       __     ______          __
	//	  / ____/___  _________ / ___/__________(_)___  / /_   / ____/___  ____/ /__
	//	 / /   / __ \/ ___/ __ \\__ \/ ___/ ___/ / __ \/ __/  / /   / __ \/ __  / _ \
	//	/ /___/ /_/ / /__/ /_/ /__/ / /__/ /  / / /_/ / /_   / /___/ /_/ / /_/ /  __/
	//	\____/\____/\___/\____/____/\___/_/  /_/ .___/\__/   \____/\____/\__,_/\___/
	//	                                      /_/
	// ==================================================================================================================================

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	state class Class1
	{
		// Member Variables
		public var public_var:String;
		private var private_var:String;
		protected var protected_var:String;

		// Member Constants
		public const public_const:String = "Class1_public_const";
		private const private_const:String = "Class1_private_const";
		protected const protected_const:String = "Class1_protected_const";

		// Static Variables
		public static var static_public_var:String;
		private static var static_private_var:String;
		protected static var static_protected_var:String;

		// (used by properties)
		private var __public_property:String;
		private var __private_property:String;
		private var __protected_property:String;

		private static var __public_static_property:String;
		private static var __private_static_property:String;
		private static var __protected_static_property:String;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function Constructor(arg1:String, arg2:String)
		{
			trace( "Class1::Constructor(" + arg1 + "," + arg2 + ")");

			public_var 			= "Class1_public_var+" + arg1;
			private_var 		= "Class1_private_var+" + arg2;
			protected_var		= "Class1_protected_var";
			public_property 	= "Class1_public_property";
			private_property 	= "Class1_private_property";
			protected_property 	= "Class1_protected_property";
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function Destructor()
		{
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public virtual function test_virtual()
		{
			trace("Class1::test_virtual");
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public virtual function test()
		{
			trace("========================== Class1::test() ==========================");


			// When called without super class, it should call the function above, Class1::test_virtual
			// When called with a super class, it should call the replaced function, Class3::test_virtual

			test_virtual();
			this.test_virtual();

			public_state.tick(0)
			private_state.tick(0)
			protected_state.tick(0)

			trace( "Class1::public_overload()                    = " + public_overload()      					);
			trace( "Class1::public_overload(arg1)                = " + public_overload("arg1")  				);
			trace( "Class1::public_overload(arg1,arg2)           = " + public_overload("arg1","arg2")			);

			trace( "Class1::private_overload()                   = " + private_overload()      					);
			trace( "Class1::private_overload(arg1)               = " + private_overload("arg1")  				);
			trace( "Class1::private_overload(arg1,arg2)          = " + private_overload("arg1","arg2")			);

			trace( "Class1::protected_overload()                 = " + protected_overload()      				);
			trace( "Class1::protected_overload(arg1)             = " + protected_overload("arg1")  				);
			trace( "Class1::protected_overload(arg1,arg2)        = " + protected_overload("arg1","arg2")		);

			trace( "Class1::public_function()                    = " + public_function() 						);
			trace( "Class1::private_function()                   = " + private_function() 						);
			trace( "Class1::protected_function()                 = " + protected_function() 					);

			trace( "Class1::public_var                           = " + public_var 								);
			trace( "Class1::private_var                          = " + private_var 								);
			trace( "Class1::protected_var                        = " + protected_var							);

			trace( "Class1::public_property                      = " + public_property 							);
			trace( "Class1::private_property                     = " + private_property      					);
			trace( "Class1::protected_property                   = " + protected_property    					);

			/*
			this.public_state.tick(0)
			this.private_state.tick(0)
			this.protected_state.tick(0)
			trace( "Class1::this.public_overload()               = " + this.public_overload()      				);
			trace( "Class1::this.public_overload(arg1)           = " + this.public_overload("arg1")  			);
			trace( "Class1::this.public_overload(arg1,arg2)      = " + this.public_overload("arg1","arg2")		);
			trace( "Class1::this.private_overload()              = " + this.private_overload()      			);
			trace( "Class1::this.private_overload(arg1)          = " + this.private_overload("arg1")  			);
			trace( "Class1::this.private_overload(arg1,arg2)     = " + this.private_overload("arg1","arg2")		);
			trace( "Class1::this.protected_overload()            = " + this.protected_overload()      			);
			trace( "Class1::this.protected_overload(arg1)        = " + this.protected_overload("arg1")  		);
			trace( "Class1::this.protected_overload(arg1,arg2)   = " + this.protected_overload("arg1","arg2")	);
			trace( "Class1::this.public_function()               = " + this.public_function() 					);
			trace( "Class1::this.private_function()              = " + this.private_function() 					);
			trace( "Class1::this.protected_function()            = " + this.protected_function() 				);
			trace( "Class1::this.public_function()               = " + this.public_function()					);
			trace( "Class1::this.private_function()              = " + this.private_function()					);
			trace( "Class1::this.protected_function()            = " + this.protected_function()				);
			trace( "Class1::this.public_var                      = " + this.public_var 							);
			trace( "Class1::this.private_var                     = " + this.private_var 						);
			trace( "Class1::this.protected_var                   = " + this.protected_var						);
			trace( "Class1::this.public_property                 = " + this.public_property 					);
			trace( "Class1::this.private_property                = " + this.private_property     				);
			trace( "Class1::this.protected_property              = " + this.protected_property   				);
			*/
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Static Functions

		public static function public_static_function(optional b:String):String { return "Class1_public_static_function"; }
		private static function private_static_function(optional b:String):String { return "Class1_private_static_function"; }
		protected static function protected_static_function(optional b:String):String { return "Class1_protected_static_function"; }

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Standard Functions

		public function public_function(optional b:String):String { return "Class1_public_function"; }
		private function private_function(optional b:String):String { return "Class1_private_function"; }
		protected function protected_function(optional b:String):String { return "Class1_protected_function"; }

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Overloaded Functions

		public function public_overload():String { return "Class1_public_overload"; }
		public function public_overload(arg:String):String { return "Class1_public_overload("+arg+")"; }
		public function public_overload(arg1:String, arg2:String):String { return "Class1_public_overload("+arg1+","+arg2+")"; }

		private function private_overload():String { return "Class1_private_overload"; }
		private function private_overload(arg:String):String { return "Class1_private_overload("+arg+")"; }
		private function private_overload(arg1:String, arg2:String):String { return "Class1_private_overload("+arg1+","+arg2+")"; }

		protected function protected_overload():String { return "Class1_protected_overload"; }
		protected function protected_overload(arg:String):String { return "Class1_protected_overload("+arg+")"; }
		protected function protected_overload(arg1:String, arg2:String):String { return "Class1_protected_overload("+arg1+","+arg2+")"; }

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// States

		public state public_state
		{
			var state_var:String;

			function enter() 	{ state_var = "+public_state_scope_var"; trace("Class1_public_state_enter " + state_var); }
			function exit() 	{ trace("Class1_public_state_exit"); }
			function tick(time:Time) 	{ trace("Class1_public_state_tick"); }
			function paint(gl:WebGLRenderingContext, time:Time) 	{ trace("Class1_public_state_paint"); }
		}

		private state private_state
		{
			var state_var:String;

			function enter() 	{ state_var = "+private_state_scope_var"; trace("Class1_private_state_enter " + state_var); }
			function exit() 	{ trace("Class1_private_state_exit"); }
			function tick(time:Time) 	{ trace("Class1_private_state_tick"); }
			function paint(gl:WebGLRenderingContext, time:Time) 	{ trace("Class1_private_state_paint"); }
		}

		protected state protected_state
		{
			var state_var:String;

			function enter() 	{ state_var = "+protected_state_scope_var"; trace("Class1_protected_state_enter " + state_var); }
			function exit() 	{ trace("Class1_protected_state_exit"); }
			function tick(time:Time) 	{ trace("Class1_protected_state_tick"); }
			function paint(gl:WebGLRenderingContext, time:Time) 	{ trace("Class1_protected_state_paint"); }
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Properties

		public property public_property
		{
			function get():String  { return __public_property; }
			function set(v:String) { __public_property = v;}
		}

		private property private_property
		{
			function get():String  { return __private_property; }
			function set(v:String) { __private_property=v; }
		}

		protected property protected_property
		{
			function get():String  { return __protected_property; }
			function set(v:String) { __protected_property = v;}
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Static Properties

		public static property public_static_property
		{
			function get():String  { return __public_static_property; }
			function set(v:String) { __public_static_property = v;}
		}

		private static property private_static_property
		{
			function get():String  { return __private_static_property; }
			function set(v:String) { __private_static_property=v; }
		}

		protected static property protected_static_property
		{
			function get():String  { return __protected_static_property; }
			function set(v:String) { __protected_static_property = v;}
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	state class Class2 : Class1
	{
		public var x:String;
		private var y:String;
		protected var z:String;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function Constructor(arg1:String) : Class1(arg1, "::arg2_from_Class2")
		{
			trace( "Class2::Constructor(" + arg1 + ")");

			x = "Class2_public_x";
			y = "Class2_private_y";
			z = "Class2_protected_z";
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public virtual function test()
		{
			trace("========================== Class2::test() (before super) ==========================");

			trace("Class2::test::super.test()");
			super.test();

			trace("========================== Class2::test() (after super) ==========================");

			trace( x );
			trace( y );
			trace( z );

			public_state.tick(0)
			protected_state.tick(0)

			trace( "Class2::cls2_public_function()               = " + cls2_public_function()                   );

			trace( "Class2::public_overload()                    = " + public_overload()      					);
			trace( "Class2::public_overload(arg1)                = " + public_overload("arg1")  				);
			trace( "Class2::public_overload(arg1,arg2)           = " + public_overload("arg1","arg2")			);
			trace( "Class2::protected_overload()                 = " + protected_overload()      				);
			trace( "Class2::protected_overload(arg1)             = " + protected_overload("arg1")  				);
			trace( "Class2::protected_overload(arg1,arg2)        = " + protected_overload("arg1","arg2")		);
			trace( "Class2::public_function()                    = " + public_function() 						);
			trace( "Class2::protected_function()                 = " + protected_function() 					);
			trace( "Class2::public_var                           = " + public_var 								);
			trace( "Class2::protected_var                        = " + protected_var							);
			trace( "Class2::public_property                      = " + public_property 							);
			trace( "Class2::protected_property                   = " + protected_property    					);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function cls2_public_function():String
		{
			return "Class2_cls2_public_function";
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	state class Class3 : Class2
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function Constructor() : Class2("::arg1_from_Class3")
		{
			trace("Class3::Constructor");
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public virtual function test_virtual()
		{
			trace("Class3::test_virtual");
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		public function test()
		{
			trace("========================== Class3::test() (before super) ==========================");

			trace("Class3::test::super.test()");

			super.test();

			trace("========================== Class3::test() (after super) ==========================");

			trace( x );
			trace( z );

			public_state.tick(0)
			protected_state.tick(0)

			trace( "Class3::public_overload()                    = " + public_overload()      					);
			trace( "Class3::public_overload(arg1)                = " + public_overload("arg1")  				);
			trace( "Class3::public_overload(arg1,arg2)           = " + public_overload("arg1","arg2")			);
			trace( "Class3::protected_overload()                 = " + protected_overload()      				);
			trace( "Class3::protected_overload(arg1)             = " + protected_overload("arg1")  				);
			trace( "Class3::protected_overload(arg1,arg2)        = " + protected_overload("arg1","arg2")		);
			trace( "Class3::public_function()                    = " + public_function() 						);
			trace( "Class3::protected_function()                 = " + protected_function() 					);
			trace( "Class3::public_var                           = " + public_var 								);
			trace( "Class3::protected_var                        = " + protected_var							);
			trace( "Class3::public_property                      = " + public_property 							);
			trace( "Class3::protected_property                   = " + protected_property    					);
		}
	}

	// ==================================================================================================================================
	//	   ______                           __           __       __                  _____           _       __
	//	  / ____/__  ____  ___  _________ _/ /____  ____/ /      / /___ __   ______ _/ ___/__________(_)___  / /_
	//	 / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ _ \/ __  /  __  / / __ `/ | / / __ `/\__ \/ ___/ ___/ / __ \/ __/
	//	/ /_/ /  __/ / / /  __/ /  / /_/ / /_/  __/ /_/ /  / /_/ / /_/ /| |/ / /_/ /___/ / /__/ /  / / /_/ / /_
	//	\____/\___/_/ /_/\___/_/   \__,_/\__/\___/\__,_/   \____/\__,_/ |___/\__,_//____/\___/_/  /_/ .___/\__/
	//	                                                                                           /_/
	// ==================================================================================================================================

	#pragma export_web
	//@line 17

	function Class1(__CLASS__CLASS1__$arg1__, __CLASS__CLASS1__$arg2__)
	{
		var __BASE__ = null;

		function __Class1(__CLASS__CLASS1__$arg1__, __CLASS__CLASS1__$arg2__)
		{
			var Class = this.Class = 'Class1',
				__PDEFINE__ = Object.defineProperty,
				__NOENUM__ = {enumerable:false},
				__CLASS__CLASS1__ = this.__CLASS__CLASS1__ = this;
			var __THIS__ = this;
			this.toString = function ()
			{
				return 'Class1'
			};
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });
			var __VIRTUAL__ = this.__VIRTUAL__ =
			{
				__PROTECTED__: {}
			},
				__PRIVATE__ = this.__PRIVATE__ = {},
				__PROTECTED__ = this.__PROTECTED__ = {};
			__PDEFINE__(this, '__PRIVATE__', __NOENUM__);
			__PDEFINE__(this, '__PROTECTED__', __NOENUM__);
			//@line 25
			this.public_const = "Class1_public_const";
			//@line 26
			__PRIVATE__.private_const = "Class1_private_const";
			//@line 27
			__PROTECTED__.protected_const = "Class1_protected_const";
			//@line 20
			this.public_var = "";
			//@line 21
			__PRIVATE__.private_var = "";
			//@line 22
			__PROTECTED__.protected_var = "";
			//@line 35
			__PRIVATE__.__public_property = "";
			//@line 36
			__PRIVATE__.__private_property = "";
			//@line 37
			__PRIVATE__.__protected_property = "";
			//@line 62
			this.test_virtual = __VIRTUAL__.test_virtual = function ()
			{
				//@line 64
				trace("Class1::test_virtual");
				//@line 65
			};
			//@line 68
			this.test = __VIRTUAL__.test = function ()
			{
				//@line 70
				trace("========================== Class1::test() ==========================");
				//@line 76
				__CLASS__CLASS1__.test_virtual();
				//@line 77
				__VIRTUAL__.test_virtual();
				//@line 79
				__CLASS__CLASS1__.public_state.tick(0);
				//@line 80
				__CLASS__CLASS1__.__PRIVATE__.private_state.tick(0);
				//@line 81
				__CLASS__CLASS1__.__PROTECTED__.protected_state.tick(0);
				//@line 83
				trace("Class1::public_overload()                    = " + __CLASS__CLASS1__.public_overload());
				//@line 84
				trace("Class1::public_overload(arg1)                = " + __CLASS__CLASS1__.public_overload$1("arg1"));
				//@line 85
				trace("Class1::public_overload(arg1,arg2)           = " + __CLASS__CLASS1__.public_overload$2("arg1", "arg2"));
				//@line 87
				trace("Class1::private_overload()                   = " + __CLASS__CLASS1__.__PRIVATE__.private_overload());
				//@line 88
				trace("Class1::private_overload(arg1)               = " + __CLASS__CLASS1__.__PRIVATE__.private_overload$1("arg1"));
				//@line 89
				trace("Class1::private_overload(arg1,arg2)          = " + __CLASS__CLASS1__.__PRIVATE__.private_overload$2("arg1", "arg2"));
				//@line 91
				trace("Class1::protected_overload()                 = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload());
				//@line 92
				trace("Class1::protected_overload(arg1)             = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload$1("arg1"));
				//@line 93
				trace("Class1::protected_overload(arg1,arg2)        = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload$2("arg1", "arg2"));
				//@line 95
				trace("Class1::public_function()                    = " + __CLASS__CLASS1__.public_function());
				//@line 96
				trace("Class1::private_function()                   = " + __CLASS__CLASS1__.__PRIVATE__.private_function());
				//@line 97
				trace("Class1::protected_function()                 = " + __CLASS__CLASS1__.__PROTECTED__.protected_function());
				//@line 99
				trace("Class1::public_var                           = " + __CLASS__CLASS1__.public_var);
				//@line 100
				trace("Class1::private_var                          = " + __CLASS__CLASS1__.__PRIVATE__.private_var);
				//@line 101
				trace("Class1::protected_var                        = " + __CLASS__CLASS1__.__PROTECTED__.protected_var);
				//@line 103
				trace("Class1::public_property                      = " + __CLASS__CLASS1__.public_property);
				//@line 104
				trace("Class1::private_property                     = " + __CLASS__CLASS1__.__PRIVATE__.private_property);
				//@line 105
				trace("Class1::protected_property                   = " + __CLASS__CLASS1__.__PROTECTED__.protected_property);
				//@line 133
			};
			//@line 145
			this.public_function = function (b)
			{
				return "Class1_public_function";
				return ""
			};
			//@line 146
			this.__PRIVATE__.private_function = function (b)
			{
				return "Class1_private_function";
				return ""
			};
			//@line 147
			this.__PROTECTED__.protected_function = function (b)
			{
				return "Class1_protected_function";
				return ""
			};
			//@line 152
			this.public_overload = function ()
			{
				return "Class1_public_overload";
				return ""
			};
			//@line 153
			this.public_overload$1 = function (arg)
			{
				return "Class1_public_overload(" + arg + ")";
				return ""
			};
			//@line 154
			this.public_overload$2 = function (arg1, arg2)
			{
				return "Class1_public_overload(" + arg1 + "," + arg2 + ")";
				return ""
			};
			//@line 156
			this.__PRIVATE__.private_overload = function ()
			{
				return "Class1_private_overload";
				return ""
			};
			//@line 157
			this.__PRIVATE__.private_overload$1 = function (arg)
			{
				return "Class1_private_overload(" + arg + ")";
				return ""
			};
			//@line 158
			this.__PRIVATE__.private_overload$2 = function (arg1, arg2)
			{
				return "Class1_private_overload(" + arg1 + "," + arg2 + ")";
				return ""
			};
			//@line 160
			this.__PROTECTED__.protected_overload = function ()
			{
				return "Class1_protected_overload";
				return ""
			};
			//@line 161
			this.__PROTECTED__.protected_overload$1 = function (arg)
			{
				return "Class1_protected_overload(" + arg + ")";
				return ""
			};
			//@line 162
			this.__PROTECTED__.protected_overload$2 = function (arg1, arg2)
			{
				return "Class1_protected_overload(" + arg1 + "," + arg2 + ")";
				return ""
			};
			//@line 200
			Object.defineProperty(this, 'public_property', {
				enumerable: true,
				//@line 202
				get: function ()
				{
					return __CLASS__CLASS1__.__PRIVATE__.__public_property;
					return ""
				},
				//@line 203
				set: function (v)
				{
					__CLASS__CLASS1__.__PRIVATE__.__public_property = v;
				}
			});
			//@line 206
			Object.defineProperty(this.__PRIVATE__, 'private_property', {
				enumerable: true,
				//@line 208
				get: function ()
				{
					return __CLASS__CLASS1__.__PRIVATE__.__private_property;
					return ""
				},
				//@line 209
				set: function (v)
				{
					__CLASS__CLASS1__.__PRIVATE__.__private_property = v;
				}
			});
			//@line 212
			Object.defineProperty(this.__PROTECTED__, 'protected_property', {
				enumerable: true,
				//@line 214
				get: function ()
				{
					return __CLASS__CLASS1__.__PRIVATE__.__protected_property;
					return ""
				},
				//@line 215
				set: function (v)
				{
					__CLASS__CLASS1__.__PRIVATE__.__protected_property = v;
				}
			});
			//@line 167
			this.public_state = (function ()
			{
				this.__name = 'public_state';
				//@line 169
				var state_var = this.state_var = "";
				//@line 171
				this.enter = function ()
				{
					state_var = "+public_state_scope_var";
					trace("Class1_public_state_enter " + state_var);
				};
				//@line 172
				this.exit = function ()
				{
					trace("Class1_public_state_exit");
				};
				//@line 173
				this.tick = function (time)
				{
					trace("Class1_public_state_tick");
				};
				//@line 174
				this.paint = function (gl, time)
				{
					trace("Class1_public_state_paint");
				};
				return this
			}).call(new State);
			//@line 177
			this.__PRIVATE__.private_state = (function ()
			{
				this.__name = 'private_state';
				//@line 179
				var state_var = this.state_var = "";
				//@line 181
				this.enter = function ()
				{
					state_var = "+private_state_scope_var";
					trace("Class1_private_state_enter " + state_var);
				};
				//@line 182
				this.exit = function ()
				{
					trace("Class1_private_state_exit");
				};
				//@line 183
				this.tick = function (time)
				{
					trace("Class1_private_state_tick");
				};
				//@line 184
				this.paint = function (gl, time)
				{
					trace("Class1_private_state_paint");
				};
				return this
			}).call(new State);
			//@line 187
			this.__PROTECTED__.protected_state = (function ()
			{
				this.__name = 'protected_state';
				//@line 189
				var state_var = this.state_var = "";
				//@line 191
				this.enter = function ()
				{
					state_var = "+protected_state_scope_var";
					trace("Class1_protected_state_enter " + state_var);
				};
				//@line 192
				this.exit = function ()
				{
					trace("Class1_protected_state_exit");
				};
				//@line 193
				this.tick = function (time)
				{
					trace("Class1_protected_state_tick");
				};
				//@line 194
				this.paint = function (gl, time)
				{
					trace("Class1_protected_state_paint");
				};
				return this
			}).call(new State);
			//@line 57
			this.Destructor = function ()
			{
				{
					//@line 59
				}
				{
					__CLASS__CLASS1__.public_var = null;
					__CLASS__CLASS1__.__PRIVATE__.private_var = null;
					__CLASS__CLASS1__.__PROTECTED__.protected_var = null;
					__CLASS__CLASS1__.public_const = null;
					__CLASS__CLASS1__.__PRIVATE__.private_const = null;
					__CLASS__CLASS1__.__PROTECTED__.protected_const = null;
					__CLASS__CLASS1__.static_public_var = null;
					__CLASS__CLASS1__.__PRIVATE__.static_private_var = null;
					__CLASS__CLASS1__.__PROTECTED__.static_protected_var = null;
					__CLASS__CLASS1__.__PRIVATE__.__public_property = null;
					__CLASS__CLASS1__.__PRIVATE__.__private_property = null;
					__CLASS__CLASS1__.__PRIVATE__.__protected_property = null;
					__CLASS__CLASS1__.__PRIVATE__.__public_static_property = null;
					__CLASS__CLASS1__.__PRIVATE__.__private_static_property = null;
					__CLASS__CLASS1__.__PRIVATE__.__protected_static_property = null;
					__CLASS__CLASS1__.public_state = null;
					__CLASS__CLASS1__.__PRIVATE__.private_state = null;
					__CLASS__CLASS1__.__PROTECTED__.protected_state = null;
					__CLASS__CLASS1__.public_property = null;
					__CLASS__CLASS1__.__PRIVATE__.private_property = null;
					__CLASS__CLASS1__.__PROTECTED__.protected_property = null;
					__CLASS__CLASS1__.public_static_property = null;
					__CLASS__CLASS1__.__PRIVATE__.private_static_property = null;
					__CLASS__CLASS1__.__PROTECTED__.protected_static_property = null;
				}
				return true
			};
			//@line 44
			this.Constructor = function (arg1, arg2)
			{
				//@line 46
				trace("Class1::Constructor(" + arg1 + "," + arg2 + ")");
				//@line 48
				__CLASS__CLASS1__.public_var = "Class1_public_var+" + arg1;
				//@line 49
				__CLASS__CLASS1__.__PRIVATE__.private_var = "Class1_private_var+" + arg2;
				//@line 50
				__CLASS__CLASS1__.__PROTECTED__.protected_var = "Class1_protected_var";
				//@line 51
				__CLASS__CLASS1__.public_property = "Class1_public_property";
				//@line 52
				__CLASS__CLASS1__.__PRIVATE__.private_property = "Class1_private_property";
				//@line 53
				__CLASS__CLASS1__.__PROTECTED__.protected_property = "Class1_protected_property";
				//@line 54
			};
			__PDEFINE__(this, 'Constructor', __NOENUM__);
			this.Constructor(__CLASS__CLASS1__$arg1__, __CLASS__CLASS1__$arg2__);
			return this;
		}
		return new __Class1(__CLASS__CLASS1__$arg1__, __CLASS__CLASS1__$arg2__);
	}
	Class1.__PRIVATE__ = {};
	Class1.__PROTECTED__ = {};
	//@line 30
	Class1.static_public_var = "";
	//@line 31
	Class1.__PRIVATE__.static_private_var = "";
	//@line 32
	Class1.__PROTECTED__.static_protected_var = "";
	//@line 39
	Class1.__PRIVATE__.__public_static_property = "";
	//@line 40
	Class1.__PRIVATE__.__private_static_property = "";
	//@line 41
	Class1.__PRIVATE__.__protected_static_property = "";
	//@line 138
	Class1.public_static_function = function (b)
	{
		return "Class1_public_static_function";
		return ""
	};
	//@line 139
	Class1.__PRIVATE__.private_static_function = function (b)
	{
		return "Class1_private_static_function";
		return ""
	};
	//@line 140
	Class1.__PROTECTED__.protected_static_function = function (b)
	{
		return "Class1_protected_static_function";
		return ""
	};
	//@line 221
	Object.defineProperty(Class1, 'public_static_property', {
		enumerable: true,
		//@line 223
		get: function ()
		{
			return Class1.__PRIVATE__.__public_static_property;
			return ""
		},
		//@line 224
		set: function (v)
		{
			Class1.__PRIVATE__.__public_static_property = v;
		}
	});
	//@line 227
	Object.defineProperty(Class1.__PRIVATE__, 'private_static_property', {
		enumerable: true,
		//@line 229
		get: function ()
		{
			return Class1.__PRIVATE__.__private_static_property;
			return ""
		},
		//@line 230
		set: function (v)
		{
			Class1.__PRIVATE__.__private_static_property = v;
		}
	});
	//@line 233
	Object.defineProperty(Class1.__PROTECTED__, 'protected_static_property', {
		enumerable: true,
		//@line 235
		get: function ()
		{
			return Class1.__PRIVATE__.__protected_static_property;
			return ""
		},
		//@line 236
		set: function (v)
		{
			Class1.__PRIVATE__.__protected_static_property = v;
		}
	});
	//@line 242

	function Class2(__CLASS__CLASS2__$arg1__)
	{
		var __BASE__ = null;

		function __Class2(__CLASS__CLASS2__$arg1__)
		{
			var Class = this.Class = 'Class2',
				__PDEFINE__ = Object.defineProperty,
				__NOENUM__ = {enumerable:false},
				__CLASS__CLASS2__ = this.__CLASS__CLASS2__ = this;
			var __THIS__ = this;
			this.toString = function ()
			{
				return 'Class2'
			};
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });
			var __VIRTUAL__ = this.__VIRTUAL__ =
			{
				__PROTECTED__: {}
			},
				__PRIVATE__ = this.__PRIVATE__,
				__PROTECTED__ = this.__PROTECTED__,
				__CLASS__CLASS1__ = this.__CLASS__CLASS1__ = __CLASS__CLASS2__.__CLASS__CLASS1__
				__CLASS__CLASS2__.__CLASS__CLASS1__.__THIS__ = __CLASS__CLASS2__;
			//@line 244
			this.x = "";
			//@line 245
			__PRIVATE__.y = "";
			//@line 246
			__PROTECTED__.z = "";
			//@line 259
			this.test = __VIRTUAL__.test = __CLASS__CLASS1__.test = function ()
			{
				//@line 261
				trace("========================== Class2::test() (before super) ==========================");
				//@line 263
				trace("Class2::test::super.test()");
				//@line 264
				__CLASS__CLASS1__.__VIRTUAL__.test();
				//@line 266
				trace("========================== Class2::test() (after super) ==========================");
				//@line 268
				trace(__CLASS__CLASS2__.x);
				//@line 269
				trace(__CLASS__CLASS2__.__PRIVATE__.y);
				//@line 270
				trace(__CLASS__CLASS2__.__PROTECTED__.z);
				//@line 272
				__CLASS__CLASS1__.public_state.tick(0);
				//@line 273
				__CLASS__CLASS1__.__PROTECTED__.protected_state.tick(0);
				//@line 275
				trace("Class2::cls2_public_function()               = " + __CLASS__CLASS2__.cls2_public_function());
				//@line 277
				trace("Class2::public_overload()                    = " + __CLASS__CLASS1__.public_overload());
				//@line 278
				trace("Class2::public_overload(arg1)                = " + __CLASS__CLASS1__.public_overload$1("arg1"));
				//@line 279
				trace("Class2::public_overload(arg1,arg2)           = " + __CLASS__CLASS1__.public_overload$2("arg1", "arg2"));
				//@line 280
				trace("Class2::protected_overload()                 = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload());
				//@line 281
				trace("Class2::protected_overload(arg1)             = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload$1("arg1"));
				//@line 282
				trace("Class2::protected_overload(arg1,arg2)        = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload$2("arg1", "arg2"));
				//@line 283
				trace("Class2::public_function()                    = " + __CLASS__CLASS1__.public_function());
				//@line 284
				trace("Class2::protected_function()                 = " + __CLASS__CLASS1__.__PROTECTED__.protected_function());
				//@line 285
				trace("Class2::public_var                           = " + __CLASS__CLASS1__.public_var);
				//@line 286
				trace("Class2::protected_var                        = " + __CLASS__CLASS1__.__PROTECTED__.protected_var);
				//@line 287
				trace("Class2::public_property                      = " + __CLASS__CLASS1__.public_property);
				//@line 288
				trace("Class2::protected_property                   = " + __CLASS__CLASS1__.__PROTECTED__.protected_property);
				//@line 289
			};
			//@line 292
			this.cls2_public_function = function ()
			{
				//@line 294
				return "Class2_cls2_public_function";
				return "" //@line 295
			};
			//@line 249
			this.Constructor = function (arg1)
			{
				//@line 251
				trace("Class2::Constructor(" + arg1 + ")");
				//@line 253
				__CLASS__CLASS2__.x = "Class2_public_x";
				//@line 254
				__CLASS__CLASS2__.__PRIVATE__.y = "Class2_private_y";
				//@line 255
				__CLASS__CLASS2__.__PROTECTED__.z = "Class2_protected_z";
				//@line 256
			};
			__PDEFINE__(this, 'Constructor', __NOENUM__);
			this.Constructor(__CLASS__CLASS2__$arg1__);
			return this;
		}
		__Class2.prototype = new Class1(__CLASS__CLASS2__$arg1__, "::arg2_from_Class2");
		return new __Class2(__CLASS__CLASS2__$arg1__);
	}
	Class2.__PRIVATE__ = {};
	Class2.__PROTECTED__ = {};
	//@line 30
	Class2.static_public_var = "";
	//@line 31
	Class2.__PRIVATE__.static_private_var = "";
	//@line 32
	Class2.__PROTECTED__.static_protected_var = "";
	//@line 39
	Class2.__PRIVATE__.__public_static_property = "";
	//@line 40
	Class2.__PRIVATE__.__private_static_property = "";
	//@line 41
	Class2.__PRIVATE__.__protected_static_property = "";
	//@line 138
	Class2.public_static_function = function (b)
	{
		return "Class1_public_static_function";
		return ""
	};
	//@line 139
	Class2.__PRIVATE__.private_static_function = function (b)
	{
		return "Class1_private_static_function";
		return ""
	};
	//@line 140
	Class2.__PROTECTED__.protected_static_function = function (b)
	{
		return "Class1_protected_static_function";
		return ""
	};
	//@line 221
	Object.defineProperty(Class2, 'public_static_property', {
		enumerable: true,
		//@line 223
		get: function ()
		{
			return Class2.__PRIVATE__.__public_static_property;
			return ""
		},
		//@line 224
		set: function (v)
		{
			Class2.__PRIVATE__.__public_static_property = v;
		}
	});
	//@line 227
	Object.defineProperty(Class2.__PRIVATE__, 'private_static_property', {
		enumerable: true,
		//@line 229
		get: function ()
		{
			return Class2.__PRIVATE__.__private_static_property;
			return ""
		},
		//@line 230
		set: function (v)
		{
			Class2.__PRIVATE__.__private_static_property = v;
		}
	});
	//@line 233
	Object.defineProperty(Class2.__PROTECTED__, 'protected_static_property', {
		enumerable: true,
		//@line 235
		get: function ()
		{
			return Class2.__PRIVATE__.__protected_static_property;
			return ""
		},
		//@line 236
		set: function (v)
		{
			Class2.__PRIVATE__.__protected_static_property = v;
		}
	});
	//@line 299

	function Class3()
	{
		var __BASE__ = null;

		function __Class3()
		{
			var Class = this.Class = 'Class3',
				__PDEFINE__ = Object.defineProperty,
				__NOENUM__ = {enumerable:false},
				__CLASS__CLASS3__ = this.__CLASS__CLASS3__ = this;
			var __THIS__ = this;
			this.toString = function ()
			{
				return 'Class3'
			};
			__PDEFINE__(this, '__THIS__', { enumerable: false, get: function () { return __THIS__; }, set: function (v) { __THIS__ = v; } });
			var __VIRTUAL__ = this.__VIRTUAL__ =
			{
				__PROTECTED__: {}
			},
				__PRIVATE__ = this.__PRIVATE__,
				__PROTECTED__ = this.__PROTECTED__,
				__CLASS__CLASS1__ = this.__CLASS__CLASS1__ = __CLASS__CLASS3__.__CLASS__CLASS2__.__CLASS__CLASS1__
				__CLASS__CLASS3__.__CLASS__CLASS2__.__CLASS__CLASS1__.__THIS__ = __CLASS__CLASS3__,
				__CLASS__CLASS2__ = this.__CLASS__CLASS2__ = __CLASS__CLASS3__.__CLASS__CLASS2__
				__CLASS__CLASS3__.__CLASS__CLASS2__.__THIS__ = __CLASS__CLASS3__;
			//@line 308
			this.test_virtual = __VIRTUAL__.test_virtual = __CLASS__CLASS2__.test_virtual = __CLASS__CLASS1__.test_virtual = function ()
			{
				//@line 310
				trace("Class3::test_virtual");
				//@line 311
			};
			//@line 314
			this.test = __VIRTUAL__.test = __CLASS__CLASS2__.test = __CLASS__CLASS1__.test = function ()
			{
				//@line 316
				trace("========================== Class3::test() (before super) ==========================");
				//@line 318
				trace("Class3::test::super.test()");
				//@line 320
				__CLASS__CLASS2__.__VIRTUAL__.test();
				//@line 322
				trace("========================== Class3::test() (after super) ==========================");
				//@line 324
				trace(__CLASS__CLASS2__.x);
				//@line 325
				trace(__CLASS__CLASS2__.__PROTECTED__.z);
				//@line 327
				__CLASS__CLASS1__.public_state.tick(0);
				//@line 328
				__CLASS__CLASS1__.__PROTECTED__.protected_state.tick(0);
				//@line 330
				trace("Class3::public_overload()                    = " + __CLASS__CLASS1__.public_overload());
				//@line 331
				trace("Class3::public_overload(arg1)                = " + __CLASS__CLASS1__.public_overload$1("arg1"));
				//@line 332
				trace("Class3::public_overload(arg1,arg2)           = " + __CLASS__CLASS1__.public_overload$2("arg1", "arg2"));
				//@line 333
				trace("Class3::protected_overload()                 = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload());
				//@line 334
				trace("Class3::protected_overload(arg1)             = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload$1("arg1"));
				//@line 335
				trace("Class3::protected_overload(arg1,arg2)        = " + __CLASS__CLASS1__.__PROTECTED__.protected_overload$2("arg1", "arg2"));
				//@line 336
				trace("Class3::public_function()                    = " + __CLASS__CLASS1__.public_function());
				//@line 337
				trace("Class3::protected_function()                 = " + __CLASS__CLASS1__.__PROTECTED__.protected_function());
				//@line 338
				trace("Class3::public_var                           = " + __CLASS__CLASS1__.public_var);
				//@line 339
				trace("Class3::protected_var                        = " + __CLASS__CLASS1__.__PROTECTED__.protected_var);
				//@line 340
				trace("Class3::public_property                      = " + __CLASS__CLASS1__.public_property);
				//@line 341
				trace("Class3::protected_property                   = " + __CLASS__CLASS1__.__PROTECTED__.protected_property);
				//@line 342
			};
			//@line 302
			this.Constructor = function ()
			{
				//@line 304
				trace("Class3::Constructor");
				//@line 305
			};
			__PDEFINE__(this, 'Constructor', __NOENUM__);
			this.Constructor();
			return this;
		}
		__Class3.prototype = new Class2("::arg1_from_Class3");
		return new __Class3();
	}
	Class3.__PRIVATE__ = {};
	Class3.__PROTECTED__ = {};
	//@line 30
	Class3.static_public_var = "";
	//@line 31
	Class3.__PRIVATE__.static_private_var = "";
	//@line 32
	Class3.__PROTECTED__.static_protected_var = "";
	//@line 39
	Class3.__PRIVATE__.__public_static_property = "";
	//@line 40
	Class3.__PRIVATE__.__private_static_property = "";
	//@line 41
	Class3.__PRIVATE__.__protected_static_property = "";
	//@line 138
	Class3.public_static_function = function (b)
	{
		return "Class1_public_static_function";
		return ""
	};
	//@line 139
	Class3.__PRIVATE__.private_static_function = function (b)
	{
		return "Class1_private_static_function";
		return ""
	};
	//@line 140
	Class3.__PROTECTED__.protected_static_function = function (b)
	{
		return "Class1_protected_static_function";
		return ""
	};
	//@line 221
	Object.defineProperty(Class3, 'public_static_property', {
		enumerable: true,
		//@line 223
		get: function ()
		{
			return Class3.__PRIVATE__.__public_static_property;
			return ""
		},
		//@line 224
		set: function (v)
		{
			Class3.__PRIVATE__.__public_static_property = v;
		}
	});
	//@line 227
	Object.defineProperty(Class3.__PRIVATE__, 'private_static_property', {
		enumerable: true,
		//@line 229
		get: function ()
		{
			return Class3.__PRIVATE__.__private_static_property;
			return ""
		},
		//@line 230
		set: function (v)
		{
			Class3.__PRIVATE__.__private_static_property = v;
		}
	});
	//@line 233
	Object.defineProperty(Class3.__PROTECTED__, 'protected_static_property', {
		enumerable: true,
		//@line 235
		get: function ()
		{
			return Class3.__PRIVATE__.__protected_static_property;
			return ""
		},
		//@line 236
		set: function (v)
		{
			Class3.__PRIVATE__.__protected_static_property = v;
		}
	});

