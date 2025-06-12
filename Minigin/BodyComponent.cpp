#include "BodyComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include "Renderer.h"
#include <box2d.h>


namespace dae
{
	b2BodyId ConvertBodyId(BodyIdTemp idToConvert)
	{
		return b2BodyId{ idToConvert.index1, idToConvert.world0, idToConvert.generation };
	}

	BodyComponent::BodyComponent(GameObject* owner, BodyInfo bodyInfo, std::unique_ptr<UserDataOverlap> userDataOverlap)
		:BaseComponent(owner), m_pBody(std::make_unique<Body>(bodyInfo, std::move(userDataOverlap))), m_BodyInfo(bodyInfo)
	{
		
	}

	void BodyComponent::Update()
	{
		b2BodyId bodyId = ConvertBodyId(m_pBody->GetBodyId());
		GetOwner()->SetWorldPos(glm::vec3{b2Body_GetPosition(bodyId).x - m_BodyInfo.dimensions.x/2, b2Body_GetPosition(bodyId).y - m_BodyInfo.dimensions.y/2, 1.f});
	}

	void BodyComponent::Initialize()
	{
		m_pBody->Initialize();
	}

	void BodyComponent::Render() const
	{
		auto& renderer = Renderer::GetInstance();
		glm::vec2 pos{ m_pBody->GetPosition() };
		glm::vec2 dimension{ m_pBody->GetDimensions() };
		//renderer.RenderDebugBox(pos.x, pos.y, dimension.x, dimension.y, true);

		glm::vec2 aa{ get<0>(m_pBody->GetAABB()) };
		glm::vec2 bb{ get<1>(m_pBody->GetAABB()) };
		renderer.RenderDebugBox(aa.x, aa.y, bb.x - aa.x, bb.y - aa.y, false);
	}

	void BodyComponent::End()
	{
		
	}


	void BodyComponent::SetVelocity(glm::vec2 vel)
	{
		b2Body_SetLinearVelocity(ConvertBodyId(m_pBody->GetBodyId()), b2Vec2{vel.x, vel.y});
	}

}


