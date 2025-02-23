#include "RotationComponent.h"
#include <stdexcept>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/rotate_vector.hpp>
#include <glm.hpp>

dae::RotationComponent::RotationComponent(GameObject* pOwner,  float radius, float rotationSpeed)
	:Component(pOwner), m_Radius(radius), m_RotationSpeed(rotationSpeed)
{

	m_Position = pOwner->GetTransform()->GetLocalPosition();
	
}

void dae::RotationComponent::Update(float deltaTime)
{
	m_CurrentAngle += m_RotationSpeed * deltaTime;
	
	GetOwner()->SetPosition( m_Position.x + cosf(m_CurrentAngle) * m_Radius, m_Position.y - sinf(m_CurrentAngle) * m_Radius );
	
}
