////////////////////////////////////////////////////////////////////////////////////////////////////

var global = this;
var engine = null;
var gl = null;

if(global["EventTarget"]) global.EventTarget = function() {};
global.trace = function(msg) { console.log(msg); };
Image.prototype.load = function(src) { this.src = src; };
function State(){};

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

////////////////////////////////////////////////////////////////////////////////////////////////////
function main()
{
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
