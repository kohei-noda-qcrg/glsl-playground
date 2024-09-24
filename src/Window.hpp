#pragma once

#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* const window;

    GLfloat aspect;

  public:
    Window(int width = 640, int height = 480, const char* title = "Hello!");

    virtual ~Window() {
        glfwDestroyWindow(window);
    }

    explicit operator bool() const {
        glfwWaitEvents();
        return !glfwWindowShouldClose(window);
    }

    auto swapBuffers() const -> void;

    static auto resize(GLFWwindow* window, int width, int height) -> void;

    auto getAspect() const -> GLfloat;
};