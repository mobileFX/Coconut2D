//@compile{true}
//@include{Coconut.js}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Simulate HTML5 DOM.
if(!global.window)
{
	global.window = new HTMLWindow();
	global.document = window.document;
}

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
	engine.tick(gl, time);
	requestAnimationFrame(tickAndPaint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
window.addEventListener("load", main);
