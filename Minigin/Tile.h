#pragma once
#include <memory>
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
		Tile(TileType type, glm::vec2 coordinates);
		~Tile();

		void SetSize(glm::vec2 size) { m_Size = size; }
		TileType GetType() { return m_Type; }
		glm::vec2 GetSize() { return m_Size; }
		glm::vec2 m_Coordinates{};

		void Render();

	private:
	

		TileType m_Type{TileType::empty};
		glm::vec2 m_Size{};

		std::vector<std::shared_ptr<Texture2D>> m_pTextures{};

	};
}