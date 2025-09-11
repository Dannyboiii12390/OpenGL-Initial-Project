#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 position;       //Object/world position offset
uniform mat4 view;           //View matrix (camera)
uniform mat4 projection;     //Projection matrix (perspective/ortho)
uniform mat4 model;

void main() 
{
    gl_Position = projection * view * model * vec4(aPos + position, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;
uniform vec4 u_Color;

void main() 
{
    //FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    FragColor = u_Color;
}