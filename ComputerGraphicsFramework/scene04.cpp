#include "stdafx.h"
#include "scene04.h"
#include "timer.h"
#include "image.h"

#define PHONG
#define SPECULAR



namespace scene04
{
	float vertexData[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f

	};

	enum vboID
	{
		POSITION,
		COLOR,
		VERTEX
	};

}

Scene04::~Scene04()
{
}

bool Scene04::Initialize()
{
#ifdef SPECULAR
	m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
	m_shader.CompileShader("Resources\\Shaders\\multi_phong.frag", GL_FRAGMENT_SHADER);
	m_shader.Link();
	m_shader.Use();
	//	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\phong.vert", "Resources\\Shaders\\phong.frag");
//#endif
//#ifdef PHONG 
//	m_shader.CompileShader("Resources\\Shaders\\texture_phong.vert", GL_VERTEX_SHADER);
//	m_shader.CompileShader("Resources\\Shaders\\texture_phong.frag", GL_FRAGMENT_SHADER);
//	m_shader.Link();
//	m_shader.Use();
#else // 
	m_cube.shaderProgram = m_engine->Get<Renderer>()->CreateShaderProgram("Resources\\Shaders\\light.vert", "Resources\\Shaders\\basic.frag");
#endif
	glGenBuffers(1, &vboHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(scene04::vertexData), scene04::vertexData, GL_STATIC_DRAW);

	//	glBindBuffer(GL_ARRAY_BUFFER, vboHandles[scene03::COLOR]);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(scene03::colorData), scene03::colorData, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexBuffer(0, vboHandle, 0, sizeof(GLfloat) * 8);
	glBindVertexBuffer(1, vboHandle, sizeof(glm::vec3), sizeof(GLfloat) * 8);
	glBindVertexBuffer(2, vboHandle, sizeof(glm::vec3)*2, sizeof(GLfloat) * 8);


	glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(0, 0);

	glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(1, 1);
	
	glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(2, 2);



	const unsigned char* image1 = Image::LoadBMP("Resources\\Textures\\crate.bmp", width, height, bpp);
	const unsigned char* image2 = Image::LoadBMP("Resources\\Textures\\grass.bmp", width, height, bpp);

	glActiveTexture(GL_TEXTURE0);
	GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	m_shader.SetUniform("texture1", texID);
	//tex2
	glActiveTexture(GL_TEXTURE1);
	GLuint textureID2;
	glGenTextures(1, &textureID2);

	glBindTexture(GL_TEXTURE_2D, textureID2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	m_shader.SetUniform("texture2", texID2);

	//glUniform1i(texID, 0);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);



	delete image1;
	delete image2;

	//
	//m_cube.mxModelViewUniform = glGetUniformLocation(m_cube.shaderProgram, "mxModelView");
	//m_cube.mxMVPUniform = glGetUniformLocation(m_cube.shaderProgram, "mxMVP");
	//m_cube.mxNormalUniform = glGetUniformLocation(m_cube.shaderProgram, "mxNormal");

	//m_cube.ambientMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "ambientMaterial");
	//m_cube.diffuseMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "diffuseMaterial");
	//m_cube.specularMaterialUniform = glGetUniformLocation(m_cube.shaderProgram, "specularMaterial");

	//m_light.positionUniform = glGetUniformLocation(m_cube.shaderProgram, "lightPosition");
	//m_light.colorUniform = glGetUniformLocation(m_cube.shaderProgram, "lightColor");

	//std::cout << "cube ambient uniform: " << m_cube.ambientMaterialUniform << std::endl;
	//std::cout << "cube diffuse uniform: " << m_cube.diffuseMaterialUniform << std::endl;
	//std::cout << "cube specular uniform: " << m_cube.specularMaterialUniform << std::endl;

	//std::cout << "cube modelView uniform: " << m_cube.mxModelViewUniform << std::endl;
	//std::cout << "cube MVP uniform: " << m_cube.mxMVPUniform << std::endl;
	//std::cout << "cube normal uniform: " << m_cube.mxNormalUniform << std::endl;

	//std::cout << "light position uniform:" << m_light.positionUniform << std::endl;
	//std::cout << "light color uniform:" << m_light.colorUniform << std::endl;




	return true;
}

void Scene04::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render code
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glfwSwapBuffers(m_engine->Get<Renderer>()->m_window);
}

void Scene04::Update()
{

	m_ambientMaterial = glm::vec3(0.2f, 0.2f, 0.2f);
	m_shader.SetUniform("ambientMaterial", m_ambientMaterial);
//	glUniform3fv(m_cube.ambientMaterialUniform, 1, &m_ambientMaterial[0]);

	m_rotation = m_rotation + m_engine->Get<Timer>()->FrameTime();
	m_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	m_rotate = glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
	m_mxModel = m_translate * m_rotate;

	m_mxView = glm::lookAt(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_mxProjection = glm::perspective(90.0f, ((float)m_engine->Get<Renderer>()->m_width / (float)m_engine->Get<Renderer>()->m_height), 0.001f, 100.0f);


	m_mxModelView = m_mxView * m_mxModel;
	m_shader.SetUniform("mxModelView", m_mxModelView);
//	glUniformMatrix4fv(m_cube.mxModelViewUniform, 1, GL_FALSE, &m_mxModelView[0][0]);

	m_MVP = m_mxProjection * m_mxView * m_mxModel;
	m_shader.SetUniform("mxMVP", m_MVP);
//	glUniformMatrix4fv(m_cube.mxMVPUniform, 1, GL_FALSE, &m_MVP[0][0]);


	m_mxNormal = glm::mat3(m_mxModelView);
	m_mxNormal = glm::inverse(m_mxNormal);
	m_mxNormal = glm::transpose(m_mxNormal);
	m_shader.SetUniform("mxNormal", m_mxNormal);
//	glUniformMatrix3fv(m_cube.mxNormalUniform, 1, GL_FALSE, &m_mxNormal[0][0]);

	m_lightPosition = m_mxView * glm::vec4(0.0f, 10.0f, 10.0f, 1.0f);
	m_shader.SetUniform("lightPosition", m_lightPosition);
//	glUniform4fv(m_light.positionUniform, 1, &m_lightPosition[0]);

	m_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	m_shader.SetUniform("lightColor", m_lightColor);
//	glUniform3fv(m_light.colorUniform, 1, &m_lightColor[0]);

	m_diffuseMaterial = glm::vec3(0.3f, 0.0f, 0.0f);
	m_shader.SetUniform("diffuseMaterial", m_diffuseMaterial);
//	glUniform3fv(m_cube.diffuseMaterialUniform, 1, &m_diffuseMaterial[0]);

	m_specularMaterial = glm::vec3(0.0f, 1.0f, 0.0f);
	m_shader.SetUniform("specularMaterial", m_specularMaterial);
//	glUniform3fv(m_cube.specularMaterialUniform, 1, &m_specularMaterial[0]);


}

void Scene04::Shutdown()
{
}
