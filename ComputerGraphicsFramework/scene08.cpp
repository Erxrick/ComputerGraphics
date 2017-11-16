#include "stdafx.h"
#include "scene08.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "timer.h"
#include <glm\gtc\random.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>



//user created Jazz

#define NUM_LIGHTS 5
#define SPOTLIGHT

Scene08::~Scene08()
{

}


bool Scene08::Initialize()
{
	m_engine->Get<Input>()->AddButton("quit", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);
	m_engine->Get<Input>()->AddButton("mode", Input::eButtonType::KEYBOARD, GLFW_KEY_SPACE);

	// light
	Light* light;
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		light = new Light(("light" + i), this);
		light->m_transform.position = glm::sphericalRand(4.0f);
		light->m_diffuse = glm::rgbColor(glm::vec3(glm::linearRand(0.0f, 360.0f), 1.0f, 1.0f));
		light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
		AddObject(light);
	}
	auto lights = GetObjects<Light>();
	//Light* light = new Light("light", this);
	//light->m_transform.position = glm::vec3(0.0f, 2.0f, 1.5f);
	//light->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	//light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	//AddObject(light);


	// model  cube
	//	creates the model object and sets the transform of the model
	auto model = new Model("cube", this);
	model->m_transform.scale = glm::vec3(1.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.0f, 0.5f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
#ifdef SPOTLIGHT
	model->m_shader.CompileShader("Resources\\Shaders\\multi_light_phong.frag", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("Resources\\Shaders\\phong_directional.frag", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();


	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.0f, 0.9f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 12.0f;
	//model->m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	for (size_t i = 0; i < lights.size(); i++)
	{
		char uniformName[32];
		sprintf_s(uniformName, "lights[%d].diffuse", i);
		model->m_shader.SetUniform(uniformName, lights[i]->m_diffuse);

		char uniformNameS[32];
		sprintf_s(uniformNameS, "lights[%d].specular", i);
		model->m_shader.SetUniform(uniformNameS, lights[i]->m_specular);

//	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
//	model->m_shader.SetUniform("light.specular", light->m_specular);
#ifdef SPOTLIGHT
	char uniformNameC[32];
	sprintf_s(uniformNameC, "lights[%d].cutoff", i);
	model->m_shader.SetUniform(uniformNameC, glm::radians(60.0f));

	//	model->m_shader.SetUniform("light.cutoff", glm::radians(60.0f));

	char uniformNameE[32];
	sprintf_s(uniformNameE, "lights[%d].exponent", i);
	model->m_shader.SetUniform(uniformNameE, 60.0f);
#endif // SPOTLIGHT
	}

	//	model->m_shader.SetUniform("fog.distanceMin", 0.01f);
	//	model->m_shader.SetUniform("fog.distanceMax", 10.0f);
	//	model->m_shader.SetUniform("fog.color", glm::vec3(0.5f, 0.5f, 0.5f));

	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\suzanne.obj");
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	//	add the model to the scene objects
	AddObject(model);
	//-------------------------------------end of cube
	// model  plane
	//	creates the model object and sets the transform of the model
	model = new Model("plane", this);
	model->m_transform.scale = glm::vec3(15.0f);
	model->m_transform.position = glm::vec3(0.0f, -3.0f, 0.0f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
#ifdef SPOTLIGHT
	model->m_shader.CompileShader("Resources\\Shaders\\multi_light_phong.frag", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("Resources\\Shaders\\phong_directional.frag", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();
//	model->m_shader.PrintActiveAttribs();
//	model->m_shader.PrintActiveUniforms();

	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 12.0f;
	//	model->m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);


	for (size_t i = 0; i < lights.size(); i++)
	{
		char uniformName[32];
		sprintf_s(uniformName, "lights[%d].diffuse", i);
		model->m_shader.SetUniform(uniformName, lights[i]->m_diffuse);

		char uniformNameS[32];
		sprintf_s(uniformNameS, "lights[%d].specular", i);
		model->m_shader.SetUniform(uniformNameS, lights[i]->m_specular);


//	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
//	model->m_shader.SetUniform("light.specular", light->m_specular);
#ifdef SPOTLIGHT
	char uniformNameC[32];
	sprintf_s(uniformNameC, "lights[%d].cutoff", i);
	model->m_shader.SetUniform(uniformNameC, glm::radians(60.0f));

	//	model->m_shader.SetUniform("light.cutoff", glm::radians(60.0f));
	
	char uniformNameE[32];
	sprintf_s(uniformNameE, "lights[%d].exponent", i);
	model->m_shader.SetUniform(uniformNameE, 60.0f);

	//model->m_shader.SetUniform("light.exponent", 60.0f);
#endif // SPOTLIGHT
	}


	//	model->m_shader.SetUniform("fog.distanceMin", 0.01f);
	//	model->m_shader.SetUniform("fog.distanceMax", 10.0f);
	//	model->m_shader.SetUniform("fog.color", glm::vec3(0.5f, 0.5f, 0.5f));

	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\plane.obj");
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	//	add the model to the scene objects
	AddObject(model);
	///-----------------------------------------end of plane
	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	//	This can be Camera::eType::EDITOR or Camera::eType::ORBIT
	//	There are two different types of camera modes
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);
	return true;
}

void Scene08::Update()
{
	if (m_engine->Get<Input>()->GetButton("quit") == Input::eButtonState::DOWN) glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);
	if (m_engine->Get<Input>()->GetButton("mode") == Input::eButtonState::DOWN)
	{
		m_pointLightMode = !m_pointLightMode;
	}
	float w = (m_pointLightMode) ? 1.0f : 0.0f;

	float dt = m_engine->Get<Timer>()->FrameTime();



	Camera* camera = GetObject<Camera>("camera");
	


	auto lights = GetObjects<Light>();
	for (int i = 0; i < lights.size(); i++)
	{
		glm::vec4 position = camera->GetView() * glm::vec4(lights[i]->m_transform.position, w);

		auto models = GetObjects<Model>();
		for (auto model : models)
		{
			model->m_shader.Use();

			char uniformName[32]; sprintf_s(uniformName, "lights[%d].position", i);
			model->m_shader.SetUniform(uniformName, position);
		}
	}

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene08::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}
void Scene08::Shutdown()
{
}