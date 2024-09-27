#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Matrix.hpp"
#include "Shape.hpp"
#include "ShapeIndex.hpp"
#include "SolidShape.hpp"
#include "SolidShapeIndex.hpp"
#include "Window.hpp"
#include "macros/assert.hpp"
#include "macros/unwrap.hpp"
#include "shape-example.hpp"
#include "util/file-io.hpp"
#include "util/span.hpp"
#include "util/print.hpp"

// print the result of a shader compilation
auto printShaderInfoLog(GLuint shader, const char* str) -> GLboolean {
    auto status = GLint{};
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        warn("Compiler error in shader: ", str);
    }

    auto log_length = GLint{};
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 0) {
        auto log = std::vector<GLchar>(log_length);
        glGetShaderInfoLog(shader, log_length, NULL, log.data());
        warn("Shader Info Log: ", log.data());
    }

    return static_cast<GLboolean>(status);
}

// print the result of linking a program
auto printProgramInfoLog(GLuint program) -> GLboolean {
    auto status = GLint{};
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        warn("Linker error in program");
    }

    auto log_length = GLint{};
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    if(log_length > 0) {
        auto log = std::vector<GLchar>(log_length);
        glGetProgramInfoLog(program, log_length, NULL, log.data());
        warn("Program Info Log: ", log.data());
    }

    return static_cast<GLboolean>(status);
}

auto createProgram(const char* vsrc, const char* fsrc) -> GLuint {
    const auto program = glCreateProgram();

    if(vsrc != NULL) {
        const auto vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);
        if(printShaderInfoLog(vobj, "vertex shader")) {
            glAttachShader(program, vobj);
        }
        glDeleteShader(vobj);
    }

    if(fsrc != NULL) {
        const auto fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);
        if(printShaderInfoLog(fobj, "fragment shader")) {
            glAttachShader(program, fobj);
        }
        glDeleteShader(fobj);
    }

    glBindAttribLocation(program, 0, "position");
    glBindAttribLocation(program, 1, "color");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);

    if(printProgramInfoLog(program)) {
        return program;
    }

    glDeleteProgram(program);
    return 0;
}

auto loadProgram(const std::filesystem::path vert_path, const std::filesystem::path frag_path) -> GLuint {
    constexpr auto error_value = GLuint{0};
    unwrap_v(vert_file, read_file(vert_path.c_str()));
    const auto vert_str = from_span(vert_file);
    unwrap_v(frag_file, read_file(frag_path.c_str()));
    const auto frag_str = from_span(frag_file);
    return createProgram(vert_str.data(), frag_str.data());
}

auto main(const int /*argc*/, const char* const argv[]) -> int {

    ensure(glfwInit() != GLFW_FALSE, "Failed to initialize GLFW");
    // Register GLFW termination function
    ensure(std::atexit(glfwTerminate) == 0, "Failed to register GLFW termination function");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    print("Successfully initialized GLFW");

    glfwSwapInterval(1);
    auto window = Window();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    const auto cwd           = std::filesystem::current_path();
    const auto command       = std::filesystem::path(std::string(argv[0]));
    const auto cmd_full_path = command.is_absolute() ? command : cwd / command;
    const auto this_file     = cmd_full_path.parent_path() / std::filesystem::path(__FILE__);
    const auto point_vert    = this_file.parent_path() / "point.vert";
    const auto point_frag    = this_file.parent_path() / "point.frag";

    const auto program = loadProgram(point_vert, point_frag);

    const auto modelviewLoc  = glGetUniformLocation(program, "model");
    const auto projectionLoc = glGetUniformLocation(program, "projection");
    const auto shape         = std::unique_ptr<const Shape>(new SolidShape(shape_example::solidCubeVertex));
    const auto shape_oct     = std::unique_ptr<const Shape>(new Shape(shape_example::octahedronVertex));

    glfwSetTime(0.0);

    print("Successfully created window");
    while(window) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        const auto* const size = window.getSize().data();
        // projection
        const auto fovy       = window.getScale() * 0.01f;
        const auto aspect     = size[0] / size[1];
        const auto projection = Matrix::perspective(fovy, aspect, 1.0f, 10.0f);
        // model
        const auto* const location = window.getCursorPos().data();
        const auto        rotate   = Matrix::rotate(0.0f, 0.0f, 1.0f, static_cast<GLfloat>(glfwGetTime()));
        const auto        model    = Matrix::translate(location[0], location[1], 0.0f) * rotate;
        // view transform matrix
        const auto pov    = std::array<GLfloat, 3>{3.0f, 4.0f, 5.0f};
        const auto target = std::array<GLfloat, 3>{0.0f, 0.0f, 0.0f};
        const auto up     = std::array<GLfloat, 3>{0.0f, 1.0f, 0.0f};
        const auto view   = Matrix::lookAt(pov, target, up);
        // modelview transform matrix
        const auto modelview = model * view;
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
        glUniformMatrix4fv(modelviewLoc, 1, GL_FALSE, modelview.data());
        shape->draw();
        shape_oct->draw();
        window.swapBuffers();
    }
    return 0;
}
