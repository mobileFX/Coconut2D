#include "WebGLWrapper.h"

/*////////////////////////////////////////////////////////////////////////////////////////////////////////

   _       __     __    ________       ___    ____  ____
  | |     / /__  / /_  / ____/ /      /   |  / __ \/  _/
  | | /| / / _ \/ __ \/ / __/ /      / /| | / /_/ // /
  | |/ |/ /  __/ /_/ / /_/ / /___   / ___ |/ ____// /
  |__/|__/\___/_.___/\____/_____/  /_/  |_/_/   /___/


////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void* WebGLWrapper::getArrayBufferPointer(fxObjectUID uid, unsigned int offset)
{
	ArrayBuffer* t = (ArrayBuffer*)(uid);
	return (*t)[offset];
}

void WebGLWrapper::bind_WebGL_API(v8::Handle<v8::Object>& global)
{
	fxJSFunctionCB fun[] = {
		{"__WebGLRenderingContext_getContextAttributes", __WebGLRenderingContext_getContextAttributes, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isContextLost", __WebGLRenderingContext_isContextLost, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getSupportedExtensions", __WebGLRenderingContext_getSupportedExtensions, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getExtension", __WebGLRenderingContext_getExtension, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_activeTexture", __WebGLRenderingContext_activeTexture, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_attachShader", __WebGLRenderingContext_attachShader, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bindAttribLocation", __WebGLRenderingContext_bindAttribLocation, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bindBuffer", __WebGLRenderingContext_bindBuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bindFramebuffer", __WebGLRenderingContext_bindFramebuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bindRenderbuffer", __WebGLRenderingContext_bindRenderbuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bindTexture", __WebGLRenderingContext_bindTexture, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_blendColor", __WebGLRenderingContext_blendColor, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_blendEquation", __WebGLRenderingContext_blendEquation, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_blendEquationSeparate", __WebGLRenderingContext_blendEquationSeparate, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_blendFunc", __WebGLRenderingContext_blendFunc, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_blendFuncSeparate", __WebGLRenderingContext_blendFuncSeparate, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bufferData", __WebGLRenderingContext_bufferData, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_bufferSubData", __WebGLRenderingContext_bufferSubData, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_checkFramebufferStatus", __WebGLRenderingContext_checkFramebufferStatus, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_clear", __WebGLRenderingContext_clear, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_clearColor", __WebGLRenderingContext_clearColor, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_clearDepth", __WebGLRenderingContext_clearDepth, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_clearStencil", __WebGLRenderingContext_clearStencil, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_colorMask", __WebGLRenderingContext_colorMask, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_compileShader", __WebGLRenderingContext_compileShader, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_compressedTexImage2D", __WebGLRenderingContext_compressedTexImage2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_compressedTexSubImage2D", __WebGLRenderingContext_compressedTexSubImage2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_copyTexImage2D", __WebGLRenderingContext_copyTexImage2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_copyTexSubImage2D", __WebGLRenderingContext_copyTexSubImage2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_createBuffer", __WebGLRenderingContext_createBuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_createFramebuffer", __WebGLRenderingContext_createFramebuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_createProgram", __WebGLRenderingContext_createProgram, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_createRenderbuffer", __WebGLRenderingContext_createRenderbuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_createShader", __WebGLRenderingContext_createShader, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_createTexture", __WebGLRenderingContext_createTexture, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_cullFace", __WebGLRenderingContext_cullFace, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_deleteBuffer", __WebGLRenderingContext_deleteBuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_deleteFramebuffer", __WebGLRenderingContext_deleteFramebuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_deleteProgram", __WebGLRenderingContext_deleteProgram, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_deleteRenderbuffer", __WebGLRenderingContext_deleteRenderbuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_deleteShader", __WebGLRenderingContext_deleteShader, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_deleteTexture", __WebGLRenderingContext_deleteTexture, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_depthFunc", __WebGLRenderingContext_depthFunc, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_depthMask", __WebGLRenderingContext_depthMask, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_depthRange", __WebGLRenderingContext_depthRange, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_detachShader", __WebGLRenderingContext_detachShader, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_disable", __WebGLRenderingContext_disable, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_disableVertexAttribArray", __WebGLRenderingContext_disableVertexAttribArray, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_drawArrays", __WebGLRenderingContext_drawArrays, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_drawElements", __WebGLRenderingContext_drawElements, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_enable", __WebGLRenderingContext_enable, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_enableVertexAttribArray", __WebGLRenderingContext_enableVertexAttribArray, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_finish", __WebGLRenderingContext_finish, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_flush", __WebGLRenderingContext_flush, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_framebufferRenderbuffer", __WebGLRenderingContext_framebufferRenderbuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_framebufferTexture2D", __WebGLRenderingContext_framebufferTexture2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_frontFace", __WebGLRenderingContext_frontFace, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_generateMipmap", __WebGLRenderingContext_generateMipmap, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getActiveAttrib", __WebGLRenderingContext_getActiveAttrib, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getActiveUniform", __WebGLRenderingContext_getActiveUniform, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getAttachedShaders", __WebGLRenderingContext_getAttachedShaders, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getAttribLocation", __WebGLRenderingContext_getAttribLocation, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getBufferParameter", __WebGLRenderingContext_getBufferParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getParameter", __WebGLRenderingContext_getParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getError", __WebGLRenderingContext_getError, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getFramebufferAttachmentParameter", __WebGLRenderingContext_getFramebufferAttachmentParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getProgramParameter", __WebGLRenderingContext_getProgramParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getProgramInfoLog", __WebGLRenderingContext_getProgramInfoLog, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getRenderbufferParameter", __WebGLRenderingContext_getRenderbufferParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getShaderParameter", __WebGLRenderingContext_getShaderParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getShaderPrecisionFormat", __WebGLRenderingContext_getShaderPrecisionFormat, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getShaderInfoLog", __WebGLRenderingContext_getShaderInfoLog, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getShaderSource", __WebGLRenderingContext_getShaderSource, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getTexParameter", __WebGLRenderingContext_getTexParameter, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getUniform", __WebGLRenderingContext_getUniform, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getUniformLocation", __WebGLRenderingContext_getUniformLocation, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getVertexAttrib", __WebGLRenderingContext_getVertexAttrib, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_getVertexAttribOffset", __WebGLRenderingContext_getVertexAttribOffset, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_hint", __WebGLRenderingContext_hint, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isBuffer", __WebGLRenderingContext_isBuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isEnabled", __WebGLRenderingContext_isEnabled, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isFramebuffer", __WebGLRenderingContext_isFramebuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isProgram", __WebGLRenderingContext_isProgram, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isRenderbuffer", __WebGLRenderingContext_isRenderbuffer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isShader", __WebGLRenderingContext_isShader, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_isTexture", __WebGLRenderingContext_isTexture, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_lineWidth", __WebGLRenderingContext_lineWidth, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_linkProgram", __WebGLRenderingContext_linkProgram, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_pixelStorei", __WebGLRenderingContext_pixelStorei, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_polygonOffset", __WebGLRenderingContext_polygonOffset, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_readPixels", __WebGLRenderingContext_readPixels, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_renderbufferStorage", __WebGLRenderingContext_renderbufferStorage, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_sampleCoverage", __WebGLRenderingContext_sampleCoverage, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_scissor", __WebGLRenderingContext_scissor, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_shaderSource", __WebGLRenderingContext_shaderSource, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_stencilFunc", __WebGLRenderingContext_stencilFunc, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_stencilFuncSeparate", __WebGLRenderingContext_stencilFuncSeparate, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_stencilMask", __WebGLRenderingContext_stencilMask, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_stencilMaskSeparate", __WebGLRenderingContext_stencilMaskSeparate, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_stencilOp", __WebGLRenderingContext_stencilOp, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_stencilOpSeparate", __WebGLRenderingContext_stencilOpSeparate, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_texImage2D", __WebGLRenderingContext_texImage2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_texParameterf", __WebGLRenderingContext_texParameterf, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_texParameteri", __WebGLRenderingContext_texParameteri, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_texSubImage2D", __WebGLRenderingContext_texSubImage2D, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform1f", __WebGLRenderingContext_uniform1f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform1fv", __WebGLRenderingContext_uniform1fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform1i", __WebGLRenderingContext_uniform1i, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform1iv", __WebGLRenderingContext_uniform1iv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform2f", __WebGLRenderingContext_uniform2f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform2fv", __WebGLRenderingContext_uniform2fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform2i", __WebGLRenderingContext_uniform2i, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform2iv", __WebGLRenderingContext_uniform2iv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform3f", __WebGLRenderingContext_uniform3f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform3fv", __WebGLRenderingContext_uniform3fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform3i", __WebGLRenderingContext_uniform3i, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform3iv", __WebGLRenderingContext_uniform3iv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform4f", __WebGLRenderingContext_uniform4f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform4fv", __WebGLRenderingContext_uniform4fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform4i", __WebGLRenderingContext_uniform4i, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniform4iv", __WebGLRenderingContext_uniform4iv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniformMatrix2fv", __WebGLRenderingContext_uniformMatrix2fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniformMatrix3fv", __WebGLRenderingContext_uniformMatrix3fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_uniformMatrix4fv", __WebGLRenderingContext_uniformMatrix4fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_useProgram", __WebGLRenderingContext_useProgram, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_validateProgram", __WebGLRenderingContext_validateProgram, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib1f", __WebGLRenderingContext_vertexAttrib1f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib1fv", __WebGLRenderingContext_vertexAttrib1fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib2f", __WebGLRenderingContext_vertexAttrib2f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib2fv", __WebGLRenderingContext_vertexAttrib2fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib3f", __WebGLRenderingContext_vertexAttrib3f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib3fv", __WebGLRenderingContext_vertexAttrib3fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib4f", __WebGLRenderingContext_vertexAttrib4f, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttrib4fv", __WebGLRenderingContext_vertexAttrib4fv, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_vertexAttribPointer", __WebGLRenderingContext_vertexAttribPointer, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_viewport", __WebGLRenderingContext_viewport, fxJSPropertyAttributeNone},
		{nullptr, nullptr, fxJSPropertyAttributeNone}};

		// Bind Global functions
		for(size_t i = 0; fun[i].name; i++)
		{
            //global->Set(v8::String::New(fun[i].name), v8::FunctionTemplate::New(fun[i].callAsFunction)->GetFunction(), fun[i].attributes);
		}
}

/** ================================================================================
 * JavaScript: getContextAttributes()
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getContextAttributes)
{
    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isContextLost()
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isContextLost)
{
    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getSupportedExtensions()
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getSupportedExtensions)
{
    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getExtension(name)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getExtension)
{
    /* Allocations */
    static size_t str_size_name;
    static char cstr_name[64];

    /* Decompose Arguments */
    fxJSString name = fxJSAllocStringCopy(fxJSGetArg(1));
    str_size_name = fxJSStringGetSize(name);
    fxJSStringToBuffer(name, cstr_name, str_size_name);
    cstr_name[str_size_name] = 0;

    /* OpenGL Method Call */
    // TODO: glGetExtension(cstr_name);

    /* Deallocations */
    fxJSFreeString(name);

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: activeTexture(texture)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_activeTexture)
{
    /* Allocations */
    static GLenum texture;

    /* Decompose Arguments */
    texture = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glActiveTexture(texture);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: attachShader(program, shader)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_attachShader)
{
    /* Allocations */
    static fxObjectUID program;
    static fxObjectUID shader;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    shader = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glAttachShader(program, shader);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bindAttribLocation(program, index, name)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bindAttribLocation)
{
    /* Allocations */
    static fxObjectUID program;
    static GLuint index;
    static size_t str_size_name;
    static char cstr_name[64];

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    index = fxJSCastNumber(fxJSGetArg(2));
    fxJSString name = fxJSAllocStringCopy(fxJSGetArg(3));
    str_size_name = fxJSStringGetSize(name);
    fxJSStringToBuffer(name, cstr_name, str_size_name);
    cstr_name[str_size_name] = 0;

    /* OpenGL Method Call */
    glBindAttribLocation(program, index, cstr_name);

    /* Deallocations */
    fxJSFreeString(name);

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bindBuffer(target, buffer)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bindBuffer)
{
    /* Allocations */
    static GLenum target;
    static fxObjectUID buffer;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    buffer = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glBindBuffer(target, buffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bindFramebuffer(target, framebuffer)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bindFramebuffer)
{
    /* Allocations */
    static GLenum target;
    static fxObjectUID framebuffer;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    framebuffer = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glBindFramebuffer(target, framebuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bindRenderbuffer(target, renderbuffer)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bindRenderbuffer)
{
    /* Allocations */
    static GLenum target;
    static fxObjectUID renderbuffer;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    renderbuffer = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glBindRenderbuffer(target, renderbuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bindTexture(target, texture)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bindTexture)
{
    /* Allocations */
    static GLenum target;
    static fxObjectUID texture;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    texture = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glBindTexture(target, texture);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: blendColor(red, green, blue, alpha)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_blendColor)
{
    /* Allocations */
    static GLclampf red;
    static GLclampf green;
    static GLclampf blue;
    static GLclampf alpha;

    /* Decompose Arguments */
    red = fxJSCastNumber(fxJSGetArg(1));
    green = fxJSCastNumber(fxJSGetArg(2));
    blue = fxJSCastNumber(fxJSGetArg(3));
    alpha = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glBlendColor(red, green, blue, alpha);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: blendEquation(mode)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_blendEquation)
{
    /* Allocations */
    static GLenum mode;

    /* Decompose Arguments */
    mode = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glBlendEquation(mode);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: blendEquationSeparate(modeRGB, modeAlpha)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_blendEquationSeparate)
{
    /* Allocations */
    static GLenum modeRGB;
    static GLenum modeAlpha;

    /* Decompose Arguments */
    modeRGB = fxJSCastNumber(fxJSGetArg(1));
    modeAlpha = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glBlendEquationSeparate(modeRGB, modeAlpha);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: blendFunc(sfactor, dfactor)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_blendFunc)
{
    /* Allocations */
    static GLenum sfactor;
    static GLenum dfactor;

    /* Decompose Arguments */
    sfactor = fxJSCastNumber(fxJSGetArg(1));
    dfactor = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glBlendFunc(sfactor, dfactor);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: blendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_blendFuncSeparate)
{
    /* Allocations */
    static GLenum srcRGB;
    static GLenum dstRGB;
    static GLenum srcAlpha;
    static GLenum dstAlpha;

    /* Decompose Arguments */
    srcRGB = fxJSCastNumber(fxJSGetArg(1));
    dstRGB = fxJSCastNumber(fxJSGetArg(2));
    srcAlpha = fxJSCastNumber(fxJSGetArg(3));
    dstAlpha = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bufferData(target, data, usage)
 * Native: bufferData(target, v_uid, v_offset, v_length, usage)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bufferData)
{
    /* Allocations */
    static GLenum target;
    static fxObjectUID data_uid;
    static unsigned int data_offset;
    static GLsizei data_length;
    static GLvoid* data_ptr;
    static GLenum usage;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    data_uid = fxJSCastNumber(fxJSGetArg(2));
    data_offset = fxJSCastNumber(fxJSGetArg(3));
    data_length = fxJSCastNumber(fxJSGetArg(4));
    data_ptr = getArrayBufferPointer(data_uid, data_offset);
    usage = fxJSCastNumber(fxJSGetArg(5));

    /* OpenGL Method Call */
    glBufferData(target, data_length, data_ptr, usage);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: bufferSubData(target, offset, data)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_bufferSubData)
{
    /* Allocations */
    static GLenum target;
    static GLintptr offset;
    static fxObjectUID data_uid;
    static unsigned int data_offset;
    static GLsizei data_length;
    static GLvoid* data_ptr;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    offset = fxJSCastNumber(fxJSGetArg(2));
    data_uid = fxJSCastNumber(fxJSGetArg(3));
    data_offset = fxJSCastNumber(fxJSGetArg(4));
    data_length = fxJSCastNumber(fxJSGetArg(5));
    data_ptr = getArrayBufferPointer(data_uid, data_offset);

    /* OpenGL Method Call */
    glBufferSubData(target, offset, data_length, data_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: checkFramebufferStatus(target)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_checkFramebufferStatus)
{
    /* Allocations */
    static GLenum target;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glCheckFramebufferStatus(target);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: clear(mask)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_clear)
{
    /* Allocations */
    static GLbitfield mask;

    /* Decompose Arguments */
    mask = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glClear(mask);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: clearColor(red, green, blue, alpha)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_clearColor)
{
    /* Allocations */
    static GLclampf red;
    static GLclampf green;
    static GLclampf blue;
    static GLclampf alpha;

    /* Decompose Arguments */
    red = fxJSCastNumber(fxJSGetArg(1));
    green = fxJSCastNumber(fxJSGetArg(2));
    blue = fxJSCastNumber(fxJSGetArg(3));
    alpha = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glClearColor(red, green, blue, alpha);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: clearDepth(depth)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_clearDepth)
{
    /* Allocations */
    static GLclampf depth;

    /* Decompose Arguments */
    depth = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    // TODO: glClearDepth(depth);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: clearStencil(s)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_clearStencil)
{
    /* Allocations */
    static GLint s;

    /* Decompose Arguments */
    s = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glClearStencil(s);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: colorMask(red, green, blue, alpha)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_colorMask)
{
    /* Allocations */
    static GLboolean red;
    static GLboolean green;
    static GLboolean blue;
    static GLboolean alpha;

    /* Decompose Arguments */
    red = fxJSCastBoolean(fxJSGetArg(1));
    green = fxJSCastBoolean(fxJSGetArg(2));
    blue = fxJSCastBoolean(fxJSGetArg(3));
    alpha = fxJSCastBoolean(fxJSGetArg(4));

    /* OpenGL Method Call */
    glColorMask(red, green, blue, alpha);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: compileShader(shader)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_compileShader)
{
    /* Allocations */
    static fxObjectUID shader;

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glCompileShader(shader);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: compressedTexImage2D(target, level, internalformat, width, height, border, data)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_compressedTexImage2D)
{
    /* Allocations */
    static GLenum target;
    static GLint level;
    static GLenum internalformat;
    static GLsizei width;
    static GLsizei height;
    static GLint border;
    static fxObjectUID data_uid;
    static unsigned int data_offset;
    static GLsizei data_length;
    static GLvoid* data_ptr;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    level = fxJSCastNumber(fxJSGetArg(2));
    internalformat = fxJSCastNumber(fxJSGetArg(3));
    width = fxJSCastNumber(fxJSGetArg(4));
    height = fxJSCastNumber(fxJSGetArg(5));
    border = fxJSCastNumber(fxJSGetArg(6));
    data_uid = fxJSCastNumber(fxJSGetArg(7));
    data_offset = fxJSCastNumber(fxJSGetArg(8));
    data_length = fxJSCastNumber(fxJSGetArg(9));
    data_ptr = getArrayBufferPointer(data_uid, data_offset);

    /* OpenGL Method Call */
    glCompressedTexImage2D(target, level, internalformat, width, height, border, data_length, data_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: compressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, data)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_compressedTexSubImage2D)
{
    /* Allocations */
    static GLenum target;
    static GLint level;
    static GLint xoffset;
    static GLint yoffset;
    static GLsizei width;
    static GLsizei height;
    static GLenum format;
    static fxObjectUID data_uid;
    static unsigned int data_offset;
    static GLsizei data_length;
    static GLvoid* data_ptr;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    level = fxJSCastNumber(fxJSGetArg(2));
    xoffset = fxJSCastNumber(fxJSGetArg(3));
    yoffset = fxJSCastNumber(fxJSGetArg(4));
    width = fxJSCastNumber(fxJSGetArg(5));
    height = fxJSCastNumber(fxJSGetArg(6));
    format = fxJSCastNumber(fxJSGetArg(7));
    data_uid = fxJSCastNumber(fxJSGetArg(8));
    data_offset = fxJSCastNumber(fxJSGetArg(9));
    data_length = fxJSCastNumber(fxJSGetArg(10));
    data_ptr = getArrayBufferPointer(data_uid, data_offset);

    /* OpenGL Method Call */
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, data_length, data_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: copyTexImage2D(target, level, internalformat, x, y, width, height, border)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_copyTexImage2D)
{
    /* Allocations */
    static GLenum target;
    static GLint level;
    static GLenum internalformat;
    static GLint x;
    static GLint y;
    static GLsizei width;
    static GLsizei height;
    static GLint border;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    level = fxJSCastNumber(fxJSGetArg(2));
    internalformat = fxJSCastNumber(fxJSGetArg(3));
    x = fxJSCastNumber(fxJSGetArg(4));
    y = fxJSCastNumber(fxJSGetArg(5));
    width = fxJSCastNumber(fxJSGetArg(6));
    height = fxJSCastNumber(fxJSGetArg(7));
    border = fxJSCastNumber(fxJSGetArg(8));

    /* OpenGL Method Call */
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: copyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_copyTexSubImage2D)
{
    /* Allocations */
    static GLenum target;
    static GLint level;
    static GLint xoffset;
    static GLint yoffset;
    static GLint x;
    static GLint y;
    static GLsizei width;
    static GLsizei height;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    level = fxJSCastNumber(fxJSGetArg(2));
    xoffset = fxJSCastNumber(fxJSGetArg(3));
    yoffset = fxJSCastNumber(fxJSGetArg(4));
    x = fxJSCastNumber(fxJSGetArg(5));
    y = fxJSCastNumber(fxJSGetArg(6));
    width = fxJSCastNumber(fxJSGetArg(7));
    height = fxJSCastNumber(fxJSGetArg(8));

    /* OpenGL Method Call */
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: createBuffer()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_createBuffer)
{
    GLuint id;
    glGenBuffers(1, &id);
    return fxJSMakeNumber(id);
}

/** ================================================================================
 * JavaScript: createFramebuffer()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_createFramebuffer)
{
    GLuint id;
    glGenFramebuffers(1, &id);
    return fxJSMakeNumber(id);
}

/** ================================================================================
 * JavaScript: createProgram()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_createProgram)
{
    return fxJSMakeNumber(glCreateProgram());
}

/** ================================================================================
 * JavaScript: createRenderbuffer()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_createRenderbuffer)
{
    GLuint id;
    glGenRenderbuffers(1, &id);
    return fxJSMakeNumber(id);
}

/** ================================================================================
 * JavaScript: createShader(type)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_createShader)
{
    /* Allocations */
    static GLenum type;

    /* Decompose Arguments */
    type = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    return fxJSMakeNumber(glCreateShader(type));
}

/** ================================================================================
 * JavaScript: createTexture()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_createTexture)
{
    GLuint id;
    glGenTextures(1, &id);
    return fxJSMakeNumber(id);
}

/** ================================================================================
 * JavaScript: cullFace(mode)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_cullFace)
{
    /* Allocations */
    static GLenum mode;

    /* Decompose Arguments */
    mode = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glCullFace(mode);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: deleteBuffer(buffer)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_deleteBuffer)
{
    /* Allocations */
    static GLuint buffer;

    /* Decompose Arguments */
    buffer = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDeleteBuffers(1, &buffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: deleteFramebuffer(framebuffer)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_deleteFramebuffer)
{
    /* Allocations */
    static GLuint framebuffer;

    /* Decompose Arguments */
    framebuffer = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDeleteFramebuffers(1, &framebuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: deleteProgram(program)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_deleteProgram)
{
    /* Allocations */
    static GLuint program;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDeleteProgram(program);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: deleteRenderbuffer(renderbuffer)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_deleteRenderbuffer)
{
    /* Allocations */
    static GLuint renderbuffer;

    /* Decompose Arguments */
    renderbuffer = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDeleteRenderbuffers(1, &renderbuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: deleteShader(shader)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_deleteShader)
{
    /* Allocations */
    static GLuint shader;

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDeleteShader(shader);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: deleteTexture(texture)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_deleteTexture)
{
    /* Allocations */
    static GLuint texture;

    /* Decompose Arguments */
    texture = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDeleteTextures(1, &texture);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: depthFunc(func)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_depthFunc)
{
    /* Allocations */
    static GLenum func;

    /* Decompose Arguments */
    func = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDepthFunc(func);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: depthMask(flag)
 * Status: TO-DO
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_depthMask)
{
    /* Allocations */
    static GLboolean flag;

    /* Decompose Arguments */
    flag = fxJSCastBoolean(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDepthMask(flag);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: depthRange(zNear, zFar)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_depthRange)
{
    /* Allocations */
    static GLclampf zNear;
    static GLclampf zFar;

    /* Decompose Arguments */
    zNear = fxJSCastNumber(fxJSGetArg(1));
    zFar = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glDepthRange(zNear, zFar);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: detachShader(program, shader)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_detachShader)
{
    /* Allocations */
    static fxObjectUID program;
    static fxObjectUID shader;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    shader = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glDetachShader(program, shader);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: disable(cap)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_disable)
{
    /* Allocations */
    static GLenum cap;

    /* Decompose Arguments */
    cap = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDisable(cap);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: disableVertexAttribArray(index)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_disableVertexAttribArray)
{
    /* Allocations */
    static GLuint index;

    /* Decompose Arguments */
    index = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glDisableVertexAttribArray(index);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: drawArrays(mode, first, count)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_drawArrays)
{
    /* Allocations */
    static GLenum mode;
    static GLint first;
    static GLsizei count;

    /* Decompose Arguments */
    mode = fxJSCastNumber(fxJSGetArg(1));
    first = fxJSCastNumber(fxJSGetArg(2));
    count = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glDrawArrays(mode, first, count);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: drawElements(mode, count, type, offset)
 * Status: TO-DO
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_drawElements)
{
    /* Allocations */
    static GLenum mode;
    static GLsizei count;
    static GLenum type;
    static GLintptr offset;

    /* Decompose Arguments */
    mode = fxJSCastNumber(fxJSGetArg(1));
    count = fxJSCastNumber(fxJSGetArg(2));
    type = fxJSCastNumber(fxJSGetArg(3));
    offset = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    //glDrawElements(mode, count, type, offset);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: enable(cap)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_enable)
{
    /* Allocations */
    static GLenum cap;

    /* Decompose Arguments */
    cap = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glEnable(cap);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: enableVertexAttribArray(index)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_enableVertexAttribArray)
{
    /* Allocations */
    static GLuint index;

    /* Decompose Arguments */
    index = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glEnableVertexAttribArray(index);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: finish()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_finish)
{
    glFinish();
    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: flush()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_flush)
{
    glFlush();
    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: framebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_framebufferRenderbuffer)
{
    /* Allocations */
    static GLenum target;
    static GLenum attachment;
    static GLenum renderbuffertarget;
    static fxObjectUID renderbuffer;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    attachment = fxJSCastNumber(fxJSGetArg(2));
    renderbuffertarget = fxJSCastNumber(fxJSGetArg(3));
    renderbuffer = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: framebufferTexture2D(target, attachment, textarget, texture, level)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_framebufferTexture2D)
{
    /* Allocations */
    static GLenum target;
    static GLenum attachment;
    static GLenum textarget;
    static fxObjectUID texture;
    static GLint level;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    attachment = fxJSCastNumber(fxJSGetArg(2));
    textarget = fxJSCastNumber(fxJSGetArg(3));
    texture = fxJSCastNumber(fxJSGetArg(4));
    level = fxJSCastNumber(fxJSGetArg(5));

    /* OpenGL Method Call */
    glFramebufferTexture2D(target, attachment, textarget, texture, level);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: frontFace(mode)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_frontFace)
{
    /* Allocations */
    static GLenum mode;

    /* Decompose Arguments */
    mode = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glFrontFace(mode);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: generateMipmap(target)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_generateMipmap)
{
    /* Allocations */
    static GLenum target;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glGenerateMipmap(target);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getActiveAttrib(program, index)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getActiveAttrib)
{
    /* Allocations */
    static fxObjectUID program;
    static GLuint index;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    index = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetActiveAttrib(program, index);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getActiveUniform(program, index)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getActiveUniform)
{
    /* Allocations */
    static fxObjectUID program;
    static GLuint index;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    index = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetActiveUniform(program, index);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getAttachedShaders(program)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getAttachedShaders)
{
    /* Allocations */
    static fxObjectUID program;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    // TODO: glGetAttachedShaders(program);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getAttribLocation(program, name)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getAttribLocation)
{
    /* Allocations */
    static GLuint program;
    static size_t str_size_name;
    static GLchar cstr_name[64];
    static GLint ret;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    fxJSString name = fxJSAllocStringCopy(fxJSGetArg(2));
    str_size_name = fxJSStringGetSize(name);
    fxJSStringToBuffer(name, cstr_name, str_size_name);
    cstr_name[str_size_name] = 0;

    /* OpenGL Method Call */
    ret = glGetAttribLocation(program, cstr_name);

    /* Deallocations */
    fxJSFreeString(name);

    return fxJSMakeNumber(ret);
}

/** ================================================================================
 * JavaScript: getBufferParameter(target, pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getBufferParameter)
{
    /* Allocations */
    static GLenum target;
    static GLenum pname;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetBufferParameter(target, pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getParameter(pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getParameter)
{
    /* Allocations */
    static GLenum pname;

    /* Decompose Arguments */
    pname = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    // TODO: glGetParameter(pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getError()
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getError)
{
    return fxJSMakeNumber(glGetError());
}

/** ================================================================================
 * JavaScript: getFramebufferAttachmentParameter(target, attachment, pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getFramebufferAttachmentParameter)
{
    /* Allocations */
    static GLenum target;
    static GLenum attachment;
    static GLenum pname;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    attachment = fxJSCastNumber(fxJSGetArg(2));
    pname = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    // TODO: glGetFramebufferAttachmentParameter(target, attachment, pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getProgramParameter(program, pname)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getProgramParameter)
{
    /* Allocations */
    static GLuint program;
    static GLenum pname;
    static GLint params;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glGetProgramiv(program, pname, &params);

    switch(pname)
    {
    case GL_DELETE_STATUS:
    case GL_LINK_STATUS:
    case GL_VALIDATE_STATUS:
        return fxJSMakeBoolean(params==0 ? false : true);
        break;

    case GL_ATTACHED_SHADERS:
    case GL_ACTIVE_ATTRIBUTES:
    case GL_ACTIVE_UNIFORMS:
        return fxJSMakeNumber(params);
        break;
    }

    /* Deallocations */
    return fxJSMakeNull();
}

/** ================================================================================
 * JavaScript: getProgramInfoLog(program)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getProgramInfoLog)
{
    /* Allocations */
    static fxObjectUID program;
    static GLsizei length;
    static GLchar* infoLog = new GLchar[INFO_LOG_BUFFER_SIZE]; // TODO delete[]

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glGetProgramInfoLog(program, INFO_LOG_BUFFER_SIZE, &length, infoLog);
    infoLog[length] = 0;

    fxJSString jstr = fxJSAllocString(infoLog);
    fxJSValue ret = fxJSMakeString(jstr);

    /* Deallocations */
    fxJSFreeString(jstr);

    return ret;
}

/** ================================================================================
 * JavaScript: getRenderbufferParameter(target, pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getRenderbufferParameter)
{
    /* Allocations */
    static GLenum target;
    static GLenum pname;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetRenderbufferParameter(target, pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getShaderParameter(shader, pname)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getShaderParameter)
{
    /* Allocations */
    static fxObjectUID shader;
    static GLenum pname;
    static GLint params;

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glGetShaderiv(shader, pname, &params);
    switch(pname)
    {
    case GL_DELETE_STATUS:
    case GL_COMPILE_STATUS:
        return fxJSMakeBoolean(params==0? false: true);
        break;

    case GL_SHADER_TYPE:
        return fxJSMakeNumber(params);
        break;
    }

    /* Deallocations */

    return fxJSMakeNull();
}

/** ================================================================================
 * JavaScript: getShaderPrecisionFormat(shadertype, precisiontype)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getShaderPrecisionFormat)
{
    /* Allocations */
    static GLenum shadertype;
    static GLenum precisiontype;

    /* Decompose Arguments */
    shadertype = fxJSCastNumber(fxJSGetArg(1));
    precisiontype = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetShaderPrecisionFormat(shadertype, precisiontype);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getShaderInfoLog(shader)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getShaderInfoLog)
{
    /* Allocations */
    static fxObjectUID shader;
    static GLsizei length;
    static GLchar* infoLog = new GLchar[INFO_LOG_BUFFER_SIZE]; // TODO delete[]

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glGetShaderInfoLog(shader, INFO_LOG_BUFFER_SIZE, &length, infoLog);
    infoLog[length] = 0;

    fxJSString jstr = fxJSAllocString(infoLog);
    fxJSValue ret = fxJSMakeString(jstr);

    /* Deallocations */
    fxJSFreeString(jstr);

    return ret;
}

/** ================================================================================
 * JavaScript: getShaderSource(shader)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getShaderSource)
{
    /* Allocations */
    static fxObjectUID shader;

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    // TODO: glGetShaderSource(shader);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getTexParameter(target, pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getTexParameter)
{
    /* Allocations */
    static GLenum target;
    static GLenum pname;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetTexParameter(target, pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getUniform(program, location)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getUniform)
{
    /* Allocations */
    static fxObjectUID program;
    static fxObjectUID location;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    location = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetUniform(program, location);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getUniformLocation(program, name)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getUniformLocation)
{
    /* Allocations */
    static GLuint program;
    static size_t str_size_name;
    static GLchar cstr_name[64];
    static GLint ret;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));
    fxJSString name = fxJSAllocStringCopy(fxJSGetArg(2));
    str_size_name = fxJSStringGetSize(name);
    fxJSStringToBuffer(name, cstr_name, str_size_name);
    cstr_name[str_size_name] = 0;

    /* OpenGL Method Call */
    ret = glGetUniformLocation(program, cstr_name);

    /* Deallocations */
    fxJSFreeString(name);

    return fxJSMakeNumber(ret);
}

/** ================================================================================
 * JavaScript: getVertexAttrib(index, pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getVertexAttrib)
{
    /* Allocations */
    static GLuint index;
    static GLenum pname;

    /* Decompose Arguments */
    index = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetVertexAttrib(index, pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: getVertexAttribOffset(index, pname)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_getVertexAttribOffset)
{
    /* Allocations */
    static GLuint index;
    static GLenum pname;

    /* Decompose Arguments */
    index = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    // TODO: glGetVertexAttribOffset(index, pname);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: hint(target, mode)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_hint)
{
    /* Allocations */
    static GLenum target;
    static GLenum mode;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    mode = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glHint(target, mode);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isBuffer(buffer)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isBuffer)
{
    /* Allocations */
    static fxObjectUID buffer;

    /* Decompose Arguments */
    buffer = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsBuffer(buffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isEnabled(cap)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isEnabled)
{
    /* Allocations */
    static GLenum cap;

    /* Decompose Arguments */
    cap = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsEnabled(cap);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isFramebuffer(framebuffer)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isFramebuffer)
{
    /* Allocations */
    static fxObjectUID framebuffer;

    /* Decompose Arguments */
    framebuffer = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsFramebuffer(framebuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isProgram(program)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isProgram)
{
    /* Allocations */
    static fxObjectUID program;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsProgram(program);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isRenderbuffer(renderbuffer)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isRenderbuffer)
{
    /* Allocations */
    static fxObjectUID renderbuffer;

    /* Decompose Arguments */
    renderbuffer = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsRenderbuffer(renderbuffer);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isShader(shader)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isShader)
{
    /* Allocations */
    static fxObjectUID shader;

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsShader(shader);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: isTexture(texture)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_isTexture)
{
    /* Allocations */
    static fxObjectUID texture;

    /* Decompose Arguments */
    texture = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glIsTexture(texture);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: lineWidth(width)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_lineWidth)
{
    /* Allocations */
    static GLfloat width;

    /* Decompose Arguments */
    width = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glLineWidth(width);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: linkProgram(program)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_linkProgram)
{
    /* Allocations */
    static GLuint program;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glLinkProgram(program);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: pixelStorei(pname, param)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_pixelStorei)
{
    /* Allocations */
    static GLenum pname;
    static GLint param;

    /* Decompose Arguments */
    pname = fxJSCastNumber(fxJSGetArg(1));
    param = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glPixelStorei(pname, param);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: polygonOffset(factor, units)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_polygonOffset)
{
    /* Allocations */
    static GLfloat factor;
    static GLfloat units;

    /* Decompose Arguments */
    factor = fxJSCastNumber(fxJSGetArg(1));
    units = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glPolygonOffset(factor, units);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: readPixels(x, y, width, height, format, type, pixels)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_readPixels)
{
    /* Allocations */
    static GLint x;
    static GLint y;
    static GLsizei width;
    static GLsizei height;
    static GLenum format;
    static GLenum type;
    static fxObjectUID pixels_uid;
    static unsigned int pixels_offset;
    static GLsizei pixels_length;
    static GLvoid* pixels_ptr;

    /* Decompose Arguments */
    x = fxJSCastNumber(fxJSGetArg(1));
    y = fxJSCastNumber(fxJSGetArg(2));
    width = fxJSCastNumber(fxJSGetArg(3));
    height = fxJSCastNumber(fxJSGetArg(4));
    format = fxJSCastNumber(fxJSGetArg(5));
    type = fxJSCastNumber(fxJSGetArg(6));
    pixels_uid = fxJSCastNumber(fxJSGetArg(7));
    pixels_offset = fxJSCastNumber(fxJSGetArg(8));
    pixels_length = fxJSCastNumber(fxJSGetArg(9));
    pixels_ptr = getArrayBufferPointer(pixels_uid, pixels_offset);

    /* OpenGL Method Call */
    // TODO: glReadPixels(x, y, width, height, format, type, pixels_length, pixels_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: renderbufferStorage(target, internalformat, width, height)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_renderbufferStorage)
{
    /* Allocations */
    static GLenum target;
    static GLenum internalformat;
    static GLsizei width;
    static GLsizei height;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    internalformat = fxJSCastNumber(fxJSGetArg(2));
    width = fxJSCastNumber(fxJSGetArg(3));
    height = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glRenderbufferStorage(target, internalformat, width, height);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: sampleCoverage(value, invert)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_sampleCoverage)
{
    /* Allocations */
    static GLclampf value;
    static GLboolean invert;

    /* Decompose Arguments */
    value = fxJSCastNumber(fxJSGetArg(1));
    invert = fxJSCastBoolean(fxJSGetArg(2));

    /* OpenGL Method Call */
    glSampleCoverage(value, invert);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: scissor(x, y, width, height)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_scissor)
{
    /* Allocations */
    static GLint x;
    static GLint y;
    static GLsizei width;
    static GLsizei height;

    /* Decompose Arguments */
    x = fxJSCastNumber(fxJSGetArg(1));
    y = fxJSCastNumber(fxJSGetArg(2));
    width = fxJSCastNumber(fxJSGetArg(3));
    height = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glScissor(x, y, width, height);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: shaderSource(shader, source)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_shaderSource)
{
    /* Allocations */
    static GLuint shader;
    static GLint str_size_source;
    static GLchar* cstr_source = new GLchar[SHADER_SOURCE_BUFFER_SIZE]; // TODO delete[]

    /* Decompose Arguments */
    shader = fxJSCastNumber(fxJSGetArg(1));
    fxJSString source = fxJSAllocStringCopy(fxJSGetArg(2));
    str_size_source = fxJSStringGetSize(source);
    fxJSStringToBuffer(source, cstr_source, str_size_source);
    cstr_source[str_size_source] = 0;

    /* OpenGL Method Call */
    glShaderSource(shader, 1, (const GLchar**)&cstr_source, &str_size_source);

    /* Deallocations */
    fxJSFreeString(source);

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: stencilFunc(func, ref, mask)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_stencilFunc)
{
    /* Allocations */
    static GLenum func;
    static GLint ref;
    static GLuint mask;

    /* Decompose Arguments */
    func = fxJSCastNumber(fxJSGetArg(1));
    ref = fxJSCastNumber(fxJSGetArg(2));
    mask = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glStencilFunc(func, ref, mask);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: stencilFuncSeparate(face, func, ref, mask)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_stencilFuncSeparate)
{
    /* Allocations */
    static GLenum face;
    static GLenum func;
    static GLint ref;
    static GLuint mask;

    /* Decompose Arguments */
    face = fxJSCastNumber(fxJSGetArg(1));
    func = fxJSCastNumber(fxJSGetArg(2));
    ref = fxJSCastNumber(fxJSGetArg(3));
    mask = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glStencilFuncSeparate(face, func, ref, mask);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: stencilMask(mask)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_stencilMask)
{
    /* Allocations */
    static GLuint mask;

    /* Decompose Arguments */
    mask = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glStencilMask(mask);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: stencilMaskSeparate(face, mask)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_stencilMaskSeparate)
{
    /* Allocations */
    static GLenum face;
    static GLuint mask;

    /* Decompose Arguments */
    face = fxJSCastNumber(fxJSGetArg(1));
    mask = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glStencilMaskSeparate(face, mask);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: stencilOp(fail, zfail, zpass)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_stencilOp)
{
    /* Allocations */
    static GLenum fail;
    static GLenum zfail;
    static GLenum zpass;

    /* Decompose Arguments */
    fail = fxJSCastNumber(fxJSGetArg(1));
    zfail = fxJSCastNumber(fxJSGetArg(2));
    zpass = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glStencilOp(fail, zfail, zpass);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: stencilOpSeparate(face, fail, zfail, zpass)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_stencilOpSeparate)
{
    /* Allocations */
    static GLenum face;
    static GLenum fail;
    static GLenum zfail;
    static GLenum zpass;

    /* Decompose Arguments */
    face = fxJSCastNumber(fxJSGetArg(1));
    fail = fxJSCastNumber(fxJSGetArg(2));
    zfail = fxJSCastNumber(fxJSGetArg(3));
    zpass = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glStencilOpSeparate(face, fail, zfail, zpass);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: texImage2D(target, level, internalformat, width, height, border, format, type, pixels)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_texImage2D)
{
    /* Allocations */
    static GLenum target;
    static GLint level;
    static GLenum internalformat;
    static GLsizei width;
    static GLsizei height;
    static GLint border;
    static GLenum format;
    static GLenum type;
    static fxObjectUID pixels_uid;
    static unsigned int pixels_offset;
    static GLsizei pixels_length;
    static GLvoid* pixels_ptr;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    level = fxJSCastNumber(fxJSGetArg(2));
    internalformat = fxJSCastNumber(fxJSGetArg(3));
    width = fxJSCastNumber(fxJSGetArg(4));
    height = fxJSCastNumber(fxJSGetArg(5));
    border = fxJSCastNumber(fxJSGetArg(6));
    format = fxJSCastNumber(fxJSGetArg(7));
    type = fxJSCastNumber(fxJSGetArg(8));
    pixels_uid = fxJSCastNumber(fxJSGetArg(9));
    pixels_offset = fxJSCastNumber(fxJSGetArg(10));
    pixels_length = fxJSCastNumber(fxJSGetArg(11));
    pixels_ptr = getArrayBufferPointer(pixels_uid, pixels_offset);

    /* OpenGL Method Call */
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: texParameterf(target, pname, param)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_texParameterf)
{
    /* Allocations */
    static GLenum target;
    static GLenum pname;
    static GLfloat param;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));
    param = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glTexParameterf(target, pname, param);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: texParameteri(target, pname, param)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_texParameteri)
{
    /* Allocations */
    static GLenum target;
    static GLenum pname;
    static GLint param;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    pname = fxJSCastNumber(fxJSGetArg(2));
    param = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glTexParameteri(target, pname, param);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_texSubImage2D)
{
    /* Allocations */
    static GLenum target;
    static GLint level;
    static GLint xoffset;
    static GLint yoffset;
    static GLsizei width;
    static GLsizei height;
    static GLenum format;
    static GLenum type;
    static fxObjectUID pixels_uid;
    static unsigned int pixels_offset;
    static GLsizei pixels_length;
    static GLvoid* pixels_ptr;

    /* Decompose Arguments */
    target = fxJSCastNumber(fxJSGetArg(1));
    level = fxJSCastNumber(fxJSGetArg(2));
    xoffset = fxJSCastNumber(fxJSGetArg(3));
    yoffset = fxJSCastNumber(fxJSGetArg(4));
    width = fxJSCastNumber(fxJSGetArg(5));
    height = fxJSCastNumber(fxJSGetArg(6));
    format = fxJSCastNumber(fxJSGetArg(7));
    type = fxJSCastNumber(fxJSGetArg(8));
    pixels_uid = fxJSCastNumber(fxJSGetArg(9));
    pixels_offset = fxJSCastNumber(fxJSGetArg(10));
    pixels_length = fxJSCastNumber(fxJSGetArg(11));
    pixels_ptr = getArrayBufferPointer(pixels_uid, pixels_offset);

    /* OpenGL Method Call */
    // TODO: glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels_length, pixels_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform1f(location, x)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform1f)
{
    /* Allocations */
    static GLint location;
    static GLfloat x;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glUniform1f(location, x);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform1fv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform1fv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLfloat* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLfloat*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform1fv(location, v_length, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform1i(location, x)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform1i)
{
    /* Allocations */
    static GLint location;
    static GLint x;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glUniform1i(location, x);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform1iv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform1iv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLint* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLint*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform1iv(location, v_length, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform2f(location, x, y)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform2f)
{
    /* Allocations */
    static GLint location;
    static GLfloat x;
    static GLfloat y;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glUniform2f(location, x, y);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform2fv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform2fv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLfloat* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLfloat*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform2fv(location, v_length / 2, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform2i(location, x, y)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform2i)
{
    /* Allocations */
    static GLint location;
    static GLint x;
    static GLint y;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glUniform2i(location, x, y);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform2iv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform2iv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLint* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLint*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform2iv(location, v_length / 2, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform3f(location, x, y, z)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform3f)
{
    /* Allocations */
    static GLint location;
    static GLfloat x;
    static GLfloat y;
    static GLfloat z;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));
    z = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glUniform3f(location, x, y, z);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform3fv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform3fv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLfloat* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLfloat*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform3fv(location, v_length / 3, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform3i(location, x, y, z)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform3i)
{
    /* Allocations */
    static GLint location;
    static GLint x;
    static GLint y;
    static GLint z;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));
    z = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glUniform3i(location, x, y, z);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform3iv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform3iv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLint* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLint*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform3iv(location, v_length / 3, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform4f(location, x, y, z, w)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform4f)
{
    /* Allocations */
    static GLint location;
    static GLfloat x;
    static GLfloat y;
    static GLfloat z;
    static GLfloat w;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));
    z = fxJSCastNumber(fxJSGetArg(4));
    w = fxJSCastNumber(fxJSGetArg(5));

    /* OpenGL Method Call */
    glUniform4f(location, x, y, z, w);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform4fv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform4fv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLfloat* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLfloat*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform4fv(location, v_length / 4, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform4i(location, x, y, z, w)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform4i)
{
    /* Allocations */
    static GLint location;
    static GLint x;
    static GLint y;
    static GLint z;
    static GLint w;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));
    z = fxJSCastNumber(fxJSGetArg(4));
    w = fxJSCastNumber(fxJSGetArg(5));

    /* OpenGL Method Call */
    glUniform4i(location, x, y, z, w);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniform4iv(location, v)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniform4iv)
{
    /* Allocations */
    static GLint location;
    static fxObjectUID v_uid;
    static unsigned int v_offset;
    static GLsizei v_length;
    static GLint* v_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    v_uid = fxJSCastNumber(fxJSGetArg(2));
    v_offset = fxJSCastNumber(fxJSGetArg(3));
    v_length = fxJSCastNumber(fxJSGetArg(4));
    v_ptr = (GLint*) getArrayBufferPointer(v_uid, v_offset);

    /* OpenGL Method Call */
    glUniform4iv(location, v_length / 4, v_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniformMatrix2fv(location, transpose, value)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniformMatrix2fv)
{
    /* Allocations */
    static GLint location;
    static GLboolean transpose;
    static fxObjectUID value_uid;
    static unsigned int value_offset;
    static GLsizei value_length;
    static GLfloat* value_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    transpose = fxJSCastBoolean(fxJSGetArg(2));
    value_uid = fxJSCastNumber(fxJSGetArg(3));
    value_offset = fxJSCastNumber(fxJSGetArg(4));
    value_length = fxJSCastNumber(fxJSGetArg(5));
    value_ptr = (GLfloat*) getArrayBufferPointer(value_uid, value_offset);

    /* OpenGL Method Call */
    glUniformMatrix2fv(location, value_length / 4, transpose, value_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniformMatrix3fv(location, transpose, value)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniformMatrix3fv)
{
    /* Allocations */
    static GLint location;
    static GLboolean transpose;
    static fxObjectUID value_uid;
    static unsigned int value_offset;
    static GLsizei value_length;
    static GLfloat* value_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    transpose = fxJSCastBoolean(fxJSGetArg(2));
    value_uid = fxJSCastNumber(fxJSGetArg(3));
    value_offset = fxJSCastNumber(fxJSGetArg(4));
    value_length = fxJSCastNumber(fxJSGetArg(5));
    value_ptr = (GLfloat*) getArrayBufferPointer(value_uid, value_offset);

    /* OpenGL Method Call */
    glUniformMatrix3fv(location, value_length / 9, transpose, value_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: uniformMatrix4fv(location, transpose, value)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_uniformMatrix4fv)
{
    /* Allocations */
    static GLint location;
    static GLboolean transpose;
    static fxObjectUID value_uid;
    static unsigned int value_offset;
    static GLsizei value_length;
    static GLfloat* value_ptr;

    /* Decompose Arguments */
    location = fxJSCastNumber(fxJSGetArg(1));
    transpose = fxJSCastBoolean(fxJSGetArg(2));
    value_uid = fxJSCastNumber(fxJSGetArg(3));
    value_offset = fxJSCastNumber(fxJSGetArg(4));
    value_length = fxJSCastNumber(fxJSGetArg(5));
    value_ptr = (GLfloat*) getArrayBufferPointer(value_uid, value_offset);

    /* OpenGL Method Call */
    glUniformMatrix4fv(location, value_length / 16, transpose, value_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: useProgram(program)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_useProgram)
{
    /* Allocations */
    static GLuint program;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glUseProgram(program);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: validateProgram(program)
 * Status: CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_validateProgram)
{
    /* Allocations */
    static GLuint program;

    /* Decompose Arguments */
    program = fxJSCastNumber(fxJSGetArg(1));

    /* OpenGL Method Call */
    glValidateProgram(program);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib1f(indx, x)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib1f)
{
    /* Allocations */
    static GLuint indx;
    static GLfloat x;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));

    /* OpenGL Method Call */
    glVertexAttrib1f(indx, x);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib1fv(indx, values)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib1fv)
{
    /* Allocations */
    static GLuint indx;
    static fxObjectUID values_uid;
    static unsigned int values_offset;
    static GLsizei values_length;
    static GLvoid* values_ptr;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    values_uid = fxJSCastNumber(fxJSGetArg(2));
    values_offset = fxJSCastNumber(fxJSGetArg(3));
    values_length = fxJSCastNumber(fxJSGetArg(4));
    values_ptr = getArrayBufferPointer(values_uid, values_offset);

    /* OpenGL Method Call */
    // TODO: glVertexAttrib1fv(indx, values_length, values_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib2f(indx, x, y)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib2f)
{
    /* Allocations */
    static GLuint indx;
    static GLfloat x;
    static GLfloat y;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));

    /* OpenGL Method Call */
    glVertexAttrib2f(indx, x, y);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib2fv(indx, values)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib2fv)
{
    /* Allocations */
    static GLuint indx;
    static fxObjectUID values_uid;
    static unsigned int values_offset;
    static GLsizei values_length;
    static GLvoid* values_ptr;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    values_uid = fxJSCastNumber(fxJSGetArg(2));
    values_offset = fxJSCastNumber(fxJSGetArg(3));
    values_length = fxJSCastNumber(fxJSGetArg(4));
    values_ptr = getArrayBufferPointer(values_uid, values_offset);

    /* OpenGL Method Call */
    // TODO: glVertexAttrib2fv(indx, values_length, values_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib3f(indx, x, y, z)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib3f)
{
    /* Allocations */
    static GLuint indx;
    static GLfloat x;
    static GLfloat y;
    static GLfloat z;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));
    z = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glVertexAttrib3f(indx, x, y, z);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib3fv(indx, values)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib3fv)
{
    /* Allocations */
    static GLuint indx;
    static fxObjectUID values_uid;
    static unsigned int values_offset;
    static GLsizei values_length;
    static GLvoid* values_ptr;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    values_uid = fxJSCastNumber(fxJSGetArg(2));
    values_offset = fxJSCastNumber(fxJSGetArg(3));
    values_length = fxJSCastNumber(fxJSGetArg(4));
    values_ptr = getArrayBufferPointer(values_uid, values_offset);

    /* OpenGL Method Call */
    // TODO: glVertexAttrib3fv(indx, values_length, values_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib4f(indx, x, y, z, w)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib4f)
{
    /* Allocations */
    static GLuint indx;
    static GLfloat x;
    static GLfloat y;
    static GLfloat z;
    static GLfloat w;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    x = fxJSCastNumber(fxJSGetArg(2));
    y = fxJSCastNumber(fxJSGetArg(3));
    z = fxJSCastNumber(fxJSGetArg(4));
    w = fxJSCastNumber(fxJSGetArg(5));

    /* OpenGL Method Call */
    glVertexAttrib4f(indx, x, y, z, w);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttrib4fv(indx, values)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttrib4fv)
{
    /* Allocations */
    static GLuint indx;
    static fxObjectUID values_uid;
    static unsigned int values_offset;
    static GLsizei values_length;
    static GLvoid* values_ptr;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    values_uid = fxJSCastNumber(fxJSGetArg(2));
    values_offset = fxJSCastNumber(fxJSGetArg(3));
    values_length = fxJSCastNumber(fxJSGetArg(4));
    values_ptr = getArrayBufferPointer(values_uid, values_offset);

    /* OpenGL Method Call */
    // TODO: glVertexAttrib4fv(indx, values_length, values_ptr);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: vertexAttribPointer(indx, size, type, normalized, stride, offset)
 * Status: TO-DO
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_vertexAttribPointer)
{
    /* Allocations */
    static GLuint indx;
    static GLint size;
    static GLenum type;
    static GLboolean normalized;
    static GLsizei stride;
    static GLintptr offset;

    /* Decompose Arguments */
    indx = fxJSCastNumber(fxJSGetArg(1));
    size = fxJSCastNumber(fxJSGetArg(2));
    type = fxJSCastNumber(fxJSGetArg(3));
    normalized = fxJSCastBoolean(fxJSGetArg(4));
    stride = fxJSCastNumber(fxJSGetArg(5));
    offset = fxJSCastNumber(fxJSGetArg(6));

    /* OpenGL Method Call */
    glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid*)offset);

    /* Deallocations */

    return fxJSMakeUndefined();
}

/** ================================================================================
 * JavaScript: viewport(x, y, width, height)
 * Status: NOT-CHECKED
 * Description:
 */
fxJSBindFunction(WebGLWrapper::__WebGLRenderingContext_viewport)
{
    /* Allocations */
    static GLint x;
    static GLint y;
    static GLsizei width;
    static GLsizei height;

    /* Decompose Arguments */
    x = fxJSCastNumber(fxJSGetArg(1));
    y = fxJSCastNumber(fxJSGetArg(2));
    width = fxJSCastNumber(fxJSGetArg(3));
    height = fxJSCastNumber(fxJSGetArg(4));

    /* OpenGL Method Call */
    glViewport(x, y, width, height);

    /* Deallocations */

    return fxJSMakeUndefined();
}


