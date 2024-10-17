#pragma once

#include <fstream>

#include "Writer.h";

class FileWriter : public Writer
{
private:
	std::ofstream ofstream_;

public:
	FileWriter(const std::string& fileName);

	~FileWriter();

	void write(const std::string& str) override final;

};