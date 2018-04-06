#ifdef GL_ES
precision lowp float;
#endif

// Inhertied from CocoShaderDefault
uniform sampler2D uSampler;

// Link with Vertex Shader
varying vec2 pTexCoord;

void main(void)
{
	vec4 color = texture2D(uSampler, pTexCoord);
	if(color.a != 1.0) discard;
	//if(color.a < 0.5) discard;
	gl_FragColor = color;
}
