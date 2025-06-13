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

    if (m_Direction.x != 0.f && m_Direction.y != 0.f)
        return;

    // Save last position
    m_LastPosition = m_Transform->GetLocalPosition();

    // Calculate new position
    glm::vec2 position = m_LastPosition + m_Direction * m_Speed * deltaTime;
    m_Transform->SetPosition(position.x, position.y);
}

void dae::MovementComponent::StayInPathPosition()
{
    if (m_Transform)
        m_Transform->SetPosition(m_LastPosition.x, m_LastPosition.y);
}

void dae::MovementComponent::OnCollision(CollisionComponent* other)
{
    if(!other || !other->GetOwnerPublic())
        return;

    const std::string& tag = other->GetOwnerPublic()->GetTag();

    if (tag == "Wall")
    {
        StayInPathPosition(); // stay in position
    }
}


