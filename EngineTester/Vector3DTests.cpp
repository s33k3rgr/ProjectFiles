#include <gtest/gtest.h>
#include <Vector3D.h>
#include <cmath>
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


TEST(Vector3D, Subtraction)
{
	Vector3D first(8, 3);
	Vector3D second(7, 1);
	Vector3D result = first - second;
	EXPECT_FLOAT_EQ(result.x , 1);
	EXPECT_FLOAT_EQ(result.y , 2);

	result = second - first;
	EXPECT_FLOAT_EQ(result.x , -1);
	EXPECT_FLOAT_EQ(result.y , -2);
}

TEST(Vector3D, Perpedicularity)
{
	Vector3D meVector(4, 2);
	Vector3D perpCw = meVector.perpCwXy();
	Vector3D perpCcw = meVector.perpCcwXy();
	EXPECT_FLOAT_EQ(perpCw.x, 2);
	EXPECT_FLOAT_EQ(perpCw.y, -4);
	EXPECT_FLOAT_EQ(perpCcw.x, -2);
	EXPECT_FLOAT_EQ(perpCcw.y, 4);
}

TEST(Vector3D, DotProduct)
{
	Vector3D first(1,2,3);
	Vector3D second(4,5,6);
	float result = first.dot(second);
	EXPECT_FLOAT_EQ(result , 32);
}

TEST(Vector3D, Magnitude)
{
	Vector3D ourVector(3,4,5);
	float magnitude = ourVector.magnitude();
	EXPECT_FLOAT_EQ(magnitude, 7.0710678118f);
}


TEST(Vector3D, Normalization)
{
	Vector3D vec(1,2,3);
	Vector3D normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, 0.2672612419f);
	EXPECT_FLOAT_EQ(normalized.y, 0.5345224838f);
	EXPECT_FLOAT_EQ(normalized.z, 0.8017837257f);
}


TEST(Vector3D, MagnitudeSquared)
{
	Vector3D ourVector(3,4,5);
	float magnitudeSquared = ourVector.magnitudeSquared();
	EXPECT_FLOAT_EQ(magnitudeSquared, 50.0f);
}



void testProjectionAlgorithms(
	const Vector3D& source,
	const Vector3D& target)
{
	Vector3D targetNormalized = target.normalized();
	Vector3D oldResult = source.dot(targetNormalized) * targetNormalized;
	Vector3D newResult = source.projectOnto(target);
	EXPECT_FLOAT_EQ(oldResult.x, newResult.x);
	EXPECT_FLOAT_EQ(oldResult.y, newResult.y);
	EXPECT_FLOAT_EQ(oldResult.z, newResult.z);
}

TEST(Vector3D, projectOnto)
{
	Vector3D source(2, 4);
	Vector3D target(1, 0);
	Vector3D result = source.projectOnto(target);
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
	EXPECT_FLOAT_EQ(result.z, 0.0f);

	Vector3D vectors[] =
	{
		Vector3D(1.0f, 2.0f, 3.0f),
		Vector3D(4.8f, 9.1f, 5.6f),
		Vector3D(0.0f, 5.0f, 0.0f),
		Vector3D(-3.2f, -4.9f, 6.7f),
		Vector3D(2.4f, 3.1f, -99.6f)
	};

	const uint NUM_VECTORS = sizeof(vectors) / sizeof(*vectors);
	for(uint i = 0; i < NUM_VECTORS - 1; i++)
	{
		testProjectionAlgorithms(vectors[i], vectors[i + 1]);
		testProjectionAlgorithms(vectors[i + 1], vectors[i]);
	}

	Vector3D a(0.5f, sqrt(3.0f) / 2.0f);
	Vector3D b(sqrt(3.0f) / 2.0f, 0.5f);
	float dotResult = a.dot(b);
	EXPECT_FLOAT_EQ(dotResult, cos( M_PI / 6.0f));
}


TEST(Vector3D, lerp)
{
	Vector3D source(4.7f, 9.2f, 7.1f);
	Vector3D target(7.4f, 2.9f, 1.7f);
	Vector3D difference = target - source;
	float alpha = 0.0f;
	while(alpha <= 1.0f)
	{
		Vector3D lerpResult1 = lerp(alpha, source, target);
		Vector3D lerpResult2 = source + alpha * difference;
		EXPECT_FLOAT_EQ(lerpResult1.x , lerpResult2.x);
		EXPECT_FLOAT_EQ(lerpResult1.y , lerpResult2.y);
		EXPECT_FLOAT_EQ(lerpResult1.z , lerpResult2.z);
		alpha += 0.01f;
	}

}


