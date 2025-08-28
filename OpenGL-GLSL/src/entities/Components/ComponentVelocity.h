#pragma once
#include "IComponent.h"

class ComponentVelocity : public IComponent
{
private:
	float vel[3] = {};
	float deltaVel[3] = {0.0f, 0.0f, 0.0f};
	

public:
	ComponentVelocity(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	std::string getName() const override;
	void setVelocity(float& x, float& y, float& z);
	float* getVelocity(float delta);
};