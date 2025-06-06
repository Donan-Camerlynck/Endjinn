#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include <memory>

namespace dae
{
	class HealthComponent : public BaseComponent
	{
	public:
		explicit HealthComponent(GameObject* owner, int maxHealth);
		void Update() override;
		void Initialize() override;
		int GetHealth() const { return m_Health; }
		void SetMaxHealth(int health) { m_MaxHealth = health; }
		void DoDamage(int damage);
		void Heal(int heal);
		void SetHealth(int health);

		Subject* GetHealthChangedEvent() const { return m_HealthChangedEvent.get(); }

	private:
		int m_Health;
		int m_MaxHealth;
		bool m_bIsDead{ false };
		bool m_bUpdateHealth{ false };
		std::unique_ptr<Subject> m_HealthChangedEvent;
	};
}


