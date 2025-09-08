#pragma once
#include <string>
#include "../../General/Shader.h"
#define PI 3.1415926535
#define f_pi static_cast<float>(PI)
/*
component sphere
component 3d polygon
component audio
component geometry - loading objs and textures
component ai - various behaviours
*/


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