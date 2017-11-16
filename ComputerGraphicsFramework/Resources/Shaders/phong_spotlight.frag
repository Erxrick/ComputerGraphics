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
uniform Light light;


void phong(vec3 position, vec3 normal, out vec3 ambientDiffuse, out vec3 specular) 
{
	vec3 ambient =  material.ambient;

	vec3 directionToLight = normalize(vec3(light.position) - position);
	vec3 spotDirection = normalize(light.direction);

	float angle = acos(dot(-directionToLight, spotDirection));

	if(angle > light.cutoff)
	{
		ambientDiffuse = material.ambient;
		specular = vec3(0.0f, 0.0f, 0.0f);
	} 
	else
	{
		float diffuseIntensity = max(dot(directionToLight, normal), 0.0f);
		float spotFactor = pow(dot(-directionToLight, spotDirection), light.exponent);
		vec3 diffuse = (light.diffuse * material.diffuse * diffuseIntensity) * spotFactor;
	
		ambientDiffuse = ambient + diffuse;


		if(diffuseIntensity > 0.0f)
		{
			vec3 positionToView = normalize(-position.xyz); 
			vec3 reflectLightVector = reflect(-directionToLight, normal);
			float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
			specularIntensity = pow(specularIntensity, material.shininess);
			specular = (light.specular * material.specular * specularIntensity) * spotFactor;
		}
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