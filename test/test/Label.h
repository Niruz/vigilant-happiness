#pragma once
#include "Renderable.h"
#include <string>
class Label : public Renderable
{
public:
	Label(const std::string& text, float x, float y, Font* font, const glm::vec4& color);
	Label(const std::string& text, const glm::vec4& pos, Font* font, const glm::vec4& color);
	Label(const std::string& text, const glm::vec4& pos, const std::string& font, const glm::vec4& color);
	void Submit(RendererBase* renderer) override;
public:

	Font * myFont;
	std::string myText;
};