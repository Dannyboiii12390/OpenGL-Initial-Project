
#include "GameScene.h"
#include "glm.hpp"
#include "../ECS/Components/Component2dPolygon.h"
#include "../ECS/Components/ComponentCircle.h"
#include "../ECS/Components/ComponentSphere.h"

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
    ent.AddComponent<ComponentCircle>(std::make_shared<Shader>("Shaders/Basic.Shader"));
    ent.AddComponent<ComponentSphere>(std::make_shared<Shader>("Shaders/Basic.Shader"), 0.5f);

    sysVel.AddEntity(&ent);

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
    
    
    float colorR[] = { 1.0f, 0.2f, 0.0f, 1.0f };
    float colorG[] = { 0.0f, 1.0f, 0.2f, 1.0f };
    float colorB[] = { 0.0f, 0.2f, 0.9f, 1.0f };

    sysVel.Update(deltaTime);

    //correct drawing pattern
    //shader->Use();                        // Bind shader
    //shader->AddUniformX(...);             // Set all needed uniforms
    //DrawMeshOrShape();

    std::shared_ptr<Shader> shader = ent.GetComponent<Component2dPolygon>("2d Polygon")->getShader();
    shader->Use();
    shader->AddUniformMat4("view", &view[0][0]);
    shader->AddUniformMat4("projection", &projection[0][0]);
    shader->AddUniform4f("u_Color", colorR);
    shader->AddUniform3f("position", ent.GetComponent<ComponentPosition>("Position")->getPosition());
    ent.GetComponent<Component2dPolygon>("2d Polygon")->draw();

    shader = ent.GetComponent<ComponentCircle>("Circle")->getShader();
    shader->Use();
    shader->AddUniformMat4("view", &view[0][0]);
    shader->AddUniformMat4("projection", &projection[0][0]);
    shader->AddUniform4f("u_Color", colorB);
    shader->AddUniform3f("position", ent.GetComponent<ComponentPosition>("Position")->getPosition());
    ent.GetComponent<ComponentCircle>("Circle")->draw();

    shader = ent.GetComponent<ComponentSphere>("Sphere")->getShader();
    shader->Use();
    shader->AddUniformMat4("view", &view[0][0]);
    shader->AddUniformMat4("projection", &projection[0][0]);
    shader->AddUniform4f("u_Color", colorG);
    shader->AddUniform3f("position", ent.GetComponent<ComponentPosition>("Position")->getPosition());
    ent.GetComponent<ComponentSphere>("Sphere")->draw();


    glfwSwapBuffers(window);
    glfwPollEvents();
}
void GameScene::Shutdown()
{
    ent.GetComponent<Component2dPolygon>("2d Polygon")->Delete();
}
