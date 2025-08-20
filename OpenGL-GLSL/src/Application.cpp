#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <sstream>
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
static ShaderProgramSource parseShader(const std::string& filePath)
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
            if(line.find("vertex") != std::string::npos)
            {
				//set mode to vertex shader
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
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
	return { ss[0].str(), ss[1].str() };
}
static int CompileShader(const unsigned int type, const std::string& source)
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
        std::cout<<"Failed to compile "<<(type == GL_VERTEX_SHADER ? "vertex": "fragment")<<"shader!"<<std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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
static void STATICDRAWpolygon(float* polygonVertices, unsigned int polygonVertexSize)
{
	unsigned int VBO, VAO; //VAO = Vertex Array Object, VBO = Vertex Buffer Object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, polygonVertexSize, polygonVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit() )
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640,480, "Hello World", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error! \n" << std::endl;
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


	};
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

    //triangle
    float polygonVertices[] = {
        0.0f,  0.5f, 0.0f,  // Top
        -0.5f, -0.5f, 0.0f, // Bottom-left
        0.5f, -0.5f, 0.0f,  // Bottom-right
    };


    STATICDRAWpolygon(polygonVertices, sizeof(polygonVertices));
    
	ShaderProgramSource source = parseShader("res/shaders/Basic.shader");
	/*std::cout << "Vertex Shader: \n" << source.VertexSource << std::endl;
	std::cout << "Fragment Shader: \n" << source.FragmentSource << std::endl;*/
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 9);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
	glDeleteProgram(shader);    
    glfwTerminate();
    return 0;
}