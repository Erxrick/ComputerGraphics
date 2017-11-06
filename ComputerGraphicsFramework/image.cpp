#include "stdafx.h"
#include "image.h"

namespace Image
{
	const unsigned char * LoadBMP(const std::string & filename, int & width, int & height, int & bpp)
	{
		std::string content;
		std::ifstream fileStream(filename, std::ios::binary);
		int size;
		int offSet;
		char  header[54];

		if (!fileStream.is_open())
		{
			std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
			return nullptr;
		}


		fileStream.read(&header[0], sizeof(header));

		if ((header[0] != 'B' && header[1] != 'M'))
		{
			std::cerr << "Could not read image " << filename << ". Incorrect file type." << std::endl;
			return nullptr;
		}

		width = *(int*)&(header[0x12]);
		height = *(int*)&(header[0x16]);
		bpp = *(int*)&(header[0x1C]);
		size = *(int*)&(header[0x22]);
		offSet = *(int*)&(header[0x0A]);


		unsigned char* data = new unsigned char[size];
		fileStream.seekg(offSet);
		fileStream.read((char*)(&data[0]), size);
		
		fileStream.close();
		return data;
	}
}