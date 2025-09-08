#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <vector>
#include <string>
#include "IComponent.h"
#include "../../General/Shader.h"

class ComponentCircle : public IComponent
{
public:
    ComponentCircle(std::shared_ptr<Shader> pShader, float radius = 1.0f, int segments = 100);
    ~ComponentCircle();

    void draw() const;
    const std::shared_ptr<Shader> getShader() const;
    const std::string& getName() const;

private:
    void generateCircleData();

    std::shared_ptr<Shader> shader;

    float m_radius;
    int m_segments;

    unsigned int VAO, VBO, IBO;
    std::vector<glm::vec2> vertices;
    std::vector<unsigned int> indices;
};