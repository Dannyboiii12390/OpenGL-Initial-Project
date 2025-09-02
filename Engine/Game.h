#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include "General/Camera.h"
#include "General/Shader.h"
#include "Scenes/GameScene.h"
#include <memory>
#include "Managers/SceneManager.h"

class Game
{
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	Camera* camera = nullptr;
	GLFWwindow* window = nullptr;

	SceneManager sceneManager;

	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;
	float lastFrame = 0.0f;

	float deltaTime = 0.0f;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow* window);

public: 

	static Game* instance;

	Game();	

	int Start();
	void Run(float deltaTime);
	void Cleanup();
	GLFWwindow* GetWindow();


};