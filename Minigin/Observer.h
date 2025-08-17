#pragma once
#include "GameObject.h"

namespace dae
{
	enum class EventType
	{
		OnDamage,
		OnDeath,
		OnScore,
		OnHeal,
		OnSetHealth
	};

	struct Event
	{
		EventType type;
		GameObject* caster;
		int value{};
	};

	class IObserver
	{

	public:
		IObserver() = default;
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;

		virtual void Notify(const Event& event) = 0;
	};
}