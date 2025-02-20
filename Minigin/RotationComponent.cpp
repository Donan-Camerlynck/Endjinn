#include "RotationComponent.h"
#include <iostream>
#include "GameObject.h"
#include "TimeManager.h"

dae::RotationComponent::RotationComponent(GameObject* owner, float radius, float rotSpeedDegrees) :
	BaseComponent(owner), m_radius(radius), m_rotationSpeed(rotSpeedDegrees)
{
}

void dae::RotationComponent::Update()
{
	const float deltaTime = TimeManager::GetInstance().GetDeltaTime();
	m_currentAngleDegrees += m_rotationSpeed * deltaTime;

	if (m_currentAngleDegrees >= 360.f) m_currentAngleDegrees -= 360.f;
	if (m_currentAngleDegrees <= -360.f) m_currentAngleDegrees += 360.f;

	const float currentAngleRadians = glm::radians(m_currentAngleDegrees);

	if (auto owner = GetOwner())
	{
		glm::vec2 offset{ m_radius * glm::cos(currentAngleRadians) ,m_radius * glm::sin(currentAngleRadians) };
		owner->SetLocalPos(glm::vec3{ offset.x, offset.y, 1.0f });
	}
}