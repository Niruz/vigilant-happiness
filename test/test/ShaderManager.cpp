#include "ShaderManager.h"
#include <assert.h>
#include <fstream>
#include <iostream>



ShaderManager* ShaderManager::Instance()
{
	static ShaderManager instance;
	return &instance;
}
void ShaderManager::bindShader(const int shaderType)
{
	glUseProgram(mShaders[shaderType].mProgram);
	mCurrentActiveShader = shaderType;
}
void ShaderManager::unbindShader()
{
	glUseProgram(0);
	mCurrentActiveShader = -1;
}
const int ShaderManager::getShaderProgram(const int shaderType)
{
	return mShaders[shaderType].mProgram;
}
const int ShaderManager::getActiveShaderProgram()
{
	assert(mCurrentActiveShader != -1);
	return mShaders[mCurrentActiveShader].mProgram;
}
Shader* ShaderManager::getShader(const int shaderType)
{
	return &mShaders[shaderType];
}
Shader& ShaderManager::getActiveShader()
{
	if (mCurrentActiveShader == -1)
		assert(mCurrentActiveShader != -1 && "ERROR: There is no active shader!");
	return mShaders[mCurrentActiveShader];
}
const int ShaderManager::getActiveShaderName()
{
	return mCurrentActiveShader;
}
bool ShaderManager::loadFile(const char* inFileName, std::string& outFileStr)
{
	///open up an in stream
	std::ifstream in(inFileName);
	///If it fails to open, return
	if (!in.is_open())
		return false;

	///Temporary char to hold a line
	char tmp[300];
	while (!in.eof())
	{
		///Get the line
		in.getline(tmp, 300);
		///Read in the the line to the string
		outFileStr += tmp;
		outFileStr += '\n';
	}

	return true;
}
const unsigned int ShaderManager::loadShader(const std::string& source, const unsigned int mode)
{
	///id used by opengl to reference the shader object
	unsigned int id;
	///Gl create shader creates a shader object with a certain specified shadertype
	id = glCreateShader(mode);
	const char* csource = source.c_str();
	///glShaderSource sets the source code in shader to the source code in the array of strings specified by string, number of strings is the second parameter (count)
	glShaderSource(id, 1, &csource, NULL);
	///Compiles the shader and used the reference to find it
	glCompileShader(id);



	///Check if there were any errors
	char error[1000];
	glGetShaderInfoLog(id, 1000, NULL, error);
	std::cout << "Compile Status: \n" << error << std::endl;

	return id;
}
void ShaderManager::onInitialize()
{
	initShader(SIMPLE_FORWARD_SHADER, "Shaders/forwardVertex.glsl", "Shaders/fragmentVertex.glsl");
	initShader(SIMPLE_SHADER, "Shaders/simpleVertex.glsl", "Shaders/simpleFragment.glsl");
	initUniforms();
}

void ShaderManager::onDeinitialize()
{
	for (int i = 0; i < MAX_SHADERS; ++i)
	{
		glDetachShader(mShaders[i].mProgram, mShaders[i].mVertexShader);
		glDetachShader(mShaders[i].mProgram, mShaders[i].mFragmentShader);
		glDeleteShader(mShaders[i].mVertexShader);
		glDeleteShader(mShaders[i].mFragmentShader);
		if (mShaders[i].mGeometryShader != -1)
			glDeleteShader(mShaders[i].mGeometryShader);
		glDeleteProgram(mShaders[i].mProgram);
	}
}
void ShaderManager::initShader(int inEnumName, const char* inVSname, const char* inFSname, const char* inGEOname)
{
	std::cout << "Initializing Shader(" << std::to_string(inEnumName) << "):" << std::endl;

	std::string source;
	bool success;
	bool useGEOshader = false;

	//Checks if the current shader has a geometry shader
	if (inGEOname)
		useGEOshader = true;

	///Load the vertex shader
	source = "";
	success = loadFile(inVSname, source);
	assert(success && "ERROR: Failed to load the vertex shader");
	mShaders[inEnumName].mVertexShader = loadShader(source, GL_VERTEX_SHADER);

	///Load the fragment shader
	source = "";
	success = loadFile(inFSname, source);
	assert(success && "ERROR: Failed to load the fragment shader");
	mShaders[inEnumName].mFragmentShader = loadShader(source, GL_FRAGMENT_SHADER);

	///Load the geometry shader
	if (useGEOshader)
	{
		source = "";
		success = loadFile(inGEOname, source);
		assert(success && "ERROR: Failed to load the geometry shader");
		mShaders[inEnumName].mGeometryShader = loadShader(source, GL_GEOMETRY_SHADER);
	}

	///Creates, links and compiles the shader
	mShaders[inEnumName].mProgram = glCreateProgram();
	glAttachShader(mShaders[inEnumName].mProgram, mShaders[inEnumName].mVertexShader);
	glAttachShader(mShaders[inEnumName].mProgram, mShaders[inEnumName].mFragmentShader);
	if (useGEOshader)
		glAttachShader(mShaders[inEnumName].mProgram, mShaders[inEnumName].mGeometryShader);
	glLinkProgram(mShaders[inEnumName].mProgram);

	///Check if the compilation went without any problems
	GLint compiled;
	glGetProgramiv(mShaders[inEnumName].mProgram, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
		std::cout << "Shader Compilation Error" << std::endl;

	///Check if the linking went without any problems
	GLint linked;
	glGetProgramiv(mShaders[inEnumName].mProgram, GL_LINK_STATUS, &linked);
	if (!linked)
		std::cout << "Shader Linkage Error" << std::endl;

	if (!compiled || !linked)
	{
		char error[256];
		for (int i = 0; i < 256; i++)
			error[i] = NULL;

		//Compilation errors
		glGetProgramInfoLog(mShaders[inEnumName].mProgram, 256, NULL, error);
		if (error[0] != 0)
			std::cout << error << std::endl;

		for (int i = 0; i < 256; i++)
			error[i] = NULL;

		//Linkage errors
		glGetProgramInfoLog(mShaders[inEnumName].mProgram, 256, NULL, error);
		if (error[0] != 0)
			std::cout << error << std::endl;
	}
}
void ShaderManager::initUniforms()
{
	int numberOfUniforms = -1;
	int nameLength = -1, uniformSize = -1;
	GLenum type = 0;
	char name[32];
	int location = -1;

	for (unsigned int shaderIt = 0; shaderIt < MAX_SHADERS; shaderIt++)
	{
		glGetProgramiv(mShaders[shaderIt].mProgram, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
		for (int uniformIt = 0; uniformIt < numberOfUniforms; uniformIt++)
		{
			glGetActiveUniform(mShaders[shaderIt].mProgram, uniformIt, sizeof(name) - 1, &nameLength, &uniformSize, &type, name);
			location = -1;
			location = glGetUniformLocation(mShaders[shaderIt].mProgram, name);

			/*	std::cout << "Uniform Info Shader(" << shaderIt << "): Name: '" << name << "' Location: " << location << " Type: '";
			if (type == GL_FLOAT_MAT4)	std::cout << "mat4";
			else if (type == GL_FLOAT_VEC3) std::cout << "vec3";
			else if (type == GL_FLOAT_VEC4) std::cout << "vec4";
			else if (type == GL_FLOAT)		std::cout << "float";
			else if (type == GL_INT)		std::cout << "int";
			else if (type == GL_BOOL)		std::cout << "bool";
			else if (type == GL_SAMPLER_2D) std::cout << "sampler2d";
			else							std::cout << type;
			std::cout << "'" << std::endl; */


			mShaders[shaderIt].setUniformLocation(name, location);
		}
		std::cout << std::endl;
	}
}
