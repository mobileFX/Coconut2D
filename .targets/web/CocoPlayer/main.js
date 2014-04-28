 "#export web"
"#include Constants.jspp";

include("payload.js");

"#ignore_errors_begin";
var global = this;
var engine = null;
var gl = null;
global.EventTarget = function() {};
global.window = new HTMLWindow();
global.document = window.document;
"#ignore_errors_end";

////////////////////////////////////////////////////////////////////////////////////////////////////
// Extensions of JavaScript Array and Object classes to match C++ Vector and Map.

Object.defineProperty(Array.prototype, "size", { value: function()
{
	return this.length;
}});

Object.defineProperty(Array.prototype, "clear", { value: function()
{
	while(this.length) { this.pop(); }
}});

Object.defineProperty(String.prototype, "size", { value: function()
{
	return this.length;
}});

////////////////////////////////////////////////////////////////////////////////////////////////////
function main()
{

	debugger;

	var obj1 = new Class1("Class1_arg1","Class1_arg2");
	obj1.test();
	trace(Class1.public_static_function());

	var obj2 = new Class2("Class2_arg1");
	obj2.test();
	trace(Class2.public_static_function());

	var obj3 = new Class3();
	obj3.test();
	trace(Class3.public_static_function());


	// Create a CANVAS element in document BODY.
	var canvas = document.body.appendChild(document.createElement("canvas"));
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	// Get WebGL context
	gl = canvas.getContext("webgl");
	gl.clearColor(1.0, 1.0, 1.0, 1.0);

	// Create a new Engine
	engine = new GameEngine();

	// Run
	requestAnimationFrame(tickAndPaint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function tickAndPaint(time)
{
	engine.run(gl, time);
	requestAnimationFrame(tickAndPaint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
window.addEventListener("load", main);


