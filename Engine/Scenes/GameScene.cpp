
#include "GameScene.h"
#include "glm.hpp"

void GameScene::Init()
{
    // Simple triangle (1 face of cube)
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    shader = std::make_unique<Shader>("Shaders/Basic.Shader");
}
void GameScene::Update(const float deltaTime, GLFWwindow* window, const int w, const int h)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader->getID());

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
        (float)w / (float)h, 0.1f, 100.0f);

    //so the square moves
    float color[] = { 0.0f, 0.2f, 0.9f };
    float velocity[] = { 0.5f, 0.0f, 0.0f };

    position[0] += velocity[0] * deltaTime;
    position[1] += velocity[1] * deltaTime;
    position[2] += velocity[2] * deltaTime;

    shader->AddUniformMat4("view", &view[0][0]);
    shader->AddUniformMat4("projection", &projection[0][0]);
    shader->AddUniform4f("u_Color", color);
    shader->AddUniform3f("position", position);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
void GameScene::Render() {}
void GameScene::Shutdown()
{
    position[0] = 0.0f;
    position[1] = 0.0f;
    position[2] = 0.0f;

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
