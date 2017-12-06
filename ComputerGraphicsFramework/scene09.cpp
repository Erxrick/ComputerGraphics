#include "stdafx.h"
#include "scene09.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "timer.h"
#include <glm\gtc\random.hpp>


#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/color_space.hpp>


Scene09::~Scene09()
{
}


bool Scene09::Initialize()
{
	// light
	Light* light = new Light("light", this);
	light->m_transform.position = glm::vec3(3.0f, 2.0f, 1.0f);
	light->m_diffuse = glm::rgbColor(glm::vec3(glm::linearRand(0.0f, 360.0f), 1.0f, 0.8f));
	light->m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	AddObject(light);



	// model
	//	creates the model object and sets the transform of the model
	auto model = new Model("suzanne", this);
	model->m_transform.scale = glm::vec3(1.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\phong.vert", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("Resources\\Shaders\\phong.frag", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	//model->m_shader.PrintActiveAttribs();
	//model->m_shader.PrintActiveUniforms();


	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 200.0f;
//	model->m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);
	
	model->m_cameraID = "camera_rtt";


	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\suzanne.obj");
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	//	add the model to the scene objects
	AddObject(model);

	//	creates the model object and sets the transform of the model
	model = new Model("cube", this);
	model->m_transform.scale = glm::vec3(1.0f);
	model->m_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

	//	loads the shaders for the model, you should be familiar with this code
	model->m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
	model->m_shader.CompileShader("Resources\\Shaders\\texture_phong.frag", GL_FRAGMENT_SHADER);
	model->m_shader.Link();
	model->m_shader.Use();
	//model->m_shader.PrintActiveAttribs();
	//model->m_shader.PrintActiveUniforms();


	//	sets the material for the model
	model->m_material.m_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	model->m_material.m_diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	model->m_material.m_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	model->m_material.m_shininess = 0.4f * 200.0f;
	//	model->m_material.LoadTexture2D("Resources\\Textures\\crate.bmp", GL_TEXTURE0);
	GLuint texture = Material::CreateTexture(512, 512);
	model->m_material.AddTexture(texture, GL_TEXTURE0);


	//	sets the shader uniforms for the model, since these won’t change during the scene we can do them in the Initialize
	model->m_shader.SetUniform("material.ambient", model->m_material.m_ambient);
	model->m_shader.SetUniform("material.diffuse", model->m_material.m_diffuse);
	model->m_shader.SetUniform("material.specular", model->m_material.m_specular);
	model->m_shader.SetUniform("material.shininess", model->m_material.m_shininess);

	model->m_shader.SetUniform("light.diffuse", light->m_diffuse);
	model->m_shader.SetUniform("light.specular", light->m_specular);

	model->m_cameraID = "camera_rtt";


	//	load the model mesh
	model->m_mesh.Load("Resources\\Meshes\\cube.obj");
	//	set the model mesh buffers to the attrib
	model->m_mesh.BindVertexAttrib(0, Mesh::eVertexType::POSITION);
	model->m_mesh.BindVertexAttrib(1, Mesh::eVertexType::NORMAL);
	model->m_mesh.BindVertexAttrib(2, Mesh::eVertexType::TEXCOORD);

	//	add the model to the scene objects
	AddObject(model);




	// camera
	Camera* camera = new Camera("camera", this);
	Camera::Data data;
	data.type = Camera::eType::ORBIT;
	camera->Initialize(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(camera);

	Camera* cam = new Camera("camera_rtt", this);
	data.type = Camera::eType::LOOK_AT;
	cam->Initialize(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), data);
	AddObject(cam);

	//Framebuffer stuff
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
//set texture to render to
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);


	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(result == GL_FRAMEBUFFER_COMPLETE);



	return true;
}

void Scene09::Update()
{
	float dt = m_engine->Get<Timer>()->FrameTime();

	Light* light = GetObject<Light>("light");
	//Get the objects from the scene that we need to update
	Model* model = GetObject<Model>("suzanne");
	m_rotation = m_rotation + 1.0f * dt;
	glm::quat rotation = glm::angleAxis(m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	model->m_transform.rotation = rotation;


	Camera* camera = GetObject<Camera>("camera_rtt");
	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);
	model->m_shader.Use();
	model->m_shader.SetUniform("light.position", position);

	camera = GetObject<Camera>("camera");
	position = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);

	model = GetObject<Model>("cube");
	model->m_shader.Use();
	model->m_shader.SetUniform("light.position", position);





	//Transform the light position to put it into view space
//	glm::vec4 position = camera->GetView() * glm::vec4(light->m_transform.position, 1.0f);
//	auto models = GetObjects<Model>();
//	for (auto model : models)
//	{
//		model->m_shader.Use();
//		model->m_shader.SetUniform("light.position", position);
//	}
	//Set the model shader as current
//	model->m_shader.Use();
	//	Set the uniforms of the model shader
//	model->m_shader.SetUniform("light.position", position);

	auto objects = GetObjects<Object>();
	for (auto object : objects)
	{
		object->Update();
	}
}

void Scene09::Render()
{
	glViewport(0, 0, 512, 512);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto renderable = GetObject<Renderable>("suzanne");
	renderable->Render();

	glFlush();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, m_engine->Get<Renderer>()->m_width, m_engine->Get<Renderer>()->m_height);
	glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	renderable = GetObject<Renderable>("cube");
	renderable->Render();
	renderable = GetObject<Renderable>("light");
	renderable->Render();


//	std::vector<Renderable*> renderables = GetObjects<Renderable>();
//	for (auto renderable : renderables)
//	{
//		renderable->Render();
//	}
	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}
void Scene09::Shutdown()
{
}