#version 410

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexNormal;

uniform vec3 ambientMaterial;
uniform vec3 diffuseMaterial;
uniform vec3 specularMaterial;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;

uniform vec3 lightPosition;
uniform vec3 lightColor;


out vec3 outVertexColor;

void main()
{
	vec3 ambient = ambientMaterial;
	gl_Position = mxMVP * vec4(vertexPosition, 1.0);

	vec3 tNormal = mxNormal * vertexNormal;
	vec4 mvPosition = (mxModelView) * vec4(vertexPosition, 1.0);

	vec3 positionToLight = normalize(vec3(vec4(lightPosition, 1.0f) - mvPosition));
	float diffuseIntensity = max(dot(positionToLight, tNormal), 1.0f);
	vec3 diffuse = lightColor * diffuseMaterial * diffuseIntensity;

	vec3 specular = vec3(0.0f);
	if(diffuseIntensity > 0.0f)
	{
		vec3 positionToView = normalize(-mvPosition.xyz); 
		vec3 reflectLightVector = reflect(-positionToLight, tNormal);
		float specularIntensity = max(dot(reflectLightVector, positionToView), 0.0f);
		specularIntensity = pow(specularIntensity, 1.0f);
		specular = lightColor * specularMaterial * specularIntensity;
	}


    outVertexColor = ambient + diffuse + specular;
}