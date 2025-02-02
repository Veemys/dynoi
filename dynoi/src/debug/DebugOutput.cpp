#include "DebugOutput.h"

#include <iostream>
#include <format>
#include <fstream>
#include <filesystem>

#include "../kernel/Cell.h"
#include "../kernel/Edge.h"
#include "../kernel/VoronoiDiagram.h"
#include "../common/Extension.h"

void DebugOutput::outputCellsDataToConsole(std::shared_ptr<VoronoiDiagram> vd)
{
	int num = 0;
	for (auto& cell : vd->cells())
	{
		DebugOutput::outputCellDataToConsole(num, cell);
	}
}

void DebugOutput::outputCellDataToConsole(int& cellsNumber, std::shared_ptr<Cell> cell)
{
	std::cout << std::format("\nCell number = {}\n", cellsNumber++);
	std::cout << std::format("Site = {} {}\n", cell->site().coord().x(), cell->site().coord().y());
	std::cout << std::format("Number of edges = {}\n", cell->edges().size());
	for (auto& edge : cell->edges())
	{
		std::cout << std::format("\t{} {}\n", edge->center().x(), edge->center().y());
	}
}

void DebugOutput::outputCellsCentersToTecplot(const std::string& path, std::shared_ptr<VoronoiDiagram> vd)
{
	std::filesystem::create_directories(path);
	std::ofstream centersOfstream(std::format("{}\\cell_centers{}", path, getExtensionString(Extension::Tecplot)));
	centersOfstream << "variables = \"x\", \"y\"\n";
	for (auto& cell : vd->cells())
	{
		centersOfstream << std::format("{}\t{}\n", cell->site().x(), cell->site().y());
	}
}

void DebugOutput::outputEdgesToTecplot(const std::string& path, std::shared_ptr<VoronoiDiagram> vd)
{
	const std::string edgesPath = std::format("{}\\edges", path);
	
	if (std::filesystem::exists(edgesPath))
	{
		std::filesystem::remove_all(edgesPath);
	}

	std::filesystem::create_directories(edgesPath);
	std::set<std::shared_ptr<Edge>> alreadyAddedEsges;
	int edgeIndex = 0;
	for (auto& cell : vd->cells())
	{
		for (auto& edge : cell->edges())
		{
			if (alreadyAddedEsges.contains(edge))
				continue;

			std::ofstream edgeOfsream(std::format("{}\\edge_{}{}", edgesPath, edgeIndex, getExtensionString(Extension::Tecplot)));
			edgeOfsream << "variables = \"x\", \"y\"\n";
			edgeOfsream << std::format("{}\t{}\n{}\t{}", edge->start().x(), edge->start().y(), edge->end().x(), edge->end().y());
			++edgeIndex;
			alreadyAddedEsges.insert(edge);
		}
	}
}