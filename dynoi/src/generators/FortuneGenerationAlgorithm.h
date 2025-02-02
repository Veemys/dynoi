#pragma once

#include <memory>

#include "../kernel/GenerationAlgorithm.h"

class Site;

class FortuneGenerationAlgorithm : public GenerationAlgorithm
{
private:


public:
	virtual ~FortuneGenerationAlgorithm() {}

	std::shared_ptr<VoronoiDiagram> apply(std::vector<Site>& sites, Boundary& boundary) override final;

};