#include "RenderComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include <iostream>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>

dae::RenderComponent::RenderComponent(GameObject* pOwner)
	:Component(pOwner)
{
}

void dae::RenderComponent::Render()
{
	const auto transform = GetOwner()->GetTransform();

	if (!transform)
	{
		std::cout << "GameObject has no transform!" << std::endl;
		Renderer::GetInstance().RenderTexture(*m_Texture, 0, 0);
		return;
	}

	const auto& position = transform->GetWorldPosition();

	// Determine texture size
	glm::ivec2 textureSize = (m_CustomSize.x > 0 && m_CustomSize.y > 0)
		? m_CustomSize
		: m_Texture->GetSize();

	// Render with rotation
	Renderer::GetInstance().RenderTexture(*m_Texture, position.x, position.y,
		static_cast<float>(textureSize.x), static_cast<float>(textureSize.y),
		m_RotationAngle);

}

void dae::RenderComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

void dae::RenderComponent::SetTexture(const std::string& filename,  glm::ivec2& customSize)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_CustomSize = customSize;

}

void dae::RenderComponent::SetTexture(const std::string& filename,  int size)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	m_CustomSize.x = size;
	m_CustomSize.y = size;

}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture,  glm::ivec2& customSize)
{
	m_Texture = texture;
	m_CustomSize = customSize;
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture,  int size)
{
	m_Texture = texture;
	m_CustomSize.x = size;
	m_CustomSize.y = size;
}

glm::ivec2 dae::RenderComponent::GetSize() const
{
	if(m_CustomSize.x > 0 && m_CustomSize.y > 0)
		return m_CustomSize;

	return m_Texture->GetSize();
}

void dae::RenderComponent::SetRotation(float angle)
{
	m_RotationAngle = angle;
}
