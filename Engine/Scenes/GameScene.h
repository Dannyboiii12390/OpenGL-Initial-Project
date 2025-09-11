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
    SystemVelocity sysVel;


public:
    void Init() override;
    void Restart() override;
    void Update(const float deltaTime, GLFWwindow* window, const int w, const int h) override;
    void Shutdown() override;

    
};