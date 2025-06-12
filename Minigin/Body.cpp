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
			pBody.position = b2Vec2{ m_BodyInfo.position.x + m_BodyInfo.dimensions.x / 2, m_BodyInfo.position.y + m_BodyInfo.dimensions.x / 2 };
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
			

			b2Polygon box = b2MakeBox(m_BodyInfo.dimensions.x / 2, m_BodyInfo.dimensions.x / 2);
			
			m_MyShapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);
			
			
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

		glm::vec2 GetDim()
		{
			return m_BodyInfo.dimensions;
		}

		std::tuple<glm::vec2, glm::vec2> GetAABB()
		{
			std::tuple<glm::vec2, glm::vec2> aabb = std::make_tuple<glm::vec2, glm::vec2>(glm::vec2{ b2Shape_GetAABB(m_MyShapeId).lowerBound.x, b2Shape_GetAABB(m_MyShapeId).lowerBound.y }, glm::vec2{ b2Shape_GetAABB(m_MyShapeId).upperBound.x, b2Shape_GetAABB(m_MyShapeId).upperBound.y });
			
			return aabb;
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
		glm::vec2 m_Center{};
		std::unique_ptr<UserDataOverlap> m_UserDataOverlap;
		b2ShapeId m_MyShapeId{};
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

	glm::vec2 Body::GetDimensions()
	{
		return m_pImpl->GetDim();
	}

	std::tuple<glm::vec2, glm::vec2> Body::GetAABB()
	{
		return m_pImpl->GetAABB();
	}



	BodyIdTemp Body::GetBodyId()
	{
		return m_pImpl->GetBodyId();
	}
}