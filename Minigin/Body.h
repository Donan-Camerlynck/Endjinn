#pragma once
#include <glm.hpp>
#include <memory>
#include "Structs.h"

struct BodyIdTemp
{
	int32_t index1;
	uint16_t world0;
	uint16_t generation;
};


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
		glm::vec2 dimensions;
		float linearDamping = 0.f;
		float gravityScale = 0.f;
		bool fixedRotation = true;
		bool isSensor{ false };
	};

	class Body
	{
	public:

		Body( BodyInfo bodyInfo, std::unique_ptr<UserDataOverlap> userDataOverlap);
		~Body();
		Body(const Body& other) = delete;
		Body(Body&& other) = delete;
		Body& operator=(const Body& other) = delete;
		Body& operator=(Body&& other) = delete;

		void Initialize();
		void Update();
		void End();
		void SetVelocity(glm::vec2 velocity);

		glm::vec2 GetPosition();

		BodyIdTemp GetBodyId();

	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
		BodyIdTemp m_BodyId{};
	};
}