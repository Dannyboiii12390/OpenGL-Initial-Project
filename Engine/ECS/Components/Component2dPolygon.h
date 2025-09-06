#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "IComponent.h"
#include "../../General/Shader.h"

class Component2dPolygon : public IComponent
{
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int IBO;
    std::shared_ptr<Shader> shader;


public:

    Component2dPolygon(const float* vertices, const unsigned int verticesCount, const unsigned int* indices, const unsigned int indicesCount, const std::shared_ptr<Shader> pShader);
    void draw();
    void Delete();
    const std::string& getName() const override;
    const std::shared_ptr<Shader> getShader() const;

};