#include "ComponentPolygon.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include "../../General/Macros.h"

ComponentPolygon::ComponentPolygon(const float* pPosition, const float* pVertices, const uint pVertexCount, const int* pIndices, const uint pIndexCount, Shader* pShader) :
	IComponent("Component Polygon"), vertexCount(pVertexCount), indexCount(pIndexCount)
{
	std::memcpy(position, pPosition, sizeof(float) * 3);
	vertexSize = vertexCount * sizeof(float);
	vertices = new float[vertexCount];
	std::memcpy(vertices, pVertices, vertexSize);
	indexSize = indexCount * sizeof(uint);
	indices = new uint[indexCount];
	std::memcpy(indices, pIndices, indexSize);
	shader = pShader;
	GLCALL(glGenVertexArrays(1, &VAO));
	GLCALL(glGenBuffers(1, &VBO));
	GLCALL(glGenBuffers(1, &IBO));
	
}
ComponentPolygon::~ComponentPolygon()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void ComponentPolygon::draw() const
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
void ComponentPolygon::setPosition(const float x, const float y, const float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}
void ComponentPolygon::setColor(const float r, const float g, const float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
