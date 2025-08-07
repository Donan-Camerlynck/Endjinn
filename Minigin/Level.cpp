#include "Level.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "ResourceManager.h"

namespace dae
{

	void Level::Load(const std::string levelPath)
	{

		const std::filesystem::path fullPath = dae::ResourceManager::GetInstance().GetPath()/ levelPath;
		const auto filename = std::filesystem::path(fullPath).string();

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
			columnCount = 0;
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
			if(m_Columns < columnCount)	m_Columns = columnCount;
		}

		file.close();
		m_Rows = rowCount;
		m_Columns = columnCount;
		SetupLevel();
	}

	void Level::SetupLevel()
	{
		if (m_Tiles.empty())
		{
			return;
		}

		//calculate size per tile
		if (m_Rows <= m_Columns)
		{
			m_TileWidth = 640 / m_Columns;
			m_TileHeight = m_TileWidth;
		}
		else
		{
			m_TileHeight = 480 / m_Rows;
			m_TileWidth = m_TileHeight;
		}
		

		//set size and coordinate for every tile
		for (size_t row{}; row < m_Tiles.size(); row++)
		{
			for (size_t column{}; column < m_Tiles[row].size(); column++)
			{
				m_Tiles[row][column].get()->SetSize(glm::vec2{ m_TileWidth, m_TileHeight });
				m_Tiles[row][column].get()->m_Coordinates = glm::vec2{ m_Tiles[row][column].get()->m_Coordinates.x * m_TileWidth, m_Tiles[row][column].get()->m_Coordinates.y * m_TileHeight };
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

	bool Level::AreAllTilesWalkable(const Rect& aabb)
	{
		float left = aabb.position.x + 1.f;
		float top = aabb.position.y + 1.f;
		float right = (aabb.position.x + aabb.size.x - 2.f);
		float bottom = (aabb.position.y + aabb.size.y - 2.f);


		for (float y = top; y <= bottom; ++y)
		{
			for (float x = left; x <= right; ++x)
			{
				if (x < 0 || y < 0 || y >= m_Tiles.size() * m_Rows || x >= m_Tiles[0].size() * m_Columns)
					return false;

				if (m_Tiles[static_cast<int>(y / m_TileHeight)][static_cast<int>(x / m_TileWidth)]->GetType() != dae::TileType::path)
					return false;
			}
		}

		return true;
	}
	
}
