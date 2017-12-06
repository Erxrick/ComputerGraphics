#pragma once
#include "scene.h"
class Scene09 :
	public Scene
{
public:
	Scene09(Engine* engine) : Scene(engine) {};
	~Scene09();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	float m_rotation = 0.0;
	GLuint m_framebuffer;
};

