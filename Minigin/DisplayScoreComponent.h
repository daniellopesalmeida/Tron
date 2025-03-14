#pragma once
#include "Component.h"
#include "Observer.h"
#include <string>
namespace dae
{
	class TextComponent;
	class DisplayScoreComponent : public Component, public Observer
	{
    public:
        DisplayScoreComponent(GameObject* pOwner);
        ~DisplayScoreComponent() override = default;

        void OnNotify(GameObject* entity, Event event) override;

        void Update(float deltaTime) override;
        void Render() override;
        void FixedUpdate() override;

    private:
        TextComponent* m_TextComponent;
        std::string m_ScoreText;
    
	};
}

