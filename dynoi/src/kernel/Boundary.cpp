#include "Boundary.h"

#include "Edge.h"
#include "Vertex.h"

Boundary::Boundary(std::list<Vector2D>& points)
	: edges_(std::set<std::shared_ptr<Edge>>())
{
	std::list<std::shared_ptr<Vertex>> vertices = convertVectorsToVertices(points);
	auto firstPoint = vertices.begin();
	auto nextPoint = vertices.begin();
	while(true)
	{
		auto currentPoint = nextPoint++;
		std::shared_ptr<Edge> newEdge = nullptr;
		if (nextPoint == vertices.end())
		{
			newEdge = std::make_shared<Edge>(*currentPoint, *firstPoint);
			(*currentPoint)->addEdge(newEdge);
			(*firstPoint)->addEdge(newEdge);
			edges_.emplace(newEdge);
			break;
		}
		else
		{
			newEdge = std::make_shared<Edge>(*currentPoint, *nextPoint);
			(*currentPoint)->addEdge(newEdge);
			(*nextPoint)->addEdge(newEdge);
			edges_.emplace(newEdge);
		}
	}
}

std::list<std::shared_ptr<Vertex>> Boundary::convertVectorsToVertices(std::list<Vector2D>& points)
{
	std::list<std::shared_ptr<Vertex>> vertices;
	for (auto currentPoint = points.begin(); currentPoint != points.end(); ++currentPoint)
	{
		vertices.push_back(std::make_shared<Vertex>(*currentPoint));
	}
	return vertices;
}

const std::set<std::shared_ptr<Edge>>& Boundary::edges() const
{
	return edges_;
}

std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>> Boundary::neighbourEdges(std::shared_ptr<Edge> edge)
{
	if (!edges_.contains(edge))
	{
		return std::make_pair(nullptr, nullptr);
	}
	std::shared_ptr<Edge> firstNeighbour = getNeighbourEdgeFromVertex(edge, edge->getStartVertex());
	std::shared_ptr<Edge> secondNeighbour = getNeighbourEdgeFromVertex(edge, edge->getEndVertex());
	return std::make_pair(firstNeighbour, secondNeighbour);
}

std::shared_ptr<Edge> Boundary::getNeighbourEdgeFromVertex(const std::shared_ptr<Edge> currentEdge, const Vertex& vertex)
{
	auto& edgesFromVertex = vertex.getEdges();
	auto edgeFromVertex = edgesFromVertex.begin();
	if (currentEdge == *edgeFromVertex)
	{
		return *(++edgeFromVertex);
	}
	else
	{
		return *(edgeFromVertex);
	}
}