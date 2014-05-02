
	======================================================================
	A. Defining a class and inheritance in plain JavaScript:
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
	B. Public / Private / Protected Members
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
	C. Static Members
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
	D. Virtual Methods
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
	E. Method Overloads
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



	Constructing the Class and then the object instance with the "new" operator is one thing. Running
	the object is another. We need to find an elaborate way of implementing private and protected
	entities such as vars, consts, functions, enums, properties, states, etc. We therefore need to
	define a __PRIVATE__ and a __PROTECTED__ bank in the inner class function for keeping class members
	in there. For static entities (vars, consts, functions, properties), we also define a __PRIVATE__
	and a __PROTECTED__ bank on the outer class function.

	Next we have to resolve runtime symbols, or in other words recognize jsdef.IDENTIFIER(s) and produce
	an access path. For example, when we type "this.walk()" in the class source code we need to resolve
	all the identifiers into their canonical form taking into account base clases, which could resolve to
	"__CLASS_DOG__.__CLASS_MAMAL__.__CLASS_ANIMAL__.walk()". Resolving identifiers is the most tricky
	bit of this compiler and the most time-consuming because it performs several lookups.


