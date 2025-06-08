#pragma once
#include "Singleton.h"
#include <box2d.h>
#include <memory>


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

		void Update();
		void End();

	private:
		friend class Singleton;
		Physics();

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}