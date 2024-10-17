#pragma once

#include "../../dynoi/src/Triangle.cpp"

TEST(TriangleTests, constructorAndGettersTest)
{
	Triangle t(Vector2D(1.0, 2.4), Vector2D(2.0, 4.4), Vector2D(5.6, 2.4));

	ASSERT_DOUBLE_EQ(1.0, t.a().x());
	ASSERT_DOUBLE_EQ(2.4, t.a().y());
	ASSERT_DOUBLE_EQ(2.0, t.b().x());
	ASSERT_DOUBLE_EQ(4.4, t.b().y());
	ASSERT_DOUBLE_EQ(5.6, t.c().x());
	ASSERT_DOUBLE_EQ(2.4, t.c().y());
}

TEST(TriangleTests, areaTest1)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(0.0, 3.0));

	ASSERT_DOUBLE_EQ(3.0, t.area());
}

TEST(TriangleTests, areaTest2)
{
	Triangle t(Vector2D(1.0, 0.0), Vector2D(3.0, 0.0), Vector2D(1.0, 3.0));

	ASSERT_DOUBLE_EQ(3.0, t.area());
}

TEST(TriangleTests, areaTest3)
{
	Triangle t(Vector2D(1.0, 0.0), Vector2D(3.0, 0.0), Vector2D(2.0, 3.0));

	ASSERT_DOUBLE_EQ(3.0, t.area());
}

TEST(TriangleTests, perimeterTest1)
{
	Triangle t(Vector2D(0.0, 0.0), Vector2D(2.0, 0.0), Vector2D(0.0, 3.0));

	ASSERT_DOUBLE_EQ(5.0 + std::sqrt(13.0), t.perimeter());
}

TEST(TriangleTests, perimeterTest2)
{
	Triangle t(Vector2D(1.0, 0.0), Vector2D(3.0, 0.0), Vector2D(1.0, 3.0));

	ASSERT_DOUBLE_EQ(5.0 + std::sqrt(13.0), t.perimeter());
}

TEST(TriangleTests, perimeterTest3)
{
	Triangle t(Vector2D(1.0, 0.0), Vector2D(3.0, 0.0), Vector2D(2.0, 3.0));

	ASSERT_DOUBLE_EQ(2.0 + 2.0 * std::sqrt(10.0), t.perimeter());
}