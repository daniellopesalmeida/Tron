#pragma once
#include "Singleton.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include <vector>

namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		
		//void Update(float deltaTime);
		void FixedUpdate();

		void AddColisionComponent(CollisionComponent* comp);
		void RemoveColisionComponent(CollisionComponent* comp);
		void ClearColisionComponents();

		std::vector<CollisionComponent*> GetCollisionComponents() { return m_CollisionObjects; }

	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		std::vector<CollisionComponent*> m_CollisionObjects{};
		bool IsColliding(CollisionComponent* first, CollisionComponent* second);
	};
}

