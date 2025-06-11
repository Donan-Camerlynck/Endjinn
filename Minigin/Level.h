#pragma once
#include <vector>
#include "GameObject.h"
#include <box2d.h>

namespace dae
{

	enum class TileType
	{
		empty,
		dirt
	};

	struct Tile
	{
		b2WorldId worldId;
		TileType type;
		GameObject* containingObject{};
	};

	class Level
	{
	public:
		Level();

		~Level();
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;

		void Initialize();
		void Update();
		void End();
	private:
		std::vector<std::vector<Tile>> m_Tiles;
		//dae::BodyInfo mainBodyInfo{
		//dae::BodyType::dynamicBody,
		//glm::vec2{280.f, 20.f},
		//10.f,
		//0.f,
		//true
		//};
	};
}