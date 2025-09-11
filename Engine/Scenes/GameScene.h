#pragma once
#include "Scene.h"
#include "../General/Shader.h"
#include "../ECS/Entity.h"
#include "../ECS/Components/ComponentPosition.h"
#include "../ECS/Components/ComponentVelocity.h"
#include "../ECS/Systems/SystemVelocity.h"


class GameScene final : public Scene
{

private:

    Entity ent;
    Entity ent2;
    SystemVelocity sysVel;

    unsigned int VBO, VAO, EBO;


public:
    void Init() override;
    void Restart() override;
    void Update(const float deltaTime, GLFWwindow* window, const int w, const int h) override;
    void Shutdown() override;

    
};