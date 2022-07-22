#version 330 core

/*
    Fragment Shader -> Calculate the color of the fragment
*/

struct Material {
    float shininess;
    sampler2D m_diffuse_texture;
    sampler2D m_specular_texture;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform vec3 viewPos;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shininess);

    // combining results
    vec3 ambient = light.ambient * vec3(texture(material.m_diffuse_texture, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.m_diffuse_texture, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.m_specular_texture, TexCoord));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shininess);

    // attenuation
    //float distance = length(fragPos - light.position);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // combine results 
    vec3 ambient = light.ambient * vec3(texture(material.m_diffuse_texture, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.m_diffuse_texture, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.m_specular_texture, TexCoord));

    ambient *= attenuation; 
    diffuse *= attenuation; 
    specular *= attenuation; 

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

    // calculating size of the spot and smooth edges
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0., 1.);
    
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.), material.shininess);

    // combining results
    vec3 ambient = light.ambient * vec3(texture(material.m_diffuse_texture, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.m_diffuse_texture, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.m_specular_texture, TexCoord));

    diffuse *= intensity;
    specular *= intensity;
   
    return (ambient + diffuse + specular);
}

void main() {
    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    // phase 2: Point light
    result += CalcPointLight(pointLight, norm, FragPos, viewDir);

    // phase 3: SpotLight
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}
