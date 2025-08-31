#include "Shader.h"


Shader::Shader(const std::string& filePath)
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

    //Log("Vertex Shader: \n" << s.VertexSource);
    //Log("Fragment Shader: \n" << s.FragmentSource);
    ID = Create(ss[0].str(), ss[1].str());
}
Shader::~Shader()
{
    if (ID != 0)
    {
        glDeleteProgram(ID);
    }
}
Shader::Shader()
{

}
const unsigned int Shader::Create(const std::string& vertexShader, const std::string& fragmentShader) const
{
    GLCALL(unsigned int program = glCreateProgram());
    GLCALL(unsigned int vs = Compile(GL_VERTEX_SHADER, vertexShader));
    GLCALL(unsigned int fs = Compile(GL_FRAGMENT_SHADER, fragmentShader));

    GLCALL(glAttachShader(program, vs));
    GLCALL(glAttachShader(program, fs));
    GLCALL(glLinkProgram(program));
    GLCALL(glValidateProgram(program));

    GLCALL(glDeleteShader(vs));
    GLCALL(glDeleteShader(fs));

    return program;
}
const int Shader::Compile(const unsigned int type, const std::string& source) const
{
    GLCALL(unsigned int shader = glCreateShader(type));
    const char* src = source.c_str();
    GLCALL(glShaderSource(shader, 1, &src, NULL));
    GLCALL(glCompileShader(shader));

    int result;
    GLCALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCALL(glGetShaderInfoLog(shader, length, &length, message));
        LOG("Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!");
        LOG(message);
        GLCALL(glDeleteShader(shader));
        return 0;
    }
    return shader;
}

Shader Shader::operator=(const Shader& s)
{
    return Shader(s.FilePath);
}


void Shader::Use() const
{
    GLCALL(glUseProgram(ID));
}
void Shader::Unuse() const
{
    GLCALL(glUseProgram(0));
}
void Shader::Remove()
{
    GLCALL(glUseProgram(ID));
    ID = 0;
}

int Shader::getID() const
{
    return ID;
}

void Shader::AddUniform4f(const std::string& name, const float* values) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform4f(location, values[0], values[1], values[2], values[3]));
}
    void Shader::AddUniform3f(const std::string& name, const float* values) const
    {
        GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
        GLCALL(glUniform3f(location, values[0], values[1], values[2]));
    }
void Shader::AddUniform2f(const std::string& name, const float* values) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform2f(location, values[0], values[1]));
}
void Shader::AddUniform1f(const std::string& name, const float* value) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform1f(location, *value));
}

void Shader::AddUniform4i(const std::string& name, const int* values) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform4i(location, values[0], values[1], values[2], values[3]));
}
void Shader::AddUniform3i(const std::string& name, const int* values) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform3i(location, values[0], values[1], values[2]));
}
void Shader::AddUniform2i(const std::string& name, const int* values) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform2i(location, values[0], values[1]));
}
void Shader::AddUniform1i(const std::string& name, const int* value) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniform1i(location, *value));
}

void Shader::AddUniformMat4(const std::string& name, const glm::mat4& matrix) const
{
    GLCALL(int location = glGetUniformLocation(ID, name.c_str()));
    GLCALL(glUniformMatrix4fv(location, 4, GL_FALSE, glm::value_ptr(matrix)));
}