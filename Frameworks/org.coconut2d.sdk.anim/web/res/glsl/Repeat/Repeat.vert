#ifdef GL_ES
precision lowp float;
#endif

// Inherited from CocoShader
uniform mat4 uProj;
uniform mat4 uMV;
uniform float uClock;

// Inherited from CocoShaderSimple
attribute vec2 iTex;
attribute vec2 iVert;
uniform vec2 uSqFrame;
uniform vec4 uTexSize;
uniform vec2 uFlip;

// Inherited from CocoShaderSaturationWithAlpha
uniform vec4 uColor;

// Link with Fragment Shader
varying vec2 pTexCoord;
varying vec4 vColor;

void main( void )
{
	// Calc sprite direction
	vec4 sprite_direction = vec4( iVert.xy * uFlip, 0.0, 1.0 );

	// Calc vertex clip space
	gl_Position = uProj * uMV * sprite_direction;

	// Calc texture map for this vert
	float x = iTex.x * uTexSize.z + uSqFrame.x;
	float y = iTex.y * uTexSize.w + uSqFrame.y;

	y -= 0.001 * uClock;

	// Pass texture coords to fragment shader
	pTexCoord = vec2(x,y);
	vColor = uColor;
}


