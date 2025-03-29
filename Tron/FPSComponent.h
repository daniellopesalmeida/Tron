#pragma once
#include "Component.h"
#include "TextComponent.h"


	class TextComponent;

	class FPSComponent final : public dae::Component
	{
	public:

		FPSComponent(dae::GameObject* pOwner);
		~FPSComponent() override = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Render() override;

		float getFPS() const { return m_Fps; }

	private:

		float m_Fps{};
		float m_ElapsedTime{};
		float m_FrameCount{};
		dae::TextComponent* m_pTextComponent;
	};

