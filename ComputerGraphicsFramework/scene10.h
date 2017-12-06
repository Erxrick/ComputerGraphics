#pragma once
#include "scene.h"
class Scene10 :
	public Scene
{
public:
	Scene10(Engine* engine) : Scene(engine) {};
	~Scene10();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	float m_rotation = 0.0;
};

