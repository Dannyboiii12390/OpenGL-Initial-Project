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

#include <fstream>
#include <string>

class FPSCounter
{
public:
    FPSCounter(const std::string& filename = "fps.txt")
        : frameCount(0), timeAccumulator(0.0f), outFile(filename)
    {
        if (!outFile.is_open())
        {
            std::cerr << "Error: Could not open " << filename << " for writing.\n";
        }
    }
    void update(float deltaTime)
    {
        if (!outFile.is_open()) return;

        frameCount++;
        timeAccumulator += deltaTime;

        if (timeAccumulator >= 1.0f)
        {
            outFile << "FPS: " << frameCount << std::endl;
            outFile.flush(); // Ensure immediate write

            frameCount = 0;
            timeAccumulator = 0.0f;
        }
    }
    void close()
    {
        if (outFile.is_open())
        {
            outFile.close();
        }
    }
    ~FPSCounter()
    {
        close();
    }

private:
    int frameCount;
    float timeAccumulator;
    std::ofstream outFile;
};


class Game
{
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

	Camera* camera = nullptr;
	GLFWwindow* window = nullptr;

    FPSCounter fps;

	SceneManager sceneManager;

	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;
	float lastFrame = 0.0f;

	float deltaTime = 0.0f;

    Game(const Game& g) = delete;
    Game& operator=(const Game& g) = delete;


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