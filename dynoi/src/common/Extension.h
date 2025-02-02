#pragma once

#include <string>

enum class Extension
{
	Boundary,
	Sites,
	Tecplot,
	Text,
	Log
};

std::string getExtensionString(Extension ex);