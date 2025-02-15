#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include "TransformComponent.h"
#include "Component.h"
#include <string>

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		TransformComponent* GetTransform() const { return m_Transform; }

		// Create and add a new component, returning a pointer to it
		template <typename T, typename... TArgs>
		T* AddComponent(TArgs&&... args);

		// Add an existing component (takes ownership)
		template <typename T>
		void AddComponent(std::unique_ptr<T> component);

		// Remove a component by type
		template <typename T>
		void RemoveComponent();

		// Get a component by type
		template <typename T>
		T* GetComponent() const;

		GameObject();
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


	private:
		TransformComponent* m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<std::unique_ptr<Component>> m_Components{};
	};

	
	template<typename T, typename ...TArgs>
	inline T* GameObject::AddComponent(TArgs && ...args)
	{
		static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

		auto component = std::make_unique<T>(this, std::forward<TArgs>(args)...);
		T* rawPtr = component.get();
		m_Components.push_back(std::move(component));
		return rawPtr;
	}

	// Implementation: Add an existing component
	template <typename T>
	void GameObject::AddComponent(std::unique_ptr<T> component)
	{
		static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

		m_Components.push_back(std::move(component)); 
	}

	// Implementation: Remove a component
	template <typename T>
	void GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

		auto it = std::remove_if(m_Components.begin(), m_Components.end(),
			[](const std::unique_ptr<Component>& component) {
				return dynamic_cast<T*>(component.get()) != nullptr;
			});
		m_Components.erase(it, m_Components.end());
	}

	// Implementation: Get a component
	template <typename T>
	T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

		for (const auto& component : m_Components)
		{
			if (T* casted = dynamic_cast<T*>(component.get()))
			{
				return casted;
			}
		}
		return nullptr;
	}
}

