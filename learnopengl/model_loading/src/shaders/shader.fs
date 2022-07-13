#version 330 core

/*
    Fragment Shader -> Calculate the color of the fragment
*/

struct Material {
    float shininess;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 colors;
uniform sampler2D m_texture;
uniform vec3 lightColor;

uniform float ambient_strength;

in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {

    vec4 result = texture(m_texture, TexCoord);

    result *= ambient_strength;

    FragColor = result;
}
