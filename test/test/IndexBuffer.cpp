#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(GLushort *data, GLsizei count)
	: mCount(count)
{
	glGenBuffers(1, &mBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*count, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
IndexBuffer::IndexBuffer(GLuint *data, GLsizei count)
	: mCount(count)
{
	glGenBuffers(1, &mBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*count, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &mBufferID);
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBufferID);
}
void IndexBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
