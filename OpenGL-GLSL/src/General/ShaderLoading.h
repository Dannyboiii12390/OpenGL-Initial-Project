#pragma once
#include <string>
#include "Macros.h"

class Shader final
{
private: 
    const int CompileShader(const unsigned int type, const std::string& source) const;
    Shader(const std::string VSource, const std::string FSource);
    const Shader parseShader(const std::string& filePath)const;
    const unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

public:
    std::string VertexSource;
    std::string FragmentSource;
    std::string FilePath;
    unsigned int ID;

	Shader(const std::string filePath);
    const void Bind() const;
    const void Unbind() const;
    const void Delete();
    
    const void AddUniform4f(const std::string& name, float a, float b, float c, float d) const;
    const void AddUniform3f(const std::string& name, float a, float b, float c) const;
};
