#pragma once
#include <fstream>

void GenerateKeyInFile(std::ofstream& file)
{
	for (size_t i{}; i < 16; ++i)
	{
		unsigned char randByte = rand();
		file << randByte;
	}
}