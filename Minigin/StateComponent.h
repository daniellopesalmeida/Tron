#pragma once
#include "Component.h"
#include "StateMachine.h"
#include <memory>

namespace dae
{
	class StateComponent final : public Component
	{
	public:
		StateComponent(GameObject* gameObject);
		~StateComponent()=default;

		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other)= delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) noexcept = delete;

		void SetState(std::unique_ptr<StateMachine> newState);

		void Update(float deltaTime) override;

	
	private:
		std::unique_ptr<StateMachine> m_pCurrentState=nullptr;

	};

}