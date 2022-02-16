#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D my_texture_one;
uniform sampler2D my_texture_two;

void main() {
    FragColor = mix(texture(my_texture_one, TexCoord), texture(my_texture_two, TexCoord), 0.2);
}

