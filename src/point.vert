#version 150 core
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;
const int Lcount=2;
uniform vec4 Lpos[Lcount];
uniform vec3 Lambient[Lcount];
uniform vec3 Ldiffuse[Lcount];
uniform vec3 Lspecular[Lcount];
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
    vec3 V=-normalize(P.xyz);
    Idiffuse=vec3(0.);
    Ispecular=vec3(0.);
    for (int i = 0; i < Lcount; ++i){
        vec3 L=normalize((Lpos[i]*P.w-P*Lpos[i].w).xyz);
        vec3 Iambient=Lambient[i]*Kambient;
        Idiffuse+=max(dot(N,L),0.)*Kdiffuse*Ldiffuse[i]+Iambient;
        vec3 H = normalize(L+V);
        Ispecular+=pow(max(dot(N,H),0.),KShininess)*Kspecular*Lspecular[i];
    }
    gl_Position=projection*P;
}