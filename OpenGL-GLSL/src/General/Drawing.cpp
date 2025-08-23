#pragma once
#include "Drawing.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void Drawing::staticPolygon(float* polygonVertices, unsigned int polygonVertexSize)
{
    unsigned int VBO, VAO; //VAO = Vertex Array Object, VBO = Vertex Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, polygonVertexSize, polygonVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

/*
    //Square
    float polygonVertices[] = {
        // First triangle
        -0.5f, -0.5f, 0.0f,  // Bottom-left
         0.5f, -0.5f, 0.0f,  // Bottom-right
         0.5f,  0.5f, 0.0f,  // Top-right

         // Second triangle
          0.5f,  0.5f, 0.0f,  // Top-right
         -0.5f,  0.5f, 0.0f,  // Top-left
         -0.5f, -0.5f, 0.0f   // Bottom-left

    // Pentagon
    float polygonVertices[] = {
        //left triangle
        0.0f,  1.0f, 0.0f,  // Top
        -0.5f, -1.0f, 0.0f, // Bottom-left
        -1.0, 0.0f, 0.0f, //top-left

        // Middle Triangle
        //0.0f,  1.0f, 0.0f,  // Top
        //-0.5f, -1.0f, 0.0f, // Bottom-left
        //0.5f, -1.0f, 0.0f,  // Bottom-right

        // Right Triangle
        0.0f,  1.0f, 0.0f,  // Top
        0.5f, -1.0f, 0.0f,  // Bottom-right
        1.0f,  0.0f, 0.0f,  // top right
    };
    */