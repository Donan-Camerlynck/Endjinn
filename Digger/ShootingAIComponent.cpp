#include "ShootingAIComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "TimeManager.h"

dae::ShootingAIComponent::ShootingAIComponent(GameObject* owner, std::unique_ptr<AIState> state, int pathingDistance, ShootingComponent* shootComp)
	:AIComponent(owner, std::move(state), pathingDistance), m_pShootComp(shootComp)
{

}


void dae::ShootingAIComponent::Update()
{
    AIComponent::Update();

    m_TimeSinceLastShot += TimeManager::GetInstance().GetDeltaTime();
    if (m_TimeSinceLastShot < 0.75) return;
    glm::vec2 targetPos = AIComponent::GetTarget()->GetWorldPos();
    glm::vec2 myPos = AIComponent::GetOwner()->GetWorldPos();
    glm::vec2 diff = targetPos - myPos;

    m_HitPoint = {};
    Tile* hitTile = nullptr;
    bool hit{ false };

    auto& level = Level::GetInstance();
    auto [rowStart, colStart] = level.GetRowColIdx(glm::ivec2(myPos));
    auto [rowEnd, colEnd] = level.GetRowColIdx(glm::ivec2(targetPos));

    if (rowStart == rowEnd)
    {
        int step = (colEnd > colStart) ? 1 : -1;
        for (int c = colStart; c != colEnd + step; c += step)
        {
            if (Tile* t = level.GetTileFromIdx(rowStart, c);
                t && t->GetType() == TileType::wall)
            {
                hitTile = t;
                m_HitPoint = {
                    t->m_Coordinates.x + (step > 0 ? 0 : t->GetSize().x),
                    myPos.y
                };
                hit = true;
                break;
            }
        }

        if (!hit)
        {
            m_pShootComp->SetDirection({ diff.x, 0.f });
            m_pShootComp->Shoot();
            m_TimeSinceLastShot = 0.0f;
        }
    }

    else if (colStart == colEnd)
    {
        int step = (rowEnd > rowStart) ? 1 : -1;
        for (int r = rowStart; r != rowEnd + step; r += step)
        {
            if (Tile* t = level.GetTileFromIdx(r, colStart);
                t && t->GetType() == TileType::wall)
            {
                hitTile = t;
                m_HitPoint = {
                    myPos.x,
                    t->m_Coordinates.y + (step > 0 ? 0 : t->GetSize().y)
                };
                hit = true;
                break;
            }
        }

        if (!hit)
        {
            m_pShootComp->SetDirection({ 0.f, diff.y });
            m_pShootComp->Shoot();
            m_TimeSinceLastShot = 0.0f;
        }
    }

}
