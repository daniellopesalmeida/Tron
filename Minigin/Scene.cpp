#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

std::shared_ptr<GameObject> dae::Scene::FindObjectByTag(const std::string& tag)
{
	for (const auto& obj : m_objects)
	{
		if (obj && obj->HasTag(tag))
			return obj;
	}
	return nullptr;
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		if (object == nullptr) continue;
		if (!object->IsMarkedForDeletion())
		{
			object->Update(deltaTime);
		}
		else
		{
			Remove(object);
		}
	}
}

void dae::Scene::FixedUpdate()
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

