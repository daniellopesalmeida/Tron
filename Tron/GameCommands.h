#pragma once
#include "Command.h"
#include "PlayerStatsComponent.h"
#include "ServiceLocator.h"
#include <StateComponent.h>
#include "PlayerState.h"
#include <memory>
#include "WeaponComponent.h"
#include <MovementComponent.h>


class Move final : public dae::GameObjectCommand
{

public:
	Move(dae::GameObject* pGameObject, glm::vec2 direction, float speed = 1.f)
		: GameObjectCommand(pGameObject), m_Direction{ direction }, m_Speed{ speed } 
	{};

	~Move() = default;

	void Execute(float) override
	{
		auto moveComp = GetGameObject()->GetComponent<dae::MovementComponent>();
		if (moveComp)
		{
			moveComp->SetSpeed(m_Speed);
			moveComp->SetDirection(m_Direction);
		}
		//std::cout << "Command Move executed!" << std::endl;

		//auto pos = GetGameObject()->GetTransform()->GetLocalPosition();
		//pos.x += m_Direction.x * m_Speed * deltaTime;
		//pos.y += m_Direction.y * m_Speed * deltaTime;
		//GetGameObject()->SetPosition(pos.x, pos.y);
		//
		////std::cout << "Moved GameObject to (" << pos.x << ", " << pos.y << ")" << std::endl;
		// Get the StateComponent attached to the GameObject
		auto stateComponent = GetGameObject()->GetComponent<dae::StateComponent>();
		if (stateComponent)
		{
			// Determine the state to switch to based on direction
			if (m_Direction.y < 0)
			{
				// Moving up
				stateComponent->SetState(std::make_unique<UpState>());

			}
			else if (m_Direction.y > 0)
			{
				// Moving down
				stateComponent->SetState(std::make_unique<DownState>());

			}
			else if (m_Direction.x > 0)
			{
				// Moving right
				stateComponent->SetState(std::make_unique<RightState>());

			}
			else if (m_Direction.x < 0)
			{
				// Moving left
				stateComponent->SetState(std::make_unique<LeftState>());

			}
		}
	
	}

private:
	glm::vec2 m_Direction;
	float m_Speed;
};

class StopMove final : public dae::GameObjectCommand
{
public:
	StopMove(dae::GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
	}

	void Execute(float) override
	{
		auto moveComp = GetGameObject()->GetComponent<dae::MovementComponent>();
		if (moveComp)
		{
			std::cout << "StopMoving!" << std::endl;
			moveComp->Stop();
		}
	}
};

class Debug final : public dae::GameObjectCommand
{

public:
	Debug(dae::GameObject* pGameObject, std::string message)
		: GameObjectCommand(pGameObject), m_Message(message)
	{
	};

	~Debug() = default;

	void Execute(float) override
	{
		std::cout << "[Debug] Key Pressed: " << m_Message << std::endl;

	}

private:
	std::string m_Message;
};

class TakeDamage final : public dae::GameObjectCommand
{

public:
	TakeDamage(dae::GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
	};

	~TakeDamage() = default;

	void Execute(float) override
	{

		GetGameObject()->GetComponent<PlayerStatsComponent>()->TakeDamage(1);
	}

private:

};

class IncreaseScore final : public dae::GameObjectCommand
{

public:
	IncreaseScore(dae::GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
	};

	~IncreaseScore() = default;

	void Execute(float) override
	{

		GetGameObject()->GetComponent<PlayerStatsComponent>()->AddScore(20);
		
	}

private:

};

class ResetAchievements : public dae::GameObjectCommand
{
public:
	ResetAchievements(dae::GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
	}
	void Execute(float) override
	{
		GetGameObject()->GetComponent<PlayerStatsComponent>()->ResetStats();
	}
};

class PauseSounds final : public dae::Command
{
public:
	PauseSounds() = default;
	void Execute(float) override 
	{
		
		auto& ss = dae::ServiceLocator::GetSoundSystem();
		if (m_Paused)
		{
			ss.UnpauseSound();
			m_Paused = !m_Paused;
		}
		else
		{
			ss.PauseSound();
			m_Paused = !m_Paused;
		}
	}

private:
	bool m_Paused = false;
};

class Shoot final : public dae::GameObjectCommand
{
public:
	Shoot(dae::GameObject* pGameObject)
		: GameObjectCommand(pGameObject)
	{
	}

	~Shoot() = default;

	void Execute(float) override
	{
		auto weapon = GetGameObject()->GetComponent<WeaponComponent>();
		if (weapon)
		{
			weapon->Shoot();
			std::cout << "Shoot!" << std::endl;
		}
		else
		{
			std::cout << "No WeaponComponent!" << std::endl;
		}
	}
};
