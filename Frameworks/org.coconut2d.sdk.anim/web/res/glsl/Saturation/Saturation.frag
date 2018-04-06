#ifdef GL_ES
precision lowp float;
#endif

// Inherited from CocoShaderDefault
uniform sampler2D uSampler;

// Inherited from CocoShaderSaturation
uniform vec4 uColor;

// Link with Vertex Shader
varying vec2 pTexCoord;

void main(void)
{
	vec4 texColor = texture2D(uSampler, pTexCoord);
	float c = (texColor.r + texColor.g + texColor.b) / 3.0;
	gl_FragColor = vec4( ( 1.0 - uColor.r ) * c + texColor.r * uColor.r, ( 1.0 - uColor.g ) * c + texColor.g * uColor.g, ( 1.0 - uColor.b ) * c + texColor.b * uColor.b, texColor.a * uColor.a );
}

