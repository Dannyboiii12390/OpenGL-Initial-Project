#include "ComponentPosition.h"

ComponentPosition::ComponentPosition(float x, float y, float z) : IComponent("Component Position")
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}
float* ComponentPosition::getPosition() {
	return position;
}
const float& ComponentPosition::getX() const {
	return position[0];
}
const float& ComponentPosition::getY() const
{
	return position[1];
}
const float& ComponentPosition::getZ() const
{
	return position[2];
}

void ComponentPosition::setPosition(float x, float y, float z) {
	position[0] = x;
	position[1] = y;
	position[2] = z;
}
std::string ComponentPosition::getName()const
{
	return name;
}
