#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <iostream>


dae::GameObject::GameObject()

{
	m_Transform = AddComponent<TransformComponent>();
}

dae::GameObject::~GameObject()
{
	

}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& comp : m_Components) comp->Update(deltaTime);
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_Components) comp->Render();
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform->SetPosition(x, y, 0.0f);
}
