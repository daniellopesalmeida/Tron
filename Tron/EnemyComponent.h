#pragma once
#include "Component.h"
#include "GameObject.h"
#include <glm.hpp>

class EnemyComponent :public dae::Component
{
public:
	EnemyComponent(dae::GameObject* pOwner);
	~EnemyComponent() = default;

	void Update(float deltaTime)override;
	void Render()override;

	void SetTarget(std::shared_ptr<dae::GameObject> target){ m_Target = target; }
	void SetNavigationNodes(std::vector<glm::vec2>& navNodes) { m_Nodes = navNodes; }

private:
	
	bool AreClose(const glm::vec2& a, const glm::vec2& b, float tolerance = 1.0f);
	std::vector<glm::vec2> FindPath(const glm::vec2& start, const glm::vec2& goal);
	bool IsBlocked(const glm::vec2& testPos);

	std::vector<glm::vec2> m_Path;
	size_t m_CurrentPathIndex{ 0 };
	std::vector<glm::vec2> m_Nodes{};
	std::shared_ptr<dae::GameObject> m_Target{};
	glm::vec2 m_Direction{0.f,0.f};
	float m_Speed{ 60.f };
};

