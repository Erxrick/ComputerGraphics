#pragma once
#include "engine.h"
#include "renderer.h"
#include "object.h"
class Scene
{
public:
	Scene(Engine* engine) : m_engine(engine) {};

	virtual ~Scene() 
	{
		for (auto obj : m_objects)
		{
			delete obj;
		}
	};

	virtual bool Initialize() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Shutdown() = 0;

public:
//protected:
	Engine* m_engine;



	void AddObject(Object* obj);
	
	template<typename T>
	T* GetObject(const std::string& name);

	template<typename T>
	std::vector<T*> GetObjects();

protected:
	std::vector<Object*> m_objects;
};

template<typename T>
inline T * Scene::GetObject(const std::string & name)
{
	for each (Object* obj in m_objects)
	{
		if (obj->m_name == name) return dynamic_cast<T*>(obj);
	}
	return nullptr;
}

template<typename T>
inline std::vector<T*> Scene::GetObjects()
{
	std::vector<T*> objects;

	for each (Object* obj in m_objects)
	{
		if (dynamic_cast<T*>(obj) != nullptr) objects.push_back(dynamic_cast<T*>(obj));
	}

	return objects;
}
