#include "Physics.h"
#include "TimeManager.h"
#include <box2d.h>

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
