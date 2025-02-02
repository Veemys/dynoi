#pragma once

#include <memory>
#include <string>

class Cell;
class VoronoiDiagram;

class DebugOutput
{
public:
	static void outputCellDataToConsole(int& cellsNumber, std::shared_ptr<Cell> cell);
	static void outputCellsDataToConsole(std::shared_ptr<VoronoiDiagram> vd);

	static void outputCellsCentersToTecplot(const std::string& path, std::shared_ptr<VoronoiDiagram> vd);
	static void outputEdgesToTecplot(const std::string& path, std::shared_ptr<VoronoiDiagram> vd);

};