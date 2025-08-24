#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>



#ifdef ENG_DEBUG
#define LOG(x) std::cout << x << std::endl
#define ASSERT(x) if (!x) __debugbreak()

#define GLCALL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#else
#define LOG(x)
#define ASSERT(x) x
#define GLCALL(x) x
#endif


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
static bool GLLogCall(const char* function, const char* file, const int line)
{
    while (GLenum error = glGetError())
    {
        LOG("[OpenGL Error: " << error << "]\n [Function: " << function << "]\n [File: " << file << "]\n [Line: " << line << "]");
        return false;
    }
    return true;
}