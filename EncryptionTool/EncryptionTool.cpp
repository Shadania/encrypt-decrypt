#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include "../Encrypt/EncryptFunction.h"
#include "../Decrypt/DecryptFunction.h"
#include "../KeyGen/KeygenFunction.h"


int main()
{
	std::cout << "You can enter <end> to stop the program at any time.\n";
	while (true)
	{
		// Start user interaction loop
		std::cout << "Please select a mode: encrypt - decrypt - keygen: ";
		std::string userChoice{};
		std::cin >> userChoice;

		enum class mode
		{
			encrypt,
			decrypt,
			keygen
		};
		mode currMode{};

		// Figure out what the user wants
		if (userChoice == "encrypt")
			currMode = mode::encrypt;
		else if (userChoice == "decrypt")
			currMode = mode::decrypt;
		else if (userChoice == "keygen")
			currMode = mode::keygen;
		else if (userChoice == "end")
		{
			std::cout << "Ending program...\n";
			return 0;
		}
		else
		{
			std::cout << "That was not a valid command!\n";
			continue;
		}

		// Generate a key
		if (currMode == mode::keygen)
		{
			std::cout << "Name of output file? ";
			std::string keyFile{};
			std::cin >> keyFile;
			if (keyFile == "end")
			{
				std::cout << "Ending program...\n";
				return 0;
			}

			std::ofstream key;
			key.open(keyFile, std::ios::out | std::ios::binary);
			if (!key.is_open())
			{
				std::cout << "Could not open the file correctly!\n";
				continue;
			}

			GenerateKeyInFile(key);

			std::cout << "Generated key.\n";
			continue;
		}

		// Encrypt and decrypt are kinda similar
		else
		{
			std::string inputFile, keyFile, outputFile;
			std::cout << "Name of inputfile? ";
			std::cin >> inputFile;
			if (inputFile == "end")
			{
				std::cout << "Ending program...\n";
				return 0;
			}
			std::cout << "Name of keyfile? ";
			std::cin >> keyFile;
			if (keyFile == "end")
			{
				std::cout << "Ending program...\n";
				return 0;
			}
			std::cout << "Name of outputfile? ";
			std::cin >> outputFile;
			if (outputFile == "end")
			{
				std::cout << "Ending program...\n";
				return 0;
			}

			std::ifstream input, key;
			std::ofstream output;
			input.open(inputFile, std::ios::binary | std::ios::in);
			key.open(keyFile, std::ios::binary | std::ios::out);
			output.open(outputFile, std::ios::binary | std::ios::out);

			if (!(input.is_open() && key.is_open() && output.is_open()))
			{
				std::cout << "Could not open all files correctly!\n";
				continue;
			}

			if (currMode == mode::decrypt)
				DecryptFile(input, key, output);
			else
				EncryptFile(input, key, output);

			std::cout << "Successfully " << userChoice << "ed file.\n";
			continue;
		}
	}

	return 1;
}