#include "CollisionManager.h"

void dae::CollisionManager::FixedUpdate()
{
	const size_t count = m_CollisionObjects.size();
	for (size_t i = 0; i < count; ++i)
	{
		CollisionComponent* first = m_CollisionObjects[i];
		if (!first) continue;

		for (size_t j = i + 1; j < count; ++j)
		{
			CollisionComponent* second = m_CollisionObjects[j];
			if (!second) continue;

			if (IsColliding(first, second))
			{
				first->OnCollision(second);
				second->OnCollision(first);
			}
		}
	}
}

void dae::CollisionManager::AddColisionComponent(CollisionComponent* comp)
{
	if (comp && std::find(m_CollisionObjects.begin(), m_CollisionObjects.end(), comp) == m_CollisionObjects.end())
	{
		m_CollisionObjects.push_back(comp);
	}
}

void dae::CollisionManager::RemoveColisionComponent(CollisionComponent* comp)
{
	auto it = std::find(m_CollisionObjects.begin(), m_CollisionObjects.end(), comp);
	if (it != m_CollisionObjects.end())
	{
		m_CollisionObjects.erase(it);
	}
}

void dae::CollisionManager::ClearColisionComponents()
{
	m_CollisionObjects.clear();
}

bool dae::CollisionManager::IsColliding(CollisionComponent* first, CollisionComponent* second)
{
	if (!first || !second)
		return false;

	const glm::vec2 firstPos = first->GetPosition() + first->GetOffset();
	const glm::vec2 secondPos = second->GetPosition() + second->GetOffset();
	const glm::vec2 firstSize = first->GetSize();
	const glm::vec2 secondSize = second->GetSize();

	const bool xOverlap = firstPos.x < secondPos.x + secondSize.x && firstPos.x + firstSize.x > secondPos.x;
	const bool yOverlap = firstPos.y < secondPos.y + secondSize.y && firstPos.y + firstSize.y > secondPos.y;

	return xOverlap && yOverlap;

}
