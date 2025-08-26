#pragma once
#include <string>
#include "Macros.h"

class Shader
{
private: 
    const int CompileShader(const uint type, const std::string& source) const;
    Shader(const std::string VSource, const std::string FSource);
    const Shader parseShader(const std::string& filePath)const;
    const uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;

public:
    std::string VertexSource;
    std::string FragmentSource;
    std::string FilePath;
    uint ID;

	Shader(const std::string filePath);
    const void Bind() const;
    const void Unbind() const;
    const void Delete();
    
};
