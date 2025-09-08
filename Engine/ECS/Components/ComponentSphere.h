#pragma once
#include "IComponent.h"
#include <vector>
#include <string>
#include <GL/glew.h>
#include <glm.hpp>

class ComponentSphere : public IComponent
{
public:
    ComponentSphere(std::shared_ptr<Shader> pShader, float radius = 1.0f, int sectorCount = 36, int stackCount = 18);
    ~ComponentSphere();

    void draw() const;
    const std::string& getName() const override;
    const std::shared_ptr<Shader> getShader() const;

private:
    void generateSphere();

    float radius;
    int sectorCount;
    int stackCount;
    
    std::shared_ptr<Shader> shader;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, IBO;


};
