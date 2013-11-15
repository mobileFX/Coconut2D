attribute vec2 iVecCoords;
attribute vec2 iTexCoords;
uniform mat4 uProjMat;
uniform mat4 uMVMat;
uniform vec2 uSprSize;
uniform vec2 uSprFrame;
varying vec2 pTexCoord; 

void main(void) 
{
    gl_Position = uProjMat * uMVMat * vec4(iVecCoords, 0.0, 1.0);
    pTexCoord = vec2(((iTexCoords.x + uSprFrame.x) * uSprSize.x), ((iTexCoords.y + uSprFrame.y) * uSprSize.y));
}

///////////////////////////////////////////////////////////////////////////////////
uniform mat4 uProjMat;

attribute float iID;
attribute float iAlpha;
attribute vec2 iVecCoords;
attribute vec2 iTexCoords;

varying vec2 pTexCoords;
varying uint pID;
varying float pAlpha;

void main(void) {
    gl_Position = uProjMat * vec4(iVecCoords, 0.0, 1.0);
    pTexCoord = iTexCoords;
	pID = uint(iID);
	pAlpha = iAlpha;
}

////////////////////////////////////////////////////////////////////////////////////////////
attribute vec2 iVecCoords;
uniform mat4 uProjMat;

void main(void) {
	gl_Position = uProjMat * vec4(iVecCoords, 0.0, 1.0);
}                                    





