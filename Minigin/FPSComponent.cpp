#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	:Component(pOwner)
{
	m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void dae::FPSComponent::Update(float deltaTime)
{
	//m_Fps = 1 / deltaTime;
	//if (m_pTextComponent)
	//{
	//	m_pTextComponent->SetText("FPS: "+std::to_string(float(m_Fps)) );
	//}
    
    m_ElapsedTime += deltaTime;
    ++m_FrameCount;

    if (m_ElapsedTime >= 1.0f) // 1 second has passed
    {
        m_Fps = (m_FrameCount) / m_ElapsedTime;

        if (m_pTextComponent)
        {
            m_pTextComponent->SetText("FPS: " + std::to_string(static_cast<int>(m_Fps)));
        }

        m_FrameCount = 0;
        m_ElapsedTime -= 1.0f;
    }
}

void dae::FPSComponent::Render()
{
}
