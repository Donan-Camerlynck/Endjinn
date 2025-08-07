#pragma once
#include <glm.hpp>

namespace dae
{
	class GameObject;

	struct UserDataOverlap
	{
		bool isGameObject{ false };
		int row{};
		int column{};
		GameObject* GameObject{};

	};

    struct Rect
    {
        glm::vec2 position; // Top-left corner
        glm::vec2 size;

        Rect() = default;
        Rect(const glm::vec2& pos, const glm::vec2& sz)
            : position(pos), size(sz) {
        }

        glm::vec2 GetMin() const { return position; }
        glm::vec2 GetMax() const { return position + size; }

        bool Contains(const glm::vec2& point) const
        {
            return point.x >= position.x && point.x <= position.x + size.x &&
                point.y >= position.y && point.y <= position.y + size.y;
        }

        bool Intersects(const Rect& other) const
        {
            return !(GetMax().x <= other.GetMin().x || GetMin().x >= other.GetMax().x ||
                GetMax().y <= other.GetMin().y || GetMin().y >= other.GetMax().y);
        }
    };
}