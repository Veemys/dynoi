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

std::string GetExtensionString(Extension ex)
{
	switch (ex)
	{
	case Extension::Boundary:
		return ".bnd";
	case Extension::Sites:
		return ".sts";
	case Extension::Tecplot:
		return ".plt";
	case Extension::Text:
		return ".txt";
	case Extension::Log:
		return ".txt";
	default:
		return "";
	}
}