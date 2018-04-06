precision highp float;
precision highp int;

// Inherited from CocoShader
uniform mat4 uProj;
uniform mat4 uMV;
uniform float uClock;

// Inherited from CocoShaderDefault
attribute vec2 iTex;
attribute vec2 iVert;
uniform vec2 uSqFrame;
uniform vec4 uTexSize;
uniform vec2 uFlip;

// Link with Fragment Shader
varying vec2 pTexCoord;

void main(void)
{
	// Calc sprite direction
	vec4 sprite_direction = vec4( iVert.xy * uFlip, 0.0, 1.0 );

	// Calc vertex clip space
	gl_Position = uProj * uMV * sprite_direction;

	// Calc texture map for this vert
	float x = iTex.x * uTexSize.z + uSqFrame.x;
	float y = iTex.y * uTexSize.w + uSqFrame.y;

	// Pass texture coords to fragment shader
	pTexCoord = vec2(x,y);
}

