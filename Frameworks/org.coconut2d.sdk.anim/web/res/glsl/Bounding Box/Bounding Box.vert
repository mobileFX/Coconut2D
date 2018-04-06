#ifdef GL_ES
precision lowp float;
#endif

// Inherited from CocoShader
uniform mat4 uProj;
uniform mat4 uMV;
uniform float uClock;

// Inherited from CocoShaderBoundingBox
attribute vec2 iVert;

void main(void)
{
	gl_Position = uProj * vec4(iVert, 0.0, 1.0);
}

