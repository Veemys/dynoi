#pragma once

#include <memory>
#include <vector>

class VoronoiDiagram;
class GenerationAlgorithm;
class Site;
class Boundary;

class Generator
{
private:
	std::shared_ptr<GenerationAlgorithm> algorithm_;

public:
	Generator(std::shared_ptr<GenerationAlgorithm> algorithm);

	~Generator() {}

	std::shared_ptr<VoronoiDiagram> execute(std::vector<Site>& sites, Boundary& boundary);

};