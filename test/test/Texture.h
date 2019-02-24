#pragma once

#include <string>
#include <glew.h>



class Texture
{
private:
	std::string mPath;
	GLuint mID;
	GLuint mWidth, mHeight;
	GLuint mInternalFormat, mImageFormat;
	GLuint mWrap_S, mWrap_T;
	GLuint mFilterMin, mFilterMax;
public:
	Texture();
	Texture(GLuint internalFormat, GLuint imageFormat, GLuint wrapS, GLuint wrapT, GLuint filtermin, GLuint filtermax);

	void Generate(GLuint width, GLuint height, unsigned char* data);

	~Texture();
	void bind() const;
	void unbind() const;

	void setInternalFormat(GLuint internalformat) { mInternalFormat = internalformat; };
	void setImageFormat(GLuint imageformat) { mImageFormat = imageformat; };
	void setWrapperFormat(GLuint s, GLuint t) { mWrap_S = s; mWrap_T = t; }
	void setFilterFormat(GLuint min, GLuint max);

	inline const unsigned int getWidth() const { return mWidth; };
	inline const unsigned int getHeight() const { return mHeight; };
	inline const unsigned int getID() const { return mID; };

private:
};
