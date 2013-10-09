//@compile{false}
//@include{Coconut.js}    
//@include{WebGL.js}

function makeProgram(gl, vs, fs)
{
	var vshader = gl.createShader(gl.VERTEX_SHADER);
	var fshader = gl.createShader(gl.FRAGMENT_SHADER);

	gl.shaderSource(vshader, vs);
	gl.shaderSource(fshader, fs);

	gl.compileShader(vshader);
	gl.compileShader(fshader);

	if (!gl.getShaderParameter(vshader, gl.COMPILE_STATUS)) alert(gl.getShaderInfoLog(vshader));
	if (!gl.getShaderParameter(fshader, gl.COMPILE_STATUS)) alert(gl.getShaderInfoLog(fshader));

	var program = gl.createProgram();
	gl.attachShader(program, vshader);
	gl.attachShader(program, fshader);
	gl.linkProgram(program);
	if (!gl.getProgramParameter(program, gl.LINK_STATUS)) alert(gl.getProgramInfoLog(program));

	return program;
}

function ortho(gl, left, right, bottom, top, near, far)
{
	var mat = [2 / (right - left), 0.0, 0.0, 0.0,
		                0.0, 2 / (top - bottom), 0.0, 0.0,
		                0.0, 0.0, -2 / (far - near), 0.0, -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0
		            ];
	gl.uniformMatrix4fv(gl.GLSLuProjMat, false, new Float32Array(mat));
}

function npo2(n)
{
	ret = 1;
	while (ret < n) ret *= 2;
	return ret;
}

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

function fxLinedText(str, width, height)
{
	this.str = str;
	this.width = width;
	this.height = height;
}

fxLinedText.prototype =
{
};

fxLinedText.prototype.str = "";
fxLinedText.prototype.width = 0;
fxLinedText.prototype.height = 0;

function fxWrappedText(gl, font, width, align)
{
	this.__gl = gl;
	this.font = font;
	this.width = width;
	this.height = this.font.height;
	this.minLineChars = Math.floor(this.width / this.font.maxAdvance);
	if (typeof align == "string") this.align = align;

	this.img = new ImageData(npo2(this.width), npo2(this.height));

	this.tex = gl.createTexture();
	gl.bindTexture(gl.TEXTURE_2D, this.tex);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, this.img);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
	gl.bindTexture(gl.TEXTURE_2D, null);

	this.mat = new Float32Array([1.0, 0.0, 0.0, 1.0,
		                0.0, 1.0, 0.0, 1.0,
		                0.0, 0.0, 1.0, 1.0,
		                0.0, 0.0, 0.0, 1.0
		            ]);

	this.w2 = this.width / 2;
	this.h2 = this.height / 2;
	this.data = new Float32Array([0.0, 0.0, 0.0, 0.0,
		                0.0, 1.0, 0.0, this.height,
		                1.0, 0.0, this.width, 0.0,
		                1.0, 1.0, this.width, this.height
		            ]);

	this.color = new Float32Array([0.0, 0.0, 0.0, 1.0]);

	this.sprSize = new Float32Array([this.width / this.img.width, this.height / this.img.height]);

	this.buffer = gl.createBuffer();
}

fxWrappedText.prototype =
{
};
fxWrappedText.prototype.__gl = null; //WebGLRenderingContext
fxWrappedText.prototype.img = null; //ImageData
fxWrappedText.prototype.tex = null; //WebGLTexture
fxWrappedText.prototype.mat = null; //Float32Array(4x4)
fxWrappedText.prototype.w2 = 0;
fxWrappedText.prototype.h2 = 0;
fxWrappedText.prototype.data = null; //Float32Array
fxWrappedText.prototype.color = null; //Float32Array(4)
fxWrappedText.prototype.sprSize = null; //Float32Array(2)
fxWrappedText.prototype.buffer = null; //WebGLBuffer
fxWrappedText.prototype.width = 0;
fxWrappedText.prototype.height = 0;
fxWrappedText.prototype.lines = [];
fxWrappedText.prototype.font = null; //fxFont
fxWrappedText.prototype.minLineChars = 0;
fxWrappedText.prototype.lineHeight = 1.0;
fxWrappedText.prototype.align = "left";

fxWrappedText.prototype.getHeight = function ()
{

	return this.lines.length * this.font.height * this.lineHeight;
};
fxWrappedText.prototype.setText = function (t)
{
	this.img.__buffer.clear();
	this.lines.length = 0;
	this.appendText(t);
};

fxWrappedText.prototype.appendText = function (t)
{
	var l = t.split("\n");
	for (var i = 0; i < l.length; i++) this.appendSingleLine(l[i]);
	this.update(this.__gl);
};

fxWrappedText.prototype.appendSingleLine = function (t)
{
	var tw = this.font.measureText(t);

	// if whole text fits in 1 line we'll go for that
	if (tw <= this.width) this.lines.push(new fxLinedText(t, tw, this.font.height));
	else while (t.length) // TODO: wrap correctly text that has no spaces and cannot fit in 1 line
	{
		// get at least minLineChars (the number of the widest character of font 1 line can fit)
		var s = t.substr(0, this.minLineChars);
		var sw = this.font.measureText(s);
		t = t.substr(this.minLineChars);
		tw -= sw;

		// search for spaces after minLineChars that can fit in 1 line
		do
		{
			var n = t.indexOf(" ") + 1;
			if (n)
			{
				var ns = t.substr(0, n);
				var w = this.font.measureText(ns);
				if (sw + w <= this.width)
				{
					sw += w;
					s += ns;
					t = t.substr(n);
					tw -= w;
				}
				else break;
			}
			else
			{
				if (sw + tw <= this.width)
				{
					sw += tw;
					s += t;
					t = "";
					tw = 0;
				}
				else break;
			}
		}
		while (t.length);
		this.lines.push(new fxLinedText(s, sw, this.font.height));
	}
}

fxWrappedText.prototype.update = function (gl)
{
	this.height = this.font.height * (this.lines.length + 1);
	this.h2 = this.height / 2;
	var nw = npo2(this.width);
	var nh = npo2(this.height);

	// Allocate new image only if the one we already have isn't enough
	if (this.img.width < nw || this.img.height < nh) this.img = new ImageData(nw, nh);

	var sx = 0.0;
	var dy = 0;
	switch (this.align)
	{
	case "left":
	case "start":
		sx = 0.0;
		break;
	case "right":
	case "end":
		sx = 1.0;
		break;
	case "center":
		sx = 0.5;
		break;
	}
	for (var i = 0; i < this.lines.length; i++)
	{
		this.font.fillText(this.img.__buffer, this.img.width, this.lines[i].str, (this.width - this.lines[i].width) * sx, dy);
		dy += this.font.height * this.lineHeight;
	}
	gl.bindTexture(gl.TEXTURE_2D, this.tex);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, this.img);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
	gl.bindTexture(gl.TEXTURE_2D, null);

	this.data[7] = this.data[15] = this.height;
	this.sprSize[1] = this.height / this.img.height;
};
fxWrappedText.prototype.draw = function (gl)
{
	gl.uniform2fv(gl.GLSLuSprSize, this.sprSize);
	gl.uniform2f(gl.GLSLuSprFrame, 0.0, 0.0);
	gl.uniformMatrix4fv(gl.GLSLuSprMat, false, this.mat);
	gl.bindBuffer(gl.ARRAY_BUFFER, this.buffer);
	gl.bufferData(gl.ARRAY_BUFFER, this.data, gl.DYNAMIC_DRAW);
	gl.vertexAttribPointer(gl.GLSLiTexCoords, 2, gl.FLOAT, false, 4 * Float32Array.BYTES_PER_ELEMENT, 0);
	gl.vertexAttribPointer(gl.GLSLiVecCoords, 2, gl.FLOAT, false, 4 * Float32Array.BYTES_PER_ELEMENT, 2 * Float32Array.BYTES_PER_ELEMENT);
	gl.bindTexture(gl.TEXTURE_2D, this.tex);
	gl.uniform1i(gl.GLSLuSampler, 0);
	gl.uniform4fv(gl.GLSLuColor, this.color);
	gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
}

window.addEventListener("load", function ()
{
	var vs_str = "attribute vec2 iVecCoords;attribute vec2 iTexCoords;uniform mat4 uProjMat;uniform mat4 uMVMat;uniform mat4 uSprMat;uniform vec2 uSprSize;uniform vec2 uSprFrame;varying vec2 pTexCoord;void main(void){ mat4 T = mat4(1.0); T[3].xyz = uSprMat[3].xyz;  mat4 R = mat4(1.0); R[0].xyz = uSprMat[0].xyz; R[1].xyz = uSprMat[1].xyz; R[2].xyz = uSprMat[2].xyz;  mat4 S = mat4(1.0); S[0].x = uSprMat[0].w; S[1].y = uSprMat[1].w; S[2].z = uSprMat[2].w; gl_Position = uProjMat * uMVMat * T * R * S * vec4(iVecCoords, 0.0, 1.0); pTexCoord = vec2(((iTexCoords.x + uSprFrame.x) * uSprSize.x), ((iTexCoords.y + uSprFrame.y) * uSprSize.y));}";
	var fs_str = "/*precision mediump float; */uniform sampler2D uSampler;uniform vec4 uColor;varying vec2 pTexCoord;void main(void){ gl_FragColor = vec4(texture2D(uSampler, pTexCoord).r * uColor.r, texture2D(uSampler, pTexCoord).g * uColor.g, texture2D(uSampler, pTexCoord).b * uColor.b, texture2D(uSampler, pTexCoord).a * uColor.a);}";

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
		                0.0, 0.0, 0.0, 1.0
		    ]);

	gl.uniformMatrix4fv(gl.GLSLuMVMat, false, MVMat);
	gl.uniform4fv(gl.GLSLuColor, new Float32Array([1.0, 1.0, 1.0, 1.0]));
	//alert("(" + innerWidth + ", " + innerHeight + ")");
	ortho(gl, 0.0, innerWidth, innerHeight, 0.0, -1.0, 1.0);
	gl.clearColor(0.0, 0.0, 1.0, 1.0);
	var Scale = 1.0;
	var Rotation = 0.0;
	var Textures = new Array();
	alert("localStorage.i = " + localStorage.i);
    if(!localStorage.i) localStorage.i = "0";
	Textures["./assets/images/metal_slug_mdpi.png"] = new Texture(gl, "./assets/images/metal_slug_mdpi.png", function (t)
	{
		var clkRight = new Audio("./assets/sounds/Powerup.ogg");
		var clkWrong = new Audio("./assets/sounds/RobotNoise.ogg");
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

		
		//var font = new fxFont(40, "blkchcry", " Helowrd!0123456789()");
        //var wt = new fxWrappedText(gl, font, innerWidth, "right");
        //wt.setText("Hello world(" + localStorage.i + ")!");
        /*
		var font2 = new CocoFont(20, "calibri", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()/.,?><';\":]|[}{\\}]`~-");
		var wt2 = new fxWrappedText(gl, font2, innerWidth, "center");
		wt2.setText("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789|[]{}\nThis field is simply used to compute a default line spacing (i.e., the baseline-to-baseline distance) when writing text with this font.\n\nNote that it usually is larger than the sum of the ascender and descender taken as absolute values.\n\nThere is also no guarantee that no glyphs extend above or below subsequent baselines when using this distance.");
		wt2.mat[13] = wt.height - wt.font.height;
		wt2.color = new Float32Array([1.0, 1.0, 1.0, 1.0]);
		*/

		window.addEventListener("touchstart", function (e)
		{
			//alert("touchstart(" + e.touches.length + ", " + e.changedTouches.length + ")");
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
					clkWrong.play();
					var S = new Sprite(gl, Textures["./assets/images/metal_slug_mdpi.png"], 36, 41);
					S.vx = Math.random() / 4 + 0.1;
					S.vy = 0.0;
					S.mat[12] = e.changedTouches.item(i).screenX;
					S.mat[13] = e.changedTouches.item(i).screenY;
					Sprites.push(S);
				}
				else clkRight.play();
			}
		});
		window.addEventListener("touchmove", function (e)
		{
			//alert("touchmove(" + e.touches.length + ", " + e.changedTouches.length + ")");
		});
		window.addEventListener("touchend", function (e)
		{
			for (var i = e.changedTouches.length; i--;)
            localStorage.i = (parseInt(localStorage.i) + 1).toString();
			//wt.setText("Hello world(" + localStorage.i + ")!");
			//alert("touchend(" + e.touches.length + ", " + e.changedTouches.length + ")");
		});
		window.addEventListener("touchcancel", function (e)
		{
			//alert("touchcancel(" + e.touches.length + ", " + e.changedTouches.length + ")");
		});

		var last_t = 0;

		function refresh(t)
		{
			var t_dif = t - last_t;
			last_t = t;

			//trace(t_dif);
			//alert(t_dif);
			for (var i = Sprites.length; i--;)
			Sprites[i].tick(t_dif);

			gl.clearColor(0, 0, 1, 1);
			gl.clear(gl.COLOR_BUFFER_BIT);

			for (var i = Sprites.length; i--;)
			Sprites[i].draw(gl);

			//wt.draw(gl);
			//wt2.draw(gl);
			requestAnimationFrame(refresh);
		}
		requestAnimationFrame(refresh);
	});
});
