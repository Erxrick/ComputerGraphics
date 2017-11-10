#include "stdafx.h"
#include "scene02.h"
#include "glm/gtc/matrix_transform.hpp"
#include "timer.h"

namespace scene02
{
	float positionData[] =
	{
		-0.8f, -0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
		0.0f,  0.8f, 0.0f,

	};

	float colorData[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glm::vec3 vPositionData[] =
	{
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(0.8f, -0.8f, 0.0f),
		glm::vec3(0.0f,  0.8f, 0.0f),
	};

	glm::vec3 vColorData[] =
	{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};

	glm::vec3 vertexData[] =
	{
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(1.0f,  0.0f, 0.0f),
		glm::vec3(0.8f, -0.8f, 0.0f),
		glm::vec3(0.0f,  1.0f, 0.0f),
		glm::vec3(0.0f,  0.8f, 0.0f),
		glm::vec3(0.0f,  0.0f, 1.0f),
		glm::vec3(-0.8f, -0.8f, 0.0f),
		glm::vec3(1.0f,  0.0f, 0.0f),
	};

	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};
}


Scene02::~Scene02()
{
}

bool Scene02::Initialize()
{
	m_shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\transform.vert", "Resources\\Shaders\\basic.frag");
	m_matrixUniform = glGetUniformLocation(m_shaderProgram, "modelMatrix");
	m_mxTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(0.5, 0.5, 0.0f));

	glfwSetInputMode(m_engine->Get<Renderer>()->m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glGenBuffers(3, vboHandles);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[scene02::POSITION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene02::positionData), scene02::positionData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[scene02::COLOR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene02::colorData), scene02::colorData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexBuffer(0, vboHandles[scene02::POSITION], 0, sizeof(glm::vec3));
	glBindVertexBuffer(1, vboHandles[scene02::COLOR], 0, sizeof(glm::vec3));

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	m_engine->Get<Input>()->AddButton("click", Input::eButtonType::MOUSE, 0);
	m_engine->Get<Input>()->AddAnalog("x-axis", Input::eAnalogType::MOUSE_X, 0);
	m_engine->Get<Input>()->AddAnalog("y-axis", Input::eAnalogType::MOUSE_Y, 0);
	m_cursorSize = .1f;

	return true;
}

void Scene02::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




	// render code
	glBindVertexArray(vaoHandle);
	glUniformMatrix4fv(m_matrixUniform, 1, GL_FALSE, &m_mxTranslate[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene02::Update()
{
//	float dt = m_engine->Get<Timer>()->FrameTime();
	m_x = (m_mouseX * 2 / m_engine->Get<Renderer>()->m_width) - 1;
	m_y = -(m_mouseY * 2 / m_engine->Get<Renderer>()->m_height) + 1;

	m_state = m_engine->Get<Input>()->GetButton("click");
	m_mouseX = m_engine->Get<Input>()->GetAnalogAbsolute("x-axis");
	m_mouseY = m_engine->Get<Input>()->GetAnalogAbsolute("y-axis");

	m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_cursorSize));
	m_mxTranslate = glm::translate(glm::mat4(1.0f), glm::vec3(m_x, m_y, 0.0f)) * m_scale;

}

void Scene02::Shutdown()
{
}
