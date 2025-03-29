#pragma once
#include "Component.h"
#include "Observer.h"
#include <string>
#include "TextComponent.h"

    class TextComponent;
	class DisplayHealthComponent : public dae::Component, public dae::Observer
	{
    public:
        DisplayHealthComponent(dae::GameObject* pOwner);
        ~DisplayHealthComponent() override = default;

        void OnNotify(dae::GameObject* entity, dae::Event event) override;

        void Update(float deltaTime)override;
        void Render() override;
        void FixedUpdate()override;

    private:
        dae::TextComponent* m_TextComponent;
        std::string m_healthText;
	};


