#pragma once
#include <vector>
#include "GameObject.h"
#include "Body.h"
#include "Tile.h"

namespace dae
{


	class Level : public Singleton<Level>
	{
	public:

		void Initialize(int rows, int columns);
		void Update();
		void Render();
		void End();

		void SetTileIsColliding(int row, int column, bool isColliding);
	private:
		int m_Rows{};
		int m_Columns{};

		std::vector<std::vector<std::unique_ptr<Tile>>> m_Tiles;
		
		dae::BodyInfo m_MainTileBodyInfo
		{
			dae::BodyType::staticBody,
			glm::vec2{0.f, 0.f},
			glm::vec2{0.5f, 0.5f},
			10.f,
			0.f,
			true
		};

		//some data to collect from file to init the level

		//texture data for all tile types
	};
}