#include "SceneManager.h"


void SceneManager::addScene(std::unique_ptr<Scene> scene)
{
	if (!sceneStack.empty())
	{
		sceneStack.top()->Shutdown();  // Clean up current scene
	}
	sceneStack.push(std::move(scene));
	sceneStack.top()->Init();

}
void SceneManager::popScene()
{
	if (!sceneStack.empty())
	{
		sceneStack.top()->Shutdown();
		sceneStack.pop();
		sceneStack.top()->Init();
	}
}
void SceneManager::update(float deltaTime, GLFWwindow* window, int w, int h)
{
	if (!sceneStack.empty())
	{
		sceneStack.top()->Update(deltaTime, window, w, h);
	}
}
void SceneManager::render()
{
	if (!sceneStack.empty())
	{
		sceneStack.top()->Render();
	}
}
Camera* SceneManager::getCurrentCamera()
{
	if (!sceneStack.empty())
	{
		return sceneStack.top()->getCamera();
	}
	return nullptr;
}
void SceneManager::shutdownAll()
{
	while (!sceneStack.empty())
	{
		sceneStack.top()->Shutdown();
		sceneStack.pop();
	}
}