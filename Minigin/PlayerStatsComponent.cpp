#include "PlayerStatsComponent.h"
#include "Subject.h"
#include "Observer.h"


dae::PlayerStatsComponent::PlayerStatsComponent(GameObject* pOwner, int maxHealth, int initialScore)
	: Component(pOwner), m_MaxHealth(maxHealth), m_Score(initialScore)
{
    m_Health = m_MaxHealth;
	m_PlayerStatsSubject = std::make_unique<Subject>();
}

void dae::PlayerStatsComponent::AddScore(int amount)
{
    if(m_Health>0)
    {
        m_Score += amount;
        m_PlayerStatsSubject->Notify(GetOwner(), Event::COLLECT_POINTS);
    }
}

void dae::PlayerStatsComponent::TakeDamage(int amount)
{
    m_Health -= amount;
    if (m_Health <= 0)
    {
        m_PlayerStatsSubject->Notify(GetOwner(), Event::PLAYER_DIED);
    }
    else
    {
        m_PlayerStatsSubject->Notify(GetOwner(), Event::PLAYER_HIT);
    }
}

void dae::PlayerStatsComponent::ResetStats()
{
    m_Health = m_MaxHealth;
    m_Score = 0;
    m_PlayerStatsSubject->Notify(GetOwner(), Event::RESET_ACHIEVEMENTS);
}

void dae::PlayerStatsComponent::AddObserver(Observer* observer)
{
	m_PlayerStatsSubject->AddObserver(observer);
}

void dae::PlayerStatsComponent::RemoveObserver(Observer* observer)
{
	m_PlayerStatsSubject->RemoveObserver(observer);
}
