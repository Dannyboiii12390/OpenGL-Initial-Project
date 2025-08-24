#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <fstream>
#include <sstream>
#include <iostream>
#include "General/ShaderLoading.h"
#include "General/Drawing.h"
#include "General/Macros.h"

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
        Log("Error! \n");
        return -1;
    }
    return 1;
}

int main(void)
{
    GLFWwindow* window = nullptr;
	if (initOpenGL(window) == -1) return -1;
	Drawing draw;
	Log("OpenGL Version: " << glGetString(GL_VERSION) << "\n");


    float positions[] = {
        -0.5f, -0.5f,
         0.5f,  -0.5f,
         0.5f, 0.5f,
         -0.5f, 0.5f,
	};
    int indices[] = {
        0, 1, 2,
        2, 3, 0
	};

    draw.staticPolygon(positions, sizeof(positions), indices, sizeof(indices));

	Shader shader("res/shaders/Basic.shader");

	shader.Bind();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        
    }

    shader.Delete();

    glfwTerminate();
    return 0;
}