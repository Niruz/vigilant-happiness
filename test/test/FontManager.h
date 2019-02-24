#pragma once


#include <map>
class Font;

#define FontMan FontManager::Instance()

class FontManager
{
public:
	static FontManager* Instance();

	///Initialization
	void onInitialize();
	///Cleanup
	void onDeinitialize();

	//identifier is what we refer the texture as
	bool LoadFont(std::string filename, std::string identifier, int size);

	Font* GetFont(std::string name);


private:
	FontManager() {};
	FontManager(const FontManager&);
	FontManager& operator = (const FontManager&);
	~FontManager() {};

	std::map<std::string, Font*> myFonts;
};
