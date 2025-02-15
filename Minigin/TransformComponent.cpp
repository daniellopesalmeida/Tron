#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner)
	:Component(pOwner)
{
	SetPosition(0, 0, 0);
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position = glm::vec3(x, y, z);
}


void dae::TransformComponent::Render() const
{
}
