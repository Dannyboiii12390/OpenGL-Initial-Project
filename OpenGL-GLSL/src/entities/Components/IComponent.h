#pragma once
#include <string>

class IComponent
{
protected:
	std::string name;

public:
	IComponent(const std::string& pName) : name(pName) {}
	virtual std::string getName() const = 0;
};