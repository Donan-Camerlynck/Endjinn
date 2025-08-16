#pragma once
#include "Singleton.h"
namespace dae
{
	class TimeManager final : public Singleton<TimeManager>
	{
		friend class Minigin;
	public:
		float GetDeltaTime() const { return m_DeltaTime; }
		float GetDesiredFPS() const { return m_DesiredFps; }

	private:
		float m_DeltaTime = 0.0f;
		float m_DesiredFps = 300.0f;
	};
}