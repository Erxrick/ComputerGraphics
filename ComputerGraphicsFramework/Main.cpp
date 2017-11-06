// ComputerGraphicsFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "engine.h"
#include "renderer.h"
#include "timer.h"
#include "system.h"
#include "glm\vec3.hpp"
#include "scene01.h"
#include"scene02.h"
#include"scene03.h"
#include "scene04.h"
#define STB_IMAGE_IMPLEMENTATION






int main()
{
	// create / initialize engine
	std::shared_ptr<Engine> engine(new Engine);
	if (!engine->Initialize())
	{
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}
	std::shared_ptr<Scene> scene(new Scene04(engine.get()));
	if (!scene->Initialize())
	{
		scene->Shutdown();
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}


	while (!glfwWindowShouldClose(engine->Get<Renderer>()->m_window))
	{
		engine->Update();
		scene->Update();
		scene->Render();

	}
	scene->Shutdown();
	engine->Shutdown();

	


    return 0;
}

