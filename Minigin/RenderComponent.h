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
		void Render() override;

		void SetTexture(const std::string& filename);
		void SetTexture(const std::string& filename,  glm::ivec2& customSize);
		void SetTexture(const std::string& filename, int size);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetTexture(std::shared_ptr<Texture2D> texture,  glm::ivec2& customSize);
		void SetTexture(std::shared_ptr<Texture2D> texture, int size);
		

		glm::ivec2 GetSize() const;
		void SetSize(const glm::ivec2& size) { m_CustomSize = size; }
		void SetScale(const glm::vec2& scale) { m_Scale = scale; }
		void SetScale(float uniformScale) { m_Scale = glm::vec2{ uniformScale }; }
		void SetRotation(float angle);
		float GetRotation() { return m_RotationAngle; }

	private:
		
		std::shared_ptr<Texture2D> m_Texture{};
		glm::ivec2 m_CustomSize{ -1, -1 };
		glm::vec2 m_Scale{ 1.0f, 1.0f };
		float m_RotationAngle{ 0.0f };
	};
}
