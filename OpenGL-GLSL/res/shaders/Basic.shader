#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

// Uniform for transforming the vertex position (e.g. translation or scaling)
uniform vec3 u_Translation;

void main()
{
    // Apply transformation (e.g. translation)
    gl_Position = position + vec4(u_Translation, 0.0);
}



#shader fragment
#version 330 core

out vec4 color;

// Uniform for color
uniform vec4 u_Color;

void main()
{
    color = u_Color;
}