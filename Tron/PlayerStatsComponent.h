#pragma once
#include "Component.h"
#include "Subject.h"
#include <memory>
#include <string>


    class Subject;
    class Observer;

	class PlayerStatsComponent : public dae::Component
	{
    public:
        PlayerStatsComponent(dae::GameObject* pOwner, int maxHealth, int initialScore=0);
        ~PlayerStatsComponent() = default;

        void AddScore(int amount);
        void TakeDamage(int amount);
        void ResetStats();

        int GetScore() const { return m_Score; }
        int GetHealth() const { return m_Health; }
        std::string GetHealthString() const;

        void AddObserver(dae::Observer* observer);
        void RemoveObserver(dae::Observer* observer);

    private:
        int m_MaxHealth;
        int m_Health;
        int m_Score;
        std::unique_ptr<dae::Subject> m_PlayerStatsSubject;
	};


