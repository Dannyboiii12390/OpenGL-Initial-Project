#include "ComponentVelocity.h"

ComponentVelocity::ComponentVelocity(const float x, const float y, const float z) : IComponent("Velocity")
{
	setVelocity(x, y, z);
}
void ComponentVelocity::setVelocity(const float& x, const float& y, const float& z)
{
	velocity[0] = x;
	velocity[1] = y;
	velocity[2] = z;
}

const std::string& ComponentVelocity::getName() const
{
	return name;
}
float* ComponentVelocity::getVelocity()
{
	return velocity;
}