#include "StateComponent.h"
#include "GameObject.h"
#include <memory>

namespace dae
{
	StateComponent::StateComponent(GameObject* pOwner)
		:Component(pOwner)
	{
	}

	void StateComponent::SetState(std::unique_ptr<StateMachine> newState)
	{
		if(m_pCurrentState && typeid(*m_pCurrentState) == typeid(*newState))
		{
			return;
		}
		if (m_pCurrentState)
		{
			m_pCurrentState->OnExit();
		}

		if (newState)
		{
			newState->SetOwner(GetOwner());
			newState->OnEnter();
		}

		m_pCurrentState = std::move(newState);
	}

	void StateComponent::Update(float )
	{
		if (m_pCurrentState)
		{
			m_pCurrentState->Update();
		}
	}

}