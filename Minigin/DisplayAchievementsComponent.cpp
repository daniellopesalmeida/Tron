#include "DisplayAchievementsComponent.h"
#include "GameObject.h"
//#include "Observer.h"
#include "PlayerStatsComponent.h"
#include <iostream>


dae::DisplayAchievementsComponent::DisplayAchievementsComponent(GameObject* pOwner,int achievScore)
	:Component(pOwner), m_AchievementScore{ achievScore }, m_AchievementUnlocked{false}
{
}

void dae::DisplayAchievementsComponent::OnNotify(GameObject* entity, Event event)
{
    switch (event)
    {
    case Event::COLLECT_POINTS:
    {
        auto statsComponent = entity->GetComponent<PlayerStatsComponent>();
        if (statsComponent && !m_AchievementUnlocked && statsComponent->GetScore() >= m_AchievementScore)
        {
            SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
            SteamUserStats()->StoreStats();
            m_AchievementUnlocked = true;
        }
        break;
    }

    case Event::RESET_ACHIEVEMENTS:
        std::cout << "Resetting all achievements..." << std::endl;
        SteamUserStats()->ResetAllStats(true);
        SteamUserStats()->StoreStats();
        m_AchievementUnlocked = false;
        break;

    default:
        break;
    }
}

void dae::DisplayAchievementsComponent::Update(float )
{
}

void dae::DisplayAchievementsComponent::Render()
{
}

void dae::DisplayAchievementsComponent::FixedUpdate()
{
}
