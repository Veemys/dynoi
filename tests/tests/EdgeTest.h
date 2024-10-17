#pragma once

#include "../../dynoi/src/Edge.cpp"

TEST(EdgeTests, constructorTest1)
{
	Vector2D v1(3.0, 5.0);
	Vector2D v2(2.0, 6.0);
	Vertex vert1 = Vertex(v1);
	Vertex vert2 = Vertex(v2);

	Edge e(vert1, vert2);
	
	ASSERT_DOUBLE_EQ(3.0, e.points().first.x());
	ASSERT_DOUBLE_EQ(5.0, e.points().first.y());
	ASSERT_DOUBLE_EQ(2.0, e.points().second.x());
	ASSERT_DOUBLE_EQ(6.0, e.points().second.y());
}

TEST(EdgeTests, constructorTest2)
{
	Vector2D v1(3.0, 5.0);
	Vector2D v2(2.0, 6.0);

	Edge e(std::make_shared<Vertex>(v1), std::make_shared<Vertex>(v2));

	ASSERT_DOUBLE_EQ(3.0, e.points().first.x());
	ASSERT_DOUBLE_EQ(5.0, e.points().first.y());
	ASSERT_DOUBLE_EQ(2.0, e.points().second.x());
	ASSERT_DOUBLE_EQ(6.0, e.points().second.y());
}

TEST(EdgeTests, constructorTest3)
{
	Vector2D v1(3.0, 5.0);
	Vector2D v2(2.0, 6.0);
	std::pair<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> pairVectors(
		std::make_pair(
			std::make_shared<Vertex>(v1),
			std::make_shared<Vertex>(v2)));

	Edge e(pairVectors);

	ASSERT_DOUBLE_EQ(3.0, e.points().first.x());
	ASSERT_DOUBLE_EQ(5.0, e.points().first.y());
	ASSERT_DOUBLE_EQ(2.0, e.points().second.x());
	ASSERT_DOUBLE_EQ(6.0, e.points().second.y());
}

TEST(EdgeTests, directionTest)
{
	Vector2D start(0.0, 0.0);
	Vector2D end(2.0, 2.0);
	Vertex vert_start = Vertex(start);
	Vertex vert_end = Vertex(end);
	Edge e(vert_start, vert_end);

	Vector2D direction(e.direction());

	ASSERT_DOUBLE_EQ(1 / std::sqrt(2), direction.x());
	ASSERT_DOUBLE_EQ(1 / std::sqrt(2), direction.y());
}

TEST(EdgeTests, normalTest)
{
	Vector2D start(0.0, 0.0);
	Vector2D end(2.0, 2.0);
	Vertex vert_start = Vertex(start);
	Vertex vert_end = Vertex(end);
	Edge e(vert_start, vert_end);

	Vector2D normal(e.normal());

	ASSERT_DOUBLE_EQ(-1 / std::sqrt(2), normal.x());
	ASSERT_DOUBLE_EQ(1 / std::sqrt(2), normal.y());
}

TEST(EdgeTests, getCenterTest)
{
	Vector2D start(1.0, 5.0);
	Vector2D end(6.0, 10.0);
	Vertex vert_start = Vertex(start);
	Vertex vert_end = Vertex(end);
	Edge e(vert_start, vert_end);

	Vector2D center(e.center());

	ASSERT_DOUBLE_EQ(3.5, center.x());
	ASSERT_DOUBLE_EQ(7.5, center.y());
}

TEST(EdgeTests, getStartTest)
{
	Vector2D start(1.0, 5.0);
	Vector2D end(6.0, 10.0);
	Vertex vert_start = Vertex(start);
	Vertex vert_end = Vertex(end);
	Edge e(vert_start, vert_end);

	ASSERT_DOUBLE_EQ(1.0, e.start().x());
	ASSERT_DOUBLE_EQ(5.0, e.start().y());
}

TEST(EdgeTests, getEndTest)
{
	Vector2D start(1.0, 5.0);
	Vector2D end(6.0, 10.0);
	Vertex vert_start = Vertex(start);
	Vertex vert_end = Vertex(end);
	Edge e(vert_start, vert_end);
	ASSERT_DOUBLE_EQ(6.0, e.end().x());
	ASSERT_DOUBLE_EQ(10.0, e.end().y());
}

TEST(EdgeTests, comparisonTest)
{
	Vector2D start1(1.0, 5.0);
	Vector2D end1(6.0, 10.0);
	Vector2D start2(1.0, 5.0);
	Vector2D end2(6.0, 10.0);
	Vector2D start3(1.1, 5.0);
	Vector2D end3(6.0, 10.0);
	Vertex start1_vert(start1);
	Vertex end1_vert(end1);
	Vertex start2_vert(start2);
	Vertex end2_vert(end2);
	Vertex start3_vert(start3);
	Vertex end3_vert(end3);
	Edge e1(start1_vert, end1_vert);
	Edge e2(start2_vert, end2_vert);
	Edge e3(start3_vert, end3_vert);

	ASSERT_TRUE(e1 == e2);
	ASSERT_FALSE(e1 == e3);
	ASSERT_FALSE(e2 == e3);
}

TEST(EdgeTests, addParentCellsTest1)
{
	std::shared_ptr<Cell> c(std::make_shared<Cell>(Site(1.0, 1.0)));
	std::shared_ptr<Edge> e = std::make_shared<Edge>(
		std::make_shared<Vertex>(Vector2D(2.0, 0.0)),
		std::make_shared<Vertex>(Vector2D(2.0, 2.0)));

	c->addEdge(e);
	e->addCells(std::make_pair(c, nullptr));
	
	ASSERT_DOUBLE_EQ(1.0, e->getParentCells().first->site().x());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCells().first->site().y());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCell(Edge::LEFT).site().x());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCell(Edge::LEFT).site().y());
	ASSERT_TRUE(e->getParentCells().first != nullptr);
	ASSERT_TRUE(e->getParentCells().second == nullptr);
}

TEST(EdgeTests, addParentCellsTest2)
{
	std::shared_ptr<Cell> c1(std::make_shared<Cell>(Site(1.0, 1.0)));
	std::shared_ptr<Cell> c2(std::make_shared<Cell>(Site(3.0, 1.0)));
	std::shared_ptr<Edge> e = std::make_shared<Edge>(
		std::make_shared<Vertex>(Vector2D(2.0, 0.0)),
		std::make_shared<Vertex>(Vector2D(2.0, 2.0)));

	c1->addEdge(e);
	c2->addEdge(e);
	e->addCells(std::make_pair(c1, c2));

	ASSERT_DOUBLE_EQ(1.0, e->getParentCells().first->site().x());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCells().first->site().y());
	ASSERT_DOUBLE_EQ(3.0, e->getParentCells().second->site().x());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCells().second->site().y());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCell(Edge::LEFT).site().x());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCell(Edge::LEFT).site().y());
	ASSERT_DOUBLE_EQ(3.0, e->getParentCell(Edge::RIGHT).site().x());
	ASSERT_DOUBLE_EQ(1.0, e->getParentCell(Edge::RIGHT).site().y());
	ASSERT_TRUE(e->getParentCells().first != nullptr);
	ASSERT_TRUE(e->getParentCells().second != nullptr);
}

TEST(EdgeTests, getVertexesTest)
{
	Vector2D v1(3.0, 5.0);
	Vector2D v2(2.0, 6.0);
	Vertex vert1 = Vertex(v1);
	Vertex vert2 = Vertex(v2);

	Edge e(vert1, vert2);

	ASSERT_DOUBLE_EQ(3.0, e.getStartVertex().coord().x());
	ASSERT_DOUBLE_EQ(5.0, e.getStartVertex().coord().y());
	ASSERT_DOUBLE_EQ(2.0, e.getEndVertex().coord().x());
	ASSERT_DOUBLE_EQ(6.0, e.getEndVertex().coord().y());
	ASSERT_DOUBLE_EQ(3.0, e.getVertices().first->coord().x());
	ASSERT_DOUBLE_EQ(5.0, e.getVertices().first->coord().y());
	ASSERT_DOUBLE_EQ(2.0, e.getVertices().second->coord().x());
	ASSERT_DOUBLE_EQ(6.0, e.getVertices().second->coord().y());
}

TEST(EdgeTests, replaceStartVertexTest)
{
	Vector2D v1(3.0, 5.0);
	Vector2D v2(2.0, 6.0);
	Vertex vert1 = Vertex(v1);
	Vertex vert2 = Vertex(v2);

	Edge e(vert1, vert2);

	Vector2D v3(11.0, 12.0);
	std::shared_ptr<Vertex> newStartVertex(std::make_shared<Vertex>(v3));

	e.replaceStartVertex(newStartVertex);

	ASSERT_DOUBLE_EQ(11.0, e.getStartVertex().coord().x());
	ASSERT_DOUBLE_EQ(12.0, e.getStartVertex().coord().y());
	ASSERT_DOUBLE_EQ(2.0, e.getEndVertex().coord().x());
	ASSERT_DOUBLE_EQ(6.0, e.getEndVertex().coord().y());
}

TEST(EdgeTests, replaceEndVertexTest)
{
	Vector2D v1(3.0, 5.0);
	Vector2D v2(2.0, 6.0);
	Vertex vert1 = Vertex(v1);
	Vertex vert2 = Vertex(v2);

	Edge e(vert1, vert2);

	Vector2D v3(11.0, 12.0);
	std::shared_ptr<Vertex> newEndVertex(std::make_shared<Vertex>(v3));

	e.replaceEndVertex(newEndVertex);

	ASSERT_DOUBLE_EQ(3.0, e.getStartVertex().coord().x());
	ASSERT_DOUBLE_EQ(5.0, e.getStartVertex().coord().y());
	ASSERT_DOUBLE_EQ(11.0, e.getEndVertex().coord().x());
	ASSERT_DOUBLE_EQ(12.0, e.getEndVertex().coord().y());
}