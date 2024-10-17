#pragma once

#include <set>
#include <memory>

#include "Site.h";

class Edge;

class Cell
{
private:
	Site site_;
	std::set<std::shared_ptr<Edge>> edges_;

	Cell() = delete;

public:
	Cell(const Site& s);

	~Cell() {}

	const std::set<std::shared_ptr<Edge>>& edges() const;
	const Site& site() const;
	void addEdge(std::shared_ptr<Edge> edge);
	void eraseEdge(std::shared_ptr<Edge> edge);

};