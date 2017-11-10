#pragma once
#include "scene.h"
class Scene06 :
	public Scene
{
public:
	Scene06(Engine* engine) : Scene(engine) {};
	~Scene06();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	float m_rotation = 0.0;
};

