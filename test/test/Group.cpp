#include "Group.h"
#include <glm/gtc/matrix_transform.hpp>
Group::Group(const glm::mat4& mat)
	: myTransformationMatrix(mat)
{

}
Group::Group(const glm::mat4& mat, float zValue)
	: myTransformationMatrix(mat), myZValue(zValue)
{

}
Group::~Group()
{
	for (Renderable* renderable : myRenderables)
		delete renderable;
	myRenderables.clear();
}
void Group::Submit(RendererBase* renderer)
{
	renderer->Push(myTransformationMatrix);
	//Add this to some sort of dynamic group if we want all renderables to be deleted when marked for deletion
	/*	std::vector<Renderable*>::iterator it = myRenderables.begin();

	while (it != myRenderables.end())
	{

	if ((*it)->myMarkedForDeletion)
	{

	it = myRenderables.erase(it);
	}
	else
	{
	(*it)->Submit(renderer);
	++it;
	}

	}*/
	for (Renderable* renderable : myRenderables)
	{
		if (!renderable->myMarkedForDeletion)
			renderable->Submit(renderer);
	}
	renderer->Pop();
};
void Group::Add(Renderable* renderable)
{
	myRenderables.push_back(renderable);
}

void Group::UpdateXYAxis(const glm::vec2& axis)
{
	glm::mat4 trans = glm::mat4(1.0f);
	myTransformationMatrix = glm::translate(trans, (glm::vec3(axis.x, axis.y, myZValue)));
}