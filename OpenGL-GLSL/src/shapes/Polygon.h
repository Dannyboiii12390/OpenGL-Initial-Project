#pragma once
#include "../General/Shader.h"
#include "../General/Macros.h"

class Polygon final
{
private:
	float position[3] = {}; // x, y, z coordinates
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

	Shader* shader; // Shader program
	
public:
	//Polygon() = delete;
	//ComponentPolygon(const float* pPosition, const float* pVertices, const uint pVertexCount, const int* pIndices, const uint pIndexCount, Shader* pShader);
	//ComponentPolygon(const float* pPosition, const float* pVertices, const uint pVertexCount, const int* pIndices, const uint pIndexCount, Shader* pShader);
	Polygon(const float* pPosition, const float* pVertices, const unsigned int pVertexCount, const int* pIndices, const unsigned int pIndexCount, Shader* pShader);
	~Polygon();
	void draw() const;
	void setPosition(const float* pPosition);
	void setColor(const float r, const float g, const float b);
	void setShader(Shader* pShader)
	{
		shader = pShader;
	}
};	
