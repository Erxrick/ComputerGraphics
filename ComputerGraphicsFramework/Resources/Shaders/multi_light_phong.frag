#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentUV;

//layout (binding=0) uniform sampler2D texture1;
//layout (binding=1) uniform sampler2D texture2;

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
uniform Light lights[5];


void phong(int lightIndex, vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular) 
{
	vec3 directionToLight = normalize(vec3(lights[lightIndex].position) - position);
	float diffuseIntensity = max(dot(directionToLight, normal), 0.0f);
	diffuse = (lights[lightIndex].diffuse * material.diffuse * diffuseIntensity);

	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-position.xyz); 
		vec3 reflectLightVector = reflect(-directionToLight, normal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = (lights[lightIndex].specular * material.specular * specularIntensity);
	}
}

void main()
{
	vec3 color = material.ambient;
	for (int i = 0; i < 5; i++)
	{
		vec3 diffuse;
		vec3 specular;
		phong(i, outFragmentPosition, outFragmentNormal, diffuse, specular);
		color += (diffuse + specular);
	}
			
    outFragmentColor = vec4(color, 1.0);
}
