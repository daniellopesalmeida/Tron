#pragma once
namespace dae
{
	enum class Event
	{
		PLAYER_HIT,  //player takes dmg
		COLLECT_POINTS,  //player collects points
		PLAYER_DIED  //player died
	};

	class GameObject;

	class Observer
	{
	public:
		Observer()=default;
		virtual ~Observer() =default;
		virtual void OnNotify(GameObject* entity, Event event)=0;
	};
}

