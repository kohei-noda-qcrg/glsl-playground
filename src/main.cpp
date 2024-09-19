#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#include "macros/assert.hpp"
#include "macros/unwrap.hpp"

auto main() -> int {

    ensure(glfwInit() == GLFW_TRUE, "Failed to initialize GLFW");
    // Register GLFW termination function
    ensure(std::atexit(glfwTerminate) == 0, "Failed to register GLFW termination function");

    print("Successfully initialized GLFW");

    const auto window = glfwCreateWindow(640, 480, "Hello, World!", NULL, NULL);
    // ensure(window == NULL, "Failed to create window");
    glfwMakeContextCurrent(window);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    print("Successfully created window");
    while(glfwWindowShouldClose(window) == GL_FALSE) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}