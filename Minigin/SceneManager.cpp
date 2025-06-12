#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include <iostream>

void dae::SceneManager::Update(float deltaTime)
{
	
	m_CurrentScene->Update(deltaTime);
	
}

void dae::SceneManager::FixedUpdate()
{
	
	m_CurrentScene->FixedUpdate();
	
}

void dae::SceneManager::Render()
{
	
	m_CurrentScene->Render();
	
}

void dae::SceneManager::SetScene(Scene& scene)
{
	for (const auto& s : m_scenes)
	{
		if (s.get() == &scene)
		{
			if (m_CurrentScene)
			{
				//dae::InputManager::GetInstance().ClearInputs();
				m_CurrentScene->RemoveAll();

			}


			m_CurrentScene = s;
			return;
		}
	}
}

void dae::SceneManager::SetScene(const std::string& name)
{
	for (const auto& scene : m_scenes)
	{
		if (scene->GetSceneName() == name)
		{
			m_CurrentScene = scene;
			return;
		}
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(std::string sceneName)
{
	for (auto scene : m_scenes)
	{
		if (scene->GetSceneName() == sceneName)
		{
			return scene;
		}
		else
		{
			std::cout << "no scene with name "" << sceneName << "" found!" << std::endl;
		}
	}
	return nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
