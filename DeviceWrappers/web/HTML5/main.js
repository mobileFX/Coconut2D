
////////////////////////////////////////////////////////////////////////////////////////////////////
function main()
{
	window.deviceZoom = 1.0;

	window.scrollTo(0,0);

	// Disable Window Scrolling
	document.ontouchmove = function(e)
	{
		__cancelEvent(e);
	};

	// Reposition window to (0,0)
	document.ontouchend = function(e)
	{
		try { window.scrollTo(0,0); } catch(e) {}
	};

	// Create a new Engine
	engine = new GameEngine();

	// Run !!
	requestAnimationFrame(tickAndPaint);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function tickAndPaint(time)
{
	requestAnimationFrame(tickAndPaint);
	engine.run(time);
}

/////////////////////////////////////////////////////////////////////////////////////
function wait_iframe_to_resize()
{
	window.setTimeout(main, 2000);
}

/////////////////////////////////////////////////////////////////////////////////////
window.addEventListener("load", wait_iframe_to_resize);
