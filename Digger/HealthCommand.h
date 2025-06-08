#pragma once
#include "ICommand.h"

namespace dae
{
	class GameObject;

	class HealthCommand : public ICommand
	{
	public:
		explicit HealthCommand(GameObject* gameObject, int healthChange)
			: m_pGameObject(gameObject), m_HealthChange(healthChange) {
		}
		void Execute() override;

	private:
		GameObject* m_pGameObject;
		int m_HealthChange;

	};

}
