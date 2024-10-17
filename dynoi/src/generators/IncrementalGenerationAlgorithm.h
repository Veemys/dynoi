#pragma once

#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

#include "../kernel/GenerationAlgorithm.h"

class Vector2D;
class Site;
class Vertex;
class Edge;
class Cell;
class Boundary;
class VoronoiDiagram;


class IncrementalGenerationAlgorithm : public GenerationAlgorithm
{
private:
	std::shared_ptr<Cell> currentCell_;
	std::unordered_map<std::shared_ptr<Edge>, std::shared_ptr<Vertex>> intersectedOldEdgesToNewVerticesLinks_;

	void initFirstCell(Boundary& boundary, VoronoiDiagram& vd, Site& firstSite);
	void addCell(VoronoiDiagram& vd, Site& site);
	std::shared_ptr<Cell> findNearestCell(VoronoiDiagram& vd, Site& site);
	std::pair<std::shared_ptr<Edge>, std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>> createDividingEdge(std::shared_ptr<Cell> newCell, std::shared_ptr<Cell> nextCell);
	bool someVertexIntersectedAndAdded(Vector2D& intersection, const std::shared_ptr<Edge>& edge, std::set<std::shared_ptr<Vertex>>& intersectedVertices);
	std::shared_ptr<Cell> getNextCell(std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>& intersectedEdges, std::shared_ptr<Edge> newEdge,
		std::set<std::shared_ptr<Cell>>& processedCell, std::set<std::shared_ptr<Cell>>& nearCells, std::shared_ptr<Cell> newCell);
	void changeDividedEdges(std::shared_ptr<Cell> newCell);
	void deleteAllEdgeInsideNewCell(std::shared_ptr<Cell> newCell);
	bool edgeLayInsideCell(std::shared_ptr<Edge> edge, std::shared_ptr<Cell> cell);
	std::shared_ptr<Edge> createEdge(std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end,
		std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>> parentCells);
	bool vertexLayInsideCell(std::shared_ptr<Vertex> vertex, std::shared_ptr<Cell> cell);
	bool vertexLayFromNewCellSide(std::shared_ptr<Vertex> vertex, std::shared_ptr<Edge> dividingEdge, std::shared_ptr<Cell> newCell);

public:
	virtual ~IncrementalGenerationAlgorithm() {}

	std::shared_ptr<VoronoiDiagram> apply(std::vector<Site>& sites, Boundary& boundary) override final;

};