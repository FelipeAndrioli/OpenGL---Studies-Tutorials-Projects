#version 330 core

/*
    Fragment Shader -> Calculate the color of the fragment
*/

struct Material {
    float shininess;
    sampler2D m_texture;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() {

    vec3 norm = normalize(Normal);

    vec3 ambient = material.ambient * light.ambient;
    
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 result = (ambient + diffuse) * vec3(texture(material.m_texture, TexCoord));
    FragColor = vec4(result, 1.0);
}
