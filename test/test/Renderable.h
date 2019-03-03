#pragma once
#include "glm\glm.hpp"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "RendererBase.h"
#include "Texture.h"

struct VertexData
{
	glm::vec4 vertex;
	glm::vec2 uv;
	float tid;
	unsigned int color;
	float invertColor;
};

class Renderable
{
public:
	glm::vec4 myPosition;
	glm::vec2 mySize;
	//glm::vec4 myColor;
	unsigned int myColor;
	std::vector<glm::vec2> myUVs;
	//Texture* myTexture;
	int myTexture;
	float myInvertColor;
	bool myMarkedForDeletion;

protected:
	Renderable() : myTexture(-1)
	{
		SetUVDefaults();
	}

public:

	Renderable(const glm::vec4& position, const glm::vec2& size, const unsigned int& color)
		: myPosition(position), mySize(size), myColor(color), myTexture(-1), myInvertColor(0), myMarkedForDeletion(false)
	{
		SetUVDefaults();
	}
	Renderable(const glm::vec4& position, const glm::vec2& size, const glm::vec4& color)
		: myPosition(position), mySize(size), myTexture(-1), myInvertColor(0), myMarkedForDeletion(false)
	{
		SetColor(color);
		SetUVDefaults();
	}
	virtual ~Renderable()
	{

	}

	virtual void Submit(RendererBase* renderer)
	{
		renderer->Submit(this);
	}
public:

	void SetColor(unsigned int color) { myColor = color; }
	void SetColor(const glm::vec4& color)
	{

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		myColor = a << 24 | b << 16 | g << 8 | r;
	}
	//The index in the texture Atlas to set
	void SetUVs(int row, int column);
	void SetUVs(int index, int width, int height);
	void SetTexture(Texture* texture) { myTexture = texture->getID(); }
	void SetPosition(const glm::vec4& position) { myPosition = position; }
	void SetInverted(int inverted) { myInvertColor = inverted; }
	inline const glm::vec4& GetPosition()			 const { return myPosition; }
	inline const glm::vec2& GetSize()                const { return mySize; }
	inline const unsigned int GetColor()               const { return myColor; }
	inline const std::vector<glm::vec2>& GetUVs()    const { return myUVs; }
	inline const GLuint GetTID() const { return myTexture; }
	inline const float GetInvertColor() const { return myInvertColor; }

private:
	void SetUVDefaults()
	{
		myUVs.push_back(glm::vec2(0, 0));
		myUVs.push_back(glm::vec2(0, 1));
		myUVs.push_back(glm::vec2(1, 1));
		myUVs.push_back(glm::vec2(1, 0));
	}

};