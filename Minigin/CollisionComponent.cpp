#include "CollisionComponent.h"

namespace dae
{
	CollisionComponent::CollisionComponent(GameObject* pGameObject, const glm::vec2& size, const glm::vec2& offset)
		:Component(pGameObject)
	{
	}

	const glm::vec2& CollisionComponent::GetPosition() const
	{
		// TODO: insert return statement here
	}

	const glm::vec2& CollisionComponent::GetSize() const
	{
		// TODO: insert return statement here
	}

	void CollisionComponent::SetSize(const glm::vec2& size)
	{
	}

	void CollisionComponent::SetOffset(const glm::vec2& offset)
	{
	}

	const glm::vec2& CollisionComponent::GetOffset() const
	{
		// TODO: insert return statement here
	}

}