#pragma once
#include <string>
#include <Scene.h>
#include <unordered_map>
#include <vec2.hpp>


class LevelCreator final
{
	enum class BlockType 
	{
		Wall=1,
		Path=2,
		Center=6,
		P1=3,
		P2=4,
		Enemy=5
	};

public:
	static std::shared_ptr<dae::GameObject> LoadLevel(dae::Scene& scene, std::string levelPath,
		std::unordered_map<std::string, std::vector<glm::vec2>>& outPositions, glm::vec2 pos = glm::vec2{ 0.f,0.f });

private:
	inline static float m_BlockSize{ 35.f };
};

