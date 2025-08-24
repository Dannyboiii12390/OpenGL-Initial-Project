#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>



#ifdef ENG_DEBUG
#define Log(x) std::cout << x << std::endl
#define ASSERT(x) if (!x) __debugbreak()

#define GLCALL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#else
#define Log(x)
#define ASSERT(x)
#define GLCALL(x)
#endif


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}
static bool GLLogCall(const char* function, const char* file, const int line)
{
    while (GLenum error = glGetError())
    {
        Log("[OpenGL Error: " << error << "]\n [Function: " << function << "]\n [File: " << file << "]\n [Line: " << line << "]");
        return false;
    }
    return true;
}