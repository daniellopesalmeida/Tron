#pragma once
#include "GameObject.h"
#include <Scene.h>


namespace dae
{
	class PlayerCharacter
	{
    public:
        PlayerCharacter(dae::Scene& scene,int x,int y,int playerId=1);
        ~PlayerCharacter()=default;
        PlayerCharacter(const PlayerCharacter& other) = delete;
        PlayerCharacter(PlayerCharacter&& other) = delete;
        PlayerCharacter& operator=(const PlayerCharacter& other) = delete;
        PlayerCharacter& operator=(PlayerCharacter&& other) = delete;

        std::shared_ptr<GameObject> GetPlayer() { return m_GameObject; }
        int GetPlayerId() { return m_PlayerID; }

    private:
        std::shared_ptr<GameObject> m_GameObject;
        std::shared_ptr<dae::GameObject> m_HealthDisplay;
        std::shared_ptr<dae::GameObject> m_ScoreDisplay;
        int m_PlayerID{};
       
    };
	

}