#include "Circle.h"
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../General/Shader.h"



Circle::Circle(float* pPosition, Shader* pShader, float pRadius, int pSegments, bool pFill) : position(pPosition), radius(pRadius), segments(pSegments), fill(pFill), shader(pShader)
{
	generateVertices();
	setupBuffers();
	const std::string name = "u_Color";
   
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
void Circle::setColor(const float r, const float g, const float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
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

    float velocity = sin(glfwGetTime()) * 0.5f;
    shader->AddUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    
    
    shader->AddUniform3f("u_Translation", velocity, 0, 0);

    shader->Bind();
    glBindVertexArray(VAO);
    if (!fill)
    {
        glDrawArrays(GL_LINE_LOOP, 0, segments);
    }
    else // use GL_TRIANGLE_FAN for filled
    {
        glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
    }
    glBindVertexArray(0);
}