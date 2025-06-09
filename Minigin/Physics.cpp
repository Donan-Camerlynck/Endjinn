#include "Physics.h"
#include "TimeManager.h"
#include <box2d.h>

namespace dae
{ 
	class Physics::Impl
	{
	public:
		Impl()
			:m_World(std::make_unique<b2WorldDef>(b2DefaultWorldDef())), m_WorldId(b2CreateWorld(m_World.get())), m_TimeStep(1.f/60.f)
		{
			m_World.get()->gravity = { 0.0f, -10.0f };
			
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
		std::unique_ptr<b2WorldDef> m_World;
		b2WorldId m_WorldId;
		float m_TimeStep;
	};

	Physics::Physics() :
		m_pImpl(std::make_unique<Impl>())
	{
	}
	Physics::~Physics() = default;

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
