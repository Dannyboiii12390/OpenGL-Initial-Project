#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "Macros.h"


class Shader final
{
private:

    const std::string VertexSource;
    const std::string FragmentSource;
    const std::string FilePath;
    unsigned int ID;

    const int Compile(const unsigned int type, const std::string& source) const;
    const unsigned int Create(const std::string& vertexShader, const std::string& fragmentShader) const;
    

public:

    Shader(const std::string& filePath);
    Shader();
    ~Shader();
    void Use() const;
    void Unuse() const;
    void Remove();

    int getID() const;

    Shader operator=(const Shader& other) = delete;


    void AddUniform4f(const std::string& name, const float* values) const;
    void AddUniform3f(const std::string& name, const float* values) const;
    void AddUniform2f(const std::string& name, const float* values) const;
    void AddUniform1f(const std::string& name, const float* value) const;

    void AddUniform4i(const std::string& name, const int* values) const;
    void AddUniform3i(const std::string& name, const int* values) const;
    void AddUniform2i(const std::string& name, const int* values) const;
    void AddUniform1i(const std::string& name, const int* value) const;

    void AddUniformMat4(const std::string& name, const float* matrix) const;
};
