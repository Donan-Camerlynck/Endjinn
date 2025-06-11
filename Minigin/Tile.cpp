#include "Tile.h"

namespace dae
{

	Tile::Tile(BodyInfo tileBodyInfo)
		:m_Body(std::make_unique<Body>(tileBodyInfo))
	{
	}

	Tile::~Tile() = default;


}