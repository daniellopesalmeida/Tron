#pragma once
#include "Component.h"

namespace dae
{

	class TrashTheCacheComponent : public Component
	{
	public:
		TrashTheCacheComponent(GameObject* pOwner);
		~TrashTheCacheComponent() override = default;
		TrashTheCacheComponent(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent(TrashTheCacheComponent&& other) = delete;
		TrashTheCacheComponent& operator=(const TrashTheCacheComponent& other) = delete;
		TrashTheCacheComponent& operator=(TrashTheCacheComponent&& other) = delete;

		void Render();
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
		void Ex2Alt();
	};
}

