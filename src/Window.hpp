#pragma once
#include <array>

#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* const window;

    std::array<GLfloat, 2> size; // size of window in pixels

    GLfloat scale; // scale factor of device coordinate system with respect to world coordinate system

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

    auto getScale() const -> GLfloat;

    const auto& getSize() const {
        return size;
    }
};