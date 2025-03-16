#include "DisplayHealthComponent.h"
#include "GameObject.h" 
#include "PlayerStatsComponent.h"
#include "TextComponent.h"

dae::DisplayHealthComponent::DisplayHealthComponent(GameObject* pOwner)
	:Component(pOwner), m_healthText{""}
{
	
	m_TextComponent = pOwner->GetComponent<TextComponent>();
	//m_healthText=m_TextComponent->GetText();
	
}

void dae::DisplayHealthComponent::OnNotify(GameObject* entity, Event event)
{
    switch (event)
    {
    case Event::PLAYER_HIT:
    case Event::RESET_ACHIEVEMENTS:
        if (auto statsComponent = entity->GetComponent<PlayerStatsComponent>())
        {
            m_healthText = "Health: " + std::to_string(statsComponent->GetHealth());
            m_TextComponent->SetText(m_healthText);
        }
        break;

    case Event::PLAYER_DIED:
        m_healthText = "Player Died!";
        m_TextComponent->SetText(m_healthText);
        break;

    default:
        break;
    }
}

void dae::DisplayHealthComponent::Update(float)
{
}

void dae::DisplayHealthComponent::Render()
{
}

void dae::DisplayHealthComponent::FixedUpdate()
{
}
