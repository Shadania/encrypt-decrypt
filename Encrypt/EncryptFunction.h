#pragma once
#include <fstream>
#include <deque>
#include <string>
#include "xxtea.h"



void EncryptFile(std::ifstream& toEncrypt, std::ifstream& key, std::ofstream& outputFile)
{
	toEncrypt.seekg(0);
	key.seekg(0);

	union FourBytes
	{
		uint32_t uint;
		char chars[4];
	};

	// Get input
	std::deque<char> bytes(
		(std::istreambuf_iterator<char>(toEncrypt)),
		(std::istreambuf_iterator<char>()));

	// Push to the front of bytes the amount of padded bytes excluding this one & pad
	unsigned char amtPaddedBytes{};
	bytes.push_front({});
	while ((bytes.size() % 4) != 0)
	{
		bytes.push_back(rand());
		amtPaddedBytes++;
	}
	bytes.front() = amtPaddedBytes;

	

	const int size{ (int)bytes.size() / 4 };

	// Ready input for encryption
	FourBytes* toEncryptArr{ new FourBytes[size]{} };
	for (size_t i{}; i < (size_t)size; ++i)
	{
		for (size_t j{}; j < 4; j++)
		{
			toEncryptArr[i].chars[j] = bytes[4 * i + j];
		}
	}

	// Get key
	uint32_t keyArr[4]{};
	bytes.clear();
	bytes = std::deque<char>(
		(std::istreambuf_iterator<char>(key)),
		(std::istreambuf_iterator<char>()));

	// Translate bytes to actual ints
	for (size_t i{}; i < 4; ++i)
	{
		FourBytes newByte{};
		for (size_t j{}; j < 4; ++j)
		{
			newByte.chars[j] = bytes[4 * i + j];
		}
		keyArr[i] = newByte.uint;
	}

	// Encrypt
	btea((uint32_t*)toEncryptArr, size, keyArr);

	// Write output
	for (size_t i{}; i < (size_t)size; ++i)
	{
		for (size_t j{}; j < 4; ++j)
		{
			outputFile << toEncryptArr[i].chars[j];
		}
	}
}