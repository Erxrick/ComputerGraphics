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


	TextureInfo textureInfo = { GL_TEXTURE_2D, activeTexture, texture };
	m_textures.push_back(textureInfo);

	delete image;

	return false;
}

void Material::SetTextures()
{
	for (TextureInfo textureInfo : m_textures)
	{
		glActiveTexture(textureInfo.activeTexture);
		glBindTexture(textureInfo.type, textureInfo.texture);
	}
}

bool Material::LoadTextureCube(const std::string& basename, const std::vector<std::string>& suffixes, const std::string& type, GLuint activeTexture)
{
	GLuint targets[] =
	{
		GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	for (int i = 0; i < 6; i++)
	{
		int width;
		int height;
		int n;
		std::string filename = basename + suffixes[i] + "." + type;
		unsigned char* image = stbi_load(filename.c_str(), &width, &height, &n, 0);
		assert(image);

	//	GLenum storageFormat = (n == 4) ? GL_RGBA8 : GL_RGB8;
		GLenum imageFormat = (n == 4) ? GL_RGBA : GL_RGB;


		glTexImage2D(targets[i], 0, imageFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, image);
		delete image;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	TextureInfo textureInfo = { GL_TEXTURE_CUBE_MAP, activeTexture, texture };
	m_textures.push_back(textureInfo);




	return true;

}

GLuint Material::CreateTexture(GLuint width, GLuint height)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return texture;

}

GLuint Material::CreateDepthTexture(GLuint width, GLuint height)
{
	GLuint depthTexture;

	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	return depthTexture;
}

GLuint Material::CreateDepthBuffer(GLuint texture, GLuint width, GLuint height)
{
	GLuint fboHandle;

	glGenFramebuffers(1, &fboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

	glDrawBuffer(GL_NONE);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(result == GL_FRAMEBUFFER_COMPLETE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return fboHandle;

}

void Material::AddTexture(GLuint texture, GLuint activeTexture)
{
	TextureInfo textureInfo = { GL_TEXTURE_2D, activeTexture, texture };
	m_textures.push_back(textureInfo);
}

