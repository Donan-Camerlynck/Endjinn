#pragma once

namespace dae
{
	class GameObject;

	struct UserDataOverlap
	{
		bool isGameObject{ false };
		int row{};
		int column{};
		GameObject* GameObject{};

	};
}