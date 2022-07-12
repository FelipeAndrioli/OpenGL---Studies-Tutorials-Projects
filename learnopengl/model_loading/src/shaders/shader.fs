#version 330 core

/*
    Fragment Shader -> Calculate the color of the fragment
*/

uniform vec3 colors;
uniform sampler2D m_texture;

in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
   FragColor = texture(m_texture, TexCoord);
}
