#pragma once
#include <vector> 
#include "Components/IComponent.h"
#include <string>
#include <memory>

class Entity
{
	std::vector<std::shared_ptr<IComponent>> components;
    int ID;
    static int staticIDs;
public:
    
    template<typename T>
    std::shared_ptr<T> GetComponent(int index)
    {
        if (index < 0 || index >= components.size())
            return nullptr;
        return std::dynamic_pointer_cast<T>(components[index]);
    }
    
    template<typename T>
    std::shared_ptr<T> GetComponent(const std::string& name)
    {
        for (const auto& component : components)
        {
            if (component->getName() == name)
            {
                return std::dynamic_pointer_cast<T>(component);
            }
        }
        return nullptr;
    }
    
    template<typename T>
    bool HasComponent(const std::string& name)
    {
        return GetComponent<T>(name) != nullptr;
    }
    
    template<typename T, typename... Args>
    void AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<IComponent, T>::value, "T must derive from IComponent");
        std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
        components.push_back(component);
    }
    
    
    void RemoveComponent(const int index);
    const int GetIndex(const std::string& name);
    Entity();
    const int getID() const;
};