#version 330 core

/*
    Vertex Shader -> Calculate the position of the vertex
*/

layout (location = 0) in vec3 aPos;

void main() {

    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
