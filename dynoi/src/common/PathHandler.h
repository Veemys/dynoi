#pragma once

#include <string>

class PathHandler
{
public:
	static bool hasParentPath(const std::string& path);
	static std::string parentPathAsString(const std::string& path);

};