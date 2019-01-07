#include "Shader.h"


Shader::Shader() :
	mVertexShader(-1),
	mFragmentShader(-1),
	mGeometryShader(-1),
	mProgram(-1)
{

}
Shader::~Shader()
{

}
void Shader::setUniformLocation(const char* inName, const int inLocation)
{
	mUniforms[inName] = inLocation;
}

int Shader::getUniformLocation(const char* inName)
{
	if (mUniforms.find(std::string(inName)) != mUniforms.end())
		return mUniforms[inName];
	else
		return -1;
}
const void Shader::bind() const
{
	glUseProgram(mProgram);
}
const void Shader::unbind() const
{
	glUseProgram(0);
}
