#include "SceneManager.h"


void SceneManager::addScene(std::unique_ptr<Scene> scene)
{
	if (sceneStack.size())
	{
		sceneStack.top()->Shutdown();
	}
	sceneStack.push(std::move(scene));
	sceneStack.top()->Init();

}
void SceneManager::popScene()
{
	if (sceneStack.size()-1) // ensure always one scene on the stack
	{
		sceneStack.top()->Shutdown();
		sceneStack.pop();
		sceneStack.top()->Restart();
	}
}
void SceneManager::update(float deltaTime, GLFWwindow* window, int w, int h)
{
	if (sceneStack.size())
	{
		sceneStack.top()->Update(deltaTime, window, w, h);
	}
}
Camera* SceneManager::getCurrentCamera()
{
	if (sceneStack.size())
	{
		return sceneStack.top()->getCamera();
	}
	return nullptr;
}
void SceneManager::shutdownAll()
{
	while (sceneStack.size())
	{
		sceneStack.top()->Shutdown();
		sceneStack.pop();
	}
}