Coconut 2D
==========

The basic idea of Coconut 2D is that you write your games and apps once in <B>JavaScript</B> and <B>WebGL</B>, and you get them to run on any <B>HTML5 Browser</B>, <B>iOS</B> or <B>Android</B> device.

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
                                                                                                           
Coconut 2D consists of a set of <B>JavaScript WebGL Frameworks</B> for building animations games and applications, and a cross-platform native Common Runtime Layer for iOS and Android that emulate basic HTML5 DOM and the WebGL API. Coconut 2D is partitioned to the following layers:

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

CocoRuntime
===========
<B>Coconut 2D Common Runtime Layer</B> is a cross platform C++ runtime that merges a JavaScript VM (Apple JavaScript Core for iOS and Google V8 for Android) with OpenGL ES, exposing a WebGL API in the JavaScript Global object. CRL architecture consists of a Device Wrapper class that interfaces with the actual hardware and a set of Core APIs that expose HTML5 APIs (WebGL, Audio, etc.) to the JavaScript environment. CRL is based on other open source libraries such as OpenAL and Vorbis OGG for audio, Freeface2 for fonts, PNGLib and JPEGLib for images and textures, and Curl for HTTP. 

CocoScript
==========
CocoScript sums Coconut 2D Core JavaScript and WebGL Frameworks:

* <B>Coconut 2D Animation Framework</B> encapsulates the core classes for creating complex timeline-driven animations programmatically, using a simplified Object Model that consists of the following core classes: <B>CocoScene</B> class implements the top-level animation resources container and renderer, <B>CocoClip</B> implements a simple animated entity, <B>CocoTimeline</B> implements an animation timeline and frame interpolation methods, <B>CocoKeyFrame</B> implements a keyframe descriptor and other helper classes such as <B>CocoImage</B>, <B>CocoSound</B>, <B>CocoMatrix</B>, etc.

* <B>Coconut 2D Game Framework - WIP</B> encapsulates the core classes for creating 2D games such as <B>CocoTiledLayer</B> for implementing Tiled Layers of reusable textures and and <B>CocoSprite</B> that implements basic sprite behaviours (Player, Enemy, Bullet, Trap, Switch, Container, etc).

* <B>Coconut 2D UI (Application) Framework - WIP</B> encapsulates core classes for User Interface programming (UIView, UIControlView, UILabelView, UIButtonView, UICheckboxView, UITextView, UIPickerView, UIPageView, UIScrollView, UITabView, UINavbarView).

CocoScript Frameworks are written in JavaScript++, a programming language written entirely in JavaScript by Roger Poon that compiles JavaScript++ code to pure JavaScript. JavaScript++ offers familiar C-style language syntax and modern language features such as classes, type safety and much more, with almost no learning curve through an extended ES3 grammar.


Contributors
============
* Elias Politakis
* George Mathiudakis
* Irida Kalostipi

Credits
=======
Special thanks to Roger Poon for his support on porting CocoScript Framework to JavaScript++.






