#version 330 core

/*
    Fragment Shader -> Calculate the color of the fragment
*/

struct Material {
    float shininess;
    sampler2D m_diffuse_texture;
    sampler2D m_specular_texture;
};

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
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
    //vec3 lightDir = normalize(-light.direction); 
    vec3 reflectDir = reflect(-lightDir, norm);

    // ambient
    vec3 ambient = light.ambient * texture(material.m_diffuse_texture, TexCoord).rgb;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * texture(material.m_diffuse_texture, TexCoord).rgb);

    // specular
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.m_specular_texture, TexCoord).rgb);
  
    // attenuation 
    float distance = length(FragPos - light.position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (ambient + diffuse + specular);

    FragColor = vec4(result, 1.0);

}
