#pragma once
#include "glm\vec2.hpp"

struct AABB
{
	AABB() {}
	AABB(const glm::vec2& center, float halfx, float halfy)
		:myOrigin(center), halfX(halfx), halfY(halfy)
	{

	}
	glm::vec2 myOrigin;
	float halfX;
	float halfY;
};