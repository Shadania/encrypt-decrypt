#pragma once
#include <fstream>
#include <vector>
#include "../Encrypt/xxtea.h"


void DecryptFile(std::ifstream& toDecrypt, std::ifstream& key, std::ofstream& outputFile)
{
	toDecrypt.seekg(0);
	key.seekg(0);

	union FourBytes
	{
		uint32_t uint;
		char chars[4];
	};

	// Get input
	std::vector<char> bytes(
		(std::istreambuf_iterator<char>(toDecrypt)),
		(std::istreambuf_iterator<char>()));

	const int size{ (int)bytes.size() / 4 };

	// Ready input for decryption
	FourBytes* toDecryptArray{ new FourBytes[size]{} };
	for (size_t i{}; i < (size_t)size; ++i)
	{
		for (size_t j{}; j < 4; j++)
		{
			toDecryptArray[i].chars[j] = bytes[4 * i + j];
		}
	}

	// Get key
	uint32_t keyArr[4]{};
	bytes.clear();
	bytes = std::vector<char>(
		(std::istreambuf_iterator<char>(key)),
		(std::istreambuf_iterator<char>()));

	for (size_t i{}; i < 4; ++i)
	{
		FourBytes newByte{};
		for (size_t j{}; j < 4; ++j)
		{
			newByte.chars[j] = bytes[4 * i + j];
		}
		keyArr[i] = newByte.uint;
	}


	// Decrypt
	btea((uint32_t*)toDecryptArray, -size, keyArr);

	// Get amount of padded bytes
	size_t paddedBytes{ (size_t)(toDecryptArray[0].chars[0]) };

	// Write output
	for (size_t i{ 1 }; i < ((size_t)size*4 - paddedBytes); ++i)
	{
		outputFile << (toDecryptArray[i/4].chars[i%4]);
	}
}