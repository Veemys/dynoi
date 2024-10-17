#include "Vertex.h"

#include "Vector2D.h"
#include "Edge.h"

Vertex::Vertex(const Vector2D& coord)
	: coord_(coord)
{

}

Vector2D& Vertex::coord()
{
	return coord_;
}

double Vertex::x()
{
	return coord_.x();
}

double Vertex::y()
{
	return coord_.y();
}

void Vertex::addEdge(std::shared_ptr<Edge> edge)
{
	edges_.emplace(edge);
}

void Vertex::removeEdge(std::shared_ptr<Edge> edge)
{
	edges_.erase(edge);
}

std::set<std::shared_ptr<Edge>>& Vertex::getEdges()
{
	return edges_;
}

const std::set<std::shared_ptr<Edge>>& Vertex::getEdges() const
{
	return edges_;
}