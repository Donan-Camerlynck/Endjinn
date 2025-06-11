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
		Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions);
		~Tile();

		void Render();

	private:
		std::unique_ptr<Body> m_Body;
		TileType m_Type{TileType::empty};
		glm::vec2 m_Dimensions{};
		GameObject* containingObject{};
	};
}