#pragma once
#include <string>
#include "IComponent.h"

class ComponentVelocity final : public IComponent
{
private:
    float velocity[3];

public:
    ComponentVelocity(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f);
    const std::string& getName() const override;
    void setVelocity(const float& x, const float& y, const float& z);
    float* getVelocity();
};