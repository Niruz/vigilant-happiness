#pragma once
#include "Renderable.h"

class Sprite : public Renderable
{
public:
	Sprite(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color);
	//If we want single textures
	Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture);
	//If we want them from an atlas
	Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, const glm::vec2& atlasposition);
	//Converts the ID given to place in the atlas given by the width/height of the texture
	Sprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, int ID);
	~Sprite();

	void setUVSpecialized(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4);
	void increaseUVAlongX(float increase);
private:

};