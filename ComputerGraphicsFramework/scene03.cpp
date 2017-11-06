#include "stdafx.h"
#include "scene03.h"
#include "timer.h"

#define PHONG


namespace scene03
{

float vertexData[] =
	{	
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};


	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};

}

Scene03::~Scene03()
{
}

bool Scene03::Initialize()
{
#ifdef PHONG
	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\phong.vert", "Resources\\Shaders\\phong.frag");

#else 
	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\light.vert", "Resources\\Shaders\\basic.frag");
#endif // 

	glGenBuffers(1, &vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene03::vertexData), scene03::vertexData, GL_STATIC_DRAW);

//	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[scene03::COLOR]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(scene03::colorData), scene03::colorData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexBuffer(0, vboHandle, 0, sizeof(glm::vec3) * 2);
	glBindVertexBuffer(1, vboHandle, sizeof(glm::vec3), sizeof(glm::vec3) * 2);

	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);

	m_cube.mxModelViewUniform = glGetUniformLocation(m_cube.shaderProgram, "mxModelView");
	m_cube.mxMVPUniform = glGetUniformLocation(m_cube.shaderProgram, "mxMVP");
	m_cube.mxNormalUniform = glGetUniformLocation(m_cube.shaderProgram, "mxNormal");
	
	m_cube.ambientMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "ambientMaterial");
	m_cube.diffuseMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "diffuseMaterial");
	m_cube.specularMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "specularMaterial");
	
	m_light.positionUniform = glGetUniformLocation(m_cube.shaderProgram, "lightPosition");
	m_light.colorUniform = glGetUniformLocation(m_cube.shaderProgram, "lightColor");

	std::cout << "cube ambient uniform: " << m_cube.ambientMaterialUniform  << std::endl;
	std::cout << "cube diffuse uniform: " << m_cube.diffuseMaterialUniform << std::endl;
	std::cout << "cube specular uniform: " << m_cube.specularMaterialUniform << std::endl;
					  
	std::cout << "cube modelView uniform: " << m_cube.mxModelViewUniform << std::endl;
	std::cout << "cube MVP uniform: " << m_cube.mxMVPUniform << std::endl;
	std::cout << "cube normal uniform: " << m_cube.mxNormalUniform << std::endl;
					  
	std::cout << "light position uniform:" << m_light.positionUniform << std::endl;
	std::cout << "light color uniform:" << m_light.colorUniform << std::endl;



	return true;
}

void Scene03::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render code
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene03::Update()
{

	m_ambientMaterial = glm::vec3(0.2f, 0.2f, 0.2f);
	glUniform3fv(m_cube.ambientMaterialUniform, 1, &m_ambientMaterial[0]);

	m_rotation = m_rotation + m_engine->Get<Timer>()->FrameTime() * 10;
	m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0.2f, 10.5f, 1.0f));
	m_mxModel = m_translate * m_rotate;

	m_mxView = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f,0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_mxProjection = glm::perspective(90.0f, ((float)m_engine->Get<Renderer>()->m_width / (float)m_engine->Get<Renderer>()->m_height), 0.001f, 100.0f);


	m_mxModelView = m_mxView * m_mxModel;
	glUniformMatrix4fv(m_cube.mxModelViewUniform, 1, GL_FALSE, &m_mxModelView[0][0]);

	m_MVP = m_mxProjection * m_mxView * m_mxModel;
	glUniformMatrix4fv(m_cube.mxMVPUniform, 1, GL_FALSE, &m_MVP[0][0]);


	m_mxNormal = glm::mat3(m_mxModelView);
	m_mxNormal = glm::inverse(m_mxNormal);
	m_mxNormal = glm::transpose(m_mxNormal);
	glUniformMatrix3fv(m_cube.mxNormalUniform, 1, GL_FALSE, &m_mxNormal[0][0]);

	m_lightPosition = m_mxView * glm::vec4(2.0f, 10.0f, 10.0f, 1.0f);
	glUniform4fv(m_light.positionUniform, 1, &m_lightPosition[0]);

	m_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glUniform3fv(m_light.colorUniform, 1, &m_lightColor[0]);

	m_diffuseMaterial = glm::vec3(0.0f, 0.0f, 1.0f);
	glUniform3fv(m_cube.diffuseMaterialUniform, 1, &m_diffuseMaterial[0]);

	m_specularMaterial = glm::vec3(0.0f, 1.0f, 0.0f);
	glUniform3fv(m_cube.specularMaterialUniform, 1, &m_specularMaterial[0]);


}

void Scene03::Shutdown()
{
}
