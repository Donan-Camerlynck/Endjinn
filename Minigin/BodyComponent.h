#pragma once
#include "BaseComponent.h"
#include "Body.h"
#include <glm.hpp>
#include <memory>

namespace dae
{

	class BodyComponent : public BaseComponent
	{
	public:
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void End() override;

		void SetVelocity(glm::vec2 velocity);

		BodyComponent(GameObject*, BodyInfo bodyInfo, std::unique_ptr<UserDataOverlap> userDataOverlap);
		virtual ~BodyComponent() override = default;
		BodyComponent(const BodyComponent& other) = delete;
		BodyComponent(BodyComponent&& other) = delete;
		BodyComponent& operator=(const BodyComponent& other) = delete;
		BodyComponent& operator=(BodyComponent&& other) = delete;

	private:
		std::unique_ptr<Body> m_pBody;
	};
}