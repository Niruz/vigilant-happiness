#pragma once
#include "RendererBase.h"
#include "IndexBuffer.h"


#include <cstddef>
#include "Renderable.h"
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	(RENDERER_VERTEX_SIZE * 4)
#define RENDERER_BUFFER_SIZE	(RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE   (RENDERER_MAX_SPRITES * 6)
#define RENDERER_MAX_TEXTURES    16

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX     1
#define SHADER_TID_INDEX    2
#define SHADER_COLOR_INDEX  3
#define SHADER_INVERT_INDEX 4

class BatchRenderer : public RendererBase
{
public:
	BatchRenderer();
	~BatchRenderer();
	void Begin() override;
	void Submit(const Renderable* renderable) override;
	void End() override;
	void Flush() override;
	void DrawString(const std::string& text, const glm::vec4& position, const Font& font, unsigned int color) override;
private:
	void Initialize();

	GLuint myVAO;
	IndexBuffer* myIBO;
	GLuint myVBO;
	GLsizei myIndexCount;

	VertexData* myBuffer;

	std::vector<GLuint> myTextureSlots;


};