#include "WeaponComponent.h"  
#include "GameObject.h"
#include "BulletComponent.h"
#include "CollisionComponent.h"
#include "SceneManager.h"
#include <iostream>
#include "PlayerStatsComponent.h"

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
    //tag
    auto tag = GetOwner()->GetTag();
    bullet->SetTag("Bullet" + tag);
    std::cout << "bullet tag: " << bullet->GetTag() << std::endl;

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
        float tipLength = 0.f; //texSize.y / 6.0f;
        tipOffset = direction * tipLength;

        // Set bullet direction
        auto bulletComp = bullet->AddComponent<BulletComponent>();
        bulletComp->SetDirection(direction);
        
    }

    // Final bullet spawn position: center + forward offset
    bullet->SetPosition(worldPos.x + offset.x + tipOffset.x,
        worldPos.y + offset.y + tipOffset.y);

    bullet->AddComponent<dae::RenderComponent>()->SetTexture(m_BulletTexture);
    glm::ivec2 collisionOffset{ 3.f,3.f };
    auto collision=bullet->AddComponent<dae::CollisionComponent>(bullet->GetComponent<dae::RenderComponent>()->GetSize()-collisionOffset*2);
    collision->SetOffset(collisionOffset);
    // Set collision callback 
    auto bulletComp=bullet->GetComponent<BulletComponent>();

    collision->SetCollisionCallback(
        [bulletComp](dae::CollisionComponent* self, dae::CollisionComponent* other)
        {
            auto otherGO = other->GetOwnerPublic();
            auto selfGO = self->GetOwnerPublic();
            if (!otherGO || !selfGO || !bulletComp) return;

            const std::string otherTag = otherGO->GetTag();
            const std::string bulletTag = selfGO->GetTag();

            //std::cout << "Collision detected! Other tag: " << otherTag << " Bullet tag: " << bulletTag << std::endl;

            // --- Player/enemy hit logic ---
            if (bulletTag != "Bullet" + otherTag)
            {
                if (auto stats = otherGO->GetComponent<PlayerStatsComponent>())
                {
                    std::cout << "Hit player! Taking damage.\n";
                    stats->TakeDamage(1);
                    stats->AddScore(100);
                    selfGO->Delete();  // Delete bullet
                    return;
                }
            }

            // --- Bounce logic ---
            if (otherTag == "Wall") 
            {
                selfGO->SetPosition(bulletComp->GetLastPosition().x, bulletComp->GetLastPosition().y);

                auto bulletPos = bulletComp->GetLastPosition();  // use last pos for accuracy
                auto otherPos = otherGO->GetTransform()->GetWorldPosition();
                auto diff = bulletPos - glm::vec2{ otherPos.x,otherPos.y };

                glm::vec2 normal;
                if (std::abs(diff.x) > std::abs(diff.y))
                    normal = glm::vec2((diff.x > 0) ? 1.0f : -1.0f, 0.0f);
                else
                    normal = glm::vec2(0.0f, (diff.y > 0) ? 1.0f : -1.0f);

                glm::vec2 incomingDir = bulletComp->GetDirection();
                glm::vec2 reflectedDir = incomingDir - 2.0f * glm::dot(incomingDir, normal) * normal;

                bulletComp->SetDirection(glm::normalize(reflectedDir));
                bulletComp->IncrementBounce();
                
            }
        });

    

    m_Scene.Add(bullet);
}
