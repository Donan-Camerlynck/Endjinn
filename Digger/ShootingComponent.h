#pragma once
#include <BaseComponent.h>
#include <glm.hpp>

namespace dae
{
    class ShootingComponent : public BaseComponent
    {
    public:
        ShootingComponent(GameObject* owner,  float speed, bool bIsPlayer);
        virtual ~ShootingComponent() override = default;
        ShootingComponent(const ShootingComponent& other) = delete;
        ShootingComponent(ShootingComponent&& other) = delete;
        ShootingComponent& operator=(const ShootingComponent& other) = delete;
        ShootingComponent& operator=(ShootingComponent&& other) = delete;
        void Shoot();
        void Update() override;
        void SetDirection(glm::vec2 direction);
    private:
        glm::vec2 m_Direction{};
        bool m_bIsPlayer{ false };
        float m_Speed;
        bool m_bShouldShoot;
    };

}

