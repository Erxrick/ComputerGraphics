#include "stdafx.h"
#include "scene11.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "timer.h"
#include "glm\vec4.hpp"
#include <glm\gtc\random.hpp>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>



Scene11::~Scene11()
{
}


bool Scene11::Initialize()
{

	// light
	Light* light = new Light("light", this);
	light->m_transform.position = glm::vec3(0.0f, 1.0f, 1.0f);
	light->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	AddObject(light);



	// model
	//	creates the model object and sets the transform of the model
	auto model = new Model("rocks", this);
	model->m_transform.scale = glm::vec3(1.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\normalmap_phong.vert", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("Resources\\Shaders\\normalmap_phong.frag", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	//model->m_shader.PrintActiveAttribs();
	//model->m_shader.PrintActiveUniforms();


	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 200.0f;
	model->m_material.LoadTexture2D("Resources\\Textures\\rocks.jpg", GL_TEXTURE0);
	model->m_material.LoadTexture2D("Resources\\Textures\\rocks_normal.jpg", GL_TEXTURE1);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);


	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\quad.obj");
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	//	add the model to the scene objects
	AddObject(model);



	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	//	This can be Camera::eType::EDITOR or Camera::eType::ORBIT
	//	There are two different types of camera modes
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);
	return true;
}

void Scene11::Update()
{
	float dt = m_engine->Get<Timer>()->FrameTime();

	//Get the objects from the scene that we need to update
	Model* model = GetObject<Model>("rocks");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");


	glm::quat rotation = glm::angleAxis(dt, glm::vec3(0.0f, 0.0f, 1.0f));
	light->m_transform.position = rotation * light->m_transform.position;
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);

		

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		glm::mat4 mxModel = model->m_transform.GetMatrix44();
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", light->m_transform.position);
	}


	//	This gets all objects in the scene and calls Update on each of them
	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene11::Render()
{
	glViewport(0, 0, m_engine->Get<Renderer>()->m_width, m_engine->Get<Renderer>()->m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}
void Scene11::Shutdown()
{
}