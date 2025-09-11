#include "Entity.h"


int Entity::staticIDs = 0;

Entity::Entity()
{
    ID = staticIDs;
    staticIDs++;
}

const int Entity::GetIndex(const std::string& name)
{
    for (unsigned int i = 0; i < components.size(); ++i)
    {
        if (components[i]->getName() == name)
        {
            return i;
        }
    }
    return -1;
}
const int Entity::GetIndex(const ComponentType& type) const
{
    for (unsigned int i = 0; i < components.size(); ++i)
    {
        if (components[i]->getType() == type)
        {
            return i;
        }
    }
    return -1;
}

const ComponentType Entity::getType() const
{
    ComponentType mask = ComponentType::None;
    
    for (const auto& comp : components)
    {
        mask = mask | comp->getType();
    }
    return mask;
}

void Entity::RemoveComponent(const int index)
{
    if (index >= 0 && index < static_cast<int>(components.size()))
    {
        components.erase(components.begin() + index);
    }
}
const int Entity::getID() const
{
    return ID;
}

