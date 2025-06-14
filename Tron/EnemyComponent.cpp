#include "EnemyComponent.h"
#include <CollisionComponent.h>
#include <CollisionManager.h>
#include <RenderComponent.h>
#include <queue>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <gtx/hash.hpp>
#include <iostream>
#include <Renderer.h>


EnemyComponent::EnemyComponent(dae::GameObject* pOwner)
    : Component(pOwner)
{
	//auto collisionComp = GetOwner()->GetComponent<dae::CollisionComponent>();
    //collisionComp->SetCollisionCallback([](dae::CollisionComponent* self, dae::CollisionComponent* other)
    //        {
    //            auto owner = self->GetOwnerPublic();
    //            if (!owner) return;
    //    
    //            
    //    
    //    
    //        });
}



bool EnemyComponent::AreClose(const glm::vec2& a, const glm::vec2& b, float tolerance)
{
    return glm::length(a - b) < tolerance;
}

std::vector<glm::vec2> EnemyComponent::FindPath(const glm::vec2& start, const glm::vec2& goal)
{

    std::unordered_map<glm::vec2, glm::vec2> cameFrom;
    std::queue<glm::vec2> frontier;
    frontier.push(start);
    cameFrom[start] = start;

    const std::vector<glm::vec2> directions{
        { 0, -35 }, // up
        { 0,  35 }, // down
        {-35,  0 }, // left
        { 35,  0 }, // right
    };

    while (!frontier.empty())
    {
        glm::vec2 current = frontier.front();
        frontier.pop();

        if (AreClose(current, goal))
            break;

        for (const auto& dir : directions)
        {
            glm::vec2 neighbor = current + dir;
            if (std::find(m_Nodes.begin(), m_Nodes.end(), neighbor) == m_Nodes.end())
                continue; // not walkable

            if (cameFrom.find(neighbor) == cameFrom.end())
            {
                frontier.push(neighbor);
                cameFrom[neighbor] = current;
            }
        }
    }

    // Reconstruct path
    std::vector<glm::vec2> path;
    glm::vec2 current = goal;

    if (cameFrom.find(goal) == cameFrom.end())
        return path; // no path

    while (current != start)
    {
        path.push_back(current);
        current = cameFrom[current];
    }

    std::reverse(path.begin(), path.end());

    

    return path;
}

bool EnemyComponent::IsBlocked(const glm::vec2& testPos)
{
    auto myGO = GetOwner();
    auto myCollider = myGO->GetComponent<dae::CollisionComponent>();
    if (!myCollider)
        return false;

    glm::vec2 size = myCollider->GetSize();
    glm::vec2 offset = myCollider->GetOffset();

    glm::vec2 testTopLeft = testPos + offset;

    for (auto* other : dae::CollisionManager::GetInstance().GetCollisionComponents())
    {
        if (!other || other == myCollider)
            continue;

        auto otherGO = other->GetOwnerPublic();
        if (!otherGO || otherGO->GetTag() != "Wall")
            continue;

        glm::vec2 otherPos = other->GetPosition() + other->GetOffset();
        glm::vec2 otherSize = other->GetSize();

        bool xOverlap = testTopLeft.x < otherPos.x + otherSize.x && testTopLeft.x + size.x > otherPos.x;
        bool yOverlap = testTopLeft.y < otherPos.y + otherSize.y && testTopLeft.y + size.y > otherPos.y;

        if (xOverlap && yOverlap)
        {
            return true;
        }
    }

    return false;
}

void EnemyComponent::Update(float deltaTime)
{
    

    if (!m_Target || m_Nodes.empty())
        return;

    auto myPos = GetOwner()->GetTransform()->GetWorldPosition();
    auto playerPos = m_Target->GetTransform()->GetWorldPosition();

    //std::cout << "EnemyPos: " << myPos.x << ", " << myPos.y << "\n";
    //std::cout << "PlayerPos: " << playerPos.x << ", " << playerPos.y << "\n";
    //std::cout << "Path size: " << m_Path.size() << "\n";

    if (m_Path.empty() || AreClose(playerPos, m_Path.back()))
    {
        m_Path = FindPath(myPos, playerPos);
        m_CurrentPathIndex = 0;
    }

    if (m_CurrentPathIndex < m_Path.size())
    {
        glm::vec2 targetNode = m_Path[m_CurrentPathIndex];
        glm::vec2 direction = glm::normalize(targetNode - myPos);

        // restrict to 4-direction movement
        if (std::abs(direction.x) > std::abs(direction.y))
        {
            direction = { direction.x > 0 ? 1.f : -1.f, 0.f };
        }
        else
        {
            direction = { 0.f, direction.y > 0 ? 1.f : -1.f };
        }

        m_Direction = direction;
        glm::vec2 newPos = GetOwner()->GetTransform()->GetWorldPosition() + m_Direction * m_Speed * deltaTime;

        // move only if not blocked
        if (!IsBlocked(newPos))
        {
            GetOwner()->SetPosition(newPos.x, newPos.y);
        }

        // reached target?
        if (AreClose(GetOwner()->GetTransform()->GetWorldPosition(), targetNode, 2.0f))
        {
            ++m_CurrentPathIndex;
        }
    }

}

void EnemyComponent::Render()
{
    SDL_Renderer* renderer = dae::Renderer::GetInstance().GetSDLRenderer();

    auto pos = m_Nodes;
    for(int idx=0;idx<pos.size();++idx)
    {
        SDL_Rect rect{
            static_cast<int>(pos[idx].x-1),
            static_cast<int>(pos[idx].y-1),
            static_cast<int>(2.f),
            static_cast<int>(2.f)

        };
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //solid red
        SDL_RenderDrawRect(renderer, &rect);
    }

   
}

