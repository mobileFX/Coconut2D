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

#include "fxCRL.h"

#include "ArrayBuffer.h"
#include "ArrayBufferView.h"
#include "TypedArray.h"
#include "DataView.h"
#include "fxFont.h"
#include "Audio.h"
#include "XMLHttpRequest.h"
#include "WebGLRenderingContext.h"

#include "fxAudioStream.h"
#include "fxFontFace.h"

//	using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Common Definitions
/////////////////////////////////////////////////////////////////////////////////////////////////////////

fxJSGlobalContext fxCRL::js_context;

#ifdef JAVASCRIPT_ENGINE_V8
v8::Isolate* fxCRL::v8_isolate;
#endif

fxJSGlobalString fxCRL::jsStr_localStorage;

fxJSGlobalString fxCRL::jsStr_onreadystatechange;
fxJSGlobalString fxCRL::jsStr_onload;
fxJSGlobalString fxCRL::jsStr_responseText;

fxJSGlobalString fxCRL::jsStr___uid;
fxJSGlobalString fxCRL::jsStr_length;
fxJSGlobalString fxCRL::jsStr_buffer;
fxJSGlobalString fxCRL::jsStr_width;
fxJSGlobalString fxCRL::jsStr_height;
fxJSGlobalString fxCRL::jsStr_maxAdvance;
fxJSGlobalString fxCRL::jsStr_byteLength;
fxJSGlobalString fxCRL::jsStr_byteOffset;
fxJSGlobalString fxCRL::jsStr_BYTES_PER_ELEMENT;

fxJSGlobalString fxCRL::jsStr_load;
fxJSGlobalString fxCRL::jsStr_focus;
fxJSGlobalString fxCRL::jsStr_blur;
fxJSGlobalString fxCRL::jsStr_unload;
fxJSGlobalString fxCRL::jsStr_resize;
fxJSGlobalString fxCRL::jsStr_click;

fxJSGlobalString fxCRL::jsStr_keydown;
fxJSGlobalString fxCRL::jsStr_keypress;
fxJSGlobalString fxCRL::jsStr_keyup;
fxJSGlobalString fxCRL::jsStr_which;

fxJSGlobalString fxCRL::jsStr_touchstart;
fxJSGlobalString fxCRL::jsStr_touchmove;
fxJSGlobalString fxCRL::jsStr_touchend;
fxJSGlobalString fxCRL::jsStr_touchcancel;

fxJSGlobalString fxCRL::jsStr_clientX;
fxJSGlobalString fxCRL::jsStr_clientY;
fxJSGlobalString fxCRL::jsStr_screenX;
fxJSGlobalString fxCRL::jsStr_screenY;
fxJSGlobalString fxCRL::jsStr_touches;
fxJSGlobalString fxCRL::jsStr_changedTouches;

template<typename T> extern fxJSClass TypedArray<T>::_Class;
template<typename T> extern fxJSConstructor TypedArray<T>::_ConstructorObject;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::quit()
{
    XMLHttpRequest::quit();
    Audio::quit();
    fxFont::quit();
    TypedArray<int32_t>::quit();
	TypedArray<uint8_t>::quit();
    TypedArray<float>::quit();
    DataView::quit();
    ArrayBufferView::quit();
    ArrayBuffer::quit();
    
    fxJSFreeGlobalString(jsStr_localStorage);
    
    fxJSFreeGlobalString(jsStr_onreadystatechange);
    fxJSFreeGlobalString(jsStr_onload);
    fxJSFreeGlobalString(jsStr_responseText);
    
    fxJSFreeGlobalString(jsStr___uid);
	fxJSFreeGlobalString(jsStr_length);
    fxJSFreeGlobalString(jsStr_buffer);
    fxJSFreeGlobalString(jsStr_width);
    fxJSFreeGlobalString(jsStr_height);
    fxJSFreeGlobalString(jsStr_maxAdvance);
    fxJSFreeGlobalString(jsStr_byteLength);
    fxJSFreeGlobalString(jsStr_byteOffset);
    fxJSFreeGlobalString(jsStr_BYTES_PER_ELEMENT);
    
    fxJSFreeGlobalString(jsStr_load);
    fxJSFreeGlobalString(jsStr_focus);
    fxJSFreeGlobalString(jsStr_blur);
    fxJSFreeGlobalString(jsStr_unload);
    fxJSFreeGlobalString(jsStr_resize);
    fxJSFreeGlobalString(jsStr_click);
    
    fxJSFreeGlobalString(jsStr_keydown);
    fxJSFreeGlobalString(jsStr_keypress);
    fxJSFreeGlobalString(jsStr_keyup);
    fxJSFreeGlobalString(jsStr_which);
    
    fxJSFreeGlobalString(jsStr_touchstart);
    fxJSFreeGlobalString(jsStr_touchmove);
    fxJSFreeGlobalString(jsStr_touchend);
    fxJSFreeGlobalString(jsStr_touchcancel);
    
    fxJSFreeGlobalString(jsStr_clientX);
    fxJSFreeGlobalString(jsStr_clientY);
    fxJSFreeGlobalString(jsStr_screenX);
    fxJSFreeGlobalString(jsStr_screenY);
    fxJSFreeGlobalString(jsStr_touches);
    fxJSFreeGlobalString(jsStr_changedTouches);
    
	#ifdef JAVASCRIPT_ENGINE_V8
    {
		#ifdef ENABLE_V8_DEBUG_AGENT
        v8::Debug::SetDebugMessageDispatchHandler(nullptr, true);
        v8::Debug::DisableAgent();
		#endif
        
        v8::V8::Dispose();
        LOGI("V8 Disposed\n");
    }
	#elif JAVASCRIPT_ENGINE_APPLE
    {
    }
	#endif
    
	#ifdef ENABLE_CURL_SUPPORT
    curl_global_cleanup();
	#endif
}

bool fxCRL::isLittleEndian() { return _isLittleEndian; }

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::init(int argc, char *argv[], const fxScreen& scr, fxDeviceWrapper* dev)
{
	screen = scr;
    device = dev;
    
    uint16_t _ = 0xFF00;
    _isLittleEndian = (*(reinterpret_cast<uint8_t*>(&_)) == 0);
    
	#ifdef ENABLE_CURL_SUPPORT
    curl_global_init(CURL_GLOBAL_ALL);
	#endif
    
    // Array of Function Bindings for Global Object
    fxJSFunctionCB fun[] = {
        {"__debug_break", __debug_break, fxJSPropertyAttributeNone},
        {"alert", __alert, fxJSPropertyAttributeNone},
        {"setTimeout", __setTimeout, fxJSPropertyAttributeNone},
        {"setInterval", __setInterval, fxJSPropertyAttributeNone},
        {"clearTimeout", __clearTimeout, fxJSPropertyAttributeNone},
        {"clearInterval", __clearInterval, fxJSPropertyAttributeNone},
        {"requestAnimationFrame", __requestAnimationFrame, fxJSPropertyAttributeNone},
        {"__hintShowInput", __hintShowInput, fxJSPropertyAttributeNone},
        {"__hintHideInput", __hintHideInput, fxJSPropertyAttributeNone},
        {"__ImageData_loadImage", __ImageData_loadImage, fxJSPropertyAttributeNone},
        {"__registerManager", __registerManager, fxJSPropertyAttributeNone},
        {"__registerCallback", __registerCallback, fxJSPropertyAttributeNone},
		{"__WebGLRenderingContext_execute", WebGLRenderingContext::_execute, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getContextAttributes", WebGLRenderingContext::_getContextAttributes, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isContextLost", WebGLRenderingContext::_isContextLost, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getSupportedExtensions", WebGLRenderingContext::_getSupportedExtensions, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getExtension", WebGLRenderingContext::_getExtension, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_activeTexture", WebGLRenderingContext::_activeTexture, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_attachShader", WebGLRenderingContext::_attachShader, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bindAttribLocation", WebGLRenderingContext::_bindAttribLocation, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bindBuffer", WebGLRenderingContext::_bindBuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bindFramebuffer", WebGLRenderingContext::_bindFramebuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bindRenderbuffer", WebGLRenderingContext::_bindRenderbuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bindTexture", WebGLRenderingContext::_bindTexture, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_blendColor", WebGLRenderingContext::_blendColor, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_blendEquation", WebGLRenderingContext::_blendEquation, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_blendEquationSeparate", WebGLRenderingContext::_blendEquationSeparate, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_blendFunc", WebGLRenderingContext::_blendFunc, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_blendFuncSeparate", WebGLRenderingContext::_blendFuncSeparate, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bufferData", WebGLRenderingContext::_bufferData, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_bufferSubData", WebGLRenderingContext::_bufferSubData, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_checkFramebufferStatus", WebGLRenderingContext::_checkFramebufferStatus, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_clear", WebGLRenderingContext::_clear, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_clearColor", WebGLRenderingContext::_clearColor, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_clearDepth", WebGLRenderingContext::_clearDepth, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_clearStencil", WebGLRenderingContext::_clearStencil, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_colorMask", WebGLRenderingContext::_colorMask, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_compileShader", WebGLRenderingContext::_compileShader, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_compressedTexImage2D", WebGLRenderingContext::_compressedTexImage2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_compressedTexSubImage2D", WebGLRenderingContext::_compressedTexSubImage2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_copyTexImage2D", WebGLRenderingContext::_copyTexImage2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_copyTexSubImage2D", WebGLRenderingContext::_copyTexSubImage2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_createBuffer", WebGLRenderingContext::_createBuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_createFramebuffer", WebGLRenderingContext::_createFramebuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_createProgram", WebGLRenderingContext::_createProgram, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_createRenderbuffer", WebGLRenderingContext::_createRenderbuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_createShader", WebGLRenderingContext::_createShader, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_createTexture", WebGLRenderingContext::_createTexture, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_cullFace", WebGLRenderingContext::_cullFace, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_deleteBuffer", WebGLRenderingContext::_deleteBuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_deleteFramebuffer", WebGLRenderingContext::_deleteFramebuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_deleteProgram", WebGLRenderingContext::_deleteProgram, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_deleteRenderbuffer", WebGLRenderingContext::_deleteRenderbuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_deleteShader", WebGLRenderingContext::_deleteShader, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_deleteTexture", WebGLRenderingContext::_deleteTexture, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_depthFunc", WebGLRenderingContext::_depthFunc, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_depthMask", WebGLRenderingContext::_depthMask, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_depthRange", WebGLRenderingContext::_depthRange, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_detachShader", WebGLRenderingContext::_detachShader, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_disable", WebGLRenderingContext::_disable, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_disableVertexAttribArray", WebGLRenderingContext::_disableVertexAttribArray, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_drawArrays", WebGLRenderingContext::_drawArrays, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_drawElements", WebGLRenderingContext::_drawElements, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_enable", WebGLRenderingContext::_enable, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_enableVertexAttribArray", WebGLRenderingContext::_enableVertexAttribArray, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_finish", WebGLRenderingContext::_finish, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_flush", WebGLRenderingContext::_flush, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_framebufferRenderbuffer", WebGLRenderingContext::_framebufferRenderbuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_framebufferTexture2D", WebGLRenderingContext::_framebufferTexture2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_frontFace", WebGLRenderingContext::_frontFace, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_generateMipmap", WebGLRenderingContext::_generateMipmap, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getActiveAttrib", WebGLRenderingContext::_getActiveAttrib, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getActiveUniform", WebGLRenderingContext::_getActiveUniform, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getAttachedShaders", WebGLRenderingContext::_getAttachedShaders, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getAttribLocation", WebGLRenderingContext::_getAttribLocation, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getBufferParameter", WebGLRenderingContext::_getBufferParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getParameter", WebGLRenderingContext::_getParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getError", WebGLRenderingContext::_getError, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getFramebufferAttachmentParameter", WebGLRenderingContext::_getFramebufferAttachmentParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getProgramParameter", WebGLRenderingContext::_getProgramParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getProgramInfoLog", WebGLRenderingContext::_getProgramInfoLog, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getRenderbufferParameter", WebGLRenderingContext::_getRenderbufferParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getShaderParameter", WebGLRenderingContext::_getShaderParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getShaderPrecisionFormat", WebGLRenderingContext::_getShaderPrecisionFormat, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getShaderInfoLog", WebGLRenderingContext::_getShaderInfoLog, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getShaderSource", WebGLRenderingContext::_getShaderSource, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getTexParameter", WebGLRenderingContext::_getTexParameter, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getUniform", WebGLRenderingContext::_getUniform, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getUniformLocation", WebGLRenderingContext::_getUniformLocation, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getVertexAttrib", WebGLRenderingContext::_getVertexAttrib, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_getVertexAttribOffset", WebGLRenderingContext::_getVertexAttribOffset, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_hint", WebGLRenderingContext::_hint, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isBuffer", WebGLRenderingContext::_isBuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isEnabled", WebGLRenderingContext::_isEnabled, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isFramebuffer", WebGLRenderingContext::_isFramebuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isProgram", WebGLRenderingContext::_isProgram, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isRenderbuffer", WebGLRenderingContext::_isRenderbuffer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isShader", WebGLRenderingContext::_isShader, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_isTexture", WebGLRenderingContext::_isTexture, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_lineWidth", WebGLRenderingContext::_lineWidth, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_linkProgram", WebGLRenderingContext::_linkProgram, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_pixelStorei", WebGLRenderingContext::_pixelStorei, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_polygonOffset", WebGLRenderingContext::_polygonOffset, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_readPixels", WebGLRenderingContext::_readPixels, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_renderbufferStorage", WebGLRenderingContext::_renderbufferStorage, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_sampleCoverage", WebGLRenderingContext::_sampleCoverage, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_scissor", WebGLRenderingContext::_scissor, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_shaderSource", WebGLRenderingContext::_shaderSource, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_stencilFunc", WebGLRenderingContext::_stencilFunc, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_stencilFuncSeparate", WebGLRenderingContext::_stencilFuncSeparate, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_stencilMask", WebGLRenderingContext::_stencilMask, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_stencilMaskSeparate", WebGLRenderingContext::_stencilMaskSeparate, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_stencilOp", WebGLRenderingContext::_stencilOp, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_stencilOpSeparate", WebGLRenderingContext::_stencilOpSeparate, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_texImage2D", WebGLRenderingContext::_texImage2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_texParameterf", WebGLRenderingContext::_texParameterf, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_texParameteri", WebGLRenderingContext::_texParameteri, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_texSubImage2D", WebGLRenderingContext::_texSubImage2D, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform1f", WebGLRenderingContext::_uniform1f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform1fv", WebGLRenderingContext::_uniform1fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform1i", WebGLRenderingContext::_uniform1i, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform1iv", WebGLRenderingContext::_uniform1iv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform2f", WebGLRenderingContext::_uniform2f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform2fv", WebGLRenderingContext::_uniform2fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform2i", WebGLRenderingContext::_uniform2i, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform2iv", WebGLRenderingContext::_uniform2iv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform3f", WebGLRenderingContext::_uniform3f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform3fv", WebGLRenderingContext::_uniform3fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform3i", WebGLRenderingContext::_uniform3i, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform3iv", WebGLRenderingContext::_uniform3iv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform4f", WebGLRenderingContext::_uniform4f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform4fv", WebGLRenderingContext::_uniform4fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform4i", WebGLRenderingContext::_uniform4i, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniform4iv", WebGLRenderingContext::_uniform4iv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniformMatrix2fv", WebGLRenderingContext::_uniformMatrix2fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniformMatrix3fv", WebGLRenderingContext::_uniformMatrix3fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_uniformMatrix4fv", WebGLRenderingContext::_uniformMatrix4fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_useProgram", WebGLRenderingContext::_useProgram, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_validateProgram", WebGLRenderingContext::_validateProgram, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib1f", WebGLRenderingContext::_vertexAttrib1f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib1fv", WebGLRenderingContext::_vertexAttrib1fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib2f", WebGLRenderingContext::_vertexAttrib2f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib2fv", WebGLRenderingContext::_vertexAttrib2fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib3f", WebGLRenderingContext::_vertexAttrib3f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib3fv", WebGLRenderingContext::_vertexAttrib3fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib4f", WebGLRenderingContext::_vertexAttrib4f, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttrib4fv", WebGLRenderingContext::_vertexAttrib4fv, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_vertexAttribPointer", WebGLRenderingContext::_vertexAttribPointer, fxJSPropertyAttributeNone},
        {"__WebGLRenderingContext_viewport", WebGLRenderingContext::_viewport, fxJSPropertyAttributeNone},
        {nullptr, nullptr, fxJSPropertyAttributeNone}};
    
#ifdef JAVASCRIPT_ENGINE_V8
    // Explicit initialization of V8
    v8::V8::Initialize();
    
    // Setup V8 flags
    v8::V8::SetFlagsFromCommandLine(&argc, argv, false);
    
    // Get current V8 VM Engine
    v8_isolate = v8::Isolate::New();
    V8_SCOPE();
    
    // Create a template for the js_global object.
    v8::Handle<v8::ObjectTemplate> temp = v8::ObjectTemplate::New();
    // Bind Global functions
    for(size_t i = 0; fun[i].name; i++)
        temp->Set(v8::String::New(fun[i].name), v8::FunctionTemplate::New(fun[i].callAsFunction), fun[i].attributes);
    
    // Create a new persistent execution context in the isolate
#ifdef QT_APPLICATION
    js_context = v8::Persistent<v8::Context>::New(v8_isolate, v8::Context::New(v8_isolate, nullptr, temp, v8::Handle<v8::Value>()) );
#else
    js_context = v8::Context::New(nullptr, temp, v8::Handle<v8::Value>());
#endif
    
    // Enter explicitly to make sure it is not lost when out of scope.
    js_context->Enter();
    
    // Enable v8 debug agent
    
#ifdef ENABLE_V8_DEBUG_AGENT
    int debug_port = 9999;
    for(int i = 1; i < argc; i++) if(strcmp(argv[i], "--debugger_port")==0) debug_port = atoi(argv[i + 1]);
    js_context->SetSecurityToken(v8::Undefined());
    v8::Debug::SetDebugEventListener2(OnDebugEvent);
    v8::Debug::SetDebugMessageDispatchHandler(OnProcessDebugMessages, true);
    v8::Debug::EnableAgent("mobileFX Common Runtime Layer v8", debug_port, true);
#endif
    
#elif JAVASCRIPT_ENGINE_APPLE
    
    JSClassDefinition temp = kJSClassDefinitionEmpty;
    temp.staticFunctions = fun;
    JSClassRef globalClass = JSClassCreate(&temp);
    js_context = JSGlobalContextCreate(globalClass);
    
#endif
    
    jsStr_localStorage = fxJSAllocGlobalString("localStorage");
    
    jsStr_onreadystatechange = fxJSAllocGlobalString("onreadystatechange");
    jsStr_onload = fxJSAllocGlobalString("onload");
    jsStr_responseText = fxJSAllocGlobalString("responseText");
    
    jsStr___uid = fxJSAllocGlobalString("__uid");
    jsStr_length = fxJSAllocGlobalString("length");
    jsStr_buffer = fxJSAllocGlobalString("buffer");
    jsStr_width = fxJSAllocGlobalString("width");
    jsStr_height = fxJSAllocGlobalString("height");
    jsStr_maxAdvance = fxJSAllocGlobalString("maxAdvance");
    jsStr_byteLength = fxJSAllocGlobalString("byteLength");
    jsStr_byteOffset = fxJSAllocGlobalString("byteOffset");
    jsStr_BYTES_PER_ELEMENT = fxJSAllocGlobalString("BYTES_PER_ELEMENT");
	
    jsStr_load = fxJSAllocGlobalString("load");
    jsStr_focus = fxJSAllocGlobalString("focus");
    jsStr_blur = fxJSAllocGlobalString("blur");
    jsStr_unload = fxJSAllocGlobalString("unload");
    jsStr_resize = fxJSAllocGlobalString("resize");
    jsStr_click = fxJSAllocGlobalString("click");
    
    jsStr_keydown = fxJSAllocGlobalString("keydown");
    jsStr_keypress = fxJSAllocGlobalString("keypress");
    jsStr_keyup = fxJSAllocGlobalString("keyup");
    jsStr_which = fxJSAllocGlobalString("which");
    
    jsStr_touchstart = fxJSAllocGlobalString("touchstart");
    jsStr_touchmove = fxJSAllocGlobalString("touchmove");
    jsStr_touchend = fxJSAllocGlobalString("touchend");
    jsStr_touchcancel = fxJSAllocGlobalString("touchcancel");
    
    jsStr_clientX = fxJSAllocGlobalString("clientX");
    jsStr_clientY = fxJSAllocGlobalString("clientY");
    jsStr_screenX = fxJSAllocGlobalString("screenX");
    jsStr_screenY = fxJSAllocGlobalString("screenY");
    jsStr_touches = fxJSAllocGlobalString("touches");
    jsStr_changedTouches = fxJSAllocGlobalString("changedTouches");
    
    LOGI("Init()\n");
    
    ArrayBuffer::init();
    ArrayBufferView::init();
    DataView::init();
    TypedArray<float>::init("Float32Array");
    TypedArray<int32_t>::init("Int32Array");
	TypedArray<uint8_t>::init("Uint8Array");
    fxFont::init();
    Audio::init();
    XMLHttpRequest::init();
    
    fxJSObject js_global = fxJSGetGlobalObject(js_context);
    
    fxJSString jstr;
    // TODO: release retained objects
    jstr = fxJSAllocString("JSON"); js_JSON = fxJSCastObject(fxJSGetProperty(js_global, jstr)); fxJSFreeString(jstr); fxJSRetainObject(js_JSON);
    jstr = fxJSAllocString("parse"); js_JSON_parse = fxJSCastFunction(fxJSGetProperty(js_JSON, jstr)); fxJSFreeString(jstr); fxJSRetainFunction(js_JSON_parse);
    jstr = fxJSAllocString("stringify"); js_JSON_stringify = fxJSCastFunction(fxJSGetProperty(js_JSON, jstr)); fxJSFreeString(jstr); fxJSRetainFunction(js_JSON_stringify);
    
    jstr = fxJSAllocString("ArrayBuffer"); fxJSSetProperty(js_global, jstr, ArrayBuffer::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("ArrayBufferView"); fxJSSetProperty(js_global, jstr, ArrayBufferView::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("DataView"); fxJSSetProperty(js_global, jstr, DataView::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("Float32Array"); fxJSSetProperty(js_global, jstr, TypedArray<float>::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("Int32Array"); fxJSSetProperty(js_global, jstr, TypedArray<int32_t>::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
	jstr = fxJSAllocString("Uint8Array"); fxJSSetProperty(js_global, jstr, TypedArray<uint8_t>::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("fxFont"); fxJSSetProperty(js_global, jstr, fxFont::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("Audio"); fxJSSetProperty(js_global, jstr, Audio::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("XMLHttpRequest"); fxJSSetProperty(js_global, jstr, XMLHttpRequest::getJSConstructor(), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    
    jstr = fxJSAllocString("innerWidth"); fxJSSetProperty(js_global, jstr, fxJSMakeNumber(screen.width), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("innerHeight"); fxJSSetProperty(js_global, jstr, fxJSMakeNumber(screen.height), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    jstr = fxJSAllocString("devicePixelRatio"); fxJSSetProperty(js_global, jstr, fxJSMakeNumber(screen.pixelRatio), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
    
	float rot = 0.0f;
	switch(screen.rotation)
	{
		case fxScreen::Rotation::NONE: rot = 0.0f; break;
		case fxScreen::Rotation::RCW: rot = M_PI_2; break;
		case fxScreen::Rotation::RCCW: rot = -M_PI_2; break;
		case fxScreen::Rotation::FULL: rot = M_PI; break;
	}
	
	jstr = fxJSAllocString("deviceRotation");
	fxJSSetProperty(js_global, jstr, fxJSMakeNumber(rot), fxJSPropertyAttributeReadOnly); fxJSFreeString(jstr);
	
    loadStorage();
    
    // Load script from file
    fxJSString script_name;
    fxJSString script_source;
    
    ArgState state = ArgState::NONE;
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "--scripts")) state = ArgState::SCRIPTS;
        else if(!strcmp(argv[i], "--fonts")) state = ArgState::FONTS;
        else {
            switch(state)
            {
                case ArgState::NONE:
                    break;
                case ArgState::SCRIPTS:
                {
                    fxFile file = fxFile(argv[i], true);
                    script_name = fxJSAllocString(file.getFullPath());
                    script_source = fxJSAllocString(file.getData());
                    fxJSRunScript(script_source, script_name);
                    fxJSFreeString(script_name);
                    fxJSFreeString(script_source);
                    break;
                }
                case ArgState::FONTS:
                {
                    fxFontFace::add(argv[i]);
                    break;
                }
            }
        }
    }
    LOGI("JavaScript modules loaded\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__debug_break)
{
#ifdef ENABLE_V8_DEBUG_AGENT
    debug_break_time = std::chrono::steady_clock::now();
#endif
    return fxJSMakeUndefined();
}

#ifdef ENABLE_V8_DEBUG_AGENT

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::OnDebugEvent(const v8::Debug::EventDetails& details)
{
    switch(details.GetEvent())
    {
        case v8::DebugEvent::Break:
            
            // Because of single threading the debugger blocks and
            // notifies "break" when actually a "continue" occurs.
            // We can take advantage of this for chrono calculations.
            start_time += (std::chrono::steady_clock::now() - debug_break_time);
            break;
            
        case v8::DebugEvent::AfterCompile:
        case v8::DebugEvent::BeforeCompile:
            break;
            
        default:
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::OnProcessDebugMessages()
{
    v8::Debug::ProcessDebugMessages();
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::tick()
{
    XMLHttpRequest::tick();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::paint()
{
    if(fxJSIsEmpty(js_requestAnimationFrameCallback)) return;
    V8_SCOPE();
    std::chrono::duration<double, std::milli> running_duration = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::steady_clock::now()-start_time);
    fxJSFunction fCB = js_requestAnimationFrameCallback;
    js_requestAnimationFrameCallback = fxJSEmptyFunction();
    fxJSValue time = fxJSMakeNumber(running_duration.count());
    fxJSCallFunction(fCB, fxJSGetGlobalObject(js_context), 1, &time);
    fxJSRelease(fCB);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::handleEvent(fxObjectUID uid, fxEvent type, void* data)
{
    V8_SCOPE();
    
    if(fxJSIsEmpty(js_CallbackManager) || fxJSIsEmpty(js_DispatchFunction) || fxJSIsEmpty(js_EventObject))
    {
        LOGW("Event too soon!\n");
        return;
    }
    
    fxJSValue eventData[2];
    eventData[0] = fxJSMakeNumber(uid);
    
    switch(type)
    {
        case fxEvent::LOAD:
        {
            eventData[1] = fxJSMakeString(jsStr_load);
            break;
        }
            
        case fxEvent::FOCUS:
        {
            eventData[1] = fxJSMakeString(jsStr_focus);
            break;
        }
            
        case fxEvent::BLUR:
        {
            saveStorage();
            eventData[1] = fxJSMakeString(jsStr_blur);
            break;
        }
            
        case fxEvent::UNLOAD:
        {
            saveStorage();
            eventData[1] = fxJSMakeString(jsStr_unload);
            break;
        }
            
        case fxEvent::RESIZE:
        {
            eventData[1] = fxJSMakeString(jsStr_resize);
            break;
        }
            
        case fxEvent::CLICK:
        {
            eventData[1] = fxJSMakeString(jsStr_click);
            int x, y;
            switch(screen.rotation)
            {
                case fxScreen::Rotation::NONE: x = fxAPIGetMouseEventX(data); y = fxAPIGetMouseEventY(data); break;
                case fxScreen::Rotation::FULL: x = -fxAPIGetMouseEventX(data); y = -fxAPIGetMouseEventY(data); break;
                case fxScreen::Rotation::RCW: x = -fxAPIGetMouseEventY(data); y = fxAPIGetMouseEventX(data); break;
                case fxScreen::Rotation::RCCW: x = fxAPIGetMouseEventY(data); y = -fxAPIGetMouseEventX(data); break;
            }
            fxJSSetProperty(js_EventObject, jsStr_clientX, fxJSMakeNumber(x), fxJSPropertyAttributeNone);
            fxJSSetProperty(js_EventObject, jsStr_clientY, fxJSMakeNumber(y), fxJSPropertyAttributeNone);
            fxJSSetProperty(js_EventObject, jsStr_screenX, fxJSMakeNumber(x), fxJSPropertyAttributeNone);
            fxJSSetProperty(js_EventObject, jsStr_screenY, fxJSMakeNumber(y), fxJSPropertyAttributeNone);
            break;
        }
            
        case fxEvent::KEYDOWN:
        {
            eventData[1] = fxJSMakeString(jsStr_keydown);
            //fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
            break;
        }
            
        case fxEvent::KEYPRESS:
        {
            eventData[1] = fxJSMakeString(jsStr_keypress);
            //fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
            break;
        }
            
        case fxEvent::KEYUP:
        {
            eventData[1] = fxJSMakeString(jsStr_keyup);
            //fxJSSetProperty(js_EventObject, jsStr_which, fxJSMakeNumber(fxAPIGetKey(data)), fxJSPropertyAttributeNone);
            break;
        }
            
        case fxEvent::TOUCHSTART:
        case fxEvent::TOUCHMOVE:
        case fxEvent::TOUCHEND:
        case fxEvent::TOUCHCANCEL:
        {
            switch(type)
            {
                case fxEvent::TOUCHSTART: eventData[1] = fxJSMakeString(jsStr_touchstart); break;
                case fxEvent::TOUCHMOVE: eventData[1] = fxJSMakeString(jsStr_touchmove); break;
                case fxEvent::TOUCHEND: eventData[1] = fxJSMakeString(jsStr_touchend); break;
                case fxEvent::TOUCHCANCEL: eventData[1] = fxJSMakeString(jsStr_touchcancel); break;
                default: break;
            }
            int x, y;
            
            fxJSSetProperty(js_TouchesObject, jsStr_length, fxJSMakeNumber(fxAPIGetTouchesLength(data)), fxJSPropertyAttributeNone);
            for(size_t i = fxAPIGetTouchesLength(data); i--;)
            {
                switch(screen.rotation)
                {
                    case fxScreen::Rotation::NONE: x = fxAPIGetTouchEventX(data, i); y = fxAPIGetTouchEventY(data, i) - screen.top; break;
                    case fxScreen::Rotation::FULL: x = screen.width - fxAPIGetTouchEventX(data, i); y = screen.height - fxAPIGetTouchEventY(data, i); break;
                    case fxScreen::Rotation::RCW: x = screen.width - fxAPIGetTouchEventY(data, i); y = fxAPIGetTouchEventX(data, i) - screen.top; break;
                    case fxScreen::Rotation::RCCW: x = fxAPIGetTouchEventY(data, i); y = screen.height - fxAPIGetTouchEventX(data, i); break;
                }
                fxJSSetProperty(js_Touches[i], jsStr_clientX, fxJSMakeNumber(x), fxJSPropertyAttributeNone);
                fxJSSetProperty(js_Touches[i], jsStr_clientY, fxJSMakeNumber(y), fxJSPropertyAttributeNone);
                fxJSSetProperty(js_Touches[i], jsStr_screenX, fxJSMakeNumber(x), fxJSPropertyAttributeNone);
                fxJSSetProperty(js_Touches[i], jsStr_screenY, fxJSMakeNumber(y), fxJSPropertyAttributeNone);
            }
            
            fxJSSetProperty(js_ChangedTouchesObject, jsStr_length, fxJSMakeNumber(fxAPIGetChangedTouchesLength(data)), fxJSPropertyAttributeNone);
            for(size_t i = fxAPIGetChangedTouchesLength(data); i--;)
            {
                switch(screen.rotation)
                {
                    case fxScreen::Rotation::NONE: x = fxAPIGetChangedTouchEventX(data, i); y = fxAPIGetChangedTouchEventY(data, i) - screen.top; break;
                    case fxScreen::Rotation::FULL: x = screen.width - fxAPIGetChangedTouchEventX(data, i); y = screen.height - fxAPIGetChangedTouchEventY(data, i); break;
                    case fxScreen::Rotation::RCW: x = screen.width - fxAPIGetChangedTouchEventY(data, i); y = fxAPIGetChangedTouchEventX(data, i) - screen.top; break;
                    case fxScreen::Rotation::RCCW: x = fxAPIGetChangedTouchEventY(data, i); y =screen.height - fxAPIGetChangedTouchEventX(data, i); break;
                }
                fxJSSetProperty(js_ChangedTouches[i], jsStr_clientX, fxJSMakeNumber(x), fxJSPropertyAttributeNone);
                fxJSSetProperty(js_ChangedTouches[i], jsStr_clientY, fxJSMakeNumber(y), fxJSPropertyAttributeNone);
                fxJSSetProperty(js_ChangedTouches[i], jsStr_screenX, fxJSMakeNumber(x), fxJSPropertyAttributeNone);
                fxJSSetProperty(js_ChangedTouches[i], jsStr_screenY, fxJSMakeNumber(y), fxJSPropertyAttributeNone);
            }
            break;
        }
            
        default:
            LOGW("Event not implemented!\n");
    }
    
    fxJSCallFunction(js_DispatchFunction, js_CallbackManager, 2, eventData);
    return;
}

#ifdef JAVASCRIPT_ENGINE_V8

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::ReportException(v8::TryCatch* try_catch)
{
    v8::HandleScope handle_scope;
    v8::String::Utf8Value exception(try_catch->Exception());
    const char* exception_string = toCString(exception);
    v8::Handle<v8::Message> message = try_catch->Message();
    if(message.IsEmpty())
    {
        // V8 didn't provide any extra information about this error; just print the exception.
        LOGW("%s\n", exception_string);
    }
    else
    {
        // Print (filename):(line number): (message).
        v8::String::Utf8Value filename(message->GetScriptResourceName());
        const char* filename_string = toCString(filename);
        int linenum = message->GetLineNumber();
        LOGW("%s:%i: %s\n", filename_string, linenum, exception_string);
        
        // Print line of source code.
        v8::String::Utf8Value sourceline(message->GetSourceLine());
        const char* sourceline_string = toCString(sourceline);
        LOGW("%s\n", sourceline_string);
        
        // Print wavy underline (GetUnderline is deprecated).
        int start = message->GetStartColumn();
        for(int i = 0; i < start; i++) { LOGW(" "); }
        int end = message->GetEndColumn();
        for(int i = start; i < end; i++) { LOGW("^");	}
        LOGW("\n");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* fxCRL::toCString(const v8::String::Utf8Value& value)
{
    return *value ? *value : "<string conversion failed>";
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::eraseTimer(const std::map<size_t, structJSTimer>::iterator& it)
{
    if(it != jsTimerList.end())
    {
        if(!fxJSIsEmpty(it->second.callback))
            fxJSRelease(it->second.callback);
        if(!fxJSIsEmpty(it->second.script))
            fxJSFreeScript(it->second.script);
        if(it->second.argc > 0)
            for(size_t i = it->second.argc; i--;)
                fxJSRelease(it->second.args[i]);
        delete it->second.args;
        jsTimerList.erase(it);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::tickTimers(const std::chrono::steady_clock::time_point& time)
{
    static std::chrono::steady_clock::time_point tbefore;
    static std::map<size_t, structJSTimer>::iterator it;
    
    it = jsTimerList.begin();
    while(it != jsTimerList.end())
    {
        if(it->second.next <= time)
        {
            if(!fxJSIsEmpty(it->second.callback))
                fxJSCallFunction(fxJSCastFunction(it->second.callback), fxJSGetGlobalObject(fxCRL::js_context), it->second.argc, it->second.args);
            else if(!fxJSIsEmpty(it->second.script))
                fxJSCallScript(it->second.script);
            if(it->second.interval == std::chrono::milliseconds(0))
                eraseTimer(it++);
            else
            {
                it->second.next = time + it->second.interval;
                it++;
            }
        }
        else it++;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::loadStorage(const char* str)
{
	if(!fxFile::exists(str, false)) fxFile::createWithData(str, "{}");
    fxFile file(str, false);
    //LOGI("json:\n%s\n", file.getData());
    fxJSString json = fxJSAllocString(file.getData());
    fxJSValue val = fxJSMakeString(json);
	//fxJSValue ret = JSValueMakeFromJSONString(js_context, json);
    fxJSValue ret = fxJSCallFunction(js_JSON_parse, js_JSON, 1, &val);
    fxJSSetProperty(fxJSGetGlobalObject(js_context), jsStr_localStorage, ret, fxJSPropertyAttributeNone);
    fxJSFreeString(json);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void fxCRL::saveStorage(const char* str)
{
    fxJSValue val = fxJSGetProperty(fxJSGetGlobalObject(js_context), jsStr_localStorage);
    fxJSValue ret = fxJSCallFunction(js_JSON_stringify, js_JSON, 1, &val);
	//fxJSString jstr = JSValueCreateJSONString(js_context, val, 0, nullptr);
    fxJSString jstr = fxJSAllocStringCopy(ret);
    size_t str_size = fxJSStringGetSize(jstr);
    char* cstr = new char[str_size + 1];
    fxJSStringToBuffer(jstr, cstr, str_size);
    cstr[str_size] = 0;
    fxFile::createWithData(str, cstr);
    fxJSFreeString(jstr);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__alert)
{
    fxJSString str = fxJSAllocStringCopy(fxJSGetArg(0));
    size_t str_size = fxJSStringGetSize(str);
    char *cstr = new char[str_size + 1];
    fxJSStringToBuffer(str, cstr, str_size);
    cstr[str_size] = 0;
    LOGI("alert: %s\n", cstr);
    delete[] cstr;
    fxJSFreeString(str);
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__setTimeout)
{
    if(fxJSGetArgCount() > 0)
    {
        structJSTimer timer;
        timer.script = fxJSEmptyScript();
        timer.callback = fxJSEmptyFunction();
        timer.interval = std::chrono::milliseconds(0);
        timer.argc = 0;
        timer.args = nullptr;
        timer.next = std::chrono::steady_clock::now() + std::chrono::milliseconds(JSINTERVAL_MIN);
        
        if(fxJSIsFunction(fxJSGetArg(0)))
        {
            timer.callback = fxJSCastObject(fxJSGetArg(0));
            fxJSRetain(timer.callback);
            if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(1)))
            {
                timer.next = std::chrono::steady_clock::now() + std::chrono::milliseconds((long long int)fxJSCastNumber(fxJSGetArg(1)));
                if(fxJSGetArgCount() > 2)
                {
                    timer.argc = fxJSGetArgCount() - 2;
                    timer.args = new fxJSValue[timer.argc];
                    for(size_t i = timer.argc; i--;)
                    {
                        timer.args[i] = fxJSGetArg(i + 2);
                        fxJSRetain(timer.args[i]);
                    }
                }
            }
            jsTimerList.insert(std::pair<size_t, structJSTimer>(++jsTimerID, timer));
            return fxJSMakeNumber(jsTimerID);
        }
        else if(fxJSIsString(fxJSGetArg(0)))
        {
            timer.script = fxJSAllocScript(fxJSGetArg(0));
            if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(1)))
            {
                timer.next = std::chrono::steady_clock::now() + std::chrono::milliseconds((long long int)fxJSCastNumber(fxJSGetArg(1)));
            }
            jsTimerList.insert(std::pair<size_t, structJSTimer>(++jsTimerID, timer));
            return fxJSMakeNumber(jsTimerID);
        }
    }
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__setInterval)
{
    if(fxJSGetArgCount() > 0)
    {
        structJSTimer timer;
        timer.script = fxJSEmptyScript();
        timer.callback = fxJSEmptyFunction();
        timer.interval = std::chrono::milliseconds(JSINTERVAL_MIN);
        timer.argc = 0;
        timer.args = nullptr;
        timer.next = std::chrono::steady_clock::now() + std::chrono::milliseconds(JSINTERVAL_MIN);
        
        if(fxJSIsFunction(fxJSGetArg(0)))
        {
            timer.callback = fxJSCastObject(fxJSGetArg(0));
            fxJSRetain(timer.callback);
            if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(1)))
            {
                timer.next = std::chrono::steady_clock::now() + std::chrono::milliseconds((long long int)fxJSCastNumber(fxJSGetArg(1)));
                if(fxJSGetArgCount() > 2)
                {
                    timer.argc = fxJSGetArgCount() - 2;
                    timer.args = new fxJSValue[timer.argc];
                    for(size_t i = timer.argc; i--;)
                    {
                        timer.args[i] = fxJSGetArg(i + 2);
                        fxJSRetain(timer.args[i]);
                    }
                }
            }
            jsTimerList.insert(std::pair<size_t, structJSTimer>(++jsTimerID, timer));
            return fxJSMakeNumber(jsTimerID);
        }
        else if(fxJSIsString(fxJSGetArg(0)))
        {
            timer.script = fxJSAllocScript(fxJSGetArg(0));
            if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(1)))
            {
                timer.next = std::chrono::steady_clock::now() + std::chrono::milliseconds((long long int)fxJSCastNumber(fxJSGetArg(1)));
            }
            jsTimerList.insert(std::pair<size_t, structJSTimer>(++jsTimerID, timer));
            return fxJSMakeNumber(jsTimerID);
        }
    }
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__clearTimeout)
{
    if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(0)))
    {
        eraseTimer(jsTimerList.find(fxJSCastNumber(fxJSGetArg(0))));
    }
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__clearInterval)
{
    if(fxJSGetArgCount() > 1 && fxJSIsNumber(fxJSGetArg(0)))
    {
        eraseTimer(jsTimerList.find(fxJSCastNumber(fxJSGetArg(0))));
    }
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__requestAnimationFrame)
{
    if(fxJSGetArgCount() > 0 && fxJSIsFunction(fxJSGetArg(0)))
    {
        js_requestAnimationFrameCallback = fxJSCastFunction(fxJSGetArg(0));
        fxJSRetainFunction(js_requestAnimationFrameCallback);
        return fxJSMakeNumber(1);
    }
    return fxJSMakeNumber(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__hintShowInput)
{
#ifdef IOS_APPLICATION
    [device showKeyboard];
#elif ANDROID_APPLICATION
    
#endif
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__hintHideInput)
{
#ifdef IOS_APPLICATION
    [device hideKeyboard];
#elif ANDROID_APPLICATION
    
#endif
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__ImageData_loadImage)
{
    if(fxJSGetArgCount() > 0 && fxJSIsString(fxJSGetArg(0)))
    {
        static size_t str_size;
        static char cstr[256];
        
        fxJSString src = fxJSAllocStringCopy(fxJSGetArg(0));
        str_size = fxJSStringGetSize(src);
        fxJSStringToBuffer(src, cstr, str_size);
        cstr[str_size] = 0;
        
        fxJSObject ret = fxJSMakeEmptyObject();
        uint32_t width, height;
        fxJSValue buffer = ArrayBuffer::NewFromImage(cstr, width, height);
        fxJSFreeString(src);
        
        if(fxJSIsEmpty(buffer))
            return fxJSMakeNull();
        
        fxJSSetProperty(ret, jsStr_buffer, buffer, fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(ret, jsStr_width, fxJSMakeNumber(width), fxJSPropertyAttributeReadOnly);
        fxJSSetProperty(ret, jsStr_height, fxJSMakeNumber(height), fxJSPropertyAttributeReadOnly);
        
        return ret;
    }
    return fxJSMakeNull();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__registerManager)
{
    if(fxJSGetArgCount() > 2 && fxJSIsObject(fxJSGetArg(0)) && fxJSIsFunction(fxJSGetArg(1)) && fxJSIsObject(fxJSGetArg(2)))
    {
        // TODO: Release Objects
        js_CallbackManager = fxJSCastObject(fxJSGetArg(0));
        fxJSRetainObject(js_CallbackManager);
        
        js_DispatchFunction = fxJSCastFunction(fxJSGetArg(1));
        fxJSRetainFunction(js_DispatchFunction);
        
        js_EventObject = fxJSCastObject(fxJSGetArg(2));
        fxJSRetainObject(js_EventObject);
        
        fxJSValue js_TouchesValue = fxJSGetProperty(js_EventObject, jsStr_touches);
        if(fxJSIsEmpty(js_TouchesValue)) return fxJSMakeNull();
        js_TouchesObject = fxJSCastObject(js_TouchesValue);
        fxJSRetainObject(js_TouchesObject);
        
        fxJSValue js_ChangedTouchesValue = fxJSGetProperty(js_EventObject, jsStr_changedTouches);
        if(fxJSIsEmpty(js_ChangedTouchesValue)) return fxJSMakeNull();
        js_ChangedTouchesObject = fxJSCastObject(js_ChangedTouchesValue);
        fxJSRetainObject(js_ChangedTouchesObject);
        
        for(size_t i = JSTOUCHLIST_MAX_LENGTH; i--;)
        {
            js_Touches[i] = fxJSCastObject(fxJSGetPropertyAt(js_TouchesObject, i));
            fxJSRetainObject(js_Touches[i]);
            
            js_ChangedTouches[i] = fxJSCastObject(fxJSGetPropertyAt(js_ChangedTouchesObject, i));
            fxJSRetainObject(js_ChangedTouches[i]);
        }
    }
    return fxJSMakeUndefined();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
fxJSBindFunction(fxCRL::__registerCallback)
{
    // TODO
    return fxJSMakeUndefined();
}


