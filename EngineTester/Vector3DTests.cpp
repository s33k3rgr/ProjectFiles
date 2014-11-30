#include <gtest/gtest.h>
#include <Vector3D.h>
using Math::Vector3D;

TEST(Vector3D, Constructor)
{
	Vector3D instance(-4.3f, 9.1f, 5.0f);
	EXPECT_FLOAT_EQ(-4.3f, instance.x);
	EXPECT_FLOAT_EQ(9.1f, instance.y);
	EXPECT_FLOAT_EQ(5.0f, instance.z);

	Vector3D defaultConstructor;
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.x);
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.y);
	EXPECT_FLOAT_EQ(0.0f, defaultConstructor.z);

}

TEST(Vector3D, VectorAddition)
{
	Vector3D first(1, 2 , 3);
	Vector3D second(3, 4, 5);

	Vector3D result1 = first + second;
	Vector3D result2 = second + first;

	EXPECT_TRUE(result1.x == 4);
	EXPECT_TRUE(result1.y == 6);
	EXPECT_TRUE(result1.z == 8);

	EXPECT_TRUE(result1.x == result2.x);
	EXPECT_TRUE(result1.y == result2.y);
	EXPECT_TRUE(result1.z == result2.z);

}


TEST(Vector3D, ScalarMultiplication)
{
	Vector3D instance(1, 2, 3);
	Vector3D multiplied1 = 5 * instance;
	Vector3D multiplied2 = instance * 5;


	EXPECT_FLOAT_EQ(5, multiplied1.x);
	EXPECT_FLOAT_EQ(10, multiplied1.y);
	EXPECT_FLOAT_EQ(15, multiplied1.z);

	EXPECT_FLOAT_EQ(multiplied1.x, multiplied2.x);
	EXPECT_FLOAT_EQ(multiplied1.y, multiplied2.y);
	EXPECT_FLOAT_EQ(multiplied1.z, multiplied2.z);

}

TEST(Vector3D, AssignmentPlusEquals)
{
	Vector3D source(5, -12, 0);
	Vector3D another(1, 1, 11);
	another += source;
	EXPECT_FLOAT_EQ(another.x , 6);
	EXPECT_FLOAT_EQ(another.y , -11);
	EXPECT_FLOAT_EQ(another.z , 11);

}
