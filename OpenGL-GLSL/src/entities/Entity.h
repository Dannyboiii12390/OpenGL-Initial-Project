#pragma once
#include <string>
#include "Components/IComponent.h"
#include <vector>
#include "../General/Macros.h"
//#include <memory>

class Entity final
{
private:
	std::string name;
	std::vector<std::shared_ptr<IComponent>> components;

public:
	Entity(const std::string& pName, uint componentsToReserve = 4);
    
    void addComponent(std::shared_ptr<IComponent> component);

    void removeComponent(const std::shared_ptr<IComponent>& component);
    void removeComponent(const std::string& componentName);
    void removeComponent(uint index);

    std::shared_ptr<IComponent> getComponent(const std::string& componentName) const;
    std::shared_ptr<IComponent> getComponent(uint index) const;
    
    const std::string& getName() const;
    const uint getComponentCount() const;

    template<typename T>
    std::shared_ptr<T> getComponent(uint compInd)
    {
        std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(getComponent(compInd));
        return ptr;
    }
    





};