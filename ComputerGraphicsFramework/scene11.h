#pragma once
#include "scene.h"
class Scene11 :
	public Scene
{
public:
	Scene11(Engine* engine) : Scene(engine) {};
	~Scene11();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	float m_rotation = 0.0;
};

