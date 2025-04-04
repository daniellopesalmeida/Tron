#pragma once
#include "Component.h"
#include <vector>



	class ThrashTheCacheComponent final : public dae::Component
	{
	public:
		ThrashTheCacheComponent(dae::GameObject* pOwner);
		~ThrashTheCacheComponent() override = default;
		ThrashTheCacheComponent(const ThrashTheCacheComponent& other) = delete;
		ThrashTheCacheComponent(ThrashTheCacheComponent&& other) = delete;
		ThrashTheCacheComponent& operator=(const ThrashTheCacheComponent& other) = delete;
		ThrashTheCacheComponent& operator=(ThrashTheCacheComponent&& other) = delete;

		void Render() override;
		void Update(float deltaTime);
		void FixedUpdate();

		struct Transform
		{
			float matrix[16] = 
			{
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1 
			};
		};

		class GameObject3D
		{
		public:
			Transform local;
			int id{};
		};

		class GameObject3DALT
		{
		public:
			Transform* local;
			int id{};
		};

	private:

		void Ex1();
		void Ex2();

		void Ex1Calc(int sampleSize);
		void Ex2Calc(int sampleSize);
		void Ex2AltCalc(int sampleSize);

		std::vector<float> m_Ex1XData{};
		std::vector<float> m_Ex1YData{};

		std::vector<float> m_Ex2XData{};
		std::vector<float> m_Ex2YData{};

		std::vector<float> m_Ex2XAltData{};
		std::vector<float> m_Ex2YAltData{};
	};


