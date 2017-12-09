#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;

out vec4 outFragmentColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Light
{
	vec4 position;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;


void phong(vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular) 
{
	vec3 directionToLight = normalize(vec3(light.position) - position);
	float diffuseIntensity = max(dot(normal, directionToLight), 0.0f);
	diffuseIntensity = clamp(diffuseIntensity, 0.0, 1.0);
	diffuse = (light.diffuse * material.diffuse * diffuseIntensity);

	if(diffuseIntensity < 0.0f)
	{
		vec3 positionToView = normalize(-position.xyz); 
		vec3 reflectLightVector = normalize(-reflect(directionToLight, normal));
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = (light.specular * material.specular * specularIntensity);
		specular = clamp(specular, 0.0, 1.0);
	}
}

void main()
{
	vec3 color = material.ambient;
	vec3 diffuse;
	vec3 specular;
	phong(outFragmentPosition, outFragmentNormal, diffuse, specular);
	color += (diffuse + specular);
//	outFragmentColor = vec4(outFragmentPosition, 1.0);
	outFragmentColor = vec4(color, 1.0);
}
