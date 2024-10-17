#pragma once

#include <utility>
#include <memory>

class Vector2D;
class Cell;
class Vertex;

class Edge
{
public:
	enum ParentCellPosition
	{
		RIGHT,
		LEFT
	};

private:
	std::shared_ptr<Vertex> start_;
	std::shared_ptr<Vertex> end_;
	std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>> parentCells_;

	Edge() = delete;

public:
	explicit Edge(const Vertex& start, const Vertex& end);
	Edge(std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end);
	Edge(const std::pair<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>>& points);

	~Edge() {}

	std::pair<Vector2D, Vector2D> points() const;
	const Vector2D& start() const;
	const Vector2D& end() const;

	Vector2D direction() const;
	Vector2D normal() const;
	Vector2D center() const;

	void addCell(std::shared_ptr<Cell> cell, ParentCellPosition cellPosition);
	void addCells(const std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>>& cells);
	Cell& getParentCell(ParentCellPosition cellPosition);
	std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>>& getParentCells();
	void eraseParentCells();

	Vertex& getStartVertex();
	Vertex& getEndVertex();
	std::pair<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> getVertices();

	void replaceStartVertex(std::shared_ptr<Vertex> newStartVertex);
	void replaceEndVertex(std::shared_ptr<Vertex> newEndVertex);

	friend bool operator==(const Edge& e1, const Edge& e2);

};