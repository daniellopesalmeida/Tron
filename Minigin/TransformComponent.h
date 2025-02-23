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

		void SetPosition(glm::vec3 position);
		void SetPosition(const float x, const float y, const float z = 0);
		void SetWorldPosition(glm::vec3 pos) { m_WorldPosition = pos; }
		const glm::vec3 GetWorldPosition();
		const glm::vec3 GetLocalPosition() { return m_LocalPosition; }


		void UpdateWorldPosition();

		void SetParent(TransformComponent* gameObject);
		void SetPosDirty() { m_IsPosDirty = true; }

		void Update(float deltaTime) override;
		void Render() const override;

	private:
		glm::vec3 m_Position{};
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};

		TransformComponent* m_parent{};
		bool m_IsPosDirty{false};

	};
}