#include "Level.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ResourceManager.h"

namespace dae
{
	


	//void Level::Initialize(int rows, int columns)
	//{
	//	m_Rows = rows;
	//	m_Columns = columns;

	//	int columnWidth = 640 / m_Rows;
	//	int rowHeight = 480 / m_Columns;

	//	//glm::vec2 dimensions{ columnWidth, rowHeight };
	//	m_MainTileBodyInfo.dimensions = glm::vec2{ columnWidth, rowHeight };
	//	
	//	m_Tiles.resize(m_Rows);  
	//	for (int y = 0; y < m_Columns; ++y) 
	//	{
	//		for (int x = 0; x < m_Rows; ++x) 
	//		{
	//			//add logic to determine location of tile
	//			BodyInfo tileInfo = m_MainTileBodyInfo;
	//			tileInfo.position = glm::vec2{x * columnWidth, y * rowHeight};
	//			std::unique_ptr<UserDataOverlap> userDataOverlap = std::make_unique<UserDataOverlap>(false, x, y);
	//			m_Tiles[y].emplace_back(std::make_unique<Tile>(tileInfo, TileType::empty, m_MainTileBodyInfo.dimensions, std::move(userDataOverlap)));
	//		}
	//	}
	//}

	void Level::Load(const std::string levelPath)
	{

		const std::filesystem::path fullPath = dae::ResourceManager::GetInstance().GetPath()/ levelPath;
		const auto filename = std::filesystem::path(fullPath).filename().string();

		//read csv
		std::ifstream file;
		file.open(filename);
		if (!file.is_open())
		{
			std::cerr << "Failed to open level file: " << filename << std::endl;
			return;
		}

		m_Tiles.clear();

		int rowCount{};
		int columnCount{};

		std::string line;
		while (std::getline(file, line))
		{
			std::vector<std::unique_ptr<Tile>> row;
			std::stringstream ss(line);
			std::string value;

			while (std::getline(ss, value, ','))
			{
				int tileCode = std::stoi(value);
				switch (tileCode)
				{
				case 0: row.push_back(std::make_unique<Tile>(TileType::empty, glm::vec2{ columnCount, rowCount })); break;
				case 1: row.push_back(std::make_unique<Tile>(TileType::wall, glm::vec2{ columnCount, rowCount })); break;
				case 2: row.push_back(std::make_unique<Tile>(TileType::path, glm::vec2{ columnCount, rowCount })); break;
				default:
					std::cerr << "Unknown tile code: " << tileCode << std::endl;
					row.push_back(std::make_unique<Tile>(TileType::empty, glm::vec2{-1,-1}));
					break;
				}
				columnCount++;
			}

			m_Tiles.push_back(std::move(row));
			rowCount++;
		}

		file.close();
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
	/*void Level::SetTileIsColliding(int row, int column, bool isColliding)
	{
		m_Tiles[column][row]->SetIsColliding(isColliding);
	}*/
}
