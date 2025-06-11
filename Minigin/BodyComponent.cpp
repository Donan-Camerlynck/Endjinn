#include "BodyComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include <box2d.h>


namespace dae
{
	b2BodyId ConvertBodyId(BodyIdTemp idToConvert)
	{
		return b2BodyId{ idToConvert.index1, idToConvert.world0, idToConvert.generation };
	}

	BodyComponent::BodyComponent(GameObject* owner, BodyInfo bodyInfo, std::unique_ptr<UserDataOverlap> userDataOverlap)
		:BaseComponent(owner), m_pBody(std::make_unique<Body>(bodyInfo, std::move(userDataOverlap)))
	{
		
	}

	void BodyComponent::Update()
	{
		b2BodyId bodyId = ConvertBodyId(m_pBody->GetBodyId());
		GetOwner()->SetWorldPos(glm::vec3{b2Body_GetPosition(bodyId).x, b2Body_GetPosition(bodyId).y, 1.f});
	}

	void BodyComponent::Initialize()
	{
		m_pBody->Initialize();
	}

	void BodyComponent::End()
	{
		
	}


	void BodyComponent::SetVelocity(glm::vec2 vel)
	{
		b2Body_SetLinearVelocity(ConvertBodyId(m_pBody->GetBodyId()), b2Vec2{vel.x, vel.y});
	}

}


