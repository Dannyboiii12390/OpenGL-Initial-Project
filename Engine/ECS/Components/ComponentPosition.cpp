
#include "ComponentPosition.h"




ComponentPosition::ComponentPosition(float x, float y, float z) : IComponent(ComponentType::Position)
{
    setPosition(x, y, z);
}
void ComponentPosition::setPosition(const float x, const float y, const float z)
{
    position[0] = x;
    position[1] = y;
    position[2] = z;
}
void ComponentPosition::getPosition(float& x, float& y, float& z) const
{
    x = position[0];
    y = position[1];
    z = position[2];
}
float* ComponentPosition::getPosition()
{
    return position;
}
const std::string& ComponentPosition::getName() const
{
    return name;
}