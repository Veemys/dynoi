#pragma once

#include <memory>

#include "../kernel/GenerationAlgorithm.h"

class Site;
class VoronoiDiagram;
class Boundary;

class NaiveGenerationAlgorithm : public GenerationAlgorithm
{
private:


public:
	virtual ~NaiveGenerationAlgorithm() {}

	std::shared_ptr<VoronoiDiagram> apply(std::vector<Site>& sites, Boundary& boundary) override final;

};