#ifdef GL_ES
precision lowp float;
#endif

// Inhertied from CocoShaderSimple
uniform sampler2D uSampler;

// Link with Vertex Shader
varying vec2 pTexCoord;
varying vec4 vColor;

void main(void)
{
	gl_FragColor = texture2D(uSampler, pTexCoord) * vColor;
}
