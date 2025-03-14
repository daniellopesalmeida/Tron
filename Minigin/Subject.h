#pragma once
#include "Observer.h"
#include <vector>

namespace dae
{
	class Observer;
	class GameObject;
	class Subject
	{
	public:
		Subject() = default;
		~Subject() = default;
		
		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;
		Subject(Subject&&) = delete;
		Subject& operator=(Subject&&) = delete;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);
		void Notify(GameObject* entity, Event event);
	private:
		std::vector<Observer*> m_Observers;
	};
}
