#pragma once
#include "glm\vec3.hpp"
class Material
{
public:
	Material();
	~Material();

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;


	struct TextureInfo
	{
		GLuint activeTexture;
		GLuint texture;
	};

	std::vector<TextureInfo> m_textures;
};

