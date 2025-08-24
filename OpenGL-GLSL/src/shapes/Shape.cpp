
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shape.h"
#include <cstring>
#include "../General/Macros.h"

Shape::Shape(const float* pPosition, const float* pVertices, const unsigned int pVertexCount, const int* pIndices, const unsigned int pIndexCount, Shader* pShader) : 
    vertexCount(pVertexCount), indexCount(pIndexCount)
{
    std::memcpy(position, pPosition, sizeof(float) * 3);

    vertexSize = vertexCount * sizeof(float);
    vertices = new float[vertexCount];
    std::memcpy(vertices, pVertices, vertexSize);

    indexSize = indexCount * sizeof(unsigned int);
    indices = new unsigned int[indexCount];
    std::memcpy(indices, pIndices, indexSize);

	shader = pShader;

    GLCALL(glGenVertexArrays(1, &VAO));
    GLCALL(glGenBuffers(1, &VBO));
    GLCALL(glGenBuffers(1, &IBO));
    
}

void Shape::draw() const
{
	shader->Bind();

    GLCALL(glBindVertexArray(VAO));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW));
    GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    GLCALL(glEnableVertexAttribArray(0));

    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW));
    GLCALL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
}
void Shape::setPosition(const float* pPosition)
{
    std::memcpy(position, pPosition, 3* sizeof(float));
}