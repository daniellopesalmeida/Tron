#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
    class Subject;
    class Observer;

	class PlayerStatsComponent : public Component
	{
    public:
        PlayerStatsComponent(GameObject* pOwner, int maxHealth, int initialScore=0);
        ~PlayerStatsComponent() = default;

        void AddScore(int amount);
        void TakeDamage(int amount);
        void ResetStats();

        int GetScore() const { return m_Score; }
        int GetHealth() const { return m_Health; }

        void AddObserver(Observer* observer);
        void RemoveObserver(Observer* observer);

    private:
        int m_MaxHealth;
        int m_Health;
        int m_Score;
        std::unique_ptr<Subject> m_PlayerStatsSubject;
	};
}

