#pragma once
#include "GameObject.h"

namespace dae
{
	class PlayerCharacter
	{
    public:
        PlayerCharacter(int x,int y);
        ~PlayerCharacter()=default;

        std::shared_ptr<GameObject> GetPlayer() { return m_GameObject; }

    private:
        std::shared_ptr<GameObject> m_GameObject;
       
    };
	

}