#include "Entity.h"

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
void Entity::RemoveComponent(const int index)
{
    if (index >= 0 && index < static_cast<int>(components.size()))
    {
        components.erase(components.begin() + index);
    }
}

