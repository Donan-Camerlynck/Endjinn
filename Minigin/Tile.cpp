#include "Tile.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{



	//Tile::Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions, std::unique_ptr<UserDataOverlap> userDataOverlap)
	//	:m_pBody(std::make_unique<Body>(tileBodyInfo, std::move(userDataOverlap))), m_Type(type), m_Dimensions(dimensions)
	//{
	//	m_pBody->Initialize();
	//}

	Tile::Tile(TileType type, glm::vec2 coordinates)
		:m_Type(type), m_Coordinates(coordinates)
	{
		m_pTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("Level/void.png"));
		m_pTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("Level/wall.png"));
		m_pTextures.push_back(dae::ResourceManager::GetInstance().LoadTexture("Level/path.png"));
	}

	Tile::~Tile() = default;

	void Tile::Render()
	{
		auto& renderer = Renderer::GetInstance();

		switch (m_Type)
		{
		case TileType::empty:
			renderer.RenderTexture(*m_pTextures[0], m_Coordinates.x * m_Size.x, m_Coordinates.y * m_Size.y, m_Size.x, m_Size.y);
			break;
		case TileType::wall:
			renderer.RenderTexture(*m_pTextures[1], m_Coordinates.x * m_Size.x, m_Coordinates.y * m_Size.y, m_Size.x, m_Size.y);
			break;
		case TileType::path:
			renderer.RenderTexture(*m_pTextures[2], m_Coordinates.x * m_Size.x, m_Coordinates.y * m_Size.y, m_Size.x, m_Size.y);
			break;
		}
		//glm::vec2 aa{ get<0>(m_pBody->GetAABB()) };
		//glm::vec2 bb{ get<1>(m_pBody->GetAABB()) };
		//renderer.RenderDebugBox(aa.x, aa.y, bb.x - aa.x, bb.y - aa.y, m_IsColliding);

	}
}