#include "Game.h"

Game* Game::instance = nullptr;

Game::Game()
{
    instance = this;
    window = nullptr;

}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (instance->firstMouse)
    {
        instance->lastX = (float)xpos;
        instance->lastY = (float)ypos;
        instance->firstMouse = false;
    }

    float xoffset = (float)xpos - instance->lastX;
    float yoffset = instance->lastY - (float)ypos;

    instance->lastX = (float)xpos;
    instance->lastY = (float)ypos;

    instance->camera->ProcessMouseMovement(xoffset, yoffset);
}
void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    instance->camera->ProcessMouseScroll((float)yoffset);
}
void Game::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}
GLFWwindow* Game::GetWindow()
{
    return window;
}
int Game::Start()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Camera", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    sceneManager.addScene(std::make_unique<GameScene>());
    camera = sceneManager.getCurrentCamera();

    return 0;
}
void Game::Run(float pDeltaTime)
{
    processInput(window);
    deltaTime = pDeltaTime;

    sceneManager.update(deltaTime, window, SCR_WIDTH, SCR_HEIGHT); 
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        sceneManager.addScene(std::make_unique<GameScene>());
        camera = sceneManager.getCurrentCamera();
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        sceneManager.popScene();
        camera = sceneManager.getCurrentCamera();
    }
}
void Game::Cleanup()
{
    sceneManager.shutdownAll();
    glfwTerminate();
}