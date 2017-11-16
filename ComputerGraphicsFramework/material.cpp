#include "stdafx.h"
#include "material.h"



#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>




Material::Material()
{
}


Material::~Material()
{
}

void Material::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_shininess = shininess;
}

bool Material::LoadTexture2D(const std::string & filename, GLuint activeTexture)
{
	int width;
	int height;
	int n;
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &n, 0);

	GLenum storageFormat = (n == 4) ? GL_RGBA8 : GL_RGB8;
	GLenum imageFormat = (n == 4) ? GL_RGBA : GL_RGB;

	GLuint texture;
	glActiveTexture(activeTexture);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, storageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);


	TextureInfo textureInfo = { activeTexture, texture };
	m_textures.push_back(textureInfo);

	delete image;

	return false;
}

void Material::SetTextures()
{
	for (TextureInfo textureInfo : m_textures)
	{
		glActiveTexture(textureInfo.activeTexture);
		glBindTexture(GL_TEXTURE_2D, textureInfo.texture);
	}
}

