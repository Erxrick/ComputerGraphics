#pragma once
#include "scene.h"
#include "glm/vec3.hpp"
class Scene01 :
	public Scene
{
public:
	Scene01(Engine* engine) : Scene(engine) {};
	~Scene01();
	
	bool Initialize();
	void Render();
	void Update();
	void Shutdown();

	GLuint m_program;
	GLuint vboHandles[3];
	GLuint vaoHandle;
	


};



