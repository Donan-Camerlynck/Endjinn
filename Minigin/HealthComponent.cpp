#include "HealthComponent.h"
#include "SceneManager.h"
#include "Scene.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int maxHealth)
	: BaseComponent(owner)
	, m_Health(maxHealth)
	, m_MaxHealth(maxHealth)
{
	m_HealthChangedEvent = std::make_unique<Subject>();
}



void dae::HealthComponent::Update()
{
	if (m_bUpdateHealth)
	{
		if (m_Health < 0)
		{
			m_Health = 0;
		}
		if (m_Health > m_MaxHealth)
		{
			m_Health = m_MaxHealth;
		}
		if (m_Health <= 0)
		{
			m_bIsDead = true;
			GetOwner()->SetActive(false);

		}
		m_bUpdateHealth = false;
	}
}

void dae::HealthComponent::Initialize()
{
	BaseComponent::Initialize();
}

void dae::HealthComponent::DoDamage(const Event& event)
{
	m_Health -= event.value;
	m_bUpdateHealth = true;
	Event damageEvent{ EventType::OnDamage, GetOwner(), event.value };
	m_HealthChangedEvent->NotifyAll( damageEvent);
}

void dae::HealthComponent::Heal(int heal)
{
	m_Health += heal;
	m_bUpdateHealth = true;
	Event healEvent{ EventType::OnHeal, GetOwner(), heal };
	m_HealthChangedEvent->NotifyAll(healEvent);
}

void dae::HealthComponent::SetHealth(int health)
{
	m_Health = health;
	m_bUpdateHealth = true;
	Event setHealthEvent{ EventType::OnSetHealth, GetOwner(), health };
	m_HealthChangedEvent->NotifyAll(setHealthEvent);
}

void dae::HealthComponent::Notify(const Event& event)
{
	if (event.caster == GetOwner())
	{
		DoDamage(event);
	}
}

