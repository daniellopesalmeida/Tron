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
	for (const auto& child : m_pChildren)
	{
		child->Update(deltaTime);
	}

	for (const auto& comp : m_Components)
	{
		if (comp == nullptr) continue;
		if (!comp->IsMarkedForDeletion())
		{
			comp->Update(deltaTime);
		}
		else
		{
			RemoveComponent(&comp);
		}
	}
}

void dae::GameObject::FixedUpdate()
{
	for (const auto& comp : m_Components)
	{
		if (comp == nullptr) continue;
		if (!comp->IsMarkedForDeletion())
		{
			comp->FixedUpdate();
		}
		else
		{
			RemoveComponent(&comp);
		}
	}
}

void dae::GameObject::Render() const
{	
	for (const auto& comp : m_Components) comp->Render();

	for (const auto& child : m_pChildren)
	{
		child->Render();
	}
}


void dae::GameObject::SetPosition(float x, float y,float z)
{
	m_Transform->SetPosition(x, y, z);
}

void dae::GameObject::SetPosition(glm::vec3 position)
{
	m_Transform->SetPosition(position);
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent, bool keepWorldPos)
{
	//Check if the new parent is valid (not itself or one of its children)
	//Update position, rotation and scale
	//Remove itself from the previous parent (RemoveChild ? ).
	//Set the given parent on itself.
	//Add itself as a child to the given parent(AddChild ? ).
	if (parent)
	{
		if (keepWorldPos)
		{
			
			m_Transform->SetPosition(m_Transform->GetWorldPosition() - parent->GetTransform()->GetWorldPosition());
		}
		m_Transform->SetPosDirty();
		m_Transform->SetParent(parent->GetTransform());
	}
	else
	{
		m_Transform->SetPosition(m_Transform->GetWorldPosition());
	}

	if (m_Parent)
	{
		m_Parent->RemoveChildFromContainer(this->shared_from_this());
	}

	m_Parent = parent.get();

	if (m_Parent)
	{
		m_Parent->AddChildToContainer(this->shared_from_this());
	}

	
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child, bool keepWorldPos)
{
	child->SetParent(this->shared_from_this(),keepWorldPos);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
    auto it = std::find(m_pChildren.begin(), m_pChildren.end(), child);
    if (it != m_pChildren.end())
    {
        m_pChildren.erase(it);
    }
}

void dae::GameObject::AddChildToContainer(std::shared_ptr<dae::GameObject> child)
{
	m_pChildren.emplace_back(child);
}

void dae::GameObject::RemoveChildFromContainer(std::shared_ptr<dae::GameObject> child)
{
	
	std::erase(m_pChildren, child);
}

void dae::GameObject::PrintNrChildren(std::string name)
{
	std::cout << "nr of children of " <<name<<": "<< m_pChildren.size() << std::endl;
}


