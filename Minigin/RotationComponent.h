#pragma once
#include "BaseComponent.h"
namespace dae
{
	class RotationComponent : public BaseComponent
	{
		float m_radius;
		float m_rotationSpeed;
		float m_currentAngleDegrees{ 0.0f };

	public:
		RotationComponent(GameObject* owner, float radius, float rotSpeedDegrees);
		virtual ~RotationComponent() override = default;
		RotationComponent(const RotationComponent& other) = delete;
		RotationComponent(RotationComponent&& other) = delete;
		RotationComponent& operator=(const RotationComponent& other) = delete;
		RotationComponent& operator=(RotationComponent&& other) = delete;

		virtual void Update() override;
	};
}

