#pragma once

#include <glew.h>


class Buffer
{
public:
	Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
	~Buffer();

	void bind() const;
	void unbind() const;

	GLuint getComponentCount() { return mComponentCount; };

private:
	GLuint mBufferID;
	GLuint mComponentCount;
};
