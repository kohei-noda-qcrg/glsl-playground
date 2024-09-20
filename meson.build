project('glsl', 'cpp', version: '1.0.0', default_options : ['warning_level=3', 'werror=false', 'cpp_std=c++20'])
add_project_arguments('-Wfatal-errors', language: 'cpp')
add_project_arguments('-Wno-missing-field-initializers', language: 'cpp')

deps = [
    dependency('gl', required: true),
    dependency('glew', required: true),
    dependency('glfw3', required: true),
    dependency('x11', required: true),
    dependency('xrandr', required: true),
    dependency('threads'),
]


src = files('src/main.cpp')

executable('glsl', src, dependencies: deps)