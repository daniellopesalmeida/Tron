#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <glm.hpp>
#include <memory>
#include <TextComponent.h>



class TextButtonComponent :public dae::Component
{
public:
	TextButtonComponent(dae::GameObject* pOwner, std::vector<std::string> stringText);
	~TextButtonComponent() = default;

	void Scroll(int dir);
	void Select();

private:
	void UpdateText();
	std::vector<std::string> m_Strings;
	int m_CurrentIndex = 0;
	dae::TextComponent* m_TextComponent;
};

