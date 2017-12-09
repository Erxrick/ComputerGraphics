#include "stdafx.h"
#include "scene12.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "timer.h"
#include "input.h"
#include "glm\vec4.hpp"
#include <glm\gtc\random.hpp>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>



#define SHADOW_BUFFER_WIDTH 1024
#define SHADOW_BUFFER_HEIGHT 1024



Scene12::~Scene12()
{
}


bool Scene12::Initialize()
{
	m_engine->Get<Input>()->AddButton("quit", Input::eButtonType::KEYBOARD, GLFW_KEY_ESCAPE);

//	glDisable(GL_CULL_FACE);

	m_depthShader = new Shader();
	m_depthShader->CompileShader("Resources\\Shaders\\shadow_depth.vert", GL_VERTEX_SHADER);
	m_depthShader->CompileShader("Resources\\Shaders\\shadow_depth.frag", GL_FRAGMENT_SHADER);
	m_depthShader->Link();

	GLuint depthTexture = Material::CreateDepthTexture(SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);


	// light
	Light* light = new Light("light", this);
	light->m_transform.position = glm::vec3(0.0f, 3.0f, 2.0f);
	light->m_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light->m_specular = glm::vec3(0.0f, 0.0f, 1.0f);
	AddObject(light);

	// suzanne
	//	creates the model object and sets the transform of the model
	auto model = new Model("model", this);
	model->m_transform.scale = glm::vec3(1.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.25f, 0.0f);
	model->m_material.m_diffuse = glm::vec3(0.4f, 0.6f, 0.4f);
	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\shadow_phong.vert", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("Resources\\Shaders\\shadow_phong.frag", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();
	model->m_material.AddTexture(depthTexture, GL_TEXTURE1);
	model->m_material.m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	model->m_material.m_diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 20.0f;

	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\suzanne.obj", true);
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);
	model->m_mesh.BindVertexAttrib(3, Mesh::eVertexType::TANGENT);
	AddObject(model);

	// floor
	//	creates the model object and sets the transform of the model
	auto model2 = new Model("floor", this);
	model2->m_transform.scale = glm::vec3(8.0f);
	model2->m_transform.position = glm::vec3(0.0f, -1.0f, 0.0f);
	//	loads the shaders for the model, you should be familiar with this code
	model2->m_shader.CompileShader("Resources\\Shaders\\shadow_phong.vert", GL_VERTEX_SHADER);
	model2->m_shader.CompileShader("Resources\\Shaders\\shadow_phong.frag", GL_FRAGMENT_SHADER);
	model2->m_shader.Link();
	model2->m_shader.Use();
	model2->m_shader.PrintActiveAttribs();
	model2->m_shader.PrintActiveUniforms();
	model2->m_material.AddTexture(depthTexture, GL_TEXTURE1);
	model2->m_material.m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	model2->m_material.m_diffuse = glm::vec3(0.5f, 0.2f, 0.5f);
	model2->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);

	model2->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model2->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model2->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model2->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model2->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model2->m_shader.SetUniform("light.specular", light->m_specular);


	//	load the model mesh
	model2->m_mesh.Load("Resources\\Meshes\\plane.obj", true);
	//	set the model mesh buffers to the attrib
	model2->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model2->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model2->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);
	model2->m_mesh.BindVertexAttrib(3, Mesh::eVertexType::TANGENT);
	AddObject(model2);

	//debug
	auto model3 = new Model("debug", this);
	model3->m_transform.scale = glm::vec3(8.0f);
	model3->m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
	//	loads the shaders for the model, you should be familiar with this code
	model3->m_shader.CompileShader("Resources\\Shaders\\shadow_debug_depth.vert", GL_VERTEX_SHADER);
	model3->m_shader.CompileShader("Resources\\Shaders\\shadow_debug_depth.frag", GL_FRAGMENT_SHADER);
	model3->m_shader.Link();
	model3->m_shader.Use();
	model3->m_shader.PrintActiveAttribs();
	model3->m_shader.PrintActiveUniforms();
	//	load the model mesh
	model3->m_mesh.Load("Resources\\Meshes\\quad.obj", true);
	//	set the model mesh buffers to the attrib
	model3->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model3->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::TEXCOORD);

	model3->m_material.AddTexture(depthTexture, GL_TEXTURE0);

	//AddObject(model3);
	

	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	//	This can be Camera::eType::EDITOR or Camera::eType::ORBIT
	//	There are two different types of camera modes
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);


	m_depthBuffer = Material::CreateDepthBuffer(depthTexture, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);


	return true;
}

void Scene12::Update()
{
	if (m_engine->Get<Input>()->GetButton("quit") == Input::eButtonState::DOWN)
	{
		glfwSetWindowShouldClose(m_engine->Get<Renderer>()->m_window, GLFW_TRUE);
	}

	float dt = m_engine->Get<Timer>()->FrameTime();

	//Get the objects from the scene that we need to update
	Model* model = GetObject<Model>("model");
	Camera* camera = GetObject<Camera>("camera");
	Light* light = GetObject<Light>("light");

	glm::quat rotation = glm::angleAxis(dt, glm::vec3(0.0f, 1.0f, 0.0f));
	light->m_transform.position = rotation * light->m_transform.position;

	glm::mat4 mxLightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
	glm::mat4 mxLightView = glm::lookAt(light->m_transform.position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mxVP = mxLightProjection * mxLightView;

	m_depthShader->Use();
	m_depthShader->SetUniform("mxLVP", mxVP);

	glm::vec4 lightPosition = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);

	glm::mat4 mxBias(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	);

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		model->m_shader.Use();
		model->m_shader.SetUniform("light.position", lightPosition);
		glm::mat4 mxModel = model->m_transform.GetMatrix44();
		glm::mat4 mxBVP = mxBias * mxVP * mxModel;
		model->m_shader.SetUniform("mxMLP", mxBVP);
	}


	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene12::Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, SHADOW_BUFFER_WIDTH, SHADOW_BUFFER_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthBuffer);
	glClear(GL_DEPTH_BUFFER_BIT);

	m_depthShader->Use();

	auto model = GetObject<Model>("model");
	m_depthShader->SetUniform("mxModel", model->m_transform.GetMatrix44());
	model->m_mesh.Render();
	model = GetObject<Model>("floor");
	m_depthShader->SetUniform("mxModel", model->m_transform.GetMatrix44());
	model->m_mesh.Render();

	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_engine->Get<Renderer>()->m_width, m_engine->Get<Renderer>()->m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto renderables = GetObjects<Renderable>();
	for (auto renderable : renderables)
	{
		renderable->Render();
	}

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}
void Scene12::Shutdown()
{
}