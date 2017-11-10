#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentUV;

layout (binding=0) uniform sampler2D texture1;
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
	vec3 position;
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
uniform Fog fog;

void main()
{
	vec3 ambient = light.ambient * material.ambient;
	float distance = abs(outFragmentPosition.z);
	float fogIntensity = clamp((distance - fog.distanceMin) / (fog.distanceMax - fog.distanceMin), 0.0, 1.0);

	vec3 positionToLight = normalize(light.position - outFragmentPosition);
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), -1.0f);
	vec3 diffuse = light.diffuse * material.diffuse * diffuseIntensity;

	vec3 specular = vec3(0.0f);
	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz); 
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, material.shininess);
		specular = light.specular * material.specular * specularIntensity;
	}

	vec4 texColor1 = texture(texture1, outFragmentUV);
//	vec4 texColor2 = texture(texture2, outFragmentUV);
//	vec4 texColor = mix(texColor1, texColor2, 0.5);


    vec4 phong = (texColor1 * vec4((ambient + diffuse), 1.0f)) + vec4(specular, 1.0f);

	vec4 color = mix(phong, vec4(fog.color, 1.0), fogIntensity);
	outFragmentColor = color;


	//outFragmentColor = texColor1;
	//outFragmentColor = vec4(1.0f, .0f, .0f, 1.0f);
}