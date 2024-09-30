#version 150 core
in vec3 Idiffuse;
in vec3 Ispecular;
out vec4 fragment;
void main()
{
    fragment=vec4(Idiffuse+Ispecular,1.);
}