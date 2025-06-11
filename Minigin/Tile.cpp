#include "Tile.h"
#include "Renderer.h"

namespace dae
{



	Tile::Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions, std::unique_ptr<UserDataOverlap> userDataOverlap)
		:m_Body(std::make_unique<Body>(tileBodyInfo, std::move(userDataOverlap))), m_Type(type), m_Dimensions(dimensions)
	{
		m_Body->Initialize();
	}

	Tile::~Tile() = default;

	void Tile::Render()
	{
		auto& renderer = Renderer::GetInstance();
		glm::vec2 pos{ m_Body->GetPosition() };
		renderer.RenderDebugBox(pos.x, pos.y, m_Dimensions.x, m_Dimensions.y, m_IsColliding);
	}
}