#include "BulletComponent.h"
#include "GameObject.h"
#include <CollisionComponent.h>
#include "PlayerStatsComponent.h"
#include <iostream>

BulletComponent::BulletComponent(dae::GameObject* pOwner)
	:Component(pOwner)
{
	//m_Transform = pOwner->GetTransform();
	m_Transform = GetOwner()->GetTransform();
	m_LastPosition=m_Transform->GetWorldPosition();

}

void BulletComponent::Update(float deltaTime)
{
	m_LastPosition = GetOwner()->GetTransform()->GetWorldPosition();

	auto pos = GetOwner()->GetTransform()->GetWorldPosition();
	pos.x += m_Direction.x * m_Speed * deltaTime;
	pos.y += m_Direction.y * m_Speed * deltaTime;
	GetOwner()->SetPosition(pos.x, pos.y);

	// Lifetime handling
	m_Lifetime += deltaTime;
	if (m_Lifetime >= m_MaxLifetime || m_NrOfBounces>=m_MaxBounces)
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

void BulletComponent::IncrementBounce()
{
	++m_NrOfBounces;
	
	std::cout << "Increment bounce: "<<m_NrOfBounces << std::endl;
}
