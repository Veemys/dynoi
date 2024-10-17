#include "Edge.h"

#include "Vector2D.h"
#include "Cell.h"
#include "Vertex.h"

Edge::Edge(const Vertex& start, const Vertex& end)
	: start_(std::make_shared<Vertex>(start)),
	end_(std::make_shared<Vertex>(end))
{
	
}

Edge::Edge(std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end)
	: start_(start),
	end_(end)
{
	
}

Edge::Edge(const std::pair<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>>& points)
	: start_(points.first),
	end_(points.second)
{
	
}

std::pair<Vector2D, Vector2D> Edge::points() const
{
	return std::make_pair(start_->coord(), end_->coord());
}

const Vector2D& Edge::start() const
{
	return start_->coord();
}

const Vector2D& Edge::end() const
{
	return end_->coord();
}

Vector2D Edge::direction() const
{
	Vector2D result = end_->coord() - start_->coord();
	result.normalize();
	return result;
}

Vector2D Edge::normal() const
{
	Vector2D dir(direction());
	return Vector2D(-dir.y(), dir.x());
}

Vector2D Edge::center() const
{
	return Vector2D((start_->coord() + end_->coord()) / 2.0);
}

void Edge::addCell(std::shared_ptr<Cell> cell, ParentCellPosition cellPosition)
{
	switch (cellPosition)
	{
	case Edge::LEFT:
		parentCells_.first = cell;
		break;
	case Edge::RIGHT:
		parentCells_.second = cell;
		break;
	default:
		throw std::exception("Unknown parent cell position.");
	}
}

void Edge::addCells(const std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>>& cells)
{
	parentCells_ = cells;
}

Cell& Edge::getParentCell(ParentCellPosition cellPosition)
{
	switch (cellPosition)
	{
	case Edge::LEFT:
		return *parentCells_.first;
	case Edge::RIGHT:
		return *parentCells_.second;
	default:
		throw std::exception("Unknown parent cell position.");
	}
}

std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>>& Edge::getParentCells()
{
	return parentCells_;
}

void Edge::eraseParentCells()
{
	parentCells_.first = nullptr;
	parentCells_.second = nullptr;
}

Vertex& Edge::getStartVertex()
{
	return *start_;
}

Vertex& Edge::getEndVertex()
{
	return *end_;
}

std::pair<std::shared_ptr<Vertex>, std::shared_ptr<Vertex>> Edge::getVertices()
{
	return std::make_pair(start_, end_);
}

void Edge::replaceStartVertex(std::shared_ptr<Vertex> newStartVertex)
{
	start_ = newStartVertex;
}

void Edge::replaceEndVertex(std::shared_ptr<Vertex> newEndVertex)
{
	end_ = newEndVertex;
}

bool operator==(const Edge& e1, const Edge& e2)
{
	return (e1.start_->x() == e2.start_->x() &&
		e1.start_->y() == e2.start_->y() &&
		e1.end_->x() == e2.end_->x() &&
		e1.end_->y() == e2.end_->y());
}