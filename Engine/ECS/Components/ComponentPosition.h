
#include "IComponent.h"

class ComponentPosition final : public IComponent
{
private:
    float position[3];

public:
    ComponentPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void setPosition(const float x, const float y, const float z);
    void getPosition(float& x, float& y, float& z) const;
    float* getPosition();
    const std::string& getName() const override;

};