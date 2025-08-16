#pragma once
#include <glm.hpp>
#include "GameObject.h"
#include "Subject.h"

namespace dae
{
	class Bullet
	{
	public:
		Bullet(glm::vec2 position, glm::vec2 velocity, GameObject* caster);
		void Update();
		bool m_bActive{ true };
		glm::vec2 GetPos() { return m_Position; }
		Subject* GetSubject() { return m_BulletCollisionEvent.get(); }
		GameObject* GetCaster() { return m_pCaster; }
		~Bullet();
	private:
		int m_Bounces{};
		int m_MaxBounces{ 5 };
		glm::vec2 m_Position;
		glm::vec2 m_Velocity;
		GameObject* m_pCaster;//gameobject that spawned bullet

		std::unique_ptr<Subject> m_BulletCollisionEvent{ nullptr };
	};
}