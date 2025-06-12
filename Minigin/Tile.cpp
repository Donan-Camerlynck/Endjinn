#include "Tile.h"
#include "Renderer.h"

namespace dae
{



	Tile::Tile(BodyInfo tileBodyInfo, TileType type, glm::vec2 dimensions, std::unique_ptr<UserDataOverlap> userDataOverlap)
		:m_pBody(std::make_unique<Body>(tileBodyInfo, std::move(userDataOverlap))), m_Type(type), m_Dimensions(dimensions)
	{
		m_pBody->Initialize();
	}

	Tile::~Tile() = default;

	void Tile::Render()
	{
		auto& renderer = Renderer::GetInstance();
		glm::vec2 pos{ m_pBody->GetPosition() };
		glm::vec2 dimension{ m_pBody->GetDimensions() };
		//renderer.RenderDebugBox(pos.x, pos.y, dimension.x, dimension.y, m_IsColliding);

		glm::vec2 aa{ get<0>(m_pBody->GetAABB()) };
		glm::vec2 bb{ get<1>(m_pBody->GetAABB()) };
		renderer.RenderDebugBox(aa.x, aa.y, bb.x - aa.x, bb.y - aa.y, m_IsColliding);

	}
}