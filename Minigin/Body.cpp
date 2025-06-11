#pragma once

#include "Body.h"
#include <box2d.h>
#include "Physics.h"

namespace dae
{
	class Body::Impl
	{
	public:
		Impl(BodyInfo bodyinfo)
			: m_BodyInfo(bodyinfo)
		{

		}

		void Initialize()
		{
			b2BodyDef pBody = b2DefaultBodyDef();
			pBody.position = b2Vec2{ m_BodyInfo.position.x, m_BodyInfo.position.y };
			pBody.type = ConvertBodyType(m_BodyInfo.type);
			pBody.fixedRotation = m_BodyInfo.fixedRotation;
			pBody.gravityScale = m_BodyInfo.gravityScale;
			pBody.linearDamping = m_BodyInfo.linearDamping;
			b2BodyId bodyId = Physics::GetInstance().CreatePhysicsBody(&pBody);
			m_BodyId = { bodyId.index1, bodyId.world0, bodyId.generation };
		}

		void Update()
		{
			
		}

		void End()
		{

		}

		BodyIdTemp GetBodyId()
		{
			return m_BodyId;
		}

		void SetVelocity(glm::vec2 vel)
		{
			b2Body_SetLinearVelocity(b2BodyId{  m_BodyId.index1, m_BodyId.world0, m_BodyId.generation }, b2Vec2{ vel.x, vel.y });
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
		BodyInfo m_BodyInfo;
		BodyIdTemp m_BodyId{};
	};



	Body::Body(BodyInfo bodyInfo)
		:m_pImpl(std::make_unique<Impl>(bodyInfo))
	{

	}
	Body::~Body()
	{
	}

	void Body::Initialize()
	{
		m_pImpl->Initialize();
	}

	void Body::Update()
	{
		m_pImpl->Update();
	}

	void Body::End()
	{ 
		m_pImpl->End();
	}

	void Body::SetVelocity(glm::vec2 velocity)
	{
		m_pImpl->SetVelocity(velocity);
	}

	BodyIdTemp Body::GetBodyId()
	{
		return m_pImpl->GetBodyId();
	}
}