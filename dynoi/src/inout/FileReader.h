#pragma once

#include <iostream>
#include <fstream>
#include <format>
#include <sstream>

#include "Reader.h"

class FileReader : public Reader
{
private:
	std::ifstream ifstream_;
	std::string fileContent_;

public:
	FileReader(const std::string& fileName);

	~FileReader();

	const std::string& read() override final;

};