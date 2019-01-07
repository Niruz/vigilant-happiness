#pragma once
#include "Shader.h"
#include <glew.h>


#define ShaderMan ShaderManager::Instance()

enum SHADERS
{
	SIMPLE_FORWARD_SHADER,
	SIMPLE_BACKGROUND1_SHADER,
	SIMPLE_BACKGROUND2_SHADER,
	SIMPLE_BACKGROUND3_SHADER,
	SIMPLE_MENU_SHADER,
	SIMPLE_TEXTURE_SHADER,
	SIMPLE_DUNGEON_SHADER,
	SIMPLE_GRAVEYARD_SHADER,
	MAX_SHADERS
};

class ShaderManager
{
private:
	ShaderManager() {};
	ShaderManager(const ShaderManager&);
	ShaderManager& operator = (const ShaderManager&);
	~ShaderManager() {};
public:


	static ShaderManager* Instance();


	///Initialize all the shaders
	void onInitialize();
	///Cleanup all the shaders
	void onDeinitialize();

	Shader* getShader(const int shaderType);


	///********************* MOST OF THE FUNCTIONS BELOW ARE A BIT REDUNDANT, BUT ARE STILL KEPT FOR FUTURE REFERENCES ***////////

	//Binds the shader to use, ranging from BASIC_SHADER to MAX_SHADER
	//Does not use any assert function to check validity, beware
	void bindShader(const int shaderType);
	void unbindShader();

	///Gets the program id of the shader
	const int getShaderProgram(const int shaderType);
	///Gets the program id of the active shader
	const int getActiveShaderProgram();
	///Gets the reference of the active shader
	Shader& getActiveShader();
	///Gets the 'mCurrentActiveShader'
	const int getActiveShaderName();

	//Let the shadermanager handle all calls to shaders
	//Get active shader is called in order to assert the validity
	inline void setUniformMatrix4fv(const char* inName, int count, bool transpose, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getActiveShader().getUniformLocation(inName), count, transpose, &matrix[0][0]);
	}
	inline void setUniformMatrix3fv(const char* inName, int count, bool transpose, const glm::mat4& matrix)
	{
		glUniformMatrix3fv(getActiveShader().getUniformLocation(inName), count, transpose, &matrix[0][0]);
	}
	inline void setUniform4f(const char* inName, const glm::vec4& vec)
	{
		glUniform4f(getActiveShader().getUniformLocation(inName), vec.x, vec.y, vec.z, vec.w);
	}
	inline void setUniform3f(const char* inName, const glm::vec3& vec)
	{
		glUniform3f(getActiveShader().getUniformLocation(inName), vec.x, vec.y, vec.z);
	}
	inline void setUniform3fv(const char* inName, GLsizei count, const glm::vec3& vec)
	{
		glUniform3fv(getActiveShader().getUniformLocation(inName), count, &vec[0]);
	}
	inline void setUniform2fv(const char* inName, GLsizei count, const glm::vec2& vec)
	{
		glUniform2fv(getActiveShader().getUniformLocation(inName), count, &vec[0]);
	}
	inline void setUniform2f(const char* inName, const glm::vec2& vec)
	{
		glUniform2f(getActiveShader().getUniformLocation(inName), vec.x, vec.y);
	}
	inline void setUniform1i(const char* inName, const int value)
	{
		glUniform1i(getActiveShader().getUniformLocation(inName), value);
	}
	inline void setUniform1fv(const char* inName, float* value, int count)
	{
		glUniform1fv(getActiveShader().getUniformLocation(inName), count, value);
	}
	inline void setUniform1f(const char* inName, float value)
	{
		glUniform1f(getActiveShader().getUniformLocation(inName), value);
	}
	//NOTE, ON SOME DRIVERS YOU NEED TO USE THE NAME AND THE ARRAY SUBSCRIPT [0]
	inline void setUniform1iv(const char* inName, int* value, int count)
	{
		//NOTE, ON SOME DRIVERS YOU NEED TO USE THE NAME AND THE ARRAY SUBSCRIPT [0]
		glUniform1iv(getActiveShader().getUniformLocation(inName), count, value);
	}
private:

	///Initialize a shader
	void initShader(int inEnumName, const char* inVSname, const char* inFSname, const char* inGEOname = NULL);
	///Initialize uniforms reads all uniforms in each shader and maps their name to the location of the uniform
	void initUniforms();
	///Function used to load shaders into memory
	bool loadFile(const char* inFileName, std::string& outFileStr);
	///Function used to load shaders into memory
	const unsigned int loadShader(const std::string& source, const unsigned int mode);

	Shader mShaders[MAX_SHADERS];

	// The number of current shaders 
	int mCurrentNumOfShaders;
	// Easy way to access the current active shader
	int mCurrentActiveShader;
};


