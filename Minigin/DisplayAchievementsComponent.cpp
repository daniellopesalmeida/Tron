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
	if (event == Event::COLLECT_POINTS)
	{
		if(entity->GetComponent<PlayerStatsComponent>() && !m_AchievementUnlocked)
		{
			if (entity->GetComponent<PlayerStatsComponent>()->GetScore() >= m_AchievementScore)
			{
				SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
				SteamUserStats()->StoreStats();
				m_AchievementUnlocked = true;
			}
		}
	}
	else if (event == Event::RESET_ACHIEVEMENTS)
	{
		std::cout << "Resetting all achievements..." << std::endl;
		SteamUserStats()->ResetAllStats(true);
		SteamUserStats()->StoreStats();
		m_AchievementUnlocked = false;
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
