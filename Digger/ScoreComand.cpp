#include "ScoreComand.h"
#include "ScoreComponent.h"
#include "GameObject.h"

void dae::ScoreCommand::Execute()
{
	m_pGameObject->GetComponent<ScoreComponent>()->AddScore(m_ScoreChange);
}
