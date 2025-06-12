#pragma once
#include "Component.h"
#include <glm.hpp>
namespace dae
{
    class TransformComponent;

    class MovementComponent : public Component
    {
    public:
        MovementComponent(GameObject* pOwner);
        ~MovementComponent() override = default;
        MovementComponent(const MovementComponent& other) = delete;
        MovementComponent(MovementComponent&& other) = delete;
        MovementComponent& operator=(const MovementComponent& other) = delete;
        MovementComponent& operator=(MovementComponent&& other) = delete;

        void SetDirection(const glm::vec2& dir) { m_Direction = dir; }
        void SetSpeed(float speed) { m_Speed = speed; }
        void Stop() { m_Direction = glm::vec2{ 0.f, 0.f }; }

        void Update(float deltaTime)override;


    private:
        TransformComponent* m_Transform{};
        glm::vec2 m_Direction{ 0.f, 0.f };
        float m_Speed{ 100.f };
    };
}

