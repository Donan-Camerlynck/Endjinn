#pragma once
#include "Singleton.h"
#include <memory>

struct b2BodyId;
struct b2BodyDef;

namespace dae
{
	

	class Physics final : public Singleton<Physics>
	{
	public:
		~Physics();
		Physics(const Physics& other) = delete;
		Physics(Physics&& other) noexcept = delete;
		Physics& operator=(const Physics& other) = delete;
		Physics& operator=(Physics&& other) noexcept = delete;

		void Initialize();
		void Update();
		void End();

		b2BodyId CreatePhysicsBody(b2BodyDef* bodyDef);

	private:
		friend class Singleton;
		Physics();

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}