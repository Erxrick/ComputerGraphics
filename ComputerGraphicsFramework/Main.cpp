// ComputerGraphicsFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	// create / initialize engine
	std::shared_ptr<Engine> engine(new Engine);
	if (!engine->Initialize())
	{
		engine->Shutdown();
		exit(EXIT_FAILURE);
	}

	while (!glfwWindowShouldClose(engine->Get<Renderer>()->m_window))
	{
		engine->Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// render code

		glfwSwapBuffers(engine->Get<Renderer>()->m_window);
	}
	engine->Shutdown();

	


    return 0;
}

