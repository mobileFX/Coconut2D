#ifdef GL_ES
precision lowp float;
#endif

// Inhertied from CocoShaderDefault
uniform sampler2D uSampler;

// Inherited from CocoShaderDefaultWithAlpha
uniform float alpha;

// Link with Vertex Shader
varying vec2 pTexCoord;

void main(void)
{
	vec4 texColor = texture2D(uSampler, pTexCoord);
	gl_FragColor = vec4(texColor.rgb, texColor.a * alpha);
}
