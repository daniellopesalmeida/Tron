#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/rotate_vector.hpp>
#include "Component.h"
#include "TransformComponent.h" 
#include "GameObject.h"
#include <glm.hpp>

namespace dae
{

	class RotationComponent final : public Component
	{

	public:
		RotationComponent(GameObject* pOwner, float radius=10.f, float rotationSpeed=1.f);
		~RotationComponent() override = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		void Update(float deltaTime);
		void SetRotationSpeed(float speed) { m_RotationSpeed = speed; }

	private:
		bool m_IsRotating{ true };
		TransformComponent* m_Transform{};
		
		glm::vec3 m_Position{};
		float m_RotationSpeed;  // Degrees per second
		float m_Radius;         // Distance from pivot
		float m_CurrentAngle{ 0.0f }; // Current angle
		
	};
}
