#pragma once
#include "scene.h"
class Scene08 :
	public Scene
{
public:
	Scene08(Engine* engine) : Scene(engine) {};
	~Scene08();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	int lights = 1;
	bool m_pointLightMode = true;
	float m_rotation[5];
};

