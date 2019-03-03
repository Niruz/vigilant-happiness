#include "Sprite.h"
Sprite::Sprite(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color)
	:Renderable(position, size, color)
{

}
Sprite::Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture)
	: Renderable(position, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	myTexture = texture->getID();
}
Sprite::~Sprite()
{
	int shit = 5;
}
Sprite::Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, const glm::vec2& atlasposition)
	: Renderable(position, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	myTexture = texture->getID();
	SetUVs(atlasposition.x, atlasposition.y);
}
Sprite::Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, int ID)
	: Renderable(position, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
	myTexture = texture->getID();
	SetUVs(ID, texture->getWidth(), texture->getHeight());
}
void Sprite::setUVSpecialized(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4)
{
	myUVs.clear();
	myUVs.push_back(p1);
	myUVs.push_back(p2);
	myUVs.push_back(p3);
	myUVs.push_back(p4);
}
void Sprite::increaseUVAlongX(float increase)
{
	myUVs[0].x += increase;
	myUVs[1].x += increase;
	myUVs[2].x += increase;
	myUVs[3].x += increase;
}