#include "EnemyCharacter.h"
#include "GameObject.h"
#include <iostream>
#include <RenderComponent.h>
#include <CollisionComponent.h>
#include "EnemyComponent.h"

EnemyCharacter::EnemyCharacter(dae::Scene& scene, float x, float y, int maxLife)
	:m_MaxLife{maxLife}
{
    std::string texturePath{ "Recognizer.png" };
	std::string bulletTexturePath{"BulletNPC.png"};

	m_GameObject = std::make_shared<dae::GameObject>();
    
	//set pos
    auto transform = m_GameObject->GetComponent<dae::TransformComponent>();
    if (transform)
    {
        transform->SetPosition(static_cast<float>(x), static_cast<float>(y));
    }
    else
    {
        std::cout << "Enemy character has no transform!" << std::endl;
    }
    //add texture
    auto render = m_GameObject->AddComponent<dae::RenderComponent>();
    render->SetTexture(texturePath);
    auto enemySize = render->GetSize();
    
    //add tag
    m_GameObject->SetTag("Enemy");

    //add collision comp
    glm::vec2 offset{ 2.f, 2.f };
    m_GameObject->AddComponent<dae::CollisionComponent>(glm::vec2{ float(enemySize.x), float(enemySize.y) });
   
    
    m_GameObject->AddComponent<EnemyComponent>();
    scene.Add(m_GameObject);
}

void EnemyCharacter::SetTarget(std::shared_ptr<dae::GameObject> player)
{
    m_GameObject->GetComponent<EnemyComponent>()->SetTarget(player);
}


