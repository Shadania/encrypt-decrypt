#include "pch.h"
#include <iostream>
#include <fstream>
#include "KeygenFunction.h"


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "This program needs 1 argument to execute! Please provide one argument (the desired file name).";
		return 1;
	}

	std::string fileName{ argv[1] };
	std::ofstream file{ fileName };

	if (!file.is_open())
	{
		std::cout << "Could not create file!";
		return 1;
	}


	GenerateKeyInFile(file);


	file.close();

	std::cout << "Key file generated.";
	return 0;
}