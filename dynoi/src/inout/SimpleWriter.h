#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <fstream>

#include "Writer.h"

class VoronoiDiagram;

// Test class for quick writing to set of .plt files
// Should be delete in future
class SimpleWriter : public Writer
{
private:
	std::ofstream ofstream_;
	std::shared_ptr<VoronoiDiagram> vd_;

public:
	SimpleWriter(const std::string& fileName, std::shared_ptr<VoronoiDiagram> vd);

	virtual ~SimpleWriter() {}

	void write(const std::string&) override final;

};