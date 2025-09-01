#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "../General/Shader.h"
#include "../General/Camera.h"
#include <memory>

class Scene
{
	//EntityManager entManager;
	//InputManager* inpManager;
	//systemManager sysManager;
protected:
	Camera camera;
public: 

	Camera* getCamera() { return &camera; };
	virtual void Init() = 0;
	virtual void Update(const float deltaTime, GLFWwindow* window, const int w, const int h) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
};