precision highp float;

// Inherited from CocoShader
uniform float uClock;

// Inhertied from CocoShaderDefault
uniform sampler2D uSampler;

// Inherited from "Warp"
uniform float alpha;
uniform float speed;
uniform float fadeAway;
uniform vec3 color;
uniform vec2 resolution;
uniform float uniformity;
uniform float rayLength;
uniform float density;

// Link with Vertex Shader
varying vec2 pTexCoord;

void main(void)
{
    float t = uClock * speed;
    vec2 position = (pTexCoord.xy - resolution.xy * 0.5) / resolution.x;
    float angle = atan(position.y, position.x) / (2.0 * 3.14159265359);
    angle -= floor(angle);
    float rad = length(position);
    float angleFract = fract(angle * 256.0);
    float angleRnd = floor(angle * 256.0) + 1.0;
    float angleRnd1 = fract(angleRnd * fract(angleRnd * 0.7235) * 45.1);
    float angleRnd2 = fract(angleRnd * fract(angleRnd * 0.82657) * 13.724);
    float t2 = t + angleRnd1 * uniformity;
    float radDist = sqrt(angleRnd2);
    float adist = radDist / rad * density;
    float dist = (t2 * 0.1 + adist);
    dist = abs(fract(dist) - fadeAway);

    float i = (1.0 / (dist)) * cos(0.6 * sin(t)) * adist / radDist / rayLength;
    if(i>1.0) i = 1.0;

    gl_FragColor = vec4(color*i, alpha*i);
}
