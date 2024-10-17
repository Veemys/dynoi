#include "SimpleWriter.h"

#include <unordered_set>

#include "../kernel/Edge.h"
#include "../kernel/Cell.h"
#include "../kernel/VoronoiDiagram.h"
#include "Writer.h"

SimpleWriter::SimpleWriter(const std::string& fileName, std::shared_ptr<VoronoiDiagram> vd)
	: ofstream_(fileName),
	vd_(vd)
{
	
}

void SimpleWriter::write(const std::string& str)
{
	std::ofstream centersOfstream("centers.plt");
	centersOfstream << "variables = \"x\", \"y\"\n";
	std::set<std::shared_ptr<Edge>> edges;
	for (auto cell : vd_->cells())
	{
		centersOfstream << cell->site().x() << "\t" << cell->site().y() << "\n";
		for (auto edge : cell->edges())
		{
			edges.insert(edge);
		}
	}

	int edgeIndex = 0;
	for (auto edge : edges)
	{
		std::ofstream edgeOfsream("edges/edge_" + std::to_string(edgeIndex) + ".plt");
		edgeOfsream << "variables = \"x\", \"y\"\n";
		edgeOfsream << edge->start().x() << "\t" << edge->start().y() << "\n" <<
			edge->end().x() << "\t" << edge->end().y();
		++edgeIndex;
	}
}