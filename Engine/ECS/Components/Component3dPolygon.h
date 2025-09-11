#pragma once
#include "IComponent.h"


class Component3dPolygon : public IComponent
{
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	std::shared_ptr<Shader> shader;
    unsigned int indexCount;

public:
	Component3dPolygon(const float* vertices, unsigned int vertexCount, const unsigned int* indices, unsigned int pIndexCount, const std::shared_ptr<Shader> pShader) : 
        IComponent(ComponentType::Polygon3d), indexCount(pIndexCount), shader(pShader)
	{
        GLCALL(glGenVertexArrays(1, &VAO));
        GLCALL(glGenBuffers(1, &VBO));
        GLCALL(glGenBuffers(1, &IBO));

        GLCALL(glBindVertexArray(VAO));

        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, vertexCount* sizeof(float), vertices, GL_STATIC_DRAW));

        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW));

        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
        GLCALL(glEnableVertexAttribArray(0));

        GLCALL(glBindVertexArray(0));
	}
    void draw()
    {
        shader->Use();
        GLCALL(glBindVertexArray(VAO));
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }
    std::shared_ptr<Shader> getShader()
    {
        return shader;
    }
    const std::string& getName() const override;

};

