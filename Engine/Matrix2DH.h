#ifndef ENGINE_MATRIX_2DH_H
#define ENGINE_MATRIX_2DH_H
#include "Vector3D.h"
#include <cmath>

namespace Math
{
	struct Matrix2DH
	{
		float r0c0, r0c1, r0c2;
		float r1c0, r1c1, r1c2;
		explicit Matrix2DH(
			float r0c0 = 1.0f,float r0c1 = 0.0f,float r0c2 = 0.0f,
			float r1c0 = 0.0f,float r1c1 = 1.0f,float r1c2 = 0.0f) :
			r0c0(r0c0), r0c1(r0c1), r0c2(r0c2),
			r1c0(r1c0), r1c1(r1c1), r1c2(r1c2) {}

		inline static Matrix2DH rotateZ(float angleInRadians);
		inline static Matrix2DH translate(float x, float y);
		inline static Matrix2DH translate(const Vector3D& position);
		inline static Matrix2DH scale(float x, float y);
	};

	inline Vector3D operator*(
		const Matrix2DH& matrix,
		const Vector3D& right);
	inline Matrix2DH operator*(
		const Matrix2DH& left,
		const Matrix2DH& right);

#include "Matrix2DH.inl"
}

#endif
