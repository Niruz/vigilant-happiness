#pragma once
#include "glm\glm.hpp"
//#include "Renderable.h"
#include <vector>

class Font;
class Renderable;
class RendererBase
{
protected:
	std::vector<glm::mat4> myTransformationStack;
	const glm::mat4* myTransformationStackBack;
protected:
	RendererBase()
	{
		myTransformationStack.push_back(glm::mat4(1.0f));
		myTransformationStackBack = &myTransformationStack.back();
	}
public:
	virtual ~RendererBase() {}
	void Push(const glm::mat4& mat, bool doOverride = false)
	{
		if (doOverride)
		{
			myTransformationStack.push_back(mat);
		}
		else
		{
			myTransformationStack.push_back(myTransformationStack.back() * mat);
		}
		myTransformationStackBack = &myTransformationStack.back();
	}
	void Pop()
	{
		if (myTransformationStack.size() > 1)
			myTransformationStack.pop_back();
		myTransformationStackBack = &myTransformationStack.back();
	}
	virtual void Begin() {}
	virtual void End() {}
	virtual void Submit(const Renderable* renderable) = 0;
	virtual void Flush() = 0;
	virtual void DrawString(const std::string& text, const glm::vec4& position, const Font& font, unsigned int color) {}
};