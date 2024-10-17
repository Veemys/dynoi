#pragma once

#include <memory>
#include <set>

class Cell;

class VoronoiDiagram
{
private:
	std::set<std::shared_ptr<Cell>> cells_;

public:
	VoronoiDiagram();

	~VoronoiDiagram() {}

	const std::set<std::shared_ptr<Cell>>& cells() const;
	void addCell(std::shared_ptr<Cell> cell);

};