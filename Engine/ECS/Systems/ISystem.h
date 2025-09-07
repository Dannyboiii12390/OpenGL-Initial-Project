#pragma once
#include <string>
#include <set>
#include <vector>
#include "../Entity.h"

class ISystem
{

	std::string name;

protected:
	std::vector<Entity*> entities;

public:
	virtual void Update(float deltTime) = 0;
	// Optional: Called when an entity is added/removed
	void AddEntity(Entity* entity);
	const bool RemoveEntity(const int ID);
	const std::string& getName();
	const std::vector<Entity*> GetEntities() const { return entities; }

};