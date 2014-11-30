#include <gtest/gtest.h>
#include <Matrix3D.h>
#include <Vector3D.h>
#include "HelperFunctions.h"
#include <cmath>
using Math::Matrix3D;
using Math::Vector3D;

TEST(Matrix3D, Constructor)
{
	Matrix3D identity;
	EXPECT_FLOAT_EQ(identity.r0c0, 1);
	EXPECT_FLOAT_EQ(identity.r0c1, 0);
	EXPECT_FLOAT_EQ(identity.r0c2, 0);
	EXPECT_FLOAT_EQ(identity.r1c0, 0);
	EXPECT_FLOAT_EQ(identity.r1c1, 1);
	EXPECT_FLOAT_EQ(identity.r1c2, 0);
	EXPECT_FLOAT_EQ(identity.r2c0, 0);
	EXPECT_FLOAT_EQ(identity.r2c1, 0);
	EXPECT_FLOAT_EQ(identity.r2c2, 1);


	Matrix3D victim(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	EXPECT_FLOAT_EQ(victim.r0c0, 1);
	EXPECT_FLOAT_EQ(victim.r0c1, 2);
	EXPECT_FLOAT_EQ(victim.r0c2, 3);
	EXPECT_FLOAT_EQ(victim.r1c0, 4);
	EXPECT_FLOAT_EQ(victim.r1c1, 5);
	EXPECT_FLOAT_EQ(victim.r1c2, 6);
	EXPECT_FLOAT_EQ(victim.r2c0, 7);
	EXPECT_FLOAT_EQ(victim.r2c1, 8);
	EXPECT_FLOAT_EQ(victim.r2c2, 9);

}

TEST(Matrix3D, MatrixVectorMultiply)
{
	Matrix3D op(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Vector3D victim(
		1,
		2,
		3);

	Vector3D VictimPrime = op * victim;
	EXPECT_FLOAT_EQ(VictimPrime.x, 14);
	EXPECT_FLOAT_EQ(VictimPrime.y, 32);
	EXPECT_FLOAT_EQ(VictimPrime.z, 50);
}

TEST(Matrix3D, Rotation)
{
	Matrix3D op;
	op = Matrix3D::rotateZ(0);
	EXPECT_FLOAT_EQ(op.r0c0, 1.0f);
	EXPECT_FLOAT_EQ(op.r0c1, 0.0f);
	EXPECT_FLOAT_EQ(op.r0c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r1c0, 0.0f);
	EXPECT_FLOAT_EQ(op.r1c1, 1.0f);
	EXPECT_FLOAT_EQ(op.r1c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c0, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c1, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c2, 1.0f);

	op = Matrix3D::rotateZ(M_PI);
	EXPECT_FLOAT_EQ(op.r0c0, -1.0f);
	EXPECT_TRUE(closeEnough(op.r0c1, 0.0f));
	EXPECT_FLOAT_EQ(op.r0c2, 0.0f);
	EXPECT_TRUE(closeEnough(op.r1c0, 0.0f));
	EXPECT_FLOAT_EQ(op.r1c1, -1.0f);
	EXPECT_FLOAT_EQ(op.r1c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c0, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c1, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c2, 1.0f);

	op = Matrix3D::rotateZ(M_PI/2);
	EXPECT_TRUE(closeEnough(op.r0c0, 0.0f));
	EXPECT_FLOAT_EQ(op.r0c1, -1.0f);
	EXPECT_FLOAT_EQ(op.r0c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r1c0, 1.0f);
	EXPECT_TRUE(closeEnough(op.r1c1, 0.0f));
	EXPECT_FLOAT_EQ(op.r1c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c0, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c1, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c2, 1.0f);

	op = Matrix3D::rotateZ(M_PI/4);
	EXPECT_FLOAT_EQ(op.r0c0, 0.70710678118f);
	EXPECT_FLOAT_EQ(op.r0c1, -0.70710678118f);
	EXPECT_FLOAT_EQ(op.r0c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r1c0, 0.70710678118f);
	EXPECT_FLOAT_EQ(op.r1c1, 0.70710678118f);
	EXPECT_FLOAT_EQ(op.r1c2, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c0, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c1, 0.0f);
	EXPECT_FLOAT_EQ(op.r2c2, 1.0f);
}

TEST(Matrix3D, Translation)
{
	Matrix3D translator = Matrix3D::translate(4, 8);
	Vector3D victim(-3, 8, 1);
	Vector3D victimPrime = translator * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 1);
	EXPECT_FLOAT_EQ(victimPrime.y, 16);
	EXPECT_FLOAT_EQ(victimPrime.z, 1);

}
