#include "stdafx.h"
#include "scene10.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "timer.h"

Scene10::~Scene10()
{
}


bool Scene10::Initialize()
{

	glDisable(GL_CULL_FACE);

	// model
	//	creates the model object and sets the transform of the model
	auto model = new Model("skybox", this);
	model->m_transform.scale = glm::vec3(20.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\reflection.vert", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("Resources\\Shaders\\reflection.frag", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	model->m_shader.PrintActiveAttribs();
	model->m_shader.PrintActiveUniforms();



	std::vector<std::string> suffixes = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
	model->m_material.LoadTextureCube("Resources\\Textures\\lancellotti", suffixes, "jpg", GL_TEXTURE0);

	GLuint skyboxIndex = glGetSubroutineIndex(model->m_shader.GetHandle(), GL_VERTEX_SHADER, "skybox");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &skyboxIndex);



	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\cube.obj");
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);


	//	add the model to the scene objects
	AddObject(model);

	// othermodel
	//	creates the model object and sets the transform of the model
	auto model2 = new Model("suzanne", this);
	model2->m_transform.scale = glm::vec3(1.0f);
	model2->m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	//	loads the shaders for the model, you should be familiar with this code
	model2->m_shader.CompileShader("Resources\\Shaders\\reflection.vert", GL_VERTEX_SHADER);
	model2->m_shader.CompileShader("Resources\\Shaders\\reflection.frag", GL_FRAGMENT_SHADER);
	model2->m_shader.Link();
	model2->m_shader.Use();
	model2->m_shader.PrintActiveAttribs();
	model2->m_shader.PrintActiveUniforms();



//	std::vector<std::string> suffixes2 = { "_posx", "_negx", "_posy", "_negy", "_posz", "_negz" };
//	model2->m_material.LoadTextureCube("Resources\\Textures\\lancellotti", suffixes2, "jpg", GL_TEXTURE0);

	GLuint reflectionIndex = glGetSubroutineIndex(model->m_shader.GetHandle(), GL_VERTEX_SHADER, "reflection");
	glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &reflectionIndex);



	//	load the model mesh
	model2->m_mesh.Load("Resources\\Meshes\\suzanne.obj");
	//	set the model mesh buffers to the attrib
	model2->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model2->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);


	//	add the model to the scene objects
	AddObject(model2);


	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	//	This can be Camera::eType::EDITOR or Camera::eType::ORBIT
	//	There are two different types of camera modes
	data.type = Camera::eType::EDITOR;
	camera->Initialize(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);
	return true;
}

void Scene10::Update()
{
	float dt = m_engine->Get<Timer>()->FrameTime();

	//Get the objects from the scene that we need to update
	Model* model = GetObject<Model>("suzanne");
	Camera* camera = GetObject<Camera>("camera");

	model->m_transform.rotation = glm::quat(glm::vec3(0.0, dt, 0.0f)) * model->m_transform.rotation;

	auto models = GetObjects<Model>();
	for (auto model : models)
	{
		glm::mat4 mxModel = model->m_transform.GetMatrix44();
		model->m_shader.Use();
		model->m_shader.SetUniform("mxModel", mxModel);
		model->m_shader.SetUniform("cameraWorldPosition", camera->m_transform.position);
	}


	//	This gets all objects in the scene and calls Update on each of them
	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene10::Render()
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
void Scene10::Shutdown()
{
}