#pragma once
#include <array>

#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* const window;

    std::array<GLfloat, 2> size;       // size of window in pixels
    mutable std::array<GLfloat, 2> cursor_pos; // position of cursor in normalized device coordinates

    GLfloat scale; // scale factor of device coordinate system with respect to world coordinate system

  public:
    Window(int width = 640, int height = 480, const char* title = "Hello!");

    virtual ~Window() {
        glfwDestroyWindow(window);
    }

    explicit operator bool() const {
        glfwWaitEvents();

        double x, y;
        glfwGetCursorPos(window, &x, &y);
        this->cursor_pos[0] = static_cast<GLfloat>(x) * 2.0f / size[0] - 1.0f;
        this->cursor_pos[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size[1];

        return !glfwWindowShouldClose(window);
    }

    auto swapBuffers() const -> void;

    static auto resize(GLFWwindow* window, int width, int height) -> void;

    auto getScale() const -> GLfloat;

    const auto& getSize() const {
        return size;
    }

    const auto& getCursorPos() const {
        return cursor_pos;
    }
};