#pragma once
#include "scene.h"
class Scene07 :
	public Scene
{
public:
	Scene07(Engine* engine) : Scene(engine) {};
	~Scene07();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	bool m_pointLightMode = true;
	float m_rotation = 0.0;
};

