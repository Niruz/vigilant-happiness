#include "Font.h"
//"Fonts/SourceSansPro-Light.ttf"
Font::Font(const std::string& name, const std::string& filename, int size)
	: myName(name), myFilename(filename), mySize(size)
{
	myFTAtlas = ftgl::texture_atlas_new(512, 512, 2);
	myFTFont = ftgl::texture_font_new_from_file(myFTAtlas, size, filename.c_str());
}
Font::~Font()
{

}