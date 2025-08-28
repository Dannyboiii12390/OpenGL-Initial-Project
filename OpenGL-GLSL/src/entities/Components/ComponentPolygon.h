#pragma once
#include "IComponent.h"
#include "../../shapes/Polygon.h"


class ComponentPolygon : public IComponent
{
private:
	float* position; // x, y, z coordinates
	float color[3] = { 1.0f, 1.0f, 1.0f };

	unsigned int VAO; // Vertex Array Object
	unsigned int VBO; // Vertex Buffer Object
	unsigned int IBO; // Index Buffer Object


	float* vertices; // Vertex data
	unsigned int vertexCount; // Number of vertices
	unsigned int vertexSize; // Size of all vertices in bytes
	unsigned int* indices; // Index data
	unsigned int indexCount; // Number of indices
	unsigned int indexSize; // Size of all vertices in bytes

	float* newVertices = new float[vertexCount];

	Shader* shader; // Shader program
public:
	ComponentPolygon(float* pPosition, float* pVertices, unsigned int pVertexCount, int* pIndices, unsigned int pIndexCount, Shader* pShader);
	~ComponentPolygon();
	std::string getName() const override { return name; }
	

	void draw() const;
	void setPosition(const float x, const float y, const float z);
	void setColor(const float r, const float g, const float b);
	void setShader(Shader* pShader);
	

};	