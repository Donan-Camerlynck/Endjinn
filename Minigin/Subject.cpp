#include "Subject.h"

namespace dae
{

	void Subject::NotifyAll(Event e)
	{
		for (auto observer : m_Observers)
		{
			observer->Notify(e);
		}
	}

	void Subject::AddObserver(IObserver* observer)
	{
		m_Observers.emplace_back(observer);
	}

	void Subject::RemoveObserver(IObserver* observer)
	{
		std::erase(m_Observers, observer);
	}

}