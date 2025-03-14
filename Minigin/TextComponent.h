#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <SDL.h>
#include "Transform.h"
#include "GameObject.h"
#include "RenderComponent.h"

namespace dae
{
    class Font;
    class GameObject;

    class TextComponent : public Component
    {
    public:
        TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font);
        virtual ~TextComponent() = default;

        TextComponent(const TextComponent& other) = delete;
        TextComponent(TextComponent&& other) = delete;
        TextComponent& operator=(const TextComponent& other) = delete;
        TextComponent& operator=(TextComponent&& other) = delete;

        void Update(float deltaTime) override;
        void Render() override;

        void SetText(const std::string& text);
        void SetColor(const SDL_Color color);
        const std::string& GetText() const { return m_Text; }
       

    private:
        std::string m_Text;
        std::shared_ptr<Font> m_Font; 
        std::shared_ptr<Texture2D> m_TextTexture; 
        SDL_Color m_Color{ 255,255,255,255 };
        bool m_NeedsUpdate; 
        RenderComponent* m_pRenderComponent;
        
    };
}


