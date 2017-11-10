#include "stdafx.h"
#include "scene.h"

void Scene::AddObject(Object * obj)
{
	m_objects.push_back(obj);
}
