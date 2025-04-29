#include "TGA.hpp"

#include <fstream>
#include <ios>

void TGA::Save(const std::string& path, const std::vector<unsigned int>& data, 
	const unsigned short width, const unsigned short height)
{
	const std::vector<unsigned short> header = { 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, width, height, 0x0820 };

	std::fstream file(path, std::ios::out | std::ios::binary);

	file.write(reinterpret_cast<const char*>(header.data()), header.size() * sizeof(unsigned short));
	file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(unsigned int));
	file.close();
}

bool TGA::Load(const std::string& path, std::vector<unsigned int>& data, unsigned short& width, unsigned short& height)
{
    // Open the file
    std::ifstream file(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        return false;
    }

    // Read the header
    std::vector<unsigned short> header(9);
    file.read(reinterpret_cast<char*>(header.data()), header.size() * sizeof(unsigned short));

    // Check if we could read the expected header size
    if (file.fail())
    {
        file.close();
        return false;
    }

    // Extract width and height from the header
    width = header[6];
    height = header[7];

    // Resize the data vector to fit the image
    data.resize(width * height);

    // Read the image data
    file.read(reinterpret_cast<char*>(data.data()), data.size() * sizeof(unsigned int));

    // Check if we read all the expected data
    bool success = !file.fail();

    file.close();
    return success;
}
