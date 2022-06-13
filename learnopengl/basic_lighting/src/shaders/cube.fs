#version 330 core

//uniform vec3 objectColor;
//uniform vec3 lightColor;

//in vec3 Normal;
//in vec3 FragPos;
//in vec3 LightPos;
in vec3 ResultingColor;

out vec4 FragColor;

void main() {

	/* -> Phong shading model
	// ambient 	
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	
	// specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); 
	vec3 specular = spec * specularStrength * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0); 
	*/

	FragColor = vec4(ResultingColor, 1.0);	
}
