#include "FileWriter.h"

#include <format>

#include "Writer.h"

FileWriter::FileWriter(const std::string& fileName)
	: ofstream_(fileName)
{
	if (!ofstream_.is_open())
	{
		throw std::exception(std::format("File {} did not open.", fileName).c_str());
	}
}

FileWriter::~FileWriter()
{
	ofstream_.close();
}

void FileWriter::write(const std::string& str)
{
	ofstream_ << str;
}