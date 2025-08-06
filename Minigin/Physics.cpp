#include "Physics.h"
#include "TimeManager.h"
#include "Renderer.h"
#include <box2d.h>
#include "Structs.h"
#include "Level.h"

namespace dae
{ 
	class Physics::Impl
	{
	public:
		Impl()
			:m_WorldId(CreateWorld()), m_TimeStep(1.f / 60.f)
		{
			
		}

		void Initialize()
		{
			
		}

		b2WorldId CreateWorld()
		{
			b2Vec2 gravity = { 0.0f, -10.0f };
			b2WorldDef worldDef{ b2DefaultWorldDef() };
			worldDef.gravity = gravity;
			b2WorldId worldId = b2CreateWorld(&worldDef);
			return worldId;
		}

		void Update()
		{
			b2World_Step(m_WorldId, TimeManager::GetInstance().GetDeltaTime(), 4);

			b2SensorEvents sensorEvents = b2World_GetSensorEvents(m_WorldId);
			//box2d code for begin overlap events
			for (int i = 0; i < sensorEvents.beginCount; ++i)
			{
				b2SensorBeginTouchEvent* beginTouch = sensorEvents.beginEvents + i;
				UserDataOverlap* myUserData = reinterpret_cast<UserDataOverlap*>(b2Shape_GetUserData(beginTouch->visitorShapeId));
				// process begin event
				if (myUserData->isGameObject)
				{

				}
				else
				{
					//Level::GetInstance().SetTileIsColliding(myUserData->row, myUserData->column, true);
				}
			}

			for (int i = 0; i < sensorEvents.endCount; ++i)
			{
				b2SensorEndTouchEvent* endTouch = sensorEvents.endEvents + i;
				if (b2Shape_IsValid(endTouch->visitorShapeId))
				{
					UserDataOverlap* myUserData = reinterpret_cast<UserDataOverlap*>(b2Shape_GetUserData(endTouch->visitorShapeId));
					// process end event
					if (myUserData->isGameObject)
					{

					}
					else
					{
						//Level::GetInstance().SetTileIsColliding(myUserData->row, myUserData->column, false);
					}
				}
			}

			
		}

		


		b2BodyId CreatePhysicsBody(b2BodyDef* bodyDef)
		{
			return b2CreateBody(m_WorldId, bodyDef);
		}

		void End()
		{
			b2DestroyWorld(m_WorldId);
		}

	private:		
		b2WorldId m_WorldId;
		float m_TimeStep;
	};

	Physics::Physics() :
		m_pImpl(std::make_unique<Impl>())
	{
	}
	Physics::~Physics() = default;

	void dae::Physics::Initialize()
	{
		m_pImpl->Initialize();
	}

	void dae::Physics::Update()
	{
		m_pImpl->Update();
	}

	

	void dae::Physics::End()
	{
		m_pImpl->End();
	}

	b2BodyId dae::Physics::CreatePhysicsBody(b2BodyDef* bodyDef)
	{
		return m_pImpl->CreatePhysicsBody(bodyDef);
	}

}
