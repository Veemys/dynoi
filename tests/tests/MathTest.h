#pragma once

#include "../../dynoi/src/Math.cpp"

TEST(MathTests, straightIntersectionTest1)
{
	std::pair<Vector2D, Vector2D> oneStraight(std::make_pair(Vector2D(1.0, 3.0), Vector2D(3.0, -1.0)));
	std::pair<Vector2D, Vector2D> twoStraight(std::make_pair(Vector2D(0.5, 1.0), Vector2D(2.5, 3.0)));

	Vector2D cross = Math::straightsIntersection(oneStraight, twoStraight);

	ASSERT_DOUBLE_EQ(1.5, cross.x());
	ASSERT_DOUBLE_EQ(2.0, cross.y());
}

TEST(MathTests, straightIntersectionTest2)
{
	std::pair<Vector2D, Vector2D> oneStraight(std::make_pair(Vector2D(0.5, 1.0), Vector2D(1.0, 2.0)));
	std::pair<Vector2D, Vector2D> twoStraight(std::make_pair(Vector2D(2.0, 2.0), Vector2D(2.5, 1.0)));

	Vector2D cross = Math::straightsIntersection(oneStraight, twoStraight);

	ASSERT_DOUBLE_EQ(1.5, cross.x());
	ASSERT_DOUBLE_EQ(3.0, cross.y());
}

TEST(MathTests, straightIntersectionTest3)
{
	std::pair<Vector2D, Vector2D> oneStraight(std::make_pair(Vector2D(-0.5, 1.0), Vector2D(-1.0, 2.0)));
	std::pair<Vector2D, Vector2D> twoStraight(std::make_pair(Vector2D(-2.0, 2.0), Vector2D(-2.5, 1.0)));

	Vector2D cross = Math::straightsIntersection(oneStraight, twoStraight);

	ASSERT_DOUBLE_EQ(-1.5, cross.x());
	ASSERT_DOUBLE_EQ(3.0, cross.y());
}

TEST(MathTests, parallelStraightIntersectionTest)
{
	std::pair<Vector2D, Vector2D> oneStraight(std::make_pair(Vector2D(-1.0, 1.0), Vector2D(-1.0, 3.0)));
	std::pair<Vector2D, Vector2D> twoStraight(std::make_pair(Vector2D(-2.0, 1.0), Vector2D(-2.0, 4.0)));

	Vector2D cross = Math::straightsIntersection(oneStraight, twoStraight);

	ASSERT_DOUBLE_EQ(std::numeric_limits<double>::max(), cross.x());
	ASSERT_DOUBLE_EQ(std::numeric_limits<double>::max(), cross.y());
}

TEST(MathTests, sameStraightIntersectionTest)
{
	std::pair<Vector2D, Vector2D> oneStraight(std::make_pair(Vector2D(-1.0, 1.0), Vector2D(-1.0, 3.0)));
	std::pair<Vector2D, Vector2D> twoStraight(std::make_pair(Vector2D(-1.0, 1.0), Vector2D(-1.0, 2.0)));

	Vector2D cross = Math::straightsIntersection(oneStraight, twoStraight);

	ASSERT_DOUBLE_EQ(std::numeric_limits<double>::max(), cross.x());
	ASSERT_DOUBLE_EQ(std::numeric_limits<double>::max(), cross.y());
}

TEST(MathTests, pointLayInsideTriangleTest1)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(1.0, 3.0));
	Vector2D point(0.5, 0.5);

	ASSERT_TRUE(Math::pointLayInsideTriangle(point, t));
}

TEST(MathTests, pointLayInsideTriangleTest2)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(1.0, 3.0));
	Vector2D point(0.5, 1.5);

	ASSERT_TRUE(Math::pointLayInsideTriangle(point, t));
}

TEST(MathTests, pointLayInsideTriangleTest3)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(1.0, 3.0));
	Vector2D point(1.0, 3.0);

	ASSERT_TRUE(Math::pointLayInsideTriangle(point, t));
}

TEST(MathTests, pointDoentLayInsideTriangleTest1)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(1.0, 3.0));
	Vector2D point(1.0, -0.001);

	ASSERT_FALSE(Math::pointLayInsideTriangle(point, t));
}

TEST(MathTests, pointDoentLayInsideTriangleTest2)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(1.0, 3.0));
	Vector2D point(0.0, 3.0);

	ASSERT_FALSE(Math::pointLayInsideTriangle(point, t));
}