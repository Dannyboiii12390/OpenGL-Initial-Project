#include "Circle.h"
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../General/ShaderLoading.h"

Circle::Circle(float* pPosition, Shader* pShader, float pRadius, int pSegments, bool pFill) : position(pPosition), radius(pRadius), segments(pSegments), fill(pFill), shader(pShader)
{
	generateVertices();
	setupBuffers();
}

Circle::~Circle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void Circle::generateVertices()
{
    vertices.reserve(segments*2);
    for (int i = 0; i < segments; ++i)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        vertices.push_back(x);
        vertices.push_back(y);
    }
}
void Circle::setupBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}
void Circle::draw() const
{
    shader->Bind();

    glBindVertexArray(VAO);
    if (!fill)
    {
        glDrawArrays(GL_LINE_LOOP, 0, segments);
    } else // use GL_TRIANGLE_FAN for filled
        {
        glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
	}
    glBindVertexArray(0);
}