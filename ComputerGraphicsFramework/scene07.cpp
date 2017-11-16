#include "stdafx.h"
#include "scene07.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include "timer.h"


#define SPOTLIGHT

Scene07::~Scene07()
{

}


bool Scene07::Initialize()
{
	m_engine->Get<Input>()->AddButton("quit", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);
	m_engine->Get<Input>()->AddButton("mode", Input::eButtonType::KEYBOARD, GLFW_KEY_SPACE);

	// light
	Light* light = new Light("light", this);
	light->m_transform.position = glm::vec3(0.0f, 2.0f, 1.5f);
	light->m_diffuse = glm::vec3(0.75f, 1.0f, 0.75f);
	light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	AddObject(light);


	// model  cube
	//	creates the model object and sets the transform of the model
	auto model = new Model("cube", this);
	model->m_transform.scale = glm::vec3(1.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.0f, 0.5f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
#ifdef SPOTLIGHT
	model->m_shader.CompileShader("Resources\\Shaders\\phong_spotlight.frag", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("Resources\\Shaders\\phong_directional.frag", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();


	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.0f, 0.9f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 12.0f;
	//model->m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);
#ifdef SPOTLIGHT
	model->m_shader.SetUniform("light.cutoff", glm::radians(45.0f));
	model->m_shader.SetUniform("light.exponent", 30.0f);
#endif // SPOTLIGHT

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
	model->m_shader.CompileShader("Resources\\Shaders\\phong_spotlight.frag", GL_FRAGMENT_SHADER);
#else
	model->m_shader.CompileShader("Resources\\Shaders\\phong_directional.frag", GL_FRAGMENT_SHADER);
#endif
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();

	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.0f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 12.0f;
//	model->m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);
#ifdef SPOTLIGHT
	model->m_shader.SetUniform("light.cutoff", glm::radians(45.0f));
	model->m_shader.SetUniform("light.exponent", 60.0f);
#endif // SPOTLIGHT


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

void Scene07::Update()
{
	if (m_engine->Get<Input>()->GetButton("quit") == Input::eButtonState::DOWN) glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);
	if (m_engine->Get<Input>()->GetButton("mode") == Input::eButtonState::DOWN)
	{
		m_pointLightMode = !m_pointLightMode;
	}
	float w = (m_pointLightMode) ? 1.0f : 0.0f;



	float dt = m_engine->Get<Timer>()->FrameTime();
	//Get the objects from the scene that we need to update
	//Model* model = GetObject<Model>("cube");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	m_rotation = 1.0f * dt;
	glm::quat rotation = glm::angleAxis(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	light->m_transform.position = rotation * light->m_transform.position;
	//glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);


	//Transform the light position to put it into view space
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.position, w);
	//Set the model shader as current
	//model->m_shader.Use();
	//	Set the uniforms of the model shader
	//model->m_shader.SetUniform("light.position", position);

	glm::mat3 viewDirectionMatrix = glm::mat3(camera->GetView());
	glm::vec3 direction = viewDirectionMatrix * glm::vec4(glm::vec3(0.0f, -1.0f, 0.0f), 0.0f);


	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", position);
#ifdef SPOTLIGHT
		model->m_shader.SetUniform("light.direction", direction);
#endif // SPOTLIGHT

	}


	//	This gets all objects in the scene and calls Update on each of them
	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene07::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	Get a vector of all Renderable objects and call Render on each one
	//		Right now we only have one renderable object in our scene and that is the model
	std::vector<Renderable*> renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}
	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}
void Scene07::Shutdown()
{
}