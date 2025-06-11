#pragma once

#include "Body.h"
#include <box2d.h>
#include "Physics.h"

namespace dae
{
	class Body::Impl
	{
	public:
		Impl(BodyInfo bodyinfo, std::unique_ptr<UserDataOverlap> userDataOverlap)
			: m_BodyInfo(bodyinfo), m_UserDataOverlap(std::move(userDataOverlap))
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

			b2ShapeDef shapeDef = b2DefaultShapeDef();
			shapeDef.isSensor = m_BodyInfo.isSensor;
			shapeDef.enableSensorEvents = true;
			shapeDef.userData = m_UserDataOverlap.get();
			b2Polygon box = b2MakeBox(m_BodyInfo.dimensions.x, m_BodyInfo.dimensions.x);
			b2ShapeId myShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);
		}

		void Update()
		{
			
		}

		void End()
		{

		}

		glm::vec2 GetPos()
		{
			b2Vec2 pos{b2Body_GetPosition(ConvertToB2BodyId(m_BodyId))};
			return glm::vec2{ pos.x, pos.y };
		}

		BodyIdTemp GetBodyId()
		{
			return m_BodyId;
		}

		void SetVelocity(glm::vec2 vel)
		{
			b2Body_SetLinearVelocity(ConvertToB2BodyId(m_BodyId), b2Vec2{vel.x, vel.y});
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

		b2BodyId ConvertToB2BodyId(BodyIdTemp bodyId)
		{
			return b2BodyId{ bodyId.index1, bodyId.world0, bodyId.generation };
		}

	private:
		BodyInfo m_BodyInfo;
		BodyIdTemp m_BodyId{};
		std::unique_ptr<UserDataOverlap> m_UserDataOverlap;
	};



	Body::Body(BodyInfo bodyInfo, std::unique_ptr<UserDataOverlap> userDataOverlap)
		:m_pImpl(std::make_unique<Impl>(bodyInfo, std::move(userDataOverlap)))
	{

	}

	Body::~Body() = default;


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

	glm::vec2 Body::GetPosition()
	{
		return m_pImpl->GetPos();
	}

	BodyIdTemp Body::GetBodyId()
	{
		return m_pImpl->GetBodyId();
	}
}