## Coconut 2D
The basic idea of Coconut 2D is that you write your games and apps once in <B>JavaScript</B> and <B>WebGL</B>, and you get them to run on any <B>HTML5 Browser</B>, <B>iOS</B> or <B>Android</B> device.

Coconut 2D consists of a set of <B>JavaScript WebGL Frameworks</B> for building animations games and applications, and a cross-platform native Common Runtime Layer for iOS and Android that emulate basic HTML5 DOM and the WebGL API. 

Coconut 2D is partitioned to the following layers:

    +---------------------------------------------------+
    |       Coconut 2D UI (Application) Framework       |
    +---------------------------------------------------+
    |            Coconut 2D Game Framework              |
    +---------------------------------------------------+
    |         Coconut 2D Animation Framework            |
    +---------------------------------------------------+
    |                                                   |
    |                    CocoScript                     |
    |       (Typed Object Oriented JavaScript)          |  CocoScript  
    |                                                   |
    +---------------------------------------------------+--------------  
    |                                                   | 
    |            HTML5 & WebGL & JavaScript             |  CocoRuntime  
    |                                                   |
    +-----------------+----------------+----------------+
    |                 |                |                |
    |       iOS       |    Android     |     HTML5      |  
    |                 |                |    Browsers    |
    +-----------------+----------------+----------------+
    |    OpenGL ES    |   OpenGL ES    |     Chrome     |
    | JavaScript Core |   Google V8    |     Firefox    |
    |                 |                |     Safari     |
    +-----------------+----------------+----------------+

## CocoRuntime
<B>Coconut 2D Common Runtime Layer</B> is a cross platform C++ runtime that merges a JavaScript VM (Apple JavaScript Core for iOS and Google V8 for Android) with OpenGL ES, exposing a WebGL API in the JavaScript Global object. CRL architecture consists of a Device Wrapper class that interfaces with the actual hardware and a set of Core APIs that expose HTML5 APIs (WebGL, Audio, etc.) to the JavaScript environment. CRL is based on other open source libraries such as OpenAL and Vorbis OGG for audio, Freeface2 for fonts, PNGLib and JPEGLib for images and textures, and Curl for HTTP. 

## CocoScript
CocoScript sums Coconut 2D Core JavaScript and WebGL Frameworks:

* <B>Coconut 2D Animation Framework</B> encapsulates the core classes for creating complex timeline-driven animations programmatically, using a simplified Object Model that consists of the following core classes: <B>CocoScene</B> class implements the top-level animation resources container and renderer, <B>CocoClip</B> implements a simple animated entity, <B>CocoTimeline</B> implements an animation timeline and frame interpolation methods, <B>CocoKeyFrame</B> implements a keyframe descriptor and other helper classes such as <B>CocoImage</B>, <B>CocoSound</B>, <B>CocoMatrix</B>, etc.

* <B>Coconut 2D Game Framework - WIP</B> encapsulates the core classes for creating 2D games such as <B>CocoTiledLayer</B> for implementing Tiled Layers of reusable textures and and <B>CocoSprite</B> that implements basic sprite behaviours (Player, Enemy, Bullet, Trap, Switch, Container, etc).

* <B>Coconut 2D UI (Application) Framework - WIP</B> encapsulates core classes for User Interface programming (UIView, UIControlView, UILabelView, UIButtonView, UICheckboxView, UITextView, UIPickerView, UIPageView, UIScrollView, UITabView, UINavbarView).

CocoScript Frameworks are written in JavaScript++, a programming language written entirely in JavaScript by Roger Poon that compiles JavaScript++ code to pure JavaScript. JavaScript++ offers familiar C-style language syntax and modern language features such as classes, type safety and much more, with almost no learning curve through an extended ES3 grammar.

## Getting Started
When coding JavaScript and HTML5 WebGL Games you typically write a State Machine Automaton (also called Game Engine) that creates a <b>HTML5 Canvas</b> element and renders the game by calling <b>requestAnimationFrame</b>.

[Live Demo](http://yiamiyo.no-ip.org/coconut/)

```javascript

//@compile{true}																						   
//@depends{Coconut.js}                                                                                     
                                                                                                           
var engine = null;                                                                                         
var gl = null;                                                                                             
var global = this;                                                                                         
                                                                                                           
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
                                                                                                           
```  

## CocoScript Animation Example
The following code demonstrates an Animation class that extends the CocoScene class, loads some PNG images with texture and spritesheet information into CocoImage objects, and creates a timeline-driven animation using CocoClip objects.

```javascript
//@compile{true}
//@depends{Coconut.js,CocoScene.jspp}

class Animation1 : CocoScene
{
	public function Constructor()
	{
		__sceneName = 'Animation1';

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// CocoImage Symbols
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		// Symbol Image: imgSparrow
		//====================================================================================================
		var imgSparrow:CocoImage = newResourceImage('imgSparrow', './assets/images/Sparrow.png');
		{
			imgSparrow.dpi = 0;
			imgSparrow.textureCellWidth = 48;
			imgSparrow.textureCellHeight = 48;
			imgSparrow.textureGrid = new Float32Array([0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,1,0,1,1,1,2,1,3,1,4,1,5,1,6,1,7,2,0,2,1,2,2,2,3,2,4,2,5,2,6,2,7,3,0,3,1,3,2,3,3,3,4,3,5,3,6,3,7,4,0,4,1,4,2,4,3,4,4,4,5,4,6,4,7,5,0,5,1,5,2,5,3,5,4,5,5,5,6,5,7,6,0,6,1,6,2,6,3]);
			imgSparrow.sequences = {
				"Fly": new CocoSequence([22,23,24]),
				"Fire": new CocoSequence([25,26,27,28,29,30,31,32,33,34,35]),
				"Die": new CocoSequence([37,38,39,40,41,42,41,42,41,42]),
				"Eat": new CocoSequence([0,44,44,45,45,46,46,47,47]),
				"Burb": new CocoSequence([0,48,48,48,49,49,49,48,48,48,49,49,49,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51,50,51]),
				"Borred": new CocoSequence([0,1,2,1,0]),
				"Jump": new CocoSequence([10,11,12,13,12,13,12,13,12,13,12,13,12,13,12,13,12,13]),
				"Walk": new CocoSequence([3,4,5,6,7,8,9]),
				"Fall": new CocoSequence([14,15]),
				"Happy": new CocoSequence([16,17,18,19,20,21])
			};
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// Scene Root Clip
		//////////////////////////////////////////////////////////////////////////////////////////////////////

		__root = new CocoClip();
		__root.__instanceName = 'root';
		__root.timeline.clear();
		__root.timeline.addKeyFrameEx(0, 1, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
		{
			var inst_Sparrow:CocoClip = new CocoClip();
			inst_Sparrow.__instanceName = 'inst_Sparrow';
			__root.addChild(inst_Sparrow);
			inst_Sparrow.timeline.clear();
			inst_Sparrow.timeline.addKeyFrameEx(0, 1, false, true, 29, 291, 1, 1, 0, 0, 0, 1);
			inst_Sparrow.timeline.addKeyFrameEx(100, 1, false, true, 450, 290, 1, 1, 0, 0, 0, 1);
			{
				var inst1:CocoClip = new CocoClip(imgSparrow, null, null);
				inst1.__instanceName = 'inst1';
				inst_Sparrow.addChild(inst1);
				inst1.timeline.clear();
				inst1.timeline.addKeyFrameEx(0, 1, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
				inst1.timeline.addKeyFrameEx(20, 1, false, true, 0, 0, 1, 1, 360, 0, 0, 1);
			}
		}
	}
}
```

And this is how the generated JavaScript code looks like:

```javascript
//@compile{false}
//@line 4
function Animation1()
{
	var __SUPER__;
	return ((function ()
	{
		var __CLASS1026__ = this,
			__PDEFINE__ = {}.constructor.defineProperty,
			__NOENUM__ =
			{
				enumerable: false
			};
		if (typeof __PDEFINE__ != 'function') __PDEFINE__ = null; /*@cc_on @if(1)try{({}).constructor.defineProperty({},'x',{})}catch(e){__PDEFINE__=null}@end @*/
		this.__SUPER__ = __SUPER__;
		__PDEFINE__ && __PDEFINE__(this, '__SUPER__', __NOENUM__);
		this.__PROTECTED__ = {};
		__PDEFINE__ && __PDEFINE__(this, '__PROTECTED__', __NOENUM__);
		var __TMP38__ = __SUPER__,
			__TMP39__ = [];
		for (var __TMP37__ in __TMP38__) __TMP39__.push(__TMP37__ + '=__TMP38__.' + __TMP37__);
		__TMP39__.length && eval('var ' + __TMP39__.join() + ';');
		__TMP38__ = __SUPER__.__PROTECTED__;
		__TMP39__.length = 0;
		for (var __TMP37__ in __TMP38__)
		{
			__TMP39__.push(__TMP37__ + '=__TMP38__.' + __TMP37__);
			this.__PROTECTED__[__TMP37__] = __TMP38__[__TMP37__];
		}
		__TMP39__.length && eval('var ' + __TMP39__.join() + ';');
		this.Constructor = function ()
		{
			//@line 7
			//@line 8
			__CLASS1026__.__SUPER__.__sceneName = "Animation1";
			//@line 16
			var imgSparrow = __CLASS1026__.__SUPER__.newResourceImage("imgSparrow", "./assets/images/Sparrow.png");
			//@line 17
			{
				//@line 18
				imgSparrow.dpi = 0;
				//@line 19
				imgSparrow.textureCellWidth = 48;
				//@line 20
				imgSparrow.textureCellHeight = 48;
				//@line 21
				imgSparrow.textureGrid = new Float32Array([0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 2, 0, 2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 3, 0, 3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, 6, 3, 7, 4, 0, 4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 4, 7, 5, 0, 5, 1, 5, 2, 5, 3, 5, 4, 5, 5, 5, 6, 5, 7, 6, 0, 6, 1, 6, 2, 6, 3]);
				//@line 22
				imgSparrow.sequences =
				{
					//@line 23
					"Fly": new CocoSequence([22, 23, 24]),
					//@line 24
					"Fire": new CocoSequence([25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35]),
					//@line 25
					"Die": new CocoSequence([37, 38, 39, 40, 41, 42, 41, 42, 41, 42]),
					//@line 26
					"Eat": new CocoSequence([0, 44, 44, 45, 45, 46, 46, 47, 47]),
					//@line 27
					"Burb": new CocoSequence([0, 48, 48, 48, 49, 49, 49, 48, 48, 48, 49, 49, 49, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51, 50, 51]),
					//@line 28
					"Borred": new CocoSequence([0, 1, 2, 1, 0]),
					//@line 29
					"Jump": new CocoSequence([10, 11, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13]),
					//@line 30
					"Walk": new CocoSequence([3, 4, 5, 6, 7, 8, 9]),
					//@line 31
					"Fall": new CocoSequence([14, 15]),
					//@line 32
					"Happy": new CocoSequence([16, 17, 18, 19, 20, 21])
				};
			}
			//@line 40
			__CLASS1026__.__SUPER__.__root = new CocoClip;
			//@line 41
			__CLASS1026__.__SUPER__.__root.__instanceName = "root";
			//@line 42
			__CLASS1026__.__SUPER__.__root.timeline.clear();
			//@line 43
			__CLASS1026__.__SUPER__.__root.timeline.addKeyFrameEx(0, 1, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
			//@line 44
			{
				//@line 45
				var inst_Sparrow = new CocoClip;
				//@line 46
				inst_Sparrow.__instanceName = "inst_Sparrow";
				//@line 47
				__CLASS1026__.__SUPER__.__root.addChild(inst_Sparrow);
				//@line 48
				inst_Sparrow.timeline.clear();
				//@line 49
				inst_Sparrow.timeline.addKeyFrameEx(0, 1, false, true, 29, 291, 1, 1, 0, 0, 0, 1);
				//@line 50
				inst_Sparrow.timeline.addKeyFrameEx(100, 1, false, true, 450, 290, 1, 1, 0, 0, 0, 1);
				//@line 51
				{
					//@line 52
					var inst1 = new CocoClip(imgSparrow, null, null);
					//@line 53
					inst1.__instanceName = "inst1";
					//@line 54
					inst_Sparrow.addChild(inst1);
					//@line 55
					inst1.timeline.clear();
					//@line 56
					inst1.timeline.addKeyFrameEx(0, 1, false, true, 0, 0, 1, 1, 0, 0, 0, 1);
					//@line 57
					inst1.timeline.addKeyFrameEx(20, 1, false, true, 0, 0, 1, 1, 360, 0, 0, 1);
				}
			}
			return __CLASS1026__
		};
		__PDEFINE__ && __PDEFINE__(this, 'Constructor', __NOENUM__);
		return this
	}).call((function (o)
	{
		return (F.prototype = __SUPER__ = o, new F);

		function F()
		{
		}
	})(new CocoScene))).Constructor.apply(this, [].slice.call(arguments))
}
```

Next, we need to play this Animation on screen. To do so we extend CocoScript GameEngine and GameEngineState classes like this:

```javascript

class GameEngine : CocoEngine
{                               
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public function Constructor()
	{
		setState( new StateAnim() );
	}
}
```

```javascript
class StateAnim :CocoEngineState
{ 
	private var scene:Animation1;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public function Constructor()
	{
		scene = new Animation1();
	}                         
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	public function tick(engine:CocoEngine, gl:WebGLRenderingContext, time:Number)
	{
		super.tick(gl, time); 
		
		if(scene!=null)
		{
			if(!scene.resourceImagesLoaded())
			{
				// Wait images to load
			}
			else if(!scene.prepared())
			{
				// Prepare the scene		
				scene.prepare(gl);				
			}
			else
			{
				// Render the scene
				gl.clear(gl.COLOR_BUFFER_BIT);
				scene.tick(gl, time);				
			}
		}				
	}
}
```




Contributors
============
* Elias Politakis
* George Mathioudakis (YiamiYo)
* Irida Kalostipi

Credits
=======
Special thanks to Roger Poon for his support on porting CocoScript Framework to JavaScript++.






