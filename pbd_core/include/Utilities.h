#ifndef SPAG_UTILITIES_H
#define SPAG_UTILITIES_H

#include "Common.h"

namespace spag{

std::string readFile(std::string_view filePath){
	std::ifstream fileStream(filePath.c_str());
	std::string contents(std::istreambuf_iterator<char>(t),
		std::istreambuf_iterator<char>());
	return string;
}

} /* namespace spag */

#endif /* SPAG_UTILITIES_H */