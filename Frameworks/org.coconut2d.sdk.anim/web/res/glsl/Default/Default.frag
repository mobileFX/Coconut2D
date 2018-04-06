#ifdef GL_ES
precision lowp float;
#endif

// Inhertied from CocoShaderDefault
uniform sampler2D uSampler;

// Link with Vertex Shader
varying vec2 pTexCoord;

void main(void)
{
	gl_FragColor = texture2D(uSampler, pTexCoord);
}
