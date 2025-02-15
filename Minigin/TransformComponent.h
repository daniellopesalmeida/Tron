#pragma once
#include <glm.hpp>
#include "Component.h"
namespace dae
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* gameObject);
		~TransformComponent() override = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		void SetPosition(const float x, const float y, const float z);
		const glm::vec3& GetPosition() const { return m_Position; }

		//void Update(float deltaTime) override;
		void Render() const override;

	private:
		glm::vec3 m_Position{};

	};
}