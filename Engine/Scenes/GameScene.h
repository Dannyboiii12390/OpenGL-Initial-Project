#pragma once
#include "Scene.h"
#include "../General/Shader.h"

class GameScene final : public Scene
{

private:
    std::unique_ptr<Shader> shader;

    unsigned int VAO, VBO;

    float position[3] = { 0.0f, 0.0f, 0.0f };

public:
    void Init() override;
    void Update(const float deltaTime, GLFWwindow* window, const int w, const int h) override;
    void Render() override;
    void Shutdown() override;

    
};