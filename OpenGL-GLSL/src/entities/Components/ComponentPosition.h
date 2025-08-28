#pragma once
#include "IComponent.h"

class ComponentPosition final : public IComponent
{
private:
	float position[3];

public:
	ComponentPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	float* getPosition();
	const float& getX() const;
	const float& getY() const;
	const float& getZ() const;

	void setPosition(const float x, const float y, const float z);
	std::string getName() const override;

	

};