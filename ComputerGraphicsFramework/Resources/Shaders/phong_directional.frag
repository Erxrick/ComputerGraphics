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
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
struct Fog
{ 
	float distanceMin;
	float distanceMax;
	vec3 color;
};

uniform Material material;
uniform Light light;


void phong(vec3 position, vec3 normal, out vec3 ambientDiffuse, out vec3 specular) 
{
	vec3 ambient = light.ambient * material.ambient;
//	float distance = abs(outFragmentPosition.z);

	vec3 directionToLight;
	if (light.position.w == 0)
	{
		directionToLight = normalize(vec3(light.position));
	}
	else
	{
		directionToLight = normalize(vec3(light.position) - position);
	}


//	vec3 positionToLight = normalize(light.position - position);
	float diffuseIntensity = max(dot(directionToLight, normal), -1.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	ambientDiffuse = ambient + diffuse;

	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-position.xyz); 
		vec3 reflectLightVector = reflect(-directionToLight, normal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}

}

void main()
{

	vec3 ambientDiffuse;
	vec3 specular;
	phong(outFragmentPosition, outFragmentNormal, ambientDiffuse, specular);
	
//	vec4 texColor1 = texture(texture1, outFragmentUV);
 
	// outFragmentColor = (texColor1 * vec4(ambientDiffuse + specular, 1.0f));
		outFragmentColor = vec4(ambientDiffuse + specular, 1.0);
}