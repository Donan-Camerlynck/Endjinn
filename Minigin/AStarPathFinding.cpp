#include "AStarPathFinding.h"
#include "Level.h"
#include <set>
#include <iostream>

namespace dae

{

	AStarPathfinding::AStarPathfinding(int rows, int cols)
		:m_Rows(rows), m_Cols(cols)
	{

	}

	//source of code: https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2
	std::deque<glm::ivec2> AStarPathfinding::FindPath(const glm::ivec2& startPos, const glm::ivec2& targetPos)
	{
		Level& level = Level::GetInstance();
		std::vector<Node> openList;
		std::set<Node> closedList;
		const auto [startRow, startCol] = level.GetRowColIdx({ startPos.x, startPos.y });
		const auto [endRow, endCol] = level.GetRowColIdx({ targetPos.x, targetPos.y });
		//const auto [startRow, startCol] = level.GetRowColIdx(startPos);
		//const auto [endRow, endCol] = level.GetRowColIdx(targetPos);


		Node startNode{ startRow,startCol };
		Node endNode{ endRow,endCol };
		startNode.gCost = 0.0f;
		startNode.hCost = Distance(startNode.row, startNode.col, endNode.row, endNode.col);
		startNode.fCost = startNode.gCost + startNode.hCost;
		startNode.pParent = nullptr;
		openList.push_back(startNode);

		while (!openList.empty())
		{
			auto compare = [](const Node& a, const Node& b) 
				{
				if (a.fCost != b.fCost) return a.fCost < b.fCost;
				return a.hCost < b.hCost;
				};

			auto currentNodeIter = std::min_element(openList.begin(), openList.end(), compare);
			Node currentNode = *currentNodeIter;
			openList.erase(currentNodeIter);
			closedList.insert(currentNode);

			if (currentNode == endNode)
			{
				std::deque<glm::ivec2> path;
				Node* pathNode = &currentNode;

				while (pathNode != nullptr)
				{
					path.push_front(Level::GetInstance().PositionFromRowCol(pathNode->row, pathNode->col) );
					pathNode = pathNode->pParent;

				}
				if (!path.empty()) path.pop_front();
				CleanupNodes();
				return path;
			}

			std::vector<Node> neighbors = GetNeighbors(currentNode);
			for (auto& neighbor : neighbors)
			{
				if (closedList.find(neighbor) != closedList.end())
					continue;

				const float tentativeG = currentNode.gCost + Distance(currentNode.row, currentNode.col, neighbor.row, neighbor.col);

				auto openNode = std::find(openList.begin(), openList.end(), neighbor);

				if (openNode == openList.end() || tentativeG < openNode->gCost)
				{
					neighbor.gCost = tentativeG;
					neighbor.hCost = Distance(neighbor.row, neighbor.col, endNode.row, endNode.col);
					neighbor.fCost = neighbor.gCost + neighbor.hCost;

					neighbor.pParent = new Node(currentNode);
					m_CleanupNodes.push_back(neighbor.pParent);

					if (openNode == openList.end())
						openList.push_back(neighbor);
					else
						*openNode = neighbor; 
				}
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
			const int newRow = node.row + delta[1];
			const int newCol = node.col + delta[0];
			if (newRow < 0 || newCol < 0) continue;
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
