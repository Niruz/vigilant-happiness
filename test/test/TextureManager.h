#pragma once

#include "Texture.h"
#include <map>
#include <vector>
#include "glm\vec2.hpp"

#define TextureMan TextureManager::Instance()

class TextureManager
{
public:
	static TextureManager* Instance();

	///Initialization
	void onInitialize();
	///Cleanup
	void onDeinitialize();

	//identifier is what we refer the texture as
	bool LoadTexture(std::string filename, std::string identifier);

	Texture* GetTexture(std::string name);

	void GetUVCoordinates(int row, int column, std::vector<glm::vec2>& vec);

	void GetUVCoordinates(int index, int width, int height, std::vector<glm::vec2>& vec);

private:
	TextureManager() {};
	TextureManager(const TextureManager&);
	TextureManager& operator = (const TextureManager&);
	~TextureManager() {};

	std::map<std::string, Texture> mTextures;

};
