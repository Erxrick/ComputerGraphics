#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;

uniform vec3 lightPosition;
uniform vec3 lightColor;


out vec4 outFragmentColor;

void main()
{
	vec3 ambient = ambientMaterial;

	vec3 positionToLight = normalize(lightPosition - outFragmentPosition);
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), -1.0f);
	vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;

	vec3 specular = vec3(0.0f);
	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz); 
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, 1.4f);
		specular = lightColor * specularMaterial * specularIntensity;
	}


    outFragmentColor =  vec4(ambient + diffuse + specular, 1.0f);

}