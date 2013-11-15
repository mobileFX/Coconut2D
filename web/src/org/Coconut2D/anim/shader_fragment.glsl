precision mediump float;
uniform sampler2D uSampler;
uniform vec4 uColor;
varying vec2 pTexCoord;

void main(void)
{
	float R = 1.0 - (1.0 - texture2D(uSampler, pTexCoord).r) * (1.0 - uColor.r);
	float G = 1.0 - (1.0 - texture2D(uSampler, pTexCoord).g) * (1.0 - uColor.g);
	float B = 1.0 - (1.0 - texture2D(uSampler, pTexCoord).b) * (1.0 - uColor.b);
	float A = texture2D(uSampler, pTexCoord).a * uColor.a;
	gl_FragColor = vec4(R, G, B, A);
}

///////////////////////////////////////////////////////////////////
precision mediump float;
uniform sampler2D uSampler[8];
varying uint pID;             
varying float pAlpha;
varying vec2 pTexCoord;

void main(void) {
    gl_FragColor = texture2D(uSampler[pID], pTexCoord) * vec4(1.0, 1.0, 1.0, uAlpha);
}



/////////////////////////////////////////////////////////////////////                                                    
precision mediump float;

void main(void) {
	gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}



