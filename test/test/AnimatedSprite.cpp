#include "AnimatedSprite.h"
AnimatedSprite::AnimatedSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading)
	: Renderable(position, size, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), myHeading(heading)
{
	myTexture = texture->getID();



}
AnimatedSprite::~AnimatedSprite()
{
	for (auto iterator : myAnimations)
		delete iterator.second;
}
void AnimatedSprite::Update()
{
	myCurrentAnimation->Update();
	//Need to get them every frame since it changes
	myUVs = myCurrentAnimation->myCurrentIndices;

	//TODO: Precalculate this
	if (myHeading == LEFTFACING)
	{
		glm::vec2 p0 = myUVs[0];
		glm::vec2 p1 = myUVs[1];
		glm::vec2 p2 = myUVs[2];
		glm::vec2 p3 = myUVs[3];

		myUVs[0] = p3;
		myUVs[1] = p2;

		myUVs[2] = p1;
		myUVs[3] = p0;
	}

}
Animation* AnimatedSprite::GetAnimation(const std::string& name)
{
	return myAnimations[name];
}
void AnimatedSprite::SetAnimation(const std::string& name)
{
	myCurrentAnimation = GetAnimation(name);

}
void AnimatedSprite::Reset()
{
	myCurrentAnimation->Reset();
}
bool AnimatedSprite::IsDone()
{
	return myCurrentAnimation->IsDone();
}
void AnimatedSprite::SetHeading(Heading heading)
{
	/*	glm::vec2 p0 = myUVs[0];
	glm::vec2 p1 = myUVs[1];
	glm::vec2 p2 = myUVs[2];
	glm::vec2 p3 = myUVs[3];

	myUVs[0] = p3;
	myUVs[1] = p2;

	myUVs[2] = p1;
	myUVs[3] = p0;*/
	myHeading = heading;
}