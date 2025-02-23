#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:

		FPSComponent(GameObject* pOwner);
		~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		float getFPS() const { return m_Fps; }

	private:

		float m_Fps{};
		float m_ElapsedTime{};
		float m_FrameCount{};
		TextComponent* m_pTextComponent;
	};
}
