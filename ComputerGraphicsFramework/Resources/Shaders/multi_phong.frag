#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentUV;

uniform vec3 lightPosition;
uniform vec3 lightColor;

layout (binding=0) uniform sampler2D texture1;
layout (binding=1) uniform sampler2D texture2;

out vec4 outFragmentColor;

struct MateriaL
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

uniform Material material;

void main()
{
	vec3 ambient = material.ambient;

	vec3 positionToLight = normalize(lightPosition - outFragmentPosition);
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), -1.0f);
	vec3 diffuse = lightColor * material.diffuse * diffuseIntensity;

	vec3 specular = vec3(0.0f);
	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz); 
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, 10.0f);
		specular = lightColor * material.specular * specularIntensity;
	}

	vec4 texColor1 = texture(texture1, outFragmentUV);
	vec4 texColor2 = texture(texture2, outFragmentUV);
	vec4 texColor = mix(texColor1, texColor2, 0.5);

    outFragmentColor =  texColor;
	//(texture(texture1, outFragmentUV) * vec4((ambient + diffuse), 1.0f)) + vec4(specular, 1.0f);

}