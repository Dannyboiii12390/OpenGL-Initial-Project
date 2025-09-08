#include "ComponentCircle.h"
#include <cmath>
#include "ComponentSphere.h"


ComponentCircle::ComponentCircle(std::shared_ptr<Shader> pShader, float pRadius, int pSegments) : radius(pRadius), segments(pSegments), shader(pShader), IComponent("Circle")
{
    generateCircleData();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glBindVertexArray(0);
}
ComponentCircle::~ComponentCircle()
{
    glDeleteBuffers(1, &IBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
void ComponentCircle::generateCircleData()
{
    vertices.clear();
    indices.clear();

    vertices.push_back(glm::vec2(0.0f, 0.0f)); // center vertex

    float angleStep = 2.0f * f_pi / segments;

    // Create vertices around the circle
    for (int i = 0; i <= segments; ++i)
    {
        float angle = i * angleStep;
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        vertices.push_back(glm::vec2(x, y));
    }

    // Create indices for triangles
    for (int i = 1; i <= segments; ++i)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
}
void ComponentCircle::draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
const std::shared_ptr<Shader> ComponentCircle::getShader() const
{
    return shader;
}
const std::string& ComponentCircle::getName() const
{
    return name;
}
