#pragma once
#include "ICommand.h"

namespace dae
{
	class GameObject;

    class ScoreCommand : public ICommand
    {
	public:
		explicit ScoreCommand(GameObject* gameObject, int scoreChange)
			: m_pGameObject(gameObject), m_ScoreChange(scoreChange) {
		}
		void Execute() override;

	private:
		GameObject* m_pGameObject;
		int m_ScoreChange;


    };

}