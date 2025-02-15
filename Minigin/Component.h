#pragma once

namespace dae
{
    class GameObject; 

    class Component
    {
    public:
        Component(GameObject* pOwner = nullptr);
        virtual ~Component() = default;

        Component(const Component&) = delete;
        Component(Component&&) noexcept = delete;
        Component& operator=(const Component&) = delete;
        Component& operator=(Component&&) noexcept = delete;

        virtual void Update(float deltaTime);
        virtual void Render() const;

        GameObject* GetOwner() const { return m_pOwner; }

    protected:
        GameObject* m_pOwner{ nullptr };
    };
}
