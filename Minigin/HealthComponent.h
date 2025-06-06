#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent : public BaseComponent
	{
	public:
		explicit HealthComponent(GameObject* owner, int maxHealth);
		void Update() override;
		int GetHealth() const { return m_Health; }
		void SetMaxHealth(int health) { m_MaxHealth = health; }
		void DoDamage(int damage);
		void Heal(int heal);
		void SetHealth(int health);

	private:
		int m_Health;
		int m_MaxHealth;
		bool m_bIsDead{ false };
		bool m_bUpdateHealth{ false };
	};
}


