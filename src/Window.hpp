#pragma once
#include <array>

#include <GLFW/glfw3.h>

class Window {
    GLFWwindow* const window;

    std::array<GLfloat, 2> size;       // size of window in pixels
    std::array<GLfloat, 2> cursor_pos; // position of cursor in normalized device coordinates

    int key_status; // status of key input

    GLfloat scale; // scale factor of device coordinate system with respect to world coordinate system

  public:
    Window(int width = 640, int height = 480, const char* title = "Hello!");

    virtual ~Window() {
        glfwDestroyWindow(window);
    }

    explicit operator bool() const;

    auto swapBuffers() const -> void;

    static auto resize(GLFWwindow* window, int width, int height) -> void;
    static auto wheel(GLFWwindow* window, double x, double y) -> void;
    static auto keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;

    auto getScale() const -> GLfloat;

    const auto& getSize() const {
        return size;
    }

    const auto& getCursorPos() const {
        return cursor_pos;
    }
};