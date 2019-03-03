#pragma once
#include "Renderable.h"
#include "Animation.h"
#include <map>
#include <string>

enum Heading
{
	LEFTFACING,
	RIGHTFACING
};
class AnimatedSprite : public Renderable
{
public:
	AnimatedSprite(const glm::vec4& position, const glm::vec2& size, Texture* texture, Heading heading);

	virtual ~AnimatedSprite();

	virtual void Update();
	virtual Animation* GetAnimation(const std::string& name);
	virtual void SetAnimation(const std::string& name);
	virtual void Reset();
	virtual bool IsDone();
	virtual void SetHeading(Heading heading);
public:

	Animation * myCurrentAnimation;
	Heading myHeading;

	std::map<std::string, Animation*> myAnimations;
};