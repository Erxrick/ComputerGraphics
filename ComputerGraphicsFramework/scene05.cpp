#include "stdafx.h"
#include "scene05.h"
#include "timer.h"
#include "image.h"
#include "light.h"
#include "input.h"
#include "meshLoader.h"

#define PHONG
#define SPECULAR

using namespace MeshLoader;

namespace scene05
{
	float vertexData[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

	};

	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};

}



Scene05::~Scene05()
{
}

bool Scene05::Initialize()
{

	m_engine->Get<Input>()->AddButton("quit", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);


#ifdef SPECULAR
	m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
	m_shader.CompileShader("Resources\\Shaders\\texture_phong_fog.frag", GL_FRAGMENT_SHADER);
	m_shader.Link();
	m_shader.Use();
	//	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\phong.vert", "Resources\\Shaders\\phong.frag");
	//#endif
	//#ifdef PHONG 
	//	m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
	//	m_shader.CompileShader("Resources\\Shaders\\texture_phong.frag", GL_FRAGMENT_SHADER);
	//	m_shader.Link();
	//	m_shader.Use();
#else // 
	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\light.vert", "Resources\\Shaders\\basic.frag");
#endif
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

//	mesh.Load("Resources\\Meshes\\cube.obj");
//	mesh.Use();

	bool success = LoadMesh("Resources\\Meshes\\cube.obj", vertices, normals, uvs);
	m_numVertices = vertices.size();


	//----------------------------------------------------------- semi working

	GLuint vboHandle[3];
	glGenBuffers(3, vboHandle);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandle[2]);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);

	//---------------------------------------------------------------------
	 //deadweight
//	glGenBuffers(1, &vboHandle);
//	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(scene05::vertexData), scene05::vertexData, GL_STATIC_DRAW);

	//	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[scene03::COLOR]);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(scene03::colorData), scene03::colorData, GL_STATIC_DRAW);


	//-------------------------------------------------------------------

	//GLuint vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexBuffer(0, vboHandle[0], 0, sizeof(glm::vec3));
	glBindVertexBuffer(1, vboHandle[1], 0, sizeof(glm::vec3));
	glBindVertexBuffer(2, vboHandle[2], 0, sizeof(glm::vec2));


	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(2, 2);
	//-------------------------------------------------------------------------------------------------------------------

	m_material.SetMaterial(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(.5f, .5f, .5f), glm::vec3(1.0f, 1.0f, 1.0f), 10.0f);
	m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	///	m_shader.SetUniform("texture1", m_material.m_textures.at(0).texture);
	//	m_material.LoadTexture2D("Resources\\Textures\\rick.jpeg", GL_TEXTURE1);
	//	m_shader.SetUniform("texture2", m_material.m_textures.at(1).texture);


	//	m_material.SetTextures();


	Camera* camera = new Camera("camera", this);
	camera->Initialize(glm::vec3(10.0f, 10.0f, -5.0f), glm::vec3(0.0f));
	AddObject(camera);


	Light* light = new Light("light", this);
	light->m_ambient = glm::vec3(0.1f);
	light->m_diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	light->m_specular = glm::vec3(1.0f);
	light->m_transform.position = glm::vec3(5.0f, 10.0f, 10.0f);

	AddObject(light);
	m_shader.PrintActiveUniforms();

	return true;
}

void Scene05::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//// render code
	//mesh.Use();
	//mesh.Render();
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, m_numVertices);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene05::Update()
{
	if (m_engine->Get<Input>()->GetButton("quit") == Input::eButtonState::DOWN) glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);

	

	Light* light = GetObject<Light>("light");

	Camera* camera = GetObject<Camera>("camera");

	auto objects = GetObjects<Object>();
	for each (Object* object in m_objects)
	{
		object->Update();
	}


	//glm::vec3 lightPosition = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);

	m_shader.SetUniform("light.position", light->m_transform.position);
	m_shader.SetUniform("light.ambient", light->m_ambient);
	m_shader.SetUniform("light.diffuse", light->m_diffuse);
	m_shader.SetUniform("light.specular", light->m_specular);


	m_rotation = m_rotation + m_engine->Get<Timer>()->FrameTime();
	m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	m_mxModel = m_translate * m_rotate;

	//m_mxProjection = glm::perspective(90.0f, ((float)m_engine->Get<Renderer>()->m_width / (float)m_engine->Get<Renderer>()->m_height), 0.001f, 100.0f);


	m_mxModelView = camera->GetView() * m_mxModel;


	m_shader.SetUniform("mxModelView", m_mxModelView);


	m_MVP = camera->GetProjection() * camera->GetView() * m_mxModel;
	m_shader.SetUniform("mxMVP", m_MVP);



	m_mxNormal = glm::mat3(m_mxModelView);
	m_mxNormal = glm::inverse(m_mxNormal);
	m_mxNormal = glm::transpose(m_mxNormal);
	m_shader.SetUniform("mxNormal", m_mxNormal);


	m_shader.SetUniform("material.ambient", m_material.m_ambient);
	m_shader.SetUniform("material.diffuse", m_material.m_diffuse);
	m_shader.SetUniform("material.specular", m_material.m_specular);
	m_shader.SetUniform("material.shininess", m_material.m_shininess);
}

void Scene05::Shutdown()
{
}
