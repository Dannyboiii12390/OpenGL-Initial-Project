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
#include "entities/Entity.h"
#include "entities/Components/ComponentPosition.h"
#include "entities/Components/ComponentPolygon.h"
#include "entities/Components/ComponentVelocity.h"
#include "entities/Camera.h"

//todo 
/*
create circle component
create velocity component
create shape system
create velocity system
create entity manager
create system manager
create geometry component
*/
Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
void processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = 800.0f / 2.0;
    static float lastY = 600.0 / 2.0;
    static bool firstMouse = true;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed

    lastX = (float)xpos;
    lastY = (float)ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

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

	// Set the mouse callback
    glfwSetCursorPosCallback(window, mouse_callback);
	// Capture the mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    int indices2[] = {
        0, 1, 2
    };
	float centre[] = { 0.0f, 0.0f, 0.0f };

    Shader shader = Shader("res/shaders/Basic.shader");
    Shader shader2 = Shader("res/shaders/BasicRed.shader");
    
	//entity-component-system
    /*Entity ent = Entity("Test", 2);
	Entity ent2 = Entity("Test2", 2);
	ent.addComponent(std::make_shared<ComponentPosition>(centre[0], centre[1], centre[2]));
	ent2.addComponent(std::make_shared<ComponentPosition>(centre[0], centre[1], centre[2]));

	std::shared_ptr<ComponentPosition> pos = ent.getComponent<ComponentPosition>(0);
    std::shared_ptr<ComponentPosition> pos2 = ent2.getComponent<ComponentPosition>(0);
    
	ent.addComponent(std::make_shared<ComponentPolygon>(pos->getPosition(), vertices, 8, indices, 6, &shader));
	ent2.addComponent(std::make_shared<ComponentPolygon>(pos2->getPosition(), triangleVertices, 6, indices2, 3, &shader2));
	ent.addComponent(std::make_shared<ComponentVelocity>(0.001f, 0.0f, 0.0f));*/ //x left and right, y up and down, z zoom in and out
	
    Circle circle = Circle(centre, &shader, 0.25f, 100, true);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapInterval(1); // Enables V-Sync (1 = on, 0 = off)

		//entity-component-system
       /*std::shared_ptr<ComponentVelocity> vel = ent.getComponent<ComponentVelocity>(2);
		float* v = vel->getVelocity(deltaTime);
		pos->setPosition(pos->getX() + v[0], pos->getY() + v[1], pos->getZ() + v[2]);*/
        
		glm::mat4 view = camera.GetViewMatrix();


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
		//entity-component-system
        /*std::shared_ptr<ComponentPolygon> s1 = ent.getComponent<ComponentPolygon>(1);
		std::shared_ptr<ComponentPolygon> s2 = ent2.getComponent<ComponentPolygon>(1);
#
        s1->draw();
		s2->draw();*/

		circle.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();


        
    }

    shader.Delete();
	shader2.Delete();

    glfwTerminate();
	
    
    return 0;
}