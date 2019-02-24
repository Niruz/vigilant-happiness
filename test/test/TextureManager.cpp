#include "TextureManager.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager* TextureManager::Instance()
{
	static TextureManager instance;
	return &instance;
}
void TextureManager::onInitialize()
{
	LoadTexture("Textures/test.png", "test");
}
void TextureManager::onDeinitialize()
{
	
}
bool TextureManager::LoadTexture(std::string filename, std::string identifier)
{

	//Either assume every png has alpha or check for the number of channels
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	mTextures[identifier].Generate(width, height, data);

	stbi_image_free(data);

	//return success
	return true;
}
Texture* TextureManager::GetTexture(std::string name)
{
	return &mTextures[name];
}
void TextureManager::GetUVCoordinates(int row, int column, std::vector<glm::vec2>& vec)
{
	//Maybe pass this in as a reference
	/*	vec.push_back(glm::vec2(0, 0));
	vec.push_back(glm::vec2(0, 1));
	vec.push_back(glm::vec2(1, 1));
	vec.push_back(glm::vec2(1, 0));
	*/
	float x1 = (row * 32.0f) / 512.0f;
	float x2 = ((row + 1) * 32.0f) / 512.0f;
	float y1 = (column * 32.0f) / 512.0f;
	float y2 = ((column + 1) * 32.0f) / 512.0f;

	vec.push_back(glm::vec2(x1, y1));
	vec.push_back(glm::vec2(x1, y2));
	vec.push_back(glm::vec2(x2, y2));
	vec.push_back(glm::vec2(x2, y1));
	int shit = 5;


	//0 
	//X = 32.0f/512, 64.0/512
	//Y = 
}

void TextureManager::GetUVCoordinates(int index, int width, int height, std::vector<glm::vec2>& vec)
{
	float cols = width / 32.0f;
	int rows = height / 32.0f;


	float test = index / cols;
	float test2 = index / rows;

	glm::vec2 pointIn2D;
	pointIn2D.x = index % (int)cols;
	pointIn2D.y = index / (int)cols;

	pointIn2D.y = (rows - 1) - pointIn2D.y;

	if (index == 0)
		int hohohoho = 5;


	float x1 = (pointIn2D.x * 32.0f + 1) / width;
	float x2 = ((pointIn2D.x + 1) * 32.0f - 1) / width;
	float y1 = (pointIn2D.y * 32.0f + 1) / height;
	float y2 = ((pointIn2D.y + 1) * 32.0f - 1) / height;

	vec.push_back(glm::vec2(x1, y1));
	vec.push_back(glm::vec2(x1, y2));
	vec.push_back(glm::vec2(x2, y2));
	vec.push_back(glm::vec2(x2, y1));
	int shit = 5;
	/*float x1 = (row * 32.0f) / 512.0f;
	float x2 = ((row + 1) * 32.0f) / 512.0f;
	float y1 = (column * 32.0f) / 512.0f;
	float y2 = ((column + 1) * 32.0f) / 512.0f;

	vec.push_back(glm::vec2(x1, y1));
	vec.push_back(glm::vec2(x1, y2));
	vec.push_back(glm::vec2(x2, y2));
	vec.push_back(glm::vec2(x2, y1));*/

}