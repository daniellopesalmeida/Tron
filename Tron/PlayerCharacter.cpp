#include "PlayerCharacter.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include <memory>
#include <iostream>
#include <Scene.h>
#include "ResourceManager.h"
#include "TextComponent.h"
#include "DisplayHealthComponent.h"
#include "DisplayScoreComponent.h"
#include "PlayerStatsComponent.h"
#include <StateComponent.h>

dae::PlayerCharacter::PlayerCharacter(dae::Scene& scene, int x , int y, int playerId)
    :m_PlayerID{playerId}
{
    
    if (m_PlayerID != 1 && m_PlayerID != 2)
    {
        std::cout << "There cant be " << m_PlayerID << " players: max 2" << std::endl;
        return;
    }

    std::string texturePath;
    SDL_Color textColor{};
    std::string playerLabel;
    glm::vec3 scorePos{};
    glm::vec3 healthPos{};

    if (m_PlayerID == 1)
    {
        texturePath = "player1.png";
        textColor = SDL_Color(255, 0, 0);
        playerLabel = "P1";
        healthPos={ 10,50,0 };
        scorePos = { 10,0,0 };

    }
    else // playerId == 2
    {
        texturePath = "player2.png";
        textColor = SDL_Color{ 100, 255, 100 };
        playerLabel = "P2";
        healthPos = { 300,50,0 };
        scorePos = { 300,0,0 };
    }

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
    render->SetTexture(texturePath);

    // Add the DisplayHealthComponent
    m_HealthDisplay = std::make_shared<dae::GameObject>();
    auto fontHealth = dae::ResourceManager::GetInstance().LoadFont("tronFont/tron.ttf", 15);
    m_HealthDisplay->AddComponent<dae::TextComponent>("# ", fontHealth)->SetColor(textColor);
    m_HealthDisplay->AddComponent<DisplayHealthComponent>();
    m_HealthDisplay->SetPosition(healthPos);
    scene.Add(m_HealthDisplay);

    // Add DisplayScoreComponent
    m_ScoreDisplay = std::make_shared<dae::GameObject>();
    m_ScoreDisplay->AddComponent<TextComponent>("Score 0", fontHealth)->SetColor(textColor);
    m_ScoreDisplay->AddComponent<DisplayScoreComponent>();
    m_ScoreDisplay->SetPosition(scorePos);
    scene.Add(m_ScoreDisplay);

    // Set up observers for health and score
    m_GameObject->AddComponent<PlayerStatsComponent>(5)->AddObserver(m_HealthDisplay->GetComponent<DisplayHealthComponent>());
    m_GameObject->GetComponent<PlayerStatsComponent>()->AddObserver(m_ScoreDisplay->GetComponent<DisplayScoreComponent>());
    m_HealthDisplay->GetComponent<dae::TextComponent>()->SetText(m_GameObject->GetComponent<PlayerStatsComponent>()->GetHealthString());

    // Add child text (name or other information)
    auto playerNameText = std::make_shared<dae::GameObject>();
    playerNameText->AddComponent<dae::TextComponent>(playerLabel, fontHealth)->SetColor(textColor);
    auto playerNameTextSize = playerNameText->GetComponent<dae::TextComponent>()->GetSize();
    auto playerTextureSize = m_GameObject->GetComponent<dae::RenderComponent>()->GetSize();
    playerNameText->SetPosition(float(playerTextureSize.x / 2 - playerNameTextSize.x / 2), float(-playerNameTextSize.y - 5));
    m_GameObject->AddChild(playerNameText);

    m_GameObject->AddComponent<dae::StateComponent>();

    scene.Add(m_GameObject);
}
