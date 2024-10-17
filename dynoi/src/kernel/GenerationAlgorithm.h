#pragma once

#include <memory>
#include <vector>

class VoronoiDiagram;
class Boundary;
class Site;

class GenerationAlgorithm abstract
{
public:
	GenerationAlgorithm() {}
	virtual ~GenerationAlgorithm() {}

	virtual std::shared_ptr<VoronoiDiagram> apply(std::vector<Site>& sites, Boundary& boundary) = 0;

};