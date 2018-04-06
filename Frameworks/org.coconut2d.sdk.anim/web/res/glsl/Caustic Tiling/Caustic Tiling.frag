precision highp float;
precision highp int;

// Inherited from CocoShader
uniform float uClock;

// Inhertied from CocoShaderDefault
uniform sampler2D uSampler;

// Inherited from "Caustic Tiling"
uniform float alpha;
uniform vec3 color;
uniform float speed;
uniform float brightness;
uniform vec2 resolution;

// Link with Vertex Shader
varying vec2 pTexCoord;

void main()
{
	float TAU = 6.28318530718;
    float c = 1.0;
    float inten = 0.005;

    vec2 uv = pTexCoord * resolution * 1.1;
    vec2 p = mod(uv * TAU, TAU) - 250.0;
    vec2 i = vec2(p);

    for ( int n = 0; n < 5; n++ )
    {
        float t = uClock * (speed/100.0) * (1.0 - (3.5 / float(n + 1)));
        i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));
        c += 1.0 / length(vec2(p.x / (sin(i.x + t) / inten), p.y / (cos(i.y + t) / inten)));
    }

    c /= 5.0;
    c = 1.17 - pow(c, brightness);

    vec3 rgb = vec3(pow(abs(c), 8.0));

	gl_FragColor = vec4(rgb * color, alpha);
}

