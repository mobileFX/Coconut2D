//@compile{true}
//@depends{WebGL.js}

/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013 www.coconut2D.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.   
 *
 * ***** END LICENSE BLOCK ***** */

// ==================================================================================================================================
//	 _       __     __    ________       __  ___                          
//	| |     / /__  / /_  / ____/ /      /  |/  /___ _______________  _____
//	| | /| / / _ \/ __ \/ / __/ /      / /|_/ / __ `/ ___/ ___/ __ \/ ___/
//	| |/ |/ /  __/ /_/ / /_/ / /___   / /  / / /_/ / /__/ /  / /_/ (__  ) 
//	|__/|__/\___/_.___/\____/_____/  /_/  /_/\__,_/\___/_/   \____/____/  
//	                                                                      
// ==================================================================================================================================

var glu = {

	makeProgram: function(gl, vs, fs)
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
};
