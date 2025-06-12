#pragma once
#include "Component.h"
#include "GameObject.h"
#include <glm.hpp>

namespace dae
{
	class CollisionComponent :public Component
	{
	public:
		CollisionComponent(GameObject* pGameObject, const glm::vec2& size, const glm::vec2& offset = { 0.f, 0.f });
		~CollisionComponent() =default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		//void Update(float deltaTime) override;
		//void FixedUpdate() override;
		
		const glm::vec2& GetPosition() const;
		const glm::vec2& GetSize() const;

		void SetSize(const glm::vec2& size);
		void SetOffset(const glm::vec2& offset);
		const glm::vec2& GetOffset() const;

	private:

	};
}

