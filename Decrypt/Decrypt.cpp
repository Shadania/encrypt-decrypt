#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "DecryptFunction.h"



int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		std::cout << "To execute, this program needs 3 arguments: inputfile, password file, outputfile\n";
		return 1;
	}

	std::string fileName{ argv[1] };
	std::ifstream inputFile{ fileName };
	if (!inputFile.is_open())
	{
		std::cout << "Did not manage to open input file\n";
		return 1;
	}
	fileName = argv[2];
	std::ifstream passwordFile{ fileName };
	if (!passwordFile.is_open())
	{
		std::cout << "Did not manage to open password file\n";
		return 1;
	}
	fileName = argv[3];
	std::ofstream outputFile{ fileName };
	if (!outputFile.is_open())
	{
		std::cout << "Did not manage to open output file\n";
		return 1;
	}

	DecryptFile(inputFile, passwordFile, outputFile);

	inputFile.close();
	passwordFile.close();
	outputFile.close();

	std::cout << "File decrypted.";

	return 0;
}

