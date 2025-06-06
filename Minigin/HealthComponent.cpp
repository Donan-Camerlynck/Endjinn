#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(GameObject* owner, int maxHealth)
	: BaseComponent(owner)
	, m_Health(maxHealth)
	, m_MaxHealth(maxHealth)
{
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
		}
		m_bUpdateHealth = false;
	}
}

void dae::HealthComponent::Initialize()
{
	BaseComponent::Initialize();
	m_HealthChangedEvent = std::make_unique<Subject>();
	
	
}

void dae::HealthComponent::DoDamage(int damage)
{
	m_Health -= damage;
	m_bUpdateHealth = true;	
	m_HealthChangedEvent->NotifyAll();
}

void dae::HealthComponent::Heal(int heal)
{
	m_Health += heal;
	m_bUpdateHealth = true;
	m_HealthChangedEvent->NotifyAll();
}

void dae::HealthComponent::SetHealth(int health)
{
	m_Health = health;
	m_bUpdateHealth = true;
	m_HealthChangedEvent->NotifyAll();
}

