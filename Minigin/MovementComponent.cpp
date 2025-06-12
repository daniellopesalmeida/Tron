#include "MovementComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::MovementComponent::MovementComponent(GameObject* pOwner)
	:Component(pOwner)
{
	m_Transform = GetOwner()->GetTransform();
}

void dae::MovementComponent::Update(float deltaTime)
{
	if (!m_Transform || (m_Direction.x == 0.f && m_Direction.y == 0.f))
		return;

	//restrict to axis-aligned movement
	if (m_Direction.x != 0.f && m_Direction.y != 0.f)
	{
		return;
	}

	// Calculate new position
	glm::vec2 position = m_Transform->GetLocalPosition();
	position += m_Direction * m_Speed * deltaTime;

	m_Transform->SetPosition(position.x,position.y);

}


