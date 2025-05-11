#pragma once
#include "StateMachine.h"
#include "memory"
#include "iostream"
#include "GameObject.h"
#include "RenderComponent.h"


enum class PlayerStateType
{
    Up,
    Down,
    Left,
    Right
};


class PlayerState:public dae::StateMachine
{
public:
	virtual void OnDirectionChanged() = 0;
};

class UpState : public PlayerState
{
public:
    void OnEnter() override 
    {
        std::cout << "Entering Up State\n";
        auto renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
        if (renderComponent)
        {
            renderComponent->SetRotation(-90);
        }
    }

    void OnExit() override 
    {
        std::cout << "Exiting Up State\n";
    }

    void Update() override 
    {
        //std::cout << "Updating Up State\n";
    }

    void OnDirectionChanged() override 
    {
        //std::cout << "Direction changed in Up State\n";
    }
};

class DownState : public PlayerState
{
public:
    void OnEnter() override
    {
        std::cout << "Entering Down State\n";
        auto renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
        if (renderComponent)
        {
            renderComponent->SetRotation(90);
        }
    }

    void OnExit() override
    {
        std::cout << "Exiting Down State\n";
    }

    void Update() override
    {
        //std::cout << "Updating Down State\n";
    }

    void OnDirectionChanged() override
    {
        std::cout << "Direction changed in Down State\n";
    }
};

class LeftState : public PlayerState
{
public:
    void OnEnter() override 
    {
        std::cout << "Entering Left State\n";
        auto renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
        if (renderComponent)
        {
            renderComponent->SetRotation(180);
        }
    }

    void OnExit() override 
    {
        std::cout << "Exiting Left State\n";
        
    }

    void Update() override 
    {
        //std::cout << "Updating Left State\n";
    }

    void OnDirectionChanged() override 
    {
        std::cout << "Direction Changed in Down State\n";
    }
};

class RightState : public PlayerState
{
public:
    void OnEnter() override
    {
        std::cout << "Entering Right State\n";
        auto renderComponent = GetOwner()->GetComponent<dae::RenderComponent>();
        if (renderComponent)
        {
            renderComponent->SetRotation(0);
        }
    }

    void OnExit() override
    {
        std::cout << "exiting Right State\n";
    }

    void Update() override
    {
        //std::cout << "Updating Right State\n";
    }

    void OnDirectionChanged() override
    {
        std::cout << "DirectionChanged in Right State\n";
    }
};