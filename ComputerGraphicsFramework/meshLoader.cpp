#include "stdafx.h"
#include "meshLoader.h"


namespace MeshLoader {

	bool loadMesh()
	{
	/*	std::string content;
		std::ifstream fileStream(filename, std::ios::in);
		int size;
		int offSet;
		char  header[54];

		if (!fileStream.is_open())
		{
			std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
			return nullptr;
		}






		if (line.subtr(0, 2) == "f ")
		{
			std::istringstream s(line.subtr(2));
			std::string pointString;
			while (std::getline(s, pointString, ' '))
			{
				size_t i = 0;
				unsigned int indices[3];
				std::istringstream pointStream(pointstring);
				std::string valueString;
				while (std::getline(pointStream, valueString, '/')) 
				{
					std::istringstream valuesStream(valueString);
					valueSream >> indices[i++];
				}
				glm::vec3 vertex = verticesTemp[indices[0] - 1];
				vertices.push_back(vertex);

				glm::vec2 uv = 

			}
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
		return false;*/
	}
}
