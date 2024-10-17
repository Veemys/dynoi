#include "Cell.h"

#include "Edge.h"

Cell::Cell(const Site& s)
	: edges_(std::set<std::shared_ptr<Edge>>()),
	site_(s)
{

}

const std::set<std::shared_ptr<Edge>>& Cell::edges() const
{
	return edges_;
}

const Site& Cell::site() const
{
	return site_;
}

void Cell::addEdge(std::shared_ptr<Edge> edge)
{
	edges_.emplace(edge);
}

void Cell::eraseEdge(std::shared_ptr<Edge> edge)
{
	edges_.erase(edge);
}