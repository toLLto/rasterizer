#pragma once

#include <string>
#include <vector>

class TGA
{
public:
	static void Save(const std::string& path, const std::vector<unsigned int>& data, 
		const unsigned short width, const unsigned short height);

	static bool Load(const std::string& path, std::vector<unsigned int>& data, 
		unsigned short& width, unsigned short& height);
};

