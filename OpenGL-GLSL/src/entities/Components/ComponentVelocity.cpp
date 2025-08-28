
#include "ComponentVelocity.h"

ComponentVelocity::ComponentVelocity(float x, float y, float z) : IComponent("ComponentVelocity")
{
	vel[0] = x;
	vel[1] = y;
	vel[2] = z;
}
std::string ComponentVelocity::getName() const { return name; }
void ComponentVelocity::setVelocity(float& x, float& y, float& z)
{
	vel[0] = x;
	vel[1] = y;
	vel[2] = z;
}
float* ComponentVelocity::getVelocity(float delta) 
{ 
	deltaVel[0] = vel[0]* delta;
	deltaVel[1] = vel[1] * delta;
	deltaVel[2] = vel[2] * delta;

	return deltaVel; 
}