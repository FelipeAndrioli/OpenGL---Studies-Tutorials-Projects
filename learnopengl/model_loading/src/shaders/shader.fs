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
uniform vec3 viewPos;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() {

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    
    vec3 ambient = light.ambient * material.ambient;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;

    vec3 result = (ambient + diffuse + specular) * vec3(texture(material.m_texture, TexCoord));

    FragColor = vec4(result, 1.0);
}






