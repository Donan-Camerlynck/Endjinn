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
				case 0: row.push_back(std::make_unique<Tile>(TileType::wall, glm::vec2{ columnCount, rowCount })); break;
				case 1: row.push_back(std::make_unique<Tile>(TileType::path, glm::vec2{ columnCount, rowCount })); break;
				case 2: row.push_back(std::make_unique<Tile>(TileType::path, glm::vec2{ columnCount, rowCount })); break;
				case 3: row.push_back(std::make_unique<Tile>(TileType::path, glm::vec2{ columnCount, rowCount })); break;
				case 4: row.push_back(std::make_unique<Tile>(TileType::teleporter, glm::vec2{ columnCount, rowCount })); break;
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
				m_Tiles[row][column].get()->m_Coordinates = glm::vec2{ m_Tiles[row][column].get()->m_Coordinates.x * m_TileWidth + m_TileWidth/2, m_Tiles[row][column].get()->m_Coordinates.y * m_TileHeight + m_TileHeight/2 };
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
		float left = aabb.position.x - 1;
		float top = aabb.position.y -1;
		float right = (aabb.position.x + aabb.size.x -1);
		float bottom = (aabb.position.y + aabb.size.y -1);


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

	bool Level::IsTileWalkable(const glm::ivec2& position, const glm::ivec2& direction)
	{
		// List of corner offsets for the object
		std::vector<glm::ivec2> corners = {
			glm::ivec2{m_TileWidth / 2 - 1, m_TileHeight / 2 -1},// top-left
			glm::ivec2{m_TileWidth /2 - 1, -m_TileHeight / 2 + 1}, // top-right
			glm::ivec2{-m_TileWidth /2 + 1, m_TileHeight /2 - 1}, // bottom-left
			glm::ivec2{-m_TileWidth /2 + 1, -m_TileHeight /2 + 1} // bottom-right
		};

		for (const auto& offset : corners)
		{
			glm::ivec2 cornerPos = position + offset;

			// Convert world position to tile coordinates
			int tileX = (cornerPos.x - m_TileWidth/2) / m_TileWidth;
			int tileY = (cornerPos.y - m_TileHeight / 2) / m_TileHeight;

			tileX++;
			tileY++;

			// Move in the given direction
			int nextTileX = (cornerPos.x + 2 * direction.x )/ m_TileWidth ;
			int nextTileY = (cornerPos.y  + 2 * direction.y) / m_TileHeight;

			// Bounds check
			if (nextTileX < 0 || nextTileY < 0 ||
				nextTileY >= static_cast<int>(m_Tiles.size()) ||
				nextTileX >= static_cast<int>(m_Tiles[nextTileY].size()))
			{
				return false;
			}

			// Tile walkability check
			TileType tileType = m_Tiles[nextTileY][nextTileX]->GetType();
			if (tileType != TileType::path)
				return false;
		}

		return true;
	}

	Tile* Level::GetTileAtPos(glm::ivec2 pos)
	{
		return m_Tiles[static_cast<int>(pos.y / m_TileHeight)][static_cast<int>(pos.x / m_TileWidth)].get();
	}

	std::tuple<int, int> Level::GetRowColIdx(const glm::ivec2& pos)
	{
		int colIdx = static_cast<int>(pos.x) / m_TileWidth;
		int rowIdx = static_cast<int>(pos.y) / m_TileHeight;

		return std::make_tuple(rowIdx, colIdx);
	}

	glm::ivec2 Level::PositionFromRowCol(int row, int col)
	{
		const float x = static_cast<float>(col * m_TileWidth);
		const float y = static_cast<float>(row * m_TileHeight);
		return { x, y };
	}

	Tile* Level::GetTileFromIdx(int row, int col)
	{
		return m_Tiles[row][col].get();
	}
	
}
