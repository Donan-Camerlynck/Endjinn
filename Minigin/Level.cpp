#include "Level.h"

namespace dae
{
	


	void Level::Initialize(int rows, int columns)
	{
		m_Rows = rows;
		m_Columns = columns;
		
		m_Tiles.resize(m_Rows);  
		for (int y = 0; y < m_Rows; ++y) 
		{
			for (int x = 0; x < m_Columns; ++x) 
			{
				//add logic to determine location of tile
				m_Tiles[y].emplace_back(std::make_unique<Tile>(m_MainTileBodyInfo));
			}
		}
	}
}
