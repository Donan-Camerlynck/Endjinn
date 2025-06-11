#pragma once
#include <memory>
#include "Body.h"
#include "GameObject.h"

namespace dae
{

	enum class TileType
	{
		empty,
		dirt
	};

	class Tile
	{
	public:
		Tile(BodyInfo tileBodyInfo);
		~Tile();

	private:
		std::unique_ptr<Body> m_Body;
		TileType type{TileType::empty};
		GameObject* containingObject{};
	};
}