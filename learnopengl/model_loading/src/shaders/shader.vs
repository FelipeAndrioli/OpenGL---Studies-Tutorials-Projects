#version 330 core

/*
    Vertex Shader -> Calculate the position of the vertex
*/

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 Normal;
out vec2 TexCoord;

void main() {

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = aNormal;
    TexCoord = aTexCoord;
}
