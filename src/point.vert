#version 150 core
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;
const vec4 Lpos=vec4(0.,0.,5.,1.);
const vec3 Lambient=vec3(.2);
const vec3 Ldiffuse=vec3(1.);
const vec3 Lspecular=vec3(1.);
const vec3 Kambient=vec3(.6,.6,.2);
const vec3 Kdiffuse=vec3(.6,.6,.2);
const vec3 Kspecular=vec3(.3);
const float KShininess=30.;
in vec4 position;
in vec3 normal;
out vec3 Idiffuse;
out vec3 Ispecular;
void main(){
    vec4 P=model*position;
    vec3 N=normalize(normalMatrix*normal);
    vec3 L=normalize((Lpos*P.w-P*Lpos.w).xyz);
    vec3 Iambient=Lambient*Kambient;
    Idiffuse=max(dot(N,L),0.)*Kdiffuse*Ldiffuse+Iambient;
    vec3 V=-normalize(P.xyz);
    vec3 R=reflect(-L,N);
    Ispecular=pow(max(dot(R,V),0.),KShininess)*Kspecular*Lspecular;
    gl_Position=projection*P;
}