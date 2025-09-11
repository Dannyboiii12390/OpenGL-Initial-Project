#pragma once
#include <string>
#include <unordered_map>
#include "../../General/Shader.h"
#define PI 3.1415926535
#define f_pi static_cast<float>(PI)
/*
component audio - next
component 3d polygon
component geometry - loading objs and textures
component ai - various behaviours
*/
enum ComponentType : long long int
{
	None		=	0LL,
	Position	=	1LL << 0,
	Velocity	=	1LL << 1,
	Sphere		=	1LL << 2,
	Circle		=	1LL << 3,
	Polygon2d	=	1LL << 4,
	Polygon3d	=	1LL << 5,
};

inline ComponentType operator|(ComponentType a, ComponentType b)
{
	return static_cast<ComponentType>(
		static_cast<long long>(a) | static_cast<long long>(b)
		);
}
inline ComponentType operator&(ComponentType a, ComponentType b)
{
	return static_cast<ComponentType>(
		static_cast<long long>(a) & static_cast<long long>(b)
		);
}
inline ComponentType& operator|=(ComponentType& a, ComponentType b)
{
	a = a | b;
	return a;
}
inline bool hasFlag(ComponentType mask, ComponentType flag)
{
	return (mask & flag) == flag;
}

/* example usage
int main() {
	ComponentType mask = ComponentType::Position | ComponentType::Circle;

	if (hasFlag(mask, ComponentType::Circle)) {
		std::cout << "Mask includes Circle\n";
	}

	if (hasFlag(mask, ComponentType::Circle | ComponentType::Position)) {
		std::cout << "Mask includes Circle and Position\n";
	}
}
*/

class IComponent
{
	// Lookup tables
	ComponentType componentTypeFromString(const std::string& name)
	{
		static const std::unordered_map<std::string, ComponentType> lookup = {
			{"Position",  ComponentType::Position},
			{"Velocity",  ComponentType::Velocity},
			{"Sphere",    ComponentType::Sphere},
			{"Circle",    ComponentType::Circle},
			{"2d Polygon", ComponentType::Polygon2d}
		};
		auto it = lookup.find(name);
		if (it != lookup.end())
		{
			return it->second;
		}
		throw std::invalid_argument("Unknown ComponentType: " + name);
	}
	std::string componentTypeToString(const ComponentType& type)
	{
		switch (type)
		{
		case ComponentType::Position:  return "Position";
		case ComponentType::Velocity:  return "Velocity";
		case ComponentType::Sphere:    return "Sphere";
		case ComponentType::Circle:    return "Circle";
		case ComponentType::Polygon2d: return "2d Polygon";
		case ComponentType::Polygon3d: return "3d Polygon";
		case ComponentType::None:	   return "None";
		default:                       throw std::invalid_argument("Unknown ComponentType: " + name);;
		}
	}

protected:
	std::string name;
	ComponentType compType;

public:

	IComponent(std::string pName) : name(pName)
	{
		compType = componentTypeFromString(pName);
	}
	IComponent(ComponentType pType) : compType(pType)
	{
		name = componentTypeToString(compType);
	}

	const ComponentType& getType() const
	{
		return compType;
	}
	virtual const std::string& getName() const = 0;
	
};