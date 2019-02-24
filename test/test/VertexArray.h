#pragma once

#include <vector>
#include <glew.h>


#include "Buffer.h"


class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(Buffer* buffer, GLuint attributeIndex);

	void bind() const;
	void unbind() const;

private:
	GLuint mArrayID;
	std::vector<Buffer*> mBuffers;
};
