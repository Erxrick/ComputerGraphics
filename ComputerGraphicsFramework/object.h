#pragma once
#include "transform.h"

class Scene;

class Object
{
public:
	Object(std::string name, Scene* scene);
	~Object();

	std::string m_name;
	Transform m_transform;

	virtual void Update() = 0;


protected:
	Scene* m_scene;
};

