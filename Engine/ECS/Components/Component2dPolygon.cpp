#include "Component2dPolygon.h"


Component2dPolygon::Component2dPolygon(const float* vertices, const unsigned int verticesCount, const unsigned int* indices, const unsigned int indicesCount, const std::shared_ptr<Shader> pShader) : IComponent("2d Polygon")
{
    shader = pShader;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);
    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices, GL_DYNAMIC_DRAW);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(int), indices, GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}
void Component2dPolygon::draw()
{
    shader->Use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Component2dPolygon::Delete()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
const std::string& Component2dPolygon::getName() const
{
    return name;
}
const std::shared_ptr<Shader> Component2dPolygon::getShader() const
{
    return shader;
}