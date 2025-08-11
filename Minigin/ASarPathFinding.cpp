#include "ASarPathFinding.h"
#include "Level.h"
#include <set>

namespace dae

{

	AStarPathfinding::AStarPathfinding(int rows, int cols)
		:m_Rows(rows), m_Cols(cols)
	{

	}


	std::deque<glm::vec2> AStarPathfinding::findPath(const glm::vec2& startPos, const glm::vec2& targetPos)
	{
		std::vector<Node> openList;
		std::set<Node> closedList;
		const auto [startRow, startCol] = Level::GetInstance().GetRowColIdx(startPos);
		const auto [endRow, endCol] = Level::GetInstance().GetRowColIdx(targetPos);

		const Node startNode{ startRow,startCol };
		const Node endNode{ endRow,endCol };
		openList.push_back(startNode);

		while (!openList.empty())
		{
			auto currentNodeIter = std::min_element(openList.begin(), openList.end());
			Node currentNode = *currentNodeIter;
			openList.erase(currentNodeIter);
			closedList.insert(currentNode);

			if (currentNode == endNode)
			{
				std::deque<glm::vec2> path;
				Node* pathNode = &currentNode;

				while (pathNode != nullptr)
				{
					path.push_front(Level::GetInstance().PositionFromRowCol(pathNode->row, pathNode->col));
					pathNode = pathNode->pParent;

				}
				path.pop_front();
				CleanupNodes();
				return path;
			}

			std::vector<Node> neighbors = GetNeighbors(currentNode);
			for (auto& neighbor : neighbors)
			{
				if (closedList.find(neighbor) != closedList.end()) continue;

				neighbor.gCost = currentNode.gCost + Distance(currentNode.row, currentNode.col, neighbor.row, neighbor.col);

				auto openNode = std::find(openList.begin(), openList.end(), neighbor);
				if (openNode != openList.end() and neighbor.gCost >= openNode->gCost) continue;

				neighbor.hCost = Distance(neighbor.row, neighbor.col, endNode.row, endNode.col);
				neighbor.fCost = neighbor.gCost + neighbor.hCost;
				neighbor.pParent = new Node(currentNode);
				m_CleanupNodes.push_back(neighbor.pParent);

				openList.push_back(neighbor);
			}

		}

		CleanupNodes();
		return {};
	}

	std::vector<Node> AStarPathfinding::GetNeighbors(const Node& node) const
	{
		std::vector<Node> neighbors;
		int deltas[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };
		auto& level = Level::GetInstance();

		for (const auto& delta : deltas)
		{
			const int newRow = node.row + delta[0];
			const int newCol = node.col + delta[1];
			Tile* tile = level.GetTileFromIdx(newRow, newCol);

			if (!(tile->GetType() == TileType::path)) continue;

			neighbors.emplace_back(newRow, newCol);
		}

		return neighbors;
	}

	float AStarPathfinding::Distance(int row, int col, int targetRow, int targetCol)
	{
		return static_cast<float>(std::abs(row - targetRow) + std::abs(col - targetCol));
	}

	void AStarPathfinding::CleanupNodes()
	{
		for (auto nodePtr : m_CleanupNodes)
		{
			delete nodePtr;
		}
		m_CleanupNodes.clear();
	}

}
