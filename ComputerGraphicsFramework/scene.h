#pragma once
#include "engine.h"
#include "renderer.h"
class Scene
{
public:
	Scene(Engine* engine) : m_engine(engine) {};

	virtual bool Initialize() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

protected:
	Engine* m_engine;
};


