#version 150 core

in vec3 Idiffuse;
out vec4 fragment;
void main()
{
    fragment=vec4(Idiffuse,1.);
}