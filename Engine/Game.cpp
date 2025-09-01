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

    scene.Init();
    camera = scene.getCamera();
    //// Simple triangle (1 face of cube)
    //float vertices[] = {
    //    -0.5f, -0.5f, -0.5f,
    //     0.5f, -0.5f, -0.5f,
    //     0.5f,  0.5f, -0.5f,
    //     0.5f,  0.5f, -0.5f,
    //    -0.5f,  0.5f, -0.5f,
    //    -0.5f, -0.5f, -0.5f,
    //};

    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &VBO);
    //glBindVertexArray(VAO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    //glEnableVertexAttribArray(0);

    //shader = std::make_unique<Shader>("Shaders/Basic.Shader");
    return 0;
}
void Game::Run(float pDeltaTime)
{
    processInput(window);
    deltaTime = pDeltaTime;

    scene.Update(deltaTime, window, SCR_WIDTH, SCR_HEIGHT);
    //glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glUseProgram(shader->getID());
    // 
    //glm::mat4 view = camera.GetViewMatrix();
    //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
    //    (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    ////so the square moves
    //float color[] = { 0.0f, 0.2f, 0.9f };
    //static float position[] = { 0.0f, 0.0f, 0.0f };
    //float velocity[] = { 0.5f, 0.0f, 0.0f };

    //position[0] += velocity[0] * deltaTime;
    //position[1] += velocity[1] * deltaTime;
    //position[2] += velocity[2] * deltaTime;

    //shader->AddUniformMat4("view", &view[0][0]);
    //shader->AddUniformMat4("projection", &projection[0][0]);
    //shader->AddUniform4f("u_Color", color);
    //shader->AddUniform3f("position", position);

    //glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    //glfwSwapBuffers(window);
    //glfwPollEvents();
}
void Game::Cleanup()
{
    scene.Shutdown();
   /* glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();*/
}