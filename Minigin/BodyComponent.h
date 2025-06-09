#pragma once
#include "BaseComponent.h"
#include <glm.hpp>
#include <memory>

namespace dae
{

	enum class BodyType
	{
		staticBody,
		kinematicBody,
		dynamicBody
	};

	struct BodyInfo
	{
		BodyType type;
		glm::vec2 position;
		float linearDamping = 0.f;
		float gravityScale = 0.f;
		bool fixedRotation = true;
	};

	class BodyComponent : public BaseComponent
	{
		virtual void Update() override;
		virtual void Initialize() override;
		virtual void End() override;

		BodyComponent(GameObject* owner, BodyInfo bodyInfo);
		virtual ~BodyComponent() override = default;
		BodyComponent(const BodyComponent& other) = delete;
		BodyComponent(BodyComponent&& other) = delete;
		BodyComponent& operator=(const BodyComponent& other) = delete;
		BodyComponent& operator=(BodyComponent&& other) = delete;

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}