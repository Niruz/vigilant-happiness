#pragma once
#include "ext/freetype-gl/freetype-gl.h"

#include <string>
class Font
{
public:
	Font(const std::string& name, const std::string& filename, int size);
	~Font();

	inline const std::string& GetName() const { return myName; }
	inline const std::string& GetFileName() const { return myFilename; }
	inline const int GetSize() const { return mySize; }
	inline const unsigned int GetID() const { return myFTAtlas->id; }

	inline ftgl::texture_font_t* GetFTFont() const { return myFTFont; };
	inline ftgl::texture_atlas_t* GetFTAtlas() const { return myFTAtlas; };
private:
	ftgl::texture_atlas_t* myFTAtlas;
	ftgl::texture_font_t*  myFTFont;

	int mySize;
	std::string myFilename;
	std::string myName;
};