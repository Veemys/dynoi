#include "PathHandler.h"

#include <filesystem>

bool PathHandler::hasParentPath(const std::string& path)
{
	return std::filesystem::path(path).has_parent_path();
}

std::string PathHandler::parentPathAsString(const std::string& path)
{
	return std::filesystem::path(path).parent_path().string();
}