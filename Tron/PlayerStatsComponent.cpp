#include "PlayerStatsComponent.h"
//#include "Subject.h"
#include "Observer.h"
#include "ServiceLocator.h"


PlayerStatsComponent::PlayerStatsComponent(dae::GameObject* pOwner, int maxHealth, int initialScore)
	: Component(pOwner), m_MaxHealth(maxHealth), m_Score(initialScore)
{
    m_Health = m_MaxHealth;
	m_PlayerStatsSubject = std::make_unique<dae::Subject>();
}

void PlayerStatsComponent::AddScore(int amount)
{
    if(m_Health>0)
    {
        m_Score += amount;
        m_PlayerStatsSubject->Notify(GetOwner(), dae::Event::COLLECT_POINTS);
        auto& soundSystem = dae::ServiceLocator::GetSoundSystem();
        soundSystem.Play(3, 0.5f, dae::SoundType::SoundEffect);
    }
}

void PlayerStatsComponent::TakeDamage(int amount)
{
    m_Health -= amount;
    if (m_Health <= 0)
    {
        m_PlayerStatsSubject->Notify(GetOwner(), dae::Event::PLAYER_DIED);
    }
    else
    {
        m_PlayerStatsSubject->Notify(GetOwner(), dae::Event::PLAYER_HIT);
        auto& soundSystem = dae::ServiceLocator::GetSoundSystem();
        soundSystem.Play(2, 0.5f, dae::SoundType::SoundEffect);
    }
}

void PlayerStatsComponent::ResetStats()
{
    m_Health = m_MaxHealth;
    m_Score = 0;
    m_PlayerStatsSubject->Notify(GetOwner(), dae::Event::RESET_ACHIEVEMENTS);
}

std::string PlayerStatsComponent::GetHealthString() const
{
    return std::string(m_Health, '#');
}

void PlayerStatsComponent::AddObserver(dae::Observer* observer)
{
	m_PlayerStatsSubject->AddObserver(observer);
}

void PlayerStatsComponent::RemoveObserver(dae::Observer* observer)
{
	m_PlayerStatsSubject->RemoveObserver(observer);
}
