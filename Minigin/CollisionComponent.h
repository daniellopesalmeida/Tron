#pragma once
#include "Component.h"
#include "GameObject.h"
#include <glm.hpp>
#include <functional>

namespace dae
{
	enum class CollisionLayer
	{
		Default,
		Player,
		Enemy,
		Bullet,
		Wall,
		Center
	};

	class CollisionComponent :public Component
	{
	public:
		using CollisionCallback = std::function<void(CollisionComponent*, CollisionComponent*)>;

		CollisionComponent(GameObject* pGameObject, const glm::vec2& size, const glm::vec2& offset = { 0.f, 0.f });
		~CollisionComponent();
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		//void Update(float deltaTime) override;
		//void FixedUpdate() override;
		void Render() override;
		
		const glm::vec2 GetPosition() const;
		const glm::vec2& GetSize() const;

		void SetSize(const glm::vec2& size);
		void SetOffset(const glm::vec2& offset);
		const glm::vec2& GetOffset() const;

		void SetCollisionCallback(CollisionCallback callback);
		void OnCollision(CollisionComponent* other) const;
		GameObject* GetOwnerPublic() const { return GetOwner(); }

		void SetLayer(CollisionLayer layer) { m_Layer = layer; }
		CollisionLayer GetLayer() const { return m_Layer; }

	private:
		glm::vec2 m_Size;
		glm::vec2 m_Offset;
		CollisionCallback m_Callback{};
		bool m_DebugMode{ true };
		CollisionLayer m_Layer{ CollisionLayer::Default };
	};
}

