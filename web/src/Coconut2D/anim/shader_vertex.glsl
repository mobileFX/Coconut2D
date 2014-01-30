attribute vec2 iVecCoords;
attribute vec2 iTexCoords;
uniform mat4 uProjMat;
uniform mat4 uMVMat;
uniform vec2 uSprSize;
uniform vec2 uSprFrame;
uniform vec2 uSprFlip;
varying vec2 pTexCoord;

void main( void )
{
	gl_Position = uProjMat * uMVMat * vec4( iVecCoords, 0.0, 1.0 );
	pTexCoord = vec2(((abs(iTexCoords.x - uSprFlip.x) + uSprFrame.x) * uSprSize.x), ((abs(iTexCoords.y - uSprFlip.y) + uSprFrame.y) * uSprSize.y));
}
