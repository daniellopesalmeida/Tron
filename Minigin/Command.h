#pragma once
#include "GameObject.h"
#include <iostream>
//#include "PlayerStatsComponent.h"

namespace dae
{
	class Command
	{

	public:
		virtual ~Command() = default;

		virtual void Execute(float deltaTime) = 0;

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

    
}

