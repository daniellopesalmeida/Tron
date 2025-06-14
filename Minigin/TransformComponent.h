#pragma once
#include <glm.hpp>
#include "Component.h"


namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pOwner);
		~TransformComponent() override = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void SetPosition(glm::vec2 position);
		void SetPosition(const float x, const float y);
		void SetWorldPosition(glm::vec2 pos) { m_WorldPosition = pos; }
		const glm::vec2 GetWorldPosition();
		const glm::vec2 GetLocalPosition() { return m_LocalPosition; }


		void UpdateWorldPosition();

		void SetParent(TransformComponent* gameObject);
		void SetPosDirty();

		void Update(float deltaTime) override;
		void Render() override;

	private:
		//glm::vec3 m_Position{};
		glm::vec2 m_LocalPosition{};
		glm::vec2 m_WorldPosition{};

		TransformComponent* m_parent{};
		bool m_IsPosDirty{false};

	};
}