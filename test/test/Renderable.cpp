#include "Renderable.h"
#include "TextureManager.h"


void Renderable::SetUVs(int row, int column)
{
	myUVs.clear();
	TextureMan->GetUVCoordinates(row, column, myUVs);
}
void Renderable::SetUVs(int index, int width, int height)
{
	myUVs.clear();
	TextureMan->GetUVCoordinates(index, width, height, myUVs);
}