#include "WeaponComponent.h"  
#include "GameObject.h"
#include "BulletComponent.h"
#include "SceneManager.h"

WeaponComponent::WeaponComponent(dae::GameObject* pOwner, dae::Scene& scene, std::string bulletTexture)
	:Component(pOwner) , m_CurrentAngle{0.0f} , m_Scene{scene},m_BulletTexture{bulletTexture}
{  
	m_TextureComponent = pOwner->GetComponent<dae::RenderComponent>();  
}  

void WeaponComponent::Update(float deltaTime)
{  
	if (m_TextureComponent)
	{
		m_CurrentAngle += 90.0f * deltaTime;
		m_TextureComponent->SetRotation(m_CurrentAngle);
	}
}  

void WeaponComponent::Render()  
{  
}  

void WeaponComponent::FixedUpdate()  
{  
}

void WeaponComponent::Shoot()
{
    auto bullet = std::make_shared<dae::GameObject>();

    // Get world position of weapon
    auto worldPos = GetOwner()->GetTransform()->GetWorldPosition();

    glm::vec2 offset{ 0.f, 0.f };
    glm::vec2 tipOffset{ 0.f, 0.f };

    if (m_TextureComponent)
    {
        const auto& texSize = m_TextureComponent->GetSize();

        // Center offset of weapon sprite
        offset.x = texSize.x / 2.0f;
        offset.y = texSize.y / 2.0f;

        // Direction based on weapon rotation
        float angleDeg = m_TextureComponent->GetRotation();
        float angleRad = glm::radians(angleDeg);
        glm::vec2 direction = { cosf(angleRad), sinf(angleRad) };

        // Offset to move bullet to the tip of the weapon
        float tipLength = texSize.y / 6.0f;
        tipOffset = direction * tipLength;

        // Set bullet direction
        auto bulletComp = bullet->AddComponent<BulletComponent>();
        bulletComp->SetDirection(direction);
        
    }

    // Final bullet spawn position: center + forward offset
    bullet->SetPosition(worldPos.x + offset.x + tipOffset.x,
        worldPos.y + offset.y + tipOffset.y);

    bullet->AddComponent<dae::RenderComponent>()->SetTexture(m_BulletTexture);
    m_Scene.Add(bullet);
}
