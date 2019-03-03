#pragma once
#include "Renderable.h"
#include "RendererBase.h"
#include <vector>
#include "Shader.h"
class Layer
{
protected:
	RendererBase * myRenderer;
	std::vector<Renderable*> myRenderables;
	Shader* myShader;

	glm::mat4 myProjectionMatrix;

public:
	Layer();
public:
	Layer(RendererBase* renderer, Shader* shader, const glm::mat4& projectionMatrix);
public:
	virtual ~Layer();
	virtual void Add(Renderable* renderable);
	virtual void Render();

	inline const std::vector<Renderable*>& GetRenderables() const { return myRenderables; }
};
