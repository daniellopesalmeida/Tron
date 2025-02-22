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

void dae::GameObject::FixedUpdate()
{
	for (auto& comp : m_Components) comp->FixedUpdate();
}

void dae::GameObject::Render() const
{
	for (auto& comp : m_Components) comp->Render();
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform->SetPosition(x, y, 0.0f);
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	//Check if the new parent is valid (not itself or one of its children)
	//Update position, rotation and scale
	//Remove itself from the previous parent (RemoveChild ? ).
	//Set the given parent on itself.
	//Add itself as a child to the given parent(AddChild ? ).

	if (parent.get() == this || std::find(m_pChildren.begin(), m_pChildren.end(), parent) != m_pChildren.end())
	{
		std::cerr << "Invalid parent assignment." << std::endl;
		return;
	}

	if (m_Parent)
	{
		m_Parent->RemoveChild(this->shared_from_this());
	}

	m_Parent = parent.get();

	if (m_Parent)
	{
		m_Parent->AddChild(this->shared_from_this());
	}

	
}

void dae::GameObject::AddChild(std::shared_ptr<dae::GameObject> child)
{
	child->SetParent(this->shared_from_this());
	m_pChildren.push_back(child);
}

void dae::GameObject::RemoveChild(std::shared_ptr<dae::GameObject> child)
{
	
	std::erase(m_pChildren, child);
}
