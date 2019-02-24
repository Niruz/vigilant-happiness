#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &mArrayID);
}
VertexArray::~VertexArray()
{
	for (unsigned int i = 0; i < mBuffers.size(); ++i)
		delete mBuffers[i];
	glDeleteVertexArrays(1, &mArrayID);
}
void VertexArray::addBuffer(Buffer* buffer, GLuint attributeIndex)
{
	bind();
	buffer->bind();

	glEnableVertexAttribArray(attributeIndex);
	glVertexAttribPointer(attributeIndex, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);


	buffer->unbind();
	unbind();

	//beware of this 
	mBuffers.push_back(buffer);
}
void VertexArray::bind() const
{
	glBindVertexArray(mArrayID);
}
void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
