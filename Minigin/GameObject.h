#pragma once
#include <memory>
#include <vector>
#include <type_traits>
#include "TransformComponent.h"
#include "Component.h"
#include <string>

namespace dae
{
	
	class GameObject final: public std::enable_shared_from_this<GameObject>
	{
	public:
		void Update(float deltaTime);
		void FixedUpdate();
		void Render() const;

		void SetPosition(float x, float y);

		TransformComponent* GetTransform() const { return m_Transform; }

		void Delete() { m_MarkedForDelete = true; }
		bool IsMarkedForDeletion() const { return m_MarkedForDelete; }
		
		void SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos = false);
		void AddChild(std::shared_ptr<GameObject> child, bool keepWorldPos = false);
		void RemoveChild(std::shared_ptr<GameObject> child);
		void AddChildToContainer(std::shared_ptr<dae::GameObject> child);
		void RemoveChildFromContainer(std::shared_ptr<dae::GameObject> child);

		void PrintNrChildren(std::string name);

		GameObject* GetParent() const { return m_Parent; }
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() { return m_pChildren; }

		// Create and add a new component, returning a pointer to it
		template <typename T, typename... TArgs>
		T* AddComponent(TArgs&&... args);

		// Remove a component by type
		template <typename T>
		void RemoveComponent();

		template <typename T> 
		void RemoveComponent(T* comp);

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
		std::vector<std::unique_ptr<Component>> m_Components{};
		bool m_MarkedForDelete{ false };
		GameObject* m_Parent{ nullptr };
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};
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

	template<typename T>
	void GameObject::RemoveComponent(T* comp)
	{
		for (auto it = begin(m_Components); it != end(m_Components); ++it)
		{
			if (dynamic_cast<T*>(it->get()) == comp)
			{
				m_Components.erase(it);
				break;
			}
		}
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

