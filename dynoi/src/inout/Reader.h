#pragma once

#include <string>

class Reader abstract
{
public:
	virtual const std::string& read() = 0;

};