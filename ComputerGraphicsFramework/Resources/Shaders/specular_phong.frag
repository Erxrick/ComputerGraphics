#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 outFragmentUV;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;

uniform vec3 lightPosition;
uniform vec3 lightColor;

layout (binding=0) uniform sampler2D texture1;
layout (binding=1) uniform sampler2D texture2;

out vec4 outFragmentColor;

void main()
{
	vec3 ambient = ambientMaterial;

	vec3 positionToLight = normalize(lightPosition - outFragmentPosition);
	float diffuseIntensity = max(dot(positionToLight, outFragmentNormal), -1.0f);
	vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;

	vec4 texColor= vec4(0.0f);
	vec4 specularColor= vec4(0.0f);
	vec3 specular = vec3(0.0f);

	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-outFragmentPosition.xyz); 
		vec3 reflectLightVector = reflect(-positionToLight, outFragmentNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, 10.0f);
		specular = vec3(texture(texture2, outFragmentUV)) * lightColor * specularMaterial * specularIntensity;
		specularColor = texture(texture2, outFragmentUV);
	}

	texColor = texture(texture1, outFragmentUV);
	outFragmentColor = ((vec4(ambient + diffuse, 1.0) * texColor) + vec4(specular, 1.0) * specularColor);
	//	outFragmentColor =  (texture(texture1, outFragmentUV) * vec4((ambient + diffuse), 1.0f)) + vec4(specular, 1.0f);

}