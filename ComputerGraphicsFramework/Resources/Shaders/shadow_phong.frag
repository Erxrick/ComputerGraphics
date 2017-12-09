#version 430

in vec3 outFragmentPosition;
in vec3 outFragmentNormal;
in vec2 texCoordFragment;
in vec4 shadowCoordFragment;



struct MaterialInfo
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct LightInfo
{
	vec4 position;
	vec3 diffuse;
	vec3 specular;
};

uniform MaterialInfo material;
uniform LightInfo light;

layout (location = 0) out vec4 outFragmentColor;

layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2DShadow shadowMap;


float calculateShadow()
{
	float bias = 0.005;
	// shadow = 1.0 (not in shadow)
	// shadow = 0.0 (in shadow)
	float shadow = texture(shadowMap, vec3(shadowCoordFragment.xy, (shadowCoordFragment.z)/shadowCoordFragment.w) - bias);

	return shadow;
}

void phong(vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular) 
{
    vec3 positionToLight = normalize(light.position.xyz - position);

    float diffuseIntensity = max(dot(positionToLight, normal), 0.0);
    diffuse = light.diffuse * material.diffuse * diffuseIntensity;
    vec3 ambient = material.ambient;


   // ambientDiffuse = ambient + diffuse;
    // specular calculations that were in main

    float specularIntensity = 0.0;
	specular = vec3(0.0);
    if (diffuseIntensity > 0.0)
    {
        vec3 positionToView = normalize(-outFragmentPosition.xyz);
        vec3 reflectLightVector = reflect(-positionToLight, normal);
        specularIntensity = max(dot(reflectLightVector, positionToView), 0.0);
        specularIntensity = pow(specularIntensity, material.shininess);
	    specular = light.specular *  material.specular * specularIntensity;
    }
}

void main()
{
	vec3 ambient = material.ambient;
	vec3 diffuse;
	vec3 specular;
	phong(outFragmentPosition, outFragmentNormal, diffuse, specular);
	
	vec4 textureColor = texture(diffuseMap, texCoordFragment);
	float shadow = calculateShadow();
    outFragmentColor = vec4(ambient + ((diffuse) * shadow), 1.0);
	//outFragmentColor = vec4(ambient + ((diffuse + specular) * shadow), 1.0);
}
