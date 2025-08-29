#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string> 
#include <fstream>
#include <sstream>
#include <iostream>
#include "ShaderLoading.h"

Shader::Shader(const std::string filePath)
{
	Shader s = parseShader(filePath);
    VertexSource = s.VertexSource;
    FragmentSource = s.FragmentSource;
    //Log("Vertex Shader: \n" << s.VertexSource);
    //Log("Fragment Shader: \n" << s.FragmentSource);
	ID = CreateShader(VertexSource, FragmentSource);
}
Shader::Shader(const std::string VSource, const std::string FSource)
{
	VertexSource = VSource;
    FragmentSource = FSource;
    ID = 0;
}

const Shader Shader::parseShader(const std::string& filePath) const
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };


    std::string line;
    std::stringstream ss[2]; // 0 for vertex, 1 for fragment
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                //set mode to vertex shader
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                //mode to fragment shader
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != ShaderType::NONE)
            {
                ss[(int)type] << line << "\n"; // append line to the correct shader type
            }
        }
    }
    return Shader(ss[0].str(), ss[1].str());
}
const int Shader::CompileShader(const unsigned int type, const std::string& source) const
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    // todo: Error handling
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(shader, length, &length, message);
        LOG("Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!");
        LOG(message);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
const unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
const void Shader::Bind() const
{
    glUseProgram(ID);
}
const void Shader::Unbind() const
{
    glUseProgram(0);
}
const void Shader::Delete()
{
    glDeleteProgram(ID);
	// Note: After deleting the program, the ID is no longer valid. Consider setting ID to 0 if needed.
    ID = 0;
}
const void Shader::AddUniform4f(const std::string& name, float a, float b, float c, float d) const
{
    Bind();
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform4f(location, a, b, c, d);
    Unbind();

}
const void Shader::AddUniform3f(const std::string& name, float a, float b, float c) const
{
    Bind();
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform3f(location, a, b, c);
    Unbind();
}