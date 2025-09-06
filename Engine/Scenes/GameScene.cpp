
#include "GameScene.h"
#include "glm.hpp"
#include "../ECS/Components/Component2dPolygon.h"

void GameScene::Init()
{

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };
    unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
    };

    ent.AddComponent<ComponentPosition>(0.0f, 0.0f, 0.0f);
    ent.AddComponent<ComponentVelocity>(0.5f, 0.0f, 0.0f);
    ent.AddComponent<Component2dPolygon>(vertices, 12, indices, 6, std::make_shared<Shader>("Shaders/Basic.Shader"));

}
void GameScene::Restart()
{
    //todo
}
void GameScene::Update(const float deltaTime, GLFWwindow* window, const int w, const int h)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
        (float)w / (float)h, 0.1f, 100.0f);


    float color[] = { 0.0f, 0.2f, 0.9f };

    float* position = ent.GetComponent<ComponentPosition>("Position")->getPosition();
    float* velocity = ent.GetComponent<ComponentVelocity>("Velocity")->getVelocity();

    position[0] += velocity[0] * deltaTime;
    position[1] += velocity[1] * deltaTime;
    position[2] += velocity[2] * deltaTime;


    std::shared_ptr<Shader> shader = ent.GetComponent<Component2dPolygon>("2d Polygon")->getShader();
    shader->AddUniformMat4("view", &view[0][0]);
    shader->AddUniformMat4("projection", &projection[0][0]);
    shader->AddUniform4f("u_Color", color);
    shader->AddUniform3f("position", position);

    ent.GetComponent<Component2dPolygon>("2d Polygon")->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}
void GameScene::Shutdown()
{
    ent.GetComponent<Component2dPolygon>("2d Polygon")->Delete();
}
