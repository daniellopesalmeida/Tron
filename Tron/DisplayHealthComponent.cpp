#include "DisplayHealthComponent.h"
#include "GameObject.h" 
#include "PlayerStatsComponent.h"


DisplayHealthComponent::DisplayHealthComponent(dae::GameObject* pOwner)
	:Component(pOwner), m_healthText{""}
{
	
	m_TextComponent = pOwner->GetComponent<dae::TextComponent>();
	//m_healthText=m_TextComponent->GetText();
	
}

void DisplayHealthComponent::OnNotify(dae::GameObject* entity, dae::Event event)
{
    switch (event)
    {
    case dae::Event::PLAYER_HIT:
    case dae::Event::RESET_ACHIEVEMENTS:
        if (auto statsComponent = entity->GetComponent<PlayerStatsComponent>())
        {
            m_healthText = "Health: " + std::to_string(statsComponent->GetHealth());
            m_TextComponent->SetText(m_healthText);
        }
        break;

    case dae::Event::PLAYER_DIED:
        m_healthText = "Player Died!";
        m_TextComponent->SetText(m_healthText);
        break;

    default:
        break;
    }
}

void DisplayHealthComponent::Update(float)
{
}

void DisplayHealthComponent::Render()
{
}

void DisplayHealthComponent::FixedUpdate()
{
}
