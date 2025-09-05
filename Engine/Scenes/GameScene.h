#pragma once
#include "Scene.h"
#include "../General/Shader.h"
#include "../ECS/Entity.h"
#include "../ECS/Components/ComponentPosition.h"
#include "../ECS/Components/ComponentVelocity.h"

class GameScene final : public Scene
{

private:
    std::shared_ptr<Shader> shader;
    Entity ent;

public:
    void Init() override;
    void Restart() override;
    void Update(const float deltaTime, GLFWwindow* window, const int w, const int h) override;
    void Shutdown() override;

    
};