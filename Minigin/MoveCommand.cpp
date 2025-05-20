#include "MoveCommand.h"
#include "GameObject.h"
#include "TimeManager.h"

dae::MoveCommand::MoveCommand(float speed, glm::vec2 direction, GameObject* gameObject)
	:m_Speed(speed), m_pGameObject(gameObject)
{
	m_Direction = glm::normalize(direction);
}

void dae::MoveCommand::Execute()
{
	if (!m_pGameObject)
	{
		return;
	}
	glm::vec2 oldPos = m_pGameObject->GetLocalPos();
	glm::vec2 newPos = oldPos + m_Direction * m_Speed * TimeManager::GetInstance().GetDeltaTime();

	m_pGameObject->SetLocalPos(glm::vec3(newPos.x, newPos.y, 1.f));
}
