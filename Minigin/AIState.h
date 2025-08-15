#pragma once

namespace dae
{
	class GameObject;
	class AIState
	{
	public:
		
		virtual ~AIState() = default;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
	};
}