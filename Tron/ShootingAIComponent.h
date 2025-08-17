#pragma once
#include "AIComponent.h"
#include "ShootingComponent.h"
namespace dae
{
	class ShootingAIComponent : public AIComponent
	{
	public:
		ShootingAIComponent(GameObject* owner, std::unique_ptr<AIState> state, int pathingDistance, ShootingComponent* shootComp);
		virtual ~ShootingAIComponent() override = default;
		ShootingAIComponent(const ShootingAIComponent& other) = delete;
		ShootingAIComponent(ShootingAIComponent&& other) = delete;
		ShootingAIComponent& operator=(const ShootingAIComponent& other) = delete;
		ShootingAIComponent& operator=(ShootingAIComponent&& other) = delete;
		void Update() override;
	private:
		ShootingComponent* m_pShootComp;
		float m_TimeSinceLastShot{};
		glm::vec2 m_HitPoint{};
	};
}


