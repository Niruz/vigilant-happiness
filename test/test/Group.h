#pragma once

#include "Renderable.h"
class Group : public Renderable
{
public:
	Group(const glm::mat4& mat);
	Group(const glm::mat4& mat, float zValue);
	virtual ~Group();
	void Submit(RendererBase* renderer) override;

	void Add(Renderable* renderable);

	void SetTransformationMatrix(const glm::mat4& mat) { myTransformationMatrix = mat; }
	glm::mat4 GetTransformationMatrix() const { return myTransformationMatrix; }

	void UpdateXYAxis(const glm::vec2& axis);
private:
	std::vector<Renderable*> myRenderables;
	glm::mat4 myTransformationMatrix;

	float myZValue;
};