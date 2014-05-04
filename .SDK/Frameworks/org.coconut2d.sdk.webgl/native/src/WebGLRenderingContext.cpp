#include "WebGLRenderingContext.hpp"

WebGLRenderingContext* gl = nullptr;

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
void WebGLRenderingContext::bufferData(GLenum target, ArrayBufferView* data, GLenum usage)
{
	assert(data);
	glBufferData(target, data->byteLength, data->get(), usage);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferData(GLenum target, ArrayBuffer* data, GLenum usage)
{
	assert(data);
	glBufferData(target, data->byteLength, data->data, usage);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferSubData(GLenum target, GLintptr offset, ArrayBufferView* data)
{
	assert(data);
	glBufferSubData(target, offset, data->byteLength, data->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::bufferSubData(GLenum target, GLintptr offset, ArrayBuffer* data)
{
	assert(data);
	glBufferSubData(target, offset, data->byteLength, data->data);
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
void WebGLRenderingContext::disableVertexAttribArray(GLuint index)
{
	glDisableVertexAttribArray(index);
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::drawArrays(GLenum mode, GLint first, GLsizei count)
{
	glDrawArrays(mode, first, count);
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
void WebGLRenderingContext::enableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray(index);
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
		ret.valBool = params;
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
GLany WebGLRenderingContext::getShaderParameter(WebGLShader* shader, GLenum pname)
{
	assert(shader);
	GLany ret;
	GLint params;
	glGetShaderiv(shader->__uid, pname, &params);
	ASSERT_GL();
	switch(pname)
	{
	case GL_SHADER_TYPE:
		ret.type = GLany::typeEnum;
		ret.valEnum = params;
		break;
	case GL_DELETE_STATUS:
	case GL_COMPILE_STATUS:
		ret.type = GLany::typeBool;
		ret.valBool = params;
		break;
	default:
		assert(false);
	}
	return ret;
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
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, GLenum type, Image* image)
{
	assert(image);
	glTexImage2D(target, level, internalformat, image->naturalWidth, image->naturalHeight, 0, format, type, image->data->data->buffer->data);
	ASSERT_GL();
}
//void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, Glenum type, ImageData* pixels);
//void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, Glenum type, HTMLCanvasElement* canvas);
//void WebGLRenderingContext::texImage2D(GLenum target, GLint level, GLenum internalformat, GLenum format, Glenum type, HTMLVideoElement* video);

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::texParameteri(GLenum target, GLenum pname, GLint param)
{
	glTexParameteri(target, pname, param);
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
	glUniform1fv(location->__uid, v->length, v->get());
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
	glUniform1iv(location->__uid, v->length, v->get());
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
	glUniform2fv(location->__uid, v->length / 2, v->get());
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
	glUniform2iv(location->__uid, v->length / 2, v->get());
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
	glUniform3fv(location->__uid, v->length / 3, v->get());
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
	glUniform3iv(location->__uid, v->length / 3, v->get());
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
	glUniform4fv(location->__uid, v->length / 4, v->get());
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
	glUniform4iv(location->__uid, v->length / 4, v->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix2fv(WebGLUniformLocation* location, GLboolean transpose, Float32Array* value)
{
	assert(location);
	assert(value);
	glUniformMatrix2fv(location->__uid, value->length / 4, transpose, value->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix2fv(WebGLUniformLocation* location, GLboolean transpose, std::vector<GLfloat> value)
{
	assert(location);
	assert(!value.empty());
	glUniformMatrix2fv(location->__uid, value.size() / 4, transpose, value.data());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix3fv(WebGLUniformLocation* location, GLboolean transpose, Float32Array* value)
{
	assert(location);
	assert(value);
	glUniformMatrix3fv(location->__uid, value->length / 9, transpose, value->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix3fv(WebGLUniformLocation* location, GLboolean transpose, std::vector<GLfloat> value)
{
	assert(location);
	assert(!value.empty());
	glUniformMatrix3fv(location->__uid, value.size() / 9, transpose, value.data());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix4fv(WebGLUniformLocation* location, GLboolean transpose, Float32Array* value)
{
	assert(location);
	assert(value);
	glUniformMatrix4fv(location->__uid, value->length / 16, transpose, value->get());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::uniformMatrix4fv(WebGLUniformLocation* location, GLboolean transpose, std::vector<GLfloat> value)
{
	assert(location);
	assert(!value.empty());
	glUniformMatrix4fv(location->__uid, value.size() / 16, transpose, value.data());
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void WebGLRenderingContext::useProgram(WebGLProgram* program)
{
	assert(program);
	glUseProgram(program->__uid);
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
void WebGLRenderingContext::vertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
	glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<GLvoid*>(offset));
	ASSERT_GL();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
WebGLProgram* makeProgram(WebGLRenderingContext* gl, std::string vs, std::string fs)
{
	WebGLShader* vshader = gl->createShader(gl->VERTEX_SHADER);
	WebGLShader* fshader = gl->createShader(gl->FRAGMENT_SHADER);

	gl->shaderSource(vshader, vs);
	gl->shaderSource(fshader, fs);

	gl->compileShader(vshader);
	gl->compileShader(fshader);

	assert(gl->getShaderParameter(vshader, gl->COMPILE_STATUS).valBool);
	assert(gl->getShaderParameter(fshader, gl->COMPILE_STATUS).valBool);

	WebGLProgram* program = gl->createProgram();
	gl->attachShader(program, vshader);
	gl->attachShader(program, fshader);
	gl->linkProgram(program);

	return program;
}
