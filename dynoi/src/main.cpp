#include <iostream>
#include <memory>

#include "kernel/Vector2D.h"
#include "kernel/Site.h"
#include "kernel/Edge.h"
#include "kernel/Cell.h"
#include "kernel/Generator.h"
#include "kernel/Boundary.h"
#include "kernel/VoronoiDiagram.h"
#include "generators/IncrementalGenerationAlgorithm.h"
#include "inout/Writer.h"
#include "inout/SimpleWriter.h"
#include "inout/FileReader.h"
#include "common/Extension.h"

// ?? todo:
// 1) create class that will be incapsulate adding and deleting elements to the diagram.
//    this class also will be provide convenient interface for these purposes

static double random(double min, double max)
{
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

static std::vector<Site> generateRandomSites(int sitesNumber, double xMin, double xMax, double yMin, double yMax)
{
	std::vector<Site> sites;
	for (int i = 0; i < sitesNumber; ++i)
	{
		double x = random(xMin, xMax);
		double y = random(yMin, yMax);
		sites.push_back(Site(x, y));
	}

	return sites;
}

template<class Container>
void processPointsFromFile(const std::string& points, Container& cont)
{
	std::string currentString("");
	Vector2D currentPoint = Vector2D();
	for (int i = 0; i < points.size(); ++i)
	{
		if (points[i] == ' ')
		{
			currentPoint.x() = std::stod(currentString);
			currentString = "";
		}
		else if (points[i] == '\n')
		{
			currentPoint.y() = std::stod(currentString);
			cont.push_back(currentPoint);
			currentString = "";
			currentPoint = Vector2D();
		}
		else
		{
			currentString.push_back(points[i]);
		}
	}
}

static void readBoundary(const std::string& projectPath, std::list<Vector2D>& boundaryPoints)
{
	FileReader reader(projectPath + GetExtensionString(Extension::Boundary));
	const std::string& pointsFromFile = reader.read();
	
	processPointsFromFile(pointsFromFile, boundaryPoints);
}

static void readSites(const std::string& projectPath, std::vector<Site>& sites)
{
	FileReader reader(projectPath + GetExtensionString(Extension::Sites));
	const std::string& sitesFromFile = reader.read();
	
	processPointsFromFile(sitesFromFile, sites);
}

int main(int argc, const char** argv)
{
	std::string projectPath(argv[1]);

	std::shared_ptr<VoronoiDiagram> vd = nullptr;

	try
	{
		std::list<Vector2D> boundaryPoints = std::list<Vector2D>();
		readBoundary(projectPath, boundaryPoints);
		Boundary boundary = Boundary(boundaryPoints);

		std::vector<Site> sites;
		readSites(projectPath, sites);

		// srand((unsigned int)time(0));
		// sites = generateRandomSites(7, 0.1, 9.9, 0.1, 9.9);

		Generator generator(std::make_shared<IncrementalGenerationAlgorithm>());

		vd = generator.execute(sites, boundary);
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	// output section for test (should be deleted in the future)
	int num = 0;
	for (auto& cell : vd->cells())
	{
		std::cout << "\nCell number = " << num++ << "\n";
		std::cout << "Site = " << cell->site().coord().x() << " " << cell->site().coord().y() << "\n";
		std::cout << "Number of edges = " << cell->edges().size() << "\n";
		for (auto& edge : cell->edges())
		{
			std::cout << "\t" << edge->center().x() << " " << edge->center().y() << "\n";
		}
	}
	// end output section

	std::string fileName = "";
	std::shared_ptr<Writer> writer = std::make_shared<SimpleWriter>(fileName, vd);
	writer->write("");

	return 0;
}

/*START WORK CORRECTLY SECTION

5.0 6.0
5.0 8.0
5.0 4.0
7.0 9.5

1.0 9.0
3.0 7.0
2.0 2.0

|-----------MAIN BENCHMARK TEST CASE FOR NOW-----------|
3.0 7.0
2.0 2.0
1.0 9.0
8.0 5.0
5.0 0.5
4.69 8.135
5.0 5.0

3.0 7.0
8.0 4.0
2.0 2.0
5.0 5.0

5.0 5.0
2.0 2.0
8.0 2.0
2.0 8.0
8.0 8.0

8.81298 4.52867
3.96078 2.53081
6.40519 5.4767
3.159 6.77215
8.41722 6.51042
5.70278 8.03269
7.83175 7.10175

4.0 6.0
6.0 4.0

END WORK CORRECTLY SECTION



START PROBLEM SECTION

|-----------Problem case #1-----------|
2.0 2.0
8.0 2.0
2.0 8.0
8.0 8.0
5.0 5.0

START PROBLEM SECTION*/