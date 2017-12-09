#pragma once
#include "scene.h"
#include "shader.h"
class Scene12 :
	public Scene
{
public:
	Scene12(Engine* engine) : Scene(engine) {};
	~Scene12();


	bool Initialize();
	void Update();
	void Render();
	void Shutdown();

	float m_rotation = 0.0;

private:
	GLuint m_depthBuffer = 0;
	Shader* m_depthShader = nullptr;


};

