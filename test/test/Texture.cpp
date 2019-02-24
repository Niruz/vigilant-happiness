#include "Texture.h"


/*
Texture::Texture()
	: mWidth(0), mHeight(0), mInternalFormat(GL_RGB), mImageFormat(GL_BGR), mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilterMin(GL_NEAREST), mFilterMax(GL_NEAREST)
{
	glGenTextures(1, &mID);
}*/
Texture::Texture()
	: mWidth(0), mHeight(0), mInternalFormat(GL_RGBA), mImageFormat(GL_RGBA), mWrap_S(GL_REPEAT), mWrap_T(GL_REPEAT), mFilterMin(GL_NEAREST), mFilterMax(GL_NEAREST)
{
	glGenTextures(1, &mID);
}
Texture::Texture(GLuint internalFormat, GLuint imageFormat, GLuint wrapS, GLuint wrapT, GLuint filtermin, GLuint filtermax)
	: mInternalFormat(internalFormat), mImageFormat(imageFormat), mWrap_S(wrapS), mWrap_T(wrapT), mFilterMin(filtermin), mFilterMax(filtermax)
{

}
Texture::~Texture()
{
	glDeleteTextures(1, &mID);
}
void Texture::Generate(GLuint width, GLuint height, unsigned char* data)
{
	bind();
	mWidth = width;
	mHeight = height;

	glTexImage2D(GL_TEXTURE_2D, 0, mInternalFormat, mWidth, mHeight, 0, mImageFormat, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrap_T);
	//note to self, this is just the filtering method when scaling up or down a texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mFilterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mFilterMax);

	unbind();
}
//TODO: should the glActiveTexture(GL_TEXTURE0) call be done from here?
//Or whoever is calling should probably know which one to bind
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, mID);
}
void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::setFilterFormat(GLuint min, GLuint max)
{
	mFilterMin = min;
	mFilterMax = max;
}