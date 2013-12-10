#ifndef __COCOMATRIX_HPP__
#define __COCOMATRIX_HPP__

class CocoMatrix
{
public:
	float rc11;
	float rc12;
	float rc13;
	float rc14;
	float rc21;
	float rc22;
	float rc23;
	float rc24;
	float rc31;
	float rc32;
	float rc33;
	float rc34;
	float rc41;
	float rc42;
	float rc43;
	float rc44;
	Array<Float32Array*> __stack = {};
	Float32Array* __data = NULL;
	CocoMatrix(CocoMatrix* M);
	void identity();
	void ortho(float left, float right, float bottom, float top, float near, float far);
	void transpose();
	float determinant();
	void invert();
	CocoVector* multiplyByVector(CocoVector* v);
	void translate(float tx, float ty);
	void scale(float sx, float sy);
	void rotateZ(float rz);
	void update(WebGLRenderingContext* gl, undefined ul);
	void push();
	void pop();
};

#endif
