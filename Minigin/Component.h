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
        virtual void FixedUpdate();

        void Delete() { m_MarkedForDelete = true; }
        bool IsMarkedForDeletion() const { return m_MarkedForDelete; }

        
    protected:

        GameObject* GetOwner() const { return m_pOwner; }

   private:
        GameObject* m_pOwner{ nullptr };
        bool m_MarkedForDelete{ false };
       
    };
}
