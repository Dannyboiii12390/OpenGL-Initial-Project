#pragma once
#include "Scene.h"
#include "../General/Shader.h"
#include "../ECS/Entity.h"
#include "../ECS/Components/ComponentPosition.h"
#include "../ECS/Components/ComponentVelocity.h"

class GameScene final : public Scene
{

private:
    std::unique_ptr<Shader> shader;
    
    Entity ent;

    unsigned int VAO, VBO;

    //float position[3] = { 0.0f, 0.0f, 0.0f };

public:
    void Init() override;
    void Restart() override;
    void Update(const float deltaTime, GLFWwindow* window, const int w, const int h) override;
    void Shutdown() override;

    
};