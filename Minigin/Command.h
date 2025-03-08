#pragma once
#include "GameObject.h"
#include <iostream>

namespace dae
{
	class Command
	{

	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;

	};

	class GameObjectCommand : public Command
	{

	public:
		GameObjectCommand(GameObject* pGameObject) : Command(), m_pGameObject{ pGameObject } {};
		virtual ~GameObjectCommand()=default;


	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }

	private:
		GameObject* m_pGameObject;
	};

    class Move final : public GameObjectCommand
    {

    public:
        Move(GameObject* pGameObject) : GameObjectCommand(pGameObject) {};
        ~Move() = default;

        void Execute() override
        {
            std::cout << "Command Move executed!" << std::endl;
        }

    private:

    };
}

