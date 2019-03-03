#include "Layer.h"
#include <glm/gtc/matrix_transform.hpp>
Layer::Layer()
{

}
Layer::Layer(RendererBase* renderer, Shader* shader, const glm::mat4& projectionMatrix)
	:myRenderer(renderer), myShader(shader), myProjectionMatrix(projectionMatrix)
{
	myShader->bind();

	myShader->setUniformMatrix4fv("projectionMatrix", 1, GL_FALSE, myProjectionMatrix);

	GLint texIDS[] = { 0, 1, 2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	myShader->setUniform1iv("textureArray[0]", texIDS, 16);

	myShader->unbind();


	/*glm::mat4 translationMatrix = glm::mat4(1.0f);
	translationMatrix = glm::translate(translationMatrix, glm::vec3(20.0f, 0.0, 0.0f));
	myRenderer->Push(translationMatrix);*/
}
Layer::~Layer()
{
	delete myRenderer;
	for (Renderable* renderable : myRenderables)
		delete renderable;
	myRenderables.clear();
}
void Layer::Add(Renderable* renderable)
{
	myRenderables.push_back(renderable);
}
void Layer::Render()
{
	myShader->bind();

	myRenderer->Begin();
	int i = 0;
	for (Renderable * renderable : myRenderables)
	{
		//just an example usage
		/*if(i % 2 == 0)
		{
		glm::mat4 translationMatrix = glm::mat4(1.0f);
		translationMatrix = glm::translate(translationMatrix, glm::vec3(10.0f, 10.0, 0.0f));
		myRenderer->Push(translationMatrix);
		myRenderer->Submit(renderable);
		myRenderer->Pop();
		}
		else
		{
		myRenderer->Submit(renderable);
		}
		i++;
		*/
		renderable->Submit(myRenderer);
	}

	//myRenderer->DrawString("Hello!", glm::vec3(0,0,1), glm::vec4(0,0,1,1));
	//myRenderer->DrawString("Hello!", glm::vec3(-640, 336, 0.8), glm::vec4(0,0,1,1));

	myRenderer->End();
	myRenderer->Flush();

	myShader->unbind();
}