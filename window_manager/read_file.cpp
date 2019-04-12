#include "read_file.h"

#include <fstream>
#include <iostream>


const std::string read_file(const std::string & path)
{
	std::string result;
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "Could not open file " << path << "\n";
		return new char[0];
	}

	std::string line;
	while (std::getline(file, line))
		result.append(line + '\n');

	file.close();

	return result;
}
