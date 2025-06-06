#pragma once

namespace dae
{
	class IObserver
	{

	public:
		IObserver() = default;
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;

		virtual void Notify() = 0;
	};
}