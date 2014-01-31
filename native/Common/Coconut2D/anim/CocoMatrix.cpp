#include "CocoMatrix.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoMatrix::CocoMatrix(CocoMatrix* M)
{
	if(M)
	{
		rc11 = M->rc11;
		rc12 = M->rc12;
		rc13 = M->rc13;
		rc14 = M->rc14;
		rc21 = M->rc21;
		rc22 = M->rc22;
		rc23 = M->rc23;
		rc24 = M->rc24;
		rc31 = M->rc31;
		rc32 = M->rc32;
		rc33 = M->rc33;
		rc34 = M->rc34;
		rc41 = M->rc41;
		rc42 = M->rc42;
		rc43 = M->rc43;
		rc44 = M->rc44;
	}
	else
	{
		identity();
	}
	__data = new Float32Array(Array<float> ()(rc11)(rc12)(rc13)(rc14)(rc21)(rc22)(rc23)(rc24)(rc31)(rc32)(rc33)(rc34)(rc41)(rc42)(rc43)(rc44));
	__dirty = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoMatrix::~CocoMatrix()
{
	if(__data)
	{
		__data = (delete __data, nullptr);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::identity()
{
	rc11 = 1;
	rc12 = 0;
	rc13 = 0;
	rc14 = 0;
	rc21 = 0;
	rc22 = 1;
	rc23 = 0;
	rc24 = 0;
	rc31 = 0;
	rc32 = 0;
	rc33 = 1;
	rc34 = 0;
	rc41 = 0;
	rc42 = 0;
	rc43 = 0;
	rc44 = 1;
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::ortho(float left, float right, float bottom, float top, float near, float far)
{
	rc11 = (float)(2) / (float)((right - left));
	rc12 = 0.0;
	rc13 = 0.0;
	rc14 = 0.0;
	rc21 = 0.0;
	rc22 = (float)(2) / (float)((top - bottom));
	rc23 = 0.0;
	rc24 = 0.0;
	rc31 = 0.0;
	rc32 = 0.0;
	rc33 = (float)(-2) / (float)((far - near));
	rc34 = 0.0;
	rc41 = (float)(-(right + left)) / (float)((right - left));
	rc42 = (float)(-(top + bottom)) / (float)((top - bottom));
	rc43 = (float)(-(far + near)) / (float)((far - near));
	rc44 = 1.0;
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::transpose()
{
	float t = 0.0;
	t = rc12;
	rc12 = rc21;
	rc21 = t;
	t = rc13;
	rc13 = rc31;
	rc31 = t;
	t = rc14;
	rc14 = rc41;
	rc41 = t;
	t = rc21;
	rc21 = rc12;
	rc12 = t;
	t = rc23;
	rc23 = rc32;
	rc32 = t;
	t = rc24;
	rc24 = rc42;
	rc42 = t;
	t = rc31;
	rc31 = rc13;
	rc13 = t;
	t = rc32;
	rc32 = rc23;
	rc23 = t;
	t = rc34;
	rc34 = rc43;
	rc43 = t;
	t = rc41;
	rc41 = rc14;
	rc14 = t;
	t = rc42;
	rc42 = rc24;
	rc24 = t;
	t = rc43;
	rc43 = rc34;
	rc34 = t;
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float CocoMatrix::determinant()
{
	float D = (rc14 * rc23 * rc32 * rc41) - (rc13 * rc24 * rc32 * rc41) - (rc14 * rc22 * rc33 * rc41) + (rc12 * rc24 * rc33 * rc41) + (rc13 * rc22 * rc34 * rc41) - (rc12 * rc23 * rc34 * rc41) - (rc14 * rc23 * rc31 * rc42) + (rc13 * rc24 * rc31 * rc42) + (rc14 * rc21 * rc33 * rc42) - (rc11 * rc24 * rc33 * rc42) - (rc13 * rc21 * rc34 * rc42) + (rc11 * rc23 * rc34 * rc42) + (rc14 * rc22 * rc31 * rc43) - (rc12 * rc24 * rc31 * rc43) - (rc14 * rc21 * rc32 * rc43) + (rc11 * rc24 * rc32 * rc43) + (rc12 * rc21 * rc34 * rc43) - (rc11 * rc22 * rc34 * rc43) - (rc13 * rc22 * rc31 * rc44) + (rc12 * rc23 * rc31 * rc44) + (rc13 * rc21 * rc32 * rc44) - (rc11 * rc23 * rc32 * rc44) - (rc12 * rc21 * rc33 * rc44) + (rc11 * rc22 * rc33 * rc44);
	return D;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::invert()
{
	float D = determinant();
	if(D == 0)
	{
		return;
	}
	float invRC11 = (rc23 * rc34 * rc42) - (rc24 * rc33 * rc42) + (rc24 * rc32 * rc43) - (rc22 * rc34 * rc43) - (rc23 * rc32 * rc44) + (rc22 * rc33 * rc44);
	float invRC12 = (rc14 * rc33 * rc42) - (rc13 * rc34 * rc42) - (rc14 * rc32 * rc43) + (rc12 * rc34 * rc43) + (rc13 * rc32 * rc44) - (rc12 * rc33 * rc44);
	float invRC13 = (rc13 * rc24 * rc42) - (rc14 * rc23 * rc42) + (rc14 * rc22 * rc43) - (rc12 * rc24 * rc43) - (rc13 * rc22 * rc44) + (rc12 * rc23 * rc44);
	float invRC14 = (rc14 * rc23 * rc32) - (rc13 * rc24 * rc32) - (rc14 * rc22 * rc33) + (rc12 * rc24 * rc33) + (rc13 * rc22 * rc34) - (rc12 * rc23 * rc34);
	float invRC21 = (rc24 * rc33 * rc41) - (rc23 * rc34 * rc41) - (rc24 * rc31 * rc43) + (rc21 * rc34 * rc43) + (rc23 * rc31 * rc44) - (rc21 * rc33 * rc44);
	float invRC22 = (rc13 * rc34 * rc41) - (rc14 * rc33 * rc41) + (rc14 * rc31 * rc43) - (rc11 * rc34 * rc43) - (rc13 * rc31 * rc44) + (rc11 * rc33 * rc44);
	float invRC23 = (rc14 * rc23 * rc41) - (rc13 * rc24 * rc41) - (rc14 * rc21 * rc43) + (rc11 * rc24 * rc43) + (rc13 * rc21 * rc44) - (rc11 * rc23 * rc44);
	float invRC24 = (rc13 * rc24 * rc31) - (rc14 * rc23 * rc31) + (rc14 * rc21 * rc33) - (rc11 * rc24 * rc33) - (rc13 * rc21 * rc34) + (rc11 * rc23 * rc34);
	float invRC31 = (rc22 * rc34 * rc41) - (rc24 * rc32 * rc41) + (rc24 * rc31 * rc42) - (rc21 * rc34 * rc42) - (rc22 * rc31 * rc44) + (rc21 * rc32 * rc44);
	float invRC32 = (rc14 * rc32 * rc41) - (rc12 * rc34 * rc41) - (rc14 * rc31 * rc42) + (rc11 * rc34 * rc42) + (rc12 * rc31 * rc44) - (rc11 * rc32 * rc44);
	float invRC33 = (rc12 * rc24 * rc41) - (rc14 * rc22 * rc41) + (rc14 * rc21 * rc42) - (rc11 * rc24 * rc42) - (rc12 * rc21 * rc44) + (rc11 * rc22 * rc44);
	float invRC34 = (rc14 * rc22 * rc31) - (rc12 * rc24 * rc31) - (rc14 * rc21 * rc32) + (rc11 * rc24 * rc32) + (rc12 * rc21 * rc34) - (rc11 * rc22 * rc34);
	float invRC41 = (rc23 * rc32 * rc41) - (rc22 * rc33 * rc41) - (rc23 * rc31 * rc42) + (rc21 * rc33 * rc42) + (rc22 * rc31 * rc43) - (rc21 * rc32 * rc43);
	float invRC42 = (rc12 * rc33 * rc41) - (rc13 * rc32 * rc41) + (rc13 * rc31 * rc42) - (rc11 * rc33 * rc42) - (rc12 * rc31 * rc43) + (rc11 * rc32 * rc43);
	float invRC43 = (rc13 * rc22 * rc41) - (rc12 * rc23 * rc41) - (rc13 * rc21 * rc42) + (rc11 * rc23 * rc42) + (rc12 * rc21 * rc43) - (rc11 * rc22 * rc43);
	float invRC44 = (rc12 * rc23 * rc31) - (rc13 * rc22 * rc31) + (rc13 * rc21 * rc32) - (rc11 * rc23 * rc32) - (rc12 * rc21 * rc33) + (rc11 * rc22 * rc33);
	rc11 = (float)(invRC11) / (float)(D);
	rc12 = (float)(invRC12) / (float)(D);
	rc13 = (float)(invRC13) / (float)(D);
	rc14 = (float)(invRC14) / (float)(D);
	rc21 = (float)(invRC21) / (float)(D);
	rc22 = (float)(invRC22) / (float)(D);
	rc23 = (float)(invRC23) / (float)(D);
	rc24 = (float)(invRC24) / (float)(D);
	rc31 = (float)(invRC31) / (float)(D);
	rc32 = (float)(invRC32) / (float)(D);
	rc33 = (float)(invRC33) / (float)(D);
	rc34 = (float)(invRC34) / (float)(D);
	rc41 = (float)(invRC41) / (float)(D);
	rc42 = (float)(invRC42) / (float)(D);
	rc43 = (float)(invRC43) / (float)(D);
	rc44 = (float)(invRC44) / (float)(D);
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoVector* CocoMatrix::multiplyByVector(CocoVector* v)
{
	CocoVector* out = new CocoVector();
	out->X = (v->X * rc11) + (v->Y * rc21) + (v->Z * rc31) + (v->W * rc41);
	out->Y = (v->X * rc12) + (v->Y * rc22) + (v->Z * rc32) + (v->W * rc42);
	out->Z = (v->X * rc13) + (v->Y * rc23) + (v->Z * rc33) + (v->W * rc43);
	out->W = (v->X * rc14) + (v->Y * rc24) + (v->Z * rc34) + (v->W * rc44);
	return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
CocoMatrix* CocoMatrix::multiplyByMatrix(CocoMatrix* v)
{
	CocoMatrix* out = new CocoMatrix();
	out->rc11 = (rc11 * v->rc11) + (rc21 * v->rc12) + (rc31 * v->rc13) + (rc41 * v->rc14);
	out->rc12 = (rc12 * v->rc11) + (rc22 * v->rc12) + (rc32 * v->rc13) + (rc42 * v->rc14);
	out->rc13 = (rc13 * v->rc11) + (rc23 * v->rc12) + (rc33 * v->rc13) + (rc43 * v->rc14);
	out->rc14 = (rc14 * v->rc11) + (rc24 * v->rc12) + (rc34 * v->rc13) + (rc44 * v->rc14);
	out->rc21 = (rc11 * v->rc21) + (rc21 * v->rc22) + (rc31 * v->rc23) + (rc41 * v->rc24);
	out->rc22 = (rc12 * v->rc21) + (rc22 * v->rc22) + (rc32 * v->rc23) + (rc42 * v->rc24);
	out->rc23 = (rc13 * v->rc21) + (rc23 * v->rc22) + (rc33 * v->rc23) + (rc43 * v->rc24);
	out->rc24 = (rc14 * v->rc21) + (rc24 * v->rc22) + (rc34 * v->rc23) + (rc44 * v->rc24);
	out->rc31 = (rc11 * v->rc31) + (rc21 * v->rc32) + (rc31 * v->rc33) + (rc41 * v->rc34);
	out->rc32 = (rc12 * v->rc31) + (rc22 * v->rc32) + (rc32 * v->rc33) + (rc42 * v->rc34);
	out->rc33 = (rc13 * v->rc31) + (rc23 * v->rc32) + (rc33 * v->rc33) + (rc43 * v->rc34);
	out->rc34 = (rc14 * v->rc31) + (rc24 * v->rc32) + (rc34 * v->rc33) + (rc44 * v->rc34);
	out->rc41 = (rc11 * v->rc41) + (rc21 * v->rc42) + (rc31 * v->rc43) + (rc41 * v->rc44);
	out->rc42 = (rc12 * v->rc41) + (rc22 * v->rc42) + (rc32 * v->rc43) + (rc42 * v->rc44);
	out->rc43 = (rc13 * v->rc41) + (rc23 * v->rc42) + (rc33 * v->rc43) + (rc43 * v->rc44);
	out->rc44 = (rc14 * v->rc41) + (rc24 * v->rc42) + (rc34 * v->rc43) + (rc44 * v->rc44);
	out->__dirty = true;
	return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::translate(float tx, float ty)
{
	rc41 += rc11 * tx + rc21 * ty;
	rc42 += rc12 * tx + rc22 * ty;
	rc43 += rc13 * tx + rc23 * ty;
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::scale(float sx, float sy)
{
	rc11 *= sx;
	rc21 *= sy;
	rc12 *= sx;
	rc22 *= sy;
	rc13 *= sx;
	rc23 *= sy;
	rc14 *= sx;
	rc24 *= sy;
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::rotateZ(float rz)
{
	float c = cos(rz);
	float s = sin(rz);
	float t0 = 0.0,  t1 = 0.0;
	t0 = rc11;
	t1 = rc21;
	rc11 = t0 * c + t1 * s;
	rc21 = -t0 * s + t1 * c;
	t0 = rc12;
	t1 = rc22;
	rc12 = t0 * c + t1 * s;
	rc22 = -t0 * s + t1 * c;
	t0 = rc13;
	t1 = rc23;
	rc13 = t0 * c + t1 * s;
	rc23 = -t0 * s + t1 * c;
	t0 = rc14;
	t1 = rc24;
	rc14 = t0 * c + t1 * s;
	rc24 = -t0 * s + t1 * c;
	__dirty = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::refresh()
{
	(*__data)[0] = rc11;
	(*__data)[1] = rc12;
	(*__data)[2] = rc13;
	(*__data)[3] = rc14;
	(*__data)[4] = rc21;
	(*__data)[5] = rc22;
	(*__data)[6] = rc23;
	(*__data)[7] = rc24;
	(*__data)[8] = rc31;
	(*__data)[9] = rc32;
	(*__data)[10] = rc33;
	(*__data)[11] = rc34;
	(*__data)[12] = rc41;
	(*__data)[13] = rc42;
	(*__data)[14] = rc43;
	(*__data)[15] = rc44;
	__dirty = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::update(WebGLRenderingContext* gl, WebGLUniformLocation* ul)
{
	if(gl && ul)
	{
		if(__dirty)
		{
			refresh();
		}
		gl->uniformMatrix4fv(ul, false, __data);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::push()
{
	__stack.push(new Float32Array(Array<float> ()(rc11)(rc12)(rc13)(rc14)(rc21)(rc22)(rc23)(rc24)(rc31)(rc32)(rc33)(rc34)(rc41)(rc42)(rc43)(rc44)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void CocoMatrix::pop()
{
	if(__stack.size())
	{
		Float32Array* data = __stack.pop();
		rc11 = (*data)[0];
		rc12 = (*data)[1];
		rc13 = (*data)[2];
		rc14 = (*data)[3];
		rc21 = (*data)[4];
		rc22 = (*data)[5];
		rc23 = (*data)[6];
		rc24 = (*data)[7];
		rc31 = (*data)[8];
		rc32 = (*data)[9];
		rc33 = (*data)[10];
		rc34 = (*data)[11];
		rc41 = (*data)[12];
		rc42 = (*data)[13];
		rc43 = (*data)[14];
		rc44 = (*data)[15];
		__dirty = true;
		if(data)
		{
			data = (delete data, nullptr);
		}
	}
}
