#pragma once
#include "Observer.h"
#include <vector>
#include "GameObject.h"

namespace dae
{
	

	class Subject final
	{
	public:
		Subject() = default;
		~Subject() = default;
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;
		void NotifyAll(const Event& event);
		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);

	private:
		std::vector<IObserver*> m_Observers;
	};
}