#version 150 core

in vec4       position; // vertex pos
uniform vec2  size;   // window size
uniform float scale;  // scale factor of device coordinate system with respect to world coordinate system

void main() {
    gl_Position = vec4(2. * scale / size, 1., 1.) * position;
}