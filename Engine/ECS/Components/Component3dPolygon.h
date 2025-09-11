#pragma once
#include "IComponent.h"

class Component3dPolygon : public IComponent
{
private:
    unsigned int VAO, VBO, IBO;
    unsigned int indicesCount;
    std::shared_ptr<Shader> shader;


};


