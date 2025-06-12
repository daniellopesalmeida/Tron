#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void FixedUpdate();
		void Render();

		void SetScene(Scene& scene);
		void SetScene(const std::string& name);
		std::shared_ptr<Scene> GetScene(std::string sceneName);
		std::shared_ptr<Scene> GetCurrentScene() {return m_CurrentScene; };
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes{};
		std::shared_ptr<Scene> m_CurrentScene{};
	};
}
