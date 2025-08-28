#pragma once
#include "IComponent.h"
#include "../../shapes/Polygon.h"


class ComponentPolygon : public IComponent
{
private:
	float* position; // x, y, z coordinates
	float color[3] = { 1.0f, 1.0f, 1.0f };

	uint VAO; // Vertex Array Object
	uint VBO; // Vertex Buffer Object
	uint IBO; // Index Buffer Object


	float* vertices; // Vertex data
	uint vertexCount; // Number of vertices
	uint vertexSize; // Size of all vertices in bytes
	uint* indices; // Index data
	uint indexCount; // Number of indices
	uint indexSize; // Size of all vertices in bytes

	float* newVertices = new float[vertexCount];

	Shader* shader; // Shader program
public:
	ComponentPolygon(float* pPosition, float* pVertices, uint pVertexCount, int* pIndices, uint pIndexCount, Shader* pShader);
	~ComponentPolygon();
	std::string getName() const override { return name; }
	

	void draw() const;
	void setPosition(const float x, const float y, const float z);
	void setColor(const float r, const float g, const float b);
	void setShader(Shader* pShader);
	

};	