#include "BodyComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include <box2d.h>


namespace dae
{
	class BodyComponent::Impl 
	{
	public:
		Impl(GameObject* owner, BodyInfo bodyinfo)
			:m_pOwner(owner), m_BodyInfo(bodyinfo), m_pBodyDef(std::make_unique<b2BodyDef>(b2DefaultBodyDef()))
		{

		}

		void Initialize()
		{
			b2BodyDef* pBody = m_pBodyDef.get();
			pBody->position = b2Vec2{ m_BodyInfo.position.x, m_BodyInfo.position.y };
			pBody->type = ConvertBodyType(m_BodyInfo.type);
			pBody->fixedRotation = m_BodyInfo.fixedRotation;
			pBody->gravityScale = m_BodyInfo.gravityScale;
			pBody->linearDamping = m_BodyInfo.linearDamping;
			m_BodyId = Physics::GetInstance().CreatePhysicsBody(pBody);
		}

		void Update()
		{
			m_pOwner->SetWorldPos(glm::vec3{b2Body_GetPosition(m_BodyId).x, b2Body_GetPosition(m_BodyId).y, 1.f});
		}

		void End()
		{

		}

		void SetVelocity(glm::vec2 vel)
		{
			b2Body_SetLinearVelocity(m_BodyId, b2Vec2{ vel.x, vel.y });
		}

		static b2BodyType ConvertBodyType(BodyType type)
		{
			switch (type)
			{
				case BodyType::staticBody:
					return b2_staticBody;
				case BodyType::kinematicBody:
					return b2_kinematicBody;
				case BodyType::dynamicBody:
					return b2_dynamicBody;
			}
			return b2_staticBody;
		}

	private:
		GameObject* m_pOwner;
		BodyInfo m_BodyInfo;
		std::unique_ptr<b2BodyDef> m_pBodyDef;
		b2BodyId m_BodyId;
	};

	BodyComponent::BodyComponent(GameObject* owner, BodyInfo bodyInfo)
		:BaseComponent(owner), m_pImpl(std::make_unique<Impl>(owner, bodyInfo))
	{
		
	}

	void BodyComponent::Update()
	{
		m_pImpl->Update();
	}

	void BodyComponent::Initialize()
	{
		m_pImpl->Initialize();
	}

	void BodyComponent::End()
	{
		m_pImpl->End();
	}

	void BodyComponent::SetVelocity(glm::vec2 vel)
	{
		m_pImpl->SetVelocity(vel);
	}

}
