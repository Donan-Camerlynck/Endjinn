#pragma once
#include <vector>
#include "GameObject.h"
#include "Tile.h"

namespace dae
{


	class Level : public Singleton<Level>
	{
	public:

		//void Initialize(int rows, int columns);
		void Load(const std::string levelPath);
		void SetupLevel();
		void Update();
		void Render();
		bool AreAllTilesWalkable(const Rect& aabb, float tileW, float tileH);
		void End();
		int GetRows() { return m_Rows; }
		int GetColumns() { return m_Columns; }
		int GetTileHeight() { return m_TileHeight; }
		int GetTileWidth() { return m_TileWidth; }

		//void SetTileIsColliding(int row, int column, bool isColliding);
	private:
		int m_Rows{};
		int m_Columns{};

		int m_TileHeight{};
		int m_TileWidth{};

		std::vector<std::vector<std::unique_ptr<Tile>>> m_Tiles;
		
		

		//some data to collect from file to init the level

		//texture data for all tile types
	};
}