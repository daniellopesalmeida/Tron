#include "CollisionComponent.h"
#include "Renderer.h"
#include "CollisionManager.h"

namespace dae
{
	CollisionComponent::CollisionComponent(GameObject* pGameObject, const glm::vec2& size, const glm::vec2& offset)
		:Component(pGameObject), m_Size{size},m_Offset{offset}
	{
		dae::CollisionManager::GetInstance().AddColisionComponent(this);
	}

	CollisionComponent::~CollisionComponent()
	{
		dae::CollisionManager::GetInstance().RemoveColisionComponent(this);
	}

	void CollisionComponent::Render()
	{
		if (!m_DebugMode)
			return;

		SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();

		auto pos = GetOwner()->GetTransform()->GetWorldPosition();
		SDL_Rect rect{
			static_cast<int>(pos.x + m_Offset.x),
			static_cast<int>(pos.y + m_Offset.y),
			static_cast<int>(m_Size.x),
			static_cast<int>(m_Size.y)
		};

		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //solid white
		SDL_RenderDrawRect(renderer, &rect);
	}

	const glm::vec2 CollisionComponent::GetPosition() const
	{
		const auto& worldPos = GetOwner()->GetTransform()->GetWorldPosition();
		return glm::vec2{ worldPos.x, worldPos.y } + m_Offset;
	}

	const glm::vec2& CollisionComponent::GetSize() const
	{
		return m_Size;
	}

	void CollisionComponent::SetSize(const glm::vec2& size)
	{
		m_Size = size;
	}

	void CollisionComponent::SetOffset(const glm::vec2& offset)
	{
		m_Offset = offset;
	}

	const glm::vec2& CollisionComponent::GetOffset() const
	{
		return m_Offset;
	}

	void CollisionComponent::SetCollisionCallback(CollisionCallback callback)
	{
		m_Callback = std::move(callback);
	}

	void CollisionComponent::OnCollision(CollisionComponent* other) const
	{
		if (m_Callback)
			m_Callback(const_cast<CollisionComponent*>(this), other);
	}

}