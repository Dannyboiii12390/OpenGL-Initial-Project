#pragma once
#include "Macros.h"




class Drawing
{
	public:
	//ideas for future functions
	/*static void drawCube(float size);
	static void drawSphere(float radius, int slices, int stacks);
	static void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks);
	static void drawCone(float baseRadius, float height, int slices, int stacks);
	static void drawTorus(float innerRadius, float outerRadius, int sides, int rings);
	static void drawGrid(float size, int divisions);
	static void drawAxes(float size);*/

	void staticPolygon(float* polygonVertices, unsigned int polygonVertexSize);
};