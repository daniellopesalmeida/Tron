#include "TextComponent.h"
#include <stdexcept>
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include <iostream>

dae::TextComponent::TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font)
	:Component(pOwner), m_NeedsUpdate(true), m_Text(text), m_Font(std::move(font)), m_TextTexture(nullptr)
{
	m_pRenderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
	//const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
	//if (surf == nullptr)
	//{
	//	throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	//}
	//auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	//if (texture == nullptr)
	//{
	//	throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	//}
	//SDL_FreeSurface(surf);
	//m_TextTexture = std::make_shared<Texture2D>(texture);
 
}

void dae::TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
		if (m_pRenderComponent)
		{
			m_pRenderComponent->SetTexture(m_TextTexture);
		}
	}
}

void dae::TextComponent::Render() const
{
	
	const auto transform = GetOwner()->GetTransform();
	if (transform != nullptr)
	{
		auto posX = transform->GetPosition().x;
		auto posY = transform->GetPosition().y;
		Renderer::GetInstance().RenderTexture(*m_TextTexture, posX, posY);

	}
	else
	{
		std::cout << "GameObject has no transform!" << std::endl;
		Renderer::GetInstance().RenderTexture(*m_TextTexture, 0, 0);
	}
	
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;

}


