#pragma once

#include <glew.h>


class IndexBuffer
{
public:
	//Glushorts since were taking in indexes which are positive
	//If we run out, just change to int, for now its 2^16 values
	IndexBuffer(GLushort *data, GLsizei count);
	IndexBuffer(GLuint *data, GLsizei count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	GLuint getCount() const { return mCount; };

private:
	GLuint mBufferID;
	GLuint mCount;
};
