#pragma once
#include <memory>
#include "Body.h"
#include "GameObject.h"
#include "Structs.h"

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
		Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions, std::unique_ptr<UserDataOverlap> userDataOverlap);
		~Tile();

		void SetIsColliding(bool isColliding) { m_IsColliding = isColliding; }

		void Render();

	private:
		bool m_IsColliding{ false };
		std::unique_ptr<Body> m_Body;
		TileType m_Type{TileType::empty};
		glm::vec2 m_Dimensions{};
		GameObject* containingObject{};
	};
}