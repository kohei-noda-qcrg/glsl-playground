#version 150 core

uniform mat4 model;// model matrix
in vec4 position;// vertex pos

void main(){
    gl_Position=model*position;
}