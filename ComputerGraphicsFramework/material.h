#pragma once
#include "glm\vec3.hpp"


class Material
{
public:
	Material();
	~Material();

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;


	struct TextureInfo
	{
		GLenum type;
		GLuint activeTexture;
		GLuint texture;
	};

	std::vector<TextureInfo> m_textures;


	void SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
	bool LoadTexture2D(const std::string& filename, GLuint activeTexture);
	bool LoadTextureCube(const std::string& basename, const std::vector<std::string>& suffixes, const std::string& type, GLuint activeTexture);
	void SetTextures();


	static GLuint CreateTexture(GLuint width, GLuint height);
	static GLuint CreateDepthTexture(GLuint width, GLuint height);
	static GLuint CreateDepthBuffer(GLuint texture, GLuint width, GLuint height);

	void AddTexture(GLuint texture, GLuint activeTexture);

};

