#include "VoronoiDiagram.h"

#include "Cell.h"

VoronoiDiagram::VoronoiDiagram()
	: cells_(std::set<std::shared_ptr<Cell>>())
{

}

const std::set<std::shared_ptr<Cell>>& VoronoiDiagram::cells() const
{
	return cells_;
}

void VoronoiDiagram::addCell(std::shared_ptr<Cell> cell)
{
	cells_.emplace(cell);
}