#pragma once
#include "Component.h"
#include <TransformComponent.h>


class TransformComponent;

class BulletComponent : public dae::Component
{
public:
	BulletComponent(dae::GameObject* pOwner);
	~BulletComponent()override = default;

	void Update(float deltaTime) override;
	void Render() override;
	void FixedUpdate() override;

	void SetDirection(const glm::vec2& dir) { m_Direction = glm::normalize(dir); }

private:
	dae::TransformComponent* m_Transform{};
	glm::vec2 m_Direction{ 1.0f, 0.0f };
	float m_Speed{ 100.0f };
	const int m_MaxBounces{ 3 };
	int m_NrOfBounces{ 0 };
	const float m_MaxLifetime{ 5.0f };
	float m_Lifetime{ 0.0f };
};

