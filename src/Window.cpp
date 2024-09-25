#include "GL/glew.h"

#include "Window.hpp"
#include "macros/assert.hpp"

Window::Window(int width, int height, const char* title)
    : window(glfwCreateWindow(width, height, title, NULL, NULL)), cursor_pos({0.0f, 0.0f}), scale(100.0f) {
    if(window == NULL) {
        warn("failed to create GLFW window");
        exit(1);
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        warn("failed to initialize GLEW");
        exit(1);
    }

    glfwSwapInterval(1);

    glfwSetWindowUserPointer(window, this);

    glfwSetWindowSizeCallback(window, resize);
    glfwSetScrollCallback(window, wheel);
    resize(window, width, height);
}

Window::operator bool() const {
    glfwWaitEvents();

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
        instance->cursor_pos[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
        instance->cursor_pos[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];
    }

    return !glfwWindowShouldClose(window);
}

auto Window::swapBuffers() const -> void {
    glfwSwapBuffers(window);
}

auto Window::resize(GLFWwindow* window, int width, int height) -> void {
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);
    glViewport(0, 0, fbwidth, fbheight);

    auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(instance != NULL) {
        instance->size[0] = static_cast<GLfloat>(width);
        instance->size[1] = static_cast<GLfloat>(height);
    }
}

auto Window::wheel(GLFWwindow* window, double /*x*/, double y) -> void {
    auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(instance != NULL) {
        instance->scale += static_cast<GLfloat>(y * 5.0f);
    }
}

auto Window::getScale() const -> GLfloat {
    return scale;
}