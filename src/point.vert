#version 150 core
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;
const vec4 Lpos=vec4(0.,0.,5.,1.);
const vec3 Ldiffuse=vec3(1.);
const vec3 Kdiffuse=vec3(.6,.6,.2);
in vec4 position;
in vec3 normal;
out vec3 Idiffuse;
void main(){
    vec4 P=model*position;
    vec3 N=normalize(normalMatrix*normal);
    vec3 L=normalize((Lpos*P.w-P*Lpos.w).xyz);
    Idiffuse=max(dot(N,L),0.)*Kdiffuse*Ldiffuse;
    gl_Position=projection*P;
}