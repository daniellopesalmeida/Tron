#pragma once
#include "GameObject.h"
#include <Scene.h>


namespace dae
{
	class PlayerCharacter
	{
    public:
        PlayerCharacter(dae::Scene& scene, float x, float y,int playerId=1, int maxHealth=3);
        ~PlayerCharacter()=default;
        PlayerCharacter(const PlayerCharacter& other) = delete;
        PlayerCharacter(PlayerCharacter&& other) = delete;
        PlayerCharacter& operator=(const PlayerCharacter& other) = delete;
        PlayerCharacter& operator=(PlayerCharacter&& other) = delete;

        std::shared_ptr<GameObject> GetPlayer() { return m_GameObject; }
        int GetPlayerId() { return m_PlayerID; }
        std::shared_ptr<GameObject> GetWeapon() { return m_WeaponObject; }


    private:
        std::shared_ptr<dae::GameObject> m_GameObject;
        std::shared_ptr<dae::GameObject> m_HealthDisplay;
        std::shared_ptr<dae::GameObject> m_ScoreDisplay;
        std::shared_ptr<dae::GameObject> m_WeaponObject;
        int m_PlayerID{};
        int m_PlayerMaxHealth{};
       
    };
	

}