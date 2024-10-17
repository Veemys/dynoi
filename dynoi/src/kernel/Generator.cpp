#include "Generator.h"

#include "VoronoiDiagram.h"
#include "GenerationAlgorithm.h"
#include "Boundary.h"

Generator::Generator(std::shared_ptr<GenerationAlgorithm> algorithm)
	: algorithm_(algorithm)
{

}

std::shared_ptr<VoronoiDiagram> Generator::execute(std::vector<Site>& sites, Boundary& boundary)
{
	return algorithm_->apply(sites, boundary);
}