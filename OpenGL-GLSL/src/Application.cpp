#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <fstream>
#include <sstream>
#include <iostream>
#include "General/ShaderLoading.h"
#include "General/Macros.h"
#include "shapes/Shape.h"

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

    Shape shape = Shape(centre, vertices, 8, indices, 6, &shader);
	Shape shape2 = Shape(centre, triangleVertices, 6, indices, 3, &shader2);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		shape.draw();
        shape2.draw();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
    }

    shader.Delete();

    glfwTerminate();
    return 0;
}