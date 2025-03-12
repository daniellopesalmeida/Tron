#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.emplace_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	std::erase(m_Observers, observer);
}

void dae::Subject::Notify(GameObject* entity, Event event)
{
	for (Observer* observer : m_Observers)
	{
		observer->OnNotify(entity, event);
	}
}
