#pragma once  
#include "Component.h"  
#include <RenderComponent.h>  
#include <Scene.h>

class WeaponComponent : public dae::Component  
{  
public:  
	WeaponComponent(dae::GameObject* pOwner, dae::Scene& scene, std::string bulletTexture);
	~WeaponComponent() override = default;

	void Update(float deltaTime) override;  
	void Render() override;  
	void FixedUpdate() override;  

	void Shoot();

private:  
	dae::Scene& m_Scene;
	dae::RenderComponent* m_TextureComponent{};
	float m_CurrentAngle{};
	std::string m_BulletTexture{};
};
