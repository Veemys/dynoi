#pragma once

#include "../../dynoi/src/Vertex.cpp"

TEST(VertexTests, constructorAndGettersTest)
{
	Vector2D v1(4.4, 5.7);

	Vertex vert(v1);

	ASSERT_DOUBLE_EQ(4.4, vert.coord().x());
	ASSERT_DOUBLE_EQ(4.4, vert.x());
	ASSERT_DOUBLE_EQ(5.7, vert.coord().y());
	ASSERT_DOUBLE_EQ(5.7, vert.y());
}

TEST(VertexTests, addAndGetEdgesTest)
{
	Vector2D v1(4.4, 5.7);
	Vector2D v2(5.6, 3.5);
	Vector2D v3(4.1, 2.0);
	Vector2D v4(5.5, 10.5);

	Vertex vert1(v1);
	Vertex vert2(v2);
	Vertex vert3(v3);
	Vertex vert4(v4);

	std::set<std::shared_ptr<Edge>> edges;
	std::shared_ptr<Edge> edge1(std::make_shared<Edge>(vert1, vert2));
	std::shared_ptr<Edge> edge2(std::make_shared<Edge>(vert1, vert3));
	std::shared_ptr<Edge> edge3(std::make_shared<Edge>(vert1, vert4));
	edges.emplace(edge1);
	edges.emplace(edge2);
	edges.emplace(edge3);

	vert1.addEdge(edge1);
	vert1.addEdge(edge2);
	vert1.addEdge(edge3);

	vert2.addEdge(edge1);
	
	vert3.addEdge(edge2);
	
	vert4.addEdge(edge3);

	ASSERT_EQ(3, vert1.getEdges().size());
	ASSERT_EQ(1, vert2.getEdges().size());
	ASSERT_EQ(1, vert3.getEdges().size());
	ASSERT_EQ(1, vert4.getEdges().size());

	for (std::shared_ptr<Edge> edge : vert1.getEdges())
	{
		ASSERT_TRUE(edges.contains(edge));
	}
	std::shared_ptr<Edge> edgeFromVert2(*vert2.getEdges().begin());
	ASSERT_TRUE(edge1 == edgeFromVert2);
	std::shared_ptr<Edge> edgeFromVert3(*vert3.getEdges().begin());
	ASSERT_TRUE(edge2 == edgeFromVert3);
	std::shared_ptr<Edge> edgeFromVert4(*vert4.getEdges().begin());
	ASSERT_TRUE(edge3 == edgeFromVert4);
}