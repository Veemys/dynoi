#pragma once

#include <string>

class Writer abstract
{
public:
	virtual void write(const std::string& str) = 0;

};