#pragma once
#include "object.h"
#include "scene.h"
#include "renderable.h"
#include "mesh.h"
#include "shader.h"


class Light :
	public Renderable
{
public:
	Light(const std::string& name, Scene* scene);
	~Light();

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	void Update();
	void Render();

public:
	Shader m_shader;
	Mesh m_mesh;

};

