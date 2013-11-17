//@compile{native}
//@include{HTMLCanvas.js}

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
//	 _       __     __    ________    ____  __      _           __ 
//	| |     / /__  / /_  / ____/ /   / __ \/ /_    (_)__  _____/ /_
//	| | /| / / _ \/ __ \/ / __/ /   / / / / __ \  / / _ \/ ___/ __/
//	| |/ |/ /  __/ /_/ / /_/ / /___/ /_/ / /_/ / / /  __/ /__/ /_  
//	|__/|__/\___/_.___/\____/_____/\____/_.___/_/ /\___/\___/\__/  
//	                                         /___/                 
// ==================================================================================================================================
function WebGLObject(uid)
{
	this.__uid = uid;
}
WebGLObject.prototype = new Object;
WebGLObject.prototype.__uid = 0;

// ==================================================================================================================================
//	 _       __     __    ________    ____        ________         
//	| |     / /__  / /_  / ____/ /   / __ )__  __/ __/ __/__  _____
//	| | /| / / _ \/ __ \/ / __/ /   / __  / / / / /_/ /_/ _ \/ ___/
//	| |/ |/ /  __/ /_/ / /_/ / /___/ /_/ / /_/ / __/ __/  __/ /    
//	|__/|__/\___/_.___/\____/_____/_____/\__,_/_/ /_/  \___/_/     
//	                                                               
// ==================================================================================================================================
function WebGLBuffer(uid)
{
	WebGLObject.call(this, uid);
}
WebGLBuffer.prototype = new WebGLObject;

// ==================================================================================================================================
//	 _       __     __    ________    ______                          __          ________         
//	| |     / /__  / /_  / ____/ /   / ____/________ _____ ___  ___  / /_  __  __/ __/ __/__  _____
//	| | /| / / _ \/ __ \/ / __/ /   / /_  / ___/ __ `/ __ `__ \/ _ \/ __ \/ / / / /_/ /_/ _ \/ ___/
//	| |/ |/ /  __/ /_/ / /_/ / /___/ __/ / /  / /_/ / / / / / /  __/ /_/ / /_/ / __/ __/  __/ /    
//	|__/|__/\___/_.___/\____/_____/_/   /_/   \__,_/_/ /_/ /_/\___/_.___/\__,_/_/ /_/  \___/_/     
//	                                                                                               
// ==================================================================================================================================
function WebGLFramebuffer(uid)
{
	WebGLObject.call(this, uid);
}
WebGLFramebuffer.prototype = new WebGLObject;

// ==================================================================================================================================
//	 _       __     __    ________    ____                 __          __          ________         
//	| |     / /__  / /_  / ____/ /   / __ \___  ____  ____/ /__  _____/ /_  __  __/ __/ __/__  _____
//	| | /| / / _ \/ __ \/ / __/ /   / /_/ / _ \/ __ \/ __  / _ \/ ___/ __ \/ / / / /_/ /_/ _ \/ ___/
//	| |/ |/ /  __/ /_/ / /_/ / /___/ _, _/  __/ / / / /_/ /  __/ /  / /_/ / /_/ / __/ __/  __/ /    
//	|__/|__/\___/_.___/\____/_____/_/ |_|\___/_/ /_/\__,_/\___/_/  /_.___/\__,_/_/ /_/  \___/_/     
//	                                                                                                
// ==================================================================================================================================
function WebGLRenderbuffer(uid)
{
	WebGLObject.call(this, uid);
}
WebGLRenderbuffer.prototype = new WebGLObject;

// ==================================================================================================================================
//	 _       __     __    ________    ____                                      
//	| |     / /__  / /_  / ____/ /   / __ \_________  ____ __________ _____ ___ 
//	| | /| / / _ \/ __ \/ / __/ /   / /_/ / ___/ __ \/ __ `/ ___/ __ `/ __ `__ \
//	| |/ |/ /  __/ /_/ / /_/ / /___/ ____/ /  / /_/ / /_/ / /  / /_/ / / / / / /
//	|__/|__/\___/_.___/\____/_____/_/   /_/   \____/\__, /_/   \__,_/_/ /_/ /_/ 
//	                                               /____/                       
// ==================================================================================================================================
function WebGLProgram(uid)
{
	WebGLObject.call(this, uid);
}
WebGLProgram.prototype = new WebGLObject;

// ==================================================================================================================================
//	 _       __     __    ________   _____ __              __         
//	| |     / /__  / /_  / ____/ /  / ___// /_  ____ _____/ /__  _____
//	| | /| / / _ \/ __ \/ / __/ /   \__ \/ __ \/ __ `/ __  / _ \/ ___/
//	| |/ |/ /  __/ /_/ / /_/ / /______/ / / / / /_/ / /_/ /  __/ /    
//	|__/|__/\___/_.___/\____/_____/____/_/ /_/\__,_/\__,_/\___/_/     
//	                                                                  
// ==================================================================================================================================
function WebGLShader(uid, type)
{
	WebGLObject.call(this, uid);
	this.type = type;
}
WebGLShader.prototype = new WebGLObject;
WebGLShader.prototype.type = 0;

// ==================================================================================================================================
//	 _       __     __    ________  ______          __                
//	| |     / /__  / /_  / ____/ / /_  __/__  _  __/ /___  __________ 
//	| | /| / / _ \/ __ \/ / __/ /   / / / _ \| |/_/ __/ / / / ___/ _ \
//	| |/ |/ /  __/ /_/ / /_/ / /___/ / /  __/>  </ /_/ /_/ / /  /  __/
//	|__/|__/\___/_.___/\____/_____/_/  \___/_/|_|\__/\__,_/_/   \___/ 
//	                                                                  
// ==================================================================================================================================
function WebGLTexture(uid)
{
	WebGLObject.call(this, uid);
}
WebGLTexture.prototype = new WebGLObject;

// ==================================================================================================================================
//	 _       __     __    ________    __  __      _ ____                     __                     __  _           
//	| |     / /__  / /_  / ____/ /   / / / /___  (_) __/___  _________ ___  / /   ____  _________ _/ /_(_)___  ____ 
//	| | /| / / _ \/ __ \/ / __/ /   / / / / __ \/ / /_/ __ \/ ___/ __ `__ \/ /   / __ \/ ___/ __ `/ __/ / __ \/ __ \
//	| |/ |/ /  __/ /_/ / /_/ / /___/ /_/ / / / / / __/ /_/ / /  / / / / / / /___/ /_/ / /__/ /_/ / /_/ / /_/ / / / /
//	|__/|__/\___/_.___/\____/_____/\____/_/ /_/_/_/  \____/_/  /_/ /_/ /_/_____/\____/\___/\__,_/\__/_/\____/_/ /_/ 
//	                                                                                                                
// ==================================================================================================================================
function WebGLUniformLocation(uid)
{
	this.__uid = uid;
}

WebGLUniformLocation.prototype = new Object();
WebGLUniformLocation.prototype.__uid = 0;

// ==================================================================================================================================
//	 _       __     __    ________   _____ __              __          ____                 _      _             ______                           __ 
//	| |     / /__  / /_  / ____/ /  / ___// /_  ____ _____/ /__  _____/ __ \________  _____(_)____(_)___  ____  / ____/___  _________ ___  ____ _/ /_
//	| | /| / / _ \/ __ \/ / __/ /   \__ \/ __ \/ __ `/ __  / _ \/ ___/ /_/ / ___/ _ \/ ___/ / ___/ / __ \/ __ \/ /_  / __ \/ ___/ __ `__ \/ __ `/ __/
//	| |/ |/ /  __/ /_/ / /_/ / /______/ / / / / /_/ / /_/ /  __/ /  / ____/ /  /  __/ /__/ (__  ) / /_/ / / / / __/ / /_/ / /  / / / / / / /_/ / /_  
//	|__/|__/\___/_.___/\____/_____/____/_/ /_/\__,_/\__,_/\___/_/  /_/   /_/   \___/\___/_/____/_/\____/_/ /_/_/    \____/_/  /_/ /_/ /_/\__,_/\__/  
//	                                                                                                                                                 
// ==================================================================================================================================
function WebGLShaderPrecisionFormat(){}
WebGLShaderPrecisionFormat.prototype = new Object();
WebGLShaderPrecisionFormat.prototype.__defineGetter__('rangeMin', function(){});
WebGLShaderPrecisionFormat.prototype.__defineGetter__('rangeMax', function(){});
WebGLShaderPrecisionFormat.prototype.__defineGetter__('precision', function(){});

// ==================================================================================================================================
//	 _       __     __    ________    ______            __            __  ___   __  __       _ __          __           
//	| |     / /__  / /_  / ____/ /   / ____/___  ____  / /____  _  __/ /_/   | / /_/ /______(_) /_  __  __/ /____  _____
//	| | /| / / _ \/ __ \/ / __/ /   / /   / __ \/ __ \/ __/ _ \| |/_/ __/ /| |/ __/ __/ ___/ / __ \/ / / / __/ _ \/ ___/
//	| |/ |/ /  __/ /_/ / /_/ / /___/ /___/ /_/ / / / / /_/  __/>  </ /_/ ___ / /_/ /_/ /  / / /_/ / /_/ / /_/  __(__  ) 
//	|__/|__/\___/_.___/\____/_____/\____/\____/_/ /_/\__/\___/_/|_|\__/_/  |_\__/\__/_/  /_/_.___/\__,_/\__/\___/____/  
//	                                                                                                                    
// ==================================================================================================================================
function WebGLContextAttributes(){}
WebGLContextAttributes.prototype = new Object();
WebGLContextAttributes.prototype.__defineSetter__('alpha', function(v){});
WebGLContextAttributes.prototype.__defineGetter__('alpha', function(){});
WebGLContextAttributes.prototype.__defineSetter__('depth', function(v){});
WebGLContextAttributes.prototype.__defineGetter__('depth', function(){});
WebGLContextAttributes.prototype.__defineSetter__('stencil', function(v){});
WebGLContextAttributes.prototype.__defineGetter__('stencil', function(){});
WebGLContextAttributes.prototype.__defineSetter__('antialias', function(v){});
WebGLContextAttributes.prototype.__defineGetter__('antialias', function(){});
WebGLContextAttributes.prototype.__defineSetter__('premultipliedAlpha', function(v){});
WebGLContextAttributes.prototype.__defineGetter__('premultipliedAlpha', function(){});
WebGLContextAttributes.prototype.__defineSetter__('preserveDrawingBuffer', function(v){});
WebGLContextAttributes.prototype.__defineGetter__('preserveDrawingBuffer', function(){});

// ==================================================================================================================================
//	 _       __     __    ________    ___        __  _            ____      ____    
//	| |     / /__  / /_  / ____/ /   /   | _____/ /_(_)   _____  /  _/___  / __/___ 
//	| | /| / / _ \/ __ \/ / __/ /   / /| |/ ___/ __/ / | / / _ \ / // __ \/ /_/ __ \
//	| |/ |/ /  __/ /_/ / /_/ / /___/ ___ / /__/ /_/ /| |/ /  __// // / / / __/ /_/ /
//	|__/|__/\___/_.___/\____/_____/_/  |_\___/\__/_/ |___/\___/___/_/ /_/_/  \____/ 
//	                                                                                
// ==================================================================================================================================
function WebGLActiveInfo(){}
WebGLActiveInfo.prototype = new Object();
WebGLActiveInfo.prototype.__defineGetter__('size', function(){});
WebGLActiveInfo.prototype.__defineGetter__('type', function(){});
WebGLActiveInfo.prototype.__defineGetter__('name', function(){});


// ==================================================================================================================================
//	 _       __     __    ________    ____                 __          _             ______            __            __ 
//	| |     / /__  / /_  / ____/ /   / __ \___  ____  ____/ /__  _____(_)___  ____ _/ ____/___  ____  / /____  _  __/ /_
//	| | /| / / _ \/ __ \/ / __/ /   / /_/ / _ \/ __ \/ __  / _ \/ ___/ / __ \/ __ `/ /   / __ \/ __ \/ __/ _ \| |/_/ __/
//	| |/ |/ /  __/ /_/ / /_/ / /___/ _, _/  __/ / / / /_/ /  __/ /  / / / / / /_/ / /___/ /_/ / / / / /_/  __/>  </ /_  
//	|__/|__/\___/_.___/\____/_____/_/ |_|\___/_/ /_/\__,_/\___/_/  /_/_/ /_/\__, /\____/\____/_/ /_/\__/\___/_/|_|\__/  
//	                                                                       /____/                                       
// ==================================================================================================================================
function WebGLRenderingContext(canvas)
{
	this.__uid = ++__uid_counter;
	this.__canvas = canvas;		
}

WebGLRenderingContext.prototype = new Object();
WebGLRenderingContext.__uid = 0;
WebGLRenderingContext.__canvas;
WebGLRenderingContext.prototype.__defineGetter__('canvas', function(){return this.__canvas;});
WebGLRenderingContext.prototype.__defineGetter__('drawingBufferWidth', function(){});
WebGLRenderingContext.prototype.__defineGetter__('drawingBufferHeight', function(){});

WebGLRenderingContext.prototype.DEPTH_BUFFER_BIT = 0x00000100;
WebGLRenderingContext.prototype.STENCIL_BUFFER_BIT = 0x00000400;
WebGLRenderingContext.prototype.COLOR_BUFFER_BIT = 0x00004000;
WebGLRenderingContext.prototype.POINTS = 0x0000;
WebGLRenderingContext.prototype.LINES = 0x0001;
WebGLRenderingContext.prototype.LINE_LOOP = 0x0002;
WebGLRenderingContext.prototype.LINE_STRIP = 0x0003;
WebGLRenderingContext.prototype.TRIANGLES = 0x0004;
WebGLRenderingContext.prototype.TRIANGLE_STRIP = 0x0005;
WebGLRenderingContext.prototype.TRIANGLE_FAN = 0x0006;
WebGLRenderingContext.prototype.ZERO = 0;
WebGLRenderingContext.prototype.ONE = 1;
WebGLRenderingContext.prototype.SRC_COLOR = 0x0300;
WebGLRenderingContext.prototype.ONE_MINUS_SRC_COLOR = 0x0301;
WebGLRenderingContext.prototype.SRC_ALPHA = 0x0302;
WebGLRenderingContext.prototype.ONE_MINUS_SRC_ALPHA = 0x0303;
WebGLRenderingContext.prototype.DST_ALPHA = 0x0304;
WebGLRenderingContext.prototype.ONE_MINUS_DST_ALPHA = 0x0305;
WebGLRenderingContext.prototype.DST_COLOR = 0x0306;
WebGLRenderingContext.prototype.ONE_MINUS_DST_COLOR = 0x0307;
WebGLRenderingContext.prototype.SRC_ALPHA_SATURATE = 0x0308;
WebGLRenderingContext.prototype.FUNC_ADD = 0x8006;
WebGLRenderingContext.prototype.BLEND_EQUATION = 0x8009;
WebGLRenderingContext.prototype.BLEND_EQUATION_RGB = 0x8009;
WebGLRenderingContext.prototype.BLEND_EQUATION_ALPHA = 0x883D;
WebGLRenderingContext.prototype.FUNC_SUBTRACT = 0x800A;
WebGLRenderingContext.prototype.FUNC_REVERSE_SUBTRACT = 0x800B;
WebGLRenderingContext.prototype.BLEND_DST_RGB = 0x80C8;
WebGLRenderingContext.prototype.BLEND_SRC_RGB = 0x80C9;
WebGLRenderingContext.prototype.BLEND_DST_ALPHA = 0x80CA;
WebGLRenderingContext.prototype.BLEND_SRC_ALPHA = 0x80CB;
WebGLRenderingContext.prototype.CONSTANT_COLOR = 0x8001;
WebGLRenderingContext.prototype.ONE_MINUS_CONSTANT_COLOR = 0x8002;
WebGLRenderingContext.prototype.CONSTANT_ALPHA = 0x8003;
WebGLRenderingContext.prototype.ONE_MINUS_CONSTANT_ALPHA = 0x8004;
WebGLRenderingContext.prototype.BLEND_COLOR = 0x8005;
WebGLRenderingContext.prototype.ARRAY_BUFFER = 0x8892;
WebGLRenderingContext.prototype.ELEMENT_ARRAY_BUFFER = 0x8893;
WebGLRenderingContext.prototype.ARRAY_BUFFER_BINDING = 0x8894;
WebGLRenderingContext.prototype.ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
WebGLRenderingContext.prototype.STREAM_DRAW = 0x88E0;
WebGLRenderingContext.prototype.STATIC_DRAW = 0x88E4;
WebGLRenderingContext.prototype.DYNAMIC_DRAW = 0x88E8;
WebGLRenderingContext.prototype.BUFFER_SIZE = 0x8764;
WebGLRenderingContext.prototype.BUFFER_USAGE = 0x8765;
WebGLRenderingContext.prototype.CURRENT_VERTEX_ATTRIB = 0x8626;
WebGLRenderingContext.prototype.FRONT = 0x0404;
WebGLRenderingContext.prototype.BACK = 0x0405;
WebGLRenderingContext.prototype.FRONT_AND_BACK = 0x0408;
WebGLRenderingContext.prototype.CULL_FACE = 0x0B44;
WebGLRenderingContext.prototype.BLEND = 0x0BE2;
WebGLRenderingContext.prototype.DITHER = 0x0BD0;
WebGLRenderingContext.prototype.STENCIL_TEST = 0x0B90;
WebGLRenderingContext.prototype.DEPTH_TEST = 0x0B71;
WebGLRenderingContext.prototype.SCISSOR_TEST = 0x0C11;
WebGLRenderingContext.prototype.POLYGON_OFFSET_FILL = 0x8037;
WebGLRenderingContext.prototype.SAMPLE_ALPHA_TO_COVERAGE = 0x809E;
WebGLRenderingContext.prototype.SAMPLE_COVERAGE = 0x80A0;
WebGLRenderingContext.prototype.NO_ERROR = 0;
WebGLRenderingContext.prototype.INVALID_ENUM = 0x0500;
WebGLRenderingContext.prototype.INVALID_VALUE = 0x0501;
WebGLRenderingContext.prototype.INVALID_OPERATION = 0x0502;
WebGLRenderingContext.prototype.OUT_OF_MEMORY = 0x0505;
WebGLRenderingContext.prototype.CW = 0x0900;
WebGLRenderingContext.prototype.CCW = 0x0901;
WebGLRenderingContext.prototype.LINE_WIDTH = 0x0B21;
WebGLRenderingContext.prototype.ALIASED_POINT_SIZE_RANGE = 0x846D;
WebGLRenderingContext.prototype.ALIASED_LINE_WIDTH_RANGE = 0x846E;
WebGLRenderingContext.prototype.CULL_FACE_MODE = 0x0B45;
WebGLRenderingContext.prototype.FRONT_FACE = 0x0B46;
WebGLRenderingContext.prototype.DEPTH_RANGE = 0x0B70;
WebGLRenderingContext.prototype.DEPTH_WRITEMASK = 0x0B72;
WebGLRenderingContext.prototype.DEPTH_CLEAR_VALUE = 0x0B73;
WebGLRenderingContext.prototype.DEPTH_FUNC = 0x0B74;
WebGLRenderingContext.prototype.STENCIL_CLEAR_VALUE = 0x0B91;
WebGLRenderingContext.prototype.STENCIL_FUNC = 0x0B92;
WebGLRenderingContext.prototype.STENCIL_FAIL = 0x0B94;
WebGLRenderingContext.prototype.STENCIL_PASS_DEPTH_FAIL = 0x0B95;
WebGLRenderingContext.prototype.STENCIL_PASS_DEPTH_PASS = 0x0B96;
WebGLRenderingContext.prototype.STENCIL_REF = 0x0B97;
WebGLRenderingContext.prototype.STENCIL_VALUE_MASK = 0x0B93;
WebGLRenderingContext.prototype.STENCIL_WRITEMASK = 0x0B98;
WebGLRenderingContext.prototype.STENCIL_BACK_FUNC = 0x8800;
WebGLRenderingContext.prototype.STENCIL_BACK_FAIL = 0x8801;
WebGLRenderingContext.prototype.STENCIL_BACK_PASS_DEPTH_FAIL = 0x8802;
WebGLRenderingContext.prototype.STENCIL_BACK_PASS_DEPTH_PASS = 0x8803;
WebGLRenderingContext.prototype.STENCIL_BACK_REF = 0x8CA3;
WebGLRenderingContext.prototype.STENCIL_BACK_VALUE_MASK = 0x8CA4;
WebGLRenderingContext.prototype.STENCIL_BACK_WRITEMASK = 0x8CA5;
WebGLRenderingContext.prototype.VIEWPORT = 0x0BA2;
WebGLRenderingContext.prototype.SCISSOR_BOX = 0x0C10;
WebGLRenderingContext.prototype.COLOR_CLEAR_VALUE = 0x0C22;
WebGLRenderingContext.prototype.COLOR_WRITEMASK = 0x0C23;
WebGLRenderingContext.prototype.UNPACK_ALIGNMENT = 0x0CF5;
WebGLRenderingContext.prototype.PACK_ALIGNMENT = 0x0D05;
WebGLRenderingContext.prototype.MAX_TEXTURE_SIZE = 0x0D33;
WebGLRenderingContext.prototype.MAX_VIEWPORT_DIMS = 0x0D3A;
WebGLRenderingContext.prototype.SUBPIXEL_BITS = 0x0D50;
WebGLRenderingContext.prototype.RED_BITS = 0x0D52;
WebGLRenderingContext.prototype.GREEN_BITS = 0x0D53;
WebGLRenderingContext.prototype.BLUE_BITS = 0x0D54;
WebGLRenderingContext.prototype.ALPHA_BITS = 0x0D55;
WebGLRenderingContext.prototype.DEPTH_BITS = 0x0D56;
WebGLRenderingContext.prototype.STENCIL_BITS = 0x0D57;
WebGLRenderingContext.prototype.POLYGON_OFFSET_UNITS = 0x2A00;
WebGLRenderingContext.prototype.POLYGON_OFFSET_FACTOR = 0x8038;
WebGLRenderingContext.prototype.TEXTURE_BINDING_2D = 0x8069;
WebGLRenderingContext.prototype.SAMPLE_BUFFERS = 0x80A8;
WebGLRenderingContext.prototype.SAMPLES = 0x80A9;
WebGLRenderingContext.prototype.SAMPLE_COVERAGE_VALUE = 0x80AA;
WebGLRenderingContext.prototype.SAMPLE_COVERAGE_INVERT = 0x80AB;
WebGLRenderingContext.prototype.COMPRESSED_TEXTURE_FORMATS = 0x86A3;
WebGLRenderingContext.prototype.DONT_CARE = 0x1100;
WebGLRenderingContext.prototype.FASTEST = 0x1101;
WebGLRenderingContext.prototype.NICEST = 0x1102;
WebGLRenderingContext.prototype.GENERATE_MIPMAP_HINT = 0x8192;
WebGLRenderingContext.prototype.BYTE = 0x1400;
WebGLRenderingContext.prototype.UNSIGNED_BYTE = 0x1401;
WebGLRenderingContext.prototype.SHORT = 0x1402;
WebGLRenderingContext.prototype.UNSIGNED_SHORT = 0x1403;
WebGLRenderingContext.prototype.INT = 0x1404;
WebGLRenderingContext.prototype.UNSIGNED_INT = 0x1405;
WebGLRenderingContext.prototype.FLOAT = 0x1406;
WebGLRenderingContext.prototype.DEPTH_COMPONENT = 0x1902;
WebGLRenderingContext.prototype.ALPHA = 0x1906;
WebGLRenderingContext.prototype.RGB = 0x1907;
WebGLRenderingContext.prototype.RGBA = 0x1908;
WebGLRenderingContext.prototype.LUMINANCE = 0x1909;
WebGLRenderingContext.prototype.LUMINANCE_ALPHA = 0x190A;
WebGLRenderingContext.prototype.UNSIGNED_SHORT_4_4_4_4 = 0x8033;
WebGLRenderingContext.prototype.UNSIGNED_SHORT_5_5_5_1 = 0x8034;
WebGLRenderingContext.prototype.UNSIGNED_SHORT_5_6_5 = 0x8363;
WebGLRenderingContext.prototype.FRAGMENT_SHADER = 0x8B30;
WebGLRenderingContext.prototype.VERTEX_SHADER = 0x8B31;
WebGLRenderingContext.prototype.MAX_VERTEX_ATTRIBS = 0x8869;
WebGLRenderingContext.prototype.MAX_VERTEX_UNIFORM_VECTORS = 0x8DFB;
WebGLRenderingContext.prototype.MAX_VARYING_VECTORS = 0x8DFC;
WebGLRenderingContext.prototype.MAX_COMBINED_TEXTURE_IMAGE_UNITS = 0x8B4D;
WebGLRenderingContext.prototype.MAX_VERTEX_TEXTURE_IMAGE_UNITS = 0x8B4C;
WebGLRenderingContext.prototype.MAX_TEXTURE_IMAGE_UNITS = 0x8872;
WebGLRenderingContext.prototype.MAX_FRAGMENT_UNIFORM_VECTORS = 0x8DFD;
WebGLRenderingContext.prototype.SHADER_TYPE = 0x8B4F;
WebGLRenderingContext.prototype.DELETE_STATUS = 0x8B80;
WebGLRenderingContext.prototype.LINK_STATUS = 0x8B82;
WebGLRenderingContext.prototype.VALIDATE_STATUS = 0x8B83;
WebGLRenderingContext.prototype.ATTACHED_SHADERS = 0x8B85;
WebGLRenderingContext.prototype.ACTIVE_UNIFORMS = 0x8B86;
WebGLRenderingContext.prototype.ACTIVE_ATTRIBUTES = 0x8B89;
WebGLRenderingContext.prototype.SHADING_LANGUAGE_VERSION = 0x8B8C;
WebGLRenderingContext.prototype.CURRENT_PROGRAM = 0x8B8D;
WebGLRenderingContext.prototype.NEVER = 0x0200;
WebGLRenderingContext.prototype.LESS = 0x0201;
WebGLRenderingContext.prototype.EQUAL = 0x0202;
WebGLRenderingContext.prototype.LEQUAL = 0x0203;
WebGLRenderingContext.prototype.GREATER = 0x0204;
WebGLRenderingContext.prototype.NOTEQUAL = 0x0205;
WebGLRenderingContext.prototype.GEQUAL = 0x0206;
WebGLRenderingContext.prototype.ALWAYS = 0x0207;
WebGLRenderingContext.prototype.KEEP = 0x1E00;
WebGLRenderingContext.prototype.REPLACE = 0x1E01;
WebGLRenderingContext.prototype.INCR = 0x1E02;
WebGLRenderingContext.prototype.DECR = 0x1E03;
WebGLRenderingContext.prototype.INVERT = 0x150A;
WebGLRenderingContext.prototype.INCR_WRAP = 0x8507;
WebGLRenderingContext.prototype.DECR_WRAP = 0x8508;
WebGLRenderingContext.prototype.VENDOR = 0x1F00;
WebGLRenderingContext.prototype.RENDERER = 0x1F01;
WebGLRenderingContext.prototype.VERSION = 0x1F02;
WebGLRenderingContext.prototype.NEAREST = 0x2600;
WebGLRenderingContext.prototype.LINEAR = 0x2601;
WebGLRenderingContext.prototype.NEAREST_MIPMAP_NEAREST = 0x2700;
WebGLRenderingContext.prototype.LINEAR_MIPMAP_NEAREST = 0x2701;
WebGLRenderingContext.prototype.NEAREST_MIPMAP_LINEAR = 0x2702;
WebGLRenderingContext.prototype.LINEAR_MIPMAP_LINEAR = 0x2703;
WebGLRenderingContext.prototype.TEXTURE_MAG_FILTER = 0x2800;
WebGLRenderingContext.prototype.TEXTURE_MIN_FILTER = 0x2801;
WebGLRenderingContext.prototype.TEXTURE_WRAP_S = 0x2802;
WebGLRenderingContext.prototype.TEXTURE_WRAP_T = 0x2803;
WebGLRenderingContext.prototype.TEXTURE_2D = 0x0DE1;
WebGLRenderingContext.prototype.TEXTURE = 0x1702;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP = 0x8513;
WebGLRenderingContext.prototype.TEXTURE_BINDING_CUBE_MAP = 0x8514;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
WebGLRenderingContext.prototype.TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
WebGLRenderingContext.prototype.MAX_CUBE_MAP_TEXTURE_SIZE = 0x851C;
WebGLRenderingContext.prototype.TEXTURE0 = 0x84C0;
WebGLRenderingContext.prototype.TEXTURE1 = 0x84C1;
WebGLRenderingContext.prototype.TEXTURE2 = 0x84C2;
WebGLRenderingContext.prototype.TEXTURE3 = 0x84C3;
WebGLRenderingContext.prototype.TEXTURE4 = 0x84C4;
WebGLRenderingContext.prototype.TEXTURE5 = 0x84C5;
WebGLRenderingContext.prototype.TEXTURE6 = 0x84C6;
WebGLRenderingContext.prototype.TEXTURE7 = 0x84C7;
WebGLRenderingContext.prototype.TEXTURE8 = 0x84C8;
WebGLRenderingContext.prototype.TEXTURE9 = 0x84C9;
WebGLRenderingContext.prototype.TEXTURE10 = 0x84CA;
WebGLRenderingContext.prototype.TEXTURE11 = 0x84CB;
WebGLRenderingContext.prototype.TEXTURE12 = 0x84CC;
WebGLRenderingContext.prototype.TEXTURE13 = 0x84CD;
WebGLRenderingContext.prototype.TEXTURE14 = 0x84CE;
WebGLRenderingContext.prototype.TEXTURE15 = 0x84CF;
WebGLRenderingContext.prototype.TEXTURE16 = 0x84D0;
WebGLRenderingContext.prototype.TEXTURE17 = 0x84D1;
WebGLRenderingContext.prototype.TEXTURE18 = 0x84D2;
WebGLRenderingContext.prototype.TEXTURE19 = 0x84D3;
WebGLRenderingContext.prototype.TEXTURE20 = 0x84D4;
WebGLRenderingContext.prototype.TEXTURE21 = 0x84D5;
WebGLRenderingContext.prototype.TEXTURE22 = 0x84D6;
WebGLRenderingContext.prototype.TEXTURE23 = 0x84D7;
WebGLRenderingContext.prototype.TEXTURE24 = 0x84D8;
WebGLRenderingContext.prototype.TEXTURE25 = 0x84D9;
WebGLRenderingContext.prototype.TEXTURE26 = 0x84DA;
WebGLRenderingContext.prototype.TEXTURE27 = 0x84DB;
WebGLRenderingContext.prototype.TEXTURE28 = 0x84DC;
WebGLRenderingContext.prototype.TEXTURE29 = 0x84DD;
WebGLRenderingContext.prototype.TEXTURE30 = 0x84DE;
WebGLRenderingContext.prototype.TEXTURE31 = 0x84DF;
WebGLRenderingContext.prototype.ACTIVE_TEXTURE = 0x84E0;
WebGLRenderingContext.prototype.REPEAT = 0x2901;
WebGLRenderingContext.prototype.CLAMP_TO_EDGE = 0x812F;
WebGLRenderingContext.prototype.MIRRORED_REPEAT = 0x8370;
WebGLRenderingContext.prototype.FLOAT_VEC2 = 0x8B50;
WebGLRenderingContext.prototype.FLOAT_VEC3 = 0x8B51;
WebGLRenderingContext.prototype.FLOAT_VEC4 = 0x8B52;
WebGLRenderingContext.prototype.INT_VEC2 = 0x8B53;
WebGLRenderingContext.prototype.INT_VEC3 = 0x8B54;
WebGLRenderingContext.prototype.INT_VEC4 = 0x8B55;
WebGLRenderingContext.prototype.BOOL = 0x8B56;
WebGLRenderingContext.prototype.BOOL_VEC2 = 0x8B57;
WebGLRenderingContext.prototype.BOOL_VEC3 = 0x8B58;
WebGLRenderingContext.prototype.BOOL_VEC4 = 0x8B59;
WebGLRenderingContext.prototype.FLOAT_MAT2 = 0x8B5A;
WebGLRenderingContext.prototype.FLOAT_MAT3 = 0x8B5B;
WebGLRenderingContext.prototype.FLOAT_MAT4 = 0x8B5C;
WebGLRenderingContext.prototype.SAMPLER_2D = 0x8B5E;
WebGLRenderingContext.prototype.SAMPLER_CUBE = 0x8B60;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_SIZE = 0x8623;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_STRIDE = 0x8624;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_TYPE = 0x8625;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_NORMALIZED = 0x886A;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_POINTER = 0x8645;
WebGLRenderingContext.prototype.VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = 0x889F;
WebGLRenderingContext.prototype.COMPILE_STATUS = 0x8B81;
WebGLRenderingContext.prototype.LOW_FLOAT = 0x8DF0;
WebGLRenderingContext.prototype.MEDIUM_FLOAT = 0x8DF1;
WebGLRenderingContext.prototype.HIGH_FLOAT = 0x8DF2;
WebGLRenderingContext.prototype.LOW_INT = 0x8DF3;
WebGLRenderingContext.prototype.MEDIUM_INT = 0x8DF4;
WebGLRenderingContext.prototype.HIGH_INT = 0x8DF5;
WebGLRenderingContext.prototype.FRAMEBUFFER = 0x8D40;
WebGLRenderingContext.prototype.RENDERBUFFER = 0x8D41;
WebGLRenderingContext.prototype.RGBA4 = 0x8056;
WebGLRenderingContext.prototype.RGB5_A1 = 0x8057;
WebGLRenderingContext.prototype.RGB565 = 0x8D62;
WebGLRenderingContext.prototype.DEPTH_COMPONENT16 = 0x81A5;
WebGLRenderingContext.prototype.STENCIL_INDEX = 0x1901;
WebGLRenderingContext.prototype.STENCIL_INDEX8 = 0x8D48;
WebGLRenderingContext.prototype.DEPTH_STENCIL = 0x84F9;
WebGLRenderingContext.prototype.RENDERBUFFER_WIDTH = 0x8D42;
WebGLRenderingContext.prototype.RENDERBUFFER_HEIGHT = 0x8D43;
WebGLRenderingContext.prototype.RENDERBUFFER_INTERNAL_FORMAT = 0x8D44;
WebGLRenderingContext.prototype.RENDERBUFFER_RED_SIZE = 0x8D50;
WebGLRenderingContext.prototype.RENDERBUFFER_GREEN_SIZE = 0x8D51;
WebGLRenderingContext.prototype.RENDERBUFFER_BLUE_SIZE = 0x8D52;
WebGLRenderingContext.prototype.RENDERBUFFER_ALPHA_SIZE = 0x8D53;
WebGLRenderingContext.prototype.RENDERBUFFER_DEPTH_SIZE = 0x8D54;
WebGLRenderingContext.prototype.RENDERBUFFER_STENCIL_SIZE = 0x8D55;
WebGLRenderingContext.prototype.FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
WebGLRenderingContext.prototype.FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
WebGLRenderingContext.prototype.FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = 0x8CD2;
WebGLRenderingContext.prototype.FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = 0x8CD3;
WebGLRenderingContext.prototype.COLOR_ATTACHMENT0 = 0x8CE0;
WebGLRenderingContext.prototype.DEPTH_ATTACHMENT = 0x8D00;
WebGLRenderingContext.prototype.STENCIL_ATTACHMENT = 0x8D20;
WebGLRenderingContext.prototype.DEPTH_STENCIL_ATTACHMENT = 0x821A;
WebGLRenderingContext.prototype.NONE = 0;
WebGLRenderingContext.prototype.FRAMEBUFFER_COMPLETE = 0x8CD5;
WebGLRenderingContext.prototype.FRAMEBUFFER_INCOMPLETE_ATTACHMENT = 0x8CD6;
WebGLRenderingContext.prototype.FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = 0x8CD7;
WebGLRenderingContext.prototype.FRAMEBUFFER_INCOMPLETE_DIMENSIONS = 0x8CD9;
WebGLRenderingContext.prototype.FRAMEBUFFER_UNSUPPORTED = 0x8CDD;
WebGLRenderingContext.prototype.FRAMEBUFFER_BINDING = 0x8CA6;
WebGLRenderingContext.prototype.RENDERBUFFER_BINDING = 0x8CA7;
WebGLRenderingContext.prototype.MAX_RENDERBUFFER_SIZE = 0x84E8;
WebGLRenderingContext.prototype.INVALID_FRAMEBUFFER_OPERATION = 0x0506;
WebGLRenderingContext.prototype.UNPACK_FLIP_Y_WEBGL = 0x9240;
WebGLRenderingContext.prototype.UNPACK_PREMULTIPLY_ALPHA_WEBGL = 0x9241;
WebGLRenderingContext.prototype.CONTEXT_LOST_WEBGL = 0x9242;
WebGLRenderingContext.prototype.UNPACK_COLORSPACE_CONVERSION_WEBGL = 0x9243;
WebGLRenderingContext.prototype.BROWSER_DEFAULT_WEBGL = 0x9244;

/** ================================================================================
 * Method: getContextAttributes()
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {WebGLContextAttributes}
 */
WebGLRenderingContext.prototype.getContextAttributes = function()
{
	return new WebGLContextAttributes(__WebGLRenderingContext_getContextAttributes(this.__uid));
};

/** ================================================================================
 * Method: isContextLost()
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isContextLost = function()
{
	return __WebGLRenderingContext_isContextLost(this.__uid);
};

/** ================================================================================
 * Method: getSupportedExtensions()
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {Array}
 */
WebGLRenderingContext.prototype.getSupportedExtensions = function()
{
	return __WebGLRenderingContext_getSupportedExtensions(this.__uid);
};

/** ================================================================================
 * Method: getExtension(name)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {String} name
 * @return {Object}
 */
WebGLRenderingContext.prototype.getExtension = function(name)
{
	return __WebGLRenderingContext_getExtension(this.__uid, name);
};

/** ================================================================================
 * Method: activeTexture(texture)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} texture
 */
WebGLRenderingContext.prototype.activeTexture = function(texture)
{
	return __WebGLRenderingContext_activeTexture(this.__uid, texture);
};

/** ================================================================================
 * Method: attachShader(program, shader)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {WebGLShader} shader
 */
WebGLRenderingContext.prototype.attachShader = function(program, shader)
{
	return __WebGLRenderingContext_attachShader(this.__uid, program.__uid, shader.__uid);
};

/** ================================================================================
 * Method: bindAttribLocation(program, index, name)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {Number} index
 * @param {String} name
 */
WebGLRenderingContext.prototype.bindAttribLocation = function(program, index, name)
{
	return __WebGLRenderingContext_bindAttribLocation(this.__uid, program.__uid, index, name);
};

/** ================================================================================
 * Method: bindBuffer(target, buffer)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {WebGLBuffer} buffer
 */
WebGLRenderingContext.prototype.bindBuffer = function(target, buffer)
{
	if(!buffer) return __WebGLRenderingContext_bindBuffer(this.__uid, target, 0); 
	return __WebGLRenderingContext_bindBuffer(this.__uid, target, buffer.__uid);
};

/** ================================================================================
 * Method: bindFramebuffer(target, framebuffer)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {WebGLFramebuffer} framebuffer
 */
WebGLRenderingContext.prototype.bindFramebuffer = function(target, framebuffer)
{
	return __WebGLRenderingContext_bindFramebuffer(this.__uid, target, framebuffer.__uid);
};

/** ================================================================================
 * Method: bindRenderbuffer(target, renderbuffer)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {WebGLRenderbuffer} renderbuffer
 */
WebGLRenderingContext.prototype.bindRenderbuffer = function(target, renderbuffer)
{
	return __WebGLRenderingContext_bindRenderbuffer(this.__uid, target, renderbuffer.__uid);
};

/** ================================================================================
 * Method: bindTexture(target, texture)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {WebGLTexture} texture
 */
WebGLRenderingContext.prototype.bindTexture = function(target, texture)
{
	if(!texture) return __WebGLRenderingContext_bindTexture(this.__uid, target, 0);
	return __WebGLRenderingContext_bindTexture(this.__uid, target, texture.__uid);
};

/** ================================================================================
 * Method: blendColor(red, green, blue, alpha)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} red
 * @param {Number} green
 * @param {Number} blue
 * @param {Number} alpha
 */
WebGLRenderingContext.prototype.blendColor = function(red, green, blue, alpha)
{
	return __WebGLRenderingContext_blendColor(this.__uid, red, green, blue, alpha);
};

/** ================================================================================
 * Method: blendEquation(mode)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mode
 */
WebGLRenderingContext.prototype.blendEquation = function(mode)
{
	return __WebGLRenderingContext_blendEquation(this.__uid, mode);
};

/** ================================================================================
 * Method: blendEquationSeparate(modeRGB, modeAlpha)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} modeRGB
 * @param {Number} modeAlpha
 */
WebGLRenderingContext.prototype.blendEquationSeparate = function(modeRGB, modeAlpha)
{
	return __WebGLRenderingContext_blendEquationSeparate(this.__uid, modeRGB, modeAlpha);
};

/** ================================================================================
 * Method: blendFunc(sfactor, dfactor)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} sfactor
 * @param {Number} dfactor
 */
WebGLRenderingContext.prototype.blendFunc = function(sfactor, dfactor)
{
	return __WebGLRenderingContext_blendFunc(this.__uid, sfactor, dfactor);
};

/** ================================================================================
 * Method: blendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} srcRGB
 * @param {Number} dstRGB
 * @param {Number} srcAlpha
 * @param {Number} dstAlpha
 */
WebGLRenderingContext.prototype.blendFuncSeparate = function(srcRGB, dstRGB, srcAlpha, dstAlpha)
{
	return __WebGLRenderingContext_blendFuncSeparate(this.__uid, srcRGB, dstRGB, srcAlpha, dstAlpha);
};

/** ================================================================================
 * Method: bufferData(target, data, usage)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Object} data
 * @param {Number} usage
 */
WebGLRenderingContext.prototype.bufferData = function(target, data, usage)
{
	if(data instanceof ArrayBuffer)
	{
		return __WebGLRenderingContext_bufferData(this.__uid, target, data.__uid, 0, data.byteLength, usage);	
	}
	else if(data instanceof ArrayBufferView)
	{
		return __WebGLRenderingContext_bufferData(this.__uid, target, data.buffer.__uid, data.byteOffset, data.length * data.BYTES_PER_ELEMENT, usage);
	}
    	else alert("Error instanceof!");
	
	data = new ArrayBuffer(data);
	return __WebGLRenderingContext_bufferData(this.__uid, target, data.__uid, 0, data.byteLength, usage);	
};

/** ================================================================================
 * Method: bufferSubData(target, offset, data)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} offset
 * @param {ArrayBufferView} data
 */
WebGLRenderingContext.prototype.bufferSubData = function(target, offset, data)
{
	return __WebGLRenderingContext_bufferSubData(this.__uid, target, offset, data.buffer.__uid, data.byteOffset, data.length * data.BYTES_PER_ELEMENT);
};

/** ================================================================================
 * Method: checkFramebufferStatus(target)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @return {Number}
 */
WebGLRenderingContext.prototype.checkFramebufferStatus = function(target)
{
	return __WebGLRenderingContext_checkFramebufferStatus(this.__uid, target);
};

/** ================================================================================
 * Method: clear(mask)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mask
 */
WebGLRenderingContext.prototype.clear = function(mask)
{
	return __WebGLRenderingContext_clear(this.__uid, mask);
};

/** ================================================================================
 * Method: clearColor(red, green, blue, alpha)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} red
 * @param {Number} green
 * @param {Number} blue
 * @param {Number} alpha
 */
WebGLRenderingContext.prototype.clearColor = function(red, green, blue, alpha)
{
	return __WebGLRenderingContext_clearColor(this.__uid, red, green, blue, alpha);
};

/** ================================================================================
 * Method: clearDepth(depth)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} depth
 */
WebGLRenderingContext.prototype.clearDepth = function(depth)
{
	return __WebGLRenderingContext_clearDepth(this.__uid, depth);
};

/** ================================================================================
 * Method: clearStencil(s)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} s
 */
WebGLRenderingContext.prototype.clearStencil = function(s)
{
	return __WebGLRenderingContext_clearStencil(this.__uid, s);
};

/** ================================================================================
 * Method: colorMask(red, green, blue, alpha)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Boolean} red
 * @param {Boolean} green
 * @param {Boolean} blue
 * @param {Boolean} alpha
 */
WebGLRenderingContext.prototype.colorMask = function(red, green, blue, alpha)
{
	return __WebGLRenderingContext_colorMask(this.__uid, red, green, blue, alpha);
};

/** ================================================================================
 * Method: compileShader(shader)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 */
WebGLRenderingContext.prototype.compileShader = function(shader)
{
	return __WebGLRenderingContext_compileShader(this.__uid, shader.__uid);
};

/** ================================================================================
 * Method: compressedTexImage2D(target, level, internalformat, width, height, border, data)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} level
 * @param {Number} internalformat
 * @param {Number} width
 * @param {Number} height
 * @param {Number} border
 * @param {ArrayBufferView} data
 */
WebGLRenderingContext.prototype.compressedTexImage2D = function(target, level, internalformat, width, height, border, data)
{
	return __WebGLRenderingContext_compressedTexImage2D(this.__uid, target, level, internalformat, width, height, border, data.__buffer.__uid, data.byteOffset, data.length);
};

/** ================================================================================
 * Method: compressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, data)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} level
 * @param {Number} xoffset
 * @param {Number} yoffset
 * @param {Number} width
 * @param {Number} height
 * @param {Number} format
 * @param {ArrayBufferView} data
 */
WebGLRenderingContext.prototype.compressedTexSubImage2D = function(target, level, xoffset, yoffset, width, height, format, data)
{
	return __WebGLRenderingContext_compressedTexSubImage2D(this.__uid, target, level, xoffset, yoffset, width, height, format, data.__buffer.__uid, data.byteOffset, data.length);
};

/** ================================================================================
 * Method: copyTexImage2D(target, level, internalformat, x, y, width, height, border)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} level
 * @param {Number} internalformat
 * @param {Number} x
 * @param {Number} y
 * @param {Number} width
 * @param {Number} height
 * @param {Number} border
 */
WebGLRenderingContext.prototype.copyTexImage2D = function(target, level, internalformat, x, y, width, height, border)
{
	return __WebGLRenderingContext_copyTexImage2D(this.__uid, target, level, internalformat, x, y, width, height, border);
};

/** ================================================================================
 * Method: copyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} level
 * @param {Number} xoffset
 * @param {Number} yoffset
 * @param {Number} x
 * @param {Number} y
 * @param {Number} width
 * @param {Number} height
 */
WebGLRenderingContext.prototype.copyTexSubImage2D = function(target, level, xoffset, yoffset, x, y, width, height)
{
	return __WebGLRenderingContext_copyTexSubImage2D(this.__uid, target, level, xoffset, yoffset, x, y, width, height);
};

/** ================================================================================
 * Method: createBuffer()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {WebGLBuffer}
 */
WebGLRenderingContext.prototype.createBuffer = function()
{
	return new WebGLBuffer(__WebGLRenderingContext_createBuffer(this.__uid));
};

/** ================================================================================
 * Method: createFramebuffer()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {WebGLFramebuffer}
 */
WebGLRenderingContext.prototype.createFramebuffer = function()
{
	return new WebGLFramebuffer(__WebGLRenderingContext_createFramebuffer(this.__uid));
};

/** ================================================================================
 * Method: createProgram()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {WebGLProgram}
 */
WebGLRenderingContext.prototype.createProgram = function()
{
	return new WebGLProgram(__WebGLRenderingContext_createProgram(this.__uid));
};

/** ================================================================================
 * Method: createRenderbuffer()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {WebGLRenderbuffer}
 */
WebGLRenderingContext.prototype.createRenderbuffer = function()
{
	return new WebGLRenderbuffer(__WebGLRenderingContext_createRenderbuffer(this.__uid));
};

/** ================================================================================
 * Method: createShader(type)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} type
 * @return {WebGLShader}
 */
WebGLRenderingContext.prototype.createShader = function(type)
{
	return new WebGLShader(__WebGLRenderingContext_createShader(this.__uid, type), type);
};

/** ================================================================================
 * Method: createTexture()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {WebGLTexture}
 */
WebGLRenderingContext.prototype.createTexture = function()
{
	return new WebGLTexture(__WebGLRenderingContext_createTexture(this.__uid));
};

/** ================================================================================
 * Method: cullFace(mode)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mode
 */
WebGLRenderingContext.prototype.cullFace = function(mode)
{
	return __WebGLRenderingContext_cullFace(this.__uid, mode);
};

/** ================================================================================
 * Method: deleteBuffer(buffer)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLBuffer} buffer
 */
WebGLRenderingContext.prototype.deleteBuffer = function(buffer)
{
	return __WebGLRenderingContext_deleteBuffer(this.__uid, buffer.__uid);
};

/** ================================================================================
 * Method: deleteFramebuffer(framebuffer)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLFramebuffer} framebuffer
 */
WebGLRenderingContext.prototype.deleteFramebuffer = function(framebuffer)
{
	return __WebGLRenderingContext_deleteFramebuffer(this.__uid, framebuffer.__uid);
};

/** ================================================================================
 * Method: deleteProgram(program)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 */
WebGLRenderingContext.prototype.deleteProgram = function(program)
{
	return __WebGLRenderingContext_deleteProgram(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: deleteRenderbuffer(renderbuffer)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLRenderbuffer} renderbuffer
 */
WebGLRenderingContext.prototype.deleteRenderbuffer = function(renderbuffer)
{
	return __WebGLRenderingContext_deleteRenderbuffer(this.__uid, renderbuffer.__uid);
};

/** ================================================================================
 * Method: deleteShader(shader)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 */
WebGLRenderingContext.prototype.deleteShader = function(shader)
{
	return __WebGLRenderingContext_deleteShader(this.__uid, shader.__uid);
};

/** ================================================================================
 * Method: deleteTexture(texture)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLTexture} texture
 */
WebGLRenderingContext.prototype.deleteTexture = function(texture)
{
	return __WebGLRenderingContext_deleteTexture(this.__uid, texture.__uid);
};

/** ================================================================================
 * Method: depthFunc(func)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} func
 */
WebGLRenderingContext.prototype.depthFunc = function(func)
{
	return __WebGLRenderingContext_depthFunc(this.__uid, func);
};

/** ================================================================================
 * Method: depthMask(flag)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Boolean} flag
 */
WebGLRenderingContext.prototype.depthMask = function(flag)
{
	return __WebGLRenderingContext_depthMask(this.__uid, flag);
};

/** ================================================================================
 * Method: depthRange(zNear, zFar)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} zNear
 * @param {Number} zFar
 */
WebGLRenderingContext.prototype.depthRange = function(zNear, zFar)
{
	return __WebGLRenderingContext_depthRange(this.__uid, zNear, zFar);
};

/** ================================================================================
 * Method: detachShader(program, shader)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {WebGLShader} shader
 */
WebGLRenderingContext.prototype.detachShader = function(program, shader)
{
	return __WebGLRenderingContext_detachShader(this.__uid, program.__uid, shader.__uid);
};

/** ================================================================================
 * Method: disable(cap)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} cap
 */
WebGLRenderingContext.prototype.disable = function(cap)
{
	return __WebGLRenderingContext_disable(this.__uid, cap);
};

/** ================================================================================
 * Method: disableVertexAttribArray(index)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} index
 */
WebGLRenderingContext.prototype.disableVertexAttribArray = function(index)
{
	return __WebGLRenderingContext_disableVertexAttribArray(this.__uid, index);
};

/** ================================================================================
 * Method: drawArrays(mode, first, count)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mode
 * @param {Number} first
 * @param {Number} count
 */
WebGLRenderingContext.prototype.drawArrays = function(mode, first, count)
{
	return __WebGLRenderingContext_drawArrays(this.__uid, mode, first, count);
};

/** ================================================================================
 * Method: drawElements(mode, count, type, offset)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mode
 * @param {Number} count
 * @param {Number} type
 * @param {Number} offset
 */
WebGLRenderingContext.prototype.drawElements = function(mode, count, type, offset)
{
	return __WebGLRenderingContext_drawElements(this.__uid, mode, count, type, offset);
};

/** ================================================================================
 * Method: enable(cap)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} cap
 */
WebGLRenderingContext.prototype.enable = function(cap)
{
	return __WebGLRenderingContext_enable(this.__uid, cap);
};

/** ================================================================================
 * Method: enableVertexAttribArray(index)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} index
 */
WebGLRenderingContext.prototype.enableVertexAttribArray = function(index)
{
	return __WebGLRenderingContext_enableVertexAttribArray(this.__uid, index);
};

/** ================================================================================
 * Method: finish()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 */
WebGLRenderingContext.prototype.finish = function()
{
	return __WebGLRenderingContext_finish(this.__uid);
};

/** ================================================================================
 * Method: flush()
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 */
WebGLRenderingContext.prototype.flush = function()
{
	return __WebGLRenderingContext_flush(this.__uid);
};

/** ================================================================================
 * Method: framebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} attachment
 * @param {Number} renderbuffertarget
 * @param {WebGLRenderbuffer} renderbuffer
 */
WebGLRenderingContext.prototype.framebufferRenderbuffer = function(target, attachment, renderbuffertarget, renderbuffer)
{
	return __WebGLRenderingContext_framebufferRenderbuffer(this.__uid, target, attachment, renderbuffertarget, renderbuffer.__uid);
};

/** ================================================================================
 * Method: framebufferTexture2D(target, attachment, textarget, texture, level)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} attachment
 * @param {Number} textarget
 * @param {WebGLTexture} texture
 * @param {Number} level
 */
WebGLRenderingContext.prototype.framebufferTexture2D = function(target, attachment, textarget, texture, level)
{
	return __WebGLRenderingContext_framebufferTexture2D(this.__uid, target, attachment, textarget, texture.__uid, level);
};

/** ================================================================================
 * Method: frontFace(mode)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mode
 */
WebGLRenderingContext.prototype.frontFace = function(mode)
{
	return __WebGLRenderingContext_frontFace(this.__uid, mode);
};

/** ================================================================================
 * Method: generateMipmap(target)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 */
WebGLRenderingContext.prototype.generateMipmap = function(target)
{
	return __WebGLRenderingContext_generateMipmap(this.__uid, target);
};

/** ================================================================================
 * Method: getActiveAttrib(program, index)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {Number} index
 * @return {WebGLActiveInfo}
 */
WebGLRenderingContext.prototype.getActiveAttrib = function(program, index)
{
	return new WebGLActiveInfo(__WebGLRenderingContext_getActiveAttrib(this.__uid, program.__uid, index), program.__uid, index);
};

/** ================================================================================
 * Method: getActiveUniform(program, index)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {Number} index
 * @return {WebGLActiveInfo}
 */
WebGLRenderingContext.prototype.getActiveUniform = function(program, index)
{
	return new WebGLActiveInfo(__WebGLRenderingContext_getActiveUniform(this.__uid, program.__uid, index), program.__uid, index);
};

/** ================================================================================
 * Method: getAttachedShaders(program)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @return {Array}
 */
WebGLRenderingContext.prototype.getAttachedShaders = function(program)
{
	return __WebGLRenderingContext_getAttachedShaders(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: getAttribLocation(program, name)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {String} name
 * @return {Number}
 */
WebGLRenderingContext.prototype.getAttribLocation = function(program, name)
{
	return __WebGLRenderingContext_getAttribLocation(this.__uid, program.__uid, name);
};

/** ================================================================================
 * Method: getBufferParameter(target, pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getBufferParameter = function(target, pname)
{
	return __WebGLRenderingContext_getBufferParameter(this.__uid, target, pname);
};

/** ================================================================================
 * Method: getParameter(pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getParameter = function(pname)
{
	return __WebGLRenderingContext_getParameter(this.__uid, pname);
};

/** ================================================================================
 * Method: getError()
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @return {Number}
 */
WebGLRenderingContext.prototype.getError = function()
{
	return __WebGLRenderingContext_getError(this.__uid);
};

/** ================================================================================
 * Method: getFramebufferAttachmentParameter(target, attachment, pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} attachment
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getFramebufferAttachmentParameter = function(target, attachment, pname)
{
	return __WebGLRenderingContext_getFramebufferAttachmentParameter(this.__uid, target, attachment, pname);
};

/** ================================================================================
 * Method: getProgramParameter(program, pname)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getProgramParameter = function(program, pname)
{
	return __WebGLRenderingContext_getProgramParameter(this.__uid, program.__uid, pname);
};

/** ================================================================================
 * Method: getProgramInfoLog(program)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @return {String}
 */
WebGLRenderingContext.prototype.getProgramInfoLog = function(program)
{
	return __WebGLRenderingContext_getProgramInfoLog(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: getRenderbufferParameter(target, pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getRenderbufferParameter = function(target, pname)
{
	return __WebGLRenderingContext_getRenderbufferParameter(this.__uid, target, pname);
};

/** ================================================================================
 * Method: getShaderParameter(shader, pname)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getShaderParameter = function(shader, pname)
{
	return __WebGLRenderingContext_getShaderParameter(this.__uid, shader.__uid, pname);
};

/** ================================================================================
 * Method: getShaderPrecisionFormat(shadertype, precisiontype)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} shadertype
 * @param {Number} precisiontype
 * @return {WebGLShaderPrecisionFormat}
 */
WebGLRenderingContext.prototype.getShaderPrecisionFormat = function(shadertype, precisiontype)
{
	return new WebGLShaderPrecisionFormat(__WebGLRenderingContext_getShaderPrecisionFormat(this.__uid, shadertype, precisiontype), shadertype, precisiontype);
};

/** ================================================================================
 * Method: getShaderInfoLog(shader)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 * @return {String}
 */
WebGLRenderingContext.prototype.getShaderInfoLog = function(shader)
{
	return __WebGLRenderingContext_getShaderInfoLog(this.__uid, shader.__uid);
};

/** ================================================================================
 * Method: getShaderSource(shader)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 * @return {String}
 */
WebGLRenderingContext.prototype.getShaderSource = function(shader)
{
	return __WebGLRenderingContext_getShaderSource(this.__uid, shader.__uid);
};

/** ================================================================================
 * Method: getTexParameter(target, pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getTexParameter = function(target, pname)
{
	return __WebGLRenderingContext_getTexParameter(this.__uid, target, pname);
};

/** ================================================================================
 * Method: getUniform(program, location)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {WebGLUniformLocation} location
 * @return {Object}
 */
WebGLRenderingContext.prototype.getUniform = function(program, location)
{
	return __WebGLRenderingContext_getUniform(this.__uid, program.__uid, location.__uid);
};

/** ================================================================================
 * Method: getUniformLocation(program, name)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @param {String} name
 * @return {WebGLUniformLocation}
 */
WebGLRenderingContext.prototype.getUniformLocation = function(program, name)
{
	return new WebGLUniformLocation(__WebGLRenderingContext_getUniformLocation(this.__uid, program.__uid, name));
};

/** ================================================================================
 * Method: getVertexAttrib(index, pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} index
 * @param {Number} pname
 * @return {Object}
 */
WebGLRenderingContext.prototype.getVertexAttrib = function(index, pname)
{
	return __WebGLRenderingContext_getVertexAttrib(this.__uid, index, pname);
};

/** ================================================================================
 * Method: getVertexAttribOffset(index, pname)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} index
 * @param {Number} pname
 * @return {Number}
 */
WebGLRenderingContext.prototype.getVertexAttribOffset = function(index, pname)
{
	return __WebGLRenderingContext_getVertexAttribOffset(this.__uid, index, pname);
};

/** ================================================================================
 * Method: hint(target, mode)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} mode
 */
WebGLRenderingContext.prototype.hint = function(target, mode)
{
	return __WebGLRenderingContext_hint(this.__uid, target, mode);
};

/** ================================================================================
 * Method: isBuffer(buffer)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLBuffer} buffer
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isBuffer = function(buffer)
{
	return __WebGLRenderingContext_isBuffer(this.__uid, buffer.__uid);
};

/** ================================================================================
 * Method: isEnabled(cap)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} cap
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isEnabled = function(cap)
{
	return __WebGLRenderingContext_isEnabled(this.__uid, cap);
};

/** ================================================================================
 * Method: isFramebuffer(framebuffer)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLFramebuffer} framebuffer
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isFramebuffer = function(framebuffer)
{
	return __WebGLRenderingContext_isFramebuffer(this.__uid, framebuffer.__uid);
};

/** ================================================================================
 * Method: isProgram(program)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isProgram = function(program)
{
	return __WebGLRenderingContext_isProgram(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: isRenderbuffer(renderbuffer)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLRenderbuffer} renderbuffer
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isRenderbuffer = function(renderbuffer)
{
	return __WebGLRenderingContext_isRenderbuffer(this.__uid, renderbuffer.__uid);
};

/** ================================================================================
 * Method: isShader(shader)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isShader = function(shader)
{
	return __WebGLRenderingContext_isShader(this.__uid, shader.__uid);
};

/** ================================================================================
 * Method: isTexture(texture)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLTexture} texture
 * @return {Boolean}
 */
WebGLRenderingContext.prototype.isTexture = function(texture)
{
	return __WebGLRenderingContext_isTexture(this.__uid, texture.__uid);
};

/** ================================================================================
 * Method: lineWidth(width)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} width
 */
WebGLRenderingContext.prototype.lineWidth = function(width)
{
	return __WebGLRenderingContext_lineWidth(this.__uid, width);
};

/** ================================================================================
 * Method: linkProgram(program)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 */
WebGLRenderingContext.prototype.linkProgram = function(program)
{
	return __WebGLRenderingContext_linkProgram(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: pixelStorei(pname, param)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} pname
 * @param {Number} param
 */
WebGLRenderingContext.prototype.pixelStorei = function(pname, param)
{
	return __WebGLRenderingContext_pixelStorei(this.__uid, pname, param);
};

/** ================================================================================
 * Method: polygonOffset(factor, units)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} factor
 * @param {Number} units
 */
WebGLRenderingContext.prototype.polygonOffset = function(factor, units)
{
	return __WebGLRenderingContext_polygonOffset(this.__uid, factor, units);
};

/** ================================================================================
 * Method: readPixels(x, y, width, height, format, type, pixels)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} x
 * @param {Number} y
 * @param {Number} width
 * @param {Number} height
 * @param {Number} format
 * @param {Number} type
 * @param {ArrayBufferView} pixels
 */
WebGLRenderingContext.prototype.readPixels = function(x, y, width, height, format, type, pixels)
{
	return __WebGLRenderingContext_readPixels(this.__uid, x, y, width, height, format, type, pixels.buffer.__uid, pixels.byteOffset, pixels.length);
};

/** ================================================================================
 * Method: renderbufferStorage(target, internalformat, width, height)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} internalformat
 * @param {Number} width
 * @param {Number} height
 */
WebGLRenderingContext.prototype.renderbufferStorage = function(target, internalformat, width, height)
{
	return __WebGLRenderingContext_renderbufferStorage(this.__uid, target, internalformat, width, height);
};

/** ================================================================================
 * Method: sampleCoverage(value, invert)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} value
 * @param {Boolean} invert
 */
WebGLRenderingContext.prototype.sampleCoverage = function(value, invert)
{
	return __WebGLRenderingContext_sampleCoverage(this.__uid, value, invert);
};

/** ================================================================================
 * Method: scissor(x, y, width, height)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} x
 * @param {Number} y
 * @param {Number} width
 * @param {Number} height
 */
WebGLRenderingContext.prototype.scissor = function(x, y, width, height)
{
	return __WebGLRenderingContext_scissor(this.__uid, x, y, width, height);
};

/** ================================================================================
 * Method: shaderSource(shader, source)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLShader} shader
 * @param {String} source
 */
WebGLRenderingContext.prototype.shaderSource = function(shader, source)
{
	return __WebGLRenderingContext_shaderSource(this.__uid, shader.__uid, source);
};

/** ================================================================================
 * Method: stencilFunc(func, ref, mask)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} func
 * @param {Number} ref
 * @param {Number} mask
 */
WebGLRenderingContext.prototype.stencilFunc = function(func, ref, mask)
{
	return __WebGLRenderingContext_stencilFunc(this.__uid, func, ref, mask);
};

/** ================================================================================
 * Method: stencilFuncSeparate(face, func, ref, mask)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} face
 * @param {Number} func
 * @param {Number} ref
 * @param {Number} mask
 */
WebGLRenderingContext.prototype.stencilFuncSeparate = function(face, func, ref, mask)
{
	return __WebGLRenderingContext_stencilFuncSeparate(this.__uid, face, func, ref, mask);
};

/** ================================================================================
 * Method: stencilMask(mask)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} mask
 */
WebGLRenderingContext.prototype.stencilMask = function(mask)
{
	return __WebGLRenderingContext_stencilMask(this.__uid, mask);
};

/** ================================================================================
 * Method: stencilMaskSeparate(face, mask)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} face
 * @param {Number} mask
 */
WebGLRenderingContext.prototype.stencilMaskSeparate = function(face, mask)
{
	return __WebGLRenderingContext_stencilMaskSeparate(this.__uid, face, mask);
};

/** ================================================================================
 * Method: stencilOp(fail, zfail, zpass)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} fail
 * @param {Number} zfail
 * @param {Number} zpass
 */
WebGLRenderingContext.prototype.stencilOp = function(fail, zfail, zpass)
{
	return __WebGLRenderingContext_stencilOp(this.__uid, fail, zfail, zpass);
};

/** ================================================================================
 * Method: stencilOpSeparate(face, fail, zfail, zpass)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} face
 * @param {Number} fail
 * @param {Number} zfail
 * @param {Number} zpass
 */
WebGLRenderingContext.prototype.stencilOpSeparate = function(face, fail, zfail, zpass)
{
	return __WebGLRenderingContext_stencilOpSeparate(this.__uid, face, fail, zfail, zpass);
};

/** ================================================================================
 * Method: texImage2D(target, level, internalformat, width, height, border, format, type, pixels)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} level
 * @param {Number} internalformat
 * @param {Number} width
 * @param {Number} height
 * @param {Number} border
 * @param {Number} format
 * @param {Number} type
 * @param {ArrayBufferView} pixels
 */
WebGLRenderingContext.prototype.texImage2D = function()
{
	var target, level, internalformat, width, height, border, format, type, pixels, data, args = arguments;
	
	target 			= args[0];
	level 			= args[1];
	internalformat 	= args[2];

	if(args.length==9)
	{
		width 	= args[3];
		height 	= args[4];
		border 	= args[5];
		format 	= args[6];
		type 	= args[7];		
		data 	= args[8];
		
		return __WebGLRenderingContext_texImage2D(this.__uid, target, level, internalformat, width, height, border, format, type, data.__buffer.__uid, data.byteOffset, data.length * data.BYTES_PER_ELEMENT);		
	}
	else
	{
		format = args[3];
		type = args[4];
		data = args[5];

		if(data instanceof ImageData)
		{
		 	border = 0;
		 	width = data.width;
		 	height = data.height;		 			 	
		 	return __WebGLRenderingContext_texImage2D(this.__uid, target, level, internalformat, width, height, border, format, type, data.__buffer.__uid, 0, data.__buffer.byteLength);
		}
		else if(data instanceof HTMLImageElement)
		{
			border = 0;
			data = data.__imageData;
			width = data.width;
			height = data.height;		 			 			 	
			return __WebGLRenderingContext_texImage2D(this.__uid, target, level, internalformat, width, height, border, format, type, data.__buffer.__uid, 0, data.__buffer.byteLength);
		}
		else if(data instanceof HTMLCanvasElement)
		{
		 	border = 0;
		 	data = data.__imageData;
		 	width = data.width;
		 	height = data.height;		 			 			 	
		 	return __WebGLRenderingContext_texImage2D(this.__uid, target, level, internalformat, width, height, border, format, type, data.__buffer.__uid, 0, data.__buffer.byteLength);
		}
		else if(data instanceof HTMLVideoElement)
		{
			// To be decided.
			return null;
		}
		else alert("Error instanceof!");
 	}
};

/** ================================================================================
 * Method: texParameterf(target, pname, param)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} pname
 * @param {Number} param
 */
WebGLRenderingContext.prototype.texParameterf = function(target, pname, param)
{
	return __WebGLRenderingContext_texParameterf(this.__uid, target, pname, param);
};

/** ================================================================================
 * Method: texParameteri(target, pname, param)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} pname
 * @param {Number} param
 */
WebGLRenderingContext.prototype.texParameteri = function(target, pname, param)
{
	return __WebGLRenderingContext_texParameteri(this.__uid, target, pname, param);
};

/** ================================================================================
 * Method: texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} target
 * @param {Number} level
 * @param {Number} xoffset
 * @param {Number} yoffset
 * @param {Number} width
 * @param {Number} height
 * @param {Number} format
 * @param {Number} type
 * @param {ArrayBufferView} pixels
 */
WebGLRenderingContext.prototype.texSubImage2D = function(target, level, xoffset, yoffset, width, height, format, type, pixels)
{
	return __WebGLRenderingContext_texSubImage2D(this.__uid, target, level, xoffset, yoffset, width, height, format, type, pixels.__buffer.__uid, pixels.byteOffset, pixels.length);
};

/** ================================================================================
 * Method: uniform1f(location, x)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 */
WebGLRenderingContext.prototype.uniform1f = function(location, x)
{
	return __WebGLRenderingContext_uniform1f(this.__uid, location.__uid, x);
};

/** ================================================================================
 * Method: uniform1fv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Float32Array} v
 */
WebGLRenderingContext.prototype.uniform1fv = function(location, v)
{
	return __WebGLRenderingContext_uniform1fv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform1i(location, x)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 */
WebGLRenderingContext.prototype.uniform1i = function(location, x)
{
	return __WebGLRenderingContext_uniform1i(this.__uid, location.__uid, x);
};

/** ================================================================================
 * Method: uniform1iv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Int32Array} v
 */
WebGLRenderingContext.prototype.uniform1iv = function(location, v)
{
	return __WebGLRenderingContext_uniform1iv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform2f(location, x, y)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 * @param {Number} y
 */
WebGLRenderingContext.prototype.uniform2f = function(location, x, y)
{
	return __WebGLRenderingContext_uniform2f(this.__uid, location.__uid, x, y);
};

/** ================================================================================
 * Method: uniform2fv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Float32Array} v
 */
WebGLRenderingContext.prototype.uniform2fv = function(location, v)
{
	return __WebGLRenderingContext_uniform2fv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform2i(location, x, y)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 * @param {Number} y
 */
WebGLRenderingContext.prototype.uniform2i = function(location, x, y)
{
	return __WebGLRenderingContext_uniform2i(this.__uid, location.__uid, x, y);
};

/** ================================================================================
 * Method: uniform2iv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Int32Array} v
 */
WebGLRenderingContext.prototype.uniform2iv = function(location, v)
{
	return __WebGLRenderingContext_uniform2iv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform3f(location, x, y, z)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 */
WebGLRenderingContext.prototype.uniform3f = function(location, x, y, z)
{
	return __WebGLRenderingContext_uniform3f(this.__uid, location.__uid, x, y, z);
};

/** ================================================================================
 * Method: uniform3fv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Float32Array} v
 */
WebGLRenderingContext.prototype.uniform3fv = function(location, v)
{
	return __WebGLRenderingContext_uniform3fv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform3i(location, x, y, z)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 */
WebGLRenderingContext.prototype.uniform3i = function(location, x, y, z)
{
	return __WebGLRenderingContext_uniform3i(this.__uid, location.__uid, x, y, z);
};

/** ================================================================================
 * Method: uniform3iv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Int32Array} v
 */
WebGLRenderingContext.prototype.uniform3iv = function(location, v)
{
	return __WebGLRenderingContext_uniform3iv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform4f(location, x, y, z, w)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 * @param {Number} w
 */
WebGLRenderingContext.prototype.uniform4f = function(location, x, y, z, w)
{
	return __WebGLRenderingContext_uniform4f(this.__uid, location.__uid, x, y, z, w);
};

/** ================================================================================
 * Method: uniform4fv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Float32Array} v
 */
WebGLRenderingContext.prototype.uniform4fv = function(location, v)
{
	return __WebGLRenderingContext_uniform4fv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniform4i(location, x, y, z, w)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 * @param {Number} w
 */
WebGLRenderingContext.prototype.uniform4i = function(location, x, y, z, w)
{
	return __WebGLRenderingContext_uniform4i(this.__uid, location.__uid, x, y, z, w);
};

/** ================================================================================
 * Method: uniform4iv(location, v)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Int32Array} v
 */
WebGLRenderingContext.prototype.uniform4iv = function(location, v)
{
	return __WebGLRenderingContext_uniform4iv(this.__uid, location.__uid, v.buffer.__uid, v.byteOffset, v.length);
};

/** ================================================================================
 * Method: uniformMatrix2fv(location, transpose, value)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Boolean} transpose
 * @param {Float32Array} value
 */
WebGLRenderingContext.prototype.uniformMatrix2fv = function(location, transpose, value)
{
	return __WebGLRenderingContext_uniformMatrix2fv(this.__uid, location.__uid, transpose, value.buffer.__uid, value.byteOffset, value.length);
};

/** ================================================================================
 * Method: uniformMatrix3fv(location, transpose, value)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Boolean} transpose
 * @param {Float32Array} value
 */
WebGLRenderingContext.prototype.uniformMatrix3fv = function(location, transpose, value)
{
	return __WebGLRenderingContext_uniformMatrix3fv(this.__uid, location.__uid, transpose, value.buffer.__uid, value.byteOffset, value.length);
};

/** ================================================================================
 * Method: uniformMatrix4fv(location, transpose, value)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLUniformLocation} location
 * @param {Boolean} transpose
 * @param {Float32Array} value
 */
WebGLRenderingContext.prototype.uniformMatrix4fv = function(location, transpose, value)
{
	return __WebGLRenderingContext_uniformMatrix4fv(this.__uid, location.__uid, transpose, value.buffer.__uid, value.byteOffset, value.length);
};

/** ================================================================================
 * Method: useProgram(program)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 */
WebGLRenderingContext.prototype.useProgram = function(program)
{
	return __WebGLRenderingContext_useProgram(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: validateProgram(program)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {WebGLProgram} program
 */
WebGLRenderingContext.prototype.validateProgram = function(program)
{
	return __WebGLRenderingContext_validateProgram(this.__uid, program.__uid);
};

/** ================================================================================
 * Method: vertexAttrib1f(indx, x)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Number} x
 */
WebGLRenderingContext.prototype.vertexAttrib1f = function(indx, x)
{
	return __WebGLRenderingContext_vertexAttrib1f(this.__uid, indx, x);
};

/** ================================================================================
 * Method: vertexAttrib1fv(indx, values)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Float32Array} values
 */
WebGLRenderingContext.prototype.vertexAttrib1fv = function(indx, values)
{
	return __WebGLRenderingContext_vertexAttrib1fv(this.__uid, indx, values.buffer.__uid, values.byteOffset, values.length);
};

/** ================================================================================
 * Method: vertexAttrib2f(indx, x, y)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Number} x
 * @param {Number} y
 */
WebGLRenderingContext.prototype.vertexAttrib2f = function(indx, x, y)
{
	return __WebGLRenderingContext_vertexAttrib2f(this.__uid, indx, x, y);
};

/** ================================================================================
 * Method: vertexAttrib2fv(indx, values)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Float32Array} values
 */
WebGLRenderingContext.prototype.vertexAttrib2fv = function(indx, values)
{
	return __WebGLRenderingContext_vertexAttrib2fv(this.__uid, indx, values.buffer.__uid, values.byteOffset, values.length);
};

/** ================================================================================
 * Method: vertexAttrib3f(indx, x, y, z)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 */
WebGLRenderingContext.prototype.vertexAttrib3f = function(indx, x, y, z)
{
	return __WebGLRenderingContext_vertexAttrib3f(this.__uid, indx, x, y, z);
};

/** ================================================================================
 * Method: vertexAttrib3fv(indx, values)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Float32Array} values
 */
WebGLRenderingContext.prototype.vertexAttrib3fv = function(indx, values)
{
	return __WebGLRenderingContext_vertexAttrib3fv(this.__uid, indx, values.buffer.__uid, values.byteOffset, values.length);
};

/** ================================================================================
 * Method: vertexAttrib4f(indx, x, y, z, w)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Number} x
 * @param {Number} y
 * @param {Number} z
 * @param {Number} w
 */
WebGLRenderingContext.prototype.vertexAttrib4f = function(indx, x, y, z, w)
{
	return __WebGLRenderingContext_vertexAttrib4f(this.__uid, indx, x, y, z, w);
};

/** ================================================================================
 * Method: vertexAttrib4fv(indx, values)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Float32Array} values
 */
WebGLRenderingContext.prototype.vertexAttrib4fv = function(indx, values)
{
	return __WebGLRenderingContext_vertexAttrib4fv(this.__uid, indx, values.buffer.__uid, values.byteOffset, values.length);
};

/** ================================================================================
 * Method: vertexAttribPointer(indx, size, type, normalized, stride, offset)
 * Status: CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} indx
 * @param {Number} size
 * @param {Number} type
 * @param {Boolean} normalized
 * @param {Number} stride
 * @param {Number} offset
 */
WebGLRenderingContext.prototype.vertexAttribPointer = function(indx, size, type, normalized, stride, offset)
{
	return __WebGLRenderingContext_vertexAttribPointer(this.__uid, indx, size, type, normalized, stride, offset);
};

/** ================================================================================
 * Method: viewport(x, y, width, height)
 * Status: NOT-CHECKED
 * Description: 
 * @expose
 * @this {WebGLRenderingContext}
 * @param {Number} x
 * @param {Number} y
 * @param {Number} width
 * @param {Number} height
 */
WebGLRenderingContext.prototype.viewport = function(x, y, width, height)
{
	return __WebGLRenderingContext_viewport(this.__uid, x, y, width, height);
};


