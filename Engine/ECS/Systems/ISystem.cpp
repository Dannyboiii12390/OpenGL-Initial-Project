#include "ISystem.h"

void ISystem::AddEntity(Entity* entity)
{
	entities.push_back(entity);
};
const bool ISystem::RemoveEntity(const int ID)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		if ((*it)->getID() == ID)
		{
			entities.erase(it);
			return true; // Entity was found and removed
		}
	}
	return false; // Entity not found
}
const std::string& ISystem::getName()
{
	return name;
}