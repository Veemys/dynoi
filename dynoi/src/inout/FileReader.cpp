#include "FileReader.h"

#include "Reader.h"

FileReader::FileReader(const std::string& fileName)
	: ifstream_(fileName),
	fileContent_("")
{
	if (!ifstream_.is_open())
	{
		throw std::exception(std::format("File {} did not open.", fileName).c_str());
	}
}

FileReader::~FileReader()
{
	ifstream_.close();
}

const std::string& FileReader::read()
{
	std::string currentLine("");
	while (std::getline(ifstream_, currentLine))
	{
		fileContent_ += currentLine + "\n";
	}

	return fileContent_;
}