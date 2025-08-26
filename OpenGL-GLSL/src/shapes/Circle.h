#pragma once
#include "../General/Macros.h"
#include <vector>
#include "../General/ShaderLoading.h"


class Circle
{
	private: 
		float* position;
		float radius;
		int segments;
		bool fill;
		uint VAO, VBO;
		std::vector<float> vertices;
		Shader* shader;

		void generateVertices();
		void setupBuffers();


	public:
		Circle(float* pPosition, Shader* pShader, float pRadius = 1.0f, int pSegments = 100, bool pFill = true);
		~Circle();
		void draw() const;
		
};