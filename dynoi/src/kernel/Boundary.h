#pragma once

#include <memory>
#include <list>
#include <set>

class Vector2D;
class Vertex;
class Edge;

class Boundary
{
private:
	std::set<std::shared_ptr<Edge>> edges_;

	std::list<std::shared_ptr<Vertex>> convertVectorsToVertices(std::list<Vector2D>& points);

	std::shared_ptr<Edge> getNeighbourEdgeFromVertex(const std::shared_ptr<Edge> currentEdge, const Vertex& vertex);

public:
	Boundary(std::list<Vector2D>& points);

	const std::set<std::shared_ptr<Edge>>& edges() const;
	std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>> neighbourEdges(std::shared_ptr<Edge> edge);

};