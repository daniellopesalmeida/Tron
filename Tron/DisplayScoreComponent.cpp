#include "DisplayScoreComponent.h"
#include "GameObject.h"
#include "PlayerStatsComponent.h"
//#include "TextComponent.h"

DisplayScoreComponent::DisplayScoreComponent(dae::GameObject* pOwner)
{
	m_TextComponent = pOwner->GetComponent<dae::TextComponent>();
}

void DisplayScoreComponent::OnNotify(dae::GameObject* entity, dae::Event event)
{
    switch (event)
    {
    case dae::Event::COLLECT_POINTS:
    case dae::Event::RESET_ACHIEVEMENTS:
        if (auto statsComponent = entity->GetComponent<PlayerStatsComponent>())
        {
            m_ScoreText = "Score: " + std::to_string(statsComponent->GetScore());
            m_TextComponent->SetText(m_ScoreText);
        }
        break;

    default:
        break;
    }
}

void DisplayScoreComponent::Update(float )
{
}

void DisplayScoreComponent::Render()
{
}

void DisplayScoreComponent::FixedUpdate()
{
}
