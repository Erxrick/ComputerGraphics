#pragma once
#include "renderable.h"
#include "shader.h"
#include "material.h"
#include "mesh.h"

class Model :
	public Renderable
{
public:
	Model(const std::string& name, Scene* scene) : Renderable(name, scene) {};
	~Model();

	Material m_material;
	Shader m_shader;
	Mesh m_mesh;

	std::string m_cameraID;

	void Update();
	void Render();

};

