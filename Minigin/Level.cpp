#include "Level.h"
#include <algorithm>

namespace dae
{
	


	void Level::Initialize(int rows, int columns)
	{
		m_Rows = rows;
		m_Columns = columns;

		int columnWidth = 640 / m_Rows;
		int rowHeight = 480 / m_Columns;

		glm::vec2 dimensions{ columnWidth, rowHeight };
		
		m_Tiles.resize(m_Rows);  
		for (int y = 0; y < m_Columns; ++y) 
		{
			for (int x = 0; x < m_Rows; ++x) 
			{
				//add logic to determine location of tile
				BodyInfo tileInfo = m_MainTileBodyInfo;
				tileInfo.position = glm::vec2{x * columnWidth, y * rowHeight};
				m_Tiles[y].emplace_back(std::make_unique<Tile>(tileInfo, TileType::empty, dimensions));
			}
		}
	}

	void Level::Render()
	{
		for (const auto& row : m_Tiles) {
			for (const auto& tilePtr : row) {
				Tile& tile = *tilePtr;
				tile.Render();
			}
		}
	}
}
