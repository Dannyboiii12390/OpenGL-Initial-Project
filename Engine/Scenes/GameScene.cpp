
#include "GameScene.h"
#include "glm.hpp"
#include "../ECS/Components/Component2dPolygon.h"
#include "../ECS/Components/ComponentCircle.h"
#include "../ECS/Components/ComponentSphere.h"
#include "../ECS/Components/Component3dPolygon.h"

template <typename T>
void drawShape(std::shared_ptr<T> shape, const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model,const float* color)
{
    std::shared_ptr<Shader> shader = shape->getShader();
    shader->Use();
    shader->AddUniformMat4("view", &view[0][0]);
    shader->AddUniformMat4("projection", &projection[0][0]);
    shader->AddUniform4f("u_Color", color);
    shader->AddUniformMat4("model", &model[0][0]);
    shape->draw();

    //correct drawing pattern
    //shader->Use();                        // Bind shader
    //shader->AddUniformX(...);             // Set all needed uniforms
    //DrawMeshOrShape();                    // Draw
}

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
    float vertices3d[] = {
    -0.5f, -0.5f, -0.5f, // 0
     0.5f, -0.5f, -0.5f, // 1
     0.5f,  0.5f, -0.5f, // 2
    -0.5f,  0.5f, -0.5f, // 3
    -0.5f, -0.5f,  0.5f, // 4
     0.5f, -0.5f,  0.5f, // 5
     0.5f,  0.5f,  0.5f, // 6
    -0.5f,  0.5f,  0.5f  // 7
    };
    unsigned int indices3d[] = {
        // Back face
        0, 1, 2,
        2, 3, 0,
        // Front face
        4, 5, 6,
        6, 7, 4,
        // Left face
        0, 3, 7,
        7, 4, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Top face
        3, 2, 6,
        6, 7, 3,
        // Bottom face
        0, 1, 5,
        5, 4, 0
    };

    ent.AddComponent<ComponentPosition>(0.0f, 0.0f, 0.0f);
    ent.AddComponent<ComponentVelocity>(0.5f, 0.0f, 0.0f);
    ent.AddComponent<Component2dPolygon>(vertices, 12, indices, 6, std::make_shared<Shader>("Shaders/Basic.Shader"));
    ent.AddComponent<ComponentCircle>(std::make_shared<Shader>("Shaders/Basic.Shader"));
    ent.AddComponent<ComponentSphere>(std::make_shared<Shader>("Shaders/Basic.Shader"), 0.5f);
    
    
    ent2.AddComponent<ComponentPosition>(1.0f, 0.0f, 0.0f);
    ent2.AddComponent<ComponentVelocity>(-0.5f, 0.0f, 0.0f);
    ent2.AddComponent<Component3dPolygon>(vertices3d, 24, indices3d, 36, std::make_shared<Shader>("Shaders/Basic.Shader"));

    sysVel.AddEntity(&ent);
    sysVel.AddEntity(&ent2);

}
void GameScene::Restart()
{
    //todo
}
void GameScene::Update(const float deltaTime, GLFWwindow* window, const int w, const int h)
{
    glEnable(GL_DEPTH_TEST);    
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float* p = ent.GetComponent<ComponentPosition>(ComponentType::Position)->getPosition();
    glm::vec3 position(p[0], p[1], p[2]);
    glm::mat4 ent1model = glm::translate(glm::mat4(1.0f), position);

    const float* p2 = ent2.GetComponent<ComponentPosition>(ComponentType::Position)->getPosition();
    glm::vec3 position2(p2[0], p2[1], p2[2]);
    glm::mat4 ent2model = glm::translate(glm::mat4(1.0f), position2);

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)w / h, 0.1f, 100.0f);

    float colorR[] = { 1.0f, 0.2f, 0.0f, 1.0f };
    float colorG[] = { 0.0f, 1.0f, 0.2f, 1.0f };
    float colorB[] = { 0.0f, 0.2f, 0.9f, 1.0f };
    float colorY[] = { 1.0f, 1.0f, 0.0f, 1.0f };

    sysVel.Update(deltaTime);

    const float pos[]{ 0.0f, 0.0f, 0.0f };
    drawShape(ent.GetComponent<Component2dPolygon>(ComponentType::Polygon2d), view, projection, ent1model, colorR);
    drawShape(ent.GetComponent<ComponentCircle>(ComponentType::Circle), view, projection, ent1model, colorG);
    drawShape(ent.GetComponent<ComponentSphere>(ComponentType::Sphere), view, projection, ent1model, colorB);
    drawShape(ent2.GetComponent<Component3dPolygon>(ComponentType::Polygon3d), view, projection, ent2model, colorY);

    glfwSwapBuffers(window);
    glfwPollEvents();
}
void GameScene::Shutdown()
{
    ent.GetComponent<Component2dPolygon>(ComponentType::Polygon2d)->Delete();
}
