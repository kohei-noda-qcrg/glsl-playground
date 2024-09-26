#version 150 core
uniform mat4 model;
uniform mat4 projection;
in vec4 position;

void main(){
    gl_Position=projection*model*position;
}