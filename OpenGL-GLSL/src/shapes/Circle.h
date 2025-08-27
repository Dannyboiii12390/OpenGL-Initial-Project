#pragma once
#include "../General/Macros.h"
#include <vector>
#include "../General/ShaderLoading.h"


class Circle final
{
	private: 
		float* position;
		float radius;
		int segments;
		bool fill;
		uint VAO, VBO;
		std::vector<float> vertices;
		Shader* shader;
		float color[3] = {1.0f, 1.0f, 1.0f};

		void generateVertices();
		void setupBuffers();


	public:
		Circle(float* pPosition, Shader* pShader, float pRadius = 1.0f, int pSegments = 100, bool pFill = true);
		~Circle();
		void draw() const;
		void setColor(const float r, const float g, const float b);
		
};