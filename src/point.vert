#version 150 core
uniform mat4 model;
uniform mat4 projection;
uniform mat3 normalMatrix;
in vec4 position;
in vec3 normal;
out vec4 VertexPos;
out vec3 VertexNormalVector;
void main(){
    VertexPos=model*position;
    VertexNormalVector=normalize(normalMatrix*normal);
    gl_Position=projection*VertexPos;
}