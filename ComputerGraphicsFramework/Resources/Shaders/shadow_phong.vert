#version 430

layout (location=0) in vec3 positionVertex;
layout (location=1) in vec3 normalVertex;
layout (location=2) in vec2 texCoordVertex;

out vec3 outFragmentPosition;
out vec3 outFragmentNormal;
out vec2 texCoordFragment;
out vec4 shadowCoordFragment;

uniform mat4 mxModelView;
uniform mat4 mxMVP;
uniform mat3 mxNormal;
uniform mat4 mxMLP;

void main()
{
	outFragmentPosition = vec3(mxModelView * vec4(positionVertex, 1.0));
	outFragmentNormal = normalize(mxNormal * normalVertex);
	texCoordFragment = texCoordVertex;
	shadowCoordFragment = mxMLP * vec4(positionVertex, 1.0);
    	gl_Position = mxMVP * vec4(positionVertex, 1.0);
}
