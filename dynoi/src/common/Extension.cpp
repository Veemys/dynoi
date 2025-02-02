#include "Extension.h"

std::string getExtensionString(Extension ex)
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
		return ".log";
	default:
		return "";
	}
}