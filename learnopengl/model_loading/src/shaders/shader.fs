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

    float innerCutOff;
    float outerCutOff;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() {
    
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 lightDir = normalize(-light.direction); 

    // check if lighting is inside the spotlight cone 
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ambient
    vec3 ambient = light.ambient * texture(material.m_diffuse_texture, TexCoord).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * texture(material.m_diffuse_texture, TexCoord).rgb);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * texture(material.m_specular_texture, TexCoord).rgb);
  
    // attenuation (point light)
    float distance = length(FragPos - light.position);
    //float distance = sqrt(pow((FragPos.x - light.position.x), 2) + pow((FragPos.y - light.position.y), 2) + pow((FragPos.z - light.position.z), 2));
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    // attenuation update
    //ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // intensity update
    diffuse *= intensity;
    specular *= intensity;

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
}
