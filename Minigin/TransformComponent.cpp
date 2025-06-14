#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pOwner)
	:Component(pOwner)
{
	SetPosition(0, 0);
}

void dae::TransformComponent::SetPosition(glm::vec2 position)
{
	m_LocalPosition = position;
	SetPosDirty();
}

void dae::TransformComponent::SetPosition(const float x, const float y)
{
	m_LocalPosition = glm::vec2(x, y);
	SetPosDirty();
}

const glm::vec2 dae::TransformComponent::GetWorldPosition()
{
	if (m_IsPosDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}


void dae::TransformComponent::UpdateWorldPosition()
{
	if (m_IsPosDirty)
	{
		if (m_parent != nullptr)
		{
			m_WorldPosition = m_parent->GetWorldPosition() + GetLocalPosition();
		}
		else
		{
			m_WorldPosition = m_LocalPosition;
		}
	}
	m_IsPosDirty = false;
}

void dae::TransformComponent::SetParent(TransformComponent* gameObject)
{
	m_parent = gameObject;
}


void dae::TransformComponent::SetPosDirty()
{
	m_IsPosDirty = true;
	dae::GameObject* GOparent = this->GetOwner();
	auto children = GOparent->GetChildren();
	for (auto& child : children)
	{
		child->GetTransform()->SetPosDirty();
	}
}


void dae::TransformComponent::Update(float)
{
	
}

void dae::TransformComponent::Render() 
{
}
