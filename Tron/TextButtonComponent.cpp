#include "TextButtonComponent.h"
#include "GameMode.h"
#include "SceneManager.h"
#include <iostream>



TextButtonComponent::TextButtonComponent(dae::GameObject* pOwner, std::vector<std::string> stringText)
	:Component(pOwner), m_Strings{stringText}, m_CurrentIndex{ 0 }
{
	m_TextComponent = GetOwner()->GetComponent<dae::TextComponent>();
	UpdateText(); // Set initial text
}

void TextButtonComponent::Scroll(int dir)
{
	if (m_Strings.empty()) return;

	m_CurrentIndex += dir;
	if (m_CurrentIndex < 0) m_CurrentIndex = static_cast<int>(m_Strings.size()) - 1;
	if (m_CurrentIndex >= static_cast<int>(m_Strings.size())) m_CurrentIndex = 0;
	std::cout << "dir: " << dir << std::endl;
	UpdateText();
}

void TextButtonComponent::Select()
{
	if (m_Strings.empty()) return;

	const std::string& selected = m_Strings[m_CurrentIndex];

	if (selected == "Single Player") 
	{
		std::cout << "selected: " << selected << std::endl;
		dae::SceneManager::GetInstance().SetScene("SinglePlayer");
	}
	else if (selected == "Versus") 
	{
		std::cout << "selected: " << selected << std::endl;
		dae::SceneManager::GetInstance().SetScene("VersusMode");
	}
}

void TextButtonComponent::UpdateText()
{
	if (m_TextComponent) 
	{
		m_TextComponent->SetText(m_Strings[m_CurrentIndex]);
	}
}
