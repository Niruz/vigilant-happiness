#pragma once
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	//Map the name of an uniform to its location.
	void setUniformLocation(const char* inName, const int inLocation);
	int  getUniformLocation(const char* inName);


	const void bind() const;
	const void unbind() const;

	const int getID() const { return mProgram; };

	int mVertexShader;
	int mFragmentShader;
	int mGeometryShader;
	int mProgram;


	inline void setUniformMatrix4fv(const char* inName, int count, bool transpose, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(inName), count, transpose, &matrix[0][0]);
	}
	inline void setUniformMatrix3fv(const char* inName, int count, bool transpose, const glm::mat4& matrix)
	{
		glUniformMatrix3fv(getUniformLocation(inName), count, transpose, &matrix[0][0]);
	}
	inline void setUniform4f(const char* inName, const glm::vec4& vec)
	{
		glUniform4f(getUniformLocation(inName), vec.x, vec.y, vec.z, vec.w);
	}
	inline void setUniform3f(const char* inName, const glm::vec3& vec)
	{
		glUniform3f(getUniformLocation(inName), vec.x, vec.y, vec.z);
	}
	inline void setUniform2f(const char* inName, const glm::vec2& vec)
	{
		glUniform2f(getUniformLocation(inName), vec.x, vec.y);
	}
	inline void setUniform1i(const char* inName, const int value)
	{
		glUniform1i(getUniformLocation(inName), value);
	}
	inline void setUniform1fv(const char* inName, float* value, int count)
	{
		glUniform1fv(getUniformLocation(inName), count, value);
	}
	inline void setUniform1iv(const char* inName, int* value, int count)
	{
		//NOTE, ON SOME DRIVERS YOU NEED TO USE THE NAME AND THE ARRAY SUBSCRIPT [0]
		glUniform1iv(getUniformLocation(inName), count, value);
	}

private:

	std::map<std::string, int> mUniforms;

};