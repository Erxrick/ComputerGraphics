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
	//

	GLuint texture;
	glGenTextures(1, &texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	////tex2
	//glActiveTexture(GL_TEXTURE1);
	//GLuint textureID2;
	//glGenTextures(1, &textureID2);

	//glBindTexture(GL_TEXTURE_2D, textureID2);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image2);
	//glGenerateMipmap(GL_TEXTURE_2D);
	//m_shader.SetUniform("texture2", texID2);

	//glUniform1i(texID, 0);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

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

