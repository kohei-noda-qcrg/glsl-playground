#version 150 core
const int Lcount=2;
uniform vec4 Lpos[Lcount];
uniform vec3 Lambient[Lcount];
uniform vec3 Ldiffuse[Lcount];
uniform vec3 Lspecular[Lcount];
layout(std140)uniform Material
{
    vec3 Kambient;
    vec3 Kdiffuse;
    vec3 Kspecular;
    float KShininess;
};
in vec4 VertexPos;
in vec3 VertexNormalVector;
out vec4 fragment;
void main()
{
    vec3 V=-normalize(VertexPos.xyz);
    vec3 Idiffuse=vec3(.0);
    vec3 Ispecular=vec3(.0);
    for(int i=0;i<Lcount;++i){
        vec3 L=normalize((Lpos[i]*VertexPos.w-VertexPos*Lpos[i].w).xyz);
        vec3 Iambient=Kambient*Lambient[i];
        Idiffuse+=max(dot(VertexNormalVector,L),.0)*Kdiffuse*Ldiffuse[i]+Iambient;
        vec3 H=normalize(L+V);
        Ispecular+=pow(max(dot(normalize(VertexNormalVector),H),.0),KShininess)*Kspecular*Lspecular[i];
    }
    fragment=vec4(Idiffuse+Ispecular,1.);
}