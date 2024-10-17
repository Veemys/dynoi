#pragma once

#include "../../dynoi/src/Vector2D.cpp"

TEST(Vector2dTests, emptyConstructorTest)
{
	Vector2D vector;
	ASSERT_DOUBLE_EQ(0, vector.x());
	ASSERT_DOUBLE_EQ(0, vector.y());
}

TEST(Vector2dTests, constructorTest)
{
	Vector2D vector(1.0, 2.0);
	ASSERT_DOUBLE_EQ(1.0, vector.x());
	ASSERT_DOUBLE_EQ(2.0, vector.y());
}

TEST(Vector2dTests, copyConstractorTest)
{
	Vector2D vector(1.0, 2.0);
	Vector2D other(vector);
	ASSERT_DOUBLE_EQ(1.0, other.x());
	ASSERT_DOUBLE_EQ(2.0, other.y());
}

TEST(Vector2dTests, equalOperatorTest)
{
	Vector2D vector(1.0, 2.0);
	Vector2D other = vector;
	ASSERT_DOUBLE_EQ(1.0, other.x());
	ASSERT_DOUBLE_EQ(2.0, other.y());
}

TEST(Vector2dTests, moveConstructorTest)
{
	Vector2D vector(1.0, 2.0);
	Vector2D other(std::move(vector));
	ASSERT_DOUBLE_EQ(1.0, other.x());
	ASSERT_DOUBLE_EQ(2.0, other.y());
}

TEST(Vector2dTests, sumOperatorTest)
{
	Vector2D one(10.0, 20.0);
	Vector2D two(30.0, 40.0);
	Vector2D sum = one + two;
	ASSERT_DOUBLE_EQ(40.0, sum.x());
	ASSERT_DOUBLE_EQ(60.0, sum.y());
}

TEST(Vector2dTests, minusOperatorTest)
{
	Vector2D one(10.0, 20.5);
	Vector2D two(5.5, 20.6);
	Vector2D diff = one - two;
	ASSERT_NEAR(4.5, diff.x(), 1e-10);
	ASSERT_NEAR(-0.1, diff.y(), 1e-10);
}

TEST(Vector2dTests, dotOperatorTest1)
{
	Vector2D vector(10.0, 20.0);
	Vector2D newVector = 2.0 * vector;
	ASSERT_DOUBLE_EQ(20.0, newVector.x());
	ASSERT_DOUBLE_EQ(40.0, newVector.y());
}

TEST(Vector2dTests, dotOperatorTest2)
{
	Vector2D vector(10.0, 20.0);
	Vector2D newVector = vector * 2.0;
	ASSERT_DOUBLE_EQ(20.0, newVector.x());
	ASSERT_DOUBLE_EQ(40.0, newVector.y());
}

TEST(Vector2dTests, scalarProducitonTest)
{
	Vector2D one(10.0, 20.5);
	Vector2D two(5.5, 20.6);
	double product = one * two;
	ASSERT_DOUBLE_EQ(477.3, product);
}

TEST(Vector2dTests, divideOperatorTest)
{
	Vector2D vector(9.0, 18.0);
	Vector2D divide = vector / 3.0;
	ASSERT_DOUBLE_EQ(3.0, divide.x());
	ASSERT_DOUBLE_EQ(6.0, divide.y());
}

TEST(Vector2dTests, vectorLengthTest)
{
	Vector2D vector(10.0, 20.0);
	ASSERT_DOUBLE_EQ(std::sqrt(10.0 * 10.0 + 20.0 * 20.0), vector.length());
}

TEST(Vector2dTests, getNormalizedVectorTest)
{
	Vector2D vector(10.0, 20.0);
	Vector2D normalizedVector = vector.getNorm();
	ASSERT_DOUBLE_EQ(10.0 / vector.length(), normalizedVector.x());
	ASSERT_DOUBLE_EQ(20.0 / vector.length(), normalizedVector.y());
}

TEST(Vector2dTests, normalizeVectorTest)
{
	Vector2D vector(10.0, 20.0);
	double oldLength = vector.length();
	vector.normalize();
	ASSERT_DOUBLE_EQ(10.0 / oldLength, vector.x());
	ASSERT_DOUBLE_EQ(20.0 / oldLength, vector.y());
}

TEST(Vector2dTests, getReversedVectorTest)
{
	Vector2D vector(10.0, 20.0);
	Vector2D reversedVector = vector.getReverse();
	ASSERT_DOUBLE_EQ(-10.0, reversedVector.x());
	ASSERT_DOUBLE_EQ(-20.0, reversedVector.y());
}

TEST(Vector2dTests, reverseVectorTest)
{
	Vector2D vector(10.0, 20.0);
	vector.reverse();
	ASSERT_DOUBLE_EQ(-10.0, vector.x());
	ASSERT_DOUBLE_EQ(-20.0, vector.y());
}