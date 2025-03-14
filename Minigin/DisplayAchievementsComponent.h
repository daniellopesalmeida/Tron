#pragma once
#include <steam_api.h>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class DisplayAchievementsComponent : public Component, public Observer
	{
	public:
		DisplayAchievementsComponent(GameObject* pOwner, int achievScore);
		~DisplayAchievementsComponent()override = default;

		void OnNotify(GameObject* entity, Event event) override;

		void Update(float deltaTime)override;
		void Render() override;
		void FixedUpdate()override;

	private:
		int m_AchievementScore;
		bool m_AchievementUnlocked;
	};
}

