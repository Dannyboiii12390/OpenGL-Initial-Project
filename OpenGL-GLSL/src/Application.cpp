#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <fstream>
#include <sstream>
#include <iostream>
#include "General/ShaderLoading.h"
#include "General/Macros.h"
#include "shapes/Polygon.h"
#include "shapes/Circle.h"
#include <chrono>
#include <fstream>

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "OpenGL";

static int initOpenGL(GLFWwindow*& window)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        LOG("Error! \n");
        return -1;
    }
    return 1;
}

int main(void)
{
    GLFWwindow* window = nullptr;
	if (initOpenGL(window) == -1) return -1;
	//Drawing draw;
	LOG("OpenGL Version: " << glGetString(GL_VERSION) << "\n");


    float vertices[] = {
        -0.5f, -0.5f,
         0.5f,  -0.5f,
         0.5f, 0.5f,
         -0.5f, 0.5f,
	};
    float triangleVertices[] = {
        // x,     y
        -1.0f, -1.0f,  // Bottom left
         0.5f, -0.5f,  // Bottom right
         0.0f,  0.5f   // Top center
    };
    int indices[] = {
        0, 1, 2,
        2, 3, 0
	};
	float centre[] = { 0.0f, 0.0f, 0.0f };
    

    Shader shader = Shader("res/shaders/Basic.shader");
    Shader shader2 = Shader("res/shaders/BasicRed.shader");

    Polygon shape = Polygon(centre, vertices, 8, indices, 6, &shader);
    //Polygon shape2 = Polygon(centre, triangleVertices, 6, indices, 3, &shader2);
	Circle circle = Circle(centre, &shader2, 1.0f, 100, false);
    
    //timer
	using namespace std::chrono;
    auto lastTime = high_resolution_clock::now();
    int frames = 0;
    float fps = 0.0f;
    // Open file to write FPS
    std::ofstream fpsFile("fps_log.txt");



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = high_resolution_clock::now();
        float deltaTime = duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();

		frames++;
        // Every second, update FPS
        if (deltaTime >= 1.0f)
        {
            fps = frames / deltaTime;
            frames = 0;
            lastTime = currentTime;

			fpsFile << "FPS: " << fps << "\n";
            
        }


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		shape.draw();
        //shape2.draw();
		circle.draw();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


        
    }

    shader.Delete();
	shader2.Delete();

    glfwTerminate();
	fpsFile << std::endl;
    fpsFile.close();
    return 0;
}