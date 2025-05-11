#include "PlayerCharacter.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include <memory>
#include <iostream>

dae::PlayerCharacter::PlayerCharacter(int x , int y)
{
    // Create the GameObject
    m_GameObject = std::make_shared<GameObject>();
    auto transform = m_GameObject->GetComponent<TransformComponent>();
    if (transform)
    {
        transform->SetPosition(static_cast<float>(x), static_cast<float>(y));
    }
    else
    {
        std::cout << "Player character has no transform!" << std::endl;
    }
    
    auto render = m_GameObject->AddComponent<RenderComponent>();
    render->SetTexture("redTank.png");

}
