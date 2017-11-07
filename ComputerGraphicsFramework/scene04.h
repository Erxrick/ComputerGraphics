#pragma once
#include "scene.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "material.h"


class Scene04 :
	public Scene
{
public:
	Scene04(Engine* engine) : Scene(engine) {};
	~Scene04();

	bool Initialize();
	void Render();
	void Update();
	void Shutdown();

	GLuint m_program;
	GLuint vboHandle;
	GLuint vaoHandle;

	glm::vec3 m_ambientMaterial;

private:
	struct object
	{
		// id / handles
		GLuint shaderProgram;
		GLuint vaoHandle;

		// transforms
		GLint mxModelViewUniform;
		GLint mxMVPUniform;
		GLint mxNormalUniform;

		// material
		GLint ambientMaterialUniform;
		GLint diffuseMaterialUniform;
		GLint specularMaterialUniform;
	};

	struct light
	{
		GLint positionUniform;
		GLint colorUniform;
	};

	object m_cube;
	light m_light;
	Shader m_shader;

	float m_rotation;
	glm::mat4 m_translate;
	glm::mat4 m_rotate;
	glm::mat4 m_mxModel;
	glm::mat4 m_mxView;
	glm::mat4 m_mxProjection;
	glm::mat4 m_mxModelView;
	glm::mat4 m_MVP;
	glm::mat3 m_mxNormal;

	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;
	glm::vec3 m_diffuseMaterial;
	glm::vec3 m_specularMaterial;

	Material m_material;



};

