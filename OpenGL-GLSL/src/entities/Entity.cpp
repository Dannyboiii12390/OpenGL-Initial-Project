#include "Entity.h"
#include <string>
#include "../General/Macros.h"

Entity::Entity(const std::string& pName, const unsigned int toReserve) : name(pName)
{
	components.reserve(toReserve);
}

void Entity::addComponent(std::shared_ptr<IComponent> component)
{
	components.emplace_back(std::move(component));
}

void Entity::removeComponent(const std::shared_ptr<IComponent>& component)
{
    components.erase(std::remove_if(components.begin(), components.end(), [&component](const std::shared_ptr<IComponent>& c)
    {
        return c == component;
    }),
    components.end());
}
void Entity::removeComponent(const std::string& componentName)
{
    components.erase(std::remove_if(components.begin(), components.end(), [&componentName](const std::shared_ptr<IComponent>& c)
    {
        return c->getName() == componentName;
    }),
    components.end());
}
void Entity::removeComponent(const unsigned int index)
{
    if (index < components.size())
    {
        components.erase(components.begin() + index);
    }
}

std::shared_ptr<IComponent> Entity::getComponent(const std::string& componentName) const
{
    for (const auto& component : components)
    {
        if (component->getName() == componentName)
        {
            return component;
        }
    }
    return nullptr;
}
std::shared_ptr<IComponent> Entity::getComponent(const unsigned int index) const
{
	return (index < components.size()) ? components[index] : nullptr;
}

const std::string& Entity::getName() const { return name; }
const unsigned int Entity::getComponentCount() const { return static_cast<unsigned int>(components.size()); }


