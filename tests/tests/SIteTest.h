#pragma once

#include "../../dynoi/src/Site.cpp"

TEST(SiteTests, emptyConstructorTest)
{
	Site s;
	ASSERT_DOUBLE_EQ(0.0, s.coord().x());
	ASSERT_DOUBLE_EQ(0.0, s.coord().y());
}

TEST(SiteTests, constructorTest1)
{
	Vector2D coord(1.0, 3.0);
	Site s(coord);
	ASSERT_DOUBLE_EQ(1.0, s.coord().x());
	ASSERT_DOUBLE_EQ(3.0, s.coord().y());
}

TEST(SiteTests, constructorTest2)
{
	Site s(1.0, 3.0);
	ASSERT_DOUBLE_EQ(1.0, s.coord().x());
	ASSERT_DOUBLE_EQ(3.0, s.coord().y());
}

TEST(SiteTests, copyConstructorTest)
{
	Site one(1.0, 2.0);
	Site two(one);
	ASSERT_DOUBLE_EQ(1.0, two.coord().x());
	ASSERT_DOUBLE_EQ(2.0, two.coord().y());
}

TEST(SiteTests, directCoordTest)
{
	Site s(15.0, 12.0);
	ASSERT_DOUBLE_EQ(15.0, s.x());
	ASSERT_DOUBLE_EQ(12.0, s.y());
}