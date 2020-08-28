#pragma once

#include <string>
#include <iostream>
#include <ctime>

namespace Codec {

	void SaveStringToFile( std::ostream &os, const std::string & str_in );
	std::string LoadStringFromFile( std::istream &is);

} // namespace Codec

void SaveStringToTextFile(std::ostream &os, const std::string &str);
std::string IntToString(size_t n, size_t field_size = 0);
