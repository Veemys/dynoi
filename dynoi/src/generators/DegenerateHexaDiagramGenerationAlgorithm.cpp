#include "DegenerateHexaDiagramGenerationAlgorithm.h"

#include <list>

#include "../kernel/Vector2D.h"
#include "../kernel/Site.h"
#include "../kernel/Vertex.h"
#include "../kernel/Edge.h"
#include "../kernel/Cell.h"
#include "../kernel/GenerationAlgorithm.h"
#include "../kernel/Boundary.h"
#include "../kernel/VoronoiDiagram.h"
#include "../mathem/Math.h"

DegenerateHexaDiagramGenerationAlgorithm::DegenerateHexaDiagramGenerationAlgorithm()
	: GenerationAlgorithm(),
	cellsAlongLength_(0),
	cellsAlongWidth_(0),
	cells_(0)
{

}

std::shared_ptr<VoronoiDiagram> DegenerateHexaDiagramGenerationAlgorithm::apply(std::vector<Site>& sites, Boundary& boundary)
{
	std::shared_ptr<VoronoiDiagram> vd = std::make_shared<VoronoiDiagram>();

	// need to return empty voronoi diagram if sites are not applyable for generate hexa diagram
	// ??

	// also need to check boundary separately

	// input sites deconstruction
	deconstructInputSites(sites);

	// creating of cells
	for (int i = 0; i < sites.size(); ++i)
	{
		cells_.push_back(std::make_shared<Cell>(sites[i]));
	}

	// main generation code
	std::list<Vector2D> points = std::list<Vector2D>();
	points.push_back(Vector2D(0.0, 0.0));
	points.push_back(Vector2D(0.0, 10.0));
	points.push_back(Vector2D(10.0, 10.0));
	points.push_back(Vector2D(10.0, 0.0));

	auto& boundEdges = boundary.edges();
	auto boundEdge = boundEdges.begin();
	leftBorder_ = *boundEdge;
	topBorder_ = *(++boundEdge);
	rightBorder_ = *(++boundEdge);
	bottomBorder_ = *(++boundEdge);

	for (int cellIndex = 0; cellIndex < cells_.size(); ++cellIndex)
	{
		createCell(cellIndex);
	}

	return vd;
}

void DegenerateHexaDiagramGenerationAlgorithm::deconstructInputSites(std::vector<Site>& sites)
{
	int startSegmentIndex = 0;
	int endSegmentIndex = startSegmentIndex + 2;
	int currentSiteIndex = startSegmentIndex + 1;
	for (;; ++startSegmentIndex, ++endSegmentIndex, ++currentSiteIndex)
	{
		const Vector2D& startSegment = sites[startSegmentIndex].coord();
		const Vector2D& endSegment = sites[endSegmentIndex].coord();
		const Site& currentSite = sites[currentSiteIndex];

		std::pair<Vector2D, Vector2D> lineSegment = std::make_pair(startSegment, endSegment);
		if (!Math::pointLayInsideSegment(currentSite.coord(), lineSegment))
		{
			cellsAlongLength_ = currentSiteIndex + 1;
			cellsAlongWidth_ = sites.size() / cellsAlongLength_;
		}
	}
}

std::shared_ptr<Cell> DegenerateHexaDiagramGenerationAlgorithm::createCell(int index)
{
	if (index == 0) // left-bottom
	{
		std::shared_ptr<Vertex> leftBottomVertex = leftBorder_->getVertices().first;
		std::shared_ptr<Vertex> leftTopVertex = std::make_shared<Vertex>(Math::straightsIntersection(
			std::make_pair(leftBorder_->getStartVertex().coord(), leftBorder_->getEndVertex().coord()),
			createDevidingStraight(cells_[index], cells_[index + cellsAlongLength_])));
		std::shared_ptr<Vertex> rightTopVertex = std::make_shared<Vertex>(Math::straightsIntersection(
			createDevidingStraight(cells_[index], cells_[index + cellsAlongLength_]),
			createDevidingStraight(cells_[index], cells_[index + 1])));
		std::shared_ptr<Vertex> rightBottomVertex = std::make_shared<Vertex>(Math::straightsIntersection(
			createDevidingStraight(cells_[index], cells_[index + 1]),
			std::make_pair(bottomBorder_->getStartVertex().coord(), bottomBorder_->getEndVertex().coord())));

		std::shared_ptr<Edge> leftEdge = std::make_shared<Edge>(leftBottomVertex, leftTopVertex);
		std::shared_ptr<Edge> topEdge = std::make_shared<Edge>(leftTopVertex, rightTopVertex);
		std::shared_ptr<Edge> rightEdge = std::make_shared<Edge>(rightTopVertex, rightBottomVertex);
		std::shared_ptr<Edge> bottomEdge = std::make_shared<Edge>(rightBottomVertex, leftBottomVertex);

		leftEdge->addCells(std::make_pair(nullptr, cells_[index]));
		topEdge->addCells(std::make_pair(cells_[index], cells_[index + cellsAlongLength_]));
		rightEdge->addCells(std::make_pair(cells_[index], cells_[index + 1]));
		bottomEdge->addCells(std::make_pair(nullptr, cells_[index]));

		cells_[index]->addEdge(leftEdge);
		cells_[index]->addEdge(topEdge);
		cells_[index]->addEdge(rightEdge);
		cells_[index]->addEdge(bottomEdge);

		cells_[index + 1]->addEdge(rightEdge);

		cells_[index + cellsAlongLength_]->addEdge(bottomEdge);
	}
	else if (index == cellsAlongLength_ - 1) // right-bottom
	{

	}
	else if (index == cells_.size() - cellsAlongWidth_) // left-top
	{

	}
	else if (index == cells_.size() - 1) // right-top
	{

	}
	else if ((cells_.size() / cellsAlongWidth_) == 0) // left
	{

	}
	else if ((cells_.size() / cellsAlongWidth_ + cellsAlongLength_) == cellsAlongLength_) // right
	{

	}
	else if (index < cellsAlongLength_) // bottom
	{
		// ?? need complete this section first of all
		// after this 'if' it is possible to continue work on other ifs
	}
	else if (index >= cells_.size() - cellsAlongWidth_) // top
	{

	}
	else // inside cells
	{

	}

	return cells_[0];
}

std::pair<Vector2D, Vector2D> DegenerateHexaDiagramGenerationAlgorithm::createDevidingStraight(std::shared_ptr<Cell> first, std::shared_ptr<Cell> second)
{
	Vector2D direction = (first->site().coord() - second->site().coord()).getNorm();
	Vector2D center = (first->site().coord() - second->site().coord()) / 2.0;
	Vector2D edgeDirection = Vector2D(-direction.y(), direction.x());
	edgeDirection.normalize();
	return std::make_pair(center + edgeDirection, center - edgeDirection);
}