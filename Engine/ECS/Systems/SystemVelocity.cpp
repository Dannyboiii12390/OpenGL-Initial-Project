#include "SystemVelocity.h"
#include "../Components/ComponentPosition.h"
#include "../Components/ComponentVelocity.h"

void SystemVelocity::Update(float deltaTime)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		bool hasComponents = hasFlag((*it)->getType(), ComponentType::Position | ComponentType::Velocity);
		if (hasComponents)
		{
			
			float* position = (*it)->GetComponent<ComponentPosition>(ComponentType::Position)->getPosition();
			float* velocity = (*it)->GetComponent<ComponentVelocity>(ComponentType::Velocity)->getVelocity();

			position[0] += velocity[0] * deltaTime;
			position[1] += velocity[1] * deltaTime;
			position[2] += velocity[2] * deltaTime;
		}
	}
}
