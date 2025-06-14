#pragma once

#include <Scene.h>

class EnemyCharacter
{
public:
	EnemyCharacter(dae::Scene& scene, float x, float y,int maxLife=1 );
    ~EnemyCharacter() = default;
    
    EnemyCharacter(const EnemyCharacter& other) = delete;
    EnemyCharacter(EnemyCharacter&& other) = delete;
    EnemyCharacter& operator=(const EnemyCharacter& other) = delete;
    EnemyCharacter& operator=(EnemyCharacter&& other) = delete;

    void SetTarget(std::shared_ptr<dae::GameObject> player);
    std::shared_ptr<dae::GameObject> GetEnemy() { return m_GameObject; }

private:
    std::shared_ptr<dae::GameObject> m_GameObject;
    int m_MaxLife{};
};

