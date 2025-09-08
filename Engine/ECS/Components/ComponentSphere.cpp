#include "ComponentSphere.h"

ComponentSphere::ComponentSphere(std::shared_ptr<Shader> pShader, float pRadius, int pSectorCount, int pStackCount) 
    : radius(pRadius), sectorCount(pSectorCount), stackCount(pStackCount),shader(pShader), IComponent("Sphere")
{
    generateSphere();
    //shader = pShader;


    // Generate buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    glEnableVertexAttribArray(0); // location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindVertexArray(0);
}
ComponentSphere::~ComponentSphere()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    glDeleteVertexArrays(1, &VAO);
}
void ComponentSphere::generateSphere()
{
    float x, y, z, xy;
    float sectorStep = 2 * f_pi / sectorCount;
    float stackStep = f_pi / stackCount;
    float sectorAngle, stackAngle;

    vertices.clear();
    indices.clear();

    // Generate vertices
    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = f_pi / 2 - i * stackStep; // from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);    // r * cos(u)
        y = radius * sinf(stackAngle);     // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;   // from 0 to 2pi

            x = xy * cosf(sectorAngle);     // r * cos(u) * cos(v)
            z = xy * sinf(sectorAngle);     // r * cos(u) * sin(v)
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    // Generate indices
    int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}
void ComponentSphere::draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
const std::string& ComponentSphere::getName() const
{
    return name;
}
const std::shared_ptr<Shader> ComponentSphere::getShader() const
{
    return shader;
}