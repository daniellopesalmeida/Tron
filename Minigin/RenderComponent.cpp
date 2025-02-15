#include "RenderComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include <iostream>

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	:Component(pOwner)
{
}

void dae::RenderComponent::Render() const
{
	const auto transform = GetOwner()->GetTransform();
	
	if (transform != nullptr)
	{
		auto posX = transform->GetPosition().x;
		auto posY = transform->GetPosition().y;
		Renderer::GetInstance().RenderTexture(*m_Texture, posX, posY);
		
	}
	else
	{
		std::cout << "GameObject has no transform!" << std::endl;
		Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
	}
}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}
