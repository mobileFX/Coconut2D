attribute vec2 iVecCoords;
attribute vec2 iTexCoords;
uniform mat4 uProjMat;
uniform mat4 uMVMat;
uniform mat4 uSprMat;
uniform vec2 uSprSize;
uniform vec2 uSprFrame;
varying vec2 pTexCoord;

void main(void)
{
	mat4 T = mat4(1.0);
	T[3].xyz = uSprMat[3].xyz;
	
	mat4 R = mat4(1.0);
	R[0].xyz = uSprMat[0].xyz;
	R[1].xyz = uSprMat[1].xyz;
	R[2].xyz = uSprMat[2].xyz;
	
	mat4 S = mat4(1.0);
	S[0].x = uSprMat[0].w;
	S[1].y = uSprMat[1].w;
	S[2].z = uSprMat[2].w;
	
	gl_Position = uProjMat * uMVMat * T * R * S * vec4(iVecCoords, 0.0, 1.0);
	pTexCoord = vec2(((iTexCoords.x + uSprFrame.x) * uSprSize.x), ((iTexCoords.y + uSprFrame.y) * uSprSize.y));
} 

attribute vec2 iVecCoords;
uniform mat4 uProjMat;

void main(void) {
	gl_Position = uProjMat * vec4(iVecCoords, 0.0, 1.0);
}                                    

