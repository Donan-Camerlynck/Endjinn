#pragma once
#include <glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(int x, int y, int z);
	private:
		glm::ivec3 m_position;
	};
}
