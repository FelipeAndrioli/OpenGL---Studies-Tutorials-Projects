#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture_a;
uniform sampler2D texture_b;

void main() {
    FragColor = mix(texture(texture_a, TexCoord), texture(texture_b, TexCoord), 0.5);
}