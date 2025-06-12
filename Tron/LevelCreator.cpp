#include "LevelCreator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "GameObject.h"
#include "RenderComponent.h"
#include "Scene.h"

std::shared_ptr<dae::GameObject> LevelCreator::LoadLevel(dae::Scene& scene,
	std::string levelPath,
	std::unordered_map<std::string, std::vector<glm::vec2>>& outPositions, glm::vec2 pos)
{
	auto levelRoot = std::make_shared<dae::GameObject>();
	std::ifstream file(levelPath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open level file: " << levelPath << std::endl;
		return nullptr;
	}

	std::string line;
	int row = 0;

    while (std::getline(file, line))
    {
        std::stringstream lineStream(line);
        int col = 0;
        std::string cell;

        while (std::getline(lineStream, cell, ';'))
        {
            // Clean cell from whitespace
            cell.erase(std::remove_if(cell.begin(), cell.end(), [](unsigned char c) {
                return std::isspace(c);
                }), cell.end());

            if (cell.empty())
            {
                ++col;
                continue;
            }

            int cellValue = std::stoi(cell);
            glm::vec2 localPos = { col * m_BlockSize, row * m_BlockSize };
            glm::vec2 worldPos = localPos + pos;

            switch (static_cast<BlockType>(cellValue))
            {
            case BlockType::Wall:
            {
                auto wall = std::make_shared<dae::GameObject>();
                wall->SetPosition(worldPos.x, worldPos.y);
                wall->AddComponent<dae::RenderComponent>()->SetTexture("Wall.png");
                levelRoot->AddChild(wall);
                break;
            }
            case BlockType::Path:
            {
                auto path = std::make_shared<dae::GameObject>();
                path->SetPosition(worldPos.x, worldPos.y);
                path->AddComponent<dae::RenderComponent>()->SetTexture("Path.png");
                levelRoot->AddChild(path);
                break;
            }
            case BlockType::P1:
            {
                auto path = std::make_shared<dae::GameObject>();
                path->SetPosition(worldPos.x, worldPos.y);
                path->AddComponent<dae::RenderComponent>()->SetTexture("Path.png");
                levelRoot->AddChild(path);
                outPositions["P1"].emplace_back(worldPos);
                break;
            }
            case BlockType::P2:
            {
                auto path = std::make_shared<dae::GameObject>();
                path->SetPosition(worldPos.x, worldPos.y);
                path->AddComponent<dae::RenderComponent>()->SetTexture("Path.png");
                levelRoot->AddChild(path);
                outPositions["P2"].emplace_back(worldPos);
                break;
            }
            case BlockType::Enemy:
            {
                auto path = std::make_shared<dae::GameObject>();
                path->SetPosition(worldPos.x, worldPos.y);
                path->AddComponent<dae::RenderComponent>()->SetTexture("Path.png");
                levelRoot->AddChild(path);
                outPositions["Enemy"].emplace_back(worldPos);
                break;
            }
            case BlockType::Center:
            {
                auto path = std::make_shared<dae::GameObject>();
                path->SetPosition(worldPos.x, worldPos.y);
                path->AddComponent<dae::RenderComponent>()->SetTexture("Path.png");
                levelRoot->AddChild(path);
                outPositions["Center"].emplace_back(worldPos);
                break;
            }
            default:
                break;
            }

            ++col;
        }

        ++row;
    }

	file.close();
    scene.Add(levelRoot);
	return levelRoot;
}
