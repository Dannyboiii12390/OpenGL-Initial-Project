#pragma once
#include "../General/ShaderLoading.h"
#include "../General/Macros.h"

class Polygon final
{
private:
	float position[3] = {}; // x, y, z coordinates
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

	Shader* shader; // Shader program
	
public:
	Polygon(const float* pPosition, const float* pVertices, const uint pVertexCount, const int* pIndices, const uint pIndexCount, Shader* pShader);
	~Polygon();
	void draw() const;
	void setPosition(const float* pPosition);
	void setColor(const float r, const float g, const float b);
	void setShader(Shader* pShader)
	{
		shader = pShader;
	}
};	
