#pragma once
#include <stack>
#include "../Scenes/Scene.h"

class SceneManager
{
	std::stack<std::unique_ptr<Scene>> sceneStack;


public:
	void addScene(std::unique_ptr<Scene> scene);
	void popScene();
	void update(float deltaTime, GLFWwindow* window, int w, int h);
	void render();
	Camera* getCurrentCamera();
	void shutdownAll();
};