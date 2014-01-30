#ifdef GL_ES
precision lowp float;
#endif

uniform sampler2D uSampler;
uniform vec4 uColor;
varying vec2 pTexCoord;

void main(void)
{
	vec4 texColor = texture2D(uSampler, pTexCoord);
	float c = (texColor.r + texColor.g + texColor.b) / 3.0;
	gl_FragColor = vec4((1.0 - uColor.r) * c + texColor.r * uColor.r, (1.0 - uColor.g) * c + texColor.g * uColor.g, (1.0 - uColor.b) * c + texColor.b * uColor.b, texColor.a * uColor.a);
}

//gl_FragColor = vec4(texColor.r * uColor.r, texColor.g * uColor.g, texColor.b * uColor.b, texColor.a * uColor.a);
