#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentUV;

layout (binding=0) uniform sampler2D diffuseMap;
layout (binding=1) uniform sampler2D normalMap;


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
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
	float exponent;
	float cutoff;
};

uniform Material material;
uniform Light light;


void phong(vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular) 
{
	vec3 directionToLight = normalize(vec3(light.position) - position);
	float diffuseIntensity = max(dot(directionToLight, normal), 0.0f);
	diffuse = (light.diffuse * material.diffuse * diffuseIntensity);

	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-position.xyz); 
		vec3 reflectLightVector = reflect(-directionToLight, normal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = (light.specular * material.specular * specularIntensity);
	}
}

void main()
{
	vec3 color = material.ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 normal = texture(normalMap, outFragmentUV).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	phong(outFragmentPosition, normal, diffuse, specular);
	chrom

	vec4 textureColor = texture(diffuseMap, outFragmentUV);
	outFragmentColor = textureColor * vec4(diffuse, 1.0) + vec4(specular, 1.0);




}



