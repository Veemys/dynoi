#pragma once

#include "../../dynoi/src/Cell.cpp"

TEST(CellTests, ordinaryConstructorTest)
{
	Site s(1.0, 2.0);
	Cell c(s);

	ASSERT_DOUBLE_EQ(1.0, c.site().x());
	ASSERT_DOUBLE_EQ(2.0, c.site().y());
}

TEST(CellTests, addEdgesTest)
{
	Cell c(Site(10.0, 20.0));
	ASSERT_DOUBLE_EQ(10.0, c.site().x());
	ASSERT_DOUBLE_EQ(20.0, c.site().y());
	Edge e1(std::make_shared<Vertex>(Vector2D(0.0, 0.0)), std::make_shared<Vertex>(Vector2D(1.0, 1.0)));
	Edge e2(std::make_shared<Vertex>(Vector2D(1.0, 1.0)), std::make_shared<Vertex>(Vector2D(2.0, 1.0)));
	Edge e3(std::make_shared<Vertex>(Vector2D(2.0, 1.0)), std::make_shared<Vertex>(Vector2D(3.0, 3.0)));
	c.addEdge(std::make_shared<Edge>(e1));
	c.addEdge(std::make_shared<Edge>(e2));
	c.addEdge(std::make_shared<Edge>(e3));
	auto& cell_edges(c.edges());
	for (auto& edge : cell_edges)
	{
		ASSERT_TRUE(*edge == e1 || *edge == e2 || *edge == e3);
	}
}