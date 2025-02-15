#pragma once
#include <memory>
#include <string>
#include "Component.h"
#include <vec2.hpp>

namespace dae
{
	class Texture2D;

	class RenderComponent final : public Component
	{
	public:
		RenderComponent(GameObject* gameObject);
		~RenderComponent() override = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		//void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);


	private:
		
		std::shared_ptr<Texture2D> m_Texture{};
	};
}
