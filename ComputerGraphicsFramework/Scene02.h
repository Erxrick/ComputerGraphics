#pragma once
#include "scene.h"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "input.h"

class Scene02 :
	public Scene
{
public:
	Scene02(Engine* engine) : Scene(engine) {};
	~Scene02();

	bool Initialize();
	void Render();
	void Update();
	void Shutdown();

	GLuint m_shaderProgram;
	GLuint vboHandles[3];
	GLuint vaoHandle;
	GLuint m_matrixUniform;
	glm::mat4 m_mxTranslate;
	glm::mat4 m_scale;
	float m_cursorSize = 1;
	Input::eButtonState m_state;

	#pragma region Mouse Stuff
	float m_mouseX;
	float m_mouseY;
	float m_x;
	float m_y;

	#pragma endregion

	
};
