#include "DisplayScoreComponent.h"
#include "GameObject.h"
#include "PlayerStatsComponent.h"
#include "TextComponent.h"

dae::DisplayScoreComponent::DisplayScoreComponent(GameObject* pOwner)
{
	m_TextComponent = pOwner->GetComponent<TextComponent>();
}

void dae::DisplayScoreComponent::OnNotify(GameObject* entity, Event event)
{
    if (event == Event::COLLECT_POINTS)
    {
        if (auto statsComponent = entity->GetComponent<PlayerStatsComponent>())
        {
            m_ScoreText = "Score: " + std::to_string(statsComponent->GetScore());
            m_TextComponent->SetText(m_ScoreText);
        }
    }
    if (event == Event::RESET_ACHIEVEMENTS)
    {
        if (auto statsComponent = entity->GetComponent<PlayerStatsComponent>())
        {
            m_ScoreText = "Score: " + std::to_string(statsComponent->GetScore());
            m_TextComponent->SetText(m_ScoreText);
        }
    }
}

void dae::DisplayScoreComponent::Update(float )
{
}

void dae::DisplayScoreComponent::Render()
{
}

void dae::DisplayScoreComponent::FixedUpdate()
{
}
