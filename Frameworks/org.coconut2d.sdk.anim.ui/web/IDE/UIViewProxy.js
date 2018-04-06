include("payload.js");

var __UIView_width = 0;
var __UIView_height = 0;
var __UIView_scene = null;
var __UIView_canvas = null;
var __UIView_ctx = null;

////////////////////////////////////////////////////////////////////////////////////////////////////
function __UIViewProxy_create_scene(js)
{
	try
	{
		// Dispose existing scene
		if(__UIView_scene)
		{
			delete __UIView_ctx;
			delete __UIView_canvas;
			delete __UIView_scene;
		}

		// Create new dummy scene
		__UIView_scene = new CocoScene();

		// Set properties
		__UIView_scene.__sceneName 			= '___UIView_Scene';
		__UIView_scene.__fps 				= js.Scene.__fps;
		__UIView_scene.__view_width 		= js.Scene.__view_width;
		__UIView_scene.__view_height 		= js.Scene.__view_height;
		__UIView_scene.__view_pixel_ratio 	= js.Scene.__view_pixel_ratio;

		// Load images
		for(var key in js.Images)
		{
			var image = js.Images[key];
			var img = __UIView_scene.newResourceImage(key, './assets/images/');

			img.textureViewWidth = image.textureViewWidth;
			img.textureViewHeight = image.textureViewHeight;
			img.textureViewScaleX = image.textureViewScaleX;
			img.textureViewScaleY = image.textureViewScaleY;
			img.textureGrid = image.textureGrid;

			var resolution = new CocoImageResolution(image.url, image.pixelRatio, image.textureWidth, image.textureHeight, 0, 0, null, null, 0, 0, eval(image.skin));
			img.addResolution(resolution);
		}

		// Prepare scene (create textures)
		__UIView_scene.prepare(engine.__ctx);

		// Create an off-screen canvas for rendering controls
		__UIView_width = engine.device.pixelsWidth;
		__UIView_height = engine.device.pixelsHeight;
		__UIView_canvas = CocoGraphics.NewCanvas(__UIView_width, __UIView_height, false);
		__UIView_ctx = __UIView_canvas.getContext("2d");
	}
	catch(e)
	{
		trace("ERROR: Failed to create Design-time Rendering Context. " + e + "\n" + e.stack);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function __UIViewProxy_get_defaults(Class)
{
	try
	{
		// Execute constructor
		var ctl = new Class(Class.__className);

		// Set view scene and force view to re-apply defaults
		ctl.__scene = __UIView_scene;
		ctl.Defaults();

		// Get control properties
		var prop, value;
		var defaults = {};
		var published = Class.__PUBLISHED__.split(",");
		for(var i=0, L=published.length; i<L; i++)
		{
			prop = published[i];
			key = prop.split(".");
			key = key[key.length-1];
			value = ctl[key];

			// Convert integers to hex
			if(value && parseInt(value)==value && (value % 1 === 0) && value>65535)
				value = "0x" + Number(value).toString(16).toUpperCase();

			defaults[prop] = value;
		}

		// Get control runtime image
		var data = JSON.stringify(defaults);
		delete ctl;

		return data;
	}
	catch(e)
	{
		trace("ERROR: Failed to get UIView Proxy Control Defaults. " + e + "\n" + e.stack);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function __UIViewProxy_create_texture(js)
{
	try
	{
		// Get constructor
		var Constructor = global[js.ClassName];

		// Execute constructor
		var ctl = new Constructor(js.InstanceName);
		ctl.__scene = __UIView_scene;
		ctl.Defaults();

		// Set control properties
		for(item in js.Properties)
		{
			if(item=="Width")
				ctl.__width = js.Properties[item];

			else if(item=="Height")
				ctl.__height = js.Properties[item];

			else
				ctl[item] = js.Properties[item];
		}

		// Compose control and copy its runtime pixels to a safearray
		__UIView_ctx.clearRect(0, 0, __UIView_width, __UIView_height);
		ctl.__IDE_Compose(__UIView_ctx, js.Buffer);

		// Dispose control
		delete ctl;
	}
	catch(e)
	{
		trace("ERROR: Failed to create UIView Proxy Control Texture. " + e + "\n" + e.stack);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
function main()
{
	engine = new CocoEngine();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
window.addEventListener("load", main);
