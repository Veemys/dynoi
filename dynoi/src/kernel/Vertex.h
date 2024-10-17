#pragma once

#include <set>
#include <memory>

#include "Vector2D.h"

class Edge;

class Vertex
{
private:
	Vector2D coord_;
	std::set<std::shared_ptr<Edge>> edges_;

	Vertex() = delete;

public:
	explicit Vertex(const Vector2D& coord);

	Vector2D& coord();
	double x();
	double y();

	void addEdge(std::shared_ptr<Edge> edge);
	void removeEdge(std::shared_ptr<Edge> edge);
	std::set<std::shared_ptr<Edge>>& getEdges();
	const std::set<std::shared_ptr<Edge>>& getEdges() const;

};