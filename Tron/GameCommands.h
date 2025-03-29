#pragma once
#include "Command.h"
#include "PlayerStatsComponent.h"


class GameCommands
{
public:
	class Move final : public dae::GameObjectCommand
	{

	public:
		Move(dae::GameObject* pGameObject, glm::vec2 direction, float speed = 1.f)
			: GameObjectCommand(pGameObject), m_Direction{ direction }, m_Speed{ speed } {
		};

		~Move() = default;

		void Execute(float deltaTime) override
		{
			std::cout << "Command Move executed!" << std::endl;

			auto pos = GetGameObject()->GetTransform()->GetLocalPosition();
			pos.x += m_Direction.x * m_Speed * deltaTime;
			pos.y += m_Direction.y * m_Speed * deltaTime;
			GetGameObject()->SetPosition(pos.x, pos.y);

			//std::cout << "Moved GameObject to (" << pos.x << ", " << pos.y << ")" << std::endl;
		}

	private:
		glm::vec2 m_Direction;
		float m_Speed;
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
};

