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
		wall,
		path
	};

	class Tile
	{
	public:
		//Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions, std::unique_ptr<UserDataOverlap> userDataOverlap);
		Tile(TileType type, glm::vec2 coordinates);
		~Tile();

		void SetSize(glm::vec2 size) { m_Size = size; }

		glm::vec2 m_Coordinates{};
		//void SetIsColliding(bool isColliding) { m_IsColliding = isColliding; }

		void Render();

	private:
		//bool m_IsColliding{ false };
		//std::unique_ptr<Body> m_pBody;

		TileType m_Type{TileType::empty};
		glm::vec2 m_Size{};

		std::vector<std::shared_ptr<Texture2D>> m_pTextures{};

		//glm::vec2 m_Dimensions{};
		//GameObject* containingObject{};
	};
}