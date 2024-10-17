#pragma once

#include <memory>
#include <vector>

#include "../kernel/GenerationAlgorithm.h"

class Vector2D;
class Site;
class Edge;
class Cell;
class VoronoiDiagram;
class Boundary;

class DegenerateHexaDiagramGenerationAlgorithm : public GenerationAlgorithm
{
private:
	// Boundary's edges
	std::shared_ptr<Edge> leftBorder_;
	std::shared_ptr<Edge> rightBorder_;
	std::shared_ptr<Edge> bottomBorder_;
	std::shared_ptr<Edge> topBorder_;

	int cellsAlongLength_;
	int cellsAlongWidth_;

	std::vector<std::shared_ptr<Cell>> cells_;

	void deconstructInputSites(std::vector<Site>& sites);
	std::shared_ptr<Cell> createCell(int index);
	std::pair<Vector2D, Vector2D> createDevidingStraight(std::shared_ptr<Cell> first, std::shared_ptr<Cell> second);

public:
	DegenerateHexaDiagramGenerationAlgorithm();

	virtual ~DegenerateHexaDiagramGenerationAlgorithm() {}

	std::shared_ptr<VoronoiDiagram> apply(std::vector<Site>& sites, Boundary& boundary) override final;

};