/* ***** BEGIN LICENSE BLOCK *****
 *
 * Copyright (C) 2013-2017 www.mobilefx.com
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

#include "WebGLRenderingContext.hpp"

WebGLRenderingContext* gl = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLRenderingContext::WebGLRenderingContext()
{
	canvas = new HTMLCanvasElement();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLRenderingContext::~WebGLRenderingContext()
{
	delete canvas;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::activeTexture(GLenum texture)
{
	glActiveTexture(texture);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::attachShader(WebGLProgram* program, WebGLShader* shader)
{
	assert(program);
	assert(shader);
	glAttachShader(program->__uid, shader->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bindBuffer(GLenum target, WebGLBuffer* buffer)
{
	if(!buffer) glBindBuffer(target, 0);
	else glBindBuffer(target, buffer->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bindTexture(GLenum target, WebGLTexture* texture)
{
	if(!texture) glBindTexture(target, 0);
	else glBindTexture(target, texture->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::blendFunc(GLenum sfactor, GLenum dfactor)
{
	glBlendFunc(sfactor, dfactor);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::blendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
	glBlendFunc(SRC_ALPHA, ONE_MINUS_SRC_ALPHA);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferData(GLenum target, ArrayBufferView* data, GLenum usage)
{
	assert(data);
	glBufferData(target, (GLsizeiptr) data->byteLength, data->get(), usage);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferData(GLenum target, ArrayBuffer* data, GLenum usage)
{
	assert(data);
	glBufferData(target, (GLsizeiptr) data->byteLength, data->data, usage);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferSubData(GLenum target, GLintptr offset, ArrayBufferView* data)
{
	assert(data);
	glBufferSubData(target, offset, (GLsizeiptr) data->byteLength, data->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferSubData(GLenum target, GLintptr offset, ArrayBuffer* data)
{
	assert(data);
	glBufferSubData(target, offset, (GLsizeiptr) data->byteLength, data->data);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::clear(GLbitfield mask)
{
	glClear(mask);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::clearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
	glClearColor(red, green, blue, alpha);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::compileShader(WebGLShader* shader)
{
	assert(shader);
	glCompileShader(shader->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLBuffer* WebGLRenderingContext::createBuffer()
{
	WebGLBuffer* ret = new WebGLBuffer();
	glGenBuffers(1, &ret->__uid);
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLFramebuffer* WebGLRenderingContext::createFramebuffer()
{
	WebGLFramebuffer* ret = new WebGLFramebuffer();
	glGenFramebuffers(1, &ret->__uid);
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLProgram* WebGLRenderingContext::createProgram()
{
	WebGLProgram* ret = new WebGLProgram();
	ret->__uid = glCreateProgram();
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLRenderbuffer* WebGLRenderingContext::createRenderbuffer()
{
	WebGLRenderbuffer* ret = new WebGLRenderbuffer();
	glGenRenderbuffers(1, &ret->__uid);
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLShader* WebGLRenderingContext::createShader(GLenum type)
{
	WebGLShader* ret = new WebGLShader();
	ret->__uid = glCreateShader(type);
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLTexture* WebGLRenderingContext::createTexture()
{
	WebGLTexture* ret = new WebGLTexture();
	glGenTextures(1, &ret->__uid);
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::cullFace(GLenum mode)
{
	glCullFace(mode);
	ASSERT_GL();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::deleteBuffer(WebGLBuffer* buffer)
{
	assert(buffer);
	glDeleteBuffers(1, &buffer->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::deleteFramebuffer(WebGLFramebuffer* framebuffer)
{
	assert(framebuffer);
	glDeleteFramebuffers(1, &framebuffer->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::deleteProgram(WebGLProgram* program)
{
	assert(program);
	glDeleteProgram(program->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::deleteRenderbuffer(WebGLRenderbuffer* renderbuffer)
{
	assert(renderbuffer);
	glDeleteRenderbuffers(1, &renderbuffer->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::deleteShader(WebGLShader* shader)
{
	assert(shader);
	glDeleteShader(shader->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::deleteTexture(WebGLTexture* texture)
{
	assert(texture);
	glDeleteTextures(1, &texture->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::depthFunc(GLenum func)
{
	glDepthFunc(func);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::depthMask(GLboolean flag)
{
	glDepthMask(flag);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::disable(GLenum cap)
{
	glDisable(cap);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::disableVertexAttribArray(int32_t index)
{
	glDisableVertexAttribArray( (GLuint) index);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::drawArrays(GLint mode, GLint first, GLsizei count)
{
    glDrawArrays( (GLenum)mode, first, count);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::drawElements(GLenum mode, GLsizei count, GLenum type, GLintptr offset)
{
	glDrawElements(mode, count, type, reinterpret_cast<GLvoid*>(offset));
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::enable(GLenum cap)
{
	glEnable(cap);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::enableVertexAttribArray(int32_t index)
{
	glEnableVertexAttribArray((GLuint)index);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::finish()
{
	glFinish();
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::flush()
{
	glFlush();
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::frontFace(GLenum mode)
{
	glFrontFace(mode);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::generateMipmap(GLenum target)
{
	glGenerateMipmap(target);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GLint WebGLRenderingContext::getAttribLocation(WebGLProgram* program, std::string name)
{
	assert(program);
	assert(!name.empty());
	GLint ret = glGetAttribLocation(program->__uid, name.c_str());
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GLenum WebGLRenderingContext::getError()
{
	return glGetError();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GLany WebGLRenderingContext::getProgramParameter(WebGLProgram* program, GLenum pname)
{
	assert(program);

    GLany ret;
	GLint params;

    glGetProgramiv(program->__uid, pname, &params);
	ASSERT_GL();

    switch(pname)
	{
	case GL_DELETE_STATUS:
	case GL_LINK_STATUS:
	case GL_VALIDATE_STATUS:
		ret.type = GLany::typeBool;
		ret.valBool = params!=0;
		break;

	case GL_ATTACHED_SHADERS:
	case GL_ACTIVE_ATTRIBUTES:
	case GL_ACTIVE_UNIFORMS:
		ret.type = GLany::typeInt;
		ret.valInt = params;
		break;
	default:
		assert(false);
	}

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GLboolean WebGLRenderingContext::getShaderParameter_boolean(WebGLShader* shader, GLenum pname)
{
	assert(shader);
	GLint params;
	glGetShaderiv(shader->__uid, pname, &params);
	ASSERT_GL();
    return GLenum(params)!=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
GLenum WebGLRenderingContext::getShaderParameter_enum(WebGLShader* shader, GLenum pname)
{
	assert(shader);
	GLint params;
	glGetShaderiv(shader->__uid, pname, &params);
	ASSERT_GL();
	return GLenum(params);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string WebGLRenderingContext::getShaderInfoLog(WebGLShader* shader)
{
	assert(shader);
	GLint s;
	glGetShaderiv(shader->__uid, GL_INFO_LOG_LENGTH, &s);
	ASSERT_GL();
	GLchar* str = new GLchar[s];
	glGetShaderInfoLog(shader->__uid, s, NULL, str);
	ASSERT_GL();
	std::string ret(str);
	delete[] str;
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
std::string WebGLRenderingContext::getProgramInfoLog(WebGLProgram* program)
{
	return "";
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLUniformLocation* WebGLRenderingContext::getUniformLocation(WebGLProgram* program, std::string name)
{
	assert(program);
	assert(!name.empty());
	WebGLUniformLocation* ret = new WebGLUniformLocation();
	ret->__uid = glGetUniformLocation(program->__uid, name.c_str());
	ASSERT_GL();
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::linkProgram(WebGLProgram* program)
{
	assert(program);
	glLinkProgram(program->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::pixelStorei(GLenum pname, GLint param)
{
	glPixelStorei(pname, param);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::shaderSource(WebGLShader* shader, std::string source)
{
	assert(shader);
	assert(!source.empty());
	const char* src = const_cast<char*>(source.c_str());
	glShaderSource(shader->__uid, 1, &src, NULL);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, ArrayBufferView* pixels)
{
	assert(pixels);
	glTexImage2D(target, level, (GLint) internalformat, width, height, border, format, type, pixels->get());
	ASSERT_GL();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, GLenum type, Image* image)
{
	assert(image);

	unsigned char* pixels = (unsigned char*) image->data();
	size_t len = image->bytesLen();

	// For OpenGL ES2 swap BGRA to ARGB.

	#if ANDROID_APPLICATION || IOS_APPLICATION

	    for(size_t i=0;i<len;i+=4)
	    {
	        unsigned char t = pixels[i];
	        pixels[i] = pixels[i+2];
	        pixels[i+2] = t;
	    }

		glTexImage2D(target, level, (GLint) internalformat, (GLsizei) image->naturalWidth, (GLsizei) image->naturalHeight, 0, RGBA, type, pixels);

	#elif WIN32_APPLICATION

		glTexImage2D(target, level, (GLint) internalformat, (GLsizei) image->naturalWidth, (GLsizei) image->naturalHeight, 0, format, type, pixels);

	#endif

	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::texSubImage2D(GLenum target, GLint level, GLsizei xoffset, GLsizei yoffset, GLenum format, GLenum type, HTMLVideoElement* video)
{
}

//void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, Glenum type, ImageData* pixels);
//void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, Glenum type, HTMLCanvasElement* canvas);
//void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, Glenum type, HTMLVideoElement* video);

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::texParameteri(GLenum target, GLenum pname, GLenum param)
{
	glTexParameteri(target, pname, (GLint) param);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform1f(WebGLUniformLocation* location, GLfloat x)
{
	assert(location);
	glUniform1f(location->__uid, x);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform1fv(WebGLUniformLocation* location, Float32Array* v)
{
	assert(location);
	assert(v);
	glUniform1fv(location->__uid, (GLsizei) v->length, v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform1i(WebGLUniformLocation* location, GLint x)
{
	assert(location);
	glUniform1i(location->__uid, x);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform1iv(WebGLUniformLocation* location, Int32Array* v)
{
	assert(location);
	assert(v);
	glUniform1iv(location->__uid, (GLsizei) v->length, v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform2f(WebGLUniformLocation* location, GLfloat x, GLfloat y)
{
	assert(location);
	glUniform2f(location->__uid, x, y);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform2fv(WebGLUniformLocation* location, Float32Array* v)
{
	assert(location);
	assert(v);
	glUniform2fv(location->__uid, (GLsizei)(v->length / 2), v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform2i(WebGLUniformLocation* location, GLint x, GLint y)
{
	assert(location);
	glUniform2i(location->__uid, x, y);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform2iv(WebGLUniformLocation* location, Int32Array* v)
{
	assert(location);
	assert(v);
	glUniform2iv(location->__uid, (GLsizei)(v->length / 2), v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform3f(WebGLUniformLocation* location, GLfloat x, GLfloat y, GLfloat z)
{
	assert(location);
	glUniform3f(location->__uid, x, y, z);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform3fv(WebGLUniformLocation* location, Float32Array* v)
{
	assert(location);
	assert(v);
	glUniform3fv(location->__uid, (GLsizei)(v->length / 3), v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform3i(WebGLUniformLocation* location, GLint x, GLint y, GLint z)
{
	assert(location);
	glUniform3i(location->__uid, x, y, z);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform3iv(WebGLUniformLocation* location, Int32Array* v)
{
	assert(location);
	assert(v);
	glUniform3iv(location->__uid, (GLsizei)(v->length / 3), v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform4f(WebGLUniformLocation* location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	assert(location);
	glUniform4f(location->__uid, x, y, z, w);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform4fv(WebGLUniformLocation* location, Float32Array* v)
{
	assert(location);
	assert(v);
	glUniform4fv(location->__uid, (GLsizei)(v->length / 4), v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform4i(WebGLUniformLocation* location, GLint x, GLint y, GLint z, GLint w)
{
	assert(location);
	glUniform4i(location->__uid, x, y, z, w);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniform4iv(WebGLUniformLocation* location, Int32Array* v)
{
	assert(location);
	assert(v);
	glUniform4iv(location->__uid, (GLsizei)(v->length / 4), v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix2fv(WebGLUniformLocation* location, GLboolean transpose, Float32Array* value)
{
	assert(location);
	assert(value);
	glUniformMatrix2fv(location->__uid, (GLsizei)(value->length / 4), transpose, value->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix2fv(WebGLUniformLocation* location, GLboolean transpose, std::vector<GLfloat> value)
{
	assert(location);
	assert(!value.empty());
	glUniformMatrix2fv(location->__uid, (GLsizei)(value.size() / 4), transpose, value.data());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix3fv(WebGLUniformLocation* location, GLboolean transpose, Float32Array* value)
{
	assert(location);
	assert(value);
	glUniformMatrix3fv(location->__uid, (GLsizei)(value->length / 9), transpose, value->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix3fv(WebGLUniformLocation* location, GLboolean transpose, std::vector<GLfloat> value)
{
	assert(location);
	assert(!value.empty());
	glUniformMatrix3fv(location->__uid, (GLsizei)(value.size() / 9), transpose, value.data());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix4fv(WebGLUniformLocation* location, GLboolean transpose, Float32Array* value)
{
	assert(location);
	assert(value);
	glUniformMatrix4fv(location->__uid, (GLsizei)(value->length / 16), transpose, value->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix4fv(WebGLUniformLocation* location, GLboolean transpose, std::vector<GLfloat> value)
{
	assert(location);
	assert(!value.empty());
	glUniformMatrix4fv(location->__uid, (GLsizei)(value.size() / 16), transpose, value.data());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::useProgram(WebGLProgram* program)
{
	glUseProgram(program ? program->__uid : 0);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::validateProgram(WebGLProgram* program)
{
	assert(program);
	glValidateProgram(program->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::vertexAttribPointer(int32_t index, int32_t size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
	glVertexAttribPointer((GLuint) index, (GLint) size, type, normalized, stride, reinterpret_cast<GLvoid*>(offset));
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::colorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
	glColorMask(red, green, blue, alpha);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::stencilMask(GLuint mask)
{
	glStencilMask(mask);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::stencilFunc(GLenum func, GLint ref, GLuint mask)
{
	glStencilFunc(func,ref,mask);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::stencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	glStencilOp(fail,zfail,zpass);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::scissor(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	glScissor((GLsizei)x, (GLsizei)y, (GLsizei)w, (GLsizei)h);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::viewport(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
{
	glViewport((GLsizei)x, (GLsizei)y, (GLsizei)w, (GLsizei)h);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::blendEquationSeparate(GLenum a, GLenum b)
{
	glBlendEquationSeparate(a,b);
}



////////////////////////////////////////////////////////////////////////////////////////////////////
bool WebGLRenderingContext::isEnabled(GLenum v)
{
	return glIsEnabled(v) != 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bindFramebuffer(GLenum target, WebGLFramebuffer* b)
{
	glBindFramebuffer(target, b->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bindRenderbuffer(GLenum target, WebGLRenderbuffer* b)
{
	glBindRenderbuffer(target, b->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::renderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
	glRenderbufferStorage(target, internalformat, width, height);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::framebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, WebGLRenderbuffer* renderbuffer)
{
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer->__uid);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::framebufferTexture2D(GLenum target,	GLenum attachment, GLenum textarget, WebGLTexture* texture, GLint level)
{
	glFramebufferTexture2D(target, attachment, textarget, texture->__uid, level);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::clearStencil(GLint s)
{
	glClearStencil(s);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::hint(GLenum target, GLenum mode)
{
	glHint(target, mode);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::lineWidth(GLfloat width)
{
	glLineWidth(width);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::clearDepth(GLfloat depth)
{
	glClearDepthf(depth);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::depthRange(GLfloat _near, GLfloat _far)
{
	glDepthRangef(_near, _far);
	ASSERT_GL();

}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::polygonOffset(GLfloat factor, GLfloat units)
{
	glPolygonOffset(factor, units);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	glBlendColor(red, green, blue, alpha);
	ASSERT_GL();
}


