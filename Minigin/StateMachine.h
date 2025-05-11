#pragma once

namespace dae
{
    class GameObject;
	class StateMachine
	{
	public:
		StateMachine()=default;
		virtual ~StateMachine() = default;

		StateMachine(const StateMachine& other) = delete;
		StateMachine(StateMachine&& other) = delete;
		StateMachine& operator=(const StateMachine& other) = delete;
		StateMachine& operator=(StateMachine&& other) = delete;

		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		virtual void Update() = 0;
		
		GameObject* GetOwner() const { return m_pOwner; }
		void SetOwner(GameObject* owner) { m_pOwner = owner; }
	private:
		GameObject* m_pOwner{};
    };
}
