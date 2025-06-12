#include "BulletComponent.h"
#include "GameObject.h"

BulletComponent::BulletComponent(dae::GameObject* pOwner)
	:Component(pOwner)
{
	//m_Transform = pOwner->GetTransform();
	m_Transform = GetOwner()->GetTransform();
}

void BulletComponent::Update(float deltaTime)
{
	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	pos.x += m_Direction.x * m_Speed * deltaTime;
	pos.y += m_Direction.y * m_Speed * deltaTime;
	GetOwner()->SetPosition(pos.x, pos.y);

	// Lifetime handling
	m_Lifetime += deltaTime;
	if (m_Lifetime >= m_MaxLifetime)
	{
		GetOwner()->Delete();
	}
}

void BulletComponent::Render()
{
}

void BulletComponent::FixedUpdate()
{
}
