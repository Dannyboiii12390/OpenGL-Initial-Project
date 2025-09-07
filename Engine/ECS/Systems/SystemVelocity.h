#pragma once
#include "ISystem.h"

class SystemVelocity : public ISystem
{
public:
	// Inherited via ISystem
	void Update(float deltTime) override;
};