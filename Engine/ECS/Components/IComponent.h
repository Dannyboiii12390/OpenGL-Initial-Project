#pragma once
#include <string>

class IComponent
{
protected:
	std::string name;

public:

	IComponent(std::string pName) : name(pName)
	{
	}
	virtual const std::string& getName() const = 0;
	
	
	
};