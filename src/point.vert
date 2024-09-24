#version 150 core

in vec4       position; // vertex pos
uniform float aspect;   // aspect ratio

void main() {
    gl_Position = vec4(1. / aspect, 1., 1., 1.) * position;
}