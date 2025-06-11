#include "Tile.h"
#include "Renderer.h"

namespace dae
{



	Tile::Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions)
		:m_Body(std::make_unique<Body>(tileBodyInfo)), m_Type(type), m_Dimensions(dimensions)
	{
		m_Body->Initialize();
	}

	Tile::~Tile() = default;

	void Tile::Render()
	{
		auto& renderer = Renderer::GetInstance();
		glm::vec2 pos{ m_Body->GetPosition() };
		renderer.RenderBox(pos.x, pos.y, m_Dimensions.x, m_Dimensions.y);
	}
}