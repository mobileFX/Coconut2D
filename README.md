## Coconut 2D
The basic idea of Coconut 2D is that you write your games and apps once in <B>JavaScript</B> and <B>WebGL</B>, and you get them to run on any <B>HTML5 Browser</B>, <B>iOS</B> or <B>Android</B> device.
### [Click Here for Live Demo](http://yiamiyo.no-ip.org/coconut/demo2.html)

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
<B>Coconut 2D Common Runtime Layer (CRL)</B> is a cross platform C++ runtime that merges a JavaScript VM (Apple JavaScript Core for iOS and Google V8 for Android) with OpenGL ES, exposing a WebGL API in the JavaScript Global object. CRL architecture consists of a Device Wrapper class that interfaces with the actual hardware and a set of Core APIs that expose HTML5 APIs (WebGL, Audio, etc.) to the JavaScript environment. CRL is based on other open source libraries such as OpenAL and Vorbis OGG for audio, Freetype2 for fonts, PNG Lib and JPEG Lib for images and textures, and Curl for HTTP. In the future this will also support Box2D Physics.

## CocoScript
CocoScript sums Coconut 2D Core JavaScript and WebGL Frameworks:

* <B>Coconut 2D Animation Framework</B> encapsulates the core classes for creating complex timeline-driven animations programmatically, using a simplified Object Model that consists of the following core classes: <B>CocoScene</B> class implements the top-level animation resources container and renderer, <B>CocoClip</B> implements a simple animated entity, <B>CocoTimeline</B> implements an animation timeline and frame interpolation methods, <B>CocoKeyFrame</B> implements a keyframe descriptor and other helper classes such as <B>CocoImage</B>, <B>CocoSound</B>, <B>CocoMatrix</B>, etc.

* <B>Coconut 2D Game Framework - WIP</B> encapsulates the core classes for creating 2D games such as <B>CocoTiledLayer</B> for implementing Tiled Layers of reusable textures and and <B>CocoSprite</B> that implements basic sprite behaviours (Player, Enemy, Bullet, Trap, Switch, Container, etc).

* <B>Coconut 2D UI (Application) Framework - WIP</B> encapsulates core classes for User Interface programming (UIView, UIControlView, UILabelView, UIButtonView, UICheckboxView, UITextView, UIPickerView, UIPageView, UIScrollView, UITabView, UINavbarView).

CocoScript Frameworks are written in JavaScript++, a programming language written entirely in JavaScript by Roger Poon that compiles JavaScript++ code to pure JavaScript. JavaScript++ offers familiar C-style language syntax and modern language features such as classes, type safety and much more, with almost no learning curve through an extended ES3 grammar.

## Getting Started
When coding JavaScript and HTML5 WebGL Games you typically write a State Machine Automaton (also called Game Engine) that creates a <b>HTML5 Canvas</b> element and renders the game by calling <b>requestAnimationFrame</b>.

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

Next, we need to play this Animation on screen. To do so we extend CocoScript <B>GameEngine</B> and <B>GameEngineState</B> classes like this:

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

## Using Coconut 2D CRL without CocoScript

It is also easy to use native WebGL without CocoScript Frameworks, using plain JavaScrpt and some HTML5 prototypes for binding JavaScript with CRL.

### [Click Here for Live Demo](http://yiamiyo.no-ip.org/coconut/demo1.html)  

(The code works as is over the Coconut 2D CRL for Android and iOS with the exact same result as in your browser!)

```javascript
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function makeProgram(gl, vs, fs)
{
	var vshader = gl.createShader(gl.VERTEX_SHADER);
	var fshader = gl.createShader(gl.FRAGMENT_SHADER);
	gl.shaderSource(vshader, vs);
	gl.shaderSource(fshader, fs);
	gl.compileShader(vshader);
	gl.compileShader(fshader);
	var program = gl.createProgram();
	gl.attachShader(program, vshader);
	gl.attachShader(program, fshader);
	gl.linkProgram(program);
	return program;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function ortho(gl, left, right, bottom, top, near, far)
{
	var mat = [2 / (right - left), 0.0, 0.0, 0.0,
		                0.0, 2 / (top - bottom), 0.0, 0.0,
		                0.0, 0.0, -2 / (far - near), 0.0, -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0
		            ];
	gl.uniformMatrix4fv(gl.GLSLuProjMat, false, new Float32Array(mat));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Texture(gl, src, cb)
{
	var t = this;
	t.img = new Image();
	t.img.onload = function ()
	{
		t.tex = gl.createTexture();
		gl.bindTexture(gl.TEXTURE_2D, t.tex);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, t.img);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.bindTexture(gl.TEXTURE_2D, null);
		cb(t);
	}
	this.img.src = src;
}
Texture.prototype.img = null;
Texture.prototype.tex = null;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
function Sprite(gl, texture, width, height)
{
	var t = this;
	t.texture = texture;

	t.vx = 0.0;
	t.vy = 0.0;
	t.mat = new Float32Array([1.0, 0.0, 0.0, 1.0,
		                0.0, 1.0, 0.0, 1.0,
		                0.0, 0.0, 1.0, 1.0,
		                0.0, 0.0, 0.0, 1.0
		            ]);

	t.w2 = width / 2;
	t.h2 = height / 2;
	t.data = new Float32Array([0.0, 0.0, -t.w2, -t.h2,
		                0.0, 1.0, -t.w2, t.h2,
		                1.0, 0.0, t.w2, -t.h2,
		                1.0, 1.0, t.w2, t.h2
		            ]);

	t.color = new Float32Array([1.0, 1.0, 1.0, 1.0]);

	t.frameCur = 0;
	t.framePast = 0.0;
	t.updateData = false;
	t.sprSize = new Float32Array([width / texture.img.naturalWidth, height / texture.img.naturalHeight]);

	t.buffer = gl.createBuffer();
}

Sprite.prototype.texture = null;

Sprite.prototype.frames = new Float32Array([0, 0,
	        1, 0,
	        2, 0,
	        3, 0,
	        4, 0,
	        5, 0,
	        6, 0,
	        7, 0,
	        8, 0
	    ]);
Sprite.prototype.frameTime = 75;
Sprite.prototype.frameNum = 9;

Sprite.prototype.tick = function (t_dif)
{
	var total = t_dif + this.framePast;
	var f_diff = Math.floor(total / this.frameTime);
	this.frameCur += f_diff;
	this.frameCur %= this.frameNum;
	this.framePast = total % this.frameTime;

	var posx = this.mat[12];
	var posy = this.mat[13];
	posx += t_dif * this.vx;
	while (posx + this.w2 > innerWidth || posx - this.w2 < 0)
	{
		this.vx = -this.vx;
		if (posx + this.w2 > innerWidth) posx -= posx + this.w2 - innerWidth;
		else if (posx - this.w2 < 0) posx = -posx + 2 * this.w2;
	}
	if (this.vx > 0 && this.data[0] > 0.5)
	{
		this.data[0] = 0.0;
		this.data[4] = 0.0;
		this.data[8] = 1.0;
		this.data[12] = 1.0;
		this.updateData = true;
	}
	else if (this.vx < 0 && this.data[8] > 0.5)
	{
		this.data[0] = 1.0;
		this.data[4] = 1.0;
		this.data[8] = 0.0;
		this.data[12] = 0.0;
		this.updateData = true;
	}

	posy += t_dif * this.vy;
	while (posy + this.h2 > innerHeight || posy - this.h2 < 0)
	{
		this.vy = -this.vy;
		if (posy + this.h2 > innerHeight) posy -= posy + this.h2 - innerHeight;
		else if (posy - this.h2 < 0) posy = -posy + 2 * this.h2;
	}
	this.mat[12] = posx;
	this.mat[13] = posy;
}

Sprite.prototype.draw = function (gl)
{
	gl.uniform2fv(gl.GLSLuSprSize, this.sprSize);
	gl.uniform2f(gl.GLSLuSprFrame, this.frames[this.frameCur * 2], this.frames[this.frameCur * 2 + 1]);
	gl.uniformMatrix4fv(gl.GLSLuSprMat, false, this.mat);
	gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
	gl.bufferData(gl.ARRAY_BUFFER, this.data, gl.DYNAMIC_DRAW);
	gl.vertexAttribPointer(gl.GLSLiTexCoords, 2, gl.FLOAT, false, 4 * Float32Array.BYTES_PER_ELEMENT, 0);
	gl.vertexAttribPointer(gl.GLSLiVecCoords, 2, gl.FLOAT, false, 4 * Float32Array.BYTES_PER_ELEMENT, 2 * Float32Array.BYTES_PER_ELEMENT);
	gl.bindTexture(gl.TEXTURE_2D, this.texture.tex);
	gl.uniform1i(gl.GLSLuSampler, 0);
	gl.uniform4fv(gl.GLSLuColor, this.color);
	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
window.addEventListener("load", function ()
{
	var vs_str = "attribute vec2 iVecCoords;attribute vec2 iTexCoords;uniform mat4 uProjMat;uniform mat4 uMVMat;uniform mat4 uSprMat;uniform vec2 uSprSize;uniform vec2 uSprFrame;varying vec2 pTexCoord;void main(void){ mat4 T = mat4(1.0); T[3].xyz = uSprMat[3].xyz;  mat4 R = mat4(1.0); R[0].xyz = uSprMat[0].xyz; R[1].xyz = uSprMat[1].xyz; R[2].xyz = uSprMat[2].xyz;  mat4 S = mat4(1.0); S[0].x = uSprMat[0].w; S[1].y = uSprMat[1].w; S[2].z = uSprMat[2].w; gl_Position = uProjMat * uMVMat * T * R * S * vec4(iVecCoords, 0.0, 1.0); pTexCoord = vec2(((iTexCoords.x + uSprFrame.x) * uSprSize.x), ((iTexCoords.y + uSprFrame.y) * uSprSize.y));}";
	var fs_str = "precision mediump float; uniform sampler2D uSampler;uniform vec4 uColor;varying vec2 pTexCoord;void main(void){ gl_FragColor = vec4(texture2D(uSampler, pTexCoord).r * uColor.r, texture2D(uSampler, pTexCoord).g * uColor.g, texture2D(uSampler, pTexCoord).b * uColor.b, texture2D(uSampler, pTexCoord).a * uColor.a);}";

	var c = document.body.appendChild(document.createElement("canvas"));
	c.width = innerWidth;
	c.height = innerHeight;
	var gl = c.getContext("experimental-webgl");
	gl.enable(gl.BLEND);
	gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);

	var glp = glu.makeProgram(gl, vs_str, fs_str);
	gl.useProgram(glp);
	gl.GLSLiVecCoords = gl.getAttribLocation(glp, "iVecCoords");
	gl.GLSLiTexCoords = gl.getAttribLocation(glp, "iTexCoords");
	gl.GLSLuProjMat = gl.getUniformLocation(glp, "uProjMat");
	gl.GLSLuMVMat = gl.getUniformLocation(glp, "uMVMat");
	gl.GLSLuSprMat = gl.getUniformLocation(glp, "uSprMat");
	gl.GLSLuSprSize = gl.getUniformLocation(glp, "uSprSize");
	gl.GLSLuSprFrame = gl.getUniformLocation(glp, "uSprFrame");
	gl.GLSLuSampler = gl.getUniformLocation(glp, "uSampler");
	gl.GLSLuColor = gl.getUniformLocation(glp, "uColor");
	gl.enableVertexAttribArray(gl.GLSLiTexCoords);
	gl.enableVertexAttribArray(gl.GLSLiVecCoords);

	var MVMat = new Float32Array([1.0, 0.0, 0.0, 0.0,
		                0.0, 1.0, 0.0, 0.0,
		                0.0, 0.0, 1.0, 0.0,
		                0.0, 0.0, 0.0, 1.0]);

	gl.uniformMatrix4fv(gl.GLSLuMVMat, false, MVMat);
	gl.uniform4fv(gl.GLSLuColor, new Float32Array([1.0, 1.0, 1.0, 1.0]));
	ortho(gl, 0.0, innerWidth, innerHeight, 0.0, -1.0, 1.0);
	gl.clearColor(0.0, 0.0, 1.0, 1.0);
	var Scale = 1.0;
	var Rotation = 0.0;
	var Textures = new Array();

	Textures["./assets/metal_slug_mdpi.png"] = new Texture(gl, "./assets/metal_slug_mdpi.png", function (t)
	{
		var Sprites = new Array();
		for (var i = 50; i--;)
		{
			var S = new Sprite(gl, t, 36, 41);
			S.vx = Math.random() / 4 + 0.1;
			S.vy = 0.0;
			S.mat[12] = Math.random() * innerWidth;
			S.mat[13] = Math.random() * innerHeight;
			Sprites.push(S);
		}

		window.addEventListener("touchstart", function (e)
		{
			for (var i = e.changedTouches.length; i--;)
			{
				var removed = false;
				for (var t = Sprites.length; t--;)
				if (Sprites[t].mat[12] - Sprites[t].w2 < e.changedTouches.item(i).screenX && Sprites[t].mat[12] + Sprites[t].w2 > e.changedTouches.item(i).screenX && Sprites[t].mat[13] - Sprites[t].h2 < e.changedTouches.item(i).screenY && Sprites[t].mat[13] + Sprites[t].h2 > e.changedTouches.item(i).screenY)
				{
					Sprites.splice(t, 1);
					removed = true;
				}
				if (!removed)
				{
					var S = new Sprite(gl, Textures["./assets/metal_slug_mdpi.png"], 36, 41);
					S.vx = Math.random() / 4 + 0.1;
					S.vy = 0.0;
					S.mat[12] = e.changedTouches.item(i).screenX;
					S.mat[13] = e.changedTouches.item(i).screenY;
					Sprites.push(S);
				}
			}
		});

		window.addEventListener("touchmove", function (e)
		{
		});

		window.addEventListener("touchend", function (e)
		{
			for (var i = e.changedTouches.length; i--;)
			wt.setText("Hello world(" + localStorage.i + ")!");
		});

		window.addEventListener("touchcancel", function (e)
		{
		});

		var last_t = 0;

		function refresh(t)
		{
			var t_dif = t - last_t;
			last_t = t;

			for (var i = Sprites.length; i--;)
			Sprites[i].tick(t_dif);

			gl.clearColor(0, 0, 1, 1);
			gl.clear(gl.COLOR_BUFFER_BIT);

			for (var i = Sprites.length; i--;)
			Sprites[i].draw(gl);

			requestAnimationFrame(refresh);
		}
		requestAnimationFrame(refresh);
	});
});
```






Contributors
============
* Elias Politakis
* George Mathioudakis (YiamiYo)
* Irida Kalostipi

Credits
=======
Special thanks to Roger Poon for his support on porting CocoScript Framework to JavaScript++.






