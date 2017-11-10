#version 410

in vec3 colorFragment;

out vec4 outFragmentColor;

void main()
{
   outFragmentColor = vec4(colorFragment, 1.0);
}